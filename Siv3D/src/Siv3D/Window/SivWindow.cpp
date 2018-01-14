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

# include "../Siv3DEngine.hpp"
# include "IWindow.hpp"
# include <Siv3D/Window.hpp>
# include <Siv3D/Monitor.hpp>
# include <Siv3D/Graphics.hpp>

namespace s3d
{
	namespace Window
	{
		void SetTitle(const String& title)
		{
			Siv3DEngine::GetWindow()->setTitle(title);
		}
		
		const WindowState& GetState()
		{
			return Siv3DEngine::GetWindow()->getState();
		}

		void SetPos(const Point& pos)
		{
			Siv3DEngine::GetWindow()->setPos(pos);
		}

		void Centering()
		{
			const auto monitors = System::EnumActiveMonitors();

			if (!monitors)
			{
				return;
			}

			const Rect workArea = monitors[System::GetCurrentMonitorIndex()].workArea;
			const s3d::Size windowSize = Siv3DEngine::GetWindow()->getState().windowSize;
			
			Point pos = workArea.pos + (workArea.size - windowSize) / 2;

			if (pos.y < 0)
			{
				pos.y = 0;
			}

			SetPos(pos);
		}

		bool Resize(const int32 width, const int32 height, const bool centering)
		{
			const auto& state = Siv3DEngine::GetWindow()->getState();

			if (state.fullScreen)
			{
				return false;
			}

			const s3d::Size newSize(width, height);

			bool result = true;

			if (state.clientSize != newSize)
			{
				result = Graphics::SetFullScreen(false, newSize, System::GetCurrentMonitorIndex());
			}

			if (centering)
			{
				Centering();
			}

			return result;
		}

		void SetBaseSize(const s3d::Size& size)
		{
			Siv3DEngine::GetWindow()->setBaseSize(size);
		}

		s3d::Size BaseSize()
		{
			return Siv3DEngine::GetWindow()->getBaseSize();
		}
	}
}
