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

# include <Siv3D/PixelShader.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/FreestandingMessageBox/FreestandingMessageBox.hpp>
# include <Siv3D/Shader/IShader.hpp>
# include <Siv3D/AssetMonitor/IAssetMonitor.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	template <>
	AssetIDWrapper<AssetHandle<PixelShader>>::AssetIDWrapper()
	{
		if (not Siv3DEngine::isActive())
		{
			FreestandingMessageBox::ShowError(U"`PixelShader` must be initialized after engine-setup. Please fix the C++ code.");
			std::abort();
		}
	}

	template <>
	AssetIDWrapper<AssetHandle<PixelShader>>::~AssetIDWrapper()
	{
		if (not Siv3DEngine::isActive())
		{
			return;
		}

		if (auto p = SIV3D_ENGINE(Shader))
		{
			p->releasePS(m_id);
		}
	}

	PixelShader::PixelShader()
	{
		// do nothing
	}

	PixelShader::PixelShader(const FilePathView path, const StringView entryPoint, const Array<ConstantBufferBinding>& bindings)
		: AssetHandle{ std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Shader)->createPSFromFile(path, entryPoint, bindings)) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	const Blob& PixelShader::getBinary() const noexcept
	{
		return SIV3D_ENGINE(Shader)->getBinaryPS(m_handle->id());
	}

	PixelShader PixelShader::HLSL(const FilePathView path, const StringView entryPoint)
	{
		return PixelShader{ path, entryPoint, {} };
	}

	PixelShader PixelShader::GLSL(const FilePathView path, const Array<ConstantBufferBinding>& bindings)
	{
		return PixelShader{ path, {}, bindings };
	}

	PixelShader PixelShader::MSL(const StringView entryPoint, const FilePathView path)
	{
		return PixelShader{ path, entryPoint, {} };
	}

	PixelShader PixelShader::ESSL(const FilePathView path, const Array<ConstantBufferBinding>& bindings)
	{
		return PixelShader{ path, {}, bindings };
	}
}
