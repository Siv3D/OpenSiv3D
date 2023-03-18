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

# include <Siv3D/AudioAssetData.hpp>

namespace s3d
{
	AudioAssetData::AudioAssetData() {}

	AudioAssetData::AudioAssetData(const FilePathView _path, const Optional<AudioLoopTiming>& _loopTiming, const Array<AssetTag>& tags)
		: IAsset{ tags }
		, path{ _path }
		, loopTiming{ _loopTiming } {}

	AudioAssetData::AudioAssetData(Audio::FileStreaming, const FilePathView _path, const Array<AssetTag>& tags)
		: IAsset{ tags }
		, path{ _path }
		, streaming{ true } {}

	AudioAssetData::AudioAssetData(Audio::FileStreaming, const FilePathView _path, const Arg::loopBegin_<uint64> _loopBegin, const Array<AssetTag>& tags)
		: IAsset{ tags }
		, path{ _path }
		, loopTiming{ AudioLoopTiming{ *_loopBegin, 0 } }
		, streaming{ true } {}

	AudioAssetData::AudioAssetData(const GMInstrument _instrument, const uint8 _key, const Duration& _noteOn, const Duration& _noteOff, const double _velocity, Arg::sampleRate_<uint32> _sampleRate, const Array<AssetTag>& tags)
		: IAsset{ tags }
		, instrument{ _instrument }
		, key{ _key }
		, noteOn{ _noteOn }
		, noteOff{ _noteOff }
		, velocity{ _velocity }
		, sampleRate{ *_sampleRate } {}

	bool AudioAssetData::load(const String& hint)
	{
		if (isUninitialized())
		{
			if (onLoad(*this, hint))
			{
				setState(AssetState::Loaded);
				return true;
			}
			else
			{
				setState(AssetState::Failed);
				return false;
			}
		}

		if (isAsyncLoading())
		{
			wait();
		}

		return isLoaded();
	}

	void AudioAssetData::loadAsync(const String& hint)
	{
		if (isUninitialized())
		{
			setState(AssetState::AsyncLoading);

			m_task = Async([this, hint = hint]()
				{
					setState(onLoad(*this, hint) ? AssetState::Loaded : AssetState::Failed);
				});
		}
	}

	void AudioAssetData::wait()
	{
		if (m_task.isValid())
		{
			m_task.get();
		}
	}

	void AudioAssetData::release()
	{
		if (isUninitialized())
		{
			return;
		}

		if (isAsyncLoading())
		{
			wait();
		}

		onRelease(*this);

		setState(AssetState::Uninitialized);
	}

	bool AudioAssetData::DefaultLoad(AudioAssetData& asset, const String&)
	{
		if (asset.audio)
		{
			return true;
		}

		if (asset.path)
		{
			if (asset.streaming)
			{
				if (asset.loopTiming)
				{
					asset.audio = Audio{ Audio::Stream, asset.path, Arg::loopBegin = asset.loopTiming->beginPos };
				}
				else
				{
					asset.audio = Audio{ Audio::Stream, asset.path };
				}
			}
			else
			{
				asset.audio = Audio{ asset.path, asset.loopTiming };
			}
		}
		else
		{
			asset.audio = Audio{ asset.instrument, asset.key, asset.noteOn, asset.noteOff, asset.velocity, asset.sampleRate };
		}

		if (not asset.audio)
		{
			return false;
		}

		return true;
	}

	void AudioAssetData::DefaultRelease(AudioAssetData& asset)
	{
		asset.audio.release();
	}
}
