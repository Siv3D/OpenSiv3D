//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
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

	/// <summary>
	/// アライメントを考慮して、指定した型のためのメモリ領域を確保します。
	/// </summary>
	/// <param name="n">
	/// 要素数。デフォルトは 1
	/// </param>
	/// <remarks>
	/// 確保したポインタは AlignedFree() で解放する必要があります。
	/// </remarks>
	/// <returns>
	/// 確保したメモリ領域の先頭ポインタ
	/// </returns>
	template <class Type, size_t Alignment = alignof(Type)>
	[[nodiscard]]
	inline Type* AlignedMalloc(size_t n = 1);

	/// <summary>
	/// AlignedMalloc() で確保したメモリ領域を解放します。
	/// Deallocates the space previously allocated by AlignedMalloc(),
	/// </summary>
	/// <param name="p">
	/// 解放するメモリ領域の先頭ポインタ
	/// Pointer to the memory to deallocate
	/// </param>
	/// <remarks>
	/// p が nullptr の場合は何も起こりません。
	/// The function accepts and does nothing with the null pointer.
	/// </remarks>
	/// <returns>
	/// なし
	/// (none)
	/// </returns>
	inline void AlignedFree(void* const p);

	/// <summary>
	/// アライメントを考慮して、指定した型のためのメモリ領域を確保します。
	/// </summary>
	/// <param name="args">
	/// コンストラクタ引数
	/// </param>
	/// <remarks>
	/// 確保したポインタは AlignedDelete() で解放する必要があります。
	/// </remarks>
	/// <returns>
	/// 確保したメモリ領域の先頭ポインタ
	/// </returns>
	template <class Type, class ...Args, std::enable_if_t<std::is_constructible_v<Type, Args...>>* = nullptr>
	[[nodiscard]]
	inline Type* AlignedNew(Args&&... args);

	/// <summary>
	/// AlignedNew() で確保したメモリ領域を解放します。
	/// </summary>
	/// <param name="p">
	/// 解放するメモリ領域の先頭ポインタ
	/// </param>
	/// <remarks>
	/// p が nullptr の場合は何も起こりません。
	/// </remarks>
	/// <returns>
	/// なし
	/// </returns>
	template <class Type>
	inline void AlignedDelete(Type* const p);

	/// <summary>
	/// ポインタがアライメントされているかを返します。
	/// </summary>
	/// <param name="p">
	/// アライメントを調べるポインタ
	/// </param>
	/// <param name="alignment">
	/// アライメント（バイト）
	/// </param>
	/// <returns>
	/// アライメントされている場合 true, それ以外の場合は false
	/// </returns>
	[[nodiscard]]
	inline bool IsAligned(const void* p, size_t alignment) noexcept;

	/// <summary>
	/// アライメントを考慮したデリータ
	/// </summary>
	template <class Type>
	struct AlignedDeleter
	{
		void operator()(Type* p)
		{
			AlignedDelete(p);
		}
	};

	/// <summary>
	/// 明示的なアライメントの指定が必要な型であるかを判定します。
	/// </summary>
	template <class Type>
	struct IsOverAligned
		: std::bool_constant<(alignof(Type) > Platform::MinAlignment)> {};

	template <class Type>
	constexpr bool IsOverAligned_v = IsOverAligned<Type>::value;
}

# include "detail/Memory.ipp"
