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

# include <Siv3D/Say.hpp>
# include <Siv3D/TextToSpeech.hpp>

namespace s3d
{
	namespace detail
	{
		SayBuffer::SayBuffer()
			: formatData(std::make_unique<FormatData>())
		{
		
		}

		SayBuffer::SayBuffer(SayBuffer&& other)
			: formatData(std::move(other.formatData))
		{
		
		}

		SayBuffer::~SayBuffer()
		{
			if (formatData)
			{
				TextToSpeech::Speak(formatData->string);
			}
		}

		void Say_impl::operator()(const String& text) const
		{
			TextToSpeech::Speak(text);
		}
	}
}
