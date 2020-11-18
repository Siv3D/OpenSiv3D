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
# include <Siv3D/Common.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/2DShapes.hpp>

namespace s3d
{
	struct FloatRect;
	struct ColorF;

	class SIV3D_NOVTABLE ISiv3DRenderer2D
	{
	public:

		static ISiv3DRenderer2D* Create();

		virtual ~ISiv3DRenderer2D() = default;

		virtual void init() = 0;

		virtual void addLine(const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2]) = 0;

		virtual void addRect(const FloatRect& rect, const Float4& color) = 0;
	};
}
