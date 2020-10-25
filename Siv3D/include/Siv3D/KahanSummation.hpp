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
# include "Common.hpp"

namespace s3d
{
	template <class Float>
	class KahanSummation
	{
	private:

		Float m_sum = 0;
		
		Float m_err = 0;

	public:

		KahanSummation() = default;

		constexpr KahanSummation(Float init) noexcept;

		constexpr void operator +=(Float value) noexcept;

		[[nodiscard]]
		constexpr Float value() const noexcept;
	};
}

# include "detail/KahanSummation.ipp"
