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

# include <Siv3D/AudioAsset.hpp>
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
	}

	AudioAsset::AudioAsset(const AssetNameView name)
		: Audio{ detail::FromAsset(SIV3D_ENGINE(Asset)->getAsset(AssetType::Audio, name)) } {}

	//bool AudioAsset::Register(const AssetName& name, const FilePathView path, const StringView entryPoint, const Array<ConstantBufferBinding>& bindings)
	//{
	//	std::unique_ptr<AudioAssetData> data = std::make_unique<AudioAssetData>(path, entryPoint, bindings);

	//	return Register(name, std::move(data));
	//}

	//bool AudioAsset::Register(const AssetName& name, const s3d::HLSL& hlsl)
	//{
	//	std::unique_ptr<AudioAssetData> data = std::make_unique<AudioAssetData>(hlsl);

	//	return Register(name, std::move(data));
	//}

	//bool AudioAsset::Register(const AssetName& name, const s3d::GLSL& glsl)
	//{
	//	std::unique_ptr<AudioAssetData> data = std::make_unique<AudioAssetData>(glsl);

	//	return Register(name, std::move(data));
	//}

	//bool AudioAsset::Register(const AssetName& name, const s3d::MSL& msl)
	//{
	//	std::unique_ptr<AudioAssetData> data = std::make_unique<AudioAssetData>(msl);

	//	return Register(name, std::move(data));
	//}

	//bool AudioAsset::Register(const AssetName& name, const s3d::ESSL& essl)
	//{
	//	std::unique_ptr<AudioAssetData> data = std::make_unique<AudioAssetData>(essl);

	//	return Register(name, std::move(data));
	//}

	//bool AudioAsset::Register(const AssetName& name, const ShaderGroup& shaderGroup)
	//{
	//	std::unique_ptr<AudioAssetData> data = std::make_unique<AudioAssetData>(shaderGroup);

	//	return Register(name, std::move(data));
	//}

	//bool AudioAsset::Register(const AssetName& name, std::unique_ptr<AudioAssetData>&& data)
	//{
	//	return SIV3D_ENGINE(Asset)->registerAsset(AssetType::Audio, name, std::move(data));
	//}


	//bool AudioAsset::Register(const AssetNameAndTags& nameAndTags, const FilePathView path, const StringView entryPoint, const Array<ConstantBufferBinding>& bindings)
	//{
	//	std::unique_ptr<AudioAssetData> data = std::make_unique<AudioAssetData>(path, entryPoint, bindings, nameAndTags.tags);

	//	return Register(nameAndTags.name, std::move(data));
	//}

	//bool AudioAsset::Register(const AssetNameAndTags& nameAndTags, const s3d::HLSL& hlsl)
	//{
	//	std::unique_ptr<AudioAssetData> data = std::make_unique<AudioAssetData>(hlsl, nameAndTags.tags);

	//	return Register(nameAndTags.name, std::move(data));
	//}

	//bool AudioAsset::Register(const AssetNameAndTags& nameAndTags, const s3d::GLSL& glsl)
	//{
	//	std::unique_ptr<AudioAssetData> data = std::make_unique<AudioAssetData>(glsl, nameAndTags.tags);

	//	return Register(nameAndTags.name, std::move(data));
	//}

	//bool AudioAsset::Register(const AssetNameAndTags& nameAndTags, const s3d::MSL& msl)
	//{
	//	std::unique_ptr<AudioAssetData> data = std::make_unique<AudioAssetData>(msl, nameAndTags.tags);

	//	return Register(nameAndTags.name, std::move(data));
	//}

	//bool AudioAsset::Register(const AssetNameAndTags& nameAndTags, const s3d::ESSL& essl)
	//{
	//	std::unique_ptr<AudioAssetData> data = std::make_unique<AudioAssetData>(essl, nameAndTags.tags);

	//	return Register(nameAndTags.name, std::move(data));
	//}

	//bool AudioAsset::Register(const AssetNameAndTags& nameAndTags, const ShaderGroup& shaderGroup)
	//{
	//	std::unique_ptr<AudioAssetData> data = std::make_unique<AudioAssetData>(shaderGroup, nameAndTags.tags);

	//	return Register(nameAndTags.name, std::move(data));
	//}

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
