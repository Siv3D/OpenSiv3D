//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "../Siv3DEngine.hpp"
# include "../Asset/IAsset.hpp"
# include <Siv3D/AudioAsset.hpp>

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

	AudioAsset::AudioAsset(const AssetName& name)
		: Audio(detail::FromAsset(Siv3DEngine::GetAsset()->getAsset(AssetType::Audio, name)))
	{

	}

	bool AudioAsset::Register(const AssetName& name, const FilePath& path, const AssetParameter& parameter)
	{
		return Register(name, path, none, parameter);
	}

	bool AudioAsset::Register(const AssetName& name, const FilePath& path, const Optional<AudioLoopTiming>& loop, const AssetParameter& parameter)
	{
		return Siv3DEngine::GetAsset()->registerAsset(AssetType::Audio, name, std::make_unique<AudioAssetData>(path, loop, parameter));
	}

	bool AudioAsset::Register(const AssetName& name, const AudioAssetData& data)
	{
		return Siv3DEngine::GetAsset()->registerAsset(AssetType::Audio, name, std::make_unique<AudioAssetData>(data));
	}

	bool AudioAsset::IsRegistered(const AssetName& name)
	{
		return Siv3DEngine::GetAsset()->isRegistered(AssetType::Audio, name);
	}

	bool AudioAsset::Preload(const AssetName& name)
	{
		return Siv3DEngine::GetAsset()->preload(AssetType::Audio, name);
	}

	void AudioAsset::Release(const AssetName& name)
	{
		Siv3DEngine::GetAsset()->release(AssetType::Audio, name);
	}

	void AudioAsset::ReleaseAll()
	{
		Siv3DEngine::GetAsset()->releaseAll(AssetType::Audio);
	}

	void AudioAsset::Unregister(const AssetName& name)
	{
		Siv3DEngine::GetAsset()->unregister(AssetType::Audio, name);
	}

	void AudioAsset::UnregisterAll()
	{
		Siv3DEngine::GetAsset()->unregisterAll(AssetType::Audio);
	}

	bool AudioAsset::IsReady(const AssetName& name)
	{
		return Siv3DEngine::GetAsset()->isReady(AssetType::Audio, name);
	}
}
