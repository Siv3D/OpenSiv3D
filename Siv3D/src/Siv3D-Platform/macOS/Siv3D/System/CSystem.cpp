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

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Resource/IResource.hpp>
# include <Siv3D/Profiler/IProfiler.hpp>
# include <Siv3D/AssetMonitor/IAssetMonitor.hpp>
# include <Siv3D/LicenseManager/ILicenseManager.hpp>
# include <Siv3D/ImageDecoder/IImageDecoder.hpp>
# include <Siv3D/ImageEncoder/IImageEncoder.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Scene/IScene.hpp>
# include <Siv3D/Cursor/ICursor.hpp>
# include <Siv3D/Keyboard/IKeyboard.hpp>
# include <Siv3D/Mouse/IMouse.hpp>
# include <Siv3D/Renderer/IRenderer.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/UserAction/IUserAction.hpp>
# include <Siv3D/Font/IFont.hpp>
# include <Siv3D/Effect/IEffect.hpp>
# include <Siv3D/Addon/IAddon.hpp>
# include <Siv3D/System/SystemLog.hpp>
# include <Siv3D/System/SystemMisc.hpp>
# include "CSystem.hpp"

namespace s3d
{
	CSystem::CSystem()
	{

	}

	CSystem::~CSystem()
	{
		LOG_SCOPED_TRACE(U"CSystem::~CSystem()");

		SystemMisc::Destroy();
		SystemLog::Final();
	}

	void CSystem::init()
	{
		LOG_SCOPED_TRACE(U"CSystem::init()");
		
		SystemLog::Initial();
		SystemMisc::Init();
		
		SIV3D_ENGINE(Resource)->init();
		SIV3D_ENGINE(Profiler)->init();
		SIV3D_ENGINE(Window)->init();
		SIV3D_ENGINE(ImageDecoder)->init();
		SIV3D_ENGINE(ImageEncoder)->init();
		SIV3D_ENGINE(Cursor)->init();
		SIV3D_ENGINE(Keyboard)->init();
		SIV3D_ENGINE(Mouse)->init();
		SIV3D_ENGINE(Renderer)->init();
		SIV3D_ENGINE(Renderer2D)->init();
		SIV3D_ENGINE(Font)->init();
		SIV3D_ENGINE(Effect)->init();
	}

	bool CSystem::update()
	{
		if (SIV3D_ENGINE(UserAction)->terminationTriggered())
		{
			return false;
		}
		
		SIV3D_ENGINE(Addon)->draw();
		SIV3D_ENGINE(Renderer)->flush();
		SIV3D_ENGINE(Profiler)->endFrame();
		SIV3D_ENGINE(Renderer)->present();
		
		//
		// previous frame
		//
		// -----------------------------------
		//
		// current frame
		//
		
		SIV3D_ENGINE(Profiler)->beginFrame();
		if (not SIV3D_ENGINE(AssetMonitor)->update())
		{
			return false;
		}
		SIV3D_ENGINE(Scene)->update();
		SIV3D_ENGINE(Window)->update();
		SIV3D_ENGINE(Renderer)->clear();
		SIV3D_ENGINE(Cursor)->update();
		SIV3D_ENGINE(Keyboard)->update();
		SIV3D_ENGINE(Mouse)->update();
		SIV3D_ENGINE(Effect)->update();
		if (not SIV3D_ENGINE(Addon)->update())
		{
			return false;
		}
		
		// triggerd by key inputs
		SIV3D_ENGINE(LicenseManager)->update();

		return true;
	}
}
