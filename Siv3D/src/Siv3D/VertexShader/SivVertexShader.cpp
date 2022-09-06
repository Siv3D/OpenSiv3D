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

# include <Siv3D/VertexShader.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Error.hpp>
# include <Siv3D/System.hpp>
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

	VertexShader::VertexShader() {}

	VertexShader::VertexShader(const FilePathView path, const StringView entryPoint, const Array<ConstantBufferBinding>& bindings)
		: AssetHandle{ std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Shader)->createVSFromFile(path, entryPoint, bindings)) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	VertexShader::~VertexShader() {}

	const Blob& VertexShader::getBinary() const noexcept
	{
		return SIV3D_ENGINE(Shader)->getBinaryVS(m_handle->id());
	}

	void VertexShader::swap(VertexShader& other) noexcept
	{
		m_handle.swap(other.m_handle);
	}

	VertexShader VertexShader::HLSL(const FilePathView path, const StringView entryPoint)
	{
		if (System::GetRendererType() != EngineOption::Renderer::Direct3D11)
		{
			throw Error{ U"HLSL must be used with EngineOption::Renderer::Direct3D11" };
		}

		return VertexShader{ path, entryPoint, {} };
	}

	VertexShader VertexShader::GLSL(const FilePathView path, const Array<ConstantBufferBinding>& bindings)
	{
		if (System::GetRendererType() != EngineOption::Renderer::OpenGL)
		{
			throw Error{ U"GLSL must be used with EngineOption::Renderer::OpenGL" };
		}

		return VertexShader{ path, {}, bindings };
	}

	VertexShader VertexShader::MSL(const StringView entryPoint, const FilePathView path)
	{
		if (System::GetRendererType() != EngineOption::Renderer::Metal)
		{
			throw Error{ U"MSL must be used with EngineOption::Renderer::Metal" };
		}

		return VertexShader{ path, entryPoint, {} };
	}

	VertexShader VertexShader::ESSL(const FilePathView path, const Array<ConstantBufferBinding>& bindings)
	{
		if (System::GetRendererType() != EngineOption::Renderer::WebGL2)
		{
			throw Error{ U"ESSL must be used with EngineOption::Renderer::WebGL2" };
		}

		return VertexShader{ path, {}, bindings };
	}

	VertexShader VertexShader::WGSL(const FilePathView path, const Array<ConstantBufferBinding>& bindings)
	{
		if (System::GetRendererType() != EngineOption::Renderer::WebGPU)
		{
			throw Error{ U"WGSL must be used with EngineOption::Renderer::WebGPU" };
		}

		return VertexShader{ path, {}, bindings };
	}
}
