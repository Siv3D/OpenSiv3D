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

#include <fcntl.h>
#include <unistd.h>

namespace tacopie {

//!
//! ctor & dtor
//!
self_pipe::self_pipe(void)
: m_fds{__TACOPIE_INVALID_FD, __TACOPIE_INVALID_FD} {
  if (pipe(m_fds) == -1) { __TACOPIE_THROW(error, "pipe() failure"); }
}

self_pipe::~self_pipe(void) {
  if (m_fds[0] != __TACOPIE_INVALID_FD) {
    close(m_fds[0]);
  }

  if (m_fds[1] != __TACOPIE_INVALID_FD) {
    close(m_fds[1]);
  }
}

//!
//! get rd/wr fds
//!
fd_t
self_pipe::get_read_fd(void) const {
  return m_fds[0];
}

fd_t
self_pipe::get_write_fd(void) const {
  return m_fds[1];
}

//!
//! notify
//!
void
self_pipe::notify(void) {
  (void) write(m_fds[1], "a", 1);
}

//!
//! clr buffer
//!
void
self_pipe::clr_buffer(void) {
  char buf[1024];
  (void) read(m_fds[0], buf, 1024);
}

} // namespace tacopie
