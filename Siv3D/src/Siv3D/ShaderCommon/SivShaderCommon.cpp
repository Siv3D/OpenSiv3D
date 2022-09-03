﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/ShaderCommon.hpp>
# include <Siv3D/VertexShader.hpp>
# include <Siv3D/PixelShader.hpp>
# include <Siv3D/System.hpp>

namespace s3d
{
	HLSL::HLSL(FilePath _path)
		: path{ std::move(_path) } {}

	HLSL::HLSL(FilePath _path, String _entryPoint)
		: path{ std::move(_path) }
		, entryPoint{ std::move(_entryPoint) } {}

	ShaderGroup HLSL::operator |(const GLSL& glsl) const
	{
		return ShaderGroup{ *this, glsl, none, none, none };
	}

	ShaderGroup HLSL::operator |(const MSL& msl) const
	{
		return ShaderGroup{ *this, none, msl, none, none };
	}

	ShaderGroup HLSL::operator |(const ESSL& essl) const
	{
		return ShaderGroup{ *this, none, none, essl, none };
	}

	ShaderGroup HLSL::operator |(const WGSL& wgsl) const
	{
		return ShaderGroup{ *this, none, none, none, wgsl };
	}

	HLSL::operator VertexShader() const
	{
		if (entryPoint)
		{
			return VertexShader::HLSL(path, entryPoint);
		}
		else
		{
			return VertexShader::HLSL(path);
		}
	}

	HLSL::operator PixelShader() const
	{
		if (entryPoint)
		{
			return PixelShader::HLSL(path, entryPoint);
		}
		else
		{
			return PixelShader::HLSL(path);
		}
	}

	GLSL::GLSL(FilePath _path, Array<ConstantBufferBinding> _bindings)
		: path{ std::move(_path) }
		, bindings{ std::move(_bindings) } {}

	ShaderGroup GLSL::operator |(const HLSL& hlsl) const
	{
		return ShaderGroup{ hlsl, *this, none, none, none };
	}

	ShaderGroup GLSL::operator |(const MSL& msl) const
	{
		return ShaderGroup{ none, *this, msl, none, none };
	}

	ShaderGroup GLSL::operator |(const ESSL& essl) const
	{
		return ShaderGroup{ none, *this, none, essl, none };
	}

	ShaderGroup GLSL::operator |(const WGSL& wgsl) const
	{
		return ShaderGroup{ none, *this, none, none, wgsl };
	}

	GLSL::operator VertexShader() const
	{
		return VertexShader::GLSL(path, bindings);
	}

	GLSL::operator PixelShader() const
	{
		return PixelShader::GLSL(path, bindings);
	}

	MSL::MSL(String _entryPoint)
		: entryPoint{ std::move(_entryPoint) } {}

	MSL::MSL(FilePath _path, String _entryPoint)
		: path{ std::move(_path) }
		, entryPoint{ std::move(_entryPoint) } {}

	ShaderGroup MSL::operator |(const HLSL& hlsl) const
	{
		return ShaderGroup{ hlsl, none, *this, none, none };
	}

	ShaderGroup MSL::operator |(const GLSL& glsl) const
	{
		return ShaderGroup{ none, glsl, *this, none, none };
	}

	ShaderGroup MSL::operator |(const ESSL& essl) const
	{
		return ShaderGroup{ none, none, *this, essl, none };
	}

	ShaderGroup MSL::operator |(const WGSL& wgsl) const
	{
		return ShaderGroup{ none, none, *this, none, wgsl };
	}

	MSL::operator VertexShader() const
	{
		if (path)
		{
			return VertexShader::MSL(entryPoint, path);
		}
		else
		{
			return VertexShader::MSL(entryPoint);
		}
	}

	MSL::operator PixelShader() const
	{
		if (path)
		{
			return PixelShader::MSL(entryPoint, path);
		}
		else
		{
			return PixelShader::MSL(entryPoint);
		}
	}

	ESSL::ESSL(FilePath _path, Array<ConstantBufferBinding> _bindings)
		: path{ std::move(_path) }
		, bindings{ std::move(_bindings) } {}

	ShaderGroup ESSL::operator |(const HLSL& hlsl) const
	{
		return ShaderGroup{ hlsl, none, none, *this, none };
	}

	ShaderGroup ESSL::operator |(const GLSL& glsl) const
	{
		return ShaderGroup{ none, glsl, none, *this, none };
	}

	ShaderGroup ESSL::operator |(const MSL& msl) const
	{
		return ShaderGroup{ none, none, msl, *this, none };
	}

	ShaderGroup ESSL::operator |(const WGSL& wgsl) const
	{
		return ShaderGroup{ none, none, none, *this, wgsl };
	}

	ESSL::operator VertexShader() const
	{
		return VertexShader::ESSL(path, bindings);
	}

	ESSL::operator PixelShader() const
	{
		return PixelShader::ESSL(path, bindings);
	}

	WGSL::WGSL(FilePath _path, Array<ConstantBufferBinding> _bindings)
		: path{ std::move(_path) }
		, bindings{ std::move(_bindings) } {}

	ShaderGroup WGSL::operator |(const HLSL& hlsl) const
	{
		return ShaderGroup{ hlsl, none, none, none, *this };
	}

	ShaderGroup WGSL::operator |(const GLSL& glsl) const
	{
		return ShaderGroup{ none, glsl, none, none, *this };
	}

	ShaderGroup WGSL::operator |(const MSL& msl) const
	{
		return ShaderGroup{ none, none, msl, none, *this };
	}

	ShaderGroup WGSL::operator |(const ESSL& essl) const
	{
		return ShaderGroup{ none, none, none, essl, *this };
	}

	WGSL::operator VertexShader() const
	{
		return VertexShader::WGSL(path, bindings);
	}

	WGSL::operator PixelShader() const
	{
		return PixelShader::WGSL(path, bindings);
	}

	ShaderGroup::ShaderGroup(const Optional<HLSL>& hlsl, const Optional<GLSL>& glsl, const Optional<MSL>& msl, const Optional<ESSL>& essl, const Optional<WGSL>& wgsl)
		: m_hlsl{ hlsl }
		, m_glsl{ glsl }
		, m_msl{ msl }
		, m_essl{ essl }
		, m_wgsl{ wgsl } {}

	ShaderGroup ShaderGroup::operator |(const HLSL& hlsl) const
	{
		return ShaderGroup{ hlsl, m_glsl, m_msl, m_essl, m_wgsl };
	}

	ShaderGroup ShaderGroup::operator |(const GLSL& glsl) const
	{
		return ShaderGroup{ m_hlsl, glsl, m_msl, m_essl, m_wgsl };
	}

	ShaderGroup ShaderGroup::operator |(const MSL& msl) const
	{
		return ShaderGroup{ m_hlsl, m_glsl, msl, m_essl, m_wgsl };
	}

	ShaderGroup ShaderGroup::operator |(const ESSL& essl) const
	{
		return ShaderGroup{ m_hlsl, m_glsl, m_msl, essl, m_wgsl };
	}

	ShaderGroup ShaderGroup::operator |(const WGSL& wgsl) const
	{
		return ShaderGroup{ m_hlsl, m_glsl, m_msl, m_essl, wgsl };
	}

	ShaderGroup::operator VertexShader() const
	{
		if (const auto renderer = System::GetRendererType();
			renderer == EngineOption::Renderer::Direct3D11)
		{
			assert(m_hlsl);
			return *m_hlsl;
		}
		else if (renderer == EngineOption::Renderer::OpenGL)
		{
			assert(m_glsl);
			return *m_glsl;
		}
		else if (renderer == EngineOption::Renderer::Metal)
		{
			assert(m_msl);
			return *m_msl;
		}
		else if (renderer == EngineOption::Renderer::WebGL2)
		{
			assert(m_essl);
			return *m_essl;
		}
		else if (renderer == EngineOption::Renderer::WebGPU)
		{
			assert(m_wgsl);
			return *m_wgsl;
		}

		return{};
	}

	ShaderGroup::operator PixelShader() const
	{
		if (const auto renderer = System::GetRendererType();
			renderer == EngineOption::Renderer::Direct3D11)
		{
			assert(m_hlsl);
			return *m_hlsl;
		}
		else if (renderer == EngineOption::Renderer::OpenGL)
		{
			assert(m_glsl);
			return *m_glsl;
		}
		else if (renderer == EngineOption::Renderer::Metal)
		{
			assert(m_msl);
			return *m_msl;
		}
		else if (renderer == EngineOption::Renderer::WebGL2)
		{
			assert(m_essl);
			return *m_essl;
		}
		else if (renderer == EngineOption::Renderer::WebGPU)
		{
			assert(m_wgsl);
			return *m_wgsl;
		}

		return{};
	}

	std::tuple<FilePath, String, Array<ConstantBufferBinding>> ShaderGroup::getParameters() const
	{
		if (const auto renderer = System::GetRendererType();
			renderer == EngineOption::Renderer::Direct3D11)
		{
			assert(m_hlsl);
			return{ m_hlsl->path, m_hlsl->entryPoint, {} };
		}
		else if (renderer == EngineOption::Renderer::OpenGL)
		{
			assert(m_glsl);
			return{ m_glsl->path, {}, m_glsl->bindings };
		}
		else if (renderer == EngineOption::Renderer::Metal)
		{
			assert(m_msl);
			return{ m_msl->path, m_msl->entryPoint, {} };
		}
		else if (renderer == EngineOption::Renderer::WebGL2)
		{
			assert(m_essl);
			return{ m_essl->path, {}, m_essl->bindings };
		}
		else if (renderer == EngineOption::Renderer::WebGPU)
		{
			assert(m_wgsl);
			return{ m_wgsl->path, {}, m_wgsl->bindings };
		}

		return{};
	}
}
