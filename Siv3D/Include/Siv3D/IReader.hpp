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
# include <type_traits>
# include "Fwd.hpp"

namespace s3d
{
	/// <summary>
	/// IReader インタフェースクラス
	/// </summary>
	class IReader
	{
	public:

		/// <summary>
		/// デストラクタ
		/// </summary>
		virtual ~IReader() = default;

		/// <summary>
		/// Reader が使用可能かを返します。
		/// </summary>
		/// <returns>
		/// Reader が使用可能な場合 true, それ以外の場合は false
		/// </returns>
		virtual bool isOpened() const = 0;

		/// <summary>
		/// Reader のサイズを返します。
		/// </summary>
		/// <returns>
		/// Reader のサイズ（バイト）
		/// </returns>
		virtual int64 size() const = 0;

		/// <summary>
		/// Reader の現在の読み込み位置を返します。
		/// </summary>
		/// <returns>
		/// 現在の読み込み位置（バイト）
		/// </returns>
		virtual int64 getPos() const = 0;

		/// <summary>
		/// Reader の読み込み位置を変更します。
		/// </summary>
		/// <param name="pos">
		/// 新しい読み込み位置（バイト）
		/// </param>
		/// <returns>
		/// 読み込み位置の変更に成功した場合 true, それ以外の場合は false
		/// </returns>
		virtual bool setPos(int64 pos) = 0;

		/// <summary>
		/// Reader を読み飛ばし、読み込み位置を変更します。
		/// </summary>
		/// <param name="offset">
		/// 読み飛ばすサイズ（バイト）
		/// </param>
		/// <returns>
		/// 新しい読み込み位置（バイト）
		/// </returns>
		virtual int64 skip(int64 offset) = 0;

		/// <summary>
		/// Reader からデータを読み込みます。
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
		virtual int64 read(void* buffer, int64 size) = 0;

		/// <summary>
		/// Reader からデータを読み込みます。
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
		virtual int64 read(void* buffer, int64 pos, int64 size) = 0;

		/// <summary>
		/// Reader からデータを読み込みます。
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
		/// 読み込み位置を変更しないデータ読み込みをサポートしている場合 true, それ以外の場合は false
		/// </returns>
		virtual bool supportsLookahead() const = 0;

		/// <summary>
		/// Reader から読み込み位置を変更しないでデータを読み込みます。
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
		virtual int64 lookahead(void* buffer, int64 size) const = 0;

		/// <summary>
		/// Reader から読み込み位置を変更しないでデータを読み込みます。
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
		virtual int64 lookahead(void* buffer, int64 pos, int64 size) const = 0;

		/// <summary>
		/// 読み込み位置を変更しないで Reader からデータを読み込みます。
		/// </summary>
		/// <param name="to">
		/// 読み込み先
		/// </param>
		/// <returns>
		/// 読み込みに成功したら true, それ以外の場合は false
		/// </returns>
		template <class Type, std::enable_if_t<std::is_trivially_copyable<Type>::value>* = nullptr>
		bool lookahead(Type& to) const
		{
			return lookahead(std::addressof(to), sizeof(Type)) == sizeof(Type);
		}
	};
}
