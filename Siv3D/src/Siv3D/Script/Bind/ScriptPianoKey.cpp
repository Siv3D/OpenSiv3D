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

# include <Siv3D/Script.hpp>
# include <Siv3D/PianoKey.hpp>

namespace s3d
{
	using namespace AngelScript;

	void RegisterPianoKey(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;
		{
			constexpr char EnumName[] = "PianoKey";
			r = engine->RegisterEnumValue(EnumName, "C_1", PianoKey::C_1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "CS_1", PianoKey::CS_1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "DF_1", PianoKey::DF_1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "D_1", PianoKey::D_1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "DS_1", PianoKey::DS_1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "EF_1", PianoKey::EF_1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "E_1", PianoKey::E_1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "FF_1", PianoKey::FF_1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "F_1", PianoKey::F_1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "ES_1", PianoKey::ES_1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "FS_1", PianoKey::FS_1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "GF_1", PianoKey::GF_1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "G_1", PianoKey::G_1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "GS_1", PianoKey::GS_1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "AF_1", PianoKey::AF_1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "A_1", PianoKey::A_1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "AS_1", PianoKey::AS_1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "BF_1", PianoKey::BF_1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "B_1", PianoKey::B_1); assert(r >= 0);

			r = engine->RegisterEnumValue(EnumName, "C0", PianoKey::C0); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "CS0", PianoKey::CS0); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "DF0", PianoKey::DF0); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "D0", PianoKey::D0); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "DS0", PianoKey::DS0); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "EF0", PianoKey::EF0); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "E0", PianoKey::E0); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "FF0", PianoKey::FF0); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "F0", PianoKey::F0); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "ES0", PianoKey::ES0); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "FS0", PianoKey::FS0); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "GF0", PianoKey::GF0); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "G0", PianoKey::G0); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "GS0", PianoKey::GS0); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "AF0", PianoKey::AF0); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "A0", PianoKey::A0); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "AS0", PianoKey::AS0); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "BF0", PianoKey::BF0); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "B0", PianoKey::B0); assert(r >= 0);

			r = engine->RegisterEnumValue(EnumName, "C1", PianoKey::C1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "CS1", PianoKey::CS1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "DF1", PianoKey::DF1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "D1", PianoKey::D1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "DS1", PianoKey::DS1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "EF1", PianoKey::EF1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "E1", PianoKey::E1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "FF1", PianoKey::FF1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "F1", PianoKey::F1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "ES1", PianoKey::ES1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "FS1", PianoKey::FS1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "GF1", PianoKey::GF1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "G1", PianoKey::G1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "GS1", PianoKey::GS1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "AF1", PianoKey::AF1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "A1", PianoKey::A1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "AS1", PianoKey::AS1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "BF1", PianoKey::BF1); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "B1", PianoKey::B1); assert(r >= 0);

			r = engine->RegisterEnumValue(EnumName, "C2", PianoKey::C2); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "CS2", PianoKey::CS2); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "DF2", PianoKey::DF2); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "D2", PianoKey::D2); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "DS2", PianoKey::DS2); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "EF2", PianoKey::EF2); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "E2", PianoKey::E2); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "FF2", PianoKey::FF2); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "F2", PianoKey::F2); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "ES2", PianoKey::ES2); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "FS2", PianoKey::FS2); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "GF2", PianoKey::GF2); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "G2", PianoKey::G2); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "GS2", PianoKey::GS2); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "AF2", PianoKey::AF2); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "A2", PianoKey::A2); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "AS2", PianoKey::AS2); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "BF2", PianoKey::BF2); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "B2", PianoKey::B2); assert(r >= 0);

			r = engine->RegisterEnumValue(EnumName, "C3", PianoKey::C3); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "CS3", PianoKey::CS3); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "DF3", PianoKey::DF3); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "D3", PianoKey::D3); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "DS3", PianoKey::DS3); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "EF3", PianoKey::EF3); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "E3", PianoKey::E3); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "FF3", PianoKey::FF3); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "F3", PianoKey::F3); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "ES3", PianoKey::ES3); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "FS3", PianoKey::FS3); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "GF3", PianoKey::GF3); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "G3", PianoKey::G3); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "GS3", PianoKey::GS3); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "AF3", PianoKey::AF3); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "A3", PianoKey::A3); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "AS3", PianoKey::AS3); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "BF3", PianoKey::BF3); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "B3", PianoKey::B3); assert(r >= 0);

			r = engine->RegisterEnumValue(EnumName, "C4", PianoKey::C4); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "CS4", PianoKey::CS4); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "DF4", PianoKey::DF4); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "D4", PianoKey::D4); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "DS4", PianoKey::DS4); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "EF4", PianoKey::EF4); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "E4", PianoKey::E4); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "FF4", PianoKey::FF4); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "F4", PianoKey::F4); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "ES4", PianoKey::ES4); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "FS4", PianoKey::FS4); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "GF4", PianoKey::GF4); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "G4", PianoKey::G4); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "GS4", PianoKey::GS4); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "AF4", PianoKey::AF4); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "A4", PianoKey::A4); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "AS4", PianoKey::AS4); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "BF4", PianoKey::BF4); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "B4", PianoKey::B4); assert(r >= 0);

			r = engine->RegisterEnumValue(EnumName, "C5", PianoKey::C5); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "CS5", PianoKey::CS5); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "DF5", PianoKey::DF5); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "D5", PianoKey::D5); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "DS5", PianoKey::DS5); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "EF5", PianoKey::EF5); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "E5", PianoKey::E5); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "FF5", PianoKey::FF5); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "F5", PianoKey::F5); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "ES5", PianoKey::ES5); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "FS5", PianoKey::FS5); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "GF5", PianoKey::GF5); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "G5", PianoKey::G5); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "GS5", PianoKey::GS5); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "AF5", PianoKey::AF5); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "A5", PianoKey::A5); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "AS5", PianoKey::AS5); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "BF5", PianoKey::BF5); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "B5", PianoKey::B5); assert(r >= 0);

			r = engine->RegisterEnumValue(EnumName, "C6", PianoKey::C6); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "CS6", PianoKey::CS6); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "DF6", PianoKey::DF6); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "D6", PianoKey::D6); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "DS6", PianoKey::DS6); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "EF6", PianoKey::EF6); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "E6", PianoKey::E6); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "FF6", PianoKey::FF6); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "F6", PianoKey::F6); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "ES6", PianoKey::ES6); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "FS6", PianoKey::FS6); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "GF6", PianoKey::GF6); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "G6", PianoKey::G6); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "GS6", PianoKey::GS6); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "AF6", PianoKey::AF6); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "A6", PianoKey::A6); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "AS6", PianoKey::AS6); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "BF6", PianoKey::BF6); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "B6", PianoKey::B6); assert(r >= 0);

			r = engine->RegisterEnumValue(EnumName, "C7", PianoKey::C7); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "CS7", PianoKey::CS7); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "DF7", PianoKey::DF7); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "D7", PianoKey::D7); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "DS7", PianoKey::DS7); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "EF7", PianoKey::EF7); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "E7", PianoKey::E7); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "FF7", PianoKey::FF7); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "F7", PianoKey::F7); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "ES7", PianoKey::ES7); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "FS7", PianoKey::FS7); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "GF7", PianoKey::GF7); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "G7", PianoKey::G7); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "GS7", PianoKey::GS7); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "AF7", PianoKey::AF7); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "A7", PianoKey::A7); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "AS7", PianoKey::AS7); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "BF7", PianoKey::BF7); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "B7", PianoKey::B7); assert(r >= 0);

			r = engine->RegisterEnumValue(EnumName, "C8", PianoKey::C8); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "CS8", PianoKey::CS8); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "DF8", PianoKey::DF8); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "D8", PianoKey::D8); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "DS8", PianoKey::DS8); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "EF8", PianoKey::EF8); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "E8", PianoKey::E8); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "FF8", PianoKey::FF8); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "F8", PianoKey::F8); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "ES8", PianoKey::ES8); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "FS8", PianoKey::FS8); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "GF8", PianoKey::GF8); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "G8", PianoKey::G8); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "GS8", PianoKey::GS8); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "AF8", PianoKey::AF8); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "A8", PianoKey::A8); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "AS8", PianoKey::AS8); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "BF8", PianoKey::BF8); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "B8", PianoKey::B8); assert(r >= 0);

			r = engine->RegisterEnumValue(EnumName, "C9", PianoKey::C9); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "CS9", PianoKey::CS9); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "DF9", PianoKey::DF9); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "D9", PianoKey::D9); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "DS9", PianoKey::DS9); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "EF9", PianoKey::EF9); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "E9", PianoKey::E9); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "FF9", PianoKey::FF9); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "F9", PianoKey::F9); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "ES9", PianoKey::ES9); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "FS9", PianoKey::FS9); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "GF9", PianoKey::GF9); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "G9", PianoKey::G9); assert(r >= 0);	
		}
	}
}
