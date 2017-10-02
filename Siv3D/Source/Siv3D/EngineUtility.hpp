//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Platform.hpp>

# if defined(SIV3D_TARGET_WINDOWS) && defined(_WINBASE_)

namespace s3d
{
	struct FunctionPointer
	{
		FunctionPointer(HMODULE module, const char* name)
			: p(::GetProcAddress(module, name)) {}

		template <class Type>
		operator Type() const { return static_cast<Type>(p); }

		void* p;
	};
}

# endif


# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include <dlfcn.h>

namespace s3d
{
	struct FunctionPointer
	{
		FunctionPointer(void* module, const char* name)
		: p(dlsym(module, name)) {}
		
		template <class Type>
		operator Type() const { return reinterpret_cast<Type>(p); }
		
		void* p;
	};
}

# endif
