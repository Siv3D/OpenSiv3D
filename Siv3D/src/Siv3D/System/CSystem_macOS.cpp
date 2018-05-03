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

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS)

# include "../Siv3DEngine.hpp"
# include "CSystem_macOS.hpp"
# include "../Logger/ILogger.hpp"
# include "../CPU/ICPU.hpp"
# include "../ImageFormat/IImageFormat.hpp"
# include "../Window/IWindow.hpp"
# include "../Profiler/IProfiler.hpp"
# include "../Clipboard/IClipboard.hpp"
# include "../DragDrop/IDragDrop.hpp"
# include "../Cursor/ICursor.hpp"
# include "../Keyboard/IKeyboard.hpp"
# include "../Mouse/IMouse.hpp"
# include "../Gamepad/IGamepad.hpp"
# include "../XInput/IXInput.hpp"
# include "../TextInput/ITextInput.hpp"
# include "../Codec/ICodec.hpp"
# include "../AudioFormat/IAudioFormat.hpp"
# include "../Audio/IAudio.hpp"
# include "../FFT/IFFT.hpp"
# include "../Network/INetwork.hpp"
# include "../Graphics/IGraphics.hpp"
# include "../Texture/ITexture.hpp"
# include "../ScreenCapture/IScreenCapture.hpp"
# include "../Font/IFont.hpp"
# include "../Print/IPrint.hpp"
# include "../Effect/IEffect.hpp"
# include "../Script/IScript.hpp"
# include "../Asset/IAsset.hpp"
# include <Siv3D/Logger.hpp>

namespace s3d
{
	CSystem_macOS::CSystem_macOS()
	{

	}

	CSystem_macOS::~CSystem_macOS()
	{
		FinalLogMessage();
	}

	bool CSystem_macOS::init()
	{
		if (!Siv3DEngine::GetLogger()->init())
		{
			return false;
		}

		InitialLogMessage();

		if (!Siv3DEngine::GetCPU()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetImageFormat()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetWindow()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetProfiler()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetClipboard()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetDragDrop()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetCursor()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetKeyboard()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetMouse()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetGamepad()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetXInput()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetTextInput()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetCodec()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetAudioFormat()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetAudio()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetFFT()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetNetwork()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetGraphics()->init())
		{
			return false;
		}
		
		Siv3DEngine::GetGraphics()->clear();

		if (!Siv3DEngine::GetScreenCapture()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetFont()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetPrint()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetEffect()->init())
		{
			return false;
		}
		
		if (!Siv3DEngine::GetScript()->init())
		{
			return false;
		}

		if (!Siv3DEngine::GetAsset()->init())
		{
			return false;
		}

		LOG_INFO(U"✅ Siv3D engine setup completed");

		return true;
	}

	bool CSystem_macOS::update(bool clearGraphics)
	{
		if (!m_updateSucceeded)
		{
			return false;
		}

		m_updateSucceeded = false;

		Siv3DEngine::GetPrint()->draw();

		if (!Siv3DEngine::GetGraphics()->flush(clearGraphics))
		{
			return false;
		}
		
		Siv3DEngine::GetProfiler()->endFrame();

		Siv3DEngine::GetGraphics()->present();

		if (!Siv3DEngine::GetScreenCapture()->update())
		{
			return false;
		}

		if (const uint32 event = m_exitEventManager.checkExitEvent())
		{
			m_exitEventManager.logExitEvent(event);

			return false;
		}

		if (!Siv3DEngine::GetProfiler()->beginFrame())
		{
			return false;
		}

		++m_frameCounter;

		m_frameDelta.update();

		if (!Siv3DEngine::GetWindow()->update())
		{
			return false;
		}
		
		Siv3DEngine::GetGraphics()->clear();
		
		Siv3DEngine::GetTexture()->update(4);
		
		if (!Siv3DEngine::GetDragDrop()->update())
		{
			return false;
		}

		Siv3DEngine::GetCursor()->update();

		Siv3DEngine::GetKeyboard()->update();

		Siv3DEngine::GetMouse()->update();

		Siv3DEngine::GetGamepad()->update(true);

		Siv3DEngine::GetXInput()->update(true);

		Siv3DEngine::GetTextInput()->update();
		
		Siv3DEngine::GetEffect()->update();
		
		return m_updateSucceeded = true;
	}

	void CSystem_macOS::reportEvent(const uint32 windowEventFlag)
	{
		m_exitEventManager.reportEvent(windowEventFlag);
	}

	void CSystem_macOS::setExitEvent(const uint32 windowEventFlag)
	{
		m_exitEventManager.setExitEvent(windowEventFlag);
	}

	uint32 CSystem_macOS::getPreviousEvent() const
	{
		return m_exitEventManager.getPreviousEvent();
	}

	uint64 CSystem_macOS::getSystemFrameCount() const noexcept
	{
		return m_frameCounter.getSystemFrameCount();
	}

	int32 CSystem_macOS::getUserFrameCount() const noexcept
	{
		return m_frameCounter.getUserFrameCount();
	}

	void CSystem_macOS::setUserFrameCount(const int32 count) noexcept
	{
		m_frameCounter.setUserFrameCount(count);
	}

	double CSystem_macOS::getDeltaTime() const noexcept
	{
		return m_frameDelta.getDeltaTimeSec();
	}
}

# endif
