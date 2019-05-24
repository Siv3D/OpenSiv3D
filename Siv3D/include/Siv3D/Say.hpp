//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "Fwd.hpp"
# include "Format.hpp"
# include "TextToSpeech.hpp"

namespace s3d
{
	namespace detail
	{
		struct SayBuffer
		{
			std::unique_ptr<FormatData> formatData;

			SayBuffer();

			SayBuffer(SayBuffer&& other);

			~SayBuffer();

			template <class Type>
			SayBuffer& operator <<(const Type& value)
			{
				Formatter(*formatData, value);

				return *this;
			}
		};

		struct Say_impl
		{
			void operator()(const String& text) const;

			template <class... Args>
			void operator()(const Args&... args) const
			{
				TextToSpeech::Speak(Format(args...));
			}

			template <class Type, class = decltype(Formatter(std::declval<FormatData&>(), std::declval<Type>()))>
			SayBuffer operator <<(const Type& value) const
			{
				SayBuffer buf;

				Formatter(*buf.formatData, value);

				return buf;
			}
		};
	}

	inline constexpr auto Say = detail::Say_impl();
}
