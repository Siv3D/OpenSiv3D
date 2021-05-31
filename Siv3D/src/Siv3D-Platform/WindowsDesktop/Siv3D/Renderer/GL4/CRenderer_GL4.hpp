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
# include <Siv3D/Common.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Scene.hpp>
# include <Siv3D/Windows/Windows.hpp>
# include <Siv3D/Renderer/IRenderer.hpp>
# include "WGLContext.hpp"
# include <Siv3D/Renderer/GL4/BackBuffer/GL4BackBuffer.hpp>
# include <Siv3D/Renderer/GL4/BlendState/GL4BlendState.hpp>
# include <Siv3D/Renderer/GL4/RasterizerState/GL4RasterizerState.hpp>
# include <Siv3D/Renderer/GL4/SamplerState/GL4SamplerState.hpp>
# include <Siv3D/Texture/GL4/CTexture_GL4.hpp>

namespace s3d
{
	class CRenderer_GL4 final : public ISiv3DRenderer
	{
	private:

		CRenderer2D_GL4* pRenderer2D = nullptr;
		CTexture_GL4* pTexture = nullptr;
		HWND m_hWnd = nullptr;

		WGLContext m_wglContext;

		std::unique_ptr<GL4BackBuffer> m_backBuffer;

		std::unique_ptr<GL4BlendState> m_blendState;

		std::unique_ptr<GL4RasterizerState> m_rasterizerState;
		
		std::unique_ptr<GL4SamplerState> m_samplerState;

	public:

		CRenderer_GL4();

		~CRenderer_GL4() override;

		EngineOption::Renderer getRendererType() const noexcept override;

		void init() override;

		StringView getName() const override;

		void clear() override;

		void flush() override;

		bool present() override;

		void captureScreenshot() override;

		const Image& getScreenCapture() const override;

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

		std::pair<float, RectF> getLetterboxComposition() const noexcept override;

		void updateSceneSize() override;

		//
		// GL4
		//

		GL4BlendState& getBlendState() noexcept;

		GL4RasterizerState& getRasterizerState() noexcept;

		GL4SamplerState& getSamplerState() noexcept;
	};
}
