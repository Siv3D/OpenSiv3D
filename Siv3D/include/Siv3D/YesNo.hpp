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

		constexpr YesNo(Helper helper) noexcept
			: m_yesNo(helper.yesNo) {}

		[[nodiscard]]
		explicit constexpr operator bool() const noexcept
		{
			return m_yesNo;
		}

		static constexpr Helper Yes{ true };

		static constexpr Helper No{ false };
	};
}
