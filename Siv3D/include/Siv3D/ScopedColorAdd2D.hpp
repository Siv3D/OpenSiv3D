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
# include "Uncopyable.hpp"
# include "Optional.hpp"
# include "ColorHSV.hpp"

namespace s3d
{
	class ScopedColorAdd2D : Uncopyable
	{
	public:

		SIV3D_NODISCARD_CXX20
		ScopedColorAdd2D() = default;

		SIV3D_NODISCARD_CXX20
		explicit ScopedColorAdd2D(const ColorF& color);

		SIV3D_NODISCARD_CXX20
		explicit ScopedColorAdd2D(double rgb, double a = 0.0);

		SIV3D_NODISCARD_CXX20
		ScopedColorAdd2D(double r, double g, double b, double a = 0.0);

		SIV3D_NODISCARD_CXX20
		ScopedColorAdd2D(ScopedColorAdd2D&& other) noexcept;

		~ScopedColorAdd2D();

		//ScopedColorAdd2D& operator =(ScopedColorAdd2D && other) noexcept;

	private:

		Optional<Float4> m_oldColor;

		void clear() noexcept;
	};
}
