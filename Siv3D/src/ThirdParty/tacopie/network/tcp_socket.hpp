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

#include <cstdint>
#include <string>
#include <vector>

#include <tacopie/utils/typedefs.hpp>

namespace tacopie {

//!
//! tacopie::tcp_socket is the class providing low-level TCP socket features.
//! The tcp_socket provides a simple but convenient abstraction to unix and windows sockets.
//! It also provides a socket type checker to ensure that server-only operations are only processable on server sockets, and client-only operations are only processable on client sockets.
//!
class tcp_socket {
public:
  //!
  //! possible types of a TCP socket, either a client or a server
  //! type is used to prevent the used of client specific operations on a server socket (and vice-versa)
  //!
  //! UNKNOWN is used when socket type could not be determined for now
  //!
  enum class type {
    CLIENT,
    SERVER,
    UNKNOWN
  };

public:
  //! ctor
  tcp_socket(void);
  //! dtor
  ~tcp_socket(void) = default;

  //!
  //! custom ctor
  //! build socket from existing file descriptor
  //!
  //! \param fd fd of the raw socket that will be used to init the tcp_socket object
  //! \param host host associated to the socket
  //! \param port port associated to the socket
  //! \param t type of the socket (client or server)
  tcp_socket(fd_t fd, const std::string& host, std::uint32_t port, type t);

  //! move ctor
  tcp_socket(tcp_socket&&);

  //! copy ctor
  tcp_socket(const tcp_socket&) = delete;
  //! assignment operator
  tcp_socket& operator=(const tcp_socket&) = delete;

public:
  //!
  //! comparison operator
  //!
  //! \return true when the underlying sockets are the same (same file descriptor and socket type).
  //!
  bool operator==(const tcp_socket& rhs) const;

  //!
  //! comparison operator
  //!
  //! \return true when the underlying sockets are different (different file descriptor or socket type).
  //!
  bool operator!=(const tcp_socket& rhs) const;

public:
  //!
  //! Read data synchronously from the underlying socket.
  //! The socket must be of type client to process this operation. If the type of the socket is unknown, the socket type will be set to client.
  //!
  //! \param size_to_read Number of bytes to read (might read less than requested)
  //! \return Returns the read bytes
  //!
  std::vector<char> recv(std::size_t size_to_read);

  //!
  //! Send data synchronously to the underlying socket.
  //! The socket must be of type client to process this operation. If the type of the socket is unknown, the socket type will be set to client.
  //!
  //! \param data Buffer containing bytes to be written
  //! \param size_to_write Number of bytes to send
  //! \return Returns the number of bytes that were effectively sent.
  //!
  std::size_t send(const std::vector<char>& data, std::size_t size_to_write);

  //!
  //! Connect the socket to the remote server.
  //! The socket must be of type client to process this operation. If the type of the socket is unknown, the socket type will be set to client.
  //!
  //! \param host Hostname of the target server
  //! \param port Port of the target server
  //! \param timeout_msecs maximum time to connect (will block until connect succeed or timeout expire). 0 will block undefinitely. If timeout expires, connection fails
  //!
  void connect(const std::string& host, std::uint32_t port, std::uint32_t timeout_msecs = 0);

  //!
  //! Binds the socket to the given host and port.
  //! The socket must be of type server to process this operation. If the type of the socket is unknown, the socket type will be set to server.
  //!
  //! \param host Hostname to be bind to
  //! \param port Port to be bind to
  //!
  void bind(const std::string& host, std::uint32_t port);

  //!
  //! Make the socket listen for incoming connections.
  //! Socket must be of type server to process this operation. If the type of the socket is unknown, the socket type will be set to server.
  //!
  //! \param max_connection_queue Size of the queue for incoming connections to be processed by the server
  //!
  void listen(std::size_t max_connection_queue);

  //!
  //! Accept a new incoming connection.
  //! The socket must be of type server to process this operation. If the type of the socket is unknown, the socket type will be set to server.
  //!
  //! \return Return the tcp_socket associated to the newly accepted connection.
  //!
  tcp_socket accept(void);

  //!
  //! Close the underlying socket.
  //!
  void close(void);

public:
  //!
  //! \return the hostname associated with the underlying socket.
  //!
  const std::string& get_host(void) const;

  //!
  //! \return the port associated with the underlying socket.
  //!
  std::uint32_t get_port(void) const;

  //!
  //! \return the type associated with the underlying socket.
  //!
  type get_type(void) const;

  //!
  //! set type, should be used if some operations determining socket type
  //! have been done on the behalf of the tcp_socket instance
  //!
  //! \param t type of the socket
  //!
  void set_type(type t);

  //!
  //! direct access to the underlying fd
  //!
  //! \return underlying socket fd
  //!
  fd_t get_fd(void) const;

public:
  //!
  //! \return whether the host is IPV6
  //!
  bool is_ipv6(void) const;

private:
  //!
  //! create a new socket if no socket has been initialized yet
  //!
  void create_socket_if_necessary(void);

  //!
  //! check whether the current socket has an approriate type for that kind of operation
  //! if current type is UNKNOWN, update internal type with given type
  //!
  //! \param t expected type of our socket to process the operation
  //!
  void check_or_set_type(type t);

private:
  //!
  //! fd associated to the socket
  //!
  fd_t m_fd;

  //!
  //! socket hostname information
  //!
  std::string m_host;
  //!
  //! socket port information
  //!
  std::uint32_t m_port;

  //!
  //! type of the socket
  //!
  type m_type;
};

} // namespace tacopie
