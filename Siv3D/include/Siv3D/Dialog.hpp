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
# include "Array.hpp"
# include "String.hpp"
# include "Optional.hpp"
# include "Texture.hpp"
# include "Wave.hpp"
# include "Audio.hpp"
# include "FileFilter.hpp"
# include "AsyncTask.hpp"

namespace s3d
{
	namespace Dialog
	{
		/// @brief オープンファイルダイアログを表示し、選択されたファイルを返します。
		/// @param filters ダイアログに表示するファイルの拡張子のフィルタ
		/// @param defaultDirectory ダイアログで表示するデフォルトディレクトリ。空の場合は OS のデフォルト
		/// @param title ダイアログのタイトル。空の場合は OS のデフォルト
		/// @return 選択されたファイルのパス。選択されなかった場合は none
		[[nodiscard]]
		Optional<FilePath> OpenFile(const Array<FileFilter>& filters = {}, FilePathView defaultDirectory = U"", StringView title = U"");

		/// @brief オープンファイルダイアログを表示し、選択されたファイルを返します。複数選択することもできます。
		/// @param filters ダイアログに表示するファイルの拡張子のフィルタ
		/// @param defaultDirectory ダイアログで表示するデフォルトディレクトリ。空の場合は OS のデフォルト
		/// @param title ダイアログのタイトル。空の場合は OS のデフォルト
		/// @return 選択されたファイルパスの一覧。選択されなかった場合は空の配列
		[[nodiscard]]
		Array<FilePath> OpenFiles(const Array<FileFilter>& filters = {}, FilePathView defaultDirectory = U"", StringView title = U"");

		/// @brief セーブファイルダイアログを表示し、選択されたファイルパスを返します。
		/// @param filters ダイアログに表示するファイルの拡張子のフィルタ
		/// @param defaultDirectory ダイアログで表示するデフォルトディレクトリ。空の場合は OS のデフォルト
		/// @param title ダイアログのタイトル。空の場合は OS のデフォルト
		/// @remark この関数はファイルの保存は行いません。戻り値をファイル保存系の関数と組み合わせて使ってください。
		/// @return 選択されたファイルパス。選択されなかった場合は none
		[[nodiscard]]
		Optional<FilePath> SaveFile(const Array<FileFilter>& filters = {}, FilePathView defaultDirectory = U"", StringView title = U"");

		/// @brief フォルダ選択ダイアログを表示し、選択されたフォルダを返します。
		/// @param defaultDirectory ダイアログで表示するデフォルトディレクトリ。空の場合は OS のデフォルト
		/// @param title ダイアログのタイトル。空の場合は OS のデフォルト
		/// @return 選択されたフォルダのパス。選択されなかった場合は none
		[[nodiscard]]
		Optional<FilePath> SelectFolder(FilePathView defaultDirectory = U"", StringView title = U"");

		/// @brief イアログから画像ファイルを選択し、Image を作成します。
		/// @param defaultDirectory ダイアログで表示するデフォルトディレクトリ。空の場合は OS のデフォルト
		/// @param title ダイアログのタイトル。空の場合は OS のデフォルト
		/// @return 作成した Image. ファイルが選択されなかった場合は空の Image
		[[nodiscard]]
		Image OpenImage(FilePathView defaultDirectory = U"", StringView title = U"");

		/// @brief ダイアログから画像ファイルを選択し、Texture を作成します。
		/// @param defaultDirectory ダイアログで表示するデフォルトディレクトリ。空の場合は OS のデフォルト
		/// @param title ダイアログのタイトル。空の場合は OS のデフォルト
		/// @return 作成したテクスチャ。ファイルが選択されなかった場合は空のテクスチャ
		[[nodiscard]]
		Texture OpenTexture(FilePathView defaultDirectory = U"", StringView title = U"");

		/// @brief ダイアログから画像ファイルを選択し、Texture を作成します。
		/// @param desc テクスチャの設定
		/// @param defaultDirectory ダイアログで表示するデフォルトディレクトリ。空の場合は OS のデフォルト
		/// @param title ダイアログのタイトル。空の場合は OS のデフォルト
		/// @return 作成したテクスチャ。ファイルが選択されなかった場合は空のテクスチャ
		[[nodiscard]]
		Texture OpenTexture(TextureDesc desc, FilePathView defaultDirectory = U"", StringView title = U"");

		/// @brief ダイアログから音声ファイルを選択し、Wave を作成します。
		/// @param defaultDirectory ダイアログで表示するデフォルトディレクトリ。空の場合は OS のデフォルト
		/// @param title ダイアログのタイトル。空の場合は OS のデフォルト
		/// @return 作成した音声。ファイルが選択されなかった場合は空の Wave
		[[nodiscard]]
		Wave OpenWave(FilePathView defaultDirectory = U"", StringView title = U"");

		/// @brief ダイアログから音声ファイルを選択し、Audio を作成します。
		/// @param defaultDirectory ダイアログで表示するデフォルトディレクトリ。空の場合は OS のデフォルト
		/// @param title ダイアログのタイトル。空の場合は OS のデフォルト
		/// @return 作成した音声。ファイルが選択されなかった場合は空の Audio
		[[nodiscard]]
		Audio OpenAudio(FilePathView defaultDirectory = U"", StringView title = U"");

		/// @brief ダイアログから音声ファイルを選択し、ストリーミング再生する Audio を作成します。
		/// @param f `Audio::Stream`
		/// @param defaultDirectory ダイアログで表示するデフォルトディレクトリ。空の場合は OS のデフォルト
		/// @param title ダイアログのタイトル。空の場合は OS のデフォルト
		/// @return 作成した音声。ファイルが選択されなかった場合は空の Audio
		[[nodiscard]]
		Audio OpenAudio(Audio::FileStreaming f, FilePathView defaultDirectory = U"", StringView title = U"");

		/// @brief セーブファイルダイアログから、画像を保存するパスを取得します。
		/// @param defaultDirectory ダイアログで表示するデフォルトディレクトリ。空の場合は OS のデフォルト
		/// @param title ダイアログのタイトル。空の場合は OS のデフォルト
		/// @remark この関数は画像ファイルの保存は行いません。`Image::save()` と組み合わせて使ってください。
		/// @return 画像ファイルを保存するパス。選択されなかった場合は none
		[[nodiscard]]
		Optional<FilePath> SaveImage(FilePathView defaultDirectory = U"", StringView title = U"");

		/// @brief セーブファイルダイアログから、音声を保存するパスを取得します。
		/// @param defaultDirectory ダイアログで表示するデフォルトディレクトリ。空の場合は OS のデフォルト
		/// @param title ダイアログのタイトル。空の場合は OS のデフォルト
		/// @remark この関数は音声ファイルの保存は行いません。`Wave::save()` と組み合わせて使ってください。
		/// @return 音声ファイルを保存するパス。選択されなかった場合は none
		[[nodiscard]]
		Optional<FilePath> SaveWave(FilePathView defaultDirectory = U"", StringView title = U"");
	}

	
# if SIV3D_PLATFORM(WEB)

 	namespace Platform::Web::Dialog 
	{
		[[nodiscard]]
		AsyncTask<Optional<FilePath>> OpenFile(const Array<FileFilter>& filters = {}, FilePathView defaultDirectory = U"", StringView title = U"");

		[[nodiscard]]
		AsyncTask<Array<FilePath>> OpenFiles(const Array<FileFilter>& filters = {}, FilePathView defaultDirectory = U"", StringView title = U"");

		[[nodiscard]]
		AsyncTask<Image> OpenImage(FilePathView defaultDirectory = U"", StringView title = U"");

		[[nodiscard]]
		AsyncTask<Texture> OpenTexture(FilePathView defaultDirectory = U"", StringView title = U"");

		[[nodiscard]]
		AsyncTask<Texture> OpenTexture(TextureDesc desc, FilePathView defaultDirectory = U"", StringView title = U"");

		[[nodiscard]]
		AsyncTask<Wave> OpenWave(FilePathView defaultDirectory = U"", StringView title = U"");

		[[nodiscard]]
		AsyncTask<Audio> OpenAudio(FilePathView defaultDirectory = U"", StringView title = U"");

		/// @brief ダイアログから音声ファイルを選択し、ストリーミング再生する Audio を作成します。
		/// @param f `Audio::Stream`
		/// @param defaultDirectory ダイアログのデフォルトディレクトリ
		/// @param title ダイアログのタイトル
		/// @return 作成した音声。ファイルが選択されなかった場合は空の Audio
		[[nodiscard]]
		AsyncTask<Audio> OpenAudio(Audio::FileStreaming f, FilePathView defaultDirectory = U"", StringView title = U"");
	}

# endif
}
