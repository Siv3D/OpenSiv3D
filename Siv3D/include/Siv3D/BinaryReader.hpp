﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "Common.hpp"
# include "IReader.hpp"
# include "String.hpp"
# include "OpenMode.hpp"

namespace s3d
{
	/// @brief 読み込み用バイナリファイル
	class BinaryReader : public IReader
	{
	private:

		class BinaryReaderDetail;

		std::shared_ptr<BinaryReaderDetail> pImpl;

	public:

		/// @brief デフォルトコンストラクタ
		BinaryReader();

		/// @brief ファイルを開きます。
		/// @param path ファイルパス
		/// @param openMode オープンモード (OpenMode の組み合わせ）
		explicit BinaryReader(FilePathView path, OpenMode openMode = {});

		/// @brief lookahead をサポートしているかを返します。
		/// @return true
		[[nodiscard]]
		bool supportsLookahead() const noexcept override;

		/// @brief ファイルを開きます。
		/// @param path ファイルパス
		/// @param openMode オープンモード (OpenMode の組み合わせ）
		/// @return ファイルのオープンに成功した場合 true, それ以外の場合は false
		bool open(FilePathView path, OpenMode openMode = {});

		/// @brief ファイルをクローズします。
		void close();

		/// @brief ファイルがオープンされているかを返します。
		/// @return ファイルがオープンされている場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isOpen() const noexcept override;

		/// @brief ファイルがオープンされているかを返します。
		/// @return ファイルがオープンされている場合 true, それ以外の場合は false	
		[[nodiscard]]
		explicit operator bool() const noexcept;

		/// @brief ファイルのサイズを返します。
		/// @return ファイルのサイズ（バイト）
		[[nodiscard]]
		int64 size() const override;

		/// @brief 現在の読み込み位置を返します。
		/// @return 現在の読み込み位置（バイト）		
		[[nodiscard]]
		int64 getPos() const override;

		/// @brief 読み込み位置を変更します。
		/// @param pos 新しい読み込み位置（バイト）
		/// @return 読み込み位置の変更に成功した場合 true, それ以外の場合は false
		bool setPos(int64 pos) override;

		/// @brief ファイルを読み飛ばし、読み込み位置を変更します。
		/// @param offset 読み飛ばすサイズ（バイト）
		/// @return 新しい読み込み位置
		int64 skip(int64 offset) override;

		/// @brief ファイルからデータを読み込みます。
		/// @param dst 読み込み先
		/// @param size 読み込むサイズ（バイト）
		/// @return 実際に読み込んだサイズ（バイト）
		int64 read(void* dst, int64 size) override;

		/// @brief ファイルからデータを読み込みます。
		/// @param dst 読み込み先
		/// @param pos 先頭から数えた読み込み開始位置（バイト）
		/// @param size 読み込むサイズ（バイト）
		/// @return 実際に読み込んだサイズ（バイト）
		int64 read(void* dst, int64 pos, int64 size) override;

		/// @brief ファイルからデータを読み込みます。
		/// @tparam TriviallyCopyable 読み込む値の型
		/// @param dst 読み込み先
		/// @return 読み込みに成功したら true, それ以外の場合は false
		SIV3D_CONCEPT_TRIVIALLY_COPYABLE
		bool read(TriviallyCopyable& dst);

		/// @brief 読み込み位置を変更しないでファイルからデータを読み込みます。
		/// @param dst 読み込み先
		/// @param size 読み込むサイズ（バイト）
		/// @return 実際に読み込んだサイズ（バイト）
		int64 lookahead(void* dst, int64 size) const override;

		/// @brief 読み込み位置を変更しないでファイルからデータを読み込みます。
		/// @param dst 読み込み先
		/// @param pos 先頭から数えた読み込み開始位置（バイト）
		/// @param size 読み込むサイズ（バイト）
		/// @return 実際に読み込んだサイズ（バイト）
		int64 lookahead(void* dst, int64 pos, int64 size) const override;

		/// @brief 読み込み位置を変更しないでファイルからデータを読み込みます。
		/// @tparam TriviallyCopyable 読み込む値の型
		/// @param dst 読み込み先
		/// @return 読み込みに成功したら true, それ以外の場合は false
		SIV3D_CONCEPT_TRIVIALLY_COPYABLE
		bool lookahead(TriviallyCopyable& dst);

		/// @brief オープンしているファイルのパスを返します。
		/// @return オープンしているファイルのパス。ファイルがオープンしていない場合は空の文字列
		[[nodiscard]]
		const FilePath& path() const noexcept;

		//[[nodiscard]] ByteArray readAll();
	};
}

# include "detail/BinaryReader.ipp"
