//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include <GL/glew.h>
# include "../../../ThirdParty/GLFW/include/GLFW/glfw3.h"
# include "../IGraphics.hpp"
# include "../../Window/IWindow.hpp"
# include "../../Texture/GL/CTexture_GL.hpp"
# include "../../Shader/GL/CShader_GL.hpp"
# include "BlendState/GLBlendState.hpp"
# include "RasterizerState/GLRasterizerState.hpp"
# include "SamplerState/GLSamplerState.hpp"
# include "../../Renderer2D/GL/CRenderer2D_GL.hpp"
# include <Siv3D/Color.hpp>

namespace s3d
{
	class ScreenCaptureManager
	{
	private:
		
		GLuint m_fbo = 0;
		
		GLuint m_texture = 0;

		Image m_image;
		
		bool m_requested = false;
		
	public:
		
		ScreenCaptureManager() = default;
		
		~ScreenCaptureManager()
		{
			if (m_texture)
			{
				::glDeleteTextures(1, &m_texture);
			}
			
			if (m_fbo)
			{
				::glDeleteFramebuffers(1, &m_fbo);
			}
		}
		
		void request()
		{
			m_requested = true;
		}
		
		bool isRequested() const
		{
			return m_requested;
		}
		
		void capture(const Size& size)
		{
			m_requested = false;
			
			if (!m_fbo || !m_texture)
			{
				::glGenFramebuffers(1, &m_fbo);
				::glGenTextures(1, &m_texture);
			}
			
			if (size != m_image.size())
			{
				::glBindTexture(GL_TEXTURE_2D, m_texture);
				::glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
				
				::glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
				::glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_texture, 0);
				
				m_image.resize(size);
			}
			
			::glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
			::glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
			
			::glBlitFramebuffer(0, 0, size.x, size.y, 0, 0, size.x, size.y, GL_COLOR_BUFFER_BIT, GL_LINEAR);
			
			::glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
			::glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

			::glReadPixels(0, 0, size.x, size.y, GL_RGBA, GL_UNSIGNED_BYTE, m_image.data());
			
			::glBindFramebuffer(GL_FRAMEBUFFER, 0);
				
			m_image.flip();
		}
		
		const Image& getImage() const
		{
			return m_image;
		}
	};
	
	class CGraphics_GL : public ISiv3DGraphics
	{
	private:
		
		WindowHandle m_glfwWindow = nullptr;
		
		ColorF m_clearColor = Color(11, 22, 33);
		
		CTexture_GL* m_texture = nullptr;
		
		CShader_GL* m_shader = nullptr;
		
		std::unique_ptr<GLBlendState> m_pBlendState;
		
		std::unique_ptr<GLRasterizerState> m_pRasterizerState;
		
		std::unique_ptr<GLSamplerState> m_pSamplerState;
		
		CRenderer2D_GL* m_renderer2D = nullptr;
		
		Size m_currentRenderTargetSize = { 640, 480 };
		
		double m_lastFlipTimeMillisec = 0;
		
		Optional<double> m_targetFrameRateHz;

		RenderTexture* m_unused = nullptr;
		
		ScreenCaptureManager m_screenCapture;
		
	public:

		CGraphics_GL();

		~CGraphics_GL() override;

		bool init() override;
		
		GLBlendState* getBlendState() { return m_pBlendState.get(); }
		
		GLRasterizerState* getRasterizerState() { return m_pRasterizerState.get(); }
		
		GLSamplerState* getSamplerState() { return m_pSamplerState.get(); }

		Array<DisplayOutput> enumOutputs() override;

		void setClearColor(const ColorF& color) override;

		bool setFullScreen(bool fullScreen, const Size& size, size_t displayIndex, double refreshRateHz) override;

		bool present() override;

		void clear() override;

		void beginResize() override
		{

		}

		bool endResize(const Size&) override
		{
			return true;
		}

		void setTargetFrameRateHz(const Optional<double>& targetFrameRateHz) override;

		Optional<double> getTargetFrameRateHz() const override;

		double getDisplayRefreshRateHz() const override
		{
			// [Siv3D ToDo]
			return 60.0;
		}

		bool flush(bool clearGraphics) override;
		
		const Size& getCurrentRenderTargetSize() const override;

		const RenderTexture& getBackBuffer2D() const override
		{
			// [Siv3D ToDo]
			return *m_unused;
		}
		
		void requestScreenCapture() override;

		const Image& getScreenCapture() const override;
	};
}

# endif
