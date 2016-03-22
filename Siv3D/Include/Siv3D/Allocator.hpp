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
# include <memory>
# include <limits>
# include <type_traits>
# include "Fwd.hpp"

namespace s3d
{
	template <class Type>
	class AlignedAllocator
	{
	public:

		static_assert(!std::is_const<Type>::value, "AlignedAllocator<const Type> is ill-formed.");

		using value_type		= Type;
		using pointer			= Type*;
		using const_pointer		= const Type*;
		using reference			= Type&;
		using const_reference	= const Type&;
		using size_type			= size_t;
		using difference_type	= std::ptrdiff_t;
		using propagate_on_container_move_assignment	= std::true_type;
		using is_always_equal							= std::true_type;
		template <class Other> struct rebind { using other = AlignedAllocator<Other>; };

		static constexpr size_t alignment = alignof(Type);

		AlignedAllocator() noexcept {}

		AlignedAllocator(const AlignedAllocator<Type>&) noexcept {}

		template <class Other>
		AlignedAllocator(const AlignedAllocator<Other>&) noexcept {}

		pointer address(reference value) const noexcept
		{
			return std::addressof(value);
		}

		const_pointer address(const_reference value) const noexcept
		{
			return std::addressof(value);
		}

		pointer allocate(size_type n, const void* = nullptr)
		{
			# if defined(SIV3D_TARGET_WINDOWS)
				return static_cast<pointer>(::_aligned_malloc(n * sizeof(Type), alignment));
			# else
				pointer p;
				::posix_memalign(&p, alignment, n * sizeof(Type));
				return p;
			# endif
		}

		void deallocate(pointer p, size_type)
		{
			# if defined(SIV3D_TARGET_WINDOWS)
				::_aligned_free(p);
			# else
				::free(p);
			# endif
		}

		size_t max_size() const noexcept
		{
			return std::numeric_limits<size_t>::max() / sizeof(Type);
		}

		template <class U, class... Args >
		void construct(U* p, Args&&... args)
		{
			::new((void *)p) U(std::forward<Args>(args)...);
		}

		template <class U>
		void destroy(U* p)
		{
			(void)p;
			p->~U();
		}
	};

	template <class Type, class Other>
	inline bool operator ==(const AlignedAllocator<Type>&, const AlignedAllocator<Other>&) noexcept
	{
		return true;
	}

	template <class Type, class Other>
	inline bool operator !=(const AlignedAllocator<Type>&, const AlignedAllocator<Other>&) noexcept
	{
		return false;
	}
	
	template <class Type>
	struct DefaultAllocator
	{
		using type = std::conditional_t<(alignof(Type)> SIV3D_ALLOCATOR_MIN_ALIGNMENT), AlignedAllocator<Type>, std::allocator<Type>>;
	};
}
