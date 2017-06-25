//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_LINUX)

# include "ICursor.hpp"
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Rectangle.hpp>
# include <Siv3D/Mat3x2.hpp>
# include <Siv3D/Cursor.hpp>
# include "../Window/IWindow.hpp"

namespace s3d
{
	class CCursor_Linux : public ISiv3DCursor
	{
	private:

		WindowHandle m_glfwWindow = nullptr;

		CursorState<Point> m_screen;

		CursorState<Point> m_client_raw;

		CursorState<Vec2> m_client_transformedF;

		CursorState<Point> m_client_transformed;

		Mat3x2 m_transform = Mat3x2::Identity();

		Mat3x2 m_transformInv = Mat3x2::Identity();

		Optional<Rect> m_clipRect;

	public:

		CCursor_Linux();

		~CCursor_Linux() override;

		bool init() override;

		void update() override;

		const CursorState<Point>& screen() const override;

		const CursorState<Point>& clientRaw() const override;

		const CursorState<Vec2>& clientTransformedF() const override;

		const CursorState<Point>& clientTransformed() const override;

		void setPos(int32 x, int32 y) override;

		void setTransform(const Mat3x2& matrix) override;

		const Mat3x2& getTransform() const override;

		void clipClientRect(bool clip) override
		{
			// [Siv3D ToDo]
		}

		void clip(const Optional<Rect>& rect) override;

		void setStyle(CursorStyle style) override;

		CursorStyle getStyle() override;
	};
}

# endif
