//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Audio.hpp>
# include <Siv3D/Audio/IAudio.hpp>
# include <Siv3D/FreestandingMessageBox/FreestandingMessageBox.hpp>
# include <Siv3D/AssetMonitor/IAssetMonitor.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	template <>
	AssetIDWrapper<AssetHandle<Audio>>::AssetIDWrapper()
	{
		if (not Siv3DEngine::isActive())
		{
			FreestandingMessageBox::ShowError(U"`Audio` must be initialized after engine-setup. Please fix the C++ code.");
			std::abort();
		}
	}

	template <>
	AssetIDWrapper<AssetHandle<Audio>>::~AssetIDWrapper()
	{
		if (not Siv3DEngine::isActive())
		{
			return;
		}

		if (auto p = SIV3D_ENGINE(Audio))
		{
			p->release(m_id);
		}
	}

	Audio::Audio() {}

	Audio::Audio(Wave&& wave)
		: Audio{ std::move(wave), Loop::Yes } {}

	Audio::Audio(Wave&& wave, const Loop loop)
		:Audio{ std::move(wave), (loop ? Optional<AudioLoopTiming>{{ 0, 0 }} : none) } {}

	Audio::Audio(Wave&& wave, const Arg::loopBegin_<uint64> loopBegin)
		: Audio{ std::move(wave), AudioLoopTiming{ *loopBegin, 0 } } {}

	Audio::Audio(Wave&& wave, const Arg::loopBegin_<uint64> loopBegin, const Arg::loopEnd_<uint64> loopEnd)
		: Audio{ std::move(wave), AudioLoopTiming{ *loopBegin, *loopEnd } } {}

	Audio::Audio(Wave&& wave, const Arg::loopBegin_<Duration> loopBegin)
		: Audio{ std::move(wave), loopBegin, Arg::loopEnd = Duration{ 0 } } {}

	Audio::Audio(Wave&& wave, const Arg::loopBegin_<Duration> loopBegin, const Arg::loopEnd_<Duration> loopEnd)
		: AssetHandle{ std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Audio)->create(std::move(wave), *loopBegin, *loopEnd)) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Audio::Audio(Wave&& wave, const Optional<AudioLoopTiming>& loop)
		: AssetHandle{ std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Audio)->create(std::move(wave), loop)) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Audio::Audio(const Wave& wave)
		: Audio{ wave, Loop::No } {}

	Audio::Audio(const Wave& wave, const Loop loop)
		: Audio{ wave, (loop ? Optional<AudioLoopTiming>{{ 0, 0 }} : none) } {}

	Audio::Audio(const Wave& wave, const Arg::loopBegin_<uint64> loopBegin)
		: Audio{ wave, AudioLoopTiming{ *loopBegin, 0 } } {}

	Audio::Audio(const Wave& wave, const Arg::loopBegin_<uint64> loopBegin, const Arg::loopEnd_<uint64> loopEnd)
		: Audio{ wave, AudioLoopTiming{ *loopBegin, *loopEnd } } {}

	Audio::Audio(const Wave& wave, const Arg::loopBegin_<Duration> loopBegin)
		: Audio{ wave, AudioLoopTiming{ static_cast<uint64>(loopBegin->count() * wave.sampleRate()), 0 } } {}

	Audio::Audio(const Wave& wave, const Arg::loopBegin_<Duration> loopBegin, const Arg::loopEnd_<Duration> loopEnd)
		: Audio{ wave, AudioLoopTiming{ static_cast<uint64>(loopBegin->count() * wave.sampleRate()), static_cast<uint64>(loopEnd->count() * wave.sampleRate()) } } {}

	Audio::Audio(const Wave& wave, const Optional<AudioLoopTiming>& loop)
		: AssetHandle{ std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Audio)->create(Wave{ wave }, loop)) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Audio::Audio(const FilePathView path)
		: Audio{ path, Loop::No } {}

	Audio::Audio(const FilePathView path, const Loop loop)
		: Audio{ Wave{ path }, loop } {}

	Audio::Audio(const FilePathView path, const Arg::loopBegin_<uint64> loopBegin)
		: Audio{ path, AudioLoopTiming{ *loopBegin, 0 } } {}

	Audio::Audio(const FilePathView path, const Arg::loopBegin_<uint64> loopBegin, const Arg::loopEnd_<uint64> loopEnd)
		: Audio{ path, AudioLoopTiming{ *loopBegin, *loopEnd } } {}

	Audio::Audio(const FilePathView path, const Arg::loopBegin_<Duration> loopBegin)
		: Audio{ path, loopBegin, Arg::loopEnd = Duration{ 0 } } {}

	Audio::Audio(const FilePathView path, const Arg::loopBegin_<Duration> loopBegin, const Arg::loopEnd_<Duration> loopEnd)
		: Audio{ Wave{ path }, loopBegin, loopEnd } {}

	Audio::Audio(const FilePathView path, const Optional<AudioLoopTiming>& loop)
		: Audio{ Wave{ path }, loop } {}

	Audio::Audio(FileStreaming, const FilePathView path)
		: AssetHandle{ std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Audio)->createStreamingNonLoop(path)) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Audio::Audio(FileStreaming, const FilePathView path, const Loop loop)
		: AssetHandle{ std::make_shared<AssetIDWrapperType>(
			((loop ? SIV3D_ENGINE(Audio)->createStreamingNonLoop(path) : SIV3D_ENGINE(Audio)->createStreamingLoop(path, 0)))) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Audio::Audio(FileStreaming, const FilePathView path, const Arg::loopBegin_<uint64> loopBegin)
		: AssetHandle{ std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Audio)->createStreamingLoop(path, *loopBegin)) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Audio::Audio(const GMInstrument instrument, const uint8 key, const Duration& duration, const double velocity, const Arg::sampleRate_<uint32> sampleRate)
		: Audio{ Wave{ instrument, key, duration, velocity, sampleRate } } {}

	Audio::Audio(const GMInstrument instrument, const uint8 key, const Duration& noteOn, const Duration& noteOff, const double velocity, const Arg::sampleRate_<uint32> sampleRate)
		: Audio{ Wave{ instrument, key, noteOn, noteOff, velocity, sampleRate } } {}

	Audio::Audio(IReader&& reader, const AudioFormat format)
		: Audio{ Wave{ std::move(reader), format } } {}

	Audio::~Audio() {}

	/*

	bool Font::addFallback(const Font& font) const
	{
		if (not font)
		{
			LOG_FAIL(U"Font::addFallback() failed (font is empty)");
			return false;
		}

		return SIV3D_ENGINE(Font)->addFallbackFont(m_handle->id(), font.m_handle);
	}

	const String& Font::familyName() const
	{
		return SIV3D_ENGINE(Font)->getProperty(m_handle->id()).familiyName;
	}
	*/
}
