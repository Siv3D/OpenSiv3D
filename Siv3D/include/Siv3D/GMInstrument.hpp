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

namespace s3d
{
	enum class GMInstrument : uint8
	{
		// Piano
		Piano1,
		Piano2,
		Piano3,
		Piano4,
		ElectricPiano1,
		ElectricPiano2,
		Harpsichord,
		Clavinet,

		// Chromatic Percussion
		Celesta,
		Glockenspiel,
		MusicBox,
		Vibraphone,
		Marimba,
		Xylophone,
		TubularBells,
		Dulcimer,

		// Organ
		DrawbarOrgan,
		PercussiveOrgan,
		RockOrgan,
		ChurchOrgan,
		ReedOrgan,
		Accordion,
		Harmonica,
		TangoAccordion,

		//Guitar
		NylonGuitar,
		SteelGuitar,
		JazzGuitar,
		CleanGuitar,
		MutedGuitar,
		OverdrivenGuitar,
		DistortionGuitar,
		GuitarHarmonics,

		// Bass
		AcousticBass,
		FingeredBass,
		PickedBass,
		FretlessBass,
		SlapBass1,
		SlapBass2,
		SynthBass1,
		SynthBass2,

		// Strings
		Violin,
		Viola,
		Cello,
		Contrabass,
		TremoloStrings,
		PizzicatoStrings,
		OrchestralHarp,
		Timpani,

		// Ensemble
		StringEnsemble1,
		StringEnsemble2,
		SynthStrings1,
		SynthStrings2,
		ChoirAahs,
		VoiceOohs,
		SynthChoir,
		OrchestraHit,

		// Brass
		Trumpet,
		Trombone,
		Tuba,
		MutedTrumpet,
		FrenchHorn,
		BrassSection,
		SynthBrass1,
		SynthBrass2,

		// Reed
		SopranoSax,
		AltoSax,
		TenorSax,
		BaritoneSax,
		Oboe,
		EnglishHorn,
		Bassoon,
		Clarinet,

		// Pipe
		Piccolo,
		Flute,
		Recorder,
		PanFlute,
		Blownbottle,
		Shakuhachi,
		Whistle,
		Ocarina,

		// Synth Lead
		SquareWave,
		SawWave,
		SynCalliope,
		ChifferLead,
		Charang,
		SoloVox,
		FifthSawWave,
		BassAndLead,

		// Synth Pad
		Fantasia,
		WarmPad,
		Polysynth,
		SpaceVoice,
		BowedGlass,
		MetalPad,
		HaloPad,
		SweepPad,

		// Synth Effects
		IceRain,
		Soundtrack,
		Crystal,
		Atmosphere,
		Brightness,
		Goblin,
		EchoDrops,
		StarTheme,

		// Ethnic
		Sitar,
		Banjo,
		Shamisen,
		Koto,
		Kalimba,
		Bagpipe,
		Fiddle,
		Shanai,

		// Percussive
		TinkleBell,
		Agogo,
		SteelDrums,
		Woodblock,
		TaikoDrum,
		MelodicTom,
		SynthDrum,
		ReverseCymbal,

		// Sound effects
		GuitarFretNoise,
		BreathNoise,
		Seashore,
		BirdTweet,
		TelephoneRing,
		Helicopter,
		Applause,
		Gunshot,
	};
}
