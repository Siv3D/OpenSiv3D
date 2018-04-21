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

#pragma once

#include <atomic>
#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <vector>

#ifdef _WIN32
#include <Winsock2.h>
#else
#include <sys/select.h>
#endif /* _WIN32 */

#include <tacopie/network/self_pipe.hpp>
#include <tacopie/network/tcp_socket.hpp>
#include <tacopie/utils/thread_pool.hpp>

#ifndef __TACOPIE_IO_SERVICE_NB_WORKERS
#define __TACOPIE_IO_SERVICE_NB_WORKERS 1
#endif /* __TACOPIE_IO_SERVICE_NB_WORKERS */

namespace tacopie {

//!
//! service that operates IO Handling.
//! It polls sockets for input and output, processes read and write operations and calls the appropriate callbacks.
//!
class io_service {
public:
  //!
  //! ctor
  //!
  //! \param nb_threads defines the number of background threads that will be used to process read and write callbacks. This must be a strictly positive value.
  //!
  io_service(std::size_t nb_threads = __TACOPIE_IO_SERVICE_NB_WORKERS);

  //! dtor
  ~io_service(void);

  //! copy ctor
  io_service(const io_service&) = delete;
  //! assignment operator
  io_service& operator=(const io_service&) = delete;

public:
  //!
  //! reset number of io_service workers assigned to this io_service
  //! this can be safely called at runtime, even if the io_service is currently running
  //! it can be useful if you need to re-adjust the number of workers
  //!
  //! \param nb_threads number of workers
  //!
  void set_nb_workers(std::size_t nb_threads);

public:
  //! callback handler typedef
  //! called on new socket event if register to io_service
  typedef std::function<void(fd_t)> event_callback_t;

  //!
  //! track socket
  //! add socket to io_service tracking for read/write operation
  //! socket is polled only if read or write callback is defined
  //!
  //! \param socket socket to be tracked
  //! \param rd_callback callback to be executed on read event
  //! \param wr_callback callback to be executed on write event
  //!
  void track(const tcp_socket& socket, const event_callback_t& rd_callback = nullptr, const event_callback_t& wr_callback = nullptr);

  //!
  //! update the read callback
  //! if socket is not tracked yet, track it
  //!
  //! \param socket socket to be tracked
  //! \param event_callback callback to be executed on read event
  //!
  void set_rd_callback(const tcp_socket& socket, const event_callback_t& event_callback);

  //!
  //! update the write callback
  //! if socket is not tracked yet, track it
  //!
  //! \param socket socket to be tracked
  //! \param event_callback callback to be executed on write event
  //!
  void set_wr_callback(const tcp_socket& socket, const event_callback_t& event_callback);

  //!
  //! remove socket from io_service tracking
  //! socket is marked for untracking and will effectively be removed asynchronously from tracking once
  //!  * poll wakes up
  //!  * no callback are being executed for that socket
  //!
  //! re-adding track while socket is pending for untrack is fine and will simply cancel the untrack operation
  //!
  //! \param socket socket to be untracked
  //!
  void untrack(const tcp_socket& socket);

  //!
  //! wait until the socket has been effectively removed
  //! basically wait until all pending callbacks are executed
  //!
  //! \param socket socket to wait for
  //!
  void wait_for_removal(const tcp_socket& socket);

private:
  //!
  //! struct tracked_socket
  //! contains information about what a current socket is tracking
  //!  * rd_callback: callback to be executed on read availability
  //!  * is_executing_rd_callback: whether the rd callback is currently being executed or not
  //!  * wr_callback: callback to be executed on write availability
  //!  * is_executing_wr_callback: whether the wr callback is currently being executed or not
  //!  * marked_for_untrack: whether the socket is marked for being untrack (that is, will be untracked whenever all the callback completed their execution)
  //!
  //!
  struct tracked_socket {
    //! ctor
    tracked_socket(void)
    : rd_callback(nullptr)
    , wr_callback(nullptr) {}

    //! rd event
    event_callback_t rd_callback;
    std::atomic<bool> is_executing_rd_callback = ATOMIC_VAR_INIT(false);

    //! wr event
    event_callback_t wr_callback;
    std::atomic<bool> is_executing_wr_callback = ATOMIC_VAR_INIT(false);

    //! marked for untrack
    std::atomic<bool> marked_for_untrack = ATOMIC_VAR_INIT(false);
  };

private:
  //!
  //! poll worker function
  //! main loop of the background thread in charge of the io_service in charge of polling fds
  //!
  void poll(void);

  //!
  //! init m_poll_fds_info
  //! simply initialize m_polled_fds variable based on m_tracked_sockets information
  //!
  //! \return maximum fd value polled
  //!
  int init_poll_fds_info(void);

  //!
  //! process poll detected events
  //! called whenever select/poll completed to check read and write availablity
  //!
  void process_events(void);

  //!
  //! process read event reported by select/poll for a given socket
  //!
  //! \param fd fd for which a read event has been reported
  //! \param socket tracked_socket associated to the given fd
  //!
  void process_rd_event(const fd_t& fd, tracked_socket& socket);

  //!
  //! process write event reported by select/poll for a given socket
  //!
  //! \param fd fd for which a write event has been reported
  //! \param socket tracked_socket associated to the given fd
  //!
  void process_wr_event(const fd_t& fd, tracked_socket& socket);

private:
  //!
  //! tracked sockets
  //!
  std::unordered_map<fd_t, tracked_socket> m_tracked_sockets;

  //!
  //! whether the worker should stop or not
  //!
  std::atomic<bool> m_should_stop;

  //!
  //! poll thread
  //!
  std::thread m_poll_worker;

  //!
  //! callback workers
  //!
  utils::thread_pool m_callback_workers;

  //!
  //! thread safety
  //!
  std::mutex m_tracked_sockets_mtx;

  //!
  //! data structure given to select (list of fds to poll)
  //!
  std::vector<fd_t> m_polled_fds;

  //!
  //! data structure given to select (list of fds to poll for read)
  //!
  fd_set m_rd_set;

  //!
  //! data structure given to select (list of fds to poll for write)
  //!
  fd_set m_wr_set;

  //!
  //! condition variable to wait on removal
  //!
  std::condition_variable m_wait_for_removal_condvar;

  //!
  //! fd associated to the pipe used to wake up the poll call
  //!
  tacopie::self_pipe m_notifier;
};

//!
//! default io_service getter & setter
//! if the default is fetched for the first time, build it, otherwise return the current instance
//! if the io_service already exist, return it and reset its number of workers if necessary
//!
//! \param num_io_workers defines the number of background threads that will be used to process read and write callbacks. This must be a strictly positive value.
//! \return shared_ptr to the default instance of the io_service
//!
const std::shared_ptr<io_service>& get_default_io_service(std::uint32_t num_io_workers = 1);

//!
//! set the default io_service to be returned by get_default_io_service
//!
//! \param service the service to be used as the default io_service instance
//!
void set_default_io_service(const std::shared_ptr<io_service>& service);

} // namespace tacopie
