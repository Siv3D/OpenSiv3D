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

# pragma once
# include <cassert>
# include <tuple>

namespace s3d
{
	class ISiv3DLicenseManager;
	class ISiv3DLogger;
	class ISiv3DSystem;
	class ISiv3DCPU;
	class ISiv3DProfiler;
	class ISiv3DImageFormat;
	class ISiv3DObjectDetection;
	class ISiv3DWindow;
	class ISiv3DConsole;
	class ISiv3DCursor;
	class ISiv3DKeyboard;
	class ISiv3DMouse;
	class ISiv3DGamepad;
	class ISiv3DXInput;
	class ISiv3DTextInput;
	class ISiv3DTextToSpeech;
	class ISiv3DClipboard;
	class ISiv3DDragDrop;
	class ISiv3DCodec;
	class ISiv3DAudioFormat;
	class ISiv3DSoundFont;
	class ISiv3DAudio;
	class ISiv3DFFT;
	class ISiv3DNetwork;
	class ISiv3DGraphics;
	class ISiv3DShader;
	class ISiv3DTexture;
	class ISiv3DRenderer2D;
	class ISiv3DScreenCapture;
	class ISiv3DFont;
	class ISiv3DSDFFont;
	class ISiv3DGUI;
	class ISiv3DEffect;
	class ISiv3DPrint;
	class ISiv3DScript;
	class ISiv3DAsset;

	template <class Interface>
	class Siv3DComponent
	{
	private:

		Interface* pInterface = nullptr;

	public:

		Siv3DComponent()
			: pInterface(Interface::Create()) {}

		~Siv3DComponent()
		{
			assert(pInterface == nullptr);
		}

		[[nodiscard]] Interface* get()
		{
			return pInterface;
		}

		void release()
		{
			assert(pInterface != nullptr);

			delete pInterface;

			pInterface = nullptr;
		}
	};

	class Siv3DEngine
	{
	private:

		inline static Siv3DEngine* pEngine = nullptr;

		std::tuple<
			  Siv3DComponent<ISiv3DLicenseManager>
			, Siv3DComponent<ISiv3DLogger>
			, Siv3DComponent<ISiv3DSystem>
			, Siv3DComponent<ISiv3DCPU>
			, Siv3DComponent<ISiv3DProfiler>
			, Siv3DComponent<ISiv3DImageFormat>
			, Siv3DComponent<ISiv3DObjectDetection>
			, Siv3DComponent<ISiv3DWindow>
			, Siv3DComponent<ISiv3DConsole>
			, Siv3DComponent<ISiv3DCursor>
			, Siv3DComponent<ISiv3DKeyboard>
			, Siv3DComponent<ISiv3DMouse>
			, Siv3DComponent<ISiv3DGamepad>
			, Siv3DComponent<ISiv3DXInput>
			, Siv3DComponent<ISiv3DTextInput>
			, Siv3DComponent<ISiv3DTextToSpeech>
			, Siv3DComponent<ISiv3DClipboard>
			, Siv3DComponent<ISiv3DDragDrop>
			, Siv3DComponent<ISiv3DCodec>
			, Siv3DComponent<ISiv3DAudioFormat>
			, Siv3DComponent<ISiv3DSoundFont>
			, Siv3DComponent<ISiv3DAudio>
			, Siv3DComponent<ISiv3DFFT>
			, Siv3DComponent<ISiv3DNetwork>
			, Siv3DComponent<ISiv3DGraphics>
			, Siv3DComponent<ISiv3DShader>
			, Siv3DComponent<ISiv3DTexture>
			, Siv3DComponent<ISiv3DRenderer2D>
			, Siv3DComponent<ISiv3DScreenCapture>
			, Siv3DComponent<ISiv3DFont>
			, Siv3DComponent<ISiv3DSDFFont>
			, Siv3DComponent<ISiv3DGUI>
			, Siv3DComponent<ISiv3DEffect>
			, Siv3DComponent<ISiv3DPrint>
			, Siv3DComponent<ISiv3DScript>
			, Siv3DComponent<ISiv3DAsset>
		> m_interfaces;

		template <size_t I, class Tuple>
		static void ReleaseComponent(Tuple&& t)
		{
			std::get<I>(t).release();

			if constexpr (I > 0)
			{
				ReleaseComponent<I - 1>(t);
			}
		}

		template <class Tuple>
		static void ReleaseAllComponents(Tuple&& t)
		{
			return ReleaseComponent<std::tuple_size_v<std::remove_reference_t<Tuple>> -1>(std::forward<Tuple>(t));
		}

	public:

		Siv3DEngine();

		~Siv3DEngine();

		[[nodiscard]] static bool isActive() noexcept
		{
			return pEngine != nullptr;
		}

		template <class Interface>
		[[nodiscard]] static auto* Get()
		{
			return std::get<Siv3DComponent<Interface>>(pEngine->m_interfaces).get();
		}
	};
}
