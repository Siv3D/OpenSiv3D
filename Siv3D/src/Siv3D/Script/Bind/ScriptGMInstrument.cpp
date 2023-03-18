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
# include <Siv3D/GMInstrument.hpp>

namespace s3d
{
	using namespace AngelScript;

	void RegisterGMInstrument(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;
		{
			constexpr char EnumName[] = "GMInstrument";
			r = engine->RegisterEnumValue(EnumName, "Piano1", FromEnum(GMInstrument::Piano1)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Piano2", FromEnum(GMInstrument::Piano2)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Piano3", FromEnum(GMInstrument::Piano3)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Piano4", FromEnum(GMInstrument::Piano4)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "ElectricPiano1", FromEnum(GMInstrument::ElectricPiano1)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "ElectricPiano2", FromEnum(GMInstrument::ElectricPiano2)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Harpsichord", FromEnum(GMInstrument::Harpsichord)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Clavinet", FromEnum(GMInstrument::Clavinet)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Celesta", FromEnum(GMInstrument::Celesta)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Glockenspiel", FromEnum(GMInstrument::Glockenspiel)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "MusicBox", FromEnum(GMInstrument::MusicBox)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Vibraphone", FromEnum(GMInstrument::Vibraphone)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Marimba", FromEnum(GMInstrument::Marimba)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Xylophone", FromEnum(GMInstrument::Xylophone)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "TubularBells", FromEnum(GMInstrument::TubularBells)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Dulcimer", FromEnum(GMInstrument::Dulcimer)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "DrawbarOrgan", FromEnum(GMInstrument::DrawbarOrgan)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "PercussiveOrgan", FromEnum(GMInstrument::PercussiveOrgan)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "RockOrgan", FromEnum(GMInstrument::RockOrgan)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "ChurchOrgan", FromEnum(GMInstrument::ChurchOrgan)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "ReedOrgan", FromEnum(GMInstrument::ReedOrgan)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Accordion", FromEnum(GMInstrument::Accordion)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Harmonica", FromEnum(GMInstrument::Harmonica)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "TangoAccordion", FromEnum(GMInstrument::TangoAccordion)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "NylonGuitar", FromEnum(GMInstrument::NylonGuitar)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "SteelGuitar", FromEnum(GMInstrument::SteelGuitar)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "JazzGuitar", FromEnum(GMInstrument::JazzGuitar)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "CleanGuitar", FromEnum(GMInstrument::CleanGuitar)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "PianMutedGuitaro1", FromEnum(GMInstrument::MutedGuitar)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "OverdrivenGuitar", FromEnum(GMInstrument::OverdrivenGuitar)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "DistortionGuitar", FromEnum(GMInstrument::DistortionGuitar)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "GuitarHarmonics", FromEnum(GMInstrument::GuitarHarmonics)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "AcousticBass", FromEnum(GMInstrument::AcousticBass)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "FingeredBass", FromEnum(GMInstrument::FingeredBass)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "PickedBass", FromEnum(GMInstrument::PickedBass)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "FretlessBass", FromEnum(GMInstrument::FretlessBass)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "SlapBass1", FromEnum(GMInstrument::SlapBass1)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "SlapBass2", FromEnum(GMInstrument::SlapBass2)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "SynthBass1", FromEnum(GMInstrument::SynthBass1)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "SynthBass2", FromEnum(GMInstrument::SynthBass2)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Violin", FromEnum(GMInstrument::Violin)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Viola", FromEnum(GMInstrument::Viola)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Cello", FromEnum(GMInstrument::Cello)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Contrabass", FromEnum(GMInstrument::Contrabass)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "TremoloStrings", FromEnum(GMInstrument::TremoloStrings)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "PizzicatoStrings", FromEnum(GMInstrument::PizzicatoStrings)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "OrchestralHarp", FromEnum(GMInstrument::OrchestralHarp)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Timpani", FromEnum(GMInstrument::Timpani)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "StringEnsemble1", FromEnum(GMInstrument::StringEnsemble1)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "StringEnsemble2", FromEnum(GMInstrument::StringEnsemble2)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "SynthStrings1", FromEnum(GMInstrument::SynthStrings1)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "SynthStrings2", FromEnum(GMInstrument::SynthStrings2)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "ChoirAahs", FromEnum(GMInstrument::ChoirAahs)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "VoiceOohs", FromEnum(GMInstrument::VoiceOohs)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "SynthChoir", FromEnum(GMInstrument::SynthChoir)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "OrchestraHit", FromEnum(GMInstrument::OrchestraHit)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Trumpet", FromEnum(GMInstrument::Trumpet)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Trombone", FromEnum(GMInstrument::Trombone)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Tuba", FromEnum(GMInstrument::Tuba)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "MutedTrumpet", FromEnum(GMInstrument::MutedTrumpet)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "FrenchHorn", FromEnum(GMInstrument::FrenchHorn)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "BrassSection", FromEnum(GMInstrument::BrassSection)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "SynthBrass1", FromEnum(GMInstrument::SynthBrass1)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "SynthBrass2", FromEnum(GMInstrument::SynthBrass2)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "SopranoSax", FromEnum(GMInstrument::SopranoSax)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "AltoSax", FromEnum(GMInstrument::AltoSax)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "TenorSax", FromEnum(GMInstrument::TenorSax)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "BaritoneSax", FromEnum(GMInstrument::BaritoneSax)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Oboe", FromEnum(GMInstrument::Oboe)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "EnglishHorn", FromEnum(GMInstrument::EnglishHorn)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Bassoon", FromEnum(GMInstrument::Bassoon)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Clarinet", FromEnum(GMInstrument::Clarinet)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Piccolo", FromEnum(GMInstrument::Piccolo)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Flute", FromEnum(GMInstrument::Flute)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Recorder", FromEnum(GMInstrument::Recorder)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "PanFlute", FromEnum(GMInstrument::PanFlute)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Blownbottle", FromEnum(GMInstrument::Blownbottle)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Shakuhachi", FromEnum(GMInstrument::Shakuhachi)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Whistle", FromEnum(GMInstrument::Whistle)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "PiaOcarinano1", FromEnum(GMInstrument::Ocarina)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "SquareWave", FromEnum(GMInstrument::SquareWave)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "SawWave", FromEnum(GMInstrument::SawWave)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "SynCalliope", FromEnum(GMInstrument::SynCalliope)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "ChifferLead", FromEnum(GMInstrument::ChifferLead)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Charang", FromEnum(GMInstrument::Charang)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "SoloVox", FromEnum(GMInstrument::SoloVox)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "FifthSawWave", FromEnum(GMInstrument::FifthSawWave)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "BassAndLead", FromEnum(GMInstrument::BassAndLead)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Fantasia", FromEnum(GMInstrument::Fantasia)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "WarmPad", FromEnum(GMInstrument::WarmPad)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Polysynth", FromEnum(GMInstrument::Polysynth)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "SpaceVoice", FromEnum(GMInstrument::SpaceVoice)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "BowedGlass", FromEnum(GMInstrument::BowedGlass)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "MetalPad", FromEnum(GMInstrument::MetalPad)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "HaloPad", FromEnum(GMInstrument::HaloPad)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "SweepPad", FromEnum(GMInstrument::SweepPad)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "IceRain", FromEnum(GMInstrument::IceRain)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Soundtrack", FromEnum(GMInstrument::Soundtrack)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Crystal", FromEnum(GMInstrument::Crystal)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Atmosphere", FromEnum(GMInstrument::Atmosphere)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Brightness", FromEnum(GMInstrument::Brightness)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Goblin", FromEnum(GMInstrument::Goblin)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "EchoDrops", FromEnum(GMInstrument::EchoDrops)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "StarTheme", FromEnum(GMInstrument::StarTheme)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Sitar", FromEnum(GMInstrument::Sitar)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Banjo", FromEnum(GMInstrument::Banjo)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Shamisen", FromEnum(GMInstrument::Shamisen)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Koto", FromEnum(GMInstrument::Koto)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Kalimba", FromEnum(GMInstrument::Kalimba)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Bagpipe", FromEnum(GMInstrument::Bagpipe)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Fiddle", FromEnum(GMInstrument::Fiddle)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Shanai", FromEnum(GMInstrument::Shanai)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "TinkleBell", FromEnum(GMInstrument::TinkleBell)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Agogo", FromEnum(GMInstrument::Agogo)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "SteelDrums", FromEnum(GMInstrument::SteelDrums)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Woodblock", FromEnum(GMInstrument::Woodblock)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "TaikoDrum", FromEnum(GMInstrument::TaikoDrum)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "MelodicTom", FromEnum(GMInstrument::MelodicTom)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "SynthDrum", FromEnum(GMInstrument::SynthDrum)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "ReverseCymbal", FromEnum(GMInstrument::ReverseCymbal)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "GuitarFretNoise", FromEnum(GMInstrument::GuitarFretNoise)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "BreathNoise", FromEnum(GMInstrument::BreathNoise)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Seashore", FromEnum(GMInstrument::Seashore)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "BirdTweet", FromEnum(GMInstrument::BirdTweet)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "TelephoneRing", FromEnum(GMInstrument::TelephoneRing)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Helicopter", FromEnum(GMInstrument::Helicopter)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Applause", FromEnum(GMInstrument::Applause)); assert(r >= 0);
			r = engine->RegisterEnumValue(EnumName, "Gunshot", FromEnum(GMInstrument::Gunshot)); assert(r >= 0);
		}
	}
}
