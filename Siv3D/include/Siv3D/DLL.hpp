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

# pragma once
# include "Common.hpp"
# include "StringView.hpp"

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

		[[nodiscard]]
		HMODULE Load(StringView path);

		void Unload(HMODULE& library);

		class GetFunctionNoThrow
		{
		public:

			SIV3D_NODISCARD_CXX20
			GetFunctionNoThrow(HMODULE _module, const char* name);

			template <class Type>
			operator Type() const noexcept
			{
				return static_cast<Type>(p);
			}

		private:

			const void* p;
		};

		class GetFunction
		{
		public:

			SIV3D_NODISCARD_CXX20
			GetFunction(HMODULE _module, const char* name);

			template <class Type>
			operator Type() const noexcept
			{
				return static_cast<Type>(p);
			}

		private:

			const void* p;
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
		void* Load(StringVire path);
	
		void Unload(void* library);

		class GetFunctionNoThrow
		{
		public:

			SIV3D_NODISCARD_CXX20
			GetFunctionNoThrow(void* _module, const char* name);

			template <class Type>
			operator Type() const noexcept
			{
				return reinterpret_cast<Type>(p);
			}

		private:

			void* p;
		};

		class GetFunction
		{
		public:

			SIV3D_NODISCARD_CXX20
			GetFunction(void* _module, const char* name);

			template <class Type>
			operator Type() const noexcept
			{
				return reinterpret_cast<Type>(p);
			}

		private:

			void* p;
		};
	}
}

# endif
