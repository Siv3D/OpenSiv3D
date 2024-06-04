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

# include <Siv3D/System.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Error.hpp>
# include <Siv3D/Unicode.hpp>
# include <emscripten.h>

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

		bool IsRunningInVisualStudio()
		{
			return false;
		}

		bool IsRunningInXcode()
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
	}
}

EMSCRIPTEN_KEEPALIVE
extern "C" void siv3dThrowException(const char* text)
{
	throw s3d::EngineError(s3d::Unicode::FromUTF8(text));
}
