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

#include <tacopie/utils/logger.hpp>
#include <tacopie/utils/thread_pool.hpp>

namespace tacopie {

namespace utils {

//!
//! ctor & dtor
//!

thread_pool::thread_pool(std::size_t nb_threads)
: m_nb_threads(nb_threads) {
  __TACOPIE_LOG(debug, "create thread_pool");

  for (std::size_t i = 0; i < nb_threads; ++i) { m_workers.push_back(std::thread(std::bind(&thread_pool::run, this))); }
}

thread_pool::~thread_pool(void) {
  __TACOPIE_LOG(debug, "destroy thread_pool");
  stop();
}

//!
//! worker main loop
//!

void
thread_pool::run(void) {
  __TACOPIE_LOG(debug, "start run() worker");

  while (!should_stop()) {
    task_t task = fetch_task();

    if (task) {
      __TACOPIE_LOG(debug, "execute task");

      try {
        task();
      }
      catch (const std::exception&) {
        __TACOPIE_LOG(warn, "uncatched exception propagated up to the threadpool.")
      }

      __TACOPIE_LOG(debug, "execution complete");
    }
  }

  __TACOPIE_LOG(debug, "stop run() worker");
}

//!
//! stop the thread pool and wait for workers completion
//!

void
thread_pool::stop(void) {
  if (!is_running()) { return; }

  m_should_stop = true;
  m_tasks_condvar.notify_all();

  for (auto& worker : m_workers) { worker.join(); }

  m_workers.clear();

  __TACOPIE_LOG(debug, "thread_pool stopped");
}

//!
//! whether the thread_pool is running or not
//!
bool
thread_pool::is_running(void) const {
  return !m_should_stop;
}

//!
//! whether the current thread should stop or not
//!
bool
thread_pool::should_stop(void) const {
  return m_should_stop || m_workers.size() > m_nb_threads;
}

//!
//! retrieve a new task
//!

thread_pool::task_t
thread_pool::fetch_task(void) {
  std::unique_lock<std::mutex> lock(m_tasks_mtx);

  __TACOPIE_LOG(debug, "waiting to fetch task");

  m_tasks_condvar.wait(lock, [&] { return should_stop() || !m_tasks.empty(); });

  if (should_stop() || m_tasks.empty()) { return nullptr; }

  task_t task = std::move(m_tasks.front());
  m_tasks.pop();
  return task;
}

//!
//! add tasks to thread pool
//!

void
thread_pool::add_task(const task_t& task) {
  std::lock_guard<std::mutex> lock(m_tasks_mtx);

  __TACOPIE_LOG(debug, "add task to thread_pool");

  m_tasks.push(task);
  m_tasks_condvar.notify_all();
}

thread_pool&
thread_pool::operator<<(const task_t& task) {
  add_task(task);

  return *this;
}

//!
//! adjust number of threads
//!
void
thread_pool::set_nb_threads(std::size_t nb_threads) {
  m_nb_threads = nb_threads;

  //! if we increased the number of threads, spawn them
  if (m_workers.size() < m_nb_threads) {
    while (m_workers.size() < m_nb_threads) {
      m_workers.push_back(std::thread(std::bind(&thread_pool::run, this)));
    }
  }
  //! otherwise, wake up threads to make them stop if necessary (until we get the right amount of threads)
  else {
    m_tasks_condvar.notify_all();
  }
}

} // namespace utils

} // namespace tacopie
