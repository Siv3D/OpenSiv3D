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
# include "Fwd.hpp"
# include "Array.hpp"
# include "ByteArrayView.hpp"

namespace s3d
{
	/// <summary>
	/// IWriter インタフェースクラス
	/// </summary>
	class IWriter
	{
	public:

		/// <summary>
		/// デストラクタ
		/// </summary>
		virtual ~IWriter() = default;

		/// <summary>
		/// Writer が使用可能かを示します。
		/// </summary>
		/// <returns>
		/// Writer が使用可能な場合 true, それ以外の場合は false
		/// </returns>
		virtual bool isOpened() const = 0;

		/// <summary>
		/// Writer のサイズを返します。
		/// </summary>
		/// <returns>
		/// Writer のサイズ（バイト）
		/// </returns>
		virtual int64 size() const = 0;

		/// <summary>
		/// Writer の現在の書き込み位置を返します。
		/// </summary>
		/// <returns>
		/// 現在の書き込み位置（バイト）
		/// </returns>
		virtual int64 getPos() const = 0;

		/// <summary>
		/// Writer の書き込み位置を変更します。
		/// </summary>
		/// <param name="pos">
		/// 新しい書き込み位置（バイト）
		/// </param>
		/// <returns>
		/// 書き込み位置の変更に成功した場合 true, それ以外の場合は false
		/// </returns>
		virtual bool setPos(int64 pos) = 0;

		/// <summary>
		/// Writer にデータを書き込みます。
		/// </summary>
		/// <param name="buffer">
		/// 書き込むデータ
		/// </param>
		/// <param name="size">
		/// 書き込むサイズ（バイト）
		/// </param>
		/// <returns>
		/// 実際に書き込んだサイズ（バイト）
		/// </returns>
		virtual int64 write(const void* buffer, size_t size) = 0;

		/// <summary>
		/// Writer にデータを書き込みます。
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
	};
}
