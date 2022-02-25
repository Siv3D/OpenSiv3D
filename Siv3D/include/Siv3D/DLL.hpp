//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
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
	using LibraryHandle = HMODULE;

	namespace DLL
	{
		[[nodiscard]]
		LibraryHandle LoadSystemLibraryNoThrow(const wchar_t* library);

		[[nodiscard]]
		LibraryHandle LoadSystemLibrary(const wchar_t* library);

		[[nodiscard]]
		LibraryHandle Load(StringView path);

		void Unload(LibraryHandle& library);

		class GetFunctionNoThrow
		{
		public:

			SIV3D_NODISCARD_CXX20
			GetFunctionNoThrow(LibraryHandle _module, const char* name);

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
			GetFunction(LibraryHandle _module, const char* name);

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

# if SIV3D_PLATFORM(MACOS) || SIV3D_PLATFORM(LINUX) || SIV3D_PLATFORM(WEB)

# include <dlfcn.h>

namespace s3d
{
	using LibraryHandle = void*;

	namespace DLL
	{
		[[nodiscard]]
		LibraryHandle Load(StringView path);
	
		void Unload(LibraryHandle& library);

		class GetFunctionNoThrow
		{
		public:

			SIV3D_NODISCARD_CXX20
			GetFunctionNoThrow(LibraryHandle _module, const char* name);

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
			GetFunction(LibraryHandle _module, const char* name);

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
