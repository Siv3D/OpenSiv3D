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

# pragma once
# include "Color.hpp"
# include "ColorF.hpp"

namespace s3d
{
	inline namespace ColorSpace
	{
		inline namespace sRGB
		{
			/// @brief sRGB 色空間の色定数
			namespace Palette
			{
				// HTML Color Names
				// https://www.w3schools.com/colors/colors_names.asp

				inline constexpr Color Black				{   0,   0,   0 };
				inline constexpr Color Dimgray				{ 105, 105, 105 };
				inline constexpr Color Dimgrey				{ 105, 105, 105 };
				inline constexpr Color Gray					{ 128, 128, 128 };
				inline constexpr Color Grey					{ 128, 128, 128 };
				inline constexpr Color Darkgray				{ 169, 169, 169 };
				inline constexpr Color Darkgrey				{ 169, 169, 169 };
				inline constexpr Color Silver				{ 192, 192, 192 };
				inline constexpr Color Lightgray			{ 211, 211, 211 };
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
				inline constexpr Color Lightslategrey		{ 119, 136, 153 };
				inline constexpr Color Slategray			{ 112, 128, 144 };
				inline constexpr Color Slategrey			{ 112, 128, 144 };
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
				inline constexpr Color Darkslategrey		{  47,  79,  79 };
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
				inline constexpr Color Lime					{   0, 255,   0 };
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

				inline constexpr Color DefaultLetterbox		{   1,   2,   3 };
				inline constexpr Color DefaultBackground	{  11,  22,  33 };
			}
		}

		namespace Linear
		{
			/// @brief リニア色空間の色定数
			namespace Palette
			{
				inline constexpr ColorF Black				{ 0.00000, 0.00000, 0.00000 };
				inline constexpr ColorF Dimgray				{ 0.14126, 0.14126, 0.14126 };
				inline constexpr ColorF Dimgrey				{ 0.14126, 0.14126, 0.14126 };
				inline constexpr ColorF Gray				{ 0.21586, 0.21586, 0.21586 };
				inline constexpr ColorF Grey				{ 0.21586, 0.21586, 0.21586 };
				inline constexpr ColorF Darkgray			{ 0.39676, 0.39676, 0.39676 };
				inline constexpr ColorF Darkgrey			{ 0.39676, 0.39676, 0.39676 };
				inline constexpr ColorF Silver				{ 0.52712, 0.52712, 0.52712 };
				inline constexpr ColorF Lightgray			{ 0.65141, 0.65141, 0.65141 };
				inline constexpr ColorF Lightgrey			{ 0.65141, 0.65141, 0.65141 };
				inline constexpr ColorF Gainsboro			{ 0.71569, 0.71569, 0.71569 };
				inline constexpr ColorF Whitesmoke			{ 0.91310, 0.91310, 0.91310 };
				inline constexpr ColorF White				{ 1.00000, 1.00000, 1.00000 };

				inline constexpr ColorF Snow				{ 1.00000, 0.95597, 0.95597 };
				inline constexpr ColorF Ghostwhite			{ 0.93869, 0.93869, 1.00000 };
				inline constexpr ColorF Floralwhite			{ 1.00000, 0.95597, 0.87137 };
				inline constexpr ColorF Linen				{ 0.95597, 0.87137, 0.79130 };
				inline constexpr ColorF Antiquewhite		{ 0.95597, 0.83077, 0.67954 };
				inline constexpr ColorF Papayawhip			{ 1.00000, 0.86316, 0.66539 };
				inline constexpr ColorF Blanchedalmond		{ 1.00000, 0.83077, 0.61050 };
				inline constexpr ColorF Bisque				{ 1.00000, 0.77582, 0.55201 };
				inline constexpr ColorF Moccasin			{ 1.00000, 0.77582, 0.46208 };
				inline constexpr ColorF Navajowhite			{ 1.00000, 0.73046, 0.41789 };
				inline constexpr ColorF Peachpuff			{ 1.00000, 0.70110, 0.48515 };
				inline constexpr ColorF Mistyrose			{ 1.00000, 0.77582, 0.75294 };
				inline constexpr ColorF Lavenderblush		{ 1.00000, 0.87137, 0.91310 };
				inline constexpr ColorF Seashell			{ 1.00000, 0.91310, 0.85499 };
				inline constexpr ColorF Oldlace				{ 0.98225, 0.91310, 0.79130 };
				inline constexpr ColorF Ivory				{ 1.00000, 1.00000, 0.87137 };
				inline constexpr ColorF Honeydew			{ 0.87137, 1.00000, 0.87137 };
				inline constexpr ColorF Mintcream			{ 0.91310, 1.00000, 0.95597 };
				inline constexpr ColorF Azure				{ 0.87137, 1.00000, 1.00000 };
				inline constexpr ColorF Aliceblue			{ 0.87137, 0.93869, 1.00000 };
				inline constexpr ColorF Lavender			{ 0.79130, 0.79130, 0.95597 };
				inline constexpr ColorF Lightsteelblue		{ 0.43415, 0.55201, 0.73046 };
				inline constexpr ColorF Lightslategray		{ 0.18447, 0.24620, 0.31855 };
				inline constexpr ColorF Lightslategrey		{ 0.18447, 0.24620, 0.31855 };
				inline constexpr ColorF Slategray			{ 0.16203, 0.21586, 0.27889 };
				inline constexpr ColorF Slategrey			{ 0.16203, 0.21586, 0.27889 };
				inline constexpr ColorF Steelblue			{ 0.06125, 0.22323, 0.45641 };
				inline constexpr ColorF Royalblue			{ 0.05286, 0.14126, 0.75294 };
				inline constexpr ColorF Midnightblue		{ 0.00972, 0.00972, 0.16203 };
				inline constexpr ColorF Navy				{ 0.00000, 0.00000, 0.21586 };
				inline constexpr ColorF Darkblue			{ 0.00000, 0.00000, 0.25818 };
				inline constexpr ColorF Mediumblue			{ 0.00000, 0.00000, 0.61050 };
				inline constexpr ColorF Blue				{ 0.00000, 0.00000, 1.00000 };
				inline constexpr ColorF Dodgerblue			{ 0.01298, 0.27889, 1.00000 };
				inline constexpr ColorF Cornflowerblue		{ 0.12744, 0.30054, 0.84687 };
				inline constexpr ColorF Deepskyblue			{ 0.00000, 0.52100, 1.00000 };
				inline constexpr ColorF Lightskyblue		{ 0.24228, 0.61721, 0.95597 };
				inline constexpr ColorF Skyblue				{ 0.24228, 0.61721, 0.83077 };
				inline constexpr ColorF Lightblue			{ 0.41789, 0.68669, 0.79130 };
				inline constexpr ColorF Powderblue			{ 0.43415, 0.74540, 0.79130 };
				inline constexpr ColorF Paleturquoise		{ 0.42869, 0.85499, 0.85499 };
				inline constexpr ColorF Lightcyan			{ 0.74540, 1.00000, 1.00000 };
				inline constexpr ColorF Cyan				{ 0.00000, 1.00000, 1.00000 };
				inline constexpr ColorF Aqua				{ 0.00000, 1.00000, 1.00000 };
				inline constexpr ColorF Turquoise			{ 0.05127, 0.74540, 0.63076 };
				inline constexpr ColorF Mediumturquoise		{ 0.06480, 0.63760, 0.60383 };
				inline constexpr ColorF Darkturquoise		{ 0.00000, 0.61721, 0.63760 };
				inline constexpr ColorF Lightseagreen		{ 0.01444, 0.44520, 0.40198 };
				inline constexpr ColorF Cadetblue			{ 0.11444, 0.34191, 0.35153 };
				inline constexpr ColorF Darkcyan			{ 0.00000, 0.25818, 0.25818 };
				inline constexpr ColorF Teal				{ 0.00000, 0.21586, 0.21586 };
				inline constexpr ColorF Darkslategray		{ 0.02843, 0.07819, 0.07819 };
				inline constexpr ColorF Darkslategrey		{ 0.02843, 0.07819, 0.07819 };
				inline constexpr ColorF Darkgreen			{ 0.00000, 0.12744, 0.00000 };
				inline constexpr ColorF Green				{ 0.00000, 0.21586, 0.00000 };
				inline constexpr ColorF Forestgreen			{ 0.01600, 0.25818, 0.01600 };
				inline constexpr ColorF Seagreen			{ 0.02732, 0.25818, 0.09531 };
				inline constexpr ColorF Mediumseagreen		{ 0.04519, 0.45079, 0.16513 };
				inline constexpr ColorF Mediumaquamarine	{ 0.13287, 0.61050, 0.40198 };
				inline constexpr ColorF Darkseagreen		{ 0.27468, 0.50289, 0.27468 };
				inline constexpr ColorF Aquamarine			{ 0.21223, 1.00000, 0.65837 };
				inline constexpr ColorF Palegreen			{ 0.31399, 0.96469, 0.31399 };
				inline constexpr ColorF Lightgreen			{ 0.27889, 0.85499, 0.27889 };
				inline constexpr ColorF Springgreen			{ 0.00000, 1.00000, 0.21223 };
				inline constexpr ColorF Mediumspringgreen	{ 0.00000, 0.95597, 0.32314 };
				inline constexpr ColorF Lawngreen			{ 0.20156, 0.97345, 0.00000 };
				inline constexpr ColorF Chartreuse			{ 0.21223, 1.00000, 0.00000 };
				inline constexpr ColorF Greenyellow			{ 0.41789, 1.00000, 0.02843 };
				inline constexpr ColorF Lime				{ 0.00000, 1.00000, 0.00000 };
				inline constexpr ColorF Limegreen			{ 0.03190, 0.61050, 0.03190 };
				inline constexpr ColorF Yellowgreen			{ 0.32314, 0.61050, 0.03190 };
				inline constexpr ColorF Darkolivegreen		{ 0.09084, 0.14703, 0.02843 };
				inline constexpr ColorF Olivedrab			{ 0.14703, 0.27050, 0.01681 };
				inline constexpr ColorF Olive				{ 0.21586, 0.21586, 0.00000 };
				inline constexpr ColorF Darkkhaki			{ 0.50888, 0.47353, 0.14703 };
				inline constexpr ColorF Palegoldenrod		{ 0.85499, 0.80695, 0.40198 };
				inline constexpr ColorF Cornsilk			{ 1.00000, 0.93869, 0.71569 };
				inline constexpr ColorF Beige				{ 0.91310, 0.91310, 0.71569 };
				inline constexpr ColorF Lightyellow			{ 1.00000, 1.00000, 0.74540 };
				inline constexpr ColorF Lightgoldenrodyellow{ 0.95597, 0.95597, 0.64448 };
				inline constexpr ColorF Lemonchiffon		{ 1.00000, 0.95597, 0.61050 };
				inline constexpr ColorF Wheat				{ 0.91310, 0.73046, 0.45079 };
				inline constexpr ColorF Burlywood			{ 0.73046, 0.47932, 0.24228 };
				inline constexpr ColorF Tan					{ 0.64448, 0.45641, 0.26225 };
				inline constexpr ColorF Khaki				{ 0.87137, 0.79130, 0.26225 };
				inline constexpr ColorF Yellow				{ 1.00000, 1.00000, 0.00000 };
				inline constexpr ColorF Gold				{ 1.00000, 0.67954, 0.00000 };
				inline constexpr ColorF Orange				{ 1.00000, 0.37626, 0.00000 };
				inline constexpr ColorF Sandybrown			{ 0.90466, 0.37124, 0.11697 };
				inline constexpr ColorF Darkorange			{ 1.00000, 0.26225, 0.00000 };
				inline constexpr ColorF Goldenrod			{ 0.70110, 0.37626, 0.01444 };
				inline constexpr ColorF Peru				{ 0.61050, 0.23455, 0.04971 };
				inline constexpr ColorF Darkgoldenrod		{ 0.47932, 0.23840, 0.00335 };
				inline constexpr ColorF Chocolate			{ 0.64448, 0.14126, 0.01298 };
				inline constexpr ColorF Sienna				{ 0.35153, 0.08438, 0.02624 };
				inline constexpr ColorF Saddlebrown			{ 0.25818, 0.05951, 0.00651 };
				inline constexpr ColorF Maroon				{ 0.21586, 0.00000, 0.00000 };
				inline constexpr ColorF Darkred				{ 0.25818, 0.00000, 0.00000 };
				inline constexpr ColorF Brown				{ 0.37626, 0.02315, 0.02315 };
				inline constexpr ColorF Firebrick			{ 0.44520, 0.01600, 0.01600 };
				inline constexpr ColorF Indianred			{ 0.61050, 0.10702, 0.10702 };
				inline constexpr ColorF Rosybrown			{ 0.50289, 0.27468, 0.27468 };
				inline constexpr ColorF Darksalmon			{ 0.81485, 0.30499, 0.19462 };
				inline constexpr ColorF Lightcoral			{ 0.87137, 0.21586, 0.21586 };
				inline constexpr ColorF Salmon				{ 0.95597, 0.21586, 0.16827 };
				inline constexpr ColorF Lightsalmon			{ 1.00000, 0.35153, 0.19462 };
				inline constexpr ColorF Coral				{ 1.00000, 0.21223, 0.08022 };
				inline constexpr ColorF Tomato				{ 1.00000, 0.12477, 0.06301 };
				inline constexpr ColorF Orangered			{ 1.00000, 0.05951, 0.00000 };
				inline constexpr ColorF Red					{ 1.00000, 0.00000, 0.00000 };
				inline constexpr ColorF Crimson				{ 0.71569, 0.00700, 0.04519 };
				inline constexpr ColorF Mediumvioletred		{ 0.57112, 0.00750, 0.23455 };
				inline constexpr ColorF Deeppink			{ 1.00000, 0.00700, 0.29177 };
				inline constexpr ColorF Hotpink				{ 1.00000, 0.14126, 0.45641 };
				inline constexpr ColorF Palevioletred		{ 0.70838, 0.16203, 0.29177 };
				inline constexpr ColorF Pink				{ 1.00000, 0.52712, 0.59720 };
				inline constexpr ColorF Lightpink			{ 1.00000, 0.46778, 0.53328 };
				inline constexpr ColorF Thistle				{ 0.68669, 0.52100, 0.68669 };
				inline constexpr ColorF Magenta				{ 1.00000, 0.00000, 1.00000 };
				inline constexpr ColorF Fuchsia				{ 1.00000, 0.00000, 1.00000 };
				inline constexpr ColorF Violet				{ 0.85499, 0.22323, 0.85499 };
				inline constexpr ColorF Plum				{ 0.72306, 0.35153, 0.72306 };
				inline constexpr ColorF Orchid				{ 0.70110, 0.16203, 0.67244 };
				inline constexpr ColorF Mediumorchid		{ 0.49102, 0.09084, 0.65141 };
				inline constexpr ColorF Darkorchid			{ 0.31855, 0.03190, 0.60383 };
				inline constexpr ColorF Darkviolet			{ 0.29614, 0.00000, 0.65141 };
				inline constexpr ColorF Darkmagenta			{ 0.25818, 0.00000, 0.25818 };
				inline constexpr ColorF Purple				{ 0.21586, 0.00000, 0.21586 };
				inline constexpr ColorF Indigo				{ 0.07036, 0.00000, 0.22323 };
				inline constexpr ColorF Darkslateblue		{ 0.06480, 0.04667, 0.25818 };
				inline constexpr ColorF Blueviolet			{ 0.25415, 0.02416, 0.76052 };
				inline constexpr ColorF Mediumpurple		{ 0.29177, 0.16203, 0.70838 };
				inline constexpr ColorF Slateblue			{ 0.14413, 0.10224, 0.61050 };
				inline constexpr ColorF Mediumslateblue		{ 0.19807, 0.13843, 0.85499 };

				inline constexpr ColorF DefaultLetterbox	{ 0.00030, 0.00061, 0.00091 };
				inline constexpr ColorF DefaultBackground	{ 0.00335, 0.00802, 0.01521 };
			}
		}
	}
}
