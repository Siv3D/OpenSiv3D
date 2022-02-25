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
# include "ShaderCommon.hpp"
# include "PixelShader.hpp"
# include "AsyncTask.hpp"

namespace s3d
{
	struct PixelShaderAssetData : IAsset
	{
		FilePath path;

		String entryPoint;

		Array<ConstantBufferBinding> bindings;

		PixelShader ps;

		std::function<bool(PixelShaderAssetData&, const String&)> onLoad = DefaultLoad;

		std::function<void(PixelShaderAssetData&)> onRelease = DefaultRelease;

		SIV3D_NODISCARD_CXX20
		PixelShaderAssetData();

		SIV3D_NODISCARD_CXX20
		PixelShaderAssetData(FilePathView path, StringView entryPoint, const Array<ConstantBufferBinding>& bindings, const Array<AssetTag>& tags = {});

		SIV3D_NODISCARD_CXX20
		explicit PixelShaderAssetData(const HLSL& hlsl, const Array<AssetTag>& tags = {});

		SIV3D_NODISCARD_CXX20
		explicit PixelShaderAssetData(const GLSL& glsl, const Array<AssetTag>& tags = {});

		SIV3D_NODISCARD_CXX20
		explicit PixelShaderAssetData(const MSL& msl, const Array<AssetTag>& tags = {});

		SIV3D_NODISCARD_CXX20
		explicit PixelShaderAssetData(const ESSL& essl, const Array<AssetTag>& tags = {});

		SIV3D_NODISCARD_CXX20
		explicit PixelShaderAssetData(const WGSL& wgsl, const Array<AssetTag>& tags = {});

		SIV3D_NODISCARD_CXX20
		explicit PixelShaderAssetData(const ShaderGroup& shaderGroup, const Array<AssetTag>& tags = {});

		bool load(const String& hint) override;

		void loadAsync(const String& hint) override;

		void wait() override;

		void release() override;

		static bool DefaultLoad(PixelShaderAssetData& asset, const String& hint);

		static void DefaultRelease(PixelShaderAssetData& asset);

	private:

		AsyncTask<void> m_task;
	};
}
