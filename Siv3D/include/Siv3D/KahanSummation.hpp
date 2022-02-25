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

namespace s3d
{
	template <class Float>
	class KahanSummation
	{
	public:

		SIV3D_NODISCARD_CXX20
		KahanSummation() = default;

		SIV3D_NODISCARD_CXX20
		constexpr KahanSummation(Float init) noexcept;

		constexpr void operator +=(Float value) noexcept;

		[[nodiscard]]
		constexpr Float value() const noexcept;

	private:

		Float m_sum = 0;

		Float m_err = 0;
	};
}

# include "detail/KahanSummation.ipp"
