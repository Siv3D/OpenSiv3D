//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Say.hpp>
# include <Siv3D/TextToSpeech.hpp>

namespace s3d
{
	namespace detail
	{
		SayBuffer::SayBuffer()
			: formatData{ std::make_unique<FormatData>() } {}

		SayBuffer::SayBuffer(SayBuffer&& other) noexcept
			: formatData{ std::move(other.formatData) } {}

		SayBuffer::~SayBuffer()
		{
			if (formatData)
			{
				TextToSpeech::Speak(formatData->string);
			}
		}

		void Say_impl::operator()(const char32_t* s) const
		{
			TextToSpeech::Speak(s);
		}

		void Say_impl::operator()(const StringView s) const
		{
			TextToSpeech::Speak(s);
		}

		void Say_impl::operator()(const String& s) const
		{
			TextToSpeech::Speak(s);
		}
	}
}
