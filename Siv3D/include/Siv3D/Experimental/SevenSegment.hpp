//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------
// s3d::SevenSegment is originally created by Hotaka Okumoto (OpenSiv3D Project)
//-----------------------------------------------

# pragma once
# include <array>
# include <Siv3D/Common.hpp>
# include <Siv3D/2DShapes.hpp>

namespace s3d
{
	namespace SevenSegment
	{
		inline void Draw(const std::array<bool, 7>& states, const Vec2& pos, double width, double t, double s, const ColorF& colorON, const ColorF& colorOFF);

		inline void DrawChar(char32 ch, const Vec2& pos, double width, double t, double s, const ColorF& colorON, const ColorF& colorOFF);
	
		inline void DrawText(StringView text, const Vec2& pos, double width, double t, double s, double margin, const ColorF& colorON, const ColorF& colorOFF);
	}
}

# include "detail/SevenSegment.ipp"

/*

# include <Siv3D.hpp>
# include <Siv3D/Experimental/SevenSegment.hpp>

void Main()
{
	int32 n = 0;

	while (System::Update())
	{
		if (MouseL.down())
		{
			n = Random(-99999, 99999);
		}

		SevenSegment::DrawText(U"{:>6}"_fmt(n), Vec2{ 40, 40 }, 70, 8, 4, 10, ColorF{ 0, 1, 0 }, ColorF{ 0.15 });

		SevenSegment::DrawText(U"{:0>6}"_fmt(Scene::FrameCount()), Vec2{ 40, 240 }, 40, 4, 1, 20, ColorF{ 1, 0.5, 0 }, ColorF{ 0, 0.2, 0.2 });
	}
}

*/
