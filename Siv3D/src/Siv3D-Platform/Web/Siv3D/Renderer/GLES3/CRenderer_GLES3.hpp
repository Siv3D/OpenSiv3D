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

# include <Siv3D/Common.hpp>
# include <Siv3D/Common/OpenGL.hpp>
# include <Siv3D/Renderer/IRenderer.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Renderer/GLES3/BackBuffer/GLES3BackBuffer.hpp>

namespace s3d
{
	class CRenderer_GLES3 final : public ISiv3DRenderer
	{
	private:
		
		GLFWwindow* m_window = nullptr;

		std::unique_ptr<GLES3BackBuffer> m_backBuffer;

	public:

		CRenderer_GLES3();

		~CRenderer_GLES3() override;

		void init() override;

		StringView getName() const override;

		void clear() override;

		void flush() override;

		bool present() override;

		void setSceneResizeMode(ResizeMode resizeMode) override;

		ResizeMode getSceneResizeMode() const noexcept override;

		void setSceneBufferSize(Size size) override;

		Size getSceneBufferSize() const noexcept override;

		void setSceneTextureFilter(TextureFilter textureFilter) override;

		TextureFilter getSceneTextureFilter() const noexcept override;

		void setBackgroundColor(const ColorF& color) override;

		const ColorF& getBackgroundColor() const noexcept override;

		void setLetterboxColor(const ColorF& color) override;

		const ColorF& getLetterboxColor() const noexcept override;

		std::pair<float, FloatRect> getLetterboxComposition() const noexcept override;	
	};
}
