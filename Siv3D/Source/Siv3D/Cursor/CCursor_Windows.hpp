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
# if defined(SIV3D_TARGET_WINDOWS)

# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include "ICursor.hpp"
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Rectangle.hpp>
# include <Siv3D/Mat3x2.hpp>
# include <Siv3D/Cursor.hpp>

namespace s3d
{
	class CCursor_Windows : public ISiv3DCursor
	{
	private:

		HWND m_hWnd = nullptr;

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

		std::array<HCURSOR, 8> m_cursorStyles;

		bool m_clipClientRect = false;

		void updateClip();

	public:

		CCursor_Windows();

		~CCursor_Windows() override;

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

		void clipClientRect(bool clip) override;

		void clip(const Optional<Rect>& rect) override;

		void setStyle(CursorStyle style) override;

		CursorStyle getStyle() override;
	};
}

# endif
