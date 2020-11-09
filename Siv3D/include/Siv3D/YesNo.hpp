//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Platform.hpp"

namespace s3d
{
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

		static constexpr Helper Yes{ true };

		static constexpr Helper No{ false };
	};
}
