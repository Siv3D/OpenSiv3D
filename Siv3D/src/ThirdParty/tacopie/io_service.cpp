// MIT License
//
// Copyright (c) 2016-2017 Simon Ninon <simon.ninon@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <tacopie/network/io_service.hpp>
#include <tacopie/utils/error.hpp>
#include <tacopie/utils/logger.hpp>

#include <fcntl.h>

#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif /* _WIN32 */

namespace tacopie {

//!
//! default io_service getter & setter
//!

static std::shared_ptr<io_service> io_service_default_instance = nullptr;

const std::shared_ptr<io_service>&
get_default_io_service(std::uint32_t num_io_workers) {
  if (io_service_default_instance == nullptr) {
    io_service_default_instance = std::make_shared<io_service>(num_io_workers);
  }
  else {
    io_service_default_instance->set_nb_workers(num_io_workers);
  }

  return io_service_default_instance;
}

void
set_default_io_service(const std::shared_ptr<io_service>& service) {
  __TACOPIE_LOG(debug, "setting new default_io_service");
  io_service_default_instance = service;
}

//!
//! ctor & dtor
//!

io_service::io_service(std::size_t nb_threads)
#ifdef _WIN32
: m_should_stop(ATOMIC_VAR_INIT(false))
#else
: m_should_stop(false)
#endif /* _WIN32 */
, m_callback_workers(nb_threads) {
  __TACOPIE_LOG(debug, "create io_service");

  //! Start worker after everything has been initialized
  m_poll_worker = std::thread(std::bind(&io_service::poll, this));
}

io_service::~io_service(void) {
  __TACOPIE_LOG(debug, "destroy io_service");

  m_should_stop = true;

  m_notifier.notify();
  if (m_poll_worker.joinable()) {
    m_poll_worker.join();
  }
  m_callback_workers.stop();
}

//!
//! io service workers
//!
void
io_service::set_nb_workers(std::size_t nb_threads) {
  m_callback_workers.set_nb_threads(nb_threads);
}


//!
//! poll worker function
//!

void
io_service::poll(void) {
  __TACOPIE_LOG(debug, "starting poll() worker");

  while (!m_should_stop) {
    int ndfs = init_poll_fds_info();

    //! setup timeout
    struct timeval* timeout_ptr = NULL;
#ifdef __TACOPIE_TIMEOUT
    struct timeval timeout;
    timeout.tv_usec = __TACOPIE_TIMEOUT;
    timeout_ptr     = &timeout;
#endif /* __TACOPIE_TIMEOUT */

    __TACOPIE_LOG(debug, "polling fds");
    if (select(ndfs, &m_rd_set, &m_wr_set, NULL, timeout_ptr) > 0) {
      process_events();
    }
    else {
      __TACOPIE_LOG(debug, "poll woke up, but nothing to process");
    }
  }

  __TACOPIE_LOG(debug, "stop poll() worker");
}

//!
//! process poll detected events
//!

void
io_service::process_events(void) {
  std::lock_guard<std::mutex> lock(m_tracked_sockets_mtx);

  __TACOPIE_LOG(debug, "processing events");

  for (const auto& fd : m_polled_fds) {
    if (fd == m_notifier.get_read_fd() && FD_ISSET(fd, &m_rd_set)) {
      m_notifier.clr_buffer();
      continue;
    }

    auto it = m_tracked_sockets.find(fd);

    if (it == m_tracked_sockets.end()) { continue; }

    auto& socket = it->second;

    if (FD_ISSET(fd, &m_rd_set) && socket.rd_callback && !socket.is_executing_rd_callback) {
      process_rd_event(fd, socket);
    }
    if (FD_ISSET(fd, &m_wr_set) && socket.wr_callback && !socket.is_executing_wr_callback) {
      process_wr_event(fd, socket);
    }

    if (socket.marked_for_untrack && !socket.is_executing_rd_callback && !socket.is_executing_wr_callback) {
      __TACOPIE_LOG(debug, "untrack socket");
      m_tracked_sockets.erase(it);
      m_wait_for_removal_condvar.notify_all();
    }
  }
}

void
io_service::process_rd_event(const fd_t& fd, tracked_socket& socket) {
  __TACOPIE_LOG(debug, "processing read event");

  auto rd_callback = socket.rd_callback;

  socket.is_executing_rd_callback = true;

  m_callback_workers << [=] {
    __TACOPIE_LOG(debug, "execute read callback");
    rd_callback(fd);

    std::lock_guard<std::mutex> lock(m_tracked_sockets_mtx);
    auto it = m_tracked_sockets.find(fd);

    if (it == m_tracked_sockets.end()) { return; }

    auto& socket                    = it->second;
    socket.is_executing_rd_callback = false;

    if (socket.marked_for_untrack && !socket.is_executing_wr_callback) {
      __TACOPIE_LOG(debug, "untrack socket");
      m_tracked_sockets.erase(it);
      m_wait_for_removal_condvar.notify_all();
    }

    m_notifier.notify();
  };
}

void
io_service::process_wr_event(const fd_t& fd, tracked_socket& socket) {
  __TACOPIE_LOG(debug, "processing write event");

  auto wr_callback = socket.wr_callback;

  socket.is_executing_wr_callback = true;

  m_callback_workers << [=] {
    __TACOPIE_LOG(debug, "execute write callback");
    wr_callback(fd);

    std::lock_guard<std::mutex> lock(m_tracked_sockets_mtx);
    auto it = m_tracked_sockets.find(fd);

    if (it == m_tracked_sockets.end()) { return; }

    auto& socket                    = it->second;
    socket.is_executing_wr_callback = false;

    if (socket.marked_for_untrack && !socket.is_executing_rd_callback) {
      __TACOPIE_LOG(debug, "untrack socket");
      m_tracked_sockets.erase(it);
      m_wait_for_removal_condvar.notify_all();
    }

    m_notifier.notify();
  };
}

//!
//! init m_poll_fds_info
//!

int
io_service::init_poll_fds_info(void) {
  std::lock_guard<std::mutex> lock(m_tracked_sockets_mtx);

  m_polled_fds.clear();
  FD_ZERO(&m_rd_set);
  FD_ZERO(&m_wr_set);

  int ndfs = (int) m_notifier.get_read_fd();
  FD_SET(m_notifier.get_read_fd(), &m_rd_set);
  m_polled_fds.push_back(m_notifier.get_read_fd());

  for (const auto& socket : m_tracked_sockets) {
    const auto& fd          = socket.first;
    const auto& socket_info = socket.second;

    bool should_rd = socket_info.rd_callback && !socket_info.is_executing_rd_callback;
    if (should_rd) {
      FD_SET(fd, &m_rd_set);
    }

    bool should_wr = socket_info.wr_callback && !socket_info.is_executing_wr_callback;
    if (should_wr) {
      FD_SET(fd, &m_wr_set);
    }

    if (should_rd || should_wr || socket_info.marked_for_untrack) {
      m_polled_fds.push_back(fd);
    }

    if ((should_rd || should_wr) && (int) fd > ndfs) {
      ndfs = (int) fd;
    }
  }

  return ndfs + 1;
}

//!
//! track & untrack socket
//!

void
io_service::track(const tcp_socket& socket, const event_callback_t& rd_callback, const event_callback_t& wr_callback) {
  std::lock_guard<std::mutex> lock(m_tracked_sockets_mtx);

  __TACOPIE_LOG(debug, "track new socket");

  auto& track_info              = m_tracked_sockets[socket.get_fd()];
  track_info.rd_callback        = rd_callback;
  track_info.wr_callback        = wr_callback;
  track_info.marked_for_untrack = false;

  m_notifier.notify();
}

void
io_service::set_rd_callback(const tcp_socket& socket, const event_callback_t& event_callback) {
  std::lock_guard<std::mutex> lock(m_tracked_sockets_mtx);

  __TACOPIE_LOG(debug, "update read socket tracking callback");

  auto& track_info       = m_tracked_sockets[socket.get_fd()];
  track_info.rd_callback = event_callback;

  m_notifier.notify();
}

void
io_service::set_wr_callback(const tcp_socket& socket, const event_callback_t& event_callback) {
  std::lock_guard<std::mutex> lock(m_tracked_sockets_mtx);

  __TACOPIE_LOG(debug, "update write socket tracking callback");

  auto& track_info       = m_tracked_sockets[socket.get_fd()];
  track_info.wr_callback = event_callback;

  m_notifier.notify();
}

void
io_service::untrack(const tcp_socket& socket) {
  std::lock_guard<std::mutex> lock(m_tracked_sockets_mtx);

  auto it = m_tracked_sockets.find(socket.get_fd());

  if (it == m_tracked_sockets.end()) { return; }

  if (it->second.is_executing_rd_callback || it->second.is_executing_wr_callback) {
    __TACOPIE_LOG(debug, "mark socket for untracking");
    it->second.marked_for_untrack = true;
  }
  else {
    __TACOPIE_LOG(debug, "untrack socket");
    m_tracked_sockets.erase(it);
    m_wait_for_removal_condvar.notify_all();
  }

  m_notifier.notify();
}

//!
//! wait until the socket has been effectively removed
//! basically wait until all pending callbacks are executed
//!

void
io_service::wait_for_removal(const tcp_socket& socket) {
  std::unique_lock<std::mutex> lock(m_tracked_sockets_mtx);

  __TACOPIE_LOG(debug, "waiting for socket removal");

  m_wait_for_removal_condvar.wait(lock, [&]() {
    __TACOPIE_LOG(debug, "socket has been removed");

    return m_tracked_sockets.find(socket.get_fd()) == m_tracked_sockets.end();
  });
}

} // namespace tacopie
