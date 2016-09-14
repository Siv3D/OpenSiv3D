//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2016 Ryo Suzuki
//	Copyright (c) 2016 OpenSiv3D Project
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
	class AlignedAllocator
	{
	public:

		static_assert(!std::is_const<Type>::value, "AlignedAllocator<const Type> is ill-formed.");

		using value_type								= Type;
		using propagate_on_container_move_assignment	= std::true_type;
		using is_always_equal							= std::true_type;
		template <class Other> struct rebind { using other = AlignedAllocator<Other>; };

		static constexpr size_t alignment = Alignment;

		AlignedAllocator() noexcept {}

		AlignedAllocator(const AlignedAllocator<Type>&) noexcept {}

		template <class Other>
		AlignedAllocator(const AlignedAllocator<Other>&) noexcept {}

		Type* allocate(size_t n, const void* = nullptr)
		{
			# if defined (SIV3D_TARGET_WINDOWS)
				return static_cast<Type*>(::_aligned_malloc(n * sizeof(Type), Alignment));
			# else
				pointer p;
				::posix_memalign(&p, Alignment, n * sizeof(Type));
				return p;
			# endif
		}

		void deallocate(Type* p, size_t)
		{
			# if defined (SIV3D_TARGET_WINDOWS)
				::_aligned_free(p);
			# else
				::free(p);
			# endif
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
