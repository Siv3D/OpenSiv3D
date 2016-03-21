
# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"

using namespace s3d;

void Main()
{
	//TestAll();
	//::OutputDebugStringW(L"Siv3D!\n");

	///*
	Println(Format(2.34, 100, uint8(23), 5.f, true, String(L"aaa")));
	Println(Format(100, uint8(23), 5.f, true, String(L"aaa"), 2.34));
	Println(Format(100, uint16(23), 5.f, true, String(L"aaa"), 2.34));
	//*/

	/*
	Println(Format2(2.34, 100, uint8(23), 5.f, true, L"aaa"));
	Println(Format2(100, uint8(23), 5.f, true, L"aaa", 2.34));
	Println(Format2(100, uint16(23), 5.f, true, L"aaa", 2.34));
	//*/
}


