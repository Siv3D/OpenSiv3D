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
	template <class Type, size_t Alignment = alignof(Type)>
	inline Type* AlignedMalloc(const size_t n = 1)
	{
	# if defined(SIV3D_TARGET_WINDOWS)

		return static_cast<Type*>(::_aligned_malloc(sizeof(Type) * n, Alignment));

	# else

		Type* p;
		::posix_memalign(&p, Alignment, sizeof(Type) * n);
		return p;
	
	# endif	
	}

	inline void AlignedFree(void* p)
	{
	# if defined(SIV3D_TARGET_WINDOWS)

		::_aligned_free(p);

	# else

		::free(p);

	# endif
	}

	template <class Type>
	struct HasAlignment
		: std::integral_constant<bool, (alignof(Type) > SIV3D_ALLOCATOR_MIN_ALIGNMENT)> {};

	template <class Type, class ...Args>
	inline auto AlignedNew(Args&&... args)
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

	template <class Type>
	inline void AlignedDelete(Type* p)
	{
		if (p == nullptr)
		{
			return;
		}

		p->~Type();

		AlignedFree(p);
	}

	template <class Type>
	struct AlignedDeleter
	{
		void operator()(Type* p)
		{
			AlignedDelete(p);
		}
	};

	template <class Type, class ...Args>
	std::unique_ptr<Type, AlignedDeleter<Type>> AlignedUnique(Args&&... args)
	{
		return std::unique_ptr<Type, AlignedDeleter<Type>>(AlignedNew<Type>(std::forward<Args>(args)...));
	}

	template <class Type, class ...Args>
	std::shared_ptr<Type> AlignedShared(Args&&... args)
	{
		return std::shared_ptr<Type>(AlignedNew<Type>(std::forward<Args>(args)...), AlignedDeleter<Type>());
	}

	template <class Type, class ...Args, std::enable_if_t<!HasAlignment<Type>::value>* = nullptr>
	std::unique_ptr<Type> MakeUnique(Args&&... args)
	{
		return std::make_unique<Type>(std::forward<Args>(args)...);
	}

	template <class Type, class ...Args, std::enable_if_t<HasAlignment<Type>::value>* = nullptr>
	std::unique_ptr<Type, AlignedDeleter<Type>> MakeUnique(Args&&... args)
	{
		return AlignedUnique<Type>(std::forward<Args>(args)...);
	}

	template <class Type, class ...Args, std::enable_if_t<!HasAlignment<Type>::value>* = nullptr>
	std::shared_ptr<Type> MakeShared(Args&&... args)
	{
		return std::make_shared<Type>(std::forward<Args>(args)...);
	}

	template <class Type, class ...Args, std::enable_if_t<HasAlignment<Type>::value>* = nullptr>
	std::shared_ptr<Type> MakeShared(Args&&... args)
	{
		return std::shared_ptr<Type>(AlignedNew<Type>(std::forward<Args>(args)...), AlignedDeleter<Type>());
	}

	inline bool IsAligned(const void* const p, const size_t alignment) noexcept
	{
		return (reinterpret_cast<size_t>(p) % alignment) == 0;
	}
}
