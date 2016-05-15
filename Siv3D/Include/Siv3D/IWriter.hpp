//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "Array.hpp"

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
		/// <param name="src">
		/// 書き込むデータ
		/// </param>
		/// <returns>
		/// 実際に書き込んだサイズ（バイト）
		/// </returns>
		template <class Type, std::enable_if_t<std::is_trivially_copyable<Type>::value>* = nullptr>
		int64 write(const Type& src)
		{
			return write(std::addressof(src), sizeof(Type));
		}

		/// <summary>
		/// Writer にデータを書き込みます。
		/// </summary>
		/// <param name="ilist">
		/// 書き込むデータ
		/// </param>
		/// <returns>
		/// 実際に書き込んだサイズ（バイト）
		/// </returns>
		template <class Type, std::enable_if_t<std::is_trivially_copyable<Type>::value>* = nullptr>
		int64 write(std::initializer_list<Type> ilist)
		{
			int64 result = 0;

			for (const auto& elem : ilist)
			{
				result += write(elem);
			}

			return result;
		}

		/// <summary>
		/// Writer にデータを書き込みます。
		/// </summary>
		/// <param name="src">
		/// 書き込むデータ
		/// </param>
		/// <returns>
		/// 実際に書き込んだサイズ（バイト）
		/// </returns>
		template <class Type, std::enable_if_t<std::is_trivially_copyable<Type>::value>* = nullptr>
		int64 write(const Array<Type>& src)
		{
			return src.empty() ? 0 : write(src.data(), src.size_bytes());
		}
	};
}
