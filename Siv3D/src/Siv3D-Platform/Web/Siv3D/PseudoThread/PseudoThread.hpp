//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2020-2021 Kamenoko-Nyokonyoko
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

# include <tuple>
# include <memory>
# include <functional>
# include <emscripten/html5.h>

namespace s3d
{
    class PseudoThread
    {
        struct ThreadStruct
        {
            long m_IntervalID;
            bool m_Aborted = false;
        };

        std::shared_ptr<ThreadStruct> m_NativeHandle;

        template <class _Fp, class ..._Args, size_t ..._Indices>
        static inline bool PseudoThreadExecute(std::tuple<std::shared_ptr<ThreadStruct>, _Fp, _Args...>& __t, std::index_sequence<_Indices...>)
        {
            return std::invoke(std::move(std::get<1>(__t)), std::move(std::get<_Indices + 2>(__t))...);
        }

        template <class _Fp>
        static void PseudoThreadProxy(void* __vp)
        {
            // _Fp = tuple< unique_ptr<__thread_struct>, Functor, Args...>
            std::unique_ptr<_Fp> __p(static_cast<_Fp*>(__vp));
            using _Index = typename std::make_index_sequence<std::tuple_size<_Fp>::value - 2>;

            auto nativeHandle = std::get<0>(*__p);

            if (nativeHandle->m_Aborted)
            {
                ::emscripten_clear_interval(nativeHandle->m_IntervalID);
                return;            
            }
            
            if (bool shouldContinue = PseudoThreadExecute(*__p.get(), _Index()); not shouldContinue) 
            {
                ::emscripten_clear_interval(nativeHandle->m_IntervalID);
                return;          
            }

            __p.release();
        }
    public:  
        PseudoThread() = default; 

        template <class _Fp, class ..._Args>
        PseudoThread(_Fp&& __f, _Args&&... __args) : 
            m_NativeHandle(std::make_shared<ThreadStruct>())
        {
            // libcxx の thread を参考に実装
            using _Gp = std::tuple<std::shared_ptr<ThreadStruct>, typename std::decay<_Fp>::type, typename std::decay<_Args>::type...>;
            std::unique_ptr<_Gp> __p(
                new _Gp(m_NativeHandle,
                        std::forward<_Fp>(__f),
                        std::forward<_Args>(__args)...));

            auto intervalID = ::emscripten_set_interval(&PseudoThreadProxy<_Gp>, 50, __p.get());
            
            if (intervalID > 0) 
            {
                std::get<0>(*__p)->m_IntervalID = intervalID;
                __p.release();
            }
        }

        PseudoThread(const PseudoThread&) = delete;
        PseudoThread& operator=(const PseudoThread&) = delete;

        PseudoThread(PseudoThread&& p)
        {
            m_NativeHandle = p.m_NativeHandle;
            p.m_NativeHandle = nullptr;
        }  

        PseudoThread& operator=(PseudoThread&& p)
        {
            if (m_NativeHandle)
            {
                m_NativeHandle->m_Aborted = true;
            }

            m_NativeHandle = p.m_NativeHandle;
            p.m_NativeHandle = nullptr;
        }  

        ~PseudoThread()
        {
            if (m_NativeHandle.get() != nullptr)
            {
                m_NativeHandle->m_Aborted = true;
            }
        }   

        bool joinable() const
        {
            return false;
        }

        void join()
        {
            // do nothing
        }

        void detach()
        {
            m_NativeHandle = nullptr;
        }  
    };
}