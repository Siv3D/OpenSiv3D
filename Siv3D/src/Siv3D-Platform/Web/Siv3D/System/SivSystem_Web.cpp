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

# include <Siv3D/System.hpp>
# include <Siv3D/FileSystem.hpp>
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

			__attribute__((import_name("siv3dGetURLParameters")))
			extern char **siv3dGetURLParameters();
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
	}
}
