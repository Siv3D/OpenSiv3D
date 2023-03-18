//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Common/OpenGL.hpp>
# include <Siv3D/Blob.hpp>
# include <Siv3D/ConstantBufferBinding.hpp>

namespace s3d
{
	class GLES3PixelShader
	{
	private:

		Blob m_binary;

		GLuint m_pixelShader = 0;

		Array<ConstantBufferBinding> m_constantBufferBindings;
		Array<std::pair<uint32, GLint>> m_textureIndices;

		bool m_initialized = false;

		void setUniformBlockBinding(const String& name, GLuint index);

		void setUniformBlockBindings(const Array<ConstantBufferBinding>& bindings);

	public:

		struct Null {};

		GLES3PixelShader() = default;

		explicit GLES3PixelShader(Null);

		explicit GLES3PixelShader(const StringView source, const Array<ConstantBufferBinding>& bindings);

		~GLES3PixelShader();

		bool isInitialized() const noexcept;

		const Blob& getBinary() const noexcept;

		GLint getShader() const;

		void bindUniformBlocks(GLuint program);

		void setPSSamplerUniforms();
	};
}
