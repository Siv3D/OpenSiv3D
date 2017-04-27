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
# include <cstdlib>
# include <memory>
# include <type_traits>
# include "Fwd.hpp"

namespace s3d
{
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
	template <class Type, size_t Alignment = alignof(Type), std::enable_if_t<(Alignment > SIV3D_PLATFORM_PTR_SIZE)>* = nullptr>
	inline Type* AlignedMalloc(const size_t n = 1)
	{
	# if defined(SIV3D_TARGET_WINDOWS)

		return static_cast<Type*>(::_aligned_malloc(sizeof(Type) * n, Alignment));

	# else

		void* p;
		::posix_memalign(&p, Alignment, sizeof(Type) * n);
		return static_cast<Type*>(p);
	
	# endif	
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
	template <class Type, size_t Alignment = alignof(Type), std::enable_if_t<(Alignment <= SIV3D_PLATFORM_PTR_SIZE)>* = nullptr>
	inline Type* AlignedMalloc(const size_t n = 1)
	{
	# if defined(SIV3D_TARGET_WINDOWS)
		
		return static_cast<Type*>(::_aligned_malloc(sizeof(Type) * n, Alignment));
		
	# else
		
		return static_cast<Type*>(::malloc(sizeof(Type) * n));
		
	# endif
	}

	/// <summary>
	/// AlignedMalloc() で確保したメモリ領域を解放します。
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
	inline void AlignedFree(void* const p)
	{
	# if defined(SIV3D_TARGET_WINDOWS)

		::_aligned_free(p);

	# else

		::free(p);

	# endif
	}

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
	template <class Type, class ...Args>
	inline Type* AlignedNew(Args&&... args)
	{
		Type* p = AlignedMalloc<Type>();

		if (p == nullptr)
		{
			throw std::bad_alloc();
		}

		try
		{
			::new (p) Type(std::forward<Args>(args)...);
		}
		catch (...)
		{
			AlignedFree(p);

			throw;
		}

		return p;
	}

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
	inline void AlignedDelete(Type* const p)
	{
		if (p == nullptr)
		{
			return;
		}

		p->~Type();

		AlignedFree(p);
	}

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
	inline bool IsAligned(const void* const p, const size_t alignment) noexcept
	{
		return (reinterpret_cast<size_t>(p) % alignment) == 0;
	}

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
		: std::integral_constant<bool, (alignof(Type) > SIV3D_ALLOCATOR_MIN_ALIGNMENT)> {};

	/// <summary>
	/// アライメントを考慮して、unique_ptr を構築します。
	/// </summary>
	/// <param name="args">
	/// コンストラクタ引数
	/// </param>
	/// <returns>
	/// 構築した unique_ptr
	/// </returns>
	template <class Type, class ...Args, std::enable_if_t<!IsOverAligned<Type>::value>* = nullptr>
	std::unique_ptr<Type> MakeUnique(Args&&... args)
	{
		return std::make_unique<Type>(std::forward<Args>(args)...);
	}

	/// <summary>
	/// アライメントを考慮して、unique_ptr を構築します。
	/// </summary>
	/// <param name="args">
	/// コンストラクタ引数
	/// </param>
	/// <returns>
	/// 構築した unique_ptr
	/// </returns>
	template <class Type, class ...Args, std::enable_if_t<IsOverAligned<Type>::value>* = nullptr>
	std::unique_ptr<Type, AlignedDeleter<Type>> MakeUnique(Args&&... args)
	{
		return std::unique_ptr<Type, AlignedDeleter<Type>>(AlignedNew<Type>(std::forward<Args>(args)...));
	}

	/// <summary>
	/// アライメントを考慮して、shared_ptr を構築します。
	/// </summary>
	/// <param name="args">
	/// コンストラクタ引数
	/// </param>
	/// <returns>
	/// 構築した shared_ptr
	/// </returns>
	template <class Type, class ...Args, std::enable_if_t<!IsOverAligned<Type>::value>* = nullptr>
	std::shared_ptr<Type> MakeShared(Args&&... args)
	{
		return std::make_shared<Type>(std::forward<Args>(args)...);
	}

	/// <summary>
	/// アライメントを考慮して、shared_ptr を構築します。
	/// </summary>
	/// <param name="args">
	/// コンストラクタ引数
	/// </param>
	/// <returns>
	/// 構築した shared_ptr
	/// </returns>
	template <class Type, class ...Args, std::enable_if_t<IsOverAligned<Type>::value>* = nullptr>
	std::shared_ptr<Type> MakeShared(Args&&... args)
	{
		return std::shared_ptr<Type>(AlignedNew<Type>(std::forward<Args>(args)...), AlignedDeleter<Type>());
	}
}
