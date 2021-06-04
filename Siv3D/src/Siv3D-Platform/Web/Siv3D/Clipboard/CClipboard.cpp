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
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include "CClipboard.hpp"

namespace s3d
{
	namespace detail
	{
		__attribute__((import_name("siv3dSetClipboardText")))
		extern void siv3dSetClipboardText(const char* text);

		using siv3dGetClipboardTextCallBack = void(*)(char* text, void* promise);

		__attribute__((import_name("siv3dGetClipboardText")))
		extern void siv3dGetClipboardText(siv3dGetClipboardTextCallBack, void*);
	}

	CClipboard::CClipboard() {}

	CClipboard::~CClipboard()
	{
		LOG_SCOPED_TRACE(U"CClipboard::~CClipboard()");
	}

	void CClipboard::init()
	{
		LOG_SCOPED_TRACE(U"CClipboard::init()");
	}

	bool CClipboard::hasChanged()
	{
		// [Siv3D ToDo]
		return false;
	}

	bool CClipboard::getText(String& text)
	{
		text.clear();

		// [Siv3D ToDo]
		
		return (not text.isEmpty());
	}

	bool CClipboard::getImage(Image& image)
	{
		image.clear();

		// [Siv3D ToDo]

		return (not image.isEmpty());
	}

	bool CClipboard::getFilePaths(Array<FilePath>& paths)
	{
		paths.clear();

		// [Siv3D ToDo]

		return (not paths.isEmpty());
	}

	void CClipboard::setText(const String& text)
	{
		detail::siv3dSetClipboardText(text.narrow().c_str());
	}

	void CClipboard::setImage(const Image& image)
	{
		// [Siv3D ToDo]
	}

	void CClipboard::clear()
	{
		setText(U"");
	}

	void CClipboard::OnGetClipboardText(char* text, void* userData)
	{
		auto& clipboard = *static_cast<CClipboard*>(userData);

		if (text)
		{
			clipboard.m_clibboardTexts << Unicode::FromUTF8(text);
		}
	}

	namespace Platform::Web::Clipboard 
	{
		namespace detail
		{
			void OnGetClipboardText(char* text, void* userData)
			{
				auto promise = static_cast<std::promise<s3d::String>*>(userData);

				if (text)
				{
					promise->set_value(Unicode::Widen(text));
				}
				else
				{
					promise->set_value(U"");
				}
			}
		}

		std::future<String> GetText()
		{
			auto p = new std::promise<s3d::String>();
			auto result_future = p->get_future();

			s3d::detail::siv3dGetClipboardText(&detail::OnGetClipboardText, p);
			
			return result_future;
		}
	}
}
