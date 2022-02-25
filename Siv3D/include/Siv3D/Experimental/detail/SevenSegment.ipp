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
// s3d::SevenSegment is originally created by Hotaka Okumoto (OpenSiv3D Project)
//-----------------------------------------------

# pragma once

namespace s3d
{
	namespace detail
	{
		inline void DrawHorizontalSegment(const Vec2& center, const double w, const double t, const ColorF& color)
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

			Quad{ x0, y0, x1, y1, x2, y2, x3, y3 }.draw(color);
			Quad{ x3, y3, x2, y2, x4, y4, x5, y5 }.draw(color);
		}

		inline void DrawVerticalSegment(const Vec2& center, const double w, const double t, const ColorF& color)
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

			Quad{ x0, y0, x1, y1, x2, y2, x3, y3 }.draw(color);
			Quad{ x1, y1, x4, y4, x5, y5, x2, y2 }.draw(color);
		}

		inline void DrawSegment(const Vec2& center, const double size, const double halfThickness, const ColorF& color, const bool isHorizontal)
		{
			if (isHorizontal)
			{
				DrawHorizontalSegment(center, size, halfThickness, color);
			}
			else
			{
				DrawVerticalSegment(center, size, halfThickness, color);
			}
		}
	}

	namespace SevenSegment
	{
		inline void Draw(const std::array<bool, 7>& states, const Vec2& pos, const double size, const double halfThickness, const double s, const ColorF& colorON, const ColorF& colorOFF)
		{
			const double w = size - halfThickness * 4;

			const double x0 = pos.x + halfThickness;
			const double x1 = pos.x + halfThickness * 2 + w / 2;
			const double x2 = pos.x + size - halfThickness;

			const double y0 = pos.y + 1 * halfThickness;
			const double y1 = pos.y + 2 * halfThickness + 0.5 * w;
			const double y2 = pos.y + 3 * halfThickness + 1.0 * w;
			const double y3 = pos.y + 4 * halfThickness + 1.5 * w;
			const double y4 = pos.y + 5 * halfThickness + 2.0 * w;

			// Horizontalならtrue
			const std::pair<Vec2, bool> positions[7] = {
				{ Vec2{ x1, y0 }, true },
				{ Vec2{ x0, y1 }, false },
				{ Vec2{ x2, y1 }, false },
				{ Vec2{ x1, y2 }, true },
				{ Vec2{ x0, y3 }, false },
				{ Vec2{ x2, y3 }, false },
				{ Vec2{ x1, y4 }, true },
			};

			for (size_t i = 0; i < 7; ++i)
			{
				detail::DrawSegment(positions[i].first, (w - s), halfThickness, (states[i] ? colorON : colorOFF), positions[i].second);
			}
		}

		inline void DrawChar(const char32 ch, const Vec2& pos, const double size, const double halfThickness, const double s, const ColorF& colorON, const ColorF& colorOFF)
		{
			if (not InRange(ch, U'0', U'9')
				&& (ch != U' ')
				&& (ch != U'-'))
			{
				return;
			}

			constexpr std::array<std::array<bool, 7>, 12> statesTable = { {
				{{ true, true, true, false, true, true, true }},		//0
				{{ false, false, true, false, false, true, false }},	//1
				{{ true, false, true, true, true, false, true }},		//2
				{{ true, false, true, true, false, true, true }},		//3
				{{ false, true, true, true, false, true, false }},		//4
				{{ true, true, false, true, false, true, true }},		//5
				{{ true, true, false, true, true, true, true }},		//6
				{{ true, false, true, false, false, true, false }},		//7
				{{ true, true, true, true, true, true, true }},			//8
				{{ true, true, true, true, false, true, true }},		//9
				{{ false, false, false, false, false, false, false }},	//(space)
				{{ false, false, false, true, false, false, false }},	//-
			} };

			const bool isSpace = (ch == U' ');
			const bool isMinus = (ch == U'-');
			const int32 tableIndex = (isSpace ? 10 : isMinus ? 11 : (ch - U'0'));

			Draw(statesTable[tableIndex], pos, size, halfThickness, s, colorON, colorOFF);
		}

		inline void DrawText(const StringView text, const Vec2& pos, const double size, const double halfThickness, const double s, const double margin, const ColorF& colorON, const ColorF& colorOFF)
		{
			for (size_t i = 0; i < text.length(); ++i)
			{
				DrawChar(text[i], { pos.x + i * (size + margin), pos.y }, size, halfThickness, s, colorON, colorOFF);
			}
		}
	}
}
