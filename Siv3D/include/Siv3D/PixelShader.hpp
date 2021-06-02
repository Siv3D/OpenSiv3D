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

		SIV3D_NODISCARD_CXX20
		PixelShader(FilePathView path, StringView entryPoint, const Array<ConstantBufferBinding>& bindings);

		//virtual ~PixelShader();

		[[nodiscard]]
		const Blob& getBinary() const noexcept;

		[[nodiscard]]
		static PixelShader HLSL(FilePathView path, StringView entryPoint = U"PS");

		[[nodiscard]]
		static PixelShader GLSL(FilePathView path, const Array<ConstantBufferBinding>& bindings);

		[[nodiscard]]
		static PixelShader MSL(StringView entryPoint, FilePathView path = {});

		[[nodiscard]]
		static PixelShader ESSL(FilePathView path, const Array<ConstantBufferBinding>& bindings);
	};
}
