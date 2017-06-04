//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "Fwd.hpp"
# include "Format.hpp"

namespace s3d
{
	namespace detail
	{
		struct PrintBuffer
		{
			std::unique_ptr<FormatData> formatData;

			PrintBuffer()
				: formatData(std::make_unique<FormatData>()) {}

			PrintBuffer(PrintBuffer&& other)
				: formatData(std::move(other.formatData)) {}

			~PrintBuffer();

			template <class Type>
			PrintBuffer& operator <<(const Type& value)
			{
				Formatter(*formatData, value);

				return *this;
			}
		};

		struct Print_impl
		{
			void writeln(const String& text) const;

			const Print_impl& operator()(const String& text) const
			{
				writeln(text);

				return *this;
			}

			template <class... Args>
			const Print_impl& operator()(const Args&... args) const
			{
				writeln(Format(args...));

				return *this;
			}

			template <class Type>
			PrintBuffer operator <<(const Type& value) const
			{
				PrintBuffer buf;

				Formatter(*buf.formatData, value);

				return buf;
			}
		};
	}

	constexpr auto Print = detail::Print_impl();

	namespace detail
	{
		inline PrintBuffer::~PrintBuffer()
		{
			if (formatData)
			{
				Print.writeln(formatData->string);
			}
		}
	}

	void ClearPrint();
}
