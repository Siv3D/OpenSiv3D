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

# include <Siv3D/AudioAssetData.hpp>

namespace s3d
{
	AudioAssetData::AudioAssetData() {}

	//AudioAssetData::AudioAssetData(const FilePathView _path, const StringView _entryPoint, const Array<ConstantBufferBinding>& _bindings, const Array<AssetTag>& tags)
	//	: IAsset{ tags }
	//	, path{ _path }
	//	, entryPoint{ _entryPoint }
	//	, bindings{ _bindings } {}

	//AudioAssetData::AudioAssetData(const HLSL& hlsl, const Array<AssetTag>& tags)
	//	: IAsset{ tags }
	//	, path{ hlsl.path }
	//	, entryPoint{ hlsl.entryPoint } {}

	//AudioAssetData::AudioAssetData(const GLSL& glsl, const Array<AssetTag>& tags)
	//	: IAsset{ tags }
	//	, path{ glsl.path }
	//	, bindings{ glsl.bindings } {}

	//AudioAssetData::AudioAssetData(const MSL& msl, const Array<AssetTag>& tags)
	//	: IAsset{ tags }
	//	, path{ msl.path }
	//	, entryPoint{ msl.entryPoint } {}

	//AudioAssetData::AudioAssetData(const ESSL& essl, const Array<AssetTag>& tags)
	//	: IAsset{ tags }
	//	, path{ essl.path }
	//	, bindings{ essl.bindings } {}

	//AudioAssetData::AudioAssetData(const ShaderGroup& shaderGroup, const Array<AssetTag>& tags)
	//	: IAsset{ tags }
	//{
	//	std::tie(path, entryPoint, bindings) = shaderGroup.getParameters();
	//}

	bool AudioAssetData::load(const String& hint)
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

	void AudioAssetData::loadAsync(const String& hint)
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

	void AudioAssetData::wait()
	{
		if (m_task.isValid())
		{
			m_task.get();
		}
	}

	void AudioAssetData::release()
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

	//bool AudioAssetData::DefaultLoad(AudioAssetData& asset, const String&)
	//{
	//	if (asset.ps)
	//	{
	//		return true;
	//	}

	//	if (const auto renderer = System::GetRendererType();
	//		renderer == EngineOption::Renderer::Direct3D11)
	//	{
	//		asset.ps = HLSL{ asset.path, asset.entryPoint };
	//	}
	//	else if (renderer == EngineOption::Renderer::OpenGL)
	//	{
	//		asset.ps = GLSL{ asset.path, asset.bindings };
	//	}
	//	else if (renderer == EngineOption::Renderer::Metal)
	//	{
	//		asset.ps = MSL{ asset.path, asset.entryPoint };
	//	}
	//	else if (renderer == EngineOption::Renderer::WebGL2)
	//	{
	//		asset.ps = ESSL{ asset.path, asset.bindings };
	//	}

	//	if (not asset.ps)
	//	{
	//		return false;
	//	}

	//	return true;
	//}

	void AudioAssetData::DefaultRelease(AudioAssetData& asset)
	{
		asset.audio.release();
	}
}
