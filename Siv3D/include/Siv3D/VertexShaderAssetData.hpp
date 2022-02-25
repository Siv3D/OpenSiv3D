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
# include "VertexShader.hpp"
# include "AsyncTask.hpp"

namespace s3d
{
	struct VertexShaderAssetData : IAsset
	{
		FilePath path;
		
		String entryPoint;
		
		Array<ConstantBufferBinding> bindings;

		VertexShader vs;

		std::function<bool(VertexShaderAssetData&, const String&)> onLoad = DefaultLoad;

		std::function<void(VertexShaderAssetData&)> onRelease = DefaultRelease;

		SIV3D_NODISCARD_CXX20
		VertexShaderAssetData();

		SIV3D_NODISCARD_CXX20
		VertexShaderAssetData(FilePathView path, StringView entryPoint, const Array<ConstantBufferBinding>& bindings, const Array<AssetTag>& tags = {});

		SIV3D_NODISCARD_CXX20
		explicit VertexShaderAssetData(const HLSL& hlsl, const Array<AssetTag>& tags = {});

		SIV3D_NODISCARD_CXX20
		explicit VertexShaderAssetData(const GLSL& glsl, const Array<AssetTag>& tags = {});

		SIV3D_NODISCARD_CXX20
		explicit VertexShaderAssetData(const MSL& msl, const Array<AssetTag>& tags = {});

		SIV3D_NODISCARD_CXX20
		explicit VertexShaderAssetData(const ESSL& essl, const Array<AssetTag>& tags = {});

		SIV3D_NODISCARD_CXX20
		explicit VertexShaderAssetData(const WGSL& wgsl, const Array<AssetTag>& tags = {});

		SIV3D_NODISCARD_CXX20
		explicit VertexShaderAssetData(const ShaderGroup& shaderGroup, const Array<AssetTag>& tags = {});

		bool load(const String& hint) override;

		void loadAsync(const String& hint) override;

		void wait() override;

		void release() override;

		static bool DefaultLoad(VertexShaderAssetData& asset, const String& hint);

		static void DefaultRelease(VertexShaderAssetData& asset);

	private:

		AsyncTask<void> m_task;
	};
}
