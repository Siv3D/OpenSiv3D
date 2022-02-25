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
	/// @brief 頂点シェーダ
	class VertexShader : public AssetHandle<VertexShader>
	{
	public:

		SIV3D_NODISCARD_CXX20
		VertexShader();

		virtual ~VertexShader();

		[[nodiscard]]
		const Blob& getBinary() const noexcept;

		void swap(VertexShader& other) noexcept;

		[[nodiscard]]
		static VertexShader HLSL(FilePathView path, StringView entryPoint = U"VS");

		[[nodiscard]]
		static VertexShader GLSL(FilePathView path, const Array<ConstantBufferBinding>& bindings);

		[[nodiscard]]
		static VertexShader MSL(StringView entryPoint, FilePathView path = {});

		[[nodiscard]]
		static VertexShader ESSL(FilePathView path, const Array<ConstantBufferBinding>& bindings);

		[[nodiscard]]
		static VertexShader WGSL(FilePathView path, const Array<ConstantBufferBinding>& bindings);

	private:

		SIV3D_NODISCARD_CXX20
		VertexShader(FilePathView path, StringView entryPoint, const Array<ConstantBufferBinding>& bindings);
	};
}

template <>
inline void std::swap(s3d::VertexShader& a, s3d::VertexShader& b) noexcept;

# include "detail/VertexShader.ipp"
