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
# include <array>
# include "../Common.hpp"
# include "P2Fwd.hpp"
# include "P2Contact.hpp"

namespace s3d
{
	/// @brief 2 つの物体にはたらく全ての接触に関する情報
	/// @remark 最大 2 つの P2Contact を持ちます。
	class P2Collision
	{
	public:

		[[nodiscard]]
		constexpr Vec2 normal() const noexcept;

		[[nodiscard]]
		std::array<P2Contact, 2>::const_iterator begin() const noexcept;

		[[nodiscard]]
		std::array<P2Contact, 2>::const_iterator end() const noexcept;

		[[nodiscard]]
		constexpr size_t num_contacts() const noexcept;

		[[nodiscard]]
		const P2Contact& contact(size_t index) const noexcept;

		[[nodiscard]]
		constexpr bool isEmpty() const noexcept;

		[[nodiscard]]
		explicit constexpr operator bool() const noexcept;

	private:

		std::array<P2Contact, 2> m_contacts;

		Vec2 m_normal = { 0.0, 0.0 };

		uint32 m_internalCount = 1;

		uint32 m_num_contacts = 0;

		friend class detail::P2ContactListener;
	};
}

# include "detail/P2Collision.ipp"
