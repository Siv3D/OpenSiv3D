//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "Asset.hpp"
# include "PixelShader.hpp"
# include "PixelShaderAssetData.hpp"
# include "HashTable.hpp"

namespace s3d
{
	class PixelShaderAsset : public PixelShader
	{
	public:

		SIV3D_NODISCARD_CXX20
		explicit PixelShaderAsset(AssetNameView name);

		static bool Register(AssetNameView name, FilePathView path, StringView entryPoint, const Array<ConstantBufferBinding>& bindings);

		static bool Register(AssetNameView name, const s3d::HLSL& hlsl);

		static bool Register(AssetNameView name, const s3d::GLSL& glsl);

		static bool Register(AssetNameView name, const s3d::MSL& msl);

		static bool Register(AssetNameView name, const s3d::ESSL& essl);

		static bool Register(AssetNameView name, const s3d::WGSL& wgsl);

		static bool Register(AssetNameView name, const ShaderGroup& shaderGroup);

		static bool Register(AssetNameView name, std::unique_ptr<PixelShaderAssetData>&& data);


		static bool Register(const AssetNameAndTags& nameAndTags, FilePathView path, StringView entryPoint, const Array<ConstantBufferBinding>& bindings);

		static bool Register(const AssetNameAndTags& nameAndTags, const s3d::HLSL& hlsl);

		static bool Register(const AssetNameAndTags& nameAndTags, const s3d::GLSL& glsl);

		static bool Register(const AssetNameAndTags& nameAndTags, const s3d::MSL& msl);

		static bool Register(const AssetNameAndTags& nameAndTags, const s3d::ESSL& essl);

		static bool Register(const AssetNameAndTags& nameAndTags, const s3d::WGSL& wgsl);

		static bool Register(const AssetNameAndTags& nameAndTags, const ShaderGroup& shaderGroup);


		[[nodiscard]]
		static bool IsRegistered(AssetNameView name);

		static bool Load(AssetNameView name);

		//static void LoadAsync(AssetNameView name);

		//static void Wait(AssetNameView name);

		[[nodiscard]]
		static bool IsReady(AssetNameView name);

		static void Release(AssetNameView name);

		static void ReleaseAll();

		static void Unregister(AssetNameView name);

		static void UnregisterAll();

		[[nodiscard]]
		static HashTable<AssetName, AssetInfo> Enumerate();
	};
}
