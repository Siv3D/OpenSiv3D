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
# include "AlignedMemory.hpp"

namespace s3d
{
	/// <summary>
	/// メモリアライメント対応アロケータ
	/// </summary>
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

		Type* allocate(const size_t n, const void* = nullptr)
		{
			return AlignedMalloc<Type, Alignment>(n);
		}

		void deallocate(Type* const p, const size_t)
		{
			AlignedFree(p);
		}
	};

	template <class Type, class Other>
	inline constexpr bool operator ==(const AlignedAllocator<Type>&, const AlignedAllocator<Other>&) noexcept
	{
		return true;
	}

	template <class Type, class Other>
	inline constexpr bool operator !=(const AlignedAllocator<Type>&, const AlignedAllocator<Other>&) noexcept
	{
		return false;
	}
	
	/// <summary>
	/// メモリアライメントを考慮したデフォルトのアロケータ
	/// </summary>
	template <class Type>
	struct DefaultAllocator
	{
		using type = std::conditional_t<IsOverAligned<Type>::value, AlignedAllocator<Type>, std::allocator<Type>>;
	};
}
