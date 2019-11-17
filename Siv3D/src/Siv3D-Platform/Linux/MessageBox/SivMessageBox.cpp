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

# include <Siv3D/MessageBox.hpp>
# define SIV3D_CONCURRENT
# include <Siv3D/ConcurrentTask.hpp>
# include <Siv3D/Monitor.hpp>
# include <Siv3D/Scene.hpp>
# include <Siv3D/Error.hpp>

# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include <X11/Xatom.h>

// X11でマクロNoneが定義されており，MessageBoxSelection::Noneと競合するためundef
# undef None

namespace s3d
{
	class SimpleMessageBox
	{
	private:
		static constexpr uint32 windowMargin = 110, buttonMarginX = 15, buttonMarginY = 2, betweenMargin = 15, messageMargin = 20, messageLineMargin = 10;
		static constexpr size_t iconWidth = 32, iconHeight = 32;
		static constexpr size_t messageMaxWidth = 540;

		Display* display;
		::Window root;
		::Window ok, yes, no, cancel;
		GC graphicContext;
		XFontSet fontset;

		int32 screen;
		uint64 white, black;
		int32 missingCount;
		char** missingList;
		char* defString;

		MessageBoxStyle style;
		MessageBoxButtons buttons;

		std::tuple<size_t, size_t> calcTextSize(const char* str)
		{
			XRectangle overallInk, overallLogical;
			Xutf8TextExtents(fontset, str, strlen(str), &overallInk, &overallLogical);

			return std::make_tuple(overallLogical.width, overallLogical.height);
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

			fontset = XCreateFontSet(display, "*", &missingList, &missingCount, &defString);
			if (fontset == nullptr)
			{
				throw std::runtime_error("Failed to create fontset");
			}
			XFreeStringList(missingList);

		}

		~SimpleMessageBox()
		{
			XFreeGC(display, graphicContext);
			XFreeFontSet(display, fontset);

			if (buttons == MessageBoxButtons::OKCancel)
			{
				XDestroyWindow(display, ok);
				XDestroyWindow(display, cancel);
			}

			if (buttons == MessageBoxButtons::OK)
			{
				XDestroyWindow(display, ok);
			}

			if (buttons == MessageBoxButtons::YesNo)
			{
				XDestroyWindow(display, yes);
				XDestroyWindow(display, no);
			}

			XDestroyWindow(display, root);
			XCloseDisplay(display);
		}

		MessageBoxSelection Show(const char* title, const char* message)
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

				// タブ文字をスペース4文字に置換する
				for (std::string::size_type pos; (pos = m.find("\t")) != std::string::npos; )
				{
					m.replace(pos, 1, "    ");
				}

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
			const auto monitor = System::EnumerateActiveMonitors().at(System::GetCurrentMonitorIndex());
			const size_t centerX = monitor.displayRect.w / 2,
						centerY = monitor.displayRect.h / 2;

			root = XCreateSimpleWindow(display, RootWindow(display, screen), centerX - windowWidth / 2, centerY - windowHeight / 2, windowWidth, windowHeight, 1, black, white);

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
					XSelectInput(display, ok, ButtonPressMask | EnterWindowMask | LeaveWindowMask);
				}
				break;

			case MessageBoxButtons::OKCancel:
				{
					int32 buttonWindowX = windowWidth / 2 - (okWidth + cancelWidth + 2 * buttonMarginX + betweenMargin) / 2,
								buttonWindowY = windowHeight - windowMargin / 2;
					ok = XCreateSimpleWindow(display, root, buttonWindowX, buttonWindowY, okWidth + buttonMarginX, okHeight + buttonMarginY, 1, black, white);
					XSelectInput(display, ok, ButtonPressMask | EnterWindowMask | LeaveWindowMask);
				}
				{
					int32 buttonWindowX = windowWidth / 2 - (okWidth + cancelWidth + 2 * buttonMarginX + betweenMargin) / 2 + okWidth + buttonMarginX + betweenMargin,
								buttonWindowY = windowHeight - windowMargin / 2;
					cancel = XCreateSimpleWindow(display, root, buttonWindowX, buttonWindowY, cancelWidth + buttonMarginX, cancelHeight + buttonMarginY, 1, black, white);
					XSelectInput(display, cancel, ButtonPressMask | EnterWindowMask | LeaveWindowMask);
				}
				break;

			case MessageBoxButtons::YesNo:
				{
					int32 buttonWindowX = windowWidth / 2 - (yesWidth + noWidth + 2 * buttonMarginX + betweenMargin) / 2,
								buttonWindowY = windowHeight - windowMargin / 2;
					yes = XCreateSimpleWindow(display, root, buttonWindowX, buttonWindowY, yesWidth + buttonMarginX, yesHeight + buttonMarginY, 1, black, white);
					XSelectInput(display, yes, ButtonPressMask | EnterWindowMask | LeaveWindowMask);
				}
				{
					int32 buttonWindowX = windowWidth / 2 - (yesWidth + noWidth + 2 * buttonMarginX + betweenMargin) / 2 + yesWidth + buttonMarginX + betweenMargin,
								buttonWindowY = windowHeight - windowMargin / 2;
					no = XCreateSimpleWindow(display, root, buttonWindowX, buttonWindowY, noWidth + buttonMarginX, noHeight + buttonMarginY, 1, black, white);
					XSelectInput(display, no, ButtonPressMask | EnterWindowMask | LeaveWindowMask);
				}
				break;
			}

			Atom wmDeleteWindowAtom = XInternAtom(display, "WM_DELETE_WINDOW", False);
			XSetWMProtocols(display, root, &wmDeleteWindowAtom, 1);
			XMapWindow(display, root);
			XMapSubwindows(display, root);
			XFlush(display);

			Array<::Window*> buttonList = {&ok, &yes, &no, &cancel};
			Array<MessageBoxSelection> selectionList = {
				MessageBoxSelection::OK,
				MessageBoxSelection::Yes,
				MessageBoxSelection::No,
				MessageBoxSelection::Cancel
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

							Xutf8DrawString(display, root, fontset, graphicContext, messageStringX,
									messageStringY + (messageLineMargin + (messages.at(i).empty() ? maxMessageHeight : h)) * i,
									messages.at(i).c_str(), std::strlen(messages.at(i).c_str()));
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
											buttonStringY = buttonHeight - buttonMarginY / 2;
								Xutf8DrawString(display, ok, fontset, graphicContext, buttonStringX, buttonStringY, "OK", std::strlen("OK"));
							}
							break;

						case MessageBoxButtons::OKCancel:
							{
								const auto [buttonWidth, buttonHeight] = calcTextSize("OK");
								int32 buttonStringX = buttonMarginX / 2,
											buttonStringY = buttonHeight - buttonMarginY / 2;
								Xutf8DrawString(display, ok, fontset, graphicContext, buttonStringX, buttonStringY, "OK", std::strlen("OK"));
							}
							{
								const auto [buttonWidth, buttonHeight] = calcTextSize("Cancel");
								int32 buttonStringX = buttonMarginX / 2,
											buttonStringY = buttonHeight - buttonMarginY / 2;
								Xutf8DrawString(display, cancel, fontset, graphicContext, buttonStringX, buttonStringY, "Cancel", std::strlen("Cancel"));
							}
							break;

						case MessageBoxButtons::YesNo:
							{
								const auto [buttonWidth, buttonHeight] = calcTextSize("Yes");
								int32 buttonStringX = buttonMarginX / 2,
											buttonStringY = buttonHeight - buttonMarginY / 2;
								Xutf8DrawString(display, yes, fontset, graphicContext, buttonStringX, buttonStringY, "Yes", std::strlen("Yes"));
							}
							{
								const auto [buttonWidth, buttonHeight] = calcTextSize("No");
								int32 buttonStringX = buttonMarginX / 2,
											buttonStringY = buttonHeight - buttonMarginY / 2;
								Xutf8DrawString(display, no, fontset, graphicContext, buttonStringX, buttonStringY, "NO", std::strlen("No"));
							}
							break;
						}
						XFlush(display);
					}
					break;
				case ButtonPress:
					for (size_t i = 0; i < buttonList.size(); ++i)
					{
						if (event.xany.window == *buttonList.at(i))
						{
							return selectionList.at(i);
						}
					}

					break;
				case LeaveNotify:
					for (auto&& button : buttonList)
					{
						if (*button == event.xany.window)
						{
							XSetWindowBorderWidth(display, *button, 1);
						}
					}
					XFlush(display);
					break;
				case EnterNotify:
					for (auto&& button : buttonList)
					{
						if (*button == event.xany.window)
						{
							XSetWindowBorderWidth(display, *button, 2);
						}
					}
					XFlush(display);
					break;
				case ClientMessage:
					if (event.xclient.data.l[0] == static_cast<int64>(wmDeleteWindowAtom))
					{
						return MessageBoxSelection::None;
					}
					break;
				}
			}
		}
	};

	MessageBoxSelection ShowMessageBox_Linux(const char* title, const char* message, MessageBoxStyle style, MessageBoxButtons buttons)
	{
		SimpleMessageBox messageBox(style, buttons);
		return messageBox.Show(title, message);
	}

	namespace System
	{
		MessageBoxSelection ShowMessageBox(const String& title, const String& text, MessageBoxStyle style, MessageBoxButtons buttons)
		{
			if (Scene::FrameCount() == 0)
			{
				throw Error(U"Currentry, System::ShowMessageBox cannot be called outside of a main loop in this platform (Linux)");
			}

			auto result = CreateConcurrentTask([&]() {
					return ShowMessageBox_Linux(title.narrow().c_str(), text.narrow().c_str(), style, buttons);
					}).get();

			return result;
		}
	}
}
