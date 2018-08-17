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

# pragma once

namespace AngelScript
{
	class asIScriptEngine;
}

namespace s3d
{
	enum class ScriptTypeID
	{
		Void = 0,
		Bool = 1,
		Int8 = 2,
		Int16 = 3,
		Int32 = 4,
		Int64 = 5,
		Uint8 = 6,
		Uint16 = 7,
		Uint32 = 8,
		Uint64 = 9,
		Float = 10,
		Double = 11,

		//Optional = ,
		String = 67108877,
		//Date,
		//DateTime,
		Color,
		ColorF,
		HSV,
		Point,
		Vec2,
		Vec3,
		Vec4,
		Circular,
		Line,
		Rect,
		RectF,
		Circle,
		Ellipse,
		Triangle,
		Quad,
		RoundRect,
		Polygon,
		LineString,


		//
		Image,


		Key,
		Texture,
		DynamicTexture,
		Font,
		DrawableString,
	};

	void RegisterTypes(AngelScript::asIScriptEngine *engine);
	void RegisterFormat(AngelScript::asIScriptEngine *engine);

	//void RegisterDate(AngelScript::asIScriptEngine *engine);
	//void RegisterDateTime(AngelScript::asIScriptEngine *engine);
	void RegisterColor(AngelScript::asIScriptEngine *engine);
	void RegisterColorF(AngelScript::asIScriptEngine *engine);
	void RegisterHSV(AngelScript::asIScriptEngine *engine);
	void RegisterPoint(AngelScript::asIScriptEngine *engine);
	void RegisterVec2(AngelScript::asIScriptEngine *engine);
	//void RegisterVec3(AngelScript::asIScriptEngine *engine);
	//void RegisterVec4(AngelScript::asIScriptEngine *engine);
	void RegisterCircular(AngelScript::asIScriptEngine *engine);
	void RegisterLine(AngelScript::asIScriptEngine *engine);
	void RegisterRect(AngelScript::asIScriptEngine *engine);
	void RegisterRectF(AngelScript::asIScriptEngine *engine);
	void RegisterCircle(AngelScript::asIScriptEngine *engine);
	void RegisterEllipse(AngelScript::asIScriptEngine *engine);
	void RegisterTriangle(AngelScript::asIScriptEngine *engine);
	void RegisterQuad(AngelScript::asIScriptEngine *engine);
	void RegisterRoundRect(AngelScript::asIScriptEngine *engine);
	//void RegisterRoundPolygon(AngelScript::asIScriptEngine *engine);
	//void RegisterRoundLineString(AngelScript::asIScriptEngine *engine);

	//void RegisterTime(asIScriptEngine *engine);

	//void RegisterMath(asIScriptEngine *engine);

	//void RegisterMathConstants(asIScriptEngine *engine);

	//void RegisterRandom(asIScriptEngine *engine);

	//void RegisterSystem(asIScriptEngine *engine);

	//void RegisterWindow(asIScriptEngine *engine);

	void RegisterCursor(AngelScript::asIScriptEngine *engine);
	void RegisterGraphics(AngelScript::asIScriptEngine *engine);

	void RegisterRandom(AngelScript::asIScriptEngine *engine);

	//void RegisterTexture(asIScriptEngine *engine);

	//void Register_DynamicTexture(asIScriptEngine *engine);


	//void RegisterFont(asIScriptEngine *engine);
	//void RegisterDrawableString(asIScriptEngine *engine);

	//void Register_Webcam(asIScriptEngine *engine);
}
