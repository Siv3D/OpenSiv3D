//-----------------------------------------------
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
# include <Siv3D/Windows/Windows.hpp>

namespace s3d
{
	class WGLContext
	{
	private:

		HWND m_hWnd = nullptr;

		HDC m_hDC = nullptr;
		
		HGLRC m_glContext = nullptr;

	public:

		WGLContext() = default;

		~WGLContext();

		void init(HWND hWnd);

		void destroy();

		void makeCurrent();

		void swapBuffers();
	};
}
