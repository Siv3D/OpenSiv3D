// MIT License
//
// Copyright (c) 2017-2019 offa
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

#include "detail/scope_guard_base.h"
#include <exception>

namespace sr
{
    namespace detail
    {

        struct scope_success_strategy
        {
            bool should_execute() const noexcept
            {
                return std::uncaught_exceptions() <= uncaught_on_creation;
            }


            int uncaught_on_creation = std::uncaught_exceptions();
        };


        template<class F>
        struct is_noexcept_dtor<F, scope_success_strategy>
            : public std::conditional_t<noexcept(std::declval<F>()()), std::true_type, std::false_type>
        {
        };

    }


    template<class EF>
    class scope_success : public detail::scope_guard_base<EF, detail::scope_success_strategy>
    {
        using ScopeGuardBase = std::enable_if_t<!std::is_same_v<detail::remove_cvref_t<EF>, scope_success<EF>>,
                                                detail::scope_guard_base<EF, detail::scope_success_strategy>
                                                >;

    public:

        using ScopeGuardBase::ScopeGuardBase;

    };


    template<class EF>
    scope_success(EF) -> scope_success<EF>;

}

