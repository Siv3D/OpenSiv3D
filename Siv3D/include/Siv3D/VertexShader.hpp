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
	/// @brief 頂点シェーダ
	class VertexShader : public AssetHandle<VertexShader>
	{
	public:

		SIV3D_NODISCARD_CXX20
		VertexShader();

		SIV3D_NODISCARD_CXX20
		VertexShader(FilePathView path, StringView entryPoint, const Array<ConstantBufferBinding>& bindings);

		//virtual ~VertexShader();

		[[nodiscard]]
		const Blob& getBinary() const noexcept;

		[[nodiscard]]
		static VertexShader HLSL(FilePathView path, StringView entryPoint = U"VS");

		[[nodiscard]]
		static VertexShader GLSL(FilePathView path, const Array<ConstantBufferBinding>& bindings);

		[[nodiscard]]
		static VertexShader MSL(StringView entryPoint, FilePathView path = {});
	};
}

# include "detail/VertexShader.ipp"
