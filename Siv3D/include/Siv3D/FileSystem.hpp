//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
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

		[[nodiscard]]
		FilePath ParentPath(FilePathView path, size_t level = 0);

		[[nodiscard]]
		FilePath ParentPath(FilePathView path, size_t level, FilePath& baseFullPath);

		[[nodiscard]]
		FilePath VolumePath(FilePathView path);

		[[nodiscard]]
		bool IsEmptyDirectory(FilePathView path);

		[[nodiscard]]
		int64 Size(FilePathView path);

		/// @brief ファイルのサイズを返します。
		/// @param path ファイルパス
		/// @remark ファイルが存在しなかったり、空である場合は 0 を返します。
		/// @return ファイルのサイズ
		[[nodiscard]]
		int64 FileSize(FilePathView path);

		[[nodiscard]]
		Optional<DateTime> CreationTime(FilePathView path);

		[[nodiscard]]
		Optional<DateTime> WriteTime(FilePathView path);

		[[nodiscard]]
		Optional<DateTime> AccessTime(FilePathView path);

		[[nodiscard]]
		Array<FilePath> DirectoryContents(FilePathView path, bool recursive = true);

		[[nodiscard]]
		const FilePath& InitialDirectory() noexcept;

		[[nodiscard]]
		const FilePath& ModulePath() noexcept;

		[[nodiscard]]
		FilePath CurrentDirectory();

		bool ChangeCurrentDirectory(FilePathView path);

		[[nodiscard]]
		const FilePath& GetFolderPath(SpecialFolder folder);

		[[nodiscard]]
		FilePath TemporaryDirectoryPath();

		[[nodiscard]]
		FilePath UniqueFilePath(FilePathView directory = TemporaryDirectoryPath());

		[[nodiscard]]
		FilePath RelativePath(FilePathView path, FilePathView start = FileSystem::CurrentDirectory());

		bool CreateDirectories(FilePathView path);

		bool CreateParentDirectories(FilePathView path);

		bool Copy(FilePathView from, FilePathView to, CopyOption copyOption = CopyOption::Default);

		bool Remove(FilePathView path, bool allowUndo = false);

		bool RemoveContents(FilePathView path, bool allowUndo = false);

		bool Rename(FilePathView from, FilePathView to);
	}
}
