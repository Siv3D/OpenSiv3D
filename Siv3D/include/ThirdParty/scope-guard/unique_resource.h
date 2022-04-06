// MIT License
//
// Copyright (c) 2017-2021 offa
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

#include "scope_exit.h"
#include "detail/wrapper.h"
#include <utility>
#include <type_traits>

namespace sr
{
    namespace detail
    {
        template<class T, class U,
                    class R = std::conditional_t<std::is_nothrow_constructible_v<T, U>, U&&, U>
                >
        constexpr R forward_if_nothrow_constructible(U&& arg)
        {
            return std::forward<U>(arg);
        }
    }


    template<class R, class D>
    class unique_resource
    {
    public:

        unique_resource()
            : resource(R{}),
            deleter(D{}),
            execute_on_reset(false)
        {
        }

        template<class RR, class DD,
                std::enable_if_t<(std::is_constructible_v<R ,RR> && std::is_constructible_v<D, DD>
                                && (std::is_nothrow_constructible_v<R, RR> || std::is_constructible_v<R, RR&>)
                                && (std::is_nothrow_constructible_v<D, DD> || std::is_constructible_v<D, DD&>)), int> = 0
                >
        unique_resource(RR&& r, DD&& d) noexcept((std::is_nothrow_constructible_v<R, RR> || std::is_nothrow_constructible_v<R, RR&>)
                                                    && (std::is_nothrow_constructible_v<D, DD> || std::is_nothrow_constructible_v<D, DD&>))
                                        : resource(detail::forward_if_nothrow_constructible<R, RR>(std::forward<RR>(r)), scope_exit{[&r, &d] { d(r); }}),
                                        deleter(detail::forward_if_nothrow_constructible<D, DD>(std::forward<DD>(d)), scope_exit{[this, &d] { d(get()); }}),
                                        execute_on_reset(true)
        {
        }

        unique_resource(unique_resource&& other) noexcept(std::is_nothrow_move_constructible_v<R>
                                                            && std::is_nothrow_move_constructible_v<D>)
                                                : resource(std::move_if_noexcept(other.resource.get())),
                                                deleter(std::move_if_noexcept(other.deleter.get()), scope_exit{[&other] {
                                                                                                            if( other.execute_on_reset == true )
                                                                                                            {
                                                                                                                other.get_deleter()(other.resource.get());
                                                                                                            }
                                                                                                            other.release(); }}),
                                                execute_on_reset(std::exchange(other.execute_on_reset, false))
        {
        }

        unique_resource(const unique_resource&) = delete;

        ~unique_resource()
        {
            reset();
        }


        void reset() noexcept
        {
            if( execute_on_reset == true )
            {
                execute_on_reset = false;
                get_deleter()(resource.get());
            }
        }

        template<class RR>
        void reset(RR&& r)
        {
            reset();

            using R1 = typename detail::Wrapper<R>::type;
            auto se = scope_exit{[this, &r] { get_deleter()(r); }};

            if constexpr( std::is_nothrow_assignable_v<R1&, RR> == true )
            {
                resource.reset(std::forward<RR>(r));
            }
            else
            {
                resource.reset(std::as_const(r));
            }

            execute_on_reset = true;
            se.release();
        }

        void release() noexcept
        {
            execute_on_reset = false;
        }

        const R& get() const noexcept
        {
            return resource.get();
        }

        template<class RR = R, std::enable_if_t<std::is_pointer_v<RR>, int> = 0>
        RR operator->() const noexcept
        {
            return resource.get();
        }

        template<class RR = R,
            std::enable_if_t<( std::is_pointer_v<RR>
                            && !std::is_void_v<std::remove_pointer_t<RR>>), int> = 0>
        std::add_lvalue_reference_t<std::remove_pointer_t<RR>> operator*() const noexcept
        {
            return *get();
        }

        const D& get_deleter() const noexcept
        {
            return deleter.get();
        }


        template<class RR = R, class DD = D,
            std::enable_if_t<(std::is_nothrow_move_assignable_v<RR>
                                || std::is_copy_assignable_v<RR>)
                            && (std::is_nothrow_move_assignable_v<DD>
                                || std::is_copy_assignable_v<DD>), int> = 0>
        unique_resource& operator=(unique_resource&& other) noexcept(std::is_nothrow_assignable_v<R&, R>
                                                                    && std::is_nothrow_assignable_v<D&, D>)
        {
            if( this != &other )
            {
                reset();

                if constexpr( std::is_nothrow_move_assignable_v<RR> == true )
                {
                    if constexpr( std::is_nothrow_move_assignable_v<DD> == true )
                    {
                        resource.reset(std::move(other.resource));
                        deleter.reset(std::move(other.deleter));
                    }
                    else
                    {
                        deleter.reset(other.deleter);
                        resource.reset(std::move(other.resource));
                    }
                }
                else
                {
                    if constexpr( std::is_nothrow_move_assignable_v<DD> == true )
                    {
                        resource.reset(other.resource);
                        deleter.reset(std::move(other.deleter));
                    }
                    else
                    {
                        resource.reset(other.resource);
                        deleter.reset(other.deleter);
                    }
                }

                execute_on_reset = std::exchange(other.execute_on_reset, false);
            }
            return *this;
        }

        unique_resource& operator=(const unique_resource&) = delete;


    private:

        detail::Wrapper<R> resource;
        detail::Wrapper<D> deleter;
        bool execute_on_reset;
    };


    template<class R, class D>
    unique_resource(R, D) -> unique_resource<R, D>;


    template<class R, class D, class S = std::decay_t<R>>
    unique_resource<std::decay_t<R>, std::decay_t<D>> make_unique_resource_checked(R&& r, const S& invalid, D&& d)
                                                            noexcept(std::is_nothrow_constructible_v<std::decay_t<R>, R>
                                                                    && std::is_nothrow_constructible_v<std::decay_t<D>, D>)
    {
        unique_resource<std::decay_t<R>, std::decay_t<D>> ur{std::forward<R>(r), std::forward<D>(d)};

        if( bool(r == invalid) )
        {
            ur.release();
        }

        return ur;
    }

}
