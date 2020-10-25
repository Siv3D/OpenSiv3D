﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"

# if SIV3D_PLATFORM(WINDOWS)

# include <Siv3D/Windows/Windows.hpp>

namespace s3d
{
	namespace DLL
	{
		[[nodiscard]]
		HMODULE LoadSystemLibraryNoThrow(const wchar_t* library);

		[[nodiscard]]
		HMODULE LoadSystemLibrary(const wchar_t* library);

		void UnloadSystemLibrary(HMODULE& library);

		class GetFunctionNoThrow
		{
		private:

			const void* p;

		public:

			SIV3D_NODISCARD_CXX20
			GetFunctionNoThrow(HMODULE _module, const char* name);

			template <class Type>
			operator Type() const noexcept
			{
				return static_cast<Type>(p);
			}
		};

		class GetFunction
		{
		private:

			const void* p;

		public:

			SIV3D_NODISCARD_CXX20
			GetFunction(HMODULE _module, const char* name);

			template <class Type>
			operator Type() const noexcept
			{
				return static_cast<Type>(p);
			}
		};
	}
}

# endif

# if SIV3D_PLATFORM(MACOS) || SIV3D_PLATFORM(LINUX)

# include <dlfcn.h>

namespace s3d
{
	namespace DLL
	{
		[[nodiscard]]
		void* LoadLibrary(const char* path);

		class GetFunctionNoThrow
		{
		private:

			const void* p;

		public:

			SIV3D_NODISCARD_CXX20
			GetFunctionNoThrow(void* _module, const char* name);

			template <class Type>
			operator Type() const noexcept
			{
				return static_cast<Type>(p);
			}
		};

		class GetFunction
		{
		private:

			const void* p;

		public:

			SIV3D_NODISCARD_CXX20
			GetFunction(void* _module, const char* name);

			template <class Type>
			operator Type() const noexcept
			{
				return static_cast<Type>(p);
			}
		};
	}
}

# endif