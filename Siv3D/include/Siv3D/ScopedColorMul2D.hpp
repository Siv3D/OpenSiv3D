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
	class ScopedColorMul2D : Uncopyable
	{
	public:

		SIV3D_NODISCARD_CXX20
		ScopedColorMul2D() = default;

		SIV3D_NODISCARD_CXX20
		explicit ScopedColorMul2D(const ColorF& color);

		SIV3D_NODISCARD_CXX20
		explicit ScopedColorMul2D(double rgb, double a = 1.0);

		SIV3D_NODISCARD_CXX20
		ScopedColorMul2D(double r, double g, double b, double a = 1.0);

		SIV3D_NODISCARD_CXX20
		ScopedColorMul2D(ScopedColorMul2D&& other) noexcept;

		~ScopedColorMul2D();

		//ScopedColorMul2D& operator =(ScopedColorMul2D && other) noexcept;

	private:

		Optional<Float4> m_oldColor;

		void clear() noexcept;
	};
}
