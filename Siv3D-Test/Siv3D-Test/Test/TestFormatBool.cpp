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

# include "Siv3DTest.hpp"

using namespace s3d;

void TestFormatBool()
{
	Log(L"### FormatBool");
	Log(L"###### ToString");
	Log(ToString(true, LetterCase::Lower));
	Log(ToString(true, LetterCase::Upper));
	Log(ToString(true, LetterCase::Capitalized));
	Log(ToString(false, LetterCase::Lower));
	Log(ToString(false, LetterCase::Upper));
	Log(ToString(false, LetterCase::Capitalized));
}
