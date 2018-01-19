//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS)

# include "ICursor.hpp"
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Rectangle.hpp>
# include <Siv3D/Mat3x2.hpp>
# include <Siv3D/Cursor.hpp>
# include "../Window/IWindow.hpp"

namespace s3d
{
	class CCursor_macOS : public ISiv3DCursor
	{
	private:

		WindowHandle m_glfwWindow = nullptr;

		CursorState<Point> m_screen;

		CursorState<Point> m_client_raw;

		CursorState<Vec2> m_client_transformedF;

		CursorState<Point> m_client_transformed;

		Mat3x2 m_transformLocal = Mat3x2::Identity();

		Mat3x2 m_transformCamera = Mat3x2::Identity();

		Mat3x2 m_transformScreen = Mat3x2::Identity();

		Mat3x2 m_transformAll = Mat3x2::Identity();

		Mat3x2 m_transformAllInv = Mat3x2::Identity();

		Optional<Rect> m_clipRect;

		CursorStyle m_curerntCursorStyle = CursorStyle::Default;

	public:

		CCursor_macOS();

		~CCursor_macOS() override;

		bool init() override;

		void update() override;

		const CursorState<Point>& screen() const override;

		const CursorState<Point>& clientRaw() const override;

		const CursorState<Vec2>& clientTransformedF() const override;

		const CursorState<Point>& clientTransformed() const override;

		void setPos(int32 x, int32 y) override;

		void setTransformLocal(const Mat3x2& matrix) override;

		void setTransformCamera(const Mat3x2& matrix) override;

		void setTransformScreen(const Mat3x2& matrix) override;

		const Mat3x2& getTransformLocal() const override;

		const Mat3x2& getTransformCamera() const override;

		const Mat3x2& getTransformScreen() const override;

		void clipClientRect(bool) override
		{
			// [Siv3D ToDo]
		}

		void clip(const Optional<Rect>& rect) override;

		void setStyle(CursorStyle style) override;

		CursorStyle getStyle() override;
	};
}

# endif
