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
# include "Optional.hpp"
# include "DateTime.hpp"
# include "Array.hpp"
# include "SpecialFolder.hpp"
# include "CopyOption.hpp"
# include "PredefinedYesNo.hpp"

namespace s3d
{
	namespace Platform
	{
	# if SIV3D_PLATFORM(WINDOWS)

		using NativeFilePath = std::wstring;

	# else

		using NativeFilePath = std::string;

	# endif
	}

	namespace FileSystem
	{
		/// @brief ファイルパスがリソースのパスであるかを返します。
		/// @param path ファイルパス
		/// @remark 実際に存在するリソースのパスである必要はありません
		/// @return リソースのパスである場合 true, それ以外の場合は false
		[[nodiscard]]
		bool IsResourcePath(FilePathView path) noexcept;

		/// @brief 指定されたパスのファイルまたはディレクトリが存在するかを返します。
		/// @param path パス
		/// @return 指定されたパスのファイルまたはディレクトリが存在場合 true, それ以外の場合は false
		[[nodiscard]]
		bool Exists(FilePathView path);

		/// @brief 指定したパスのディレクトリが存在するかを返します。
		/// @param path ディレクトリのパス
		/// @return 指定したパスのディレクトリが存在する場合 true, それ以外の場合は false
		[[nodiscard]]
		bool IsDirectory(FilePathView path);
		
		/// @brief 指定したパスのファイルが存在するかを返します。
		/// @param path ファイルパス
		/// @return 指定したパスのファイルが存在する場合 true, それ以外の場合は false
		[[nodiscard]]
		bool IsFile(FilePathView path);

		/// @brief 指定したパスのリソースが存在するかを返します。
		/// @param path リソースパス
		/// @return 指定したパスのリソースが存在する場合 true, それ以外の場合は false
		[[nodiscard]]
		bool IsResource(FilePathView path);

		/// @brief 絶対パスを返します。
		/// @param path パス
		/// @remark 実際に存在するファイルやディレクトリのパスである必要はありません
		/// @remark 例: "C:/Users/Siv/Desktop/picture.png"
		/// @return 絶対パス。失敗した場合は空の文字列
		[[nodiscard]]
		FilePath FullPath(FilePathView path);

		/// @brief OS ネイティブの形式で表記された絶対パスを返します。
		/// @param path パス
		/// @return OS ネイティブの形式で表記された絶対パス。失敗した場合は空の文字列
		[[nodiscard]]
		Platform::NativeFilePath NativePath(FilePathView path);

		/// @brief ファイルの拡張子(.を含まない) を小文字にして返します。
		/// @param path ファイルパス
		/// @remark 例: "png"
		/// @return 小文字の拡張子。失敗した場合は空の文字列
		[[nodiscard]]
		String Extension(FilePathView path);

		/// @brief 親ディレクトリを含まずに、ファイル名を返します。
		/// @param path ファイルパス
		/// @remark 例: "picture.png"
		/// @return ファイル名。失敗した場合は空の文字列
		[[nodiscard]]
		String FileName(FilePathView path);

		/// @brief 親ディレクトリを含まずに、拡張子を除いたファイル名を返します。
		/// @param path ファイルパス
		/// @remark 例: "picture"
		/// @return ファイル名。失敗した場合は空の文字列
		[[nodiscard]]
		String BaseName(FilePathView path);

		/// @brief 指定したパスの親ディレクトリを返します。
		/// @param path パス
		/// @param level 親のレベル。大きいほど上位の親ディレクトリ
		/// @return 親ディレクトリ。失敗した場合は空の文字列
		[[nodiscard]]
		FilePath ParentPath(FilePathView path, size_t level = 0);

		/// @brief 指定したパスの親ディレクトリを返します。合わせて、渡したパスのフルパスを取得します。
		/// @param path パス
		/// @param level 親のレベル。大きいほど上位の親ディレクトリ
		/// @param baseFullPath 渡したパスのフルパスを格納する変数への参照
		/// @return 親ディレクトリ。失敗した場合は空の文字列
		[[nodiscard]]
		FilePath ParentPath(FilePathView path, size_t level, FilePath& baseFullPath);

		[[nodiscard]]
		FilePath VolumePath(FilePathView path);

		[[nodiscard]]
		FilePath PathAppend(FilePathView lhs, FilePathView rhs);

		/// @brief 指定したパスが空のディレクトリであるかを返します。
		/// @param path パス
		/// @return 空のディレクトリである場合 true, それ以外の場合は false
		[[nodiscard]]
		bool IsEmptyDirectory(FilePathView path);

		/// @brief 指定したファイルやディレクトリのサイズを返します。
		/// @param path パス
		/// @return ファイルやディレクトリのサイズ
		[[nodiscard]]
		int64 Size(FilePathView path);

		/// @brief ファイルのサイズを返します。
		/// @param path ファイルパス
		/// @remark `FileSystem::Size()` と異なり、ディレクトリのサイズは取得できません。
		/// @remark ファイルが存在しなかったり、空である場合は 0 を返します。
		/// @return ファイルのサイズ
		[[nodiscard]]
		int64 FileSize(FilePathView path);

		/// @brief ファイルの作成日時を取得します。
		/// @param path ファイルパス
		/// @return ファイルの作成日時。取得に失敗した場合 none
		[[nodiscard]]
		Optional<DateTime> CreationTime(FilePathView path);

		/// @brief ファイルの最終更新日時を取得します。
		/// @param path ファイルパス
		/// @return ファイルの最終更新日時。取得に失敗した場合 none
		[[nodiscard]]
		Optional<DateTime> WriteTime(FilePathView path);

		/// @brief ファイルの最終アクセス日時を取得します。
		/// @param path ファイルパス
		/// @return ファイルの最終アクセス日時。取得に失敗した場合 none
		[[nodiscard]]
		Optional<DateTime> AccessTime(FilePathView path);

		/// @brief 指定したディレクトリの中身（パス）を取得します。
		/// @param path ディレクトリのパス
		/// @param recursive ディレクトリの中身にあるディレクトリの中身も取得する場合は `Recursive::Yes`, それ以外の場合は `Recursive::No`
		/// @return 指定したディレクトリの中身（パス）の一覧
		[[nodiscard]]
		Array<FilePath> DirectoryContents(FilePathView path, Recursive recursive = Recursive::Yes);

		/// @brief 実行ファイルを起動したディレクトリを返します。
		/// @return 実行ファイルを起動したディレクトリ
		[[nodiscard]]
		const FilePath& InitialDirectory() noexcept;

		/// @brief 実行ファイルのフルパスを返します。
		/// @return 実行ファイルのフルパス
		[[nodiscard]]
		const FilePath& ModulePath() noexcept;

		/// @brief 現在のカレントディレクトリを返します。
		/// @return 現在のカレントディレクトリ
		[[nodiscard]]
		FilePath CurrentDirectory();

		/// @brief カレントディレクトリを変更します。
		/// @param path 新しいカレントディレクトリ
		/// @return カレントディレクトリの変更に成功した場合 true, それ以外の場合は false
		bool ChangeCurrentDirectory(FilePathView path);

		/// @brief 特殊フォルダのパスを返します。
		/// @param folder 特殊フォルダの種類
		/// @return 特殊フォルダのパス。存在しない場合は空の文字列
		[[nodiscard]]
		const FilePath& GetFolderPath(SpecialFolder folder);

		/// @brief 一時ファイルの保存に使えるフォルダのパスを返します。
		/// @return 一時ファイルの保存に使えるフォルダのパス
		[[nodiscard]]
		FilePath TemporaryDirectoryPath();

		/// @brief 一時ファイル用に使えるファイルパスを返します。
		/// @param directory 一時ファイルの保存に使うフォルダのパス
		/// @return 一時ファイル用に使えるファイルパス
		[[nodiscard]]
		FilePath UniqueFilePath(FilePathView directory = TemporaryDirectoryPath());

		/// @brief 相対パスを作成して返します。
		/// @param path パス
		/// @param start 相対パスの基準となるパス
		/// @return start からみた path の相対パス
		[[nodiscard]]
		FilePath RelativePath(FilePathView path, FilePathView start = CurrentDirectory());

		/// @brief ディレクトリを作成します。
		/// @param path 作成するディレクトリのパス
		/// @remark 間のディレクトリが存在しない場合は自動的に作成します。
		/// @return 作成に成功したか、すでに同名のディレクトリが存在する場合 true, それ以外の場合は false
		bool CreateDirectories(FilePathView path);

		/// @brief 指定したパスの親ディレクトリを作成します。
		/// @param path パス
		/// @remark 間のディレクトリが存在しない場合は自動的に作成します。
		/// @return 作成に成功したか、すでに同名のディレクトリが存在する場合 true, それ以外の場合は false
		bool CreateParentDirectories(FilePathView path);

		/// @brief 指定したファイルまたはディレクトリをコピーします。
		/// @param from コピー元のパス
		/// @param to コピー先のパス
		/// @param copyOption オプション
		/// @return コピーに成功した場合 true, それ以外の場合は false
		bool Copy(FilePathView from, FilePathView to, CopyOption copyOption = CopyOption::Default);

		/// @brief 指定したファイルまたはディレクトリを削除します。
		/// @param path 削除するパス
		/// @param allowUndo 削除したファイルやディレクトリをゴミ箱に送る場合 `AllowUndo::Yes`, それ以外の場合は `AllowUndo::No`
		/// @return 削除に成功した場合 true, それ以外の場合は false
		bool Remove(FilePathView path, AllowUndo allowUndo = AllowUndo::No);

		/// @brief 指定したディレクトリの中身を削除します。
		/// @param path 中身を削除するディレクトリのパス
		/// @param allowUndo 削除したファイルやディレクトリをゴミ箱に送る場合 `AllowUndo::Yes`, それ以外の場合は `AllowUndo::No`
		/// @remark この関数の実行後、指定したディレクトリは空の状態になります。
		/// @return 削除に成功した場合 true, それ以外の場合は false
		bool RemoveContents(FilePathView path, AllowUndo allowUndo = AllowUndo::No);

		/// @brief 指定したファイルまたはディレクトリをリネームします。
		/// @param from リネームするパス
		/// @param to リネーム後のパス
		/// @return リネームに成功した場合 true, それ以外の場合は false
		bool Rename(FilePathView from, FilePathView to);
	}

# if SIV3D_PLATFORM(WEB)

	namespace Platform::Web
	{
		/// @brief ブラウザ上の仮想ファイルをローカルにダウンロードします。
		/// @param filePath ブラウザ上の仮想ファイルへのパス
		void DownloadFile(FilePathView filePath);

		/// @brief サーバー上からブラウザ上の仮想ファイルへファイルをダウンロードします。
		/// @param filePath ブラウザ上の仮想ファイルへのパス
		void FetchFileIfNotExists(FilePathView filePath);
	}

# endif
}
