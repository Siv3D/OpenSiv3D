//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Array.hpp>
# include <Siv3D/Mat3x2.hpp>
# include <Siv3D/Cursor/ICursor.hpp>

namespace s3d
{
	class CCursor_Null final : public ISiv3DCursor
	{
	private:

		CursorState m_state;

		Mat3x2 m_transformLocal		= Mat3x2::Identity();
		Mat3x2 m_transformCamera	= Mat3x2::Identity();
		Mat3x2 m_transformScreen	= Mat3x2::Identity();

	public:

		CCursor_Null();

		~CCursor_Null() override;

		void init() override;

		bool update() override;
		
		const CursorState& getState() const noexcept override;

		void setPos(Point pos) override;

		const Mat3x2& getLocalTransform() const noexcept override;

		const Mat3x2& getCameraTransform() const noexcept override;

		const Mat3x2& getScreenTransform() const noexcept override;

		void setLocalTransform(const Mat3x2& matrix) override;

		void setCameraTransform(const Mat3x2& matrix) override;

		void setScreenTransform(const Mat3x2& matrix) override;

		bool isClippedToWindow() const noexcept override;

		void clipToWindow(bool clip) override;

		void requestStyle(CursorStyle style) override;

		void setDefaultStyle(CursorStyle style) override;

		bool registerCursor(StringView name, const Image& image, Point hotSpot) override;

		void requestStyle(StringView name) override;

		void setCapture(bool captured) noexcept override;

		bool isCaptured() const noexcept override;
	};
}
