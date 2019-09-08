//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include <Siv3D/Color.hpp>
# include <Siv3D/Optional.hpp>
# include <Siv3D/Scene.hpp>
# include <Graphics/IGraphics.hpp>
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include "SceneTexture.hpp"
# include "BlendState/GLBlendState.hpp"
# include "RasterizerState/GLRasterizerState.hpp"
# include "SamplerState/GLSamplerState.hpp"

namespace s3d
{
	class CGraphics_GL : public ISiv3DGraphics
	{
	private:

		GLFWwindow* m_window = nullptr;
		
		std::unique_ptr<GLBlendState> m_pBlendState;
		std::unique_ptr<GLRasterizerState> m_pRasterizerState;
		std::unique_ptr<GLSamplerState> m_pSamplerState;
		
		ColorF m_clearColor = Palette::DefaultBackground;
		ColorF m_letterboxColor = Palette::DefaultLetterbox;
		bool m_skipClearScene = false;
		
		Optional<double> m_targetFrameRateHz;
		
		double m_lastFlipTimeMillisec = 0;
		
		SceneTexture m_sceneTexture;
		TextureFilter m_sceneTextureFilter = Scene::DefaultFilter;
		
		Size m_frameBufferSize = Size(0, 0);

	public:

		CGraphics_GL();

		~CGraphics_GL() override;

		void init() override;

		bool present() override;

		void clear() override;

		void flush() override;
		
		void setSceneTextureFilter(TextureFilter textureFilter) override;
		
		TextureFilter getSceneTextureFilter() const override;

		void setBackgroundColor(const ColorF& color) override;

		void setLetterboxColor(const ColorF& color) override;

		void setTargetFrameRateHz(const Optional<double>& targetFrameRateHz) override;

		Optional<double> getTargetFrameRateHz() const override;

		double getDPIScaling() const override;

		double getDisplayRefreshRateHz() const override;

		void skipClearScreen() override;

		const Size& getBackBufferSize() const override;

		const Size& getSceneSize() const override;

		void setSceneSize(const Size& sceneSize) override;

		void resizeBuffers(const Size& backBufferSize, const Size& sceneSize) override;

		Optional<Rect> getFullscreenRect() override;

		void requestScreenCapture() override;

		const Image& getScreenCapture() const override;
		
		GLBlendState* getBlendState() { return m_pBlendState.get(); }
		
		GLRasterizerState* getRasterizerState() { return m_pRasterizerState.get(); }
		
		GLSamplerState* getSamplerState() { return m_pSamplerState.get(); }
		
		SceneTexture& getRenderTarget() { return m_sceneTexture; }
	};
}
