//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Color.hpp"

namespace s3d
{
	/// <summary>
	/// カラーパレット
	/// </summary>
	namespace Palette
	{
		constexpr Color Black{ 0,0,0 };
		constexpr Color Dimgray{ 105,105,105 };
		constexpr Color Gray{ 128,128,128 };
		constexpr Color Darkgray{ 169,169,169 };
		constexpr Color Silver{ 192,192,192 };
		constexpr Color Lightgrey{ 211,211,211 };
		constexpr Color Gainsboro{ 220,220,220 };
		constexpr Color Whitesmoke{ 245,245,245 };
		constexpr Color White{ 255,255,255 };
		constexpr Color Snow{ 255,250,250 };
		constexpr Color Ghostwhite{ 248,248,255 };
		constexpr Color Floralwhite{ 255,250,240 };
		constexpr Color Linen{ 250,240,230 };
		constexpr Color Antiquewhite{ 250,235,215 };
		constexpr Color Papayawhip{ 255,239,213 };
		constexpr Color Blanchedalmond{ 255,235,205 };
		constexpr Color Bisque{ 255,228,196 };
		constexpr Color Moccasin{ 255,228,181 };
		constexpr Color Navajowhite{ 255,222,173 };
		constexpr Color Peachpuff{ 255,218,185 };
		constexpr Color Mistyrose{ 255,228,225 };
		constexpr Color Lavenderblush{ 255,240,245 };
		constexpr Color Seashell{ 255,245,238 };
		constexpr Color Oldlace{ 253,245,230 };
		constexpr Color Ivory{ 255,255,240 };
		constexpr Color Honeydew{ 240,255,240 };
		constexpr Color Mintcream{ 245,255,250 };
		constexpr Color Azure{ 240,255,255 };
		constexpr Color Aliceblue{ 240,248,255 };
		constexpr Color Lavender{ 230,230,250 };
		constexpr Color Lightsteelblue{ 176,196,222 };
		constexpr Color Lightslategray{ 119,136,153 };
		constexpr Color Slategray{ 112,128,144 };
		constexpr Color Steelblue{ 70,130,180 };
		constexpr Color Royalblue{ 65,105,225 };
		constexpr Color Midnightblue{ 25,25,112 };
		constexpr Color Navy{ 0,0,128 };
		constexpr Color Darkblue{ 0,0,139 };
		constexpr Color Mediumblue{ 0,0,205 };
		constexpr Color Blue{ 0,0,255 };
		constexpr Color Dodgerblue{ 30,144,255 };
		constexpr Color Cornflowerblue{ 100,149,237 };
		constexpr Color Deepskyblue{ 0,191,255 };
		constexpr Color Lightskyblue{ 135,206,250 };
		constexpr Color Skyblue{ 135,206,235 };
		constexpr Color Lightblue{ 173,216,230 };
		constexpr Color Powderblue{ 176,224,230 };
		constexpr Color Paleturquoise{ 175,238,238 };
		constexpr Color Lightcyan{ 224,255,255 };
		constexpr Color Cyan{ 0,255,255 };
		constexpr Color Aqua{ 0,255,255 };
		constexpr Color Turquoise{ 64,224,208 };
		constexpr Color Mediumturquoise{ 72,209,204 };
		constexpr Color Darkturquoise{ 0,206,209 };
		constexpr Color Lightseagreen{ 32,178,170 };
		constexpr Color Cadetblue{ 95,158,160 };
		constexpr Color Darkcyan{ 0,139,139 };
		constexpr Color Teal{ 0,128,128 };
		constexpr Color Darkslategray{ 47,79,79 };
		constexpr Color Darkgreen{ 0,100,0 };
		constexpr Color Green{ 0,128,0 };
		constexpr Color Forestgreen{ 34,139,34 };
		constexpr Color Seagreen{ 46,139,87 };
		constexpr Color Mediumseagreen{ 60,179,113 };
		constexpr Color Mediumaquamarine{ 102,205,170 };
		constexpr Color Darkseagreen{ 143,188,143 };
		constexpr Color Aquamarine{ 127,255,212 };
		constexpr Color Palegreen{ 152,251,152 };
		constexpr Color Lightgreen{ 144,238,144 };
		constexpr Color Springgreen{ 0,255,127 };
		constexpr Color Mediumspringgreen{ 0,250,154 };
		constexpr Color Lawngreen{ 124,252,0 };
		constexpr Color Chartreuse{ 127,255,0 };
		constexpr Color Greenyellow{ 173,255,47 };
		constexpr Color Lime{ 0,255,0 };
		constexpr Color Limegreen{ 50,205,50 };
		constexpr Color Yellowgreen{ 154,205,50 };
		constexpr Color Darkolivegreen{ 85,107,47 };
		constexpr Color Olivedrab{ 107,142,35 };
		constexpr Color Olive{ 128,128,0 };
		constexpr Color Darkkhaki{ 189,183,107 };
		constexpr Color Palegoldenrod{ 238,232,170 };
		constexpr Color Cornsilk{ 255,248,220 };
		constexpr Color Beige{ 245,245,220 };
		constexpr Color Lightyellow{ 255,255,224 };
		constexpr Color Lightgoldenrodyellow{ 250,250,210 };
		constexpr Color Lemonchiffon{ 255,250,205 };
		constexpr Color Wheat{ 245,222,179 };
		constexpr Color Burlywood{ 222,184,135 };
		constexpr Color Tan{ 210,180,140 };
		constexpr Color Khaki{ 240,230,140 };
		constexpr Color Yellow{ 255,255,0 };
		constexpr Color Gold{ 255,215,0 };
		constexpr Color Orange{ 255,165,0 };
		constexpr Color Sandybrown{ 244,164,96 };
		constexpr Color Darkorange{ 255,140,0 };
		constexpr Color Goldenrod{ 218,165,32 };
		constexpr Color Peru{ 205,133,63 };
		constexpr Color Darkgoldenrod{ 184,134,11 };
		constexpr Color Chocolate{ 210,105,30 };
		constexpr Color Sienna{ 160,82,45 };
		constexpr Color Saddlebrown{ 139,69,19 };
		constexpr Color Maroon{ 128,0,0 };
		constexpr Color Darkred{ 139,0,0 };
		constexpr Color Brown{ 165,42,42 };
		constexpr Color Firebrick{ 178,34,34 };
		constexpr Color Indianred{ 205,92,92 };
		constexpr Color Rosybrown{ 188,143,143 };
		constexpr Color Darksalmon{ 233,150,122 };
		constexpr Color Lightcoral{ 240,128,128 };
		constexpr Color Salmon{ 250,128,114 };
		constexpr Color Lightsalmon{ 255,160,122 };
		constexpr Color Coral{ 255,127,80 };
		constexpr Color Tomato{ 255,99,71 };
		constexpr Color Orangered{ 255,69,0 };
		constexpr Color Red{ 255,0,0 };
		constexpr Color Crimson{ 220,20,60 };
		constexpr Color Mediumvioletred{ 199,21,133 };
		constexpr Color Deeppink{ 255,20,147 };
		constexpr Color Hotpink{ 255,105,180 };
		constexpr Color Palevioletred{ 219,112,147 };
		constexpr Color Pink{ 255,192,203 };
		constexpr Color Lightpink{ 255,182,193 };
		constexpr Color Thistle{ 216,191,216 };
		constexpr Color Magenta{ 255,0,255 };
		constexpr Color Fuchsia{ 255,0,255 };
		constexpr Color Violet{ 238,130,238 };
		constexpr Color Plum{ 221,160,221 };
		constexpr Color Orchid{ 218,112,214 };
		constexpr Color Mediumorchid{ 186,85,211 };
		constexpr Color Darkorchid{ 153,50,204 };
		constexpr Color Darkviolet{ 148,0,211 };
		constexpr Color Darkmagenta{ 139,0,139 };
		constexpr Color Purple{ 128,0,128 };
		constexpr Color Indigo{ 75,0,130 };
		constexpr Color Darkslateblue{ 72,61,139 };
		constexpr Color Blueviolet{ 138,43,226 };
		constexpr Color Mediumpurple{ 147,112,219 };
		constexpr Color Slateblue{ 106,90,205 };
		constexpr Color Mediumslateblue{ 123,104,238 };
	};
}
