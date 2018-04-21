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

#include <tacopie/network/self_pipe.hpp>
#include <tacopie/utils/error.hpp>

#include <Winsock2.h>

#include <tacopie/utils/typedefs.hpp>
#include <fcntl.h>
#include <iostream>
namespace tacopie {

//!
//! ctor & dtor
//!
self_pipe::self_pipe(void)
: m_fd(__TACOPIE_INVALID_FD) {
  //! Create a server
  m_fd = ::socket(AF_INET, SOCK_DGRAM, 0);
  if (m_fd == __TACOPIE_INVALID_FD) { __TACOPIE_THROW(error, "fail socket()"); }

  u_long flags = 1;
  ioctlsocket(m_fd, FIONBIO, &flags);

  //! Bind server to localhost
  struct sockaddr_in inaddr;
  memset(&inaddr, 0, sizeof(inaddr));
  inaddr.sin_family      = AF_INET;
  inaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  inaddr.sin_port        = 0;
  if (bind(m_fd, (struct sockaddr*) &inaddr, sizeof(inaddr)) == SOCKET_ERROR) { __TACOPIE_THROW(error, "fail bind()"); }

  //! Retrieve server information
  m_addr_len = sizeof(m_addr);
  memset(&m_addr, 0, sizeof(m_addr));
  if (getsockname(m_fd, &m_addr, &m_addr_len) == SOCKET_ERROR) { __TACOPIE_THROW(error, "fail getsockname()"); }

  //! connect read fd to the server
  if (connect(m_fd, &m_addr, m_addr_len) == SOCKET_ERROR) { __TACOPIE_THROW(error, "fail connect()"); }
}

self_pipe::~self_pipe(void) {
  if (m_fd != __TACOPIE_INVALID_FD) {
    closesocket(m_fd);
  }
}

//!
//! get rd/wr fds
//!
fd_t
self_pipe::get_read_fd(void) const {
  return m_fd;
}

fd_t
self_pipe::get_write_fd(void) const {
  return m_fd;
}

//!
//! notify
//!
void
self_pipe::notify(void) {
  (void) sendto(m_fd, "a", 1, 0, &m_addr, m_addr_len);
}

//!
//! clr buffer
//!
void
self_pipe::clr_buffer(void) {
  char buf[1024];
  (void) recvfrom(m_fd, buf, 1024, 0, &m_addr, &m_addr_len);
}

} // namespace tacopie
