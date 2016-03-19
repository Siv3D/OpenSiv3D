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
# include <string>
# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include <Siv3D.hpp>

class RDTSC
{
private:

	s3d::uint64 begin;

public:

	RDTSC()
		: begin(__rdtsc()) {}

	~RDTSC()
	{
		const auto result = __rdtsc() - begin;

		::OutputDebugStringW((std::to_wstring(result) + L" cycles\n").c_str());
	}
};

inline void Println(const s3d::String& s)
{
	::OutputDebugStringW((s + L"\n").c_str());
}

inline void Println(const s3d::wchar* s)
{
	::OutputDebugStringW(s);
	::OutputDebugStringW(L"\n");
}


inline void Println(bool b)
{
	::OutputDebugStringW(b ? L"true\n" : L"false\n");
}

inline void InitTest()
{
	__rdtsc();
}

void TestTypes();
void TestArray();
//void TestString();

inline void TestAll()
{
	InitTest();
	TestTypes();
	TestArray();
}
