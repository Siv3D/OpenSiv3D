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
# include "String.hpp"
# include "Array.hpp"

namespace s3d
{
	/// @brief ファイル拡張子フィルタ
	struct FileFilter
	{
		/// @brief 名前
		String name;

		/// @brief 拡張子のパターン。空の場合はすべてのファイル
		Array<String> patterns;

		/// @brief BMP ファイル用の拡張子フィルタを返します。
		/// @return `FileFilter{ U"BMP",{ U"bmp" } }` 
		[[nodiscard]]
		static FileFilter BMP();

		/// @brief GIF ファイル用の拡張子フィルタを返します。
		/// @return `FileFilter{ U"GIF",{ U"gif" } }` 
		[[nodiscard]]
		static FileFilter GIF();

		/// @brief JPEG ファイル用の拡張子フィルタを返します。
		/// @return `FileFilter{ U"JPEG",{ U"jpg", U"jpeg" } }`
		[[nodiscard]]
		static FileFilter JPEG();

		/// @brief PNG ファイル用の拡張子フィルタを返します。
		/// @return `FileFilter{ U"PNG",{ U"png" } }`
		[[nodiscard]]
		static FileFilter PNG();

		/// @brief PPM ファイル用の拡張子フィルタを返します。
		/// @return `FileFilter{ U"PPM",{ U"ppm", U"pgm", U"pbm", U"pnm" } }`
		[[nodiscard]]
		static FileFilter PPM();

		/// @brief SVG ファイル用の拡張子フィルタを返します。
		/// @return `FileFilter{ U"SVG",{ U"svg" } }`
		[[nodiscard]]
		static FileFilter SVG();

		/// @brief TGA ファイル用の拡張子フィルタを返します。
		/// @return `FileFilter{ U"TGA",{ U"tga" } }`
		[[nodiscard]]
		static FileFilter TGA();

		/// @brief WebP ファイル用の拡張子フィルタを返します。
		/// @return `FileFilter{ U"WebP",{ U"webp" } }`
		[[nodiscard]]
		static FileFilter WebP();

		/// @brief すべての画像ファイル用の拡張子フィルタを返します。
		/// @return `FileFilter{ U"All Picture Files",{ U"png", U"jpg", U"jpeg", U"bmp", U"gif", U"tga", U"svg", U"webp", U"ppm", U"pgm", U"pbm", U"pnm" } }`
		[[nodiscard]]
		static FileFilter AllImageFiles();

		/// @brief AVI ファイル用の拡張子フィルタを返します。
		/// @return `FileFilter{ U"AVI",{ U"avi" } }`
		[[nodiscard]]
		static FileFilter AVI();

		/// @brief MP4 ファイル用の拡張子フィルタを返します。
		/// @return `FileFilter{ U"MP4",{ U"mp4" } }`
		[[nodiscard]]
		static FileFilter MP4();

		/// @brief WebM ファイル用の拡張子フィルタを返します。
		/// @return `FileFilter{ U"WebM",{ U"webm" } }`
		[[nodiscard]]
		static FileFilter WebM();

		/// @brief すべての動画ファイル用の拡張子フィルタを返します。
		/// @return `FileFilter{ U"All Video Files",{ U"avi", U"mp4", U"webm" } }`
		[[nodiscard]]
		static FileFilter AllVideoFiles();

		/// @brief AAC ファイル用の拡張子フィルタを返します。
		/// @return `FileFilter{ U"AAC",{ U"m4a" } }`
		[[nodiscard]]
		static FileFilter AAC();

		/// @brief AIFF ファイル用の拡張子フィルタを返します。
		/// @return `FileFilter{ U"AIFF",{ U"aif", U"aiff", U"aifc" } }`
		[[nodiscard]]
		static FileFilter AIFF();

		/// @brief FLAC ファイル用の拡張子フィルタを返します。
		/// @return `FileFilter{ U"FLAC",{ U"flac" } }`
		[[nodiscard]]
		static FileFilter FLAC();

		/// @brief MIDI ファイル用の拡張子フィルタを返します。
		/// @return `FileFilter{ U"MIDI",{ U"mid" } }`
		[[nodiscard]]
		static FileFilter MIDI();

		/// @brief MP3 ファイル用の拡張子フィルタを返します。
		/// @return `FileFilter{ U"MP3",{ U"mp3" } }`
		[[nodiscard]]
		static FileFilter MP3();

		/// @brief Ogg Vorbis ファイル用の拡張子フィルタを返します。
		/// @return `FileFilter{ U"Ogg Vorbis",{ U"ogg" } }`
		[[nodiscard]]
		static FileFilter OggVorbis();

		/// @brief Opus ファイル用の拡張子フィルタを返します。
		/// @return `FileFilter{ U"Opus",{ U"opus" } }`
		[[nodiscard]]
		static FileFilter Opus();

		/// @brief WAVE ファイル用の拡張子フィルタを返します。
		/// @return `FileFilter{ U"WAVE",{ U"wav" } }`
		[[nodiscard]]
		static FileFilter WAVE();

		/// @brief WMA ファイル用の拡張子フィルタを返します。
		/// @return `FileFilter{ U"WMA",{ U"wma" } }`
		[[nodiscard]]
		static FileFilter WMA();

		/// @brief すべてのオーディオファイル用の拡張子フィルタを返します。
		/// @return `FileFilter{ U"All Audio Files",{ U"wav", U"mp3", U"m4a", U"ogg", U"opus", U"mid", (+プラットフォームに応じた追加のフォーマット) } }`
		[[nodiscard]]
		static FileFilter AllAudioFiles();

		/// @brief CSV ファイル用の拡張子フィルタを返します。
		/// @return `FileFilter{ U"CSV",{ U"csv" } }`
		[[nodiscard]]
		static FileFilter CSV();

		/// @brief INI ファイル用の拡張子フィルタを返します。
		/// @return `FileFilter{ U"INI",{ U"ini" } }`
		[[nodiscard]]
		static FileFilter INI();

		/// @brief JSON ファイル用の拡張子フィルタを返します。
		/// @return `FileFilter{ U"JSON",{ U"json" } }`
		[[nodiscard]]
		static FileFilter JSON();

		/// @brief プレーンテキストファイル用の拡張子フィルタを返します。
		/// @return `FileFilter{ U"Text",{ U"txt" } }`
		[[nodiscard]]
		static FileFilter Text();

		/// @brief TOML ファイル用の拡張子フィルタを返します。
		/// @return `FileFilter{ U"TOML",{ U"toml" } }`
		[[nodiscard]]
		static FileFilter TOML();

		/// @brief XML ファイル用の拡張子フィルタを返します。
		/// @return `FileFilter{ U"XML",{ U"xml" } }`
		[[nodiscard]]
		static FileFilter XML();

		/// @brief すべてのファイル用の拡張子フィルタを返します。
		/// @return `FileFilter{ U"All Files", {} }`
		[[nodiscard]]
		static FileFilter AllFiles();
	};
}

# include "detail/FileFilter.ipp"
