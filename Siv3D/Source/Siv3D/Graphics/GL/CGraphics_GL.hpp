//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
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
# include "BlendState/GLBlendState.hpp"
# include "../../Renderer2D/GL/CRenderer2D_GL.hpp"
# include <Siv3D/Color.hpp>

namespace s3d
{
	class CGraphics_GL : public ISiv3DGraphics
	{
	private:
		
		WindowHandle m_glfwWindow = nullptr;
		
		ColorF m_clearColor = Color(11, 22, 33);
		
		bool m_vsync = true;

		CTexture_GL* m_texture = nullptr;
		
		std::unique_ptr<GLBlendState> m_pBlendState;
		
		CRenderer2D_GL* m_renderer2D = nullptr;
		
		Size m_currentRenderTargetSize = { 640, 480 };
		
		double m_lastFlipTimeMillisec = 0;
		
		Optional<double> m_targetFrameRateHz;

	public:

		CGraphics_GL();

		~CGraphics_GL() override;

		bool init() override;
		
		GLBlendState* getBlendState() { return m_pBlendState.get(); }

		Array<DisplayOutput> enumOutputs() override;

		void setClearColor(const ColorF& color) override;

		bool setFullScreen(bool fullScreen, const Size& size, size_t displayIndex, double refreshRateHz) override;

		bool present() override;

		void clear() override;

		void beginResize() override
		{

		}

		bool endResize(const Size& size) override
		{
			return true;
		}
		
		void setVSyncEnabled(bool enabled) override;
		
		bool isVSyncEnabled() const override;

		void setTargetFrameRateHz(const Optional<double>& targetFrameRateHz) override;

		Optional<double> getTargetFrameRateHz() const override;

		double getDisplayRefreshRateHz() const override
		{
			// [Siv3D ToDo]
			return 60.0;
		}

		bool flush() override;
		
		const Size& getCurrentRenderTargetSize() const override;
	};
}

# endif
