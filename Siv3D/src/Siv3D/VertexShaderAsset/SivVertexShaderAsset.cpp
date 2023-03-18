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

# include <Siv3D/VertexShaderAsset.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/EngineLog.hpp>
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

		[[nodiscard]]
		static bool CheckFileExists(const FilePathView path)
		{
			if (not FileSystem::Exists(path))
			{
				LOG_FAIL(U"❌ VertexShaderAsset::Register(): Shader file `" + path + U"` not found");
				return false;
			}

			return true;
		}
	}

	VertexShaderAsset::VertexShaderAsset(const AssetNameView name)
		: VertexShader{ detail::FromAsset(SIV3D_ENGINE(Asset)->getAsset(AssetType::VertexShader, name)) } {}

	bool VertexShaderAsset::Register(const AssetNameView name, const FilePathView path, const StringView entryPoint, const Array<ConstantBufferBinding>& bindings)
	{
		if (not detail::CheckFileExists(path))
		{
			return false;
		}

		std::unique_ptr<VertexShaderAssetData> data = std::make_unique<VertexShaderAssetData>(path, entryPoint, bindings);

		return Register(name, std::move(data));
	}

	bool VertexShaderAsset::Register(const AssetNameView name, const s3d::HLSL& hlsl)
	{
		if (not detail::CheckFileExists(hlsl.path))
		{
			return false;
		}

		std::unique_ptr<VertexShaderAssetData> data = std::make_unique<VertexShaderAssetData>(hlsl);

		return Register(name, std::move(data));
	}

	bool VertexShaderAsset::Register(const AssetNameView name, const s3d::GLSL& glsl)
	{
		if (not detail::CheckFileExists(glsl.path))
		{
			return false;
		}

		std::unique_ptr<VertexShaderAssetData> data = std::make_unique<VertexShaderAssetData>(glsl);

		return Register(name, std::move(data));
	}

	bool VertexShaderAsset::Register(const AssetNameView name, const s3d::MSL& msl)
	{
		if ((msl.path) && (not detail::CheckFileExists(msl.path)))
		{
			return false;
		}

		std::unique_ptr<VertexShaderAssetData> data = std::make_unique<VertexShaderAssetData>(msl);

		return Register(name, std::move(data));
	}

	bool VertexShaderAsset::Register(const AssetNameView name, const s3d::ESSL& essl)
	{
		if (not detail::CheckFileExists(essl.path))
		{
			return false;
		}

		std::unique_ptr<VertexShaderAssetData> data = std::make_unique<VertexShaderAssetData>(essl);

		return Register(name, std::move(data));
	}

	bool VertexShaderAsset::Register(const AssetNameView name, const s3d::WGSL& wgsl)
	{
		if (not detail::CheckFileExists(wgsl.path))
		{
			return false;
		}

		std::unique_ptr<VertexShaderAssetData> data = std::make_unique<VertexShaderAssetData>(wgsl);

		return Register(name, std::move(data));
	}

	bool VertexShaderAsset::Register(const AssetNameView name, const ShaderGroup& shaderGroup)
	{
		std::unique_ptr<VertexShaderAssetData> data = std::make_unique<VertexShaderAssetData>(shaderGroup);

		return Register(name, std::move(data));
	}

	bool VertexShaderAsset::Register(const AssetNameView name, std::unique_ptr<VertexShaderAssetData>&& data)
	{
		return SIV3D_ENGINE(Asset)->registerAsset(AssetType::VertexShader, name, std::move(data));
	}


	bool VertexShaderAsset::Register(const AssetNameAndTags& nameAndTags, const FilePathView path, const StringView entryPoint, const Array<ConstantBufferBinding>& bindings)
	{
		if (not detail::CheckFileExists(path))
		{
			return false;
		}

		std::unique_ptr<VertexShaderAssetData> data = std::make_unique<VertexShaderAssetData>(path, entryPoint, bindings, nameAndTags.tags);

		return Register(nameAndTags.name, std::move(data));
	}

	bool VertexShaderAsset::Register(const AssetNameAndTags& nameAndTags, const s3d::HLSL& hlsl)
	{
		if (not detail::CheckFileExists(hlsl.path))
		{
			return false;
		}

		std::unique_ptr<VertexShaderAssetData> data = std::make_unique<VertexShaderAssetData>(hlsl, nameAndTags.tags);

		return Register(nameAndTags.name, std::move(data));
	}

	bool VertexShaderAsset::Register(const AssetNameAndTags& nameAndTags, const s3d::GLSL& glsl)
	{
		if (not detail::CheckFileExists(glsl.path))
		{
			return false;
		}

		std::unique_ptr<VertexShaderAssetData> data = std::make_unique<VertexShaderAssetData>(glsl, nameAndTags.tags);

		return Register(nameAndTags.name, std::move(data));
	}

	bool VertexShaderAsset::Register(const AssetNameAndTags& nameAndTags, const s3d::MSL& msl)
	{
		if ((msl.path) && (not detail::CheckFileExists(msl.path)))
		{
			return false;
		}

		std::unique_ptr<VertexShaderAssetData> data = std::make_unique<VertexShaderAssetData>(msl, nameAndTags.tags);

		return Register(nameAndTags.name, std::move(data));
	}

	bool VertexShaderAsset::Register(const AssetNameAndTags& nameAndTags, const s3d::ESSL& essl)
	{
		if (not detail::CheckFileExists(essl.path))
		{
			return false;
		}

		std::unique_ptr<VertexShaderAssetData> data = std::make_unique<VertexShaderAssetData>(essl, nameAndTags.tags);

		return Register(nameAndTags.name, std::move(data));
	}

	bool VertexShaderAsset::Register(const AssetNameAndTags& nameAndTags, const s3d::WGSL& wgsl)
	{
		if (not detail::CheckFileExists(wgsl.path))
		{
			return false;
		}

		std::unique_ptr<VertexShaderAssetData> data = std::make_unique<VertexShaderAssetData>(wgsl, nameAndTags.tags);

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
