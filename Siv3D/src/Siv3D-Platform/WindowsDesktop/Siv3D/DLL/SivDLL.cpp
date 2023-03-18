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

# include <Siv3D/DLL.hpp>
# include <Siv3D/Error.hpp>
# include <Siv3D/FormatLiteral.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	namespace DLL
	{
		LibraryHandle LoadSystemLibraryNoThrow(const wchar_t* library)
		{
			LOG_TRACE(U"DLL::LoadSystemLibraryNoThrow(\"{}\")"_fmt(Unicode::FromWstring(library)));

			return ::LoadLibraryExW(library, nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
		}

		LibraryHandle LoadSystemLibrary(const wchar_t* library)
		{
			LOG_TRACE(U"DLL::LoadSystemLibrary(\"{}\")"_fmt(Unicode::FromWstring(library)));

			const LibraryHandle hModule = ::LoadLibraryExW(library, nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);

			if (not hModule)
			{
				throw EngineError{ U"Failed to load `{}`"_fmt(Unicode::FromWstring(library)) };
			}

			return hModule;
		}

		LibraryHandle Load(const StringView path)
		{
			LOG_TRACE(U"DLL::Load(\"path = `{}`\")"_fmt(path));

			return ::LoadLibraryW(path.toWstr().c_str());
		}

		void Unload(LibraryHandle& library)
		{
			if (not library)
			{
				return;
			}
			
			::FreeLibrary(library);
				
			library = nullptr;
		}

		GetFunctionNoThrow::GetFunctionNoThrow(LibraryHandle _module, const char* name)
			: p{ static_cast<const void*>(::GetProcAddress(_module, name)) }
		{
			LOG_TRACE(U"DLL::GetFunctionNoThrow::GetFunctionNoThrow(name = \"{}\") p = {}"_fmt(Unicode::Widen(name), p));
		}

		GetFunction::GetFunction(LibraryHandle _module, const char* name)
			: p(static_cast<const void*>(::GetProcAddress(_module, name)))
		{
			LOG_TRACE(U"DLL::GetFunction::GetFunction(name = \"{}\") p = {}"_fmt(Unicode::Widen(name), p));

			if (not p)
			{
				throw EngineError{ U"Failed to get function: `{}`"_fmt(Unicode::Widen(name)) };
			}
		}
	}
}
