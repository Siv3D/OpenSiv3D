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

# include <Siv3D/Windows.hpp>
# include <Siv3D/DLL.hpp>
# include <Siv3D/EngineError.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/Format.hpp>

namespace s3d
{
	namespace DLL
	{
		HMODULE LoadSystemLibrary(const wchar_t* library)
		{
			LOG_TRACE(U"DLL::LoadSystemLibrary(library = `{}`)"_fmt(Unicode::FromWString(library)));

			return ::LoadLibraryExW(library, nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
		}

		GetFunctionNoThrow::GetFunctionNoThrow(HMODULE module, const char* name)
			: p(reinterpret_cast<void*>(::GetProcAddress(module, name)))
		{
			LOG_TRACE(U"DLL::GetFunctionNoThrow::GetFunctionNoThrow(name = `{}`) p = {}"_fmt(Unicode::Widen(name), p));
		}

		GetFunction::GetFunction(HMODULE module, const char* name)
			: p(reinterpret_cast<void*>(::GetProcAddress(module, name)))
		{
			LOG_TRACE(U"DLL::GetFunction::GetFunction(name = `{}`) p = {}"_fmt(Unicode::Widen(name), p));

			if (!p)
			{
				throw EngineError(U"Failed to get function: `{}`"_fmt(Unicode::Widen(name)));
			}
		}
	}
}
