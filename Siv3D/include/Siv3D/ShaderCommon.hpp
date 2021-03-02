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

# pragma once
# include "Common.hpp"
# include "Optional.hpp"
# include "VertexShader.hpp"
# include "PixelShader.hpp"
# include "System.hpp"

namespace s3d
{
	class ShaderGroup;
	struct HLSL;
	struct GLSL;
	struct MSL;
	struct ESSL;

	/// @brief HLSL ファイル
	struct HLSL
	{
		FilePath path;

		String entryPoint;

		SIV3D_NODISCARD_CXX20
		explicit HLSL(FilePath _path);

		SIV3D_NODISCARD_CXX20
		HLSL(FilePath _path, String _entryPoint);

		[[nodiscard]]
		ShaderGroup operator |(const GLSL& glsl) const;

		[[nodiscard]]
		ShaderGroup operator |(const MSL& msl) const;

		[[nodiscard]]
		ShaderGroup operator |(const ESSL& essl) const;

		[[nodiscard]]
		operator VertexShader() const;

		[[nodiscard]]
		operator PixelShader() const;
	};

	/// @brief GLSL ファイル
	struct GLSL
	{
		FilePath path;

		Array<ConstantBufferBinding> bindings;

		SIV3D_NODISCARD_CXX20
		GLSL(FilePath _path, Array<ConstantBufferBinding> _bindings);

		[[nodiscard]]
		ShaderGroup operator |(const HLSL& hlsl) const;

		[[nodiscard]]
		ShaderGroup operator |(const MSL& msl) const;

		[[nodiscard]]
		ShaderGroup operator |(const ESSL& essl) const;

		[[nodiscard]]
		operator VertexShader() const;

		[[nodiscard]]
		operator PixelShader() const;
	};

	/// @brief Metal Shading Language ファイル
	struct MSL
	{
		FilePath path;

		String entryPoint;

		SIV3D_NODISCARD_CXX20
		explicit MSL(StringView _entryPoint);

		SIV3D_NODISCARD_CXX20
		MSL(FilePath _path, StringView _entryPoint);

		[[nodiscard]]
		ShaderGroup operator |(const HLSL& hlsl) const;

		[[nodiscard]]
		ShaderGroup operator |(const GLSL& glsl) const;

		[[nodiscard]]
		ShaderGroup operator |(const ESSL& essl) const;

		[[nodiscard]]
		operator VertexShader() const;

		[[nodiscard]]
		operator PixelShader() const;
	};

	/// @brief OpenGL ES Shading Language ファイル
	struct ESSL
	{
		FilePath path;

		Array<ConstantBufferBinding> bindings;

		SIV3D_NODISCARD_CXX20
		ESSL(FilePath _path, Array<ConstantBufferBinding> _bindings);

		[[nodiscard]]
		ShaderGroup operator |(const HLSL& hlsl) const;

		[[nodiscard]]
		ShaderGroup operator |(const GLSL& hlsl) const;

		[[nodiscard]]
		ShaderGroup operator |(const MSL& msl) const;

		[[nodiscard]]
		operator VertexShader() const;

		[[nodiscard]]
		operator PixelShader() const;
	};

	class ShaderGroup
	{
	public:

		SIV3D_NODISCARD_CXX20
		ShaderGroup() = default;

		SIV3D_NODISCARD_CXX20
		ShaderGroup(const Optional<HLSL>& hlsl, const Optional<GLSL>& glsl, const Optional<MSL>& msl, const Optional<ESSL>& essl);

		[[nodiscard]]
		ShaderGroup operator |(const HLSL& hlsl) const;

		[[nodiscard]]
		ShaderGroup operator |(const GLSL& glsl) const;

		[[nodiscard]]
		ShaderGroup operator |(const MSL& msl) const;

		[[nodiscard]]
		ShaderGroup operator |(const ESSL& essl) const;

		[[nodiscard]]
		operator VertexShader() const;

		[[nodiscard]]
		operator PixelShader() const;

	private:

		Optional<HLSL> m_hlsl;
		Optional<GLSL> m_glsl;
		Optional<MSL>  m_msl;
		Optional<ESSL> m_essl;
	};
}

# include "detail/ShaderCommon.ipp"
