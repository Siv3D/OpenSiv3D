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
# include <memory>
# include <mutex>
# include <Siv3D/Array.hpp>
# include <Siv3D/HashTable.hpp>
# include <Siv3D/UniqueResource.hpp>
# include <Siv3D/Mat3x2.hpp>
# include <Siv3D/CursorStyle.hpp>
# include <Siv3D/Cursor/ICursor.hpp>
# include <Siv3D/Windows/Windows.hpp>

namespace s3d
{
	class CCursor final : public ISiv3DCursor
	{
	public:

		CCursor();

		~CCursor() override;

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

		////////////////////////////////////////////////////////////////
		//
		//	Windows
		//
		void handleMessage(UINT message, WPARAM wParam, LPARAM lParam);

		void onSetCursor();

	private:

		HWND m_hWnd = nullptr;

		std::mutex m_clientPosBufferMutex;
		Array<std::pair<uint64, Point>> m_clientPosBuffer;

		CursorState m_state;

		Mat3x2 m_transformLocal		= Mat3x2::Identity();
		Mat3x2 m_transformCamera	= Mat3x2::Identity();
		Mat3x2 m_transformScreen	= Mat3x2::Identity();
		Mat3x2 m_transformAll		= Mat3x2::Identity();
		Mat3x2 m_transformAllInv	= Mat3x2::Identity();

		bool m_clippedToWindow = false;

		static void CursorDeleter(HICON h)
		{
			::DestroyIcon(h);
		}

		std::array<HCURSOR, 11> m_systemCursors;
		HICON m_currentCursor = nullptr;
		HICON m_defaultCursor = nullptr;
		HICON m_requestedCursor = nullptr;
		HashTable<String, unique_resource<HICON, decltype(&CursorDeleter)>> m_customCursors;

		bool m_captured = false;

		void confineCursor();
	};
}

