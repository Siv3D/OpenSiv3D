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

#include <utility>
#include <type_traits>

namespace sr::detail
{
    // From P0550
    template<class T>
    using remove_cvref = std::remove_cv<std::remove_reference<T>>;

    template<class T>
    using remove_cvref_t = typename remove_cvref<T>::type;



    template<class F, class S>
    struct is_noexcept_dtor : public std::true_type
    {
    };

    template<class F, class S>
    inline constexpr bool is_noexcept_dtor_v = is_noexcept_dtor<F, S>::value;

    template<class T>
    constexpr decltype(auto) forward_if_nothrow_move_constructible(T&& arg)
    {
        if constexpr( std::is_nothrow_move_constructible_v<T> == true )
        {
            return std::forward<T>(arg);
        }
        return arg;
    }



    template<class EF, class Strategy>
    class scope_guard_base : private Strategy
    {
    public:

        template<class EFP,
            std::enable_if_t<std::is_constructible_v<EF, EFP>, int> = 0,
            std::enable_if_t<(!std::is_lvalue_reference_v<EFP>)
                                && std::is_nothrow_constructible_v<EF, EFP>, int> = 0
            >
        explicit scope_guard_base(EFP&& exitFunction) noexcept(std::is_nothrow_constructible_v<EF, EFP>
                                                                || std::is_nothrow_constructible_v<EF, EFP&>)
                                                    : exitfunction(std::forward<EFP>(exitFunction)),
                                                    execute_on_destruction(true)
        {
        }

        template<class EFP,
            std::enable_if_t<std::is_constructible_v<EF, EFP>, int> = 0,
            std::enable_if_t<std::is_lvalue_reference_v<EFP>, int> = 0
            >
        explicit scope_guard_base(EFP&& exitFunction) try : exitfunction(exitFunction),
                                                        execute_on_destruction(true)
        {
        }
        catch( ... )
        {
            exitFunction();
            throw;
        }

        template<class EFP = EF, std::enable_if_t<(std::is_nothrow_move_constructible_v<EF>
                                                    || std::is_copy_constructible_v<EF>), int> = 0
                >
        scope_guard_base(scope_guard_base&& other) noexcept(std::is_nothrow_move_constructible_v<EF>
                                                            || std::is_nothrow_copy_constructible_v<EF>)
                                        : Strategy(other),
                                        exitfunction(forward_if_nothrow_move_constructible(other.exitfunction)),
                                        execute_on_destruction(other.execute_on_destruction)
        {
            other.release();
        }

        scope_guard_base(const scope_guard_base&) = delete;


        ~scope_guard_base() noexcept(is_noexcept_dtor_v<EF, Strategy>)
        {
            if( (execute_on_destruction == true) && (this->should_execute() == true) )
            {
                exitfunction();
            }
        }


        void release() noexcept
        {
            execute_on_destruction = false;
        }


        scope_guard_base& operator=(const scope_guard_base&) = delete;
        scope_guard_base& operator=(scope_guard_base&&) = delete;


    private:

        EF exitfunction;
        bool execute_on_destruction;
    };

}
