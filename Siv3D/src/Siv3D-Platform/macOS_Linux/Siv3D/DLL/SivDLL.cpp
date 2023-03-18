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
# include <Siv3D/Unicode.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Format.hpp>

namespace s3d
{
	namespace DLL
	{
		LibraryHandle Load(const StringView path)
		{
			LOG_TRACE(U"DLL::Load(path = `{}`)"_fmt(path));

			return ::dlopen(path.narrow().c_str(), RTLD_LOCAL | RTLD_LAZY);
		}
	
		void Unload(LibraryHandle& library)
		{
			LOG_TRACE(U"DLL::Unload()");
			
			if (library)
			{
				::dlclose(library);
			}
			
			library = nullptr;
		}

		GetFunctionNoThrow::GetFunctionNoThrow(LibraryHandle module, const char* name)
			: p{ reinterpret_cast<void*>(::dlsym(module, name)) }
		{
			LOG_TRACE(U"DLL::GetFunctionNoThrow::GetFunctionNoThrow(name = `{}`) p = {}"_fmt(Unicode::Widen(name), p));
		}

		GetFunction::GetFunction(LibraryHandle module, const char* name)
			: p{ reinterpret_cast<void*>(::dlsym(module, name)) }
		{
			LOG_TRACE(U"DLL::GetFunction::GetFunction(name = `{}`) p = {}"_fmt(Unicode::Widen(name), p));

			if (not p)
			{
				throw EngineError{ U"Failed to get function: `{}`"_fmt(Unicode::Widen(name)) };
			}
		}
	}
}
