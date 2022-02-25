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
# include <array>
# include "../Common.hpp"
# include "P2Fwd.hpp"
# include "P2Contact.hpp"

namespace s3d
{
	/// @brief 2 つの物体 A, B 間の接触に関する情報
	/// @remark 最大 2 つの P2Contact を持ちます。
	class P2Collision
	{
	public:

		/// @brief 物体 A から物体 B への接触の方向ベクトル返します。
		/// @return 物体 A から物体 B への接触の方向ベクトル
		[[nodiscard]]
		constexpr Vec2 normal() const noexcept;

		/// @brief 発生した衝突の先頭イテレータを返します。
		/// @return 発生した衝突の先頭イテレータ
		[[nodiscard]]
		std::array<P2Contact, 2>::const_iterator begin() const noexcept;

		/// @brief 発生した衝突の終端イテレータを返します。
		/// @return 発生した衝突の終端イテレータ
		[[nodiscard]]
		std::array<P2Contact, 2>::const_iterator end() const noexcept;

		/// @brief 発生した衝突の数（最大 2）を返します。
		/// @return 発生した衝突の数
		[[nodiscard]]
		constexpr size_t num_contacts() const noexcept;

		/// @brief 発生した衝突の情報を返します。
		/// @param index 衝突のインデックス
		/// @remark index は `num_contacts()` 未満である必要があります。
		/// @return 発生した衝突の情報
		[[nodiscard]]
		const P2Contact& contact(size_t index) const noexcept;

		/// @brief 衝突が発生しているかを返します。
		/// @remark `0 < num_contacts()` を返します。
		/// @return 衝突が発生している場合 true, それ以外の場合は false
		[[nodiscard]]
		constexpr bool hasContacts() const noexcept;

	private:

		std::array<P2Contact, 2> m_contacts;

		Vec2 m_normal = { 0.0, 0.0 };

		uint32 m_internalCount = 1;

		uint32 m_num_contacts = 0;

		friend class detail::P2ContactListener;
	};
}

# include "detail/P2Collision.ipp"
