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

#include <tacopie/network/tcp_server.hpp>
#include <tacopie/utils/error.hpp>
#include <tacopie/utils/logger.hpp>

#ifdef _WIN32
#include <Winsock2.h>
#include <Ws2tcpip.h>
#else
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#endif /* _WIN32 */

#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif /* SOCKET_ERROR */

#if _WIN32
#define __TACOPIE_LENGTH(size) static_cast<int>(size) // for Windows, convert buffer size to `int`
#pragma warning(disable : 4996)                       // for Windows, `inet_ntoa` is deprecated as it does not support IPv6
#else
#define __TACOPIE_LENGTH(size) size // for Unix, keep buffer size as `size_t`
#endif                              /* _WIN32 */

namespace tacopie {

//!
//! ctor & dtor
//!

tcp_socket::tcp_socket(void)
: m_fd(__TACOPIE_INVALID_FD)
, m_host("")
, m_port(0)
, m_type(type::UNKNOWN) { __TACOPIE_LOG(debug, "create tcp_socket"); }

//!
//! custom ctor
//! build socket from existing file descriptor
//!

tcp_socket::tcp_socket(fd_t fd, const std::string& host, std::uint32_t port, type t)
: m_fd(fd)
, m_host(host)
, m_port(port)
, m_type(t) { __TACOPIE_LOG(debug, "create tcp_socket"); }

//!
//! Move constructor
//!

tcp_socket::tcp_socket(tcp_socket&& socket)
: m_fd(std::move(socket.m_fd))
, m_host(socket.m_host)
, m_port(socket.m_port)
, m_type(socket.m_type) {
  socket.m_fd   = __TACOPIE_INVALID_FD;
  socket.m_type = type::UNKNOWN;

  __TACOPIE_LOG(debug, "moved tcp_socket");
}

//!
//! client socket operations
//!

std::vector<char>
tcp_socket::recv(std::size_t size_to_read) {
  create_socket_if_necessary();
  check_or_set_type(type::CLIENT);

  std::vector<char> data(size_to_read, 0);

  ssize_t rd_size = ::recv(m_fd, const_cast<char*>(data.data()), __TACOPIE_LENGTH(size_to_read), 0);

  if (rd_size == SOCKET_ERROR) { __TACOPIE_THROW(error, "recv() failure"); }

  if (rd_size == 0) { __TACOPIE_THROW(warn, "nothing to read, socket has been closed by remote host"); }

  data.resize(rd_size);

  return data;
}

std::size_t
tcp_socket::send(const std::vector<char>& data, std::size_t size_to_write) {
  create_socket_if_necessary();
  check_or_set_type(type::CLIENT);

  ssize_t wr_size = ::send(m_fd, data.data(), __TACOPIE_LENGTH(size_to_write), 0);

  if (wr_size == SOCKET_ERROR) { __TACOPIE_THROW(error, "send() failure"); }

  return wr_size;
}

//!
//! server socket operations
//!

void
tcp_socket::listen(std::size_t max_connection_queue) {
  create_socket_if_necessary();
  check_or_set_type(type::SERVER);

  if (::listen(m_fd, __TACOPIE_LENGTH(max_connection_queue)) == SOCKET_ERROR) { __TACOPIE_THROW(debug, "listen() failure"); }
}

tcp_socket
tcp_socket::accept(void) {
  create_socket_if_necessary();
  check_or_set_type(type::SERVER);

  struct sockaddr_storage ss;
  socklen_t addrlen = sizeof(ss);

  fd_t client_fd = ::accept(m_fd, reinterpret_cast<struct sockaddr*>(&ss), &addrlen);

  if (client_fd == __TACOPIE_INVALID_FD) { __TACOPIE_THROW(error, "accept() failure"); }

  //! now determine host and port based on socket type
  std::string saddr;
  std::uint32_t port;

  //! ipv6
  if (ss.ss_family == AF_INET6) {
    struct sockaddr_in6* addr6 = reinterpret_cast<struct sockaddr_in6*>(&ss);
    char buf[INET6_ADDRSTRLEN] = {};
    const char* addr           = ::inet_ntop(ss.ss_family, &addr6->sin6_addr, buf, INET6_ADDRSTRLEN);

    if (addr) {
      saddr = std::string("[") + addr + "]";
    }

    port = ntohs(addr6->sin6_port);
  }
  //! ipv4
  else {
    struct sockaddr_in* addr4 = reinterpret_cast<struct sockaddr_in*>(&ss);
    char buf[INET_ADDRSTRLEN] = {};
    const char* addr          = ::inet_ntop(ss.ss_family, &addr4->sin_addr, buf, INET_ADDRSTRLEN);

    if (addr) {
      saddr = addr;
    }

    port = ntohs(addr4->sin_port);
  }
  return {client_fd, saddr, port, type::CLIENT};
}

//!
//! check whether the current socket has an appropriate type for that kind of operation
//! if current type is UNKNOWN, update internal type with given type
//!

void
tcp_socket::check_or_set_type(type t) {
  if (m_type != type::UNKNOWN && m_type != t) { __TACOPIE_THROW(error, "trying to perform invalid operation on socket"); }

  m_type = t;
}

//!
//! get socket name information
//!

const std::string&
tcp_socket::get_host(void) const {
  return m_host;
}

std::uint32_t
tcp_socket::get_port(void) const {
  return m_port;
}

//!
//! get socket type
//!

tcp_socket::type
tcp_socket::get_type(void) const {
  return m_type;
}

//!
//! set type, should be used if some operations determining socket type
//! have been done on the behalf of the tcp_socket instance
//!

void
tcp_socket::set_type(type t) {
  m_type = t;
}

//!
//! direct access to the underlying fd
//!

fd_t
tcp_socket::get_fd(void) const {
  return m_fd;
}

//!
//! ipv6 checking
//!

bool
tcp_socket::is_ipv6(void) const {
  return m_host.find(':') != std::string::npos;
}

//!
//! comparison operator
//!
bool
tcp_socket::operator==(const tcp_socket& rhs) const {
  return m_fd == rhs.m_fd && m_type == rhs.m_type;
}

bool
tcp_socket::operator!=(const tcp_socket& rhs) const {
  return !operator==(rhs);
}

} // namespace tacopie
