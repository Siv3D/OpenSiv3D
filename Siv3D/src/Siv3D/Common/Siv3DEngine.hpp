//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <tuple>
# include "Siv3DComponent.hpp"

namespace s3d
{
	class ISiv3DEmpty;
	class ISiv3DLicenseManager;
	class ISiv3DLogger;
	class ISiv3DSystem;
	class ISiv3DResource;
	class ISiv3DProfiler;
	class ISiv3DAssetMonitor;
	class ISiv3DUserAction;
	class ISiv3DWindow;
	class ISiv3DImageDecoder;
	class ISiv3DImageEncoder;
	class ISiv3DScene;
	class ISiv3DConsole;
	class ISiv3DCursor;
	class ISiv3DKeyboard;
	class ISiv3DMouse;
	class ISiv3DXInput;
	class ISiv3DGamepad;
	class ISiv3DPentablet;
	class ISiv3DTextInput;
	class ISiv3DClipboard;
	class ISiv3DDragDrop;
	class ISiv3DToastNotification;
	class ISiv3DNetwork;
	class ISiv3DSoundFont;
	class ISiv3DAudioCodec;
	class ISiv3DAudioDecoder;
	class ISiv3DAudioEncoder;
	class ISiv3DFFT;
	class ISiv3DAudio;
	class ISiv3DTextToSpeech;
	class ISiv3DRenderer;
	class ISiv3DTexture;
	class ISiv3DShader;
	class ISiv3DMesh;
	class ISiv3DRenderer2D;
	class ISiv3DRenderer3D;
	class ISiv3DScreenCapture;
	class ISiv3DModel;
	class ISiv3DFont;
	class ISiv3DGUI;
	class ISiv3DPrint;
	class ISiv3DPrimitiveMesh;
	class ISiv3DAsset;
	class ISiv3DEffect;
	class ISiv3DTrailRenderer;
	class ISiv3DScript;
	class ISiv3DAddon;

	class Siv3DEngine
	{
	private:

		inline static Siv3DEngine* pEngine = nullptr;

		std::tuple<
			Siv3DComponent<ISiv3DEmpty>,
			Siv3DComponent<ISiv3DLicenseManager>,
			Siv3DComponent<ISiv3DLogger>,
			Siv3DComponent<ISiv3DSystem>,
			Siv3DComponent<ISiv3DResource>,
			Siv3DComponent<ISiv3DProfiler>,
			Siv3DComponent<ISiv3DAssetMonitor>,
			Siv3DComponent<ISiv3DUserAction>,
			Siv3DComponent<ISiv3DWindow>,
			Siv3DComponent<ISiv3DImageDecoder>,
			Siv3DComponent<ISiv3DImageEncoder>,
			Siv3DComponent<ISiv3DScene>,
			Siv3DComponent<ISiv3DConsole>,
			Siv3DComponent<ISiv3DCursor>,
			Siv3DComponent<ISiv3DKeyboard>,
			Siv3DComponent<ISiv3DMouse>,
			Siv3DComponent<ISiv3DXInput>,
			Siv3DComponent<ISiv3DGamepad>,
			Siv3DComponent<ISiv3DPentablet>,
			Siv3DComponent<ISiv3DTextInput>,
			Siv3DComponent<ISiv3DClipboard>,
			Siv3DComponent<ISiv3DDragDrop>,
			Siv3DComponent<ISiv3DToastNotification>,
			Siv3DComponent<ISiv3DNetwork>,
			Siv3DComponent<ISiv3DSoundFont>,
			Siv3DComponent<ISiv3DAudioCodec>,
			Siv3DComponent<ISiv3DAudioDecoder>,
			Siv3DComponent<ISiv3DAudioEncoder>,
			Siv3DComponent<ISiv3DFFT>,
			Siv3DComponent<ISiv3DAudio>,
			Siv3DComponent<ISiv3DTextToSpeech>,
			Siv3DComponent<ISiv3DRenderer>,
			Siv3DComponent<ISiv3DTexture>,
			Siv3DComponent<ISiv3DShader>,
			Siv3DComponent<ISiv3DMesh>,
			Siv3DComponent<ISiv3DRenderer2D>,
			Siv3DComponent<ISiv3DRenderer3D>,
			Siv3DComponent<ISiv3DScreenCapture>,
			Siv3DComponent<ISiv3DModel>,
			Siv3DComponent<ISiv3DFont>,
			Siv3DComponent<ISiv3DGUI>,
			Siv3DComponent<ISiv3DPrint>,
			Siv3DComponent<ISiv3DPrimitiveMesh>,
			Siv3DComponent<ISiv3DAsset>,
			Siv3DComponent<ISiv3DEffect>,
			Siv3DComponent<ISiv3DTrailRenderer>,
			Siv3DComponent<ISiv3DScript>,
			Siv3DComponent<ISiv3DAddon>> m_components;

	public:

		Siv3DEngine() noexcept;

		~Siv3DEngine();

		[[nodiscard]]
		static bool isActive() noexcept;

		template <class Interface>
		[[nodiscard]]
		static auto* Get() noexcept
		{
			return std::get<Siv3DComponent<Interface>>(pEngine->m_components).get();
		}
	};

	# define SIV3D_ENGINE(COMPONENT) Siv3DEngine::Get<ISiv3D##COMPONENT>()
}
