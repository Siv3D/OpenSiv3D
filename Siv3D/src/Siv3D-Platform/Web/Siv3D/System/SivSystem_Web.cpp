//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/System.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/InputGroups.hpp>
# include <emscripten.h>
# include <GLFW/glfw3.h>

namespace s3d
{
	namespace System
	{
		namespace detail
		{
			__attribute__((import_name("siv3dLaunchBrowser")))
			void siv3dLaunchBrowser(const char* url);
		}

		bool LaunchBrowser(const FilePathView _url)
		{
			String url{ _url };
			const bool isWebPage = url.starts_with(U"http://")
				|| url.starts_with(U"https://");

			if (not isWebPage)
			{
				const String extension = FileSystem::Extension(_url);
				const bool isHTML = (extension == U"html") || (extension == U"htm");

				if (not isHTML)
				{
					return false;
				}

				url = FileSystem::FullPath(_url);
			}

			detail::siv3dLaunchBrowser(url.toUTF8().c_str());
			return true;
		}

		bool ShowInFileManager(const FilePathView path)
		{
			return false;
		}
	}

	namespace Platform::Web::System
	{
		namespace detail
		{
			void RunMainLoop(void* userData)
			{
				const auto* mainLoop = static_cast<const std::function<void()>*>(userData);
				mainLoop->operator()();
			}
		}

		void SetMainLoop(std::function<void()> mainLoop)
		{
			/*
				emscripten_set_main_loop を呼ぶと
				JavaScript の例外を使って大域脱出が行われる。
			
				そのため、この関数の処理が戻ってくることはない上、
				スタックメモリのアンワインド処理も行われないため、
				Main 関数でラムダ式による変数の参照キャプチャを行なったり、
				この関数で mainLoop へのポインタを束縛したりしても
				メモリの領域外アクセスにはならない

				(ただし、アプリを閉じたときに Main 関数の変数のデストラクタが呼ばれることもないので
				注意が必要である)
			*/
			static std::function<void()> g_mainLoop = mainLoop;
			::emscripten_set_main_loop_arg(&detail::RunMainLoop, &g_mainLoop, 0, 1);
		}
	
		namespace detail
		{
			static HashTable<uint8, uint16> KeyConversionTable
			{
				{ 0x03, 0 },
				{ 0x08, GLFW_KEY_BACKSPACE },
				{ 0x09, GLFW_KEY_TAB },
				{ 0x0C, 0 },
				{ 0x0D, GLFW_KEY_ENTER },
				{ 0x10, 0 }, // shift
				{ 0x11, 0 }, // control
				{ 0x12, 0 }, // alt
				{ 0x13, GLFW_KEY_PAUSE },
				{ 0x1B, GLFW_KEY_ESCAPE },
				{ 0x20, GLFW_KEY_SPACE },
				{ 0x21, GLFW_KEY_PAGE_UP },
				{ 0x22, GLFW_KEY_PAGE_DOWN },
				{ 0x23, GLFW_KEY_END },
				{ 0x24, GLFW_KEY_HOME },
				{ 0x25, GLFW_KEY_LEFT },
				{ 0x26, GLFW_KEY_UP },
				{ 0x27, GLFW_KEY_RIGHT },
				{ 0x28, GLFW_KEY_DOWN },
				{ 0x2C, GLFW_KEY_PRINT_SCREEN },
				{ 0x2D, GLFW_KEY_INSERT },
				{ 0x2E, GLFW_KEY_DELETE },
				{ 0x30, GLFW_KEY_0 },
				{ 0x31, GLFW_KEY_1 },
				{ 0x32, GLFW_KEY_2 },
				{ 0x33, GLFW_KEY_3 },
				{ 0x34, GLFW_KEY_4 },
				{ 0x35, GLFW_KEY_5 },
				{ 0x36, GLFW_KEY_6 },
				{ 0x37, GLFW_KEY_7 },
				{ 0x38, GLFW_KEY_8 },
				{ 0x39, GLFW_KEY_9 },
				{ 0x41, GLFW_KEY_A },
				{ 0x42, GLFW_KEY_B },
				{ 0x43, GLFW_KEY_C },
				{ 0x44, GLFW_KEY_D },
				{ 0x45, GLFW_KEY_E },
				{ 0x46, GLFW_KEY_F },
				{ 0x47, GLFW_KEY_G },
				{ 0x48, GLFW_KEY_H },
				{ 0x49, GLFW_KEY_I },
				{ 0x4A, GLFW_KEY_J },
				{ 0x4B, GLFW_KEY_K },
				{ 0x4C, GLFW_KEY_L },
				{ 0x4D, GLFW_KEY_M },
				{ 0x4E, GLFW_KEY_N },
				{ 0x4F, GLFW_KEY_O },
				{ 0x50, GLFW_KEY_P },
				{ 0x51, GLFW_KEY_Q },
				{ 0x52, GLFW_KEY_R },
				{ 0x53, GLFW_KEY_S },
				{ 0x54, GLFW_KEY_T },
				{ 0x55, GLFW_KEY_U },
				{ 0x56, GLFW_KEY_V },
				{ 0x57, GLFW_KEY_W },
				{ 0x58, GLFW_KEY_X },
				{ 0x59, GLFW_KEY_Y },
				{ 0x5A, GLFW_KEY_Z },
				{ 0x60, GLFW_KEY_KP_0 },
				{ 0x61, GLFW_KEY_KP_1 },
				{ 0x62, GLFW_KEY_KP_2 },
				{ 0x63, GLFW_KEY_KP_3 },
				{ 0x64, GLFW_KEY_KP_4 },
				{ 0x65, GLFW_KEY_KP_5 },
				{ 0x66, GLFW_KEY_KP_6 },
				{ 0x67, GLFW_KEY_KP_7 },
				{ 0x68, GLFW_KEY_KP_8 },
				{ 0x69, GLFW_KEY_KP_9 },
				{ 0x6A, GLFW_KEY_KP_MULTIPLY },
				{ 0x6B, GLFW_KEY_KP_ADD },
				{ 0x6C, GLFW_KEY_KP_ENTER },
				{ 0x6D, GLFW_KEY_KP_SUBTRACT },
				{ 0x6E, GLFW_KEY_KP_DECIMAL },
				{ 0x6F, GLFW_KEY_KP_DIVIDE },
				{ 0x70, GLFW_KEY_F1 },
				{ 0x71, GLFW_KEY_F2 },
				{ 0x72, GLFW_KEY_F3 },
				{ 0x73, GLFW_KEY_F4 },
				{ 0x74, GLFW_KEY_F5 },
				{ 0x75, GLFW_KEY_F6 },
				{ 0x76, GLFW_KEY_F7 },
				{ 0x77, GLFW_KEY_F8 },
				{ 0x78, GLFW_KEY_F9 },
				{ 0x79, GLFW_KEY_F10 },
				{ 0x7A, GLFW_KEY_F11 },
				{ 0x7B, GLFW_KEY_F12 },
				{ 0x7C, GLFW_KEY_F13 },
				{ 0x7D, GLFW_KEY_F14 },
				{ 0x7E, GLFW_KEY_F15 },
				{ 0x7F, GLFW_KEY_F16 },
				{ 0x80, GLFW_KEY_F17 },
				{ 0x81, GLFW_KEY_F18 },
				{ 0x82, GLFW_KEY_F19 },
				{ 0x83, GLFW_KEY_F20 },
				{ 0x84, GLFW_KEY_F21 },
				{ 0x85, GLFW_KEY_F22 },
				{ 0x86, GLFW_KEY_F23 },
				{ 0x87, GLFW_KEY_F24 },
				{ 0x90, GLFW_KEY_NUM_LOCK },
				{ 0xA0, GLFW_KEY_LEFT_SHIFT },
				{ 0xA1, GLFW_KEY_RIGHT_SHIFT },
				{ 0xA2, GLFW_KEY_LEFT_CONTROL },
				{ 0xA3, GLFW_KEY_RIGHT_CONTROL },
				{ 0xA4, GLFW_KEY_LEFT_ALT },
				{ 0xA5, GLFW_KEY_RIGHT_ALT },
				{ 0xB0, 0 }, // media next track
				{ 0xB1, 0 }, // media previous track
				{ 0xB2, 0 }, // media stop
				{ 0xB3, 0 }, // media play/pause
				{ 0xBA, GLFW_KEY_APOSTROPHE }, // ? [Siv3D TODO]
				{ 0xBB, GLFW_KEY_SEMICOLON }, // ? [Siv3D TODO]
				{ 0xBC, GLFW_KEY_COMMA },
				{ 0xBD, GLFW_KEY_MINUS },
				{ 0xBE, GLFW_KEY_PERIOD },
				{ 0xBF, GLFW_KEY_SLASH },
				{ 0xC0, GLFW_KEY_GRAVE_ACCENT }, // ? [Siv3D TODO]
				{ 0xD8, 0 }, // command
				{ 0xD9, GLFW_KEY_LEFT_SUPER },
				{ 0xDA, GLFW_KEY_RIGHT_SUPER },
				{ 0xDB, GLFW_KEY_LEFT_BRACKET }, // ? [Siv3D TODO]
				{ 0xDC, GLFW_KEY_BACKSLASH }, // ? [Siv3D TODO]
				//{ 0xDC, SIV3D_KEY_JIS_YEN }, // ¥ (JIS)
				{ 0xDD, GLFW_KEY_RIGHT_BRACKET }, // ? [Siv3D TODO]
				{ 0xDE, 0 }, // ? [Siv3D TODO]
				{ 0xE2, SIV3D_KEY_JIS_UNDERSCORE }, // _ (JIS)
			};

			__attribute__((import_name("siv3dGetURLParameters")))
			extern char **siv3dGetURLParameters();

			__attribute__((import_name("siv3dAddAllowedKeyBinding")))
			void siv3dAddAllowedKeyBinding(uint16 keyCode, bool ctrlKey, bool shiftKey, bool altKey, bool metaKey, bool allowed);

			__attribute__((import_name("siv3dDisableAllKeyBindings")))
			void siv3dDisableAllKeyBindings(bool disabled);
		}

		HashTable<String, String> GetURLParameters()
		{
			int paramReadPos = 0;
			auto params = detail::siv3dGetURLParameters();

			HashTable<String, String> result;

			while (params[paramReadPos] != nullptr)
			{
				auto keyCStr = params[paramReadPos++];
				auto valueCStr = params[paramReadPos++];

				auto key = Unicode::FromUTF8(keyCStr);
				auto value = Unicode::FromUTF8(valueCStr);

				result.emplace(key, value);

				::free(keyCStr);
				::free(valueCStr);
			}
			
			::free(params);

			return result;
		}

		void DisbaleBrowserKeyboardShortcuts(const Array<BrowserKeyboardShorcut>& allowList)
		{
			for (auto [ key, modifier ] : allowList)
			{
				if (key.deviceType() != InputDeviceType::Keyboard) 
				{
					continue;
				}

				const auto ctrlKey = static_cast<bool>(FromEnum(modifier) & FromEnum(KeyModifier::Control));
				const auto shiftKey = static_cast<bool>(FromEnum(modifier) & FromEnum(KeyModifier::Shift));

				if (const auto& code = detail::KeyConversionTable.find(key.code()); code != detail::KeyConversionTable.end())
				{
					detail::siv3dAddAllowedKeyBinding(code->second, ctrlKey, shiftKey, false, false, true);
				}
			}

			detail::siv3dDisableAllKeyBindings(true);
		}
	}
}
