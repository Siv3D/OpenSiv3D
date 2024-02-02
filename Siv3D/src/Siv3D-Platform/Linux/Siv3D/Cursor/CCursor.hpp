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
# include <Siv3D/HashTable.hpp>
# include <Siv3D/UniqueResource.hpp>
# include <Siv3D/Mat3x2.hpp>
# include <Siv3D/CursorStyle.hpp>
# include <Siv3D/Cursor/ICursor.hpp>
# include <Siv3D/Common/OpenGL.hpp>

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

	private:

		GLFWwindow* m_window = nullptr;

		CursorState m_state;

		Mat3x2 m_transformLocal		= Mat3x2::Identity();
		Mat3x2 m_transformCamera	= Mat3x2::Identity();
		Mat3x2 m_transformScreen	= Mat3x2::Identity();
		Mat3x2 m_transformAll		= Mat3x2::Identity();
		Mat3x2 m_transformAllInv	= Mat3x2::Identity();	

		bool m_clipToWindow = false;

		static void CursorDeleter(GLFWcursor* h)
		{
			::glfwDestroyCursor(h);
		}

		std::array<GLFWcursor*, 11> m_systemCursors;
		GLFWcursor* m_currentCursor = nullptr;
		GLFWcursor* m_defaultCursor = nullptr;
		GLFWcursor* m_requestedCursor = nullptr;
		HashTable<String, unique_resource<GLFWcursor*, decltype(&CursorDeleter)>> m_customCursors;

		bool m_captured = false;
	};
}
