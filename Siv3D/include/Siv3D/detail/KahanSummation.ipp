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

namespace s3d
{
	template <class Float>
	inline constexpr KahanSummation<Float>::KahanSummation(const Float init) noexcept
		: m_sum{ init } {}

	template <class Float>
	inline constexpr void KahanSummation<Float>::operator +=(const Float value) noexcept
	{
		const Float y = (value - m_err);
		const Float t = (m_sum + y);
		m_err = ((t - m_sum) - y);
		m_sum = t;
	}

	template <class Float>
	inline constexpr Float KahanSummation<Float>::value() const noexcept
	{
		return m_sum;
	}
}
