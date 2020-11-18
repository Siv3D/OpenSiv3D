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

		void addLine(const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2]) override;

		void addRect(const FloatRect& rect, const Float4& color) override;
	};
}
