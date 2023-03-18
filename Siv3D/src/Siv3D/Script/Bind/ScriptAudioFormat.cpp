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
# include <Siv3D/AudioFormat.hpp>

namespace s3d
{
	using namespace AngelScript;

	void RegisterAudioFormat(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;
		{
			constexpr char TypeName[] = "AudioFormat";
			r = engine->RegisterEnumValue(TypeName, "Unknown", static_cast<int32>(AudioFormat::Unknown)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "WAVE", static_cast<int32>(AudioFormat::WAVE)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "MP3", static_cast<int32>(AudioFormat::MP3)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "AAC", static_cast<int32>(AudioFormat::AAC)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "OggVorbis", static_cast<int32>(AudioFormat::OggVorbis)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Opus", static_cast<int32>(AudioFormat::Opus)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "WMA", static_cast<int32>(AudioFormat::WMA)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "AIFF", static_cast<int32>(AudioFormat::AIFF)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "FLAC", static_cast<int32>(AudioFormat::FLAC)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "MIDI", static_cast<int32>(AudioFormat::MIDI)); assert(r >= 0);
			r = engine->RegisterEnumValue(TypeName, "Unspecified", static_cast<int32>(AudioFormat::Unspecified)); assert(r >= 0);
		}
	}
}
