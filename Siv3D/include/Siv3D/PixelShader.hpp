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
# include "AssetHandle.hpp"
# include "Array.hpp"
# include "ConstantBufferBinding.hpp"
# include "Blob.hpp"

namespace s3d
{
	/// @brief ピクセルシェーダ
	class PixelShader : public AssetHandle<PixelShader>
	{
	public:

		SIV3D_NODISCARD_CXX20
		PixelShader();

		virtual ~PixelShader();

		[[nodiscard]]
		const Blob& getBinary() const noexcept;

		void swap(PixelShader& other) noexcept;

		[[nodiscard]]
		static PixelShader HLSL(FilePathView path, StringView entryPoint = U"PS");

		[[nodiscard]]
		static PixelShader GLSL(FilePathView path, const Array<ConstantBufferBinding>& bindings);

		[[nodiscard]]
		static PixelShader MSL(StringView entryPoint, FilePathView path = {});

		[[nodiscard]]
		static PixelShader ESSL(FilePathView path, const Array<ConstantBufferBinding>& bindings);

		[[nodiscard]]
		static PixelShader WGSL(FilePathView path, const Array<ConstantBufferBinding>& bindings);
	
	private:

		SIV3D_NODISCARD_CXX20
		PixelShader(FilePathView path, StringView entryPoint, const Array<ConstantBufferBinding>& bindings);
	};
}

template <>
inline void std::swap(s3d::PixelShader& a, s3d::PixelShader& b) noexcept;

# include "detail/PixelShader.ipp"
