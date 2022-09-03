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

# include <Siv3D/PixelShaderAssetData.hpp>
# include <Siv3D/System.hpp>

namespace s3d
{
	PixelShaderAssetData::PixelShaderAssetData() {}

	PixelShaderAssetData::PixelShaderAssetData(const FilePathView _path, const StringView _entryPoint, const Array<ConstantBufferBinding>& _bindings, const Array<AssetTag>& tags)
		: IAsset{ tags }
		, path{ _path }
		, entryPoint{ _entryPoint }
		, bindings{ _bindings } {}

	PixelShaderAssetData::PixelShaderAssetData(const HLSL& hlsl, const Array<AssetTag>& tags)
		: IAsset{ tags }
		, path{ hlsl.path }
		, entryPoint{ hlsl.entryPoint } {}

	PixelShaderAssetData::PixelShaderAssetData(const GLSL& glsl, const Array<AssetTag>& tags)
		: IAsset{ tags }
		, path{ glsl.path }
		, bindings{ glsl.bindings } {}

	PixelShaderAssetData::PixelShaderAssetData(const MSL& msl, const Array<AssetTag>& tags)
		: IAsset{ tags }
		, path{ msl.path }
		, entryPoint{ msl.entryPoint } {}

	PixelShaderAssetData::PixelShaderAssetData(const ESSL& essl, const Array<AssetTag>& tags)
		: IAsset{ tags }
		, path{ essl.path }
		, bindings{ essl.bindings } {}

	PixelShaderAssetData::PixelShaderAssetData(const WGSL& wgsl, const Array<AssetTag>& tags)
		: IAsset{ tags }
		, path{ wgsl.path }
		, bindings{ wgsl.bindings } {}

	PixelShaderAssetData::PixelShaderAssetData(const ShaderGroup& shaderGroup, const Array<AssetTag>& tags)
		: IAsset{ tags }
	{
		std::tie(path, entryPoint, bindings) = shaderGroup.getParameters();
	}

	bool PixelShaderAssetData::load(const String& hint)
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

	void PixelShaderAssetData::loadAsync(const String& hint)
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

	void PixelShaderAssetData::wait()
	{
		if (m_task.isValid())
		{
			m_task.get();
		}
	}

	void PixelShaderAssetData::release()
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

	bool PixelShaderAssetData::DefaultLoad(PixelShaderAssetData& asset, const String&)
	{
		if (asset.ps)
		{
			return true;
		}

		if (const auto renderer = System::GetRendererType();
			renderer == EngineOption::Renderer::Direct3D11)
		{
			asset.ps = HLSL{ asset.path, asset.entryPoint };
		}
		else if (renderer == EngineOption::Renderer::OpenGL)
		{
			asset.ps = GLSL{ asset.path, asset.bindings };
		}
		else if (renderer == EngineOption::Renderer::Metal)
		{
			asset.ps = MSL{ asset.path, asset.entryPoint };
		}
		else if (renderer == EngineOption::Renderer::WebGL2)
		{
			asset.ps = ESSL{ asset.path, asset.bindings };
		}
		else if (renderer == EngineOption::Renderer::WebGPU)
		{
			asset.ps = WGSL{ asset.path, asset.bindings };
		}

		if (not asset.ps)
		{
			return false;
		}

		return true;
	}

	void PixelShaderAssetData::DefaultRelease(PixelShaderAssetData& asset)
	{
		asset.ps.release();
	}
}
