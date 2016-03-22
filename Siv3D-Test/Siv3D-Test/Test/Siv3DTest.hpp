//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D.hpp>

# if defined(SIV3D_TARGET_WINDOWS)
	# define  NOMINMAX
	# define  STRICT
	# define  WIN32_LEAN_AND_MEAN
	# define  _WIN32_WINNT _WIN32_WINNT_WIN7
	# define  NTDDI_VERSION NTDDI_WIN7
	# include <Windows.h>
# endif

namespace s3d
{
# if defined(SIV3D_TARGET_WINDOWS)
	class RDTSC
	{
	private:

		uint64 begin;

	public:

		RDTSC()
			: begin(__rdtsc()) {}

		~RDTSC()
		{
			const auto result = __rdtsc() - begin;

			::OutputDebugStringW((std::to_wstring(result) + L" cycles\n").c_str());
		}
	};
# endif

	inline void Log(const String& text)
	{
		# if defined(SIV3D_TARGET_WINDOWS)
			::OutputDebugStringW((text + L"\n").c_str());
		# else
			std::wcout << text << L'\n';
		# endif
	}

	template <class... Args>
	inline void Log(const Args&... args)
	{
		Log(Format(args...));
	}
}

inline void InitTest()
{
	# if defined(SIV3D_TARGET_WINDOWS)
		__rdtsc();
	# endif
}

void TestTypes();
void TestArray();
void TestOptional();
void TestString();
void TestFormatFloat();
void TestFormatInt();
void TestFormatBool();

inline void TestAll()
{
	InitTest();
	TestTypes();
	TestArray();
	TestOptional();
	TestString();
	TestFormatFloat();
	TestFormatInt();
	TestFormatBool();
}
