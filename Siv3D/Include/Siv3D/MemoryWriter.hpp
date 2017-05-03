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
# include "IWriter.hpp"
# include "ByteArrayView.hpp"

namespace s3d
{
	/// <summary>
	/// 書き込み用バッファ
	/// </summary>
	class MemoryWriter : public IWriter
	{
	private:

		class CMemoryWriter;

		std::shared_ptr<CMemoryWriter> pImpl;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		MemoryWriter();

		/// <summary>
		/// デストラクタ
		/// </summary>
		~MemoryWriter() = default;

		/// <summary>
		/// 書き込みバッファを解放します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void release();

		/// <summary>
		/// 書き込み用バッファが使用可能かを返します。
		/// </summary>
		/// <returns>
		/// つねに true
		/// </returns>
		bool isOpened() const override { return true; }

		/// <summary>
		/// 書き込み用バッファの内容を消去し、書き込み位置を先頭に戻します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void clear();

		/// <summary>
		/// 書き込み用バッファが使用可能かを返します。
		/// </summary>
		/// <returns>
		/// つねに true
		/// </returns>
		explicit operator bool() const { return isOpened(); }

		/// <summary>
		/// 書き込み用バッファのサイズを返します。
		/// </summary>
		/// <returns>
		/// 書き込み用バッファのサイズ（バイト）
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
		///	バッファにデータを書き込みます。
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
		/// バッファにデータを書き込みます。
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
		/// 書き込みバッファの先頭ポインタを返します。
		/// </summary>
		/// <remarks>
		/// 現在の書き込み位置に関係なく、バッファの先頭のポインタを返します。
		/// </remarks>
		/// <returns>
		/// 書き込みバッファの先頭ポインタ
		/// </returns>
		const Byte* data() const;

		/// <summary>
		/// バッファの内容をファイルに保存します。
		/// </summary>
		/// <param name="path">
		/// ファイルパス
		/// </param>
		/// <remarks>
		/// 現在の書き込み位置に関係なく、バッファの内容全てを保存します。
		/// </remarks>
		/// <returns>
		/// 保存に成功した場合 true, それ以外の場合は false
		/// </returns>
		bool save(const FilePath& path) const;

		ByteArrayView getView() const;
	};
}
