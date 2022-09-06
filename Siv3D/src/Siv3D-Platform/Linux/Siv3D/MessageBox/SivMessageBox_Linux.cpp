//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/MessageBox.hpp>
# include <Siv3D/AsyncTask.hpp>
# include <Siv3D/Monitor.hpp>
# include <Siv3D/MonitorInfo.hpp>
# include <Siv3D/Scene.hpp>
# include <Siv3D/Error.hpp>

# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include <X11/Xatom.h>
# include <X11/Xft/Xft.h>

namespace s3d
{
	namespace detail
	{
		enum class MessageBoxButtons
		{
			OK,

			OKCancel,

			YesNo,
		};

		class SimpleMessageBox
		{
		private:
			static constexpr uint32 windowMargin = 110, buttonMarginX = 15, buttonMarginY = 4, betweenMargin = 15, messageMargin = 20, messageLineMargin = 10;
			static constexpr size_t iconWidth = 32, iconHeight = 32;
			static constexpr size_t messageMaxWidth = 540;

			Display* display;
			::Window root;
			::Window ok, yes, no, cancel;
			GC graphicContext;

			XftFont* xftFont;
			XftColor color;
			XftDraw* xftDrawRoot;
			XftDraw* xftOk, *xftCancel, *xftYes, *xftNo;

			Colormap cmap;

			int32 screen;
			uint64 white, black;

			MessageBoxStyle style;
			MessageBoxButtons buttons;

			std::tuple<size_t, size_t> calcTextSize(const char* str)
			{
				XGlyphInfo extents;
				::XftTextExtentsUtf8(display, xftFont, (FcChar8*)str, std::strlen(str), &extents);

				return std::make_tuple(extents.width, extents.height);
			}

		public:
			SimpleMessageBox(MessageBoxStyle style, MessageBoxButtons buttons) : style(style), buttons(buttons)
			{
				display = XOpenDisplay("");
				screen = DefaultScreen(display);
				white = WhitePixel(display, screen);
				black = BlackPixel(display, screen);

				if (setlocale(LC_CTYPE, "") == nullptr)
				{
					throw std::runtime_error("Can't set locale");
				}

				if (!XSupportsLocale())
				{
					throw std::runtime_error("Current locale is not supported");
				}

				xftFont = XftFontOpen(display, 0, XFT_FAMILY, XftTypeString, "", XFT_SIZE, XftTypeDouble, 14.0, nullptr);
				if (xftFont == nullptr)
				{
					throw std::runtime_error("Failed to create fontset");
				}

				cmap = DefaultColormap(display, 0);
				XftColorAllocName(display, DefaultVisual(display, 0), cmap, "black", &color);
			}

			~SimpleMessageBox()
			{
				XFreeGC(display, graphicContext);

				if (buttons == MessageBoxButtons::OKCancel)
				{
					XftDrawDestroy(xftOk);
					XftDrawDestroy(xftCancel);
					XDestroyWindow(display, ok);
					XDestroyWindow(display, cancel);
				}

				if (buttons == MessageBoxButtons::OK)
				{
					XftDrawDestroy(xftOk);
					XDestroyWindow(display, ok);
				}

				if (buttons == MessageBoxButtons::YesNo)
				{
					XftDrawDestroy(xftYes);
					XftDrawDestroy(xftNo);
					XDestroyWindow(display, yes);
					XDestroyWindow(display, no);
				}

				XftDrawDestroy(xftDrawRoot);
				XDestroyWindow(display, root);
				XCloseDisplay(display);
			}

			MessageBoxResult Show(const char* title, const char* message)
			{
				static const char* icons[] = {
					"0000001111000000"
					"0000110000110000"
					"0001000110001000"
					"0010000110000100"
					"0100000000000010"
					"0100000110000010"
					"1000000110000001"
					"1000000110000001"
					"1000000110000001"
					"1000000110000001"
					"0100000110000010"
					"0100000110000010"
					"0010000110000100"
					"0001000110001000"
					"0000110000110000"
					"0000001111000000"
					,
					"0000000000000000"
					"0000000110000000"
					"0000001001000000"
					"0000001001000000"
					"0000010000100000"
					"0000010110100000"
					"0000100110010000"
					"0000100110010000"
					"0001000110001000"
					"0001000110001000"
					"0010000000000100"
					"0010000110000100"
					"0100000110000010"
					"0100000000000010"
					"0111111111111110"
					"0000000000000000"
					,
					"0000001111000000"
					"0000110000110000"
					"0001000000001000"
					"0010000000000100"
					"0100100000010010"
					"0100010000100010"
					"1000001001000001"
					"1000000110000001"
					"1000000110000001"
					"1000001001000001"
					"0100010000100010"
					"0100100000010010"
					"0010000000000100"
					"0001000000001000"
					"0000110000110000"
					"0000001111000000"
					,
					"0000001111000000"
					"0000110000110000"
					"0001000110001000"
					"0010001111000100"
					"0100110001100010"
					"0100110000110010"
					"1000110000110001"
					"1000000001100001"
					"1000000011000001"
					"1000000110000001"
					"0100000110000010"
					"0100000000000010"
					"0010000110000100"
					"0001000110001000"
					"0000110000110000"
					"0000001111000000"
				};

				Array<std::string> messages;
				{
					std::string m = message;

					// TODO: タブの描画処理

					int32 sumLength = 0;
					std::string s;
					bool isPrevCharCR = false,
							isPrevCharLF = false;
					for (size_t i = 0; i < m.size(); ++i)
					{
						if (m.at(i) == '\n')
						{
							if (!isPrevCharCR)
							{
								messages.emplace_back(s);
								s.clear();
								isPrevCharLF = true;
							}

							isPrevCharCR = false;

							sumLength++;
							continue;
						}
						else if (m.at(i) == '\r')
						{
							if (!isPrevCharLF)
							{
								messages.emplace_back(s);
								s.clear();

								isPrevCharCR = true;
							}

							isPrevCharLF = false;

							sumLength++;
							continue;
						}

						isPrevCharCR = false;
						isPrevCharLF = false;

						s += m.at(i);
						if (i + 1 >= m.size())
						{
							messages.emplace_back(s);
							sumLength += s.size();
							s.clear();

							continue;
						}

						// 単語の途中で改行しないようにする
						const auto [w, h] = calcTextSize(s.c_str());
						if (w > messageMaxWidth)
						{
							if (std::isalpha(m.at(i)))
							{
								for (int32 j = i - 1; j >= sumLength; --j)
								{
									if (m.at(j) == ' ')
									{
										s.erase(s.begin() + s.size() - (i - j), s.end());
										i = j;
										break;
									}
								}
							}

							messages.emplace_back(s);
							sumLength += s.size();
							s.clear();
						}
					}
				}

				size_t maxMessageHeight = 0;
				size_t width = 0, height = 0;
				for (auto&& s : messages)
				{
					auto [w, h] = calcTextSize(s.c_str());
					maxMessageHeight = Max(maxMessageHeight, h);
				}

				for (auto&& s : messages)
				{
					auto [w, h] = calcTextSize(s.c_str());
					width = Max(width, w);
					height += messageLineMargin + (s.empty() ? maxMessageHeight : h);
				}

				const auto [okWidth, okHeight] = calcTextSize("OK");
				const auto [cancelWidth, cancelHeight] = calcTextSize("Cancel");
				const auto [yesWidth, yesHeight] = calcTextSize("Yes");
				const auto [noWidth, noHeight] = calcTextSize("No");

				const auto windowWidth = Max(okWidth + cancelWidth + windowMargin + iconWidth, width + windowMargin + betweenMargin + iconWidth),
							windowHeight = height + windowMargin;

				// メインウィンドウ
				const auto monitor = System::EnumerateMonitors().at(System::GetCurrentMonitorIndex());
				const size_t centerX = monitor.displayRect.w / 2,
							centerY = monitor.displayRect.h / 2;

				root = XCreateSimpleWindow(display, RootWindow(display, screen), centerX - windowWidth / 2, centerY - windowHeight / 2, windowWidth, windowHeight, 1, black, white);

				xftDrawRoot = XftDrawCreate(display, root, DefaultVisual(display, 0), cmap);

				auto sizeHints = XAllocSizeHints();
				if (sizeHints)
				{
					sizeHints->flags = USPosition | USSize | PMaxSize | PMinSize;
					sizeHints->x = centerX - windowWidth / 2;
					sizeHints->y = centerY - windowHeight / 2;
					sizeHints->width = windowWidth;
					sizeHints->height = windowHeight;

					sizeHints->min_width = sizeHints->max_width = windowWidth;
					sizeHints->min_height = sizeHints->max_height = windowHeight;
					XSetNormalHints(display, root, sizeHints);
					XFree(sizeHints);
				}

				graphicContext = XCreateGC(display, root, 0, nullptr);

				// タイトル
				XStoreName(display, root, title);
				// タイトルのUTF-8対応
				XChangeProperty(display, root, XInternAtom(display, "_NET_WM_NAME", False), XInternAtom(display, "UTF8_STRING", False),
						8, PropModeReplace, (unsigned char*)title, strlen(title));

				XSetBackground(display, graphicContext, white);
				XSetForeground(display, graphicContext, black);
				XSelectInput(display, root, ExposureMask);


				// ボタン
				switch (buttons)
				{
				case MessageBoxButtons::OK:
					{
						int32 buttonWindowX = windowWidth / 2 - (okWidth + buttonMarginX) / 2,
									buttonWindowY = windowHeight - windowMargin / 2;
						ok = XCreateSimpleWindow(display, root, buttonWindowX, buttonWindowY, okWidth + buttonMarginX, okHeight + buttonMarginY, 1, black, white);
						xftOk = XftDrawCreate(display, ok, DefaultVisual(display, 0), cmap);
						XSelectInput(display, ok, ButtonPressMask | ButtonReleaseMask | EnterWindowMask | LeaveWindowMask);
					}
					break;

				case MessageBoxButtons::OKCancel:
					{
						int32 buttonWindowX = windowWidth / 2 - (okWidth + cancelWidth + 2 * buttonMarginX + betweenMargin) / 2,
									buttonWindowY = windowHeight - windowMargin / 2;
						ok = XCreateSimpleWindow(display, root, buttonWindowX, buttonWindowY, okWidth + buttonMarginX, okHeight + buttonMarginY, 1, black, white);
						xftOk = XftDrawCreate(display, ok, DefaultVisual(display, 0), cmap);
						XSelectInput(display, ok, ButtonPressMask | ButtonReleaseMask | EnterWindowMask | LeaveWindowMask);
					}
					{
						int32 buttonWindowX = windowWidth / 2 - (okWidth + cancelWidth + 2 * buttonMarginX + betweenMargin) / 2 + okWidth + buttonMarginX + betweenMargin,
									buttonWindowY = windowHeight - windowMargin / 2;
						cancel = XCreateSimpleWindow(display, root, buttonWindowX, buttonWindowY, cancelWidth + buttonMarginX, cancelHeight + buttonMarginY, 1, black, white);
						xftCancel = XftDrawCreate(display, cancel, DefaultVisual(display, 0), cmap);
						XSelectInput(display, cancel, ButtonPressMask | ButtonReleaseMask | EnterWindowMask | LeaveWindowMask);
					}
					break;

				case MessageBoxButtons::YesNo:
					{
						int32 buttonWindowX = windowWidth / 2 - (yesWidth + noWidth + 2 * buttonMarginX + betweenMargin) / 2,
									buttonWindowY = windowHeight - windowMargin / 2;
						yes = XCreateSimpleWindow(display, root, buttonWindowX, buttonWindowY, yesWidth + buttonMarginX, yesHeight + buttonMarginY, 1, black, white);
						xftYes = XftDrawCreate(display, yes, DefaultVisual(display, 0), cmap);
						XSelectInput(display, yes, ButtonPressMask | ButtonReleaseMask | EnterWindowMask | LeaveWindowMask);
					}
					{
						int32 buttonWindowX = windowWidth / 2 - (yesWidth + noWidth + 2 * buttonMarginX + betweenMargin) / 2 + yesWidth + buttonMarginX + betweenMargin,
									buttonWindowY = windowHeight - windowMargin / 2;
						no = XCreateSimpleWindow(display, root, buttonWindowX, buttonWindowY, noWidth + buttonMarginX, noHeight + buttonMarginY, 1, black, white);
						xftNo = XftDrawCreate(display, no, DefaultVisual(display, 0), cmap);
						XSelectInput(display, no, ButtonPressMask | ButtonReleaseMask | EnterWindowMask | LeaveWindowMask);
					}
					break;
				}

				Atom wmDeleteWindowAtom = XInternAtom(display, "WM_DELETE_WINDOW", False);
				XSetWMProtocols(display, root, &wmDeleteWindowAtom, 1);
				XMapWindow(display, root);
				XMapSubwindows(display, root);
				XFlush(display);

				Array<::Window*> buttonList = {&ok, &yes, &no, &cancel};
				Array<MessageBoxResult> selectionList = {
					MessageBoxResult::OK,
					MessageBoxResult::Yes,
					MessageBoxResult::No,
					MessageBoxResult::Cancel
				};

				while (true)
				{
					XEvent event;
					XNextEvent(display, &event);
					switch (event.type)
					{
					case Expose:
						if (event.xexpose.count == 0)
						{
							int32 messageStringX = (windowWidth - width) / 2,
										messageStringY = windowMargin / 2;

							for (size_t i = 0; i < messages.size(); ++i)
							{
								const auto [w, h] = calcTextSize(messages.at(i).c_str());

								XftDrawStringUtf8(xftDrawRoot, &color, xftFont, messageStringX,
										messageStringY + (messageLineMargin + (messages.at(i).empty() ? maxMessageHeight : h)) * i,
										(FcChar8*)messages.at(i).c_str(), std::strlen(messages.at(i).c_str()));
							}

							if (style != MessageBoxStyle::Default)
							{
								for (size_t i = 0; i < iconWidth; ++i)
								{
									for (size_t j = 0; j < iconHeight; ++j)
									{
										const size_t x = i / 2,
													y = j / 2;
										const size_t idx = iconWidth / 2 * y + x;
										const char c = icons[static_cast<size_t>(style) - 1][idx];
										if (c == '1')
										{
											XDrawPoint(display, root, graphicContext, i + messageMargin, j + windowMargin / 2 - iconHeight / 2);
										}
									}
								}
							}

							switch (buttons)
							{
							case MessageBoxButtons::OK:
								{
									const auto [buttonWidth, buttonHeight] = calcTextSize("OK");
									int32 buttonStringX = buttonMarginX / 2,
												buttonStringY = buttonHeight + buttonMarginY / 2;
									XftDrawStringUtf8(xftOk, &color, xftFont, buttonStringX, buttonStringY, (FcChar8*)"OK", std::strlen("OK"));
								}
								break;

							case MessageBoxButtons::OKCancel:
								{
									const auto [buttonWidth, buttonHeight] = calcTextSize("OK");
									int32 buttonStringX = buttonMarginX / 2,
												buttonStringY = buttonHeight + buttonMarginY / 2;
									XftDrawStringUtf8(xftOk, &color, xftFont, buttonStringX, buttonStringY, (FcChar8*)"OK", std::strlen("OK"));
								}
								{
									const auto [buttonWidth, buttonHeight] = calcTextSize("Cancel");
									int32 buttonStringX = buttonMarginX / 2,
												buttonStringY = buttonHeight + buttonMarginY / 2;
									XftDrawStringUtf8(xftCancel, &color, xftFont, buttonStringX, buttonStringY, (FcChar8*)"Cancel", std::strlen("Cancel"));
								}
								break;

							case MessageBoxButtons::YesNo:
								{
									const auto [buttonWidth, buttonHeight] = calcTextSize("Yes");
									int32 buttonStringX = buttonMarginX / 2,
												buttonStringY = buttonHeight + buttonMarginY / 2;
									XftDrawStringUtf8(xftYes, &color, xftFont, buttonStringX, buttonStringY, (FcChar8*)"Yes", std::strlen("Yes"));
								}
								{
									const auto [buttonWidth, buttonHeight] = calcTextSize("No");
									int32 buttonStringX = buttonMarginX / 2,
												buttonStringY = buttonHeight + buttonMarginY / 2;
									XftDrawStringUtf8(xftNo, &color, xftFont, buttonStringX, buttonStringY, (FcChar8*)"No", std::strlen("No"));
								}
								break;
							}
							XFlush(display);
						}
						break;

					case ButtonPress:
						XSetWindowBorderWidth(display, event.xany.window, 2);
						XFlush(display);
						break;

					case ButtonRelease:
						XSetWindowBorderWidth(display, event.xany.window, 1);
						XFlush(display);

						for (size_t i = 0; i < buttonList.size(); ++i)
						{
							if (event.xany.window == *buttonList.at(i))
							{
								return selectionList.at(i);
							}
						}
						break;

					case ClientMessage:
						if (event.xclient.data.l[0] == static_cast<int64>(wmDeleteWindowAtom))
						{
							if (buttons == MessageBoxButtons::OK)
								return MessageBoxResult::OK;
							else if (buttons == MessageBoxButtons::OKCancel)
								return MessageBoxResult::Cancel;
							else
								return MessageBoxResult::Cancel;
						}
						break;
					}
				}
			}
		};

		static MessageBoxResult ShowMessageBox_impl(const char* title, const char* message, MessageBoxStyle style, MessageBoxButtons buttons)
		{
			SimpleMessageBox messageBox(style, buttons);
			return messageBox.Show(title, message);
		}

		static MessageBoxResult ShowMessageBox(const StringView title, const StringView text, MessageBoxStyle style, MessageBoxButtons buttons)
		{
			if (Scene::FrameCount() == 0)
			{
				throw Error{ U"Currentry, System::MessageBox~ cannot be called outside of a main loop in this platform (Linux)" };
			}

			auto result = Async([=]() {
					return ShowMessageBox_impl(title.narrow().c_str(), text.narrow().c_str(), style, buttons);
					}).get();

			return result;
		}
	}

	namespace System
	{
		MessageBoxResult MessageBoxOK(const StringView title, const StringView text, const MessageBoxStyle style)
		{
			return detail::ShowMessageBox(title, text, style, detail::MessageBoxButtons::OK);
		}

		MessageBoxResult MessageBoxOKCancel(const StringView title, const StringView text, const MessageBoxStyle style)
		{
			return detail::ShowMessageBox(title, text, style, detail::MessageBoxButtons::OKCancel);
		}

		MessageBoxResult MessageBoxYesNo(const StringView title, const StringView text, const MessageBoxStyle style)
		{
			return detail::ShowMessageBox(title, text, style, detail::MessageBoxButtons::YesNo);
		}
	}
}
