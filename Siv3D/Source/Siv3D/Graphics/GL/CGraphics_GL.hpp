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

# include "../../../ThirdParty/GLFW/include/GLFW/glfw3.h"
# include "../IGraphics.hpp"
# include "../../Window/IWindow.hpp"
# include <Siv3D/Color.hpp>

namespace s3d
{
	class CGraphics_GL : public ISiv3DGraphics
	{
	private:
		
		WindowHandle m_glfwWindow = nullptr;
		
		ColorF m_clearColor = Color(11, 22, 33);
		
		bool m_vsync = true;

	public:

		CGraphics_GL();

		~CGraphics_GL() override;

		bool init() override;

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
	};
}

# endif
