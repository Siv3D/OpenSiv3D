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

# include <Siv3D/MessageBox.hpp>
# include <Siv3D/AsyncTask.hpp>
# include <Siv3D/Window.hpp>
# include <Siv3D/Font.hpp>
# include <Siv3D/DrawableText.hpp>
# include <Siv3D/System.hpp>
# include <Siv3D/Scene.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3D/CursorStyle.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/SimpleGUI.hpp>
# include <Siv3D/Transformer2D.hpp>
# include <Siv3D/ScopedRenderStates2D.hpp>
# include <Siv3D/ScopedRenderTarget2D.hpp>
# include <Siv3D/ScopedColorAdd2D.hpp>
# include <Siv3D/ScopedColorMul2D.hpp>
# include <Siv3D/UserAction.hpp>
# include <Siv3D/WindowState.hpp>
# include <Siv3D/Windows/Windows.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace detail
	{
		static constexpr int32 MessageBoxStyleFlags[5] =
		{
			0,
			MB_ICONINFORMATION,
			MB_ICONWARNING,
			MB_ICONERROR,
			MB_ICONQUESTION,
		};

		static MessageBoxResult ShowMessageBox(const StringView title, const StringView text, const MessageBoxStyle style, const int32 buttons)
		{
			if (Window::GetState().fullscreen)
			{
				return MessageBoxResult::Cancel;
			}

			const int32 flag = (MessageBoxStyleFlags[static_cast<int32>(style)] | buttons);

			const int32 result = Async([=]()
				{
					const HWND hWnd = static_cast<HWND>(SIV3D_ENGINE(Window)->getHandle());
					return ::MessageBoxW(hWnd, text.toWstr().c_str(), title.toWstr().c_str(), flag);
				}).get();

			switch (result)
			{
			case IDOK:
				return MessageBoxResult::OK;
			case IDCANCEL:
			default:
				return MessageBoxResult::Cancel;
			case IDYES:
				return MessageBoxResult::Yes;
			case IDNO:
				return MessageBoxResult::No;
			}
		}

		class SceneMessageBoxImpl
		{
		public:

			static constexpr Size MessageBoxSize{ 360, 240 };

			static constexpr Size MessageBoxButtonSize{ 120, 40 };

			static constexpr ColorF MessageBoxBackgroundColor{ 0.96 };

			static constexpr ColorF MessageBoxActiveButtonColor{ 1.0 };

			static constexpr ColorF MessageBoxTextColor{ 0.11 };

			SceneMessageBoxImpl()
			{
				System::SetTerminationTriggers(UserAction::CloseButtonClicked);
				Scene::SetBackground(ColorF{ 0.11 });
			}

			~SceneMessageBoxImpl()
			{
				System::SetTerminationTriggers(m_triggers);
				Scene::SetBackground(m_bgColor);
			}

			MessageBoxResult show(StringView text, const std::pair<String, MessageBoxResult>& button) const
			{
				while (System::Update())
				{
					drawMessageBox(text);
					m_buttonC.draw(m_buttonC.mouseOver() ? MessageBoxActiveButtonColor : MessageBoxBackgroundColor).drawFrame(0, 1, MessageBoxTextColor);
					m_font(button.first).drawAt(m_buttonC.center().moveBy(0, -1), MessageBoxTextColor);

					if (m_buttonC.mouseOver())
					{
						Cursor::RequestStyle(CursorStyle::Hand);

						if (MouseL.down())
						{
							break;
						}
					}
				}

				return button.second;
			}

			MessageBoxResult show(const StringView text, const std::pair<String, MessageBoxResult>& button0, const std::pair<String, MessageBoxResult>& button1) const
			{
				MessageBoxResult result = MessageBoxResult::Cancel;

				while (System::Update())
				{
					drawMessageBox(text);
					m_buttonL.draw(m_buttonL.mouseOver() ? MessageBoxActiveButtonColor : MessageBoxBackgroundColor).drawFrame(0, 1, MessageBoxTextColor);
					m_buttonR.draw(m_buttonR.mouseOver() ? MessageBoxActiveButtonColor : MessageBoxBackgroundColor).drawFrame(0, 1, MessageBoxTextColor);
					m_font(button0.first).drawAt(m_buttonL.center().moveBy(0, -1), MessageBoxTextColor);
					m_font(button1.first).drawAt(m_buttonR.center().moveBy(0, -1), MessageBoxTextColor);

					if (m_buttonL.mouseOver())
					{
						Cursor::RequestStyle(CursorStyle::Hand);

						if (MouseL.down())
						{
							result = button0.second;
							break;
						}
					}
					else if (m_buttonR.mouseOver())
					{
						Cursor::RequestStyle(CursorStyle::Hand);

						if (MouseL.down())
						{
							result = button1.second;
							break;
						}
					}
				}

				return result;
			}

			static MessageBoxResult ShowOK(StringView text)
			{
				return SceneMessageBoxImpl{}.show(text, { U"OK", MessageBoxResult::OK });
			}

			[[nodiscard]]
			static MessageBoxResult ShowOKCancel(StringView text)
			{
				return SceneMessageBoxImpl{}.show(text, { U"OK", MessageBoxResult::OK }, { U"Cancel", MessageBoxResult::Cancel });
			}

			[[nodiscard]]
			static MessageBoxResult ShowYesNo(StringView text)
			{
				return SceneMessageBoxImpl{}.show(text, { U"Yes", MessageBoxResult::Yes }, { U"No", MessageBoxResult::No });
			}

		private:

			Transformer2D m_tr{ Mat3x2::Identity(), Mat3x2::Identity(), Transformer2D::Target::SetLocal };

			ScopedRenderStates2D m_rs{ BlendState::Default2D, SamplerState::Default2D, RasterizerState::Default2D };

			ScopedRenderTarget2D m_rt{ none };

			ScopedColorAdd2D m_add{ 0.0 };

			ScopedColorMul2D m_mul{ 1.0 };

			uint32 m_triggers = System::GetTerminationTriggers();

			ColorF m_bgColor = Scene::GetBackground();

			Vec2 m_pos = ((Scene::Size() - MessageBoxSize) * 0.5);

			RectF m_messageBoxRect{ m_pos, MessageBoxSize };

			RectF m_buttonC = RectF{ Arg::bottomCenter(m_messageBoxRect.bottomCenter().movedBy(0, -20)), MessageBoxButtonSize };

			RectF m_buttonL = RectF{ Arg::bottomCenter(m_messageBoxRect.bottomCenter().movedBy(-80, -20)), MessageBoxButtonSize };

			RectF m_buttonR = RectF{ Arg::bottomCenter(m_messageBoxRect.bottomCenter().movedBy(80, -20)), MessageBoxButtonSize };

			Font m_font = SimpleGUI::GetFont();

			void drawMessageBox(StringView text) const
			{
				m_messageBoxRect.draw(MessageBoxBackgroundColor).stretched(-5).drawFrame(1, 0, MessageBoxTextColor);
				m_font(text).draw(14, m_messageBoxRect.stretched(-20, -20, -80, -20), MessageBoxTextColor);
			}
		};
	}

	namespace System
	{
		MessageBoxResult MessageBoxOK(const StringView title, const StringView text, const MessageBoxStyle style)
		{
			if (Window::GetState().fullscreen)
			{
				return detail::SceneMessageBoxImpl::ShowOK(text);
			}
			else
			{
				return detail::ShowMessageBox(title, text, style, MB_OK);
			}
		}

		MessageBoxResult MessageBoxOKCancel(const StringView title, const StringView text, const MessageBoxStyle style)
		{
			if (Window::GetState().fullscreen)
			{
				return detail::SceneMessageBoxImpl::ShowOKCancel(text);
			}
			else
			{
				return detail::ShowMessageBox(title, text, style, MB_OKCANCEL);
			}
		}

		MessageBoxResult MessageBoxYesNo(const StringView title, const StringView text, const MessageBoxStyle style)
		{
			if (Window::GetState().fullscreen)
			{
				return detail::SceneMessageBoxImpl::ShowYesNo(text);
			}
			else
			{
				return detail::ShowMessageBox(title, text, style, MB_YESNO);
			}
		}
	}
}
