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
#include <cstdint>
#include <list>
#include <memory>
#include <mutex>
#include <string>

#include <tacopie/network/io_service.hpp>
#include <tacopie/network/tcp_client.hpp>
#include <tacopie/network/tcp_socket.hpp>
#include <tacopie/utils/typedefs.hpp>

#define __TACOPIE_CONNECTION_QUEUE_SIZE 1024

namespace tacopie {

//!
//! tacopie::tcp_server is the class providing TCP Server features.
//! The tcp_server works entirely asynchronously, waiting for the io_service to notify whenever a new client wished to connect.
//!
class tcp_server {
public:
  //! ctor
  tcp_server(void);
  //! dtor
  ~tcp_server(void);

  //! copy ctor
  tcp_server(const tcp_server&) = delete;
  //! assignment operator
  tcp_server& operator=(const tcp_server&) = delete;

public:
  //!
  //! comparison operator
  //!
  //! \return true when the underlying sockets are the same (same file descriptor and socket type).
  //!
  bool operator==(const tcp_server& rhs) const;

  //!
  //! comparison operator
  //!
  //! \return true when the underlying sockets are different (different file descriptor or socket type).
  //!
  bool operator!=(const tcp_server& rhs) const;

public:
  //!
  //! callback called whenever a new client is connecting to the server
  //!
  //! Takes as parameter a shared pointer to the tcp_client that wishes to connect
  //! Returning true means connection is handled by tcp_client wrapper and nothing will be done by tcp_server. Returning false means connection is handled by tcp_server, will be stored in an internal list and tcp_client disconection_handler overriden.
  //!
  typedef std::function<bool(const std::shared_ptr<tcp_client>&)> on_new_connection_callback_t;

  //!
  //! Start the tcp_server at the given host and port.
  //!
  //! \param host hostname to be connected to
  //! \param port port to be connected to
  //! \param callback callback to be called on new connections (may be null, connections are then handled automatically by the tcp_server object)
  //!
  void start(const std::string& host, std::uint32_t port, const on_new_connection_callback_t& callback = nullptr);

  //!
  //! Disconnect the tcp_server if it was currently running.
  //!
  //! \param wait_for_removal When sets to true, disconnect blocks until the underlying TCP server has been effectively removed from the io_service and that all the underlying callbacks have completed.
  //! \param recursive_wait_for_removal When sets to true and wait_for_removal is also set to true, blocks until all the underlying TCP client connected to the TCP server have been effectively removed from the io_service and that all the underlying callbacks have completed.
  //!
  void stop(bool wait_for_removal = false, bool recursive_wait_for_removal = true);

  //!
  //! \return whether the server is currently running or not
  ///!
  bool is_running(void) const;

public:
  //!
  //! \return the tacopie::tcp_socket associated to the server. (non-const version)
  //!
  tcp_socket& get_socket(void);

  //!
  //! \return the tacopie::tcp_socket associated to the server. (const version)
  //!
  const tcp_socket& get_socket(void) const;

public:
  //!
  //! \return io service monitoring this tcp connection
  //!
  const std::shared_ptr<tacopie::io_service>& get_io_service(void) const;

public:
  //!
  //! \return the list of tacopie::tcp_client connected to the server.
  //!
  const std::list<std::shared_ptr<tacopie::tcp_client>>& get_clients(void) const;

private:
  //!
  //! io service read callback
  //!
  //! \param fd socket that triggered the read callback
  //!
  void on_read_available(fd_t fd);

  //!
  //! client disconnected
  //! called whenever a client disconnected from the tcp_server
  //!
  //! \param client disconnected client
  //!
  void on_client_disconnected(const std::shared_ptr<tcp_client>& client);

private:
  //!
  //! store io_service
  //! prevent deletion of io_service before the tcp_server itself
  //!
  std::shared_ptr<io_service> m_io_service;

  //1
  //! server socket
  //!
  tacopie::tcp_socket m_socket;

  //!
  //! whether the server is currently running or not
  //!
  std::atomic<bool> m_is_running = ATOMIC_VAR_INIT(false);

  //!
  //! clients
  //!
  std::list<std::shared_ptr<tacopie::tcp_client>> m_clients;

  //!
  //! clients thread safety
  //!
  std::mutex m_clients_mtx;

  //!
  //! on new connection callback
  //!
  on_new_connection_callback_t m_on_new_connection_callback;
};

} // namespace tacopie
