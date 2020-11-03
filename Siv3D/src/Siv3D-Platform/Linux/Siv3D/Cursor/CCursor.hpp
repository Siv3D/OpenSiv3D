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
# include <variant>
# include <Siv3D/Array.hpp>
# include <Siv3D/HashTable.hpp>
# include <Siv3D/UniqueResource.hpp>
# include <Siv3D/CursorStyle.hpp>
# include <Siv3D/Cursor/ICursor.hpp>
# include <Siv3D/Common/OpenGL.hpp>

namespace s3d
{
	class CCursor final : public ISiv3DCursor
	{
	private:

		GLFWwindow* m_window = nullptr;

		CursorState m_state;

		bool m_clipToWindow = false;

		static void CursorDeleter(GLFWcursor* h)
		{
			::glfwDestroyCursor(h);
		}

		std::variant<CursorStyle, String> m_currentCursor;
		std::variant<CursorStyle, String> m_defaultCursor;
		std::variant<CursorStyle, String> m_requestedCursor;
		HashTable<String, unique_resource<GLFWcursor*, decltype(&CursorDeleter)>> m_customCursors;

	public:

		CCursor();

		~CCursor() override;

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
