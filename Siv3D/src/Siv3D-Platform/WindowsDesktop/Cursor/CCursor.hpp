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
# include <mutex>
# include <atomic>
# include <Siv3D/Windows.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3D/Mat3x2.hpp>
# include <Cursor/ICursor.hpp>

namespace s3d
{
	class CCursor : public ISiv3DCursor
	{
	private:

		HWND m_hWnd = nullptr;

		std::mutex m_mutexMouseMove;
		Array<std::pair<Point, uint64>> m_buffer_internal;
		Array<std::pair<Point, uint64>> m_buffer;
		Array<std::pair<Point, uint64>> m_bufferTransformed;

		CursorState<Point> m_screen;
		CursorState<Point> m_client_raw;
		CursorState<Vec2> m_client_transformedF;
		CursorState<Point> m_client_transformed;

		Mat3x2 m_transformLocal = Mat3x2::Identity();
		Mat3x2 m_transformCamera = Mat3x2::Identity();
		Mat3x2 m_transformScreen = Mat3x2::Identity();

		Mat3x2 m_transformAll = Mat3x2::Identity();
		Mat3x2 m_transformAllInv = Mat3x2::Identity();

		std::atomic<bool> m_altPressed = false;
		bool m_clipToWindow = false;

		std::array<HCURSOR, 8> m_cursorStyles;
		CursorStyle m_curerntCursorStyle = CursorStyle::Default;
		CursorStyle m_defaultCursorStyle = CursorStyle::Default;
		CursorStyle m_requestedCursorStyle = CursorStyle::Default;

		void updateClip();

		void updateCursorStyle();

	public:

		CCursor();

		~CCursor() override;

		void init() override;

		void update() override;

		void onMouseMove(int32 x, int32 y) override;

		void onAltPressed() override;

		const CursorState<Point>& screen() const override;

		const CursorState<Point>& clientRaw() const override;

		const CursorState<Vec2>& clientTransformedF() const override;

		const CursorState<Point>& clientTransformed() const override;

		const Array<std::pair<Point, uint64>>& getBufferTransformed() const override;

		void setPos(const Point& pos) override;

		void setLocalTransform(const Mat3x2& matrix) override;

		void setCameraTransform(const Mat3x2& matrix) override;

		void setScreenTransform(const Mat3x2& matrix) override;

		const Mat3x2& getLocalTransform() const override;

		const Mat3x2& getCameraTransform() const override;

		const Mat3x2& getScreenTransform() const override;

		void clipToWindow(bool clip) override;

		void requestStyle(CursorStyle style) override;

		void setDefaultStyle(CursorStyle style) override;

		void applyStyleImmediately(CursorStyle style) override;

		CursorStyle getRequestedStyle() const override;

		CursorStyle getDefaultStyle() const override;
	};
}
