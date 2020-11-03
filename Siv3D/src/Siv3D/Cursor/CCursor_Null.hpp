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
# include <Siv3D/Array.hpp>
# include <Siv3D/Cursor/ICursor.hpp>

namespace s3d
{
	class CCursor_Null final : public ISiv3DCursor
	{
	private:

		CursorState m_state;

	public:

		CCursor_Null();

		~CCursor_Null() override;

		void init() override;

		bool update() override;
		
		const CursorState& getState() const noexcept override;

		void setPos(Point pos) override;

		bool isClippedToWindow() const noexcept override;

		void clipToWindow(bool clip) override;

		void requestStyle(CursorStyle style) override;

		void setDefaultStyle(CursorStyle style) override;

		bool registerCursor(StringView name, const Image& image, Point hotSpot) override;

		void requestStyle(StringView name) override;
	};
}
