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

# pragma once
# include <tuple>
# include "Siv3DComponent.hpp"

namespace s3d
{
	class ISiv3DDummy;
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
	class ISiv3DRenderer;
	class ISiv3DTexture;
	class ISiv3DShader;
	class ISiv3DRenderer2D;
	class ISiv3DScreenCapture;
	class ISiv3DFont;
	class ISiv3DGUI;
	class ISiv3DPrint;
	class ISiv3DEffect;
	class ISiv3DAddon;

	class Siv3DEngine
	{
	private:

		inline static Siv3DEngine* pEngine = nullptr;

		std::tuple<
			Siv3DComponent<ISiv3DDummy>,
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
			Siv3DComponent<ISiv3DRenderer>,
			Siv3DComponent<ISiv3DTexture>,
			Siv3DComponent<ISiv3DShader>,
			Siv3DComponent<ISiv3DRenderer2D>,
			Siv3DComponent<ISiv3DScreenCapture>,
			Siv3DComponent<ISiv3DFont>,
			Siv3DComponent<ISiv3DGUI>,
			Siv3DComponent<ISiv3DPrint>,
			Siv3DComponent<ISiv3DEffect>,
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
