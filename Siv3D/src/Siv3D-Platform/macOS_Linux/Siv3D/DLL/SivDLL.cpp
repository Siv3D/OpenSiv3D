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

# include <Siv3D/DLL.hpp>
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Format.hpp>

namespace s3d
{
	namespace DLL
	{
		void* Load(const StringVire path)
		{
			LOG_TRACE(U"DLL::Load(path = `{}`)"_fmt(path));

			return ::dlopen(path.narrow().c_str(), RTLD_LOCAL | RTLD_LAZY);
		}

		GetFunctionNoThrow::GetFunctionNoThrow(void* module, const char* name)
			: p{ reinterpret_cast<void*>(::dlsym(module, name)) }
		{
			LOG_TRACE(U"DLL::GetFunctionNoThrow::GetFunctionNoThrow(name = `{}`) p = {}"_fmt(Unicode::Widen(name), p));
		}

		GetFunction::GetFunction(void* module, const char* name)
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
