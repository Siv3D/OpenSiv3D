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

#include <tacopie/utils/typedefs.hpp>

namespace tacopie {

//!
//! used to force poll to wake up
//! simply make poll watch for read events on one side of the pipe and write to the other side
//!
class self_pipe {
public:
  //! ctor
  self_pipe(void);
  //! dtor
  ~self_pipe(void);

  //! copy ctor
  self_pipe(const self_pipe&) = delete;
  //! assignment operator
  self_pipe& operator=(const self_pipe&) = delete;

public:
  //!
  //! \return the read fd of the pipe
  //!
  fd_t get_read_fd(void) const;

  //!
  //! \return the write fd of the pipe
  //!
  fd_t get_write_fd(void) const;

  //!
  //! notify the self pipe (basically write to the pipe)
  //!
  void notify(void);

  //!
  //! clear the pipe (basically read from the pipe)
  //!
  void clr_buffer(void);

private:
#ifdef _WIN32
  //!
  //! socket fd
  //!
  fd_t m_fd;

  //!
  //! socket information
  //!
  struct sockaddr m_addr;

  //!
  //! socket information (addr len)
  //!
  int m_addr_len;
#else
  //!
  //! pipe file descriptors
  //!
  fd_t m_fds[2];
#endif /* _WIN32 */
};

} // namespace tacopie
