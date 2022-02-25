//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "String.hpp"

namespace s3d
{
	namespace detail
	{
		//////////////////////////////////////////////////////////////////////////////
		//
		//	Copyright (c) 2012 - present, Victor Zverovich
		//
		//	Permission is hereby granted, free of charge, to any person obtaining
		//	a copy of this software and associated documentation files (the
		//	"Software"), to deal in the Software without restriction, including
		//	without limitation the rights to use, copy, modify, merge, publish,
		//	distribute, sublicense, and/or sell copies of the Software, and to
		//	permit persons to whom the Software is furnished to do so, subject to
		//	the following conditions:
		//
		//	The above copyright notice and this permission notice shall be
		//	included in all copies or substantial portions of the Software.
		//
		//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
		//	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
		//	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
		//	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
		//	LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
		//	OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
		//	WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
		//
		//	--- Optional exception to the license ---
		//
		//	As an exception, if, as a result of your compiling your source code, portions
		//	of this Software are embedded into a machine-executable object form of such
		//	source code, you may redistribute such embedded portions in such object form
		//	without including the above copyright and permission notices.
		class IntFormatter
		{
		private:

			enum { BUFFER_SIZE = std::numeric_limits<uint64>::digits10 + 3 };

			mutable char32 buffer_[BUFFER_SIZE];

			char32* str_;

			char32* format_decimal(uint64 value) noexcept;

			void format_signed(int64 value) noexcept;

		public:

			SIV3D_NODISCARD_CXX20
			explicit IntFormatter(int32 value) noexcept;

			SIV3D_NODISCARD_CXX20
			explicit IntFormatter(int64 value) noexcept;

			SIV3D_NODISCARD_CXX20
			explicit IntFormatter(uint32 value) noexcept;

			SIV3D_NODISCARD_CXX20
			explicit IntFormatter(uint64 value) noexcept;

			std::size_t size() const noexcept
			{
				return buffer_ - str_ + BUFFER_SIZE - 1;
			}

			const char32* data() const  noexcept
			{
				return str_;
			}

			const char32* c_str() const noexcept
			{
				buffer_[BUFFER_SIZE - 1] = '\0';
				return str_;
			}

			String str() const
			{
				return String(str_, size());
			}
		};
		//
		//////////////////////////////////////////////////////////////////////////////
	}
}
