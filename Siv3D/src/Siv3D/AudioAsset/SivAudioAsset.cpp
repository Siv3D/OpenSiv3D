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

# include <Siv3D/AudioAsset.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Asset/IAsset.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static Audio FromAsset(const IAsset* asset)
		{
			if (const AudioAssetData* assetData = dynamic_cast<const AudioAssetData*>(asset))
			{
				return assetData->audio;
			}

			return{};
		}

		[[nodiscard]]
		static bool CheckFileExists(const FilePathView path)
		{
			if (not FileSystem::Exists(path))
			{
				LOG_FAIL(U"❌ AudioAsset::Register(): Audio file `" + path + U"` not found");
				return false;
			}

			return true;
		}
	}

	AudioAsset::AudioAsset(const AssetNameView name)
		: Audio{ detail::FromAsset(SIV3D_ENGINE(Asset)->getAsset(AssetType::Audio, name)) } {}
	
	bool AudioAsset::Register(const AssetNameView name, const FilePathView path)
	{
		return Register(name, path, none);
	}

	bool AudioAsset::Register(const AssetNameView name, const FilePathView path, const Loop loop)
	{
		if (loop)
		{
			return Register(name, path, AudioLoopTiming{});
		}
		else
		{
			return Register(name, path, none);
		}
	}

	bool AudioAsset::Register(const AssetNameView name, const FilePathView path, const Arg::loopBegin_<uint64> loopBegin)
	{
		return Register(name, path, AudioLoopTiming{ *loopBegin });
	}

	bool AudioAsset::Register(const AssetNameView name, const FilePathView path, const Arg::loopBegin_<uint64> loopBegin, const Arg::loopEnd_<uint64> loopEnd)
	{
		return Register(name, path, AudioLoopTiming{ *loopBegin, *loopEnd });
	}

	bool AudioAsset::Register(const AssetNameView name, const FilePathView path, const Optional<AudioLoopTiming>& loop)
	{
		if (not detail::CheckFileExists(path))
		{
			return false;
		}

		std::unique_ptr<AudioAssetData> data = std::make_unique<AudioAssetData>(path, loop);

		return Register(name, std::move(data));
	}

	bool AudioAsset::Register(const AssetNameView name, Audio::FileStreaming, const FilePathView path)
	{
		return Register(name, Audio::Stream, path, Loop::No);
	}

	bool AudioAsset::Register(const AssetNameView name, Audio::FileStreaming, const FilePathView path, const Loop loop)
	{
		if (not detail::CheckFileExists(path))
		{
			return false;
		}

		std::unique_ptr<AudioAssetData> data;
		
		if (loop)
		{
			data = std::make_unique<AudioAssetData>(Audio::Stream, path, Arg::loopBegin = 0);
		}
		else
		{
			data = std::make_unique<AudioAssetData>(Audio::Stream, path);
		}

		return Register(name, std::move(data));
	}

	bool AudioAsset::Register(const AssetNameView name, Audio::FileStreaming, const FilePathView path, const Arg::loopBegin_<uint64> loopBegin)
	{
		if (not detail::CheckFileExists(path))
		{
			return false;
		}

		std::unique_ptr<AudioAssetData> data = std::make_unique<AudioAssetData>(Audio::Stream, path, loopBegin);

		return Register(name, std::move(data));
	}

	bool AudioAsset::Register(const AssetNameView name, const GMInstrument instrument, const uint8 key, const Duration& duration, const double velocity, const Arg::sampleRate_<uint32> sampleRate)
	{
		return Register(name, instrument, key, duration, SecondsF{ 1.0 }, velocity, sampleRate);
	}

	bool AudioAsset::Register(const AssetNameView name, const GMInstrument instrument, const uint8 key, const Duration& noteOn, const Duration& noteOff, const double velocity, const Arg::sampleRate_<uint32> sampleRate)
	{
		std::unique_ptr<AudioAssetData> data = std::make_unique<AudioAssetData>(instrument, key, noteOn, noteOff, velocity, sampleRate);

		return Register(name, std::move(data));
	}

	bool AudioAsset::Register(const AssetNameView name, std::unique_ptr<AudioAssetData>&& data)
	{
		return SIV3D_ENGINE(Asset)->registerAsset(AssetType::Audio, name, std::move(data));
	}

	bool AudioAsset::Register(const AssetNameAndTags& nameAndTag, const FilePathView path)
	{
		return Register(nameAndTag, path, none);
	}

	bool AudioAsset::Register(const AssetNameAndTags& nameAndTag, const FilePathView path, const Loop loop)
	{
		if (loop)
		{
			return Register(nameAndTag, path, AudioLoopTiming{});
		}
		else
		{
			return Register(nameAndTag, path, none);
		}
	}

	bool AudioAsset::Register(const AssetNameAndTags& nameAndTag, const FilePathView path, const Arg::loopBegin_<uint64> loopBegin)
	{
		return Register(nameAndTag, path, AudioLoopTiming{ *loopBegin });
	}

	bool AudioAsset::Register(const AssetNameAndTags& nameAndTag, const FilePathView path, const Arg::loopBegin_<uint64> loopBegin, const Arg::loopEnd_<uint64> loopEnd)
	{
		return Register(nameAndTag, path, AudioLoopTiming{ *loopBegin, *loopEnd });
	}

	bool AudioAsset::Register(const AssetNameAndTags& nameAndTag, const FilePathView path, const Optional<AudioLoopTiming>& loop)
	{
		if (not detail::CheckFileExists(path))
		{
			return false;
		}

		std::unique_ptr<AudioAssetData> data = std::make_unique<AudioAssetData>(path, loop, nameAndTag.tags);

		return Register(nameAndTag.name, std::move(data));
	}

	bool AudioAsset::Register(const AssetNameAndTags& nameAndTag, Audio::FileStreaming, const FilePathView path)
	{
		return Register(nameAndTag, Audio::Stream, path, Loop::No);
	}

	bool AudioAsset::Register(const AssetNameAndTags& nameAndTag, Audio::FileStreaming, const FilePathView path, const Loop loop)
	{
		if (not detail::CheckFileExists(path))
		{
			return false;
		}

		std::unique_ptr<AudioAssetData> data;

		if (loop)
		{
			data = std::make_unique<AudioAssetData>(Audio::Stream, path, Arg::loopBegin = 0, nameAndTag.tags);
		}
		else
		{
			data = std::make_unique<AudioAssetData>(Audio::Stream, path, nameAndTag.tags);
		}

		return Register(nameAndTag.name, std::move(data));
	}

	bool AudioAsset::Register(const AssetNameAndTags& nameAndTag, Audio::FileStreaming, const FilePathView path, const Arg::loopBegin_<uint64> loopBegin)
	{
		if (not detail::CheckFileExists(path))
		{
			return false;
		}

		std::unique_ptr<AudioAssetData> data = std::make_unique<AudioAssetData>(Audio::Stream, path, loopBegin, nameAndTag.tags);

		return Register(nameAndTag.name, std::move(data));
	}

	bool AudioAsset::Register(const AssetNameAndTags& nameAndTag, const GMInstrument instrument, const uint8 key, const Duration& duration, const double velocity, const Arg::sampleRate_<uint32> sampleRate)
	{
		return Register(nameAndTag, instrument, key, duration, SecondsF{ 1.0 }, velocity, sampleRate);
	}

	bool AudioAsset::Register(const AssetNameAndTags& nameAndTag, const GMInstrument instrument, const uint8 key, const Duration& noteOn, const Duration& noteOff, const double velocity, const Arg::sampleRate_<uint32> sampleRate)
	{
		std::unique_ptr<AudioAssetData> data = std::make_unique<AudioAssetData>(instrument, key, noteOn, noteOff, velocity, sampleRate, nameAndTag.tags);

		return Register(nameAndTag.name, std::move(data));
	}


	bool AudioAsset::IsRegistered(const AssetNameView name)
	{
		return SIV3D_ENGINE(Asset)->isRegistered(AssetType::Audio, name);
	}

	bool AudioAsset::Load(const AssetNameView name)
	{
		return SIV3D_ENGINE(Asset)->load(AssetType::Audio, name, {});
	}

	void AudioAsset::LoadAsync(const AssetNameView name)
	{
		SIV3D_ENGINE(Asset)->loadAsync(AssetType::Audio, name, {});
	}

	void AudioAsset::Wait(const AssetNameView name)
	{
		SIV3D_ENGINE(Asset)->wait(AssetType::Audio, name);
	}

	bool AudioAsset::IsReady(const AssetNameView name)
	{
		return SIV3D_ENGINE(Asset)->isReady(AssetType::Audio, name);
	}

	void AudioAsset::Release(const AssetNameView name)
	{
		SIV3D_ENGINE(Asset)->release(AssetType::Audio, name);
	}

	void AudioAsset::ReleaseAll()
	{
		SIV3D_ENGINE(Asset)->releaseAll(AssetType::Audio);
	}

	void AudioAsset::Unregister(const AssetNameView name)
	{
		SIV3D_ENGINE(Asset)->unregister(AssetType::Audio, name);
	}

	void AudioAsset::UnregisterAll()
	{
		SIV3D_ENGINE(Asset)->unregisterAll(AssetType::Audio);
	}

	HashTable<AssetName, AssetInfo> AudioAsset::Enumerate()
	{
		return SIV3D_ENGINE(Asset)->enumerate(AssetType::Audio);
	}
}
