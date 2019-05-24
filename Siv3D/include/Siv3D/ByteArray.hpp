//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "Fwd.hpp"
# include "Array.hpp"
# include "IReader.hpp"
# include "ByteArrayView.hpp"

namespace s3d
{
	class ByteArray : public IReader
	{
	private:

		class ByteArrayDetail;

		std::shared_ptr<ByteArrayDetail> pImpl;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		ByteArray();

		explicit ByteArray(FilePathView path)
			: ByteArray()
		{
			createFromFile(path);
		}

		/// <summary>
		/// データをコピーして読み込み用バッファを作成します。
		/// </summary>
		/// <param name="src">
		/// コピーするデータの先頭ポインタ
		/// </param>
		/// <param name="size">
		/// コピーするデータのサイズ（バイト）
		/// </param>
		ByteArray(const void* src, size_t size)
			: ByteArray()
		{
			create(src, size);
		}

		/// <summary>
		/// データをコピーして読み込み用バッファを作成します。
		/// </summary>
		/// <param name="data">
		/// コピーするデータ
		/// </param>
		explicit ByteArray(const Array<Byte>& data)
			: ByteArray()
		{
			create(data);
		}

		/// <summary>
		/// データをムーブして読み込み用バッファを作成します。
		/// </summary>
		/// <param name="data">
		/// ムーブするデータ
		/// </param>
		explicit ByteArray(Array<Byte>&& data)
			: ByteArray()
		{
			create(std::move(data));
		}

		operator ByteArrayView() const noexcept
		{
			return view();
		}

		/// <summary>
		/// データをコピーして読み込み用バッファを作成します。
		/// </summary>
		bool createFromFile(FilePathView path);

		/// <summary>
		/// データをコピーして読み込み用バッファを作成します。
		/// </summary>
		/// <param name="src">
		/// コピーするデータの先頭ポインタ
		/// </param>
		/// <param name="size">
		/// コピーするデータのサイズ（バイト）
		/// </param>
		/// <returns>
		/// バッファの作成に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool create(const void* src, size_t size);

		/// <summary>
		/// データをコピーして読み込み用バッファを作成します。
		/// </summary>
		/// <param name="data">
		/// コピーするデータ
		/// </param>
		/// <returns>
		/// バッファの作成に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool create(const Array<Byte>& data);

		/// <summary>
		/// データをムーブして読み込み用バッファを作成します。
		/// </summary>
		/// <param name="data">
		/// ムーブするデータ
		/// </param>
		/// <returns>
		/// バッファの作成に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool create(Array<Byte>&& data);

		/// <summary>
		/// 読み込みバッファを解放します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void release();

		/// <summary>
		/// 読み込み用バッファが使用可能かを返します。
		/// </summary>
		/// <returns>
		/// 使用可能な場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] bool isOpened() const override;

		/// <summary>
		/// 読み込み用バッファが使用可能かを返します。
		/// </summary>
		/// <returns>
		/// 使用可能な場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] explicit operator bool() const { return isOpened(); }

		/// <summary>
		/// 読み込み用バッファのサイズを返します。
		/// </summary>
		/// <returns>
		/// 読み込み用バッファのサイズ（バイト）
		/// </returns>
		[[nodiscard]] int64 size() const override;

		/// <summary>
		/// 現在の読み込み位置を返します。
		/// </summary>
		/// <returns>
		/// 現在の読み込み位置（バイト）
		/// </returns>
		[[nodiscard]] int64 getPos() const override;

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
		/// 読み込みバッファの先頭ポインタを返します。
		/// </summary>
		/// <remarks>
		/// 現在の読み込み位置に関係なく、バッファの先頭のポインタを返します。
		/// </remarks>
		/// <returns>
		/// 読み込みバッファの先頭ポインタ
		/// </returns>
		[[nodiscard]] const Byte* data() const;

		/// <summary>
		/// ファイルからデータを読み込みます。
		/// </summary>
		/// <param name="dst">
		/// 読み込み先
		/// </param>
		/// <param name="size">
		/// 読み込むサイズ（バイト）
		/// </param>
		/// <returns>
		/// 実際に読み込んだサイズ（バイト）
		/// </returns>
		int64 read(void* dst, int64 size) override;

		/// <summary>
		/// ファイルからデータを読み込みます。
		/// </summary>
		/// <param name="dst">
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
		int64 read(void* dst, int64 pos, int64 size) override;

		/// <summary>
		/// ファイルからデータを読み込みます。
		/// </summary>
		/// <param name="to">
		/// 読み込み先
		/// </param>
		/// <returns>
		/// 読み込みに成功したら true, それ以外の場合は false
		/// </returns>
		template <class Type, std::enable_if_t<std::is_trivially_copyable_v<Type>>* = nullptr>
		bool read(Type& to)
		{
			return IReader::read(to);
		}

		/// <summary>
		/// 読み込み位置を変更しないデータ読み込みをサポートしているかを返します。
		/// </summary>
		/// <returns>
		/// つねに true
		/// </returns>
		[[nodiscard]] bool supportsLookahead() const override { return true; }

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
		template <class Type, std::enable_if_t<std::is_trivially_copyable_v<Type>>* = nullptr>
		bool lookahead(Type& to)
		{
			return IReader::lookahead(to);
		}

		[[nodiscard]] ByteArrayView view() const noexcept
		{
			return{ data(), static_cast<size_t>(size()) };
		}

		[[nodiscard]] const Byte& operator[](size_t index) const
		{
			return *(data() + index);
		}

		/// <summary>
		/// バッファの内容をファイルに保存します。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		/// <remarks>
		/// 現在の読み込み位置に関係なく、バッファの内容全てを保存します。
		/// </remarks>
		/// <returns>
		/// 保存に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool save(const FilePath& path) const;
	};
}

namespace s3d
{
	void Formatter(FormatData& formatData, const ByteArray& value);

	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const ByteArray& value)
	{
		return output << value.view().toHex();
	}
}
