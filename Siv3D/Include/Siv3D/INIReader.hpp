//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "Fwd.hpp"

namespace s3d
{
	class INIReader
	{
	private:

		class CINIReader;

		std::shared_ptr<CINIReader> pImpl;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		INIReader();

		/// <summary>
		/// INI ファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		explicit INIReader(const FilePath& path, bool trackFile = true);

		/// <summary>
		/// INI ファイルを開きます。
		/// </summary>
		/// <param name="reader">
		/// IReader
		/// </param>
		template <class Reader, std::enable_if_t<std::is_base_of<IReader, Reader>::value>* = nullptr>
		explicit INIReader(Reader&& reader)
			: INIReader()
		{
			open(std::move(reader));
		}

		/// <summary>
		/// INI ファイルを開きます。
		/// </summary>
		/// <param name="reader">
		/// IReader
		/// </param>
		explicit INIReader(const std::shared_ptr<IReader>& reader);

		/// <summary>
		/// デストラクタ
		/// </summary>
		~INIReader();

		/// <summary>
		/// INI ファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		/// <returns>
		/// ファイルのオープンに成功した場合 true, それ以外の場合は false
		/// </returns>
		bool open(const FilePath& path, bool trackFile = true);

		/// <summary>
		/// INI ファイルを開きます。
		/// </summary>
		/// <param name="reader">
		/// IReader
		/// </param>
		/// <returns>
		/// ファイルのオープンに成功した場合 true, それ以外の場合は false
		/// </returns>
		template <class Reader, std::enable_if_t<std::is_base_of<IReader, Reader>::value>* = nullptr>
		bool open(Reader&& reader)
		{
			return open(std::make_shared<Reader>(std::move(reader)));
		}

		/// <summary>
		/// INI ファイルを開きます。
		/// </summary>
		/// <param name="reader">
		/// IReader
		/// </param>
		/// <returns>
		/// ファイルのオープンに成功した場合 true, それ以外の場合は false
		/// </returns>
		bool open(const std::shared_ptr<IReader>& reader);

		/// <summary>
		/// INI ファイルをクローズします。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void close();

		/// <summary>
		/// INI ファイルがオープンされているかを返します。
		/// </summary>
		/// <returns>
		/// ファイルがオープンされている場合 true, それ以外の場合は false
		/// </returns>
		bool isOpened() const;

		/// <summary>
		/// INI ファイルがオープンされているかを返します。
		/// </summary>
		/// <returns>
		/// ファイルがオープンされている場合 true, それ以外の場合は false
		/// </returns>
		explicit operator bool() const { return isOpened(); }

		/// <summary>
		/// INI ファイルの内容が変更されたかを返します。
		/// </summary>
		/// <remarks>
		/// ファイルの内容が変更された場合、reload() を呼ぶまで true を返します。
		/// </remarks>
		/// <returns>
		/// INI ファイルの内容が変更された場合 true, それ以外の場合は false
		/// </returns>
		bool hasChanged() const;

		/// <summary>
		/// INI ファイルが変更された場合、データの内容を更新します。
		/// </summary>
		/// <returns>
		/// 更新に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool reload();

		/// <summary>
		/// INI ファイルのパスを返します。
		/// </summary>
		const FilePath& path() const;
	};
}
