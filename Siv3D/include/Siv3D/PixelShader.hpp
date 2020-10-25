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
# include <memory>
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

		PixelShader();

		PixelShader(FilePathView path, StringView entryPoint, const Array<ConstantBufferBinding>& bindings);

		//virtual ~PixelShader();

		[[nodiscard]]
		const Blob& getBinary() const noexcept;

		static PixelShader HLSL(FilePathView path, StringView entryPoint = U"PS");

		static PixelShader GLSL(FilePathView path, const Array<ConstantBufferBinding>& bindings);

		static PixelShader MSL(StringView entryPoint, FilePathView path = {});
	};
}

# include "detail/PixelShader.ipp"

