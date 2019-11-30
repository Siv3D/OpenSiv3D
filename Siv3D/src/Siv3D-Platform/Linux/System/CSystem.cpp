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

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3DEngine.hpp>
# include <LicenseManager/ILicenseManager.hpp>
# include <CPU/ICPU.hpp>
# include <Profiler/IProfiler.hpp>
# include <ImageFormat/IImageFormat.hpp>
# include <ObjectDetection/IObjectDetection.hpp>
# include <Window/IWindow.hpp>
# include <Cursor/ICursor.hpp>
# include <Keyboard/IKeyboard.hpp>
# include <Mouse/IMouse.hpp>
# include <Gamepad/IGamepad.hpp>
# include <XInput/IXInput.hpp>
# include <TextInput/ITextInput.hpp>
# include <TextToSpeech/ITextToSpeech.hpp>
# include <Clipboard/IClipboard.hpp>
# include <DragDrop/IDragDrop.hpp>
# include <Codec/ICodec.hpp>
# include <AudioFormat/IAudioFormat.hpp>
# include <Audio/IAudio.hpp>
# include <FFT/IFFT.hpp>
# include <Network/INetwork.hpp>
# include <ToastNotification/IToastNotification.hpp>
# include <Graphics/IGraphics.hpp>
# include <ScreenCapture/IScreenCapture.hpp>
# include <Font/IFont.hpp>
# include <SDFFont/ISDFFont.hpp>
# include <GUI/IGUI.hpp>
# include <Effect/IEffect.hpp>
# include <Print/IPrint.hpp>
# include <Asset/IAsset.hpp>
# include <Script/IScript.hpp>
# include <System/CSystem.hpp>
# include <System/SystemLog.hpp>

namespace s3d
{
	CSystem::CSystem()
	{

	}

	CSystem::~CSystem()
	{
		SystemLog::Final();
	}

	void CSystem::init()
	{
		LOG_TRACE(U"CSystem::init()");
		SystemLog::Initial();
	
		Siv3DEngine::Get<ISiv3DCPU>()->init();
		Siv3DEngine::Get<ISiv3DProfiler>()->init();
		Siv3DEngine::Get<ISiv3DImageFormat>()->init();
		Siv3DEngine::Get<ISiv3DObjectDetection>()->init();
		Siv3DEngine::Get<ISiv3DWindow>()->init();

		Siv3DEngine::Get<ISiv3DCursor>()->init();
		Siv3DEngine::Get<ISiv3DKeyboard>()->init();
		Siv3DEngine::Get<ISiv3DMouse>()->init();
		Siv3DEngine::Get<ISiv3DGamepad>()->init();
		Siv3DEngine::Get<ISiv3DXInput>()->init();
		Siv3DEngine::Get<ISiv3DTextInput>()->init();
		Siv3DEngine::Get<ISiv3DTextToSpeech>()->init();
		Siv3DEngine::Get<ISiv3DClipboard>()->init();
		Siv3DEngine::Get<ISiv3DDragDrop>()->init();
		Siv3DEngine::Get<ISiv3DCodec>()->init();
		Siv3DEngine::Get<ISiv3DAudioFormat>()->init();
		Siv3DEngine::Get<ISiv3DAudio>()->init();
		Siv3DEngine::Get<ISiv3DFFT>()->init();
		Siv3DEngine::Get<ISiv3DNetwork>()->init();
		Siv3DEngine::Get<ISiv3DToastNotification>()->init();

		Siv3DEngine::Get<ISiv3DGraphics>()->init();
		Siv3DEngine::Get<ISiv3DScreenCapture>()->init();
		Siv3DEngine::Get<ISiv3DFont>()->init();
		Siv3DEngine::Get<ISiv3DSDFFont>()->init();
		Siv3DEngine::Get<ISiv3DGUI>()->init();
		Siv3DEngine::Get<ISiv3DEffect>()->init();
		Siv3DEngine::Get<ISiv3DPrint>()->init();
		Siv3DEngine::Get<ISiv3DAsset>()->init();
		Siv3DEngine::Get<ISiv3DScript>()->init();

		Siv3DEngine::Get<ISiv3DCursor>()->update();


		m_setupState = SetupState::Initialized;
		LOG_INFO(U"✅ Siv3D engine setup completed");
	}

	bool CSystem::update()
	{
		if (!std::exchange(m_updateSucceeded, false))
		{
			return false;
		}

		if (m_setupState == SetupState::Initialized)
		{
			Siv3DEngine::Get<ISiv3DWindow>()->show(true);

			m_setupState = SetupState::Displayed;

			Siv3DEngine::Get<ISiv3DCursor>()->applyStyleImmediately(CursorStyle::Default);
		}

		Siv3DEngine::Get<ISiv3DPrint>()->draw();/*
		*/Siv3DEngine::Get<ISiv3DGraphics>()->flush();/*
		*/Siv3DEngine::Get<ISiv3DProfiler>()->endFrame();/*
		*/if (!Siv3DEngine::Get<ISiv3DGraphics>()->present())
		{
			return false;
		}

		if (const uint32 event = m_terminationTrigger.checkTermination())
		{
			m_terminationTrigger.logExitEvent(event);
			return false;
		}

		/////////////////////////////////////////////////////
		//
		// New Frame
		//
		if (!Siv3DEngine::Get<ISiv3DProfiler>()->beginFrame())
		{
			return false;
		}

		++m_frameCounter;
		m_frameDelta.update();
		const bool onDeviceChange = m_onDeviceChange.exchange(false);

		Siv3DEngine::Get<ISiv3DWindow>()->update();
		Siv3DEngine::Get<ISiv3DGraphics>()->clear();/*
		*/Siv3DEngine::Get<ISiv3DAsset>()->update();

		Siv3DEngine::Get<ISiv3DCursor>()->update();
		Siv3DEngine::Get<ISiv3DGamepad>()->update(onDeviceChange);
		Siv3DEngine::Get<ISiv3DXInput>()->update(onDeviceChange);
		Siv3DEngine::Get<ISiv3DKeyboard>()->update();/*
		*/Siv3DEngine::Get<ISiv3DMouse>()->update();/*
		*/Siv3DEngine::Get<ISiv3DTextInput>()->update();
		Siv3DEngine::Get<ISiv3DDragDrop>()->update();
		Siv3DEngine::Get<ISiv3DLicenseManager>()->update();
		Siv3DEngine::Get<ISiv3DScreenCapture>()->update();
		Siv3DEngine::Get<ISiv3DEffect>()->update();

		m_updateSucceeded = true;
		return true;
	}

	void CSystem::setTerminationTriggers(const uint32 userActionFlags)
	{
		m_terminationTrigger.setTerminationTriggers(userActionFlags);
	}

	uint32 CSystem::getTerminationTriggers()
	{
		return m_terminationTrigger.getTerminationTriggers();
	}

	uint32 CSystem::getUserActions()
	{
		return m_terminationTrigger.getPreviousUserActions();
	}

	void CSystem::reportUserActions(const uint32 userActions)
	{
		m_terminationTrigger.reportUserActions(userActions);
	}

	uint64 CSystem::getSystemFrameCount() const noexcept
	{
		return m_frameCounter.getSystemFrameCount();
	}

	int32 CSystem::getUserFrameCount() const noexcept
	{
		return m_frameCounter.getUserFrameCount();
	}

	void CSystem::setUserFrameCount(const int32 count) noexcept
	{
		m_frameCounter.setUserFrameCount(count);
	}

	FrameDelta& CSystem::getFrameDelta() noexcept
	{
		return m_frameDelta;
	}

	void CSystem::onDeviceChange()
	{
		LOG_TRACE(U"CSystem::onDeviceChange()");

		m_onDeviceChange = true;
	}
}
