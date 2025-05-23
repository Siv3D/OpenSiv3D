﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2025 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Common/OpenGL.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/ColorHSV.hpp>

namespace s3d
{
	class GL4InternalTexture2D
	{
	private:

		// [フレームバッファ]
		GLuint m_frameBuffer = 0;
		
		// [メインテクスチャ]
		GLuint m_texture = 0;

		Size m_size = Size{ 0, 0 };

		uint32 m_sampleCount = 1;

	public:

		GL4InternalTexture2D() = default;

		~GL4InternalTexture2D();

		[[nodiscard]]
		bool isEmpty() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		[[nodiscard]]
		const Size& size() const noexcept;

		void clear(ColorF color);

		[[nodiscard]]
		GLuint getFrameBuffer() const noexcept;

		[[nodiscard]]
		GLuint getTexture() const noexcept;

		[[nodiscard]]
		static std::unique_ptr<GL4InternalTexture2D> CreateRenderTargetTexture2D(Size size, uint32 sampleCount = 1);
	};
}
