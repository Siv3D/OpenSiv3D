//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "CSoundFont.hpp"
# include <Siv3D/SoundFont.hpp>
# include <Siv3D/Wave.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Compression.hpp>
# include <Siv3D/Resource.hpp>
# include <Siv3D/Logger.hpp>
# include "../EngineDirectory/EngineDirectory.hpp"

namespace s3d
{
	CSoundFont::CSoundFont()
	{
		
	}

	CSoundFont::~CSoundFont()
	{
		if (m_standardSoundFont)
		{
			::tsf_close(m_standardSoundFont);
		}
	}

	bool CSoundFont::init()
	{
		if (m_standardSoundFont)
		{
			return true;
		}

		if (m_unavailable)
		{
			return false;
		}

		const String soundFontName = U"GMGSx.sf2";
		const FilePath soundFontDirectory = EngineDirectory::CurrectVersionCommon() + U"soundfont/";
		const FilePath soundFontResourcePath = Resource(U"engine/soundfont/" + soundFontName + U".zst");

		if (!FileSystem::Exists(soundFontDirectory + soundFontName)
			&& FileSystem::Exists(soundFontResourcePath))
		{
			if (!Compression::DecompressFileToFile(soundFontResourcePath, soundFontDirectory + soundFontName))
			{
				LOG_FAIL(U"❌ Failed to decompress standard soundfont");
			}
		}

		m_standardSoundFont = ::tsf_load_filename((soundFontDirectory + soundFontName).narrow().c_str());

		if (!m_standardSoundFont)
		{
			m_unavailable = true;

			return false;
		}

		LOG_INFO(U"ℹ️ SoundFont initialized");

		return true;
	}

	void CSoundFont::render(Wave& wave, size_t samples, const uint32 samplingRate, const uint8 instrument, const uint8 key, const double velocity)
	{
		if (!wave)
		{
			return;
		}

		if (!m_standardSoundFont)
		{
			if (!init())
			{
				return;
			}
		}

		::tsf_set_output(m_standardSoundFont, TSF_STEREO_INTERLEAVED, samplingRate, 0);

		::tsf_note_on(m_standardSoundFont, instrument, key, static_cast<float>(velocity));

		samples = std::min(samples, wave.size());

		::tsf_render_float(m_standardSoundFont, &wave[0].left, static_cast<int32>(samples), 0);

		::tsf_note_off(m_standardSoundFont, instrument, key);

		if (const size_t rest = wave.size() - samples)
		{
			::tsf_render_float(m_standardSoundFont, &wave[samples].left, static_cast<int32>(rest), 0);
		}

		::tsf_reset(m_standardSoundFont);
	}
}
