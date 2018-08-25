//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Script.hpp>
# include <Siv3D/Color.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	void RegisterPalette(asIScriptEngine* engine)
	{
		int32 r = 0;

		r = engine->SetDefaultNamespace("Palette"); assert(r >= 0);
		{
			r = engine->RegisterGlobalProperty("const Color Black", (void*)&Palette::Black); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Dimgray", (void*)&Palette::Dimgray); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Gray", (void*)&Palette::Gray); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Darkgray", (void*)&Palette::Darkgray); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Silver", (void*)&Palette::Silver); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Lightgrey", (void*)&Palette::Lightgrey); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Gainsboro", (void*)&Palette::Gainsboro); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Whitesmoke", (void*)&Palette::Whitesmoke); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color White", (void*)&Palette::White); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Snow", (void*)&Palette::Snow); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Ghostwhite", (void*)&Palette::Ghostwhite); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Floralwhite", (void*)&Palette::Floralwhite); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Linen", (void*)&Palette::Linen); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Antiquewhite", (void*)&Palette::Antiquewhite); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Papayawhip", (void*)&Palette::Papayawhip); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Blanchedalmond", (void*)&Palette::Blanchedalmond); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Bisque", (void*)&Palette::Bisque); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Moccasin", (void*)&Palette::Moccasin); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Navajowhite", (void*)&Palette::Navajowhite); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Peachpuff", (void*)&Palette::Peachpuff); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Mistyrose", (void*)&Palette::Mistyrose); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Lavenderblush", (void*)&Palette::Lavenderblush); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Seashell", (void*)&Palette::Seashell); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Oldlace", (void*)&Palette::Oldlace); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Ivory", (void*)&Palette::Ivory); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Honeydew", (void*)&Palette::Honeydew); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Mintcream", (void*)&Palette::Mintcream); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Azure", (void*)&Palette::Azure); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Aliceblue", (void*)&Palette::Aliceblue); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Lavender", (void*)&Palette::Lavender); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Lightsteelblue", (void*)&Palette::Lightsteelblue); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Lightslategray", (void*)&Palette::Lightslategray); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Slategray", (void*)&Palette::Slategray); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Steelblue", (void*)&Palette::Steelblue); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Royalblue", (void*)&Palette::Royalblue); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Midnightblue", (void*)&Palette::Midnightblue); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Navy", (void*)&Palette::Navy); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Darkblue", (void*)&Palette::Darkblue); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Mediumblue", (void*)&Palette::Mediumblue); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Blue", (void*)&Palette::Blue); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Dodgerblue", (void*)&Palette::Dodgerblue); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Cornflowerblue", (void*)&Palette::Cornflowerblue); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Deepskyblue", (void*)&Palette::Deepskyblue); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Lightskyblue", (void*)&Palette::Lightskyblue); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Skyblue", (void*)&Palette::Skyblue); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Lightblue", (void*)&Palette::Lightblue); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Powderblue", (void*)&Palette::Powderblue); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Paleturquoise", (void*)&Palette::Paleturquoise); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Lightcyan", (void*)&Palette::Lightcyan); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Cyan", (void*)&Palette::Cyan); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Aqua", (void*)&Palette::Aqua); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Turquoise", (void*)&Palette::Turquoise); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Mediumturquoise", (void*)&Palette::Mediumturquoise); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Darkturquoise", (void*)&Palette::Darkturquoise); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Lightseagreen", (void*)&Palette::Lightseagreen); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Cadetblue", (void*)&Palette::Cadetblue); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Darkcyan", (void*)&Palette::Darkcyan); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Teal", (void*)&Palette::Teal); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Darkslategray", (void*)&Palette::Darkslategray); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Darkgreen", (void*)&Palette::Darkgreen); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Green", (void*)&Palette::Green); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Forestgreen", (void*)&Palette::Forestgreen); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Seagreen", (void*)&Palette::Seagreen); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Mediumseagreen", (void*)&Palette::Mediumseagreen); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Mediumaquamarine", (void*)&Palette::Mediumaquamarine); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Darkseagreen", (void*)&Palette::Darkseagreen); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Aquamarine", (void*)&Palette::Aquamarine); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Palegreen", (void*)&Palette::Palegreen); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Lightgreen", (void*)&Palette::Lightgreen); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Springgreen", (void*)&Palette::Springgreen); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Mediumspringgreen", (void*)&Palette::Mediumspringgreen); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Lawngreen", (void*)&Palette::Lawngreen); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Chartreuse", (void*)&Palette::Chartreuse); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Greenyellow", (void*)&Palette::Greenyellow); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Lime", (void*)&Palette::Lime); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Limegreen", (void*)&Palette::Limegreen); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Yellowgreen", (void*)&Palette::Yellowgreen); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Darkolivegreen", (void*)&Palette::Darkolivegreen); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Olivedrab", (void*)&Palette::Olivedrab); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Olive", (void*)&Palette::Olive); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Darkkhaki", (void*)&Palette::Darkkhaki); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Palegoldenrod", (void*)&Palette::Palegoldenrod); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Cornsilk", (void*)&Palette::Cornsilk); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Beige", (void*)&Palette::Beige); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Lightyellow", (void*)&Palette::Lightyellow); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Lightgoldenrodyellow", (void*)&Palette::Lightgoldenrodyellow); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Lemonchiffon", (void*)&Palette::Lemonchiffon); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Wheat", (void*)&Palette::Wheat); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Burlywood", (void*)&Palette::Burlywood); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Tan", (void*)&Palette::Tan); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Khaki", (void*)&Palette::Khaki); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Yellow", (void*)&Palette::Yellow); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Gold", (void*)&Palette::Gold); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Orange", (void*)&Palette::Orange); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Sandybrown", (void*)&Palette::Sandybrown); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Darkorange", (void*)&Palette::Darkorange); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Goldenrod", (void*)&Palette::Goldenrod); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Peru", (void*)&Palette::Peru); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Darkgoldenrod", (void*)&Palette::Darkgoldenrod); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Chocolate", (void*)&Palette::Chocolate); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Sienna", (void*)&Palette::Sienna); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Saddlebrown", (void*)&Palette::Saddlebrown); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Maroon", (void*)&Palette::Maroon); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Darkred", (void*)&Palette::Darkred); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Brown", (void*)&Palette::Brown); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Firebrick", (void*)&Palette::Firebrick); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Indianred", (void*)&Palette::Indianred); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Rosybrown", (void*)&Palette::Rosybrown); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Darksalmon", (void*)&Palette::Darksalmon); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Lightcoral", (void*)&Palette::Lightcoral); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Salmon", (void*)&Palette::Salmon); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Lightsalmon", (void*)&Palette::Lightsalmon); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Coral", (void*)&Palette::Coral); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Tomato", (void*)&Palette::Tomato); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Orangered", (void*)&Palette::Orangered); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Red", (void*)&Palette::Red); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Crimson", (void*)&Palette::Crimson); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Mediumvioletred", (void*)&Palette::Mediumvioletred); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Deeppink", (void*)&Palette::Deeppink); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Hotpink", (void*)&Palette::Hotpink); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Palevioletred", (void*)&Palette::Palevioletred); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Pink", (void*)&Palette::Pink); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Lightpink", (void*)&Palette::Lightpink); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Thistle", (void*)&Palette::Thistle); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Magenta", (void*)&Palette::Magenta); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Fuchsia", (void*)&Palette::Fuchsia); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Violet", (void*)&Palette::Violet); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Plum", (void*)&Palette::Plum); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Orchid", (void*)&Palette::Orchid); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Mediumorchid", (void*)&Palette::Mediumorchid); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Darkorchid", (void*)&Palette::Darkorchid); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Darkviolet", (void*)&Palette::Darkviolet); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Darkmagenta", (void*)&Palette::Darkmagenta); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Purple", (void*)&Palette::Purple); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Indigo", (void*)&Palette::Indigo); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Darkslateblue", (void*)&Palette::Darkslateblue); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Blueviolet", (void*)&Palette::Blueviolet); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Mediumpurple", (void*)&Palette::Mediumpurple); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Slateblue", (void*)&Palette::Slateblue); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const Color Mediumslateblue", (void*)&Palette::Mediumslateblue); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
