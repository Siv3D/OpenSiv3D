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

# include <Siv3D/VertexShader.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/FreestandingMessageBox/FreestandingMessageBox.hpp>
# include <Siv3D/Shader/IShader.hpp>
# include <Siv3D/AssetMonitor/IAssetMonitor.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	template <>
	AssetIDWrapper<AssetHandle<VertexShader>>::AssetIDWrapper()
	{
		if (not Siv3DEngine::isActive())
		{
			FreestandingMessageBox::ShowError(U"`VertexShader` must be initialized after engine-setup. Please fix the C++ code.");
			std::abort();
		}
	}

	template <>
	AssetIDWrapper<AssetHandle<VertexShader>>::~AssetIDWrapper()
	{
		if (not Siv3DEngine::isActive())
		{
			return;
		}

		if (auto p = SIV3D_ENGINE(Shader))
		{
			p->releaseVS(m_id);
		}
	}

	VertexShader::VertexShader()
	{
		// do nothing
	}

	VertexShader::VertexShader(const FilePathView path, const StringView entryPoint, const Array<ConstantBufferBinding>& bindings)
		: AssetHandle{ std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Shader)->createVSFromFile(path, entryPoint, bindings)) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	const Blob& VertexShader::getBinary() const noexcept
	{
		return SIV3D_ENGINE(Shader)->getBinaryVS(m_handle->id());
	}

	VertexShader VertexShader::HLSL(const FilePathView path, const StringView entryPoint)
	{
		return VertexShader{ path, entryPoint, {} };
	}

	VertexShader VertexShader::GLSL(const FilePathView path, const Array<ConstantBufferBinding>& bindings)
	{
		return VertexShader{ path, {}, bindings };
	}

	VertexShader VertexShader::MSL(const StringView entryPoint, const FilePathView path)
	{
		return VertexShader{ path, entryPoint, {} };
	}

	VertexShader VertexShader::ESSL(const FilePathView path, const Array<ConstantBufferBinding>& bindings)
	{
		return VertexShader{ path, {}, bindings };
	}
}
