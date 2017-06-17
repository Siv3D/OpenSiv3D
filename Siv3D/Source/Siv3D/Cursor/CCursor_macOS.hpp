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

		Point m_previousScreenPos{ 0, 0 };

		Point m_screenPos{ 0, 0 };

		Point m_screenDelta{ 0, 0 };

		Point m_previousClientPos_raw{ 0, 0 };

		Point m_clientPos_raw{ 0, 0 };

		Point m_clientPos_transformedPoint{ 0, 0 };

		Vec2 m_clientPos_transformedVec2{ 0, 0 };

		Point m_previousClientPos_transformedPoint{ 0, 0 };

		Vec2 m_previousClientPos_transformedVec2{ 0, 0 };

		Mat3x2 m_transform = Mat3x2::Identity();

		Mat3x2 m_transformInv = Mat3x2::Identity();

		Optional<Rect> m_clipRect;

		CursorStyle m_curerntCursorStyle = CursorStyle::Default;

	public:

		CCursor_macOS();

		~CCursor_macOS() override;

		bool init() override;

		void update() override;

		const Point& previousScreenPos() const override;

		const Point& screenPos() const override;

		const Point& screenDelta() const override;

		const Point& previousClientPos() const override;

		const Point& clientPos() const override;

		Point clientDelta() const override;

		const Vec2& previousClientPosF() const override;

		const Vec2& clientPosF() const override;

		Vec2 clientDeltaF() const override;

		void setPos(int32 x, int32 y) override;

		void setTransform(const Mat3x2& matrix) override;

		const Mat3x2& getTransform() const override;

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
