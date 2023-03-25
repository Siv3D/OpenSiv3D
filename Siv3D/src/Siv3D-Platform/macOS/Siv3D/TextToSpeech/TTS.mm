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

# include <Siv3D/LanguageCode.hpp>
# include "TTS.hpp"

namespace s3d
{
	namespace detail
	{
		inline constexpr float ConvertSpeed(const double speed)
		{
			return static_cast<float>(200 + (std::clamp(speed, 0.0, 2.0) - 1.0) * 100);
		}
		
		NSString* ConvertLanguageCode(const LanguageCode languageCode)
		{
			// [Siv3D ToDo] more languages!
			switch (languageCode)
			{
				case LanguageCode::ArabicSA:
					return @"com.apple.speech.synthesis.voice.tarik";
				case LanguageCode::ChineseCN:
					return @"com.apple.speech.synthesis.voice.ting-ting";
				case LanguageCode::ChineseHK:
					return @"com.apple.speech.synthesis.voice.sin-ji";
				case LanguageCode::ChineseTW:
					return @"com.apple.speech.synthesis.voice.mei-Jia";
				case LanguageCode::EnglishAU:
					return @"com.apple.speech.synthesis.voice.karen";
				case LanguageCode::EnglishGB:
					return @"com.apple.speech.synthesis.voice.daniel";
				case LanguageCode::EnglishUS:
					return @"com.apple.speech.synthesis.voice.Alex";
				case LanguageCode::FrenchFR:
					return @"com.apple.speech.synthesis.voice.thomas";
				case LanguageCode::GermanDE:
					return @"com.apple.speech.synthesis.voice.anna";
				case LanguageCode::HindiIN:
					return @"com.apple.speech.synthesis.voice.lekha";
				case LanguageCode::ItalianIT:
					return @"com.apple.speech.synthesis.voice.alice";
				case LanguageCode::Japanese:
					return @"com.apple.speech.synthesis.voice.kyoko";
				case LanguageCode::Korean:
					return @"com.apple.speech.synthesis.voice.yuna";
				case LanguageCode::PortugueseBR:
					return @"com.apple.speech.synthesis.voice.luciana";
				case LanguageCode::RussianRU:
					return @"com.apple.speech.synthesis.voice.milena";
				case LanguageCode::SpanishES:
					return @"com.apple.speech.synthesis.voice.monica";
				default:
					return nil;
			}
		}
	}
	
	TTS::~TTS()
	{
		reset();
	}
	
	bool TTS::hasLanguage(const LanguageCode languageCode)
	{
		@autoreleasepool
		{
			NSSpeechSynthesizer* tmp = [[NSSpeechSynthesizer alloc] initWithVoice:nil];
			const bool result = [tmp setVoice: detail::ConvertLanguageCode(languageCode)];
			return result;
		}
	}
	
	void TTS::setDefaultLanguage(const LanguageCode languageCode)
	{
		m_defaultLanguageCode = languageCode;
	}
	
	LanguageCode TTS::getDefaultLanguage() const
	{
		return m_defaultLanguageCode;
	}
	
	bool TTS::speak(const std::string& text, LanguageCode languageCode)
	{
		reset();
		
		if (languageCode == LanguageCode::Unspecified)
		{
			languageCode = m_defaultLanguageCode;
		}
		
		m_speechSynth = [[NSSpeechSynthesizer alloc] initWithVoice:nil];
		
		[m_speechSynth setVoice: detail::ConvertLanguageCode(languageCode)];
		[m_speechSynth setVolume:m_volume];
		[m_speechSynth setRate:detail::ConvertSpeed(m_speed)];
		
		NSString* text_ns = [NSString stringWithUTF8String:text.c_str()];
		[m_speechSynth startSpeakingString:text_ns];
		
		return true;
	}
	
	bool TTS::isSpeaking() const
	{
		return [m_speechSynth isSpeaking];
	}
	
	void TTS::reset()
	{
		if (!m_speechSynth)
		{
			return;
		}
		
		[m_speechSynth stopSpeaking];
		m_speechSynth = nil;
	}
	
	void TTS::pause()
	{
		if (!m_speechSynth)
		{
			return;
		}
		
		[m_speechSynth pauseSpeakingAtBoundary:NSSpeechImmediateBoundary];
	}
	
	void TTS::resume()
	{
		if (!m_speechSynth)
		{
			return;
		}
		
		[m_speechSynth continueSpeaking];
	}
	
	void TTS::setVolume(const double volume)
	{
		m_volume = std::clamp(volume, 0.0, 1.0);
		
		if (m_speechSynth)
		{
			[m_speechSynth setVolume:m_volume];
		}
	}
	
	double TTS::getVolume() const
	{
		return m_volume;
	}
	
	void TTS::setSpeed(const double speed)
	{
		m_speed = std::clamp(speed, 0.0, 2.0);
		
		if (m_speechSynth)
		{
			[m_speechSynth setRate:detail::ConvertSpeed(m_speed)];
		}
	}
	
	double TTS::getSpeed() const
	{
		return m_speed;
	}
}
