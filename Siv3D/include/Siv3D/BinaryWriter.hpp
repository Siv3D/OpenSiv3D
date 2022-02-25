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
# include <memory>
# include "Common.hpp"
# include "IWriter.hpp"
# include "StringView.hpp"
# include "OpenMode.hpp"

namespace s3d
{
	class String;
	using FilePath = String;

	/// @brief 書き込み用バイナリファイル
	class BinaryWriter : public IWriter
	{
	public:

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		BinaryWriter();

		/// @brief ファイルを開きます。
		/// @param path ファイルパス
		/// @param openMode オープンモード (`OpenMode` の組み合わせ）
		SIV3D_NODISCARD_CXX20
		explicit BinaryWriter(FilePathView path, OpenMode openMode = OpenMode::Trunc);

		/// @brief ファイルを開きます。
		/// @param path ファイルパス
		/// @param openMode オープンモード (`OpenMode` の組み合わせ）
		/// @return ファイルのオープンに成功した場合 true, それ以外の場合は false
		bool open(FilePathView path, OpenMode openMode = OpenMode::Trunc);

		/// @brief ファイルを閉じます。
		/// @remark ファイルがオープンしていない場合は何もしません。
		void close();

		/// @brief ファイルが開いているかを返します。
		/// @return ファイルが開いている場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isOpen() const noexcept override;

		/// @brief ファイルが開いているかを返します。
		/// @return ファイルが開いている場合 true, それ以外の場合は false	
		[[nodiscard]]
		explicit operator bool() const noexcept;

		/// @brief 書き込んだデータのバッファをフラッシュして、確実にファイルに書き込みます。
		void flush();

		/// @brief 開いているファイルの内容をすべて消去し、サイズが 0 のファイルにします。
		void clear();

		/// @brief 開いているファイルの現在のサイズ（バイト）を返します。
		/// @return 開いているファイルの現在のサイズ（バイト）
		[[nodiscard]]
		int64 size() const override;

		/// @brief 現在の書き込み位置を返します。
		/// @return 現在の書き込み位置
		[[nodiscard]]
		int64 getPos() const override;

		/// @brief 書き込み位置を変更します。
		/// @param pos 新しい書き込み位置（バイト）
		/// @return 書き込み位置の変更に成功した場合 true, それ以外の場合は false
		bool setPos(int64 pos) override;

		/// @brief 書き込み位置をファイルの終端に移動させます。
		/// @return 新しい書き込み位置（バイト）
		int64 seekToEnd();

		/// @brief 現在の書き込み位置にデータを書き込みます。
		/// @param src 書き込むデータ
		/// @param sizeBytes 書き込むサイズ（バイト）
		/// @remark 書き込み位置がファイルの終端の場合、書き込んだ分だけファイルのサイズが拡張されます。
		/// @return 実際に書き込んだサイズ（バイト）
		int64 write(const void* src, int64 sizeBytes) override;

		/// @brief 現在の書き込み位置にデータを書き込みます。
		/// @tparam TriviallyCopyable 書き込む値の型
		/// @param src 書き込むデータ
		/// @remark 書き込み位置がファイルの終端の場合、書き込んだ分だけファイルのサイズが拡張されます。
		/// @return 書き込みに成功した場合 true, それ以外の場合は false
		SIV3D_CONCEPT_TRIVIALLY_COPYABLE
		bool write(const TriviallyCopyable& src);

		/// @brief 開いているファイルのパスを返します。
		/// @return 開いているファイルのパス。ファイルが開いていない場合は空の文字列
		[[nodiscard]]
		const FilePath& path() const noexcept;
	
	private:

		class BinaryWriterDetail;

		std::shared_ptr<BinaryWriterDetail> pImpl;
	};
}

# include "detail/BinaryWriter.ipp"
