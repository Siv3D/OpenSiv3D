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
# include <Siv3D/Renderer2D/IRenderer2D.hpp>

namespace s3d
{
	class CRenderer2D_Null final : public ISiv3DRenderer2D
	{
	private:

	public:

		CRenderer2D_Null();

		~CRenderer2D_Null() override;

		void init() override;

		void test_renderRectangle(const RectF& rect, const ColorF& color) override;

		void flush();

		void drawFullScreenTriangle(TextureFilter textureFilter);
	};
}
