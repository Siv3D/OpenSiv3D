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

# include <Siv3D/VertexShaderAssetData.hpp>
# include <Siv3D/System.hpp>

namespace s3d
{
	VertexShaderAssetData::VertexShaderAssetData() {}

	VertexShaderAssetData::VertexShaderAssetData(const FilePathView _path, const StringView _entryPoint, const Array<ConstantBufferBinding>& _bindings, const Array<AssetTag>& tags)
		: IAsset{ tags }
		, path{ _path }
		, entryPoint{ _entryPoint }
		, bindings{ _bindings } {}

	VertexShaderAssetData::VertexShaderAssetData(const HLSL& hlsl, const Array<AssetTag>& tags)
		: IAsset{ tags }
		, path{ hlsl.path }
		, entryPoint{ hlsl.entryPoint } {}

	VertexShaderAssetData::VertexShaderAssetData(const GLSL& glsl, const Array<AssetTag>& tags)
		: IAsset{ tags }
		, path{ glsl.path }
		, bindings{ glsl.bindings } {}

	VertexShaderAssetData::VertexShaderAssetData(const MSL& msl, const Array<AssetTag>& tags)
		: IAsset{ tags }
		, path{ msl.path }
		, entryPoint{ msl.entryPoint } {}

	VertexShaderAssetData::VertexShaderAssetData(const ESSL& essl, const Array<AssetTag>& tags)
		: IAsset{ tags }
		, path{ essl.path }
		, bindings{ essl.bindings } {}

	VertexShaderAssetData::VertexShaderAssetData(const WGSL& wgsl, const Array<AssetTag>& tags)
		: IAsset{ tags }
		, path{ wgsl.path }
		, bindings{ wgsl.bindings } {}

	VertexShaderAssetData::VertexShaderAssetData(const ShaderGroup& shaderGroup, const Array<AssetTag>& tags)
		: IAsset{ tags }
	{
		std::tie(path, entryPoint, bindings) = shaderGroup.getParameters();
	}

	bool VertexShaderAssetData::load(const String& hint)
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

	void VertexShaderAssetData::loadAsync(const String& hint)
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

	void VertexShaderAssetData::wait()
	{
		if (m_task.isValid())
		{
			m_task.get();
		}
	}

	void VertexShaderAssetData::release()
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

	bool VertexShaderAssetData::DefaultLoad(VertexShaderAssetData& asset, const String&)
	{
		if (asset.vs)
		{
			return true;
		}

		if (const auto renderer = System::GetRendererType();
			renderer == EngineOption::Renderer::Direct3D11)
		{
			asset.vs = HLSL{ asset.path, asset.entryPoint };
		}
		else if (renderer == EngineOption::Renderer::OpenGL)
		{
			asset.vs = GLSL{ asset.path, asset.bindings };
		}
		else if (renderer == EngineOption::Renderer::Metal)
		{
			asset.vs = MSL{ asset.path, asset.entryPoint };
		}
		else if (renderer == EngineOption::Renderer::WebGL2)
		{
			asset.vs = ESSL{ asset.path, asset.bindings };
		}
		else if (renderer == EngineOption::Renderer::WebGPU)
		{
			asset.vs = WGSL{ asset.path, asset.bindings };
		}

		if (not asset.vs)
		{
			return false;
		}

		return true;
	}

	void VertexShaderAssetData::DefaultRelease(VertexShaderAssetData& asset)
	{
		asset.vs.release();
	}
}
