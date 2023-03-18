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
	class GL4VertexShader
	{
	private:

		Blob m_binary;

		GLuint m_vsProgram = 0;

		Array<std::pair<uint32, GLint>> m_textureIndices;

		bool m_initialized = false;

		void setUniformBlockBinding(const StringView name, GLuint index);

		void setUniformBlockBindings(const Array<ConstantBufferBinding>& bindings);

	public:

		struct Null {};

		GL4VertexShader() = default;

		explicit GL4VertexShader(Null);

		explicit GL4VertexShader(const StringView source, const Array<ConstantBufferBinding>& bindings);

		~GL4VertexShader();

		bool isInitialized() const noexcept;

		const Blob& getBinary() const noexcept;

		GLint getProgram() const;

		void setVSSamplerUniform();
	};
}
