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

# include <Siv3D/VertexShaderAsset.hpp>
# include <Siv3D/Asset/IAsset.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static VertexShader FromAsset(const IAsset* asset)
		{
			if (const VertexShaderAssetData* assetData = dynamic_cast<const VertexShaderAssetData*>(asset))
			{
				return assetData->vs;
			}

			return{};
		}
	}

	VertexShaderAsset::VertexShaderAsset(const AssetNameView name)
		: VertexShader{ detail::FromAsset(SIV3D_ENGINE(Asset)->getAsset(AssetType::VertexShader, name)) } {}

	bool VertexShaderAsset::Register(const AssetName& name, const FilePathView path, const StringView entryPoint, const Array<ConstantBufferBinding>& bindings)
	{
		std::unique_ptr<VertexShaderAssetData> data = std::make_unique<VertexShaderAssetData>(path, entryPoint, bindings);

		return Register(name, std::move(data));
	}

	bool VertexShaderAsset::Register(const AssetName& name, const s3d::HLSL& hlsl)
	{
		std::unique_ptr<VertexShaderAssetData> data = std::make_unique<VertexShaderAssetData>(hlsl);

		return Register(name, std::move(data));
	}

	bool VertexShaderAsset::Register(const AssetName& name, const s3d::GLSL& glsl)
	{
		std::unique_ptr<VertexShaderAssetData> data = std::make_unique<VertexShaderAssetData>(glsl);

		return Register(name, std::move(data));
	}

	bool VertexShaderAsset::Register(const AssetName& name, const s3d::MSL& msl)
	{
		std::unique_ptr<VertexShaderAssetData> data = std::make_unique<VertexShaderAssetData>(msl);

		return Register(name, std::move(data));
	}

	bool VertexShaderAsset::Register(const AssetName& name, const s3d::ESSL& essl)
	{
		std::unique_ptr<VertexShaderAssetData> data = std::make_unique<VertexShaderAssetData>(essl);

		return Register(name, std::move(data));
	}

	bool VertexShaderAsset::Register(const AssetName& name, const ShaderGroup& shaderGroup)
	{
		std::unique_ptr<VertexShaderAssetData> data = std::make_unique<VertexShaderAssetData>(shaderGroup);

		return Register(name, std::move(data));
	}

	bool VertexShaderAsset::Register(const AssetName& name, std::unique_ptr<VertexShaderAssetData>&& data)
	{
		return SIV3D_ENGINE(Asset)->registerAsset(AssetType::VertexShader, name, std::move(data));
	}


	bool VertexShaderAsset::Register(const AssetNameAndTags& nameAndTags, const FilePathView path, const StringView entryPoint, const Array<ConstantBufferBinding>& bindings)
	{
		std::unique_ptr<VertexShaderAssetData> data = std::make_unique<VertexShaderAssetData>(path, entryPoint, bindings, nameAndTags.tags);

		return Register(nameAndTags.name, std::move(data));
	}

	bool VertexShaderAsset::Register(const AssetNameAndTags& nameAndTags, const s3d::HLSL& hlsl)
	{
		std::unique_ptr<VertexShaderAssetData> data = std::make_unique<VertexShaderAssetData>(hlsl, nameAndTags.tags);

		return Register(nameAndTags.name, std::move(data));
	}

	bool VertexShaderAsset::Register(const AssetNameAndTags& nameAndTags, const s3d::GLSL& glsl)
	{
		std::unique_ptr<VertexShaderAssetData> data = std::make_unique<VertexShaderAssetData>(glsl, nameAndTags.tags);

		return Register(nameAndTags.name, std::move(data));
	}

	bool VertexShaderAsset::Register(const AssetNameAndTags& nameAndTags, const s3d::MSL& msl)
	{
		std::unique_ptr<VertexShaderAssetData> data = std::make_unique<VertexShaderAssetData>(msl, nameAndTags.tags);

		return Register(nameAndTags.name, std::move(data));
	}

	bool VertexShaderAsset::Register(const AssetNameAndTags& nameAndTags, const s3d::ESSL& essl)
	{
		std::unique_ptr<VertexShaderAssetData> data = std::make_unique<VertexShaderAssetData>(essl, nameAndTags.tags);

		return Register(nameAndTags.name, std::move(data));
	}

	bool VertexShaderAsset::Register(const AssetNameAndTags& nameAndTags, const ShaderGroup& shaderGroup)
	{
		std::unique_ptr<VertexShaderAssetData> data = std::make_unique<VertexShaderAssetData>(shaderGroup, nameAndTags.tags);

		return Register(nameAndTags.name, std::move(data));
	}

	bool VertexShaderAsset::IsRegistered(const AssetNameView name)
	{
		return SIV3D_ENGINE(Asset)->isRegistered(AssetType::VertexShader, name);
	}

	bool VertexShaderAsset::Load(const AssetNameView name)
	{
		return SIV3D_ENGINE(Asset)->load(AssetType::VertexShader, name, {});
	}

	//void VertexShaderAsset::LoadAsync(const AssetNameView name)
	//{
	//	SIV3D_ENGINE(Asset)->loadAsync(AssetType::VertexShader, name, {});
	//}

	//void VertexShaderAsset::Wait(const AssetNameView name)
	//{
	//	SIV3D_ENGINE(Asset)->wait(AssetType::VertexShader, name);
	//}

	bool VertexShaderAsset::IsReady(const AssetNameView name)
	{
		return SIV3D_ENGINE(Asset)->isReady(AssetType::VertexShader, name);
	}

	void VertexShaderAsset::Release(const AssetNameView name)
	{
		SIV3D_ENGINE(Asset)->release(AssetType::VertexShader, name);
	}

	void VertexShaderAsset::ReleaseAll()
	{
		SIV3D_ENGINE(Asset)->releaseAll(AssetType::VertexShader);
	}

	void VertexShaderAsset::Unregister(const AssetNameView name)
	{
		SIV3D_ENGINE(Asset)->unregister(AssetType::VertexShader, name);
	}

	void VertexShaderAsset::UnregisterAll()
	{
		SIV3D_ENGINE(Asset)->unregisterAll(AssetType::VertexShader);
	}

	HashTable<AssetName, AssetInfo> VertexShaderAsset::Enumerate()
	{
		return SIV3D_ENGINE(Asset)->enumerate(AssetType::VertexShader);
	}
}
