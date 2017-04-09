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
# include "IWriter.hpp"
# include "FileSystem.hpp"

namespace s3d
{
	/// <summary>
	/// 書き込み用バイナリファイル
	/// </summary>
	class BinaryWriter : public IWriter
	{
	private:

		class CBinaryWriter;

		std::shared_ptr<CBinaryWriter> pImpl;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		BinaryWriter();

		/// <summary>
		/// 書き込み用のバイナリファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		/// <param name="openMode">
		/// オープンモード
		/// </param>
		explicit BinaryWriter(const FilePath& path, OpenMode openMode = OpenMode::Trunc)
			: BinaryWriter()
		{
			open(path, openMode);
		}

		/// <summary>
		/// デストラクタ
		/// </summary>
		~BinaryWriter() = default;

		/// <summary>
		/// 書き込み用のバイナリファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		/// <param name="openMode">
		/// オープンモード
		/// </param>
		/// <returns>
		/// ファイルのオープンに成功した場合 true, それ以外の場合は false
		/// </returns>
		bool open(const FilePath& path, OpenMode openMode = OpenMode::Trunc);

		/// <summary>
		/// バイナリファイルの書き込みバッファをフラッシュします。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void flush();

		/// <summary>
		/// バイナリファイルをクローズします。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void close();

		/// <summary>
		/// バイナリファイルがオープンされているかを返します。
		/// </summary>
		/// <returns>
		/// ファイルがオープンされている場合 true, それ以外の場合は false
		/// </returns>
		bool isOpened() const override;

		/// <summary>
		/// バイナリファイルがオープンされているかを返します。
		/// </summary>
		/// <returns>
		/// ファイルがオープンされている場合 true, それ以外の場合は false
		/// </returns>
		explicit operator bool() const { return isOpened(); }

		/// <summary>
		/// 現在開いているファイルの内容を消去し、書き込み位置を先頭に戻します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void clear();

		/// <summary>
		/// バイナリファイルのサイズを返します。
		/// </summary>
		/// <returns>
		/// バイナリファイルのサイズ（バイト）
		/// </returns>
		int64 size() const override;

		/// <summary>
		/// 現在の書き込み位置を返します。
		/// </summary>
		/// <returns>
		/// 現在の書き込み位置（バイト）
		/// </returns>
		int64 getPos() const override;

		/// <summary>
		/// 書き込み位置を変更します。
		/// </summary>
		/// <param name="pos">
		/// 新しい書き込み位置（バイト）
		/// </param>
		/// <returns>
		/// 書き込み位置の変更に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool setPos(int64 pos) override;

		/// <summary>
		/// 書き込み位置を終端に移動します。
		/// </summary>
		/// <returns>
		/// 新しい書き込み位置（バイト）
		/// </returns>
		int64 seekEnd();

		/// <summary>
		/// ファイルにデータを書き込みます。
		/// </summary>
		/// <param name="src">
		/// 書き込むデータ
		/// </param>
		/// <param name="size">
		/// 書き込むサイズ（バイト）
		/// </param>
		/// <returns>
		/// 実際に書き込んだサイズ（バイト）
		/// </returns>
		int64 write(const void* src, size_t size) override;

		/// <summary>
		/// ファイルにデータを書き込みます。
		/// </summary>
		/// <param name="view">
		/// 書き込むデータ
		/// </param>
		/// <returns>
		/// 実際に書き込んだサイズ（バイト）
		/// </returns>
		int64 write(ByteArrayView view)
		{
			return write(view.data(), view.size());
		}

		/// <summary>
		/// オープンしているファイルのパスを返します。
		/// </summary>
		/// <remarks>
		/// クローズしている場合は空の文字列です。
		/// </remarks>
		const FilePath& path() const;
	};
}
