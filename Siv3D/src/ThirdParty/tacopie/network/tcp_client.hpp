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
#include <mutex>
#include <queue>
#include <string>

#include <tacopie/network/io_service.hpp>
#include <tacopie/network/tcp_socket.hpp>
#include <tacopie/utils/typedefs.hpp>

namespace tacopie {

//!
//! tacopie::tcp_server is the class providing TCP Client features.
//! The tcp_client works entirely asynchronously
//!
class tcp_client {
public:
  //! ctor & dtor
  tcp_client(std::uint32_t num_io_workers = 1);
  ~tcp_client(void);

  //!
  //! custom ctor
  //! build socket from existing socket
  //!
  //! \param socket tcp_socket instance to be used for building the client (socket will be moved)
  //!
  explicit tcp_client(tcp_socket&& socket);

  //! copy ctor
  tcp_client(const tcp_client&) = delete;
  //! assignment operator
  tcp_client& operator=(const tcp_client&) = delete;

public:
  //!
  //! comparison operator
  //!
  //! \return true when the underlying sockets are the same (same file descriptor and socket type).
  //!
  bool operator==(const tcp_client& rhs) const;

  //!
  //! comparison operator
  //!
  //! \return true when the underlying sockets are different (different file descriptor or socket type).
  //!
  bool operator!=(const tcp_client& rhs) const;

public:
  //!
  //! \return the hostname associated with the underlying socket.
  //!
  const std::string& get_host(void) const;

  //!
  //! \return the port associated with the underlying socket.
  //!
  std::uint32_t get_port(void) const;

public:
  //!
  //! Connect the socket to the remote server.
  //!
  //! \param host Hostname of the target server
  //! \param port Port of the target server
  //! \param timeout_msecs maximum time to connect (will block until connect succeed or timeout expire). 0 will block undefinitely. If timeout expires, connection fails
  //!
  void connect(const std::string& host, std::uint32_t port, std::uint32_t timeout_msecs = 0);

  //!
  //! Disconnect the tcp_client if it was currently connected.
  //!
  //! \param wait_for_removal When sets to true, disconnect blocks until the underlying TCP client has been effectively removed from the io_service and that all the underlying callbacks have completed.
  //!
  void disconnect(bool wait_for_removal = false);

  //!
  //! \return whether the client is currently connected or not
  //!
  bool is_connected(void) const;

private:
  //!
  //! Call the user-defined disconnection handler
  //!
  void call_disconnection_handler(void);

public:
  //!
  //! structure to store read requests result
  //!  * success: Whether the read operation has succeeded or not. If false, the client has been disconnected
  //!  * buffer: Vector containing the read bytes
  //!
  struct read_result {
    //!
    //! whether the operation succeeeded or not
    //!
    bool success;
    //!
    //! read bytes
    //!
    std::vector<char> buffer;
  };

  //!
  //! structure to store write requests result
  //!  * success: Whether the write operation has succeeded or not. If false, the client has been disconnected
  //!  * size: Number of bytes written
  //!
  struct write_result {
    //!
    //! whether the operation succeeeded or not
    //!
    bool success;
    //!
    //! number of bytes written
    //!
    std::size_t size;
  };

public:
  //!
  //! callback to be called on async read completion
  //! takes the read_result as a parameter
  //!
  typedef std::function<void(read_result&)> async_read_callback_t;

  //!
  //! callback to be called on async write completion
  //! takes the write_result as a parameter
  //!
  typedef std::function<void(write_result&)> async_write_callback_t;

public:
  //!
  //! structure to store read requests information
  //!  * size: Number of bytes to read
  //!  * async_read_callback: Callback to be called on a read operation completion, even though the operation read less bytes than requested.
  //!
  struct read_request {
    //!
    //! number of bytes to read
    //!
    std::size_t size;
    //!
    //! callback to be executed on read operation completion
    //!
    async_read_callback_t async_read_callback;
  };

  //!
  //! structure to store write requests information
  //!  * buffer: Bytes to be written
  //!  * async_write_callback: Callback to be called on a write operation completion, even though the operation wrote less bytes than requested.
  //!
  struct write_request {
    //!
    //! bytes to write
    //!
    std::vector<char> buffer;
    //!
    //! callback to be executed on write operation completion
    //!
    async_write_callback_t async_write_callback;
  };

public:
  //!
  //! async read operation
  //!
  //! \param request read request information
  //!
  void async_read(const read_request& request);

  //!
  //! async write operation
  //!
  //! \param request write request information
  //!
  void async_write(const write_request& request);

public:
  //!
  //! \return underlying tcp_socket (non-const version)
  //!
  tacopie::tcp_socket& get_socket(void);

  //!
  //! \return underlying tcp_socket (const version)
  //!
  const tacopie::tcp_socket& get_socket(void) const;

public:
  //!
  //! \return io service monitoring this tcp connection
  //!
  const std::shared_ptr<tacopie::io_service>& get_io_service(void) const;

public:
  //!
  //! disconnection handle
  //! called whenever a disconnection occured
  //!
  //!
  typedef std::function<void()> disconnection_handler_t;

  //!
  //! set on disconnection handler
  //!
  //! \param disconnection_handler the handler to be called on disconnection
  //!
  void set_on_disconnection_handler(const disconnection_handler_t& disconnection_handler);

private:
  //!
  //! io service read callback
  //! called by the io service whenever the socket is readable
  //!
  //! \param fd file description of the socket for which the read is available
  //!
  void on_read_available(fd_t fd);

  //!
  //! io service write callback
  //! called by the io service whenever the socket is writable
  //!
  //! \param fd file description of the socket for which the write is available
  //!
  void on_write_available(fd_t fd);

private:
  //!
  //! Clear pending read requests (basically empty the queue of read requests)
  //!
  void clear_read_requests(void);

  //!
  //! Clear pending write requests (basically empty the queue of write requests)
  //!
  void clear_write_requests(void);

private:
  //!
  //! process read operations when available
  //! basically called whenever on_read_available is called and try to read from the socket
  //! handle possible case of failure and fill in the result
  //!
  //! \param result result of the read operation
  //! \return the callback to be executed (set in the read request) on read completion (may be null)
  //!
  async_read_callback_t process_read(read_result& result);

  //!
  //! process write operations when available
  //! basically called whenever on_write_available is called and try to write to the socket
  //! handle possible case of failure and fill in the result
  //!
  //! \param result result of the write operation
  //! \return the callback to be executed (set in the write request) on read completion (may be null)
  //!
  async_write_callback_t process_write(write_result& result);

private:
  //!
  //! store io_service
  //! prevent deletion of io_service before the tcp_client itself
  //!
  std::shared_ptr<io_service> m_io_service;

  //!
  //! client socket
  //!
  tacopie::tcp_socket m_socket;

  //!
  //! whether the client is currently connected or not
  //!
  std::atomic<bool> m_is_connected = ATOMIC_VAR_INIT(false);

  //!
  //! read requests
  //!
  std::queue<read_request> m_read_requests;
  //!
  //! write requests
  //!
  std::queue<write_request> m_write_requests;

  //!
  //! read requests thread safety
  //!
  std::mutex m_read_requests_mtx;
  //!
  //! write requests thread safety
  //!
  std::mutex m_write_requests_mtx;

  //!
  //! disconnection handler
  //!
  disconnection_handler_t m_disconnection_handler;
};

} // namespace tacopie
