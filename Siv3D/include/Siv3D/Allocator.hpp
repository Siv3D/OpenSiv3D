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
# include "Common.hpp"
# include "Memory.hpp"

namespace s3d
{
	/// @brief メモリアライメント対応アロケータ
	/// @tparam Type アロケーションするオブジェクトの型
	/// @tparam Alignment アライメント（バイト）
	template <class Type, size_t Alignment = alignof(Type)>
	class Allocator
	{
	public:

		static_assert(!std::is_const_v<Type>, "Allocator<const Type> is ill-formed.");

		using value_type								= Type;
		using size_type									= std::size_t;
		using difference_type							= std::ptrdiff_t;
		using propagate_on_container_move_assignment	= std::true_type;
		using is_always_equal							= std::true_type;

		static constexpr size_t alignment = Alignment;

		SIV3D_NODISCARD_CXX20
		constexpr Allocator() noexcept = default;

		SIV3D_NODISCARD_CXX20
		constexpr Allocator(const Allocator&) noexcept = default;

		template <class Other>
		SIV3D_NODISCARD_CXX20
		constexpr Allocator(const Allocator<Other>&) noexcept {}

		[[nodiscard]]
	# if SIV3D_PLATFORM(WINDOWS)
		__declspec(allocator)
	# endif
		Type* allocate(size_t n);

		void deallocate(Type* p, size_t);
	};

	template <class T1, class T2>
	[[nodiscard]]
	inline constexpr bool operator ==(const Allocator<T1>&, const Allocator<T2>&) noexcept;

	/// @brief メモリアライメントを考慮したデフォルトのアロケータ
	/// @tparam Type アロケーションするオブジェクトの型
	template <class Type>
	struct DefaultAllocator
	{
		using type = std::conditional_t<IsOverAligned_v<Type>, Allocator<Type>, std::allocator<Type>>;
	};
}

# include "detail/Allocator.ipp"
