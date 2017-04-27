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
# include "IReader.hpp"
# include "ByteArray.hpp"

namespace s3d
{
	/// <summary>
	/// 読み込み用バイナリファイル
	/// </summary>
	class BinaryReader : public IReader
	{
	private:

		class CBinaryReader;

		std::shared_ptr<CBinaryReader> pImpl;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		BinaryReader();

		/// <summary>
		/// バイナリファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		explicit BinaryReader(const FilePath& path)
			: BinaryReader()
		{
			open(path);
		}

		/// <summary>
		/// バイナリファイルを開きます。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		/// <returns>
		/// ファイルのオープンに成功した場合 true, それ以外の場合は false
		/// </returns>
		bool open(const FilePath& path);

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
		/// バイナリファイルのサイズを返します。
		/// </summary>
		/// <returns>
		/// バイナリファイルのサイズ（バイト）
		/// </returns>
		int64 size() const override;

		/// <summary>
		/// 現在の読み込み位置を返します。
		/// </summary>
		/// <returns>
		/// 現在の読み込み位置（バイト）
		/// </returns>
		int64 getPos() const override;

		/// <summary>
		/// 読み込み位置を変更します。
		/// </summary>
		/// <param name="pos">
		/// 新しい読み込み位置（バイト）
		/// </param>
		/// <returns>
		/// 読み込み位置の変更に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool setPos(int64 pos) override;

		/// <summary>
		/// ファイルを読み飛ばし、読み込み位置を変更します。
		/// </summary>
		/// <param name="offset">
		/// 読み飛ばすサイズ（バイト）
		/// </param>
		/// <returns>
		/// 新しい読み込み位置
		/// </returns>
		int64 skip(int64 offset) override;

		/// <summary>
		/// ファイルからデータを読み込みます。
		/// </summary>
		/// <param name="buffer">
		/// 読み込み先
		/// </param>
		/// <param name="size">
		/// 読み込むサイズ（バイト）
		/// </param>
		/// <returns>
		/// 実際に読み込んだサイズ（バイト）
		/// </returns>
		int64 read(void* buffer, int64 size) override;

		/// <summary>
		/// ファイルからデータを読み込みます。
		/// </summary>
		/// <param name="buffer">
		/// 読み込み先
		/// </param>
		/// <param name="pos">
		/// 先頭から数えた読み込み開始位置（バイト）
		/// </param>
		/// <param name="size">
		/// 読み込むサイズ（バイト）
		/// </param>
		/// <returns>
		/// 実際に読み込んだサイズ（バイト）
		/// </returns>
		int64 read(void* buffer, int64 pos, int64 size) override;

		/// <summary>
		/// ファイルからデータを読み込みます。
		/// </summary>
		/// <param name="to">
		/// 読み込み先
		/// </param>
		/// <returns>
		/// 読み込みに成功したら true, それ以外の場合は false
		/// </returns>
		template <class Type, std::enable_if_t<std::is_trivially_copyable<Type>::value>* = nullptr>
		bool read(Type& to)
		{
			return read(std::addressof(to), sizeof(Type)) == sizeof(Type);
		}

		/// <summary>
		/// 読み込み位置を変更しないデータ読み込みをサポートしているかを返します。
		/// </summary>
		/// <returns>
		/// つねに true
		/// </returns>
		bool supportsLookahead() const override { return true; }

		/// <summary>
		/// 読み込み位置を変更しないでファイルからデータを読み込みます。
		/// </summary>
		/// <param name="buffer">
		/// 読み込み先
		/// </param>
		/// <param name="size">
		/// 読み込むサイズ（バイト）
		/// </param>
		/// <returns>
		/// 実際に読み込んだサイズ（バイト）
		/// </returns>
		int64 lookahead(void* buffer, int64 size) const override;

		/// <summary>
		/// 読み込み位置を変更しないでファイルからデータを読み込みます。
		/// </summary>
		/// <param name="buffer">
		/// 読み込み先
		/// </param>
		/// <param name="pos">
		/// 先頭から数えた読み込み開始位置（バイト）
		/// </param>
		/// <param name="size">
		/// 読み込むサイズ（バイト）
		/// </param>
		/// <returns>
		/// 実際に読み込んだサイズ（バイト）
		/// </returns>
		int64 lookahead(void* buffer, int64 pos, int64 size) const override;

		/// <summary>
		/// 読み込み位置を変更しないでファイルからデータを読み込みます。
		/// </summary>
		/// <param name="to">
		/// 読み込み先
		/// </param>
		/// <returns>
		/// 読み込みに成功したら true, それ以外の場合は false
		/// </returns>
		template <class Type, std::enable_if_t<std::is_trivially_copyable<Type>::value>* = nullptr>
		bool lookahead(Type& to)
		{
			return lookahead(std::addressof(to), sizeof(Type)) == sizeof(Type);
		}

		/// <summary>
		/// オープンしているファイルのパスを返します。
		/// </summary>
		/// <remarks>
		/// クローズしている場合は空の文字列です。
		/// </remarks>
		const FilePath& path() const;

		ByteArray readAll()
		{
			Array<Byte> data(static_cast<size_t>(size()));

			read(data.data(), 0, size());

			return ByteArray(std::move(data));
		}
	};
}
