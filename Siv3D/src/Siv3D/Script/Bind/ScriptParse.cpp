//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Script.hpp>
# include <Siv3D/Parse.hpp>
# include <Siv3D/ColorHSV.hpp>
# include <Siv3D/2DShapes.hpp>
# include <Siv3D/Bezier2.hpp>
# include <Siv3D/Bezier3.hpp>
# include <Siv3D/Circular.hpp>
# include <Siv3D/OffsetCircular.hpp>
# include <Siv3D/Mat3x2.hpp>

namespace s3d
{
	using namespace AngelScript;

	template <class Type>
	Type ParseT(const String& s)
	{
		try
		{
			return s3d::Parse<Type>(s);
		}
		catch (const ParseError& e)
		{
			if (asIScriptContext* context = asGetActiveContext())
			{
				context->SetException(e.what().narrow().c_str());
			}

			return{};
		}
	}

	template <class Type>
	Type ParseOrT(const String& s, const Type& defaultValue)
	{
		return s3d::ParseOr<Type>(s, defaultValue);
	}

	void RegisterParse(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		r = engine->RegisterGlobalFunction("bool ParseBool(const String&in)", asFUNCTION(ParseT<bool>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int8 ParseInt8(const String&in)", asFUNCTION(ParseT<int8>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int16 ParseInt16(const String&in)", asFUNCTION(ParseT<int16>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int32 ParseInt32(const String&in)", asFUNCTION(ParseT<int32>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int64 ParseInt64(const String&in)", asFUNCTION(ParseT<int64>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint8 ParseUint8(const String&in)", asFUNCTION(ParseT<uint8>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint16 ParseUint16(const String&in)", asFUNCTION(ParseT<uint16>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint32 ParseUint32(const String&in)", asFUNCTION(ParseT<uint32>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint64 ParseUint64(const String&in)", asFUNCTION(ParseT<uint64>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("float ParseFloat(const String&in)", asFUNCTION(ParseT<float>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double ParseDouble(const String&in)", asFUNCTION(ParseT<double>), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("Color ParseColor(const String&in)", asFUNCTION(ParseT<Color>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("ColorF ParseColorF(const String&in)", asFUNCTION(ParseT<ColorF>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("HSV ParseHSV(const String&in)", asFUNCTION(ParseT<HSV>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Point ParsePoint(const String&in)", asFUNCTION(ParseT<Point>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Float2 ParseFloat2(const String&in)", asFUNCTION(ParseT<Float2>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Float3 ParseFloat3(const String&in)", asFUNCTION(ParseT<Float3>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Float4 ParseFloat4(const String&in)", asFUNCTION(ParseT<Float4>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec2 ParseVec2(const String&in)", asFUNCTION(ParseT<Vec2>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec3 ParseVec3(const String&in)", asFUNCTION(ParseT<Vec3>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec4 ParseVec4(const String&in)", asFUNCTION(ParseT<Vec4>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Circular ParseCircular(const String&in)", asFUNCTION(ParseT<Circular>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("OffsetCircular ParseOffsetCircular(const String&in)", asFUNCTION(ParseT<OffsetCircular>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Mat3x2 ParseMat3x2(const String&in)", asFUNCTION(ParseT<Mat3x2>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Bezier2 ParseBezier2(const String&in)", asFUNCTION(ParseT<Bezier2>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Bezier3 ParseBezier3(const String&in)", asFUNCTION(ParseT<Bezier3>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Line ParseLine(const String&in)", asFUNCTION(ParseT<Line>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Rect ParseRect(const String&in)", asFUNCTION(ParseT<Rect>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("RectF ParseRectF(const String&in)", asFUNCTION(ParseT<RectF>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Circle ParseCircle(const String&in)", asFUNCTION(ParseT<Circle>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Ellipse ParseEllipse(const String&in)", asFUNCTION(ParseT<Ellipse>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Triangle ParseTriangle(const String&in)", asFUNCTION(ParseT<Triangle>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Quad ParseQuad(const String&in)", asFUNCTION(ParseT<Quad>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("RoundRect ParseRoundRect(const String&in)", asFUNCTION(ParseT<RoundRect>), asCALL_CDECL); assert(r >= 0);


		r = engine->RegisterGlobalFunction("bool ParseOrBool(const String&in, const bool& in)", asFUNCTION(ParseOrT<bool>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int8 ParseOrInt8(const String&in, const int8& in)", asFUNCTION(ParseOrT<int8>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int16 ParseOrInt16(const String&in, const int16& in)", asFUNCTION(ParseOrT<int16>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int32 ParseOrInt32(const String&in, const int32& in)", asFUNCTION(ParseOrT<int32>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int64 ParseOrInt64(const String&in, const int64& in)", asFUNCTION(ParseOrT<int64>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint8 ParseOrUint8(const String&in, const uint8& in)", asFUNCTION(ParseOrT<uint8>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint16 ParseOrUint16(const String&in, const uint16& in)", asFUNCTION(ParseOrT<uint16>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint32 ParseOrUint32(const String&in, const uint32& in)", asFUNCTION(ParseOrT<uint32>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint64 ParseOrUint64(const String&in, const uint64& in)", asFUNCTION(ParseOrT<uint64>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("float ParseOrFloat(const String&in, const float& in)", asFUNCTION(ParseOrT<float>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double ParseOrDouble(const String&in, const double& in)", asFUNCTION(ParseOrT<double>), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("Color ParseOrColor(const String&in, const Color& in)", asFUNCTION(ParseOrT<Color>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("ColorF ParseOrColorF(const String&in, const ColorF& in)", asFUNCTION(ParseOrT<ColorF>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("HSV ParseOrHSV(const String&in, const HSV& in)", asFUNCTION(ParseOrT<HSV>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Point ParseOrPoint(const String&in, const Point& in)", asFUNCTION(ParseOrT<Point>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Float2 ParseOrFloat2(const String&in, const Float2& in)", asFUNCTION(ParseOrT<Float2>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Float3 ParseOrFloat3(const String&in, const Float3& in)", asFUNCTION(ParseOrT<Float3>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Float4 ParseOrFloat4(const String&in, const Float4& in)", asFUNCTION(ParseOrT<Float4>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec2 ParseOrVec2(const String&in, const Vec2& in)", asFUNCTION(ParseOrT<Vec2>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec3 ParseOrVec3(const String&in, const Vec3& in)", asFUNCTION(ParseOrT<Vec3>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec4 ParseOrVec4(const String&in, const Vec4& in)", asFUNCTION(ParseOrT<Vec4>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Circular ParseOrCircular(const String&in, const Circular& in)", asFUNCTION(ParseOrT<Circular>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("OffsetCircular ParseOrOffsetCircular(const String&in, const OffsetCircular& in)", asFUNCTION(ParseOrT<OffsetCircular>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Mat3x2 ParseOrMat3x2(const String&in, const Mat3x2& in)", asFUNCTION(ParseOrT<Mat3x2>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Bezier2 ParseOrBezier2(const String&in, const Bezier2& in)", asFUNCTION(ParseOrT<Bezier2>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Bezier3 ParseOrBezier3(const String&in, const Bezier3& in)", asFUNCTION(ParseOrT<Bezier3>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Line ParseOrLine(const String&in, const Line& in)", asFUNCTION(ParseOrT<Line>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Rect ParseOrRect(const String&in, const Rect& in)", asFUNCTION(ParseOrT<Rect>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("RectF ParseOrRectF(const String&in, const RectF& in)", asFUNCTION(ParseOrT<RectF>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Circle ParseOrCircle(const String&in, const Circle& in)", asFUNCTION(ParseOrT<Circle>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Ellipse ParseOrEllipse(const String&in, const Ellipse& in)", asFUNCTION(ParseOrT<Ellipse>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Triangle ParseOrTriangle(const String&in, const Triangle& in)", asFUNCTION(ParseOrT<Triangle>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Quad ParseOrQuad(const String&in, const Quad& in)", asFUNCTION(ParseOrT<Quad>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("RoundRect ParseOrRoundRect(const String&in, const RoundRect& in)", asFUNCTION(ParseOrT<RoundRect>), asCALL_CDECL); assert(r >= 0);
	}
}
