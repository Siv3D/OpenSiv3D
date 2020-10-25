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
# include <Siv3D/Rectangle.hpp>
# include <Siv3D/ColorHSV.hpp>
# include <Siv3D/TextureFilter.hpp>

namespace s3d
{
	class SIV3D_NOVTABLE ISiv3DRenderer2D
	{
	public:

		static ISiv3DRenderer2D* Create();

		virtual ~ISiv3DRenderer2D() = default;

		virtual void init() = 0;

		virtual void test_renderRectangle(const RectF& rect, const ColorF& color) = 0;
	};
}
