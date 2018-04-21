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
#include <tacopie/utils/typedefs.hpp>

#include <cstring>

#include <Winsock2.h>
#include <Ws2tcpip.h>

namespace tacopie {

void
tcp_socket::connect(const std::string& host, std::uint32_t port, std::uint32_t timeout_msecs) {
  //! Reset host and port
  m_host = host;
  m_port = port;

  create_socket_if_necessary();
  check_or_set_type(type::CLIENT);

  struct sockaddr_storage ss;
  socklen_t addr_len;

  //! 0-init addr info struct
  std::memset(&ss, 0, sizeof(ss));

  if (is_ipv6()) {
    //! init sockaddr_in6 struct
    struct sockaddr_in6* addr = reinterpret_cast<struct sockaddr_in6*>(&ss);
    //! convert addr
    if (::inet_pton(AF_INET6, host.data(), &addr->sin6_addr) < 0) {
      __TACOPIE_THROW(error, "inet_pton() failure");
    }
    //! remaining fields
    ss.ss_family    = AF_INET6;
    addr->sin6_port = htons(port);
    addr_len        = sizeof(*addr);
  }
  else {
    struct addrinfo* result = nullptr;
    struct addrinfo hints;

    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family   = AF_INET;

    //! resolve DNS
    if (getaddrinfo(host.c_str(), nullptr, &hints, &result) != 0) { __TACOPIE_THROW(error, "getaddrinfo() failure"); }

    //! init sockaddr_in struct
    struct sockaddr_in* addr = reinterpret_cast<struct sockaddr_in*>(&ss);
    //! host
    addr->sin_addr = ((struct sockaddr_in*) (result->ai_addr))->sin_addr;
    //! Remaining fields
    addr->sin_port = htons(port);
    ss.ss_family   = AF_INET;
    addr_len       = sizeof(*addr);

    freeaddrinfo(result);
  }

  if (timeout_msecs > 0) {
    //! for timeout connection handling:
    //!  1. set socket to non blocking
    //!  2. connect
    //!  3. poll select
    //!  4. check connection status
    u_long mode = 1;
    if (ioctlsocket(m_fd, FIONBIO, &mode) != 0) {
      close();
      __TACOPIE_THROW(error, "connect() set non-blocking failure");
    }
  }
  else {
    //! For no timeout case, still make sure that the socket is in blocking mode
    //! As reported in #32, this might not be the case on some OS
    u_long mode = 0;
    if (ioctlsocket(m_fd, FIONBIO, &mode) != 0) {
      close();
      __TACOPIE_THROW(error, "connect() set blocking failure");
    }
  }

  int ret = ::connect(m_fd, reinterpret_cast<const struct sockaddr*>(&ss), addr_len);
  if (ret == -1 && WSAGetLastError() != WSAEWOULDBLOCK) {
    close();
    __TACOPIE_THROW(error, "connect() failure");
  }

  if (timeout_msecs > 0) {
    timeval tv;
    tv.tv_sec  = (timeout_msecs / 1000);
    tv.tv_usec = ((timeout_msecs - (tv.tv_sec * 1000)) * 1000);

    FD_SET set;
    FD_ZERO(&set);
    FD_SET(m_fd, &set);

    //! 1 means we are connected.
    //! 0 means a timeout.
    if (select(static_cast<int>(m_fd) + 1, NULL, &set, NULL, &tv) == 1) {
      //! Make sure there are no async connection errors
      int err = 0;
      int len = sizeof(len);
      if (getsockopt(m_fd, SOL_SOCKET, SO_ERROR, reinterpret_cast<char*>(&err), &len) == -1 || err != 0) {
        close();
        __TACOPIE_THROW(error, "connect() failure");
      }

      //! Set back to blocking mode as the user of this class is expecting
      u_long mode = 0;
      if (ioctlsocket(m_fd, FIONBIO, &mode) != 0) {
        close();
        __TACOPIE_THROW(error, "connect() set blocking failure");
      }
    }
    else {
      close();
      __TACOPIE_THROW(error, "connect() timed out");
    }
  }
}

//!
//! server socket operations
//!

void
tcp_socket::bind(const std::string& host, std::uint32_t port) {
  //! Reset host and port
  m_host = host;
  m_port = port;

  create_socket_if_necessary();
  check_or_set_type(type::SERVER);

  struct sockaddr_storage ss;
  socklen_t addr_len;

  //! 0-init addr info struct
  std::memset(&ss, 0, sizeof(ss));

  if (is_ipv6()) {
    //! init sockaddr_in6 struct
    struct sockaddr_in6* addr = reinterpret_cast<struct sockaddr_in6*>(&ss);
    //! convert addr
    if (::inet_pton(AF_INET6, host.data(), &addr->sin6_addr) < 0) {
      __TACOPIE_THROW(error, "inet_pton() failure");
    }
    //! remaining fields
    addr->sin6_port = htons(port);
    ss.ss_family    = AF_INET6;
    addr_len        = sizeof(*addr);
  }
  else {
    struct addrinfo* result = nullptr;

    //! dns resolution
    if (getaddrinfo(host.c_str(), nullptr, nullptr, &result) != 0) {
      __TACOPIE_THROW(error, "getaddrinfo() failure");
    }

    //! init sockaddr_in struct
    struct sockaddr_in* addr = reinterpret_cast<struct sockaddr_in*>(&ss);
    //! addr
    addr->sin_addr = ((struct sockaddr_in*) (result->ai_addr))->sin_addr;
    //! remaining fields
    addr->sin_port = htons(port);
    ss.ss_family   = AF_INET;
    addr_len       = sizeof(*addr);

    freeaddrinfo(result);
  }

  if (::bind(m_fd, reinterpret_cast<const struct sockaddr*>(&ss), addr_len) == SOCKET_ERROR) { __TACOPIE_THROW(error, "bind() failure"); }
}

//!
//! general socket operations
//!

void
tcp_socket::close(void) {
  if (m_fd != __TACOPIE_INVALID_FD) {
    __TACOPIE_LOG(debug, "close socket");
    closesocket(m_fd);
  }

  m_fd   = __TACOPIE_INVALID_FD;
  m_type = type::UNKNOWN;
}
//!
//! create a new socket if no socket has been initialized yet
//!

void
tcp_socket::create_socket_if_necessary(void) {
  if (m_fd != __TACOPIE_INVALID_FD) { return; }

  //! new TCP socket
  //! handle ipv6 addr
  short family;
  if (is_ipv6()) {
    family = AF_INET6;
  }
  else {
    family = AF_INET;
  }
  m_fd   = socket(family, SOCK_STREAM, 0);
  m_type = type::UNKNOWN;

  if (m_fd == __TACOPIE_INVALID_FD) { __TACOPIE_THROW(error, "tcp_socket::create_socket_if_necessary: socket() failure"); }
}

} // namespace tacopie
