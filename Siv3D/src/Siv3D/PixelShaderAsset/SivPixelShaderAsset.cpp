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

# include <Siv3D/PixelShaderAsset.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Asset/IAsset.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static PixelShader FromAsset(const IAsset* asset)
		{
			if (const PixelShaderAssetData* assetData = dynamic_cast<const PixelShaderAssetData*>(asset))
			{
				return assetData->ps;
			}

			return{};
		}

		[[nodiscard]]
		static bool CheckFileExists(const FilePathView path)
		{
			if (not FileSystem::Exists(path))
			{
				LOG_FAIL(U"❌ PixelShaderAsset::Register(): Shader file `" + path + U"` not found");
				return false;
			}

			return true;
		}
	}

	PixelShaderAsset::PixelShaderAsset(const AssetNameView name)
		: PixelShader{ detail::FromAsset(SIV3D_ENGINE(Asset)->getAsset(AssetType::PixelShader, name)) } {}

	bool PixelShaderAsset::Register(const AssetNameView name, const FilePathView path, const StringView entryPoint, const Array<ConstantBufferBinding>& bindings)
	{
		if (not detail::CheckFileExists(path))
		{
			return false;
		}

		std::unique_ptr<PixelShaderAssetData> data = std::make_unique<PixelShaderAssetData>(path, entryPoint, bindings);

		return Register(name, std::move(data));
	}

	bool PixelShaderAsset::Register(const AssetNameView name, const s3d::HLSL& hlsl)
	{
		if (not detail::CheckFileExists(hlsl.path))
		{
			return false;
		}

		std::unique_ptr<PixelShaderAssetData> data = std::make_unique<PixelShaderAssetData>(hlsl);

		return Register(name, std::move(data));
	}

	bool PixelShaderAsset::Register(const AssetNameView name, const s3d::GLSL& glsl)
	{
		if (not detail::CheckFileExists(glsl.path))
		{
			return false;
		}

		std::unique_ptr<PixelShaderAssetData> data = std::make_unique<PixelShaderAssetData>(glsl);

		return Register(name, std::move(data));
	}

	bool PixelShaderAsset::Register(const AssetNameView name, const s3d::MSL& msl)
	{
		if ((msl.path) && (not detail::CheckFileExists(msl.path)))
		{
			return false;
		}

		std::unique_ptr<PixelShaderAssetData> data = std::make_unique<PixelShaderAssetData>(msl);

		return Register(name, std::move(data));
	}

	bool PixelShaderAsset::Register(const AssetNameView name, const s3d::ESSL& essl)
	{
		if (not detail::CheckFileExists(essl.path))
		{
			return false;
		}

		std::unique_ptr<PixelShaderAssetData> data = std::make_unique<PixelShaderAssetData>(essl);

		return Register(name, std::move(data));
	}

	bool PixelShaderAsset::Register(const AssetNameView name, const s3d::WGSL& wgsl)
	{
		if (not detail::CheckFileExists(wgsl.path))
		{
			return false;
		}

		std::unique_ptr<PixelShaderAssetData> data = std::make_unique<PixelShaderAssetData>(wgsl);

		return Register(name, std::move(data));
	}

	bool PixelShaderAsset::Register(const AssetNameView name, const ShaderGroup& shaderGroup)
	{
		std::unique_ptr<PixelShaderAssetData> data = std::make_unique<PixelShaderAssetData>(shaderGroup);

		return Register(name, std::move(data));
	}

	bool PixelShaderAsset::Register(const AssetNameView name, std::unique_ptr<PixelShaderAssetData>&& data)
	{
		return SIV3D_ENGINE(Asset)->registerAsset(AssetType::PixelShader, name, std::move(data));
	}


	bool PixelShaderAsset::Register(const AssetNameAndTags& nameAndTags, const FilePathView path, const StringView entryPoint, const Array<ConstantBufferBinding>& bindings)
	{
		if (not detail::CheckFileExists(path))
		{
			return false;
		}

		std::unique_ptr<PixelShaderAssetData> data = std::make_unique<PixelShaderAssetData>(path, entryPoint, bindings, nameAndTags.tags);

		return Register(nameAndTags.name, std::move(data));
	}

	bool PixelShaderAsset::Register(const AssetNameAndTags& nameAndTags, const s3d::HLSL& hlsl)
	{
		if (not detail::CheckFileExists(hlsl.path))
		{
			return false;
		}

		std::unique_ptr<PixelShaderAssetData> data = std::make_unique<PixelShaderAssetData>(hlsl, nameAndTags.tags);

		return Register(nameAndTags.name, std::move(data));
	}

	bool PixelShaderAsset::Register(const AssetNameAndTags& nameAndTags, const s3d::GLSL& glsl)
	{
		if (not detail::CheckFileExists(glsl.path))
		{
			return false;
		}

		std::unique_ptr<PixelShaderAssetData> data = std::make_unique<PixelShaderAssetData>(glsl, nameAndTags.tags);

		return Register(nameAndTags.name, std::move(data));
	}

	bool PixelShaderAsset::Register(const AssetNameAndTags& nameAndTags, const s3d::MSL& msl)
	{
		if ((msl.path) && (not detail::CheckFileExists(msl.path)))
		{
			return false;
		}

		std::unique_ptr<PixelShaderAssetData> data = std::make_unique<PixelShaderAssetData>(msl, nameAndTags.tags);

		return Register(nameAndTags.name, std::move(data));
	}

	bool PixelShaderAsset::Register(const AssetNameAndTags& nameAndTags, const s3d::ESSL& essl)
	{
		if (not detail::CheckFileExists(essl.path))
		{
			return false;
		}

		std::unique_ptr<PixelShaderAssetData> data = std::make_unique<PixelShaderAssetData>(essl, nameAndTags.tags);

		return Register(nameAndTags.name, std::move(data));
	}

	bool PixelShaderAsset::Register(const AssetNameAndTags& nameAndTags, const s3d::WGSL& wgsl)
	{
		if (not detail::CheckFileExists(wgsl.path))
		{
			return false;
		}

		std::unique_ptr<PixelShaderAssetData> data = std::make_unique<PixelShaderAssetData>(wgsl, nameAndTags.tags);

		return Register(nameAndTags.name, std::move(data));
	}

	bool PixelShaderAsset::Register(const AssetNameAndTags& nameAndTags, const ShaderGroup& shaderGroup)
	{
		std::unique_ptr<PixelShaderAssetData> data = std::make_unique<PixelShaderAssetData>(shaderGroup, nameAndTags.tags);

		return Register(nameAndTags.name, std::move(data));
	}

	bool PixelShaderAsset::IsRegistered(const AssetNameView name)
	{
		return SIV3D_ENGINE(Asset)->isRegistered(AssetType::PixelShader, name);
	}

	bool PixelShaderAsset::Load(const AssetNameView name)
	{
		return SIV3D_ENGINE(Asset)->load(AssetType::PixelShader, name, {});
	}

	//void PixelShaderAsset::LoadAsync(const AssetNameView name)
	//{
	//	SIV3D_ENGINE(Asset)->loadAsync(AssetType::PixelShader, name, {});
	//}

	//void PixelShaderAsset::Wait(const AssetNameView name)
	//{
	//	SIV3D_ENGINE(Asset)->wait(AssetType::PixelShader, name);
	//}

	bool PixelShaderAsset::IsReady(const AssetNameView name)
	{
		return SIV3D_ENGINE(Asset)->isReady(AssetType::PixelShader, name);
	}

	void PixelShaderAsset::Release(const AssetNameView name)
	{
		SIV3D_ENGINE(Asset)->release(AssetType::PixelShader, name);
	}

	void PixelShaderAsset::ReleaseAll()
	{
		SIV3D_ENGINE(Asset)->releaseAll(AssetType::PixelShader);
	}

	void PixelShaderAsset::Unregister(const AssetNameView name)
	{
		SIV3D_ENGINE(Asset)->unregister(AssetType::PixelShader, name);
	}

	void PixelShaderAsset::UnregisterAll()
	{
		SIV3D_ENGINE(Asset)->unregisterAll(AssetType::PixelShader);
	}

	HashTable<AssetName, AssetInfo> PixelShaderAsset::Enumerate()
	{
		return SIV3D_ENGINE(Asset)->enumerate(AssetType::PixelShader);
	}
}
