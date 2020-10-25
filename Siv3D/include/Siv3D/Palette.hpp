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
# include "Color.hpp"

namespace s3d
{
	/// @brief 色の定数
	namespace Palette
	{
		// HTML Color Names
		// https://www.w3schools.com/colors/colors_names.asp

		inline constexpr Color Black				{   0,   0,   0 };
		inline constexpr Color Dimgray				{ 105, 105, 105 };
		inline constexpr Color Gray					{ 128, 128, 128 };
		inline constexpr Color Darkgray				{ 169, 169, 169 };
		inline constexpr Color Silver				{ 192, 192, 192 };
		inline constexpr Color Lightgrey			{ 211, 211, 211 };
		inline constexpr Color Gainsboro			{ 220, 220, 220 };
		inline constexpr Color Whitesmoke			{ 245, 245, 245 };
		inline constexpr Color White				{ 255, 255, 255 };

		inline constexpr Color Snow					{ 255, 250, 250 };
		inline constexpr Color Ghostwhite			{ 248, 248, 255 };
		inline constexpr Color Floralwhite			{ 255, 250, 240 };
		inline constexpr Color Linen				{ 250, 240, 230 };
		inline constexpr Color Antiquewhite			{ 250, 235, 215 };
		inline constexpr Color Papayawhip			{ 255, 239, 213 };
		inline constexpr Color Blanchedalmond		{ 255, 235, 205 };
		inline constexpr Color Bisque				{ 255, 228, 196 };
		inline constexpr Color Moccasin				{ 255, 228, 181 };
		inline constexpr Color Navajowhite			{ 255, 222, 173 };
		inline constexpr Color Peachpuff			{ 255, 218, 185 };
		inline constexpr Color Mistyrose			{ 255, 228, 225 };
		inline constexpr Color Lavenderblush		{ 255, 240, 245 };
		inline constexpr Color Seashell				{ 255, 245, 238 };
		inline constexpr Color Oldlace				{ 253, 245, 230 };
		inline constexpr Color Ivory				{ 255, 255, 240 };
		inline constexpr Color Honeydew				{ 240, 255, 240 };
		inline constexpr Color Mintcream			{ 245, 255, 250 };
		inline constexpr Color Azure				{ 240, 255, 255 };
		inline constexpr Color Aliceblue			{ 240, 248, 255 };
		inline constexpr Color Lavender				{ 230, 230, 250 };
		inline constexpr Color Lightsteelblue		{ 176, 196, 222 };
		inline constexpr Color Lightslategray		{ 119, 136, 153 };
		inline constexpr Color Slategray			{ 112, 128, 144 };
		inline constexpr Color Steelblue			{  70, 130, 180 };
		inline constexpr Color Royalblue			{  65, 105, 225 };
		inline constexpr Color Midnightblue			{  25,  25, 112 };
		inline constexpr Color Navy					{   0,   0, 128 };
		inline constexpr Color Darkblue				{   0,   0, 139 };
		inline constexpr Color Mediumblue			{   0,   0, 205 };
		inline constexpr Color Blue					{   0,   0, 255 };
		inline constexpr Color Dodgerblue			{  30, 144, 255 };
		inline constexpr Color Cornflowerblue		{ 100, 149, 237 };
		inline constexpr Color Deepskyblue			{   0, 191, 255 };
		inline constexpr Color Lightskyblue			{ 135, 206, 250 };
		inline constexpr Color Skyblue				{ 135, 206, 235 };
		inline constexpr Color Lightblue			{ 173, 216, 230 };
		inline constexpr Color Powderblue			{ 176, 224, 230 };
		inline constexpr Color Paleturquoise		{ 175, 238, 238 };
		inline constexpr Color Lightcyan			{ 224, 255, 255 };
		inline constexpr Color Cyan					{   0, 255, 255 };
		inline constexpr Color Aqua					{   0, 255, 255 };
		inline constexpr Color Turquoise			{  64, 224, 208 };
		inline constexpr Color Mediumturquoise		{  72, 209, 204 };
		inline constexpr Color Darkturquoise		{   0, 206, 209 };
		inline constexpr Color Lightseagreen		{  32, 178, 170 };
		inline constexpr Color Cadetblue			{  95, 158, 160 };
		inline constexpr Color Darkcyan				{   0, 139, 139 };
		inline constexpr Color Teal					{   0, 128, 128 };
		inline constexpr Color Darkslategray		{  47,  79,  79 };
		inline constexpr Color Darkgreen			{   0, 100,   0 };
		inline constexpr Color Green				{   0, 128,   0 };
		inline constexpr Color Forestgreen			{  34, 139,  34 };
		inline constexpr Color Seagreen				{  46, 139,  87 };
		inline constexpr Color Mediumseagreen		{  60, 179, 113 };
		inline constexpr Color Mediumaquamarine		{ 102, 205, 170 };
		inline constexpr Color Darkseagreen			{ 143, 188, 143 };
		inline constexpr Color Aquamarine			{ 127, 255, 212 };
		inline constexpr Color Palegreen			{ 152, 251, 152 };
		inline constexpr Color Lightgreen			{ 144, 238, 144 };
		inline constexpr Color Springgreen			{   0, 255, 127 };
		inline constexpr Color Mediumspringgreen	{   0, 250, 154 };
		inline constexpr Color Lawngreen			{ 124, 252,   0 };
		inline constexpr Color Chartreuse			{ 127, 255,   0 };
		inline constexpr Color Greenyellow			{ 173, 255,  47 };
		inline constexpr Color Lime				{   0, 255,   0 };
		inline constexpr Color Limegreen			{  50, 205,  50 };
		inline constexpr Color Yellowgreen			{ 154, 205,  50 };
		inline constexpr Color Darkolivegreen		{  85, 107,  47 };
		inline constexpr Color Olivedrab			{ 107, 142,  35 };
		inline constexpr Color Olive				{ 128, 128,   0 };
		inline constexpr Color Darkkhaki			{ 189, 183, 107 };
		inline constexpr Color Palegoldenrod		{ 238, 232, 170 };
		inline constexpr Color Cornsilk				{ 255, 248, 220 };
		inline constexpr Color Beige				{ 245, 245, 220 };
		inline constexpr Color Lightyellow			{ 255, 255, 224 };
		inline constexpr Color Lightgoldenrodyellow	{ 250, 250, 210 };
		inline constexpr Color Lemonchiffon			{ 255, 250, 205 };
		inline constexpr Color Wheat				{ 245, 222, 179 };
		inline constexpr Color Burlywood			{ 222, 184, 135 };
		inline constexpr Color Tan					{ 210, 180, 140 };
		inline constexpr Color Khaki				{ 240, 230, 140 };
		inline constexpr Color Yellow				{ 255, 255,   0 };
		inline constexpr Color Gold					{ 255, 215,   0 };
		inline constexpr Color Orange				{ 255, 165,   0 };
		inline constexpr Color Sandybrown			{ 244, 164,  96 };
		inline constexpr Color Darkorange			{ 255, 140,   0 };
		inline constexpr Color Goldenrod			{ 218, 165,  32 };
		inline constexpr Color Peru					{ 205, 133,  63 };
		inline constexpr Color Darkgoldenrod		{ 184, 134,  11 };
		inline constexpr Color Chocolate			{ 210, 105,  30 };
		inline constexpr Color Sienna				{ 160,  82,  45 };
		inline constexpr Color Saddlebrown			{ 139,  69,  19 };
		inline constexpr Color Maroon				{ 128,   0,   0 };
		inline constexpr Color Darkred				{ 139,   0,   0 };
		inline constexpr Color Brown				{ 165,  42,  42 };
		inline constexpr Color Firebrick			{ 178,  34,  34 };
		inline constexpr Color Indianred			{ 205,  92,  92 };
		inline constexpr Color Rosybrown			{ 188, 143, 143 };
		inline constexpr Color Darksalmon			{ 233, 150, 122 };
		inline constexpr Color Lightcoral			{ 240, 128, 128 };
		inline constexpr Color Salmon				{ 250, 128, 114 };
		inline constexpr Color Lightsalmon			{ 255, 160, 122 };
		inline constexpr Color Coral				{ 255, 127,  80 };
		inline constexpr Color Tomato				{ 255,  99,  71 };
		inline constexpr Color Orangered			{ 255,  69,   0 };
		inline constexpr Color Red					{ 255,   0,   0 };
		inline constexpr Color Crimson				{ 220,  20,  60 };
		inline constexpr Color Mediumvioletred		{ 199,  21, 133 };
		inline constexpr Color Deeppink				{ 255,  20, 147 };
		inline constexpr Color Hotpink				{ 255, 105, 180 };
		inline constexpr Color Palevioletred		{ 219, 112, 147 };
		inline constexpr Color Pink					{ 255, 192, 203 };
		inline constexpr Color Lightpink			{ 255, 182, 193 };
		inline constexpr Color Thistle				{ 216, 191, 216 };
		inline constexpr Color Magenta				{ 255,   0, 255 };
		inline constexpr Color Fuchsia				{ 255,   0, 255 };
		inline constexpr Color Violet				{ 238, 130, 238 };
		inline constexpr Color Plum					{ 221, 160, 221 };
		inline constexpr Color Orchid				{ 218, 112, 214 };
		inline constexpr Color Mediumorchid			{ 186,  85, 211 };
		inline constexpr Color Darkorchid			{ 153,  50, 204 };
		inline constexpr Color Darkviolet			{ 148,   0, 211 };
		inline constexpr Color Darkmagenta			{ 139,   0, 139 };
		inline constexpr Color Purple				{ 128,   0, 128 };
		inline constexpr Color Indigo				{  75,   0, 130 };
		inline constexpr Color Darkslateblue		{  72,  61, 139 };
		inline constexpr Color Blueviolet			{ 138,  43, 226 };
		inline constexpr Color Mediumpurple			{ 147, 112, 219 };
		inline constexpr Color Slateblue			{ 106,  90, 205 };
		inline constexpr Color Mediumslateblue		{ 123, 104, 238 };
	};

	namespace Palette
	{
		inline constexpr Color DefaultLetterbox		{   1,   2,   3 };
		inline constexpr Color DefaultBackground	{  11,  22,  33 };
	}
}
