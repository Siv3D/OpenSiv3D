//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "Graphics2D.hpp"
# include "Uncopyable.hpp"

namespace s3d
{
	class ScopedColorMul2D : Uncopyable
	{
	private:

		Optional<ColorF> m_oldColor;

		void clear();

	public:

		ScopedColorMul2D() = default;

		explicit ScopedColorMul2D(const ColorF& color);

		explicit ScopedColorMul2D(double rgb, double a = 1.0);

		ScopedColorMul2D(double r, double g, double b, double a = 1.0);

		ScopedColorMul2D(ScopedColorMul2D&& other);

		~ScopedColorMul2D();

		ScopedColorMul2D& operator =(ScopedColorMul2D&& other);
	};

	class ScopedColorAdd2D : Uncopyable
	{
	private:

		Optional<ColorF> m_oldColor;

		void clear();

	public:

		ScopedColorAdd2D() = default;

		explicit ScopedColorAdd2D(const ColorF& color);

		explicit ScopedColorAdd2D(double rgb, double a = 0.0);

		ScopedColorAdd2D(double r, double g, double b, double a = 0.0);

		ScopedColorAdd2D(ScopedColorAdd2D&& other);

		~ScopedColorAdd2D();

		ScopedColorAdd2D& operator =(ScopedColorAdd2D&& other);
	};
}
