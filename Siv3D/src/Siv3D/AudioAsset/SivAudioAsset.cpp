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

# include <Siv3D/AudioAsset.hpp>
# include <Siv3DEngine.hpp>
# include <Asset/IAsset.hpp>

namespace s3d
{
	namespace detail
	{
		static Audio FromAsset(const IAsset* asset)
		{
			if (const AudioAssetData* audioAssetData = dynamic_cast<const AudioAssetData*>(asset))
			{
				return audioAssetData->audio;
			}

			return Audio();
		}
	}

	const String& AudioAssetData::Name()
	{
		static const String name = U"Audio";

		return name;
	}

	bool AudioAssetData::DefaultPreload(AudioAssetData& asset)
	{
		if (asset.audio)
		{
			return true;
		}

		asset.audio = Audio(asset.path, asset.loop);

		return !asset.audio.isEmpty();
	}

	bool AudioAssetData::DefaultUpdate(AudioAssetData&)
	{
		return true;
	}

	bool AudioAssetData::DefaultRelease(AudioAssetData& asset)
	{
		asset.audio.release();

		return true;
	}

	AudioAssetData::AudioAssetData()
		: IAsset()
		, onPreload(DefaultPreload)
		, onUpdate(DefaultUpdate)
		, onRelease(DefaultRelease)
	{

	}

	AudioAssetData::AudioAssetData(
		const FilePath& _path,
		const Optional<AudioLoopTiming>& _loop,
		const AssetParameter& _parameter,
		std::function<bool(AudioAssetData&)> _onPreload,
		std::function<bool(AudioAssetData&)> _onUpdate,
		std::function<bool(AudioAssetData&)> _onRelease)
		: IAsset(_parameter)
		, path(_path)
		, loop(_loop)
		, onPreload(_onPreload)
		, onUpdate(_onUpdate)
		, onRelease(_onRelease)
	{

	}

	bool AudioAssetData::preload()
	{
		if (uninitialized())
		{
			setState(onPreload(*this) ? State::LoadSucceeded : State::LoadFailed);
		}

		return loadSucceeded();
	}

	void AudioAssetData::preloadAsync()
	{
		if (uninitialized())
		{
			launchLoading([this]() { return onPreload(*this); });

			setState(State::PreloadingAsync);
		}
	}

	bool AudioAssetData::update()
	{
		if (!isPreloaded())
		{
			return false;
		}

		return onUpdate(*this);
	}

	bool AudioAssetData::release()
	{
		if (uninitialized())
		{
			return true;
		}

		const bool result = onRelease(*this);

		setState(State::Uninitialized);

		return result;
	}

	AudioAsset::AudioAsset(const AssetName& name)
		: Audio(detail::FromAsset(Siv3DEngine::Get<ISiv3DAsset>()->getAsset(AssetType::Audio, name)))
	{

	}

	bool AudioAsset::Register(const AssetName& name, const FilePath& path, const AssetParameter& parameter)
	{
		return Register(name, path, none, parameter);
	}

	bool AudioAsset::Register(const AssetName& name, const FilePath& path, const Optional<AudioLoopTiming>& loop, const AssetParameter& parameter)
	{
		return Siv3DEngine::Get<ISiv3DAsset>()->registerAsset(AssetType::Audio, name, std::make_unique<AudioAssetData>(path, loop, parameter));
	}

	bool AudioAsset::Register(const AssetName& name, const GMInstrument instrumrnt, const uint8 key, const Duration& duration, const AssetParameter& parameter)
	{
		return Register(name, instrumrnt, key, duration, 1.0, Wave::DefaultSamplingRate, 0.01f, parameter);
	}

	bool AudioAsset::Register(const AssetName& name, const GMInstrument instrumrnt, const uint8 key, const Duration& duration, const double velocity, const AssetParameter& parameter)
	{
		return Register(name, instrumrnt, key, duration, velocity, Wave::DefaultSamplingRate, 0.01f, parameter);
	}

	bool AudioAsset::Register(const AssetName& name, const GMInstrument instrumrnt, const uint8 key, const Duration& duration, const double velocity, Arg::samplingRate_<uint32> samplingRate, const AssetParameter& parameter)
	{
		return Register(name, instrumrnt, key, duration, velocity, samplingRate, 0.01f, parameter);
	}

	bool AudioAsset::Register(const AssetName& name, const GMInstrument instrumrnt, const uint8 key, const Duration& duration, const double velocity, Arg::samplingRate_<uint32> samplingRate, const float silenceValue, const AssetParameter& parameter)
	{
		return Register(name, AudioAssetData(FilePath(), none, parameter,
			[=](AudioAssetData& a) { a.audio = Audio(instrumrnt, key, duration, velocity, samplingRate, silenceValue); return !!a.audio; },
			AudioAssetData::DefaultUpdate,
			AudioAssetData::DefaultRelease
		));
	}

	bool AudioAsset::Register(const AssetName& name, const AudioAssetData& data)
	{
		return Siv3DEngine::Get<ISiv3DAsset>()->registerAsset(AssetType::Audio, name, std::make_unique<AudioAssetData>(data));
	}

	bool AudioAsset::IsRegistered(const AssetName& name)
	{
		return Siv3DEngine::Get<ISiv3DAsset>()->isRegistered(AssetType::Audio, name);
	}

	bool AudioAsset::Preload(const AssetName& name)
	{
		return Siv3DEngine::Get<ISiv3DAsset>()->preload(AssetType::Audio, name);
	}

	void AudioAsset::Release(const AssetName& name)
	{
		Siv3DEngine::Get<ISiv3DAsset>()->release(AssetType::Audio, name);
	}

	void AudioAsset::ReleaseAll()
	{
		Siv3DEngine::Get<ISiv3DAsset>()->releaseAll(AssetType::Audio);
	}

	void AudioAsset::Unregister(const AssetName& name)
	{
		Siv3DEngine::Get<ISiv3DAsset>()->unregister(AssetType::Audio, name);
	}

	void AudioAsset::UnregisterAll()
	{
		Siv3DEngine::Get<ISiv3DAsset>()->unregisterAll(AssetType::Audio);
	}

	bool AudioAsset::IsReady(const AssetName& name)
	{
		return Siv3DEngine::Get<ISiv3DAsset>()->isReady(AssetType::Audio, name);
	}
}
