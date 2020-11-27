//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	inline HLSL::HLSL(const FilePath _path)
		: path(_path) {}

	inline HLSL::HLSL(const FilePath _path, const String _entryPoint)
		: path(_path)
		, entryPoint(_entryPoint) {}

	inline ShaderGroup HLSL::operator |(const GLSL& glsl) const
	{
		return ShaderGroup{ *this, glsl, none };
	}

	inline ShaderGroup HLSL::operator |(const MSL& msl) const
	{
		return ShaderGroup{ *this, none, msl };
	}

	inline HLSL::operator VertexShader() const
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

	inline HLSL::operator PixelShader() const
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

	inline GLSL::GLSL(const FilePath _path, Array<ConstantBufferBinding> _bindings)
		: path(_path)
		, bindings(std::move(_bindings)) {}

	inline ShaderGroup GLSL::operator |(const HLSL& hlsl) const
	{
		return ShaderGroup{ hlsl, *this, none };
	}

	inline ShaderGroup GLSL::operator |(const MSL& msl) const
	{
		return ShaderGroup{ none, *this, msl };
	}

	inline GLSL::operator VertexShader() const
	{
		return VertexShader::GLSL(path, bindings);
	}

	inline GLSL::operator PixelShader() const
	{
		return PixelShader::GLSL(path, bindings);
	}

	inline MSL::MSL(StringView _entryPoint)
		: entryPoint(_entryPoint) {}

	inline MSL::MSL(FilePath _path, StringView _entryPoint)
		: path(_path)
		, entryPoint(_entryPoint) {}

	inline ShaderGroup MSL::operator |(const HLSL& hlsl) const
	{
		return ShaderGroup{ hlsl, none, *this };
	}

	inline ShaderGroup MSL::operator |(const GLSL& glsl) const
	{
		return ShaderGroup{ none, glsl, *this };
	}

	inline MSL::operator VertexShader() const
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

	inline MSL::operator PixelShader() const
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

	inline ESSL::ESSL(const FilePath _path, Array<ConstantBufferBinding> _bindings)
		: path(_path)
		, bindings(std::move(_bindings)) {}

	inline ShaderGroup ESSL::operator |(const HLSL& hlsl) const
	{
		return ShaderGroup{ hlsl, none, none };
	}

	inline ShaderGroup ESSL::operator |(const GLSL& glsl) const
	{
		return ShaderGroup{ none, glsl, none };
	}

	inline ShaderGroup ESSL::operator |(const MSL& msl) const
	{
		return ShaderGroup{ none, none, msl };
	}

	inline ESSL::operator VertexShader() const
	{
		return VertexShader::ESSL(path, bindings);
	}

	inline ESSL::operator PixelShader() const
	{
		return PixelShader::ESSL(path, bindings);
	}

	inline ShaderGroup::ShaderGroup(const Optional<HLSL>& hlsl, const Optional<GLSL>& glsl, const Optional<MSL>& msl)
		: m_hlsl(hlsl)
		, m_glsl(glsl)
		, m_msl(msl) {}

	inline ShaderGroup ShaderGroup::operator |(const HLSL& hlsl) const
	{
		return ShaderGroup{ hlsl, m_glsl, m_msl };
	}

	inline ShaderGroup ShaderGroup::operator |(const GLSL& glsl) const
	{
		return ShaderGroup{ m_hlsl, glsl, m_msl };
	}

	inline ShaderGroup ShaderGroup::operator |(const MSL& msl) const
	{
		return ShaderGroup{ m_hlsl, m_glsl, msl };
	}

	inline ShaderGroup::operator VertexShader() const
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

		return VertexShader{};
	}

	inline ShaderGroup::operator PixelShader() const
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

		return PixelShader{};
	}
}
