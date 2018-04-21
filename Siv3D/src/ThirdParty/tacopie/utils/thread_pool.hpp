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
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace tacopie {

namespace utils {

//!
//! basic thread pool used to push async tasks from the io_service
//!
class thread_pool {
public:
  //!
  //! ctor
  //! created the worker thread that start working immediately
  //!
  //! \param nb_threads number of threads to start the thread pool
  //!
  explicit thread_pool(std::size_t nb_threads);

  //! dtor
  ~thread_pool(void);

  //! copy ctor
  thread_pool(const thread_pool&) = delete;
  //! assignment operator
  thread_pool& operator=(const thread_pool&) = delete;

public:
  //!
  //! task typedef
  ///! simply a callable taking no parameter
  //!
  typedef std::function<void()> task_t;

  //!
  //! add tasks to thread pool
  //! task is enqueued and will be executed whenever all previously executed tasked have been executed (or are currently being executed)
  //!
  //! \param task task to be executed by the threadpool
  //!
  void add_task(const task_t& task);

  //!
  //! same as add_task
  //!
  //! \param task task to be executed by the threadpool
  //! \return current instance
  //!
  thread_pool& operator<<(const task_t& task);

  //!
  //! stop the thread pool and wait for workers completion
  //! if some tasks are pending, they won't be executed
  //!
  void stop(void);

public:
  //!
  //! \return whether the thread_pool is running or not
  //!
  bool is_running(void) const;

public:
  //!
  //! reset the number of threads working in the thread pool
  //! this can be safely called at runtime and can be useful if you need to adjust the number of workers
  //!
  //! this function returns immediately, but change might be applied in the background
  //! that is, increasing number of threads will spwan new threads directly from this function (but they may take a while to start)
  //! moreover, shrinking the number of threads can only be applied in the background to make sure to not stop some threads in the middle of their task
  //!
  //! changing number of workers do not affect tasks to be executed and tasks currently being executed
  //!
  //! \param nb_threads number of threads
  //!
  void set_nb_threads(std::size_t nb_threads);

private:
  //!
  //! worker main loop
  //!
  void run(void);

  //!
  //! retrieve a new task
  //! fetch the first element in the queue, or wait if no task are available
  //! may return null if the threadpool is stopped
  //!
  task_t fetch_task(void);

  //!
  //! \return whether the thread should stop or not
  //!
  bool should_stop(void) const;

private:
  //!
  //! threads
  //!
  std::vector<std::thread> m_workers;

  //!
  //! number of threads allowed
  //!
  std::size_t m_nb_threads;

  //!
  //! whether the thread_pool should stop or not
  //!
  std::atomic<bool> m_should_stop = ATOMIC_VAR_INIT(false);

  //!
  //! tasks
  //!
  std::queue<task_t> m_tasks;

  //!
  //! tasks thread safety
  //!
  std::mutex m_tasks_mtx;

  //!
  //! task condvar to sync on tasks changes
  //!
  std::condition_variable m_tasks_condvar;
};

} // namespace utils

} // namespace tacopie
