//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2020-2021 Kamenoko-Nyokonyoko
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

# include <tuple>
# include <memory>
# include <chrono>
# include <functional>
# include <emscripten/html5.h>

namespace s3d
{
    namespace detail
    {
        void clearInterval(long intervalID);
    }

    class PseudoThread
    {
    public:
        /** 
         * @brief スレッドを起動する関数 (pthread_create) の型
         */
        using ThreadLaunchFunction = long (*)(bool (*functionPointer)(void*), void* userData);

        /** 
         * @brief スレッドを終了する関数 (pthread_create) の型
         */
        using ThreadTerminateFunction = void (*)(long threadHandle);

        PseudoThread() = default; 

        template <class _Fp, class ..._Args>
        PseudoThread(std::chrono::milliseconds interval, _Fp&& __f, _Args&&... __args) : 
            m_ThreadContext(std::make_shared<ThreadStruct>())
        {
            // libcxx の thread を参考に実装
            using _Gp = std::tuple<std::shared_ptr<ThreadStruct>, typename std::decay<_Fp>::type, typename std::decay<_Args>::type...>;
            std::unique_ptr<_Gp> __p(
                new _Gp(m_ThreadContext,
                        std::forward<_Fp>(__f),
                        std::forward<_Args>(__args)...));

            auto intervalID = ::emscripten_set_interval(&PseudoThreadProxyVoid<_Gp>, interval.count(), __p.get());
            
            if (intervalID > 0) 
            {
                std::get<0>(*__p)->nativeHandle = intervalID;
                std::get<0>(*__p)->terminateThread = &detail::clearInterval;
                __p.release();
            }
        }

        template <class _Fp, class ..._Args>
        PseudoThread(ThreadLaunchFunction createThread, ThreadTerminateFunction terminateThread, _Fp&& __f, _Args&&... __args) : 
            m_ThreadContext(std::make_shared<ThreadStruct>())
        {
            // libcxx の thread を参考に実装
            using _Gp = std::tuple<std::shared_ptr<ThreadStruct>, typename std::decay<_Fp>::type, typename std::decay<_Args>::type...>;
            std::unique_ptr<_Gp> __p(
                new _Gp(m_ThreadContext,
                        std::forward<_Fp>(__f),
                        std::forward<_Args>(__args)...));

            auto intervalID = createThread(&PseudoThreadProxy<_Gp>, __p.get());
            
            if (intervalID > 0) 
            {
                std::get<0>(*__p)->nativeHandle = intervalID;
                std::get<0>(*__p)->terminateThread = terminateThread;
                __p.release();
            }
        }

        PseudoThread(const PseudoThread&) = delete;
        PseudoThread& operator=(const PseudoThread&) = delete;

        PseudoThread(PseudoThread&& p)
        {
            m_ThreadContext = p.m_ThreadContext;
            p.m_ThreadContext = nullptr;
        }  

        PseudoThread& operator=(PseudoThread&& p)
        {
            if (m_ThreadContext)
            {
                m_ThreadContext->aborted = true;
            }

            m_ThreadContext = p.m_ThreadContext;
            p.m_ThreadContext = nullptr;

            return *this;
        }  

        ~PseudoThread()
        {
            kill();
        }   

        bool joinable() const
        {
            return m_ThreadContext && m_ThreadContext->nativeHandle != 0;
        }

        void join()
        {
            // do nothing
        }

        void detach()
        {
            m_ThreadContext = nullptr;
        }  

        void kill()
        {
            if (m_ThreadContext.get() != nullptr)
            {
                m_ThreadContext->aborted = true;
            }
        }

    private:

        struct ThreadStruct
        {
            long nativeHandle;
            bool aborted = false;

            ThreadTerminateFunction terminateThread;
        };

        std::shared_ptr<ThreadStruct> m_ThreadContext;

        template <class _Fp, class ..._Args, size_t ..._Indices>
        static inline bool PseudoThreadExecute(std::tuple<std::shared_ptr<ThreadStruct>, _Fp, _Args...>& __t, std::index_sequence<_Indices...>)
        {
            return std::invoke(std::ref(std::get<1>(__t)), std::ref(std::get<_Indices + 2>(__t))...);
        }

        template <class _Fp>
        static bool PseudoThreadProxy(void* __vp)
        {
            // _Fp = tuple< unique_ptr<__thread_struct>, Functor, Args...>
            std::unique_ptr<_Fp> __p(static_cast<_Fp*>(__vp));
            using _Index = typename std::make_index_sequence<std::tuple_size<_Fp>::value - 2>;

            auto threadContext = std::get<0>(*__p);

            if (threadContext->aborted)
            {
                threadContext->terminateThread(threadContext->nativeHandle);
                return false;            
            }
            
            if (bool shouldContinue = PseudoThreadExecute(*__p.get(), _Index()); not shouldContinue) 
            {
                threadContext->terminateThread(threadContext->nativeHandle);
                threadContext->nativeHandle = 0;
                return false;          
            }

            __p.release();
            return true;
        }

        template <class _Fp>
        static void PseudoThreadProxyVoid(void* __vp)
        {
            // _Fp = tuple< unique_ptr<__thread_struct>, Functor, Args...>
            std::unique_ptr<_Fp> __p(static_cast<_Fp*>(__vp));
            using _Index = typename std::make_index_sequence<std::tuple_size<_Fp>::value - 2>;

            auto threadContext = std::get<0>(*__p);

            if (threadContext->aborted)
            {
                threadContext->terminateThread(threadContext->nativeHandle);
                return;            
            }
            
            if (bool shouldContinue = PseudoThreadExecute(*__p.get(), _Index()); not shouldContinue) 
            {
                threadContext->terminateThread(threadContext->nativeHandle);
                threadContext->nativeHandle = 0;
                return;          
            }

            __p.release();
        }
    };
}