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

# include "CSoundFont.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Compression.hpp>
# include <Siv3D/Resource.hpp>
# include <Siv3D/CacheDirectory/CacheDirectory.hpp>

namespace s3d
{
	namespace detail
	{
		// 実行ファイルに同梱されている、圧縮済みフォントファイルをキャッシュフォルダに展開する。
		// キャッシュフォルダに展開済みのフォントがある場合はスキップ。
		bool ExtractEngineSoundFonts()
		{
			LOG_SCOPED_TRACE(U"detail::ExtractEngineSoundFonts()");

			const FilePath soundfontCacheDirectory = CacheDirectory::Engine() + U"soundfont/";

			LOG_INFO(U"soundfontCacheDirectory: " + soundfontCacheDirectory);

			{
				const FilePath name = U"GMGSx.sf2";
				const FilePath cachedSoundFontPath = (soundfontCacheDirectory + name);
				const bool existsInCache = FileSystem::Exists(cachedSoundFontPath);

				// 展開済みのフォントがある場合はスキップ
				if (existsInCache)
				{
					LOG_INFO(U"ℹ️ Engine font `{0}` found in the user cache directory"_fmt(name));
					return true;
				}

				const FilePath fontResourcePath = Resource(U"engine/soundfont/" + name + U".zstdcmp");
				const bool existsInResource = FileSystem::Exists(fontResourcePath);

				if (not existsInResource)
				{
					LOG_INFO(U"Engine soundfont `{0}` not found"_fmt(fontResourcePath));
					return false;
				}

				// フォントファイルの展開に失敗したらエラー
				if (not Compression::DecompressFileToFile(fontResourcePath, cachedSoundFontPath))
				{
					LOG_ERROR(U"✖ Engine font `{0}` decompression failed"_fmt(name));
					FileSystem::Remove(cachedSoundFontPath);
					return false;
				}
			}

			return true;
		}
	}

	CSoundFont::CSoundFont()
	{

	}

	CSoundFont::~CSoundFont()
	{
		LOG_SCOPED_TRACE(U"CSoundFont::~CSoundFont()");
	}

	void CSoundFont::init()
	{
		LOG_SCOPED_TRACE(U"CSoundFont::init()");

		// エンジンサウンドフォントの展開
		{
			m_hasGMGSx = detail::ExtractEngineSoundFonts();
		}
	}

	Wave CSoundFont::render(const GMInstrument instrument, const uint8 key, const Duration& noteOn, const Duration& noteOff, const double velocity, const Arg::sampleRate_<uint32> sampleRate)
	{
		if (not m_hasGMGSx)
		{
			return{};
		}

		const FilePath standardSoundFont = CacheDirectory::Engine() + U"soundfont/GMGSx.sf2";

		SoundFont soundFont{ standardSoundFont };

		if (not soundFont)
		{
			return{};
		}

		return soundFont.render(instrument, key, noteOn, noteOff, velocity, sampleRate);
	}

	Wave CSoundFont::renderMIDI(const FilePathView path, std::array<Array<MIDINote>, 16>& midiScore, const Arg::sampleRate_<uint32> sampleRate, const Duration& tail)
	{
		if (not m_hasGMGSx)
		{
			return{};
		}

		const FilePath standardSoundFont = CacheDirectory::Engine() + U"soundfont/GMGSx.sf2";

		SoundFont soundFont{ standardSoundFont };

		if (not soundFont)
		{
			return{};
		}

		return soundFont.renderMIDI(path, midiScore, tail, sampleRate);
	}

	Wave CSoundFont::renderMIDI(IReader& reader, std::array<Array<MIDINote>, 16>& midiScore, const Arg::sampleRate_<uint32> sampleRate, const Duration& tail)
	{
		if (not m_hasGMGSx)
		{
			return{};
		}

		const FilePath standardSoundFont = CacheDirectory::Engine() + U"soundfont/GMGSx.sf2";

		SoundFont soundFont{ standardSoundFont };

		if (not soundFont)
		{
			return{};
		}

		return soundFont.renderMIDI(reader, midiScore, tail, sampleRate);
	}
}
