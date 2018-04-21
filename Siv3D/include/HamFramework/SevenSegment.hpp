//-----------------------------------------------
//
//    This file is part of the HamFramework for Siv3D.
//
//    Copyright (C) 2014-2018 HAMSTRO
//    Copyright (c) 2017 OpenSiv3D Project
//
//    Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D.hpp>

namespace s3d
{
	namespace SevenSegment
	{
		namespace detail
		{
			inline void DrawHorizontalSegment(const Vec2& center, double w, double t, const ColorF& color)
			{
				const double x0 = center.x - w / 2;
				const double y0 = center.y - t;
				const double x1 = center.x + w / 2;
				const double y1 = center.y - t;

				const double x2 = center.x + w / 2 + t;
				const double y2 = center.y;
				const double x3 = center.x - w / 2 - t;
				const double y3 = center.y;

				const double x4 = x1;
				const double y4 = center.y + t;
				const double x5 = x0;
				const double y5 = center.y + t;

				Quad(x0, y0, x1, y1, x2, y2, x3, y3).draw(color);
				Quad(x3, y3, x2, y2, x4, y4, x5, y5).draw(color);
			}

			inline void DrawVerticalSegment(const Vec2& center, double w, double t, const ColorF& color)
			{
				const double x0 = center.x - t;
				const double y0 = center.y - w / 2;
				const double x1 = center.x;
				const double y1 = center.y - w / 2 - t;

				const double x2 = center.x;
				const double y2 = center.y + w / 2 + t;
				const double x3 = center.x - t;
				const double y3 = center.y + w / 2;

				const double x4 = center.x + t;
				const double y4 = y0;
				const double x5 = center.x + t;
				const double y5 = y3;

				Quad(x0, y0, x1, y1, x2, y2, x3, y3).draw(color);
				Quad(x1, y1, x4, y4, x5, y5, x2, y2).draw(color);
			}

			inline void DrawSegment(const Vec2& center, double w, double t, const Color& color, bool isHorizontal)
			{
				if (isHorizontal)
				{
					DrawHorizontalSegment(center, w, t, color);
				}
				else
				{
					DrawVerticalSegment(center, w, t, color);
				}
			}
		}

		inline void Draw(const std::array<bool, 7>& states, const Vec2& pos, double width, double t, double s, const ColorF& colorON, const ColorF& colorOFF)
		{
			const double w = width - t * 4;

			const double x0 = pos.x + t;
			const double x1 = pos.x + t * 2 + w / 2;
			const double x2 = pos.x + width - t;

			const double y0 = pos.y + 1 * t;
			const double y1 = pos.y + 2 * t + 0.5 * w;
			const double y2 = pos.y + 3 * t + 1.0 * w;
			const double y3 = pos.y + 4 * t + 1.5 * w;
			const double y4 = pos.y + 5 * t + 2.0 * w;

			//Horizontalならtrue
			const std::pair<Vec2, bool> positions[7] = {
				{ Vec2(x1, y0), true },
				{ Vec2(x0, y1), false },
				{ Vec2(x2, y1), false },
				{ Vec2(x1, y2), true },
				{ Vec2(x0, y3), false },
				{ Vec2(x2, y3), false },
				{ Vec2(x1, y4), true },
			};

			for (size_t i = 0; i < 7; ++i)
			{
				detail::DrawSegment(positions[i].first, w - s, t, states[i] ? colorON : colorOFF, positions[i].second);
			}
		}

		inline void DrawChar(char32 ch, const Vec2& pos, double width, double t, double s, const ColorF& colorON, const ColorF& colorOFF)
		{
			if (!InRange(ch, U'0', U'9') && ch != U' ' && ch != U'-')
			{
				return;
			}

			constexpr std::array<std::array<bool, 7>, 12> statesTable = {{
				{ true, true, true, false, true, true, true },			//0
				{ false, false, true, false, false, true, false },		//1
				{ true, false, true, true, true, false, true },			//2
				{ true, false, true, true, false, true, true },			//3
				{ false, true, true, true, false, true, false },		//4
				{ true, true, false, true, false, true, true },			//5
				{ true, true, false, true, true, true, true },			//6
				{ true, false, true, false, false, true, false },		//7
				{ true, true, true, true, true, true, true },			//8
				{ true, true, true, true, false, true, true },			//9
				{ false, false, false, false, false, false, false },	//(empty)
				{ false, false, false, true, false, false, false },		//-
			}};

			const bool isEmpty = (ch == U' ');
			const bool isMinus = (ch == U'-');
			const int32 tableIndex = isEmpty ? 10 : isMinus ? 11 : (ch - U'0');

			Draw(statesTable[tableIndex], pos, width, t, s, colorON, colorOFF);
		}

		inline void DrawText(const String& text, const Vec2& pos, double width, double t, double s, double margin, const ColorF& colorON, const ColorF& colorOFF)
		{
			for (size_t i = 0; i < text.length(); ++i)
			{
				DrawChar(text[i], { pos.x + i * (width + margin), pos.y }, width, t, s, colorON, colorOFF);
			}
		}
	}
}

/* example

# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	int32 n = 0;
	
	while (System::Update())
	{
		if (MouseL.down())
		{
			n = Random(-99999, 99999);
		}
		
		SevenSegment::DrawText(Format(n).lpad(6), Vec2(20, 20), 70, 8, 4, 10, ColorF(0, 1, 0), ColorF(0.25));
	}
}

*/
