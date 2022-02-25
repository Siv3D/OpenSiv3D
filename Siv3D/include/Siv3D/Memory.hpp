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

namespace s3d
{
	namespace Platform
	{
		/// @brief ポインタのサイズ | The size of a pointer
		inline constexpr size_t PointerSize = sizeof(void*);

		/// @brief 最小のメモリアラインメント | The minimum alignment of the memory
		inline constexpr size_t MinAlignment = __STDCPP_DEFAULT_NEW_ALIGNMENT__;

		/// @brief アライメントを指定してメモリを確保します。
		/// @param size 確保するメモリのサイズ
		/// @return 確保したメモリ
		template <size_t Alignment>
		[[nodiscard]]
		inline void* AlignedMalloc(size_t size) noexcept;

		/// @brief アライメントを指定して確保したメモリを解放します。
		/// @param p 解放するメモリのポインタ
		/// @return なし
		inline void AlignedFree(void* const p) noexcept;
	}

	/// @brief アライメントを考慮して、指定した型のためのメモリ領域を確保します。
	/// @tparam Type メモリを確保するオブジェクトの型
	/// @param n 要素数。デフォルトは 1
	/// @remark 確保したポインタは `AlignedFree()` で解放する必要があります。
	/// @return 確保したメモリ領域の先頭ポインタ
	template <class Type, size_t Alignment = alignof(Type)>
	[[nodiscard]]
	inline Type* AlignedMalloc(size_t n = 1);

	/// @brief AlignedMalloc() で確保したメモリ領域を解放します。| Deallocates the space previously allocated by AlignedMalloc()
	/// @param p 解放するメモリ領域の先頭ポインタ | Pointer to the memory to deallocate
	/// @remark p が nullptr の場合は何も起こりません。| The function accepts and does nothing with the null pointer.
	inline void AlignedFree(void* const p);

	/// @brief アライメントを考慮して、指定した型のためのメモリ領域を確保し、オブジェクトを構築します。
	/// @tparam Type 構築するオブジェクト
	/// @tparam ...Args コンストラクタ引数の型
	/// @param ...args コンストラクタ引数
	/// @remark 確保したポインタは `AlignedDelete()` で解放する必要があります。
	/// @return 確保したメモリ領域の先頭ポインタ
	template <class Type, class ...Args, std::enable_if_t<std::is_constructible_v<Type, Args...>>* = nullptr>
	[[nodiscard]]
	inline Type* AlignedNew(Args&&... args);

	/// @brief `AlignedNew()` で確保したオブジェクトを破棄し、メモリ領域を解放します。
	/// @tparam Type オブジェクトの型
	/// @param p 解放するメモリ領域の先頭ポインタ
	/// @remark p が nullptr の場合は何も起こりません。
	template <class Type>
	inline void AlignedDelete(Type* const p);

	/// @brief ポインタが指定したサイズにアライメントされているかを返します。
	/// @param p アライメントを調べるポインタ
	/// @param alignment アライメントのサイズ（バイト）
	/// @return 指定したサイズにアライメントされている場合 true, それ以外の場合は false
	[[nodiscard]]
	inline bool IsAligned(const void* p, size_t alignment) noexcept;

	/// @brief アライメントを考慮したデリータ
	/// @tparam Type オブジェクトの型
	template <class Type>
	struct AlignedDeleter
	{
		void operator ()(Type* p);
	};

	/// @brief 明示的なアライメントの指定が必要な型であるかを判定します。
	/// @tparam Type オブジェクトの型
	template <class Type>
	struct IsOverAligned
		: std::bool_constant<(alignof(Type) > Platform::MinAlignment)> {};

	/// @brief 明示的なアライメントの指定が必要な型であるかを示します。
	/// @tparam Type オブジェクトの型
	template <class Type>
	constexpr bool IsOverAligned_v = IsOverAligned<Type>::value;
}

# include "detail/Memory.ipp"
