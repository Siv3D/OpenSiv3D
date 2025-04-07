//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2025 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Platform.hpp"

namespace s3d
{
	/// @brief Yes/No パラメータのためのユーティリティクラス
	/// @tparam Tag タグ名
	template <class Tag>
	struct YesNo
	{
	private:

		bool m_yesNo;

		struct Helper
		{
			bool yesNo;
		};

	public:

		SIV3D_NODISCARD_CXX20
		explicit constexpr YesNo(bool yesNo) noexcept
			: m_yesNo{ yesNo } {}

		SIV3D_NODISCARD_CXX20
		constexpr YesNo(Helper helper) noexcept
			: m_yesNo{ helper.yesNo } {}

		[[nodiscard]]
		explicit constexpr operator bool() const noexcept
		{
			return m_yesNo;
		}

		[[nodiscard]]
		constexpr bool operator ==(const YesNo<Tag>& other) const noexcept
		{
			return m_yesNo == other.m_yesNo;
		}

		[[nodiscard]]
		constexpr bool operator ==(const Helper& other) const noexcept
		{
			return m_yesNo == other.yesNo;
		}

		[[nodiscard]]
		constexpr bool getBool() const noexcept
		{
			return m_yesNo;
		}

		/// @brief Yes を示す定数
		static constexpr Helper Yes{ true };

		/// @brief No を示す定数
		static constexpr Helper No{ false };
	};
}
