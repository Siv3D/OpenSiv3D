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
# include <Siv3D/Random.hpp>
# include <Siv3D/RandomDuration.hpp>
# include <Siv3D/RandomColor.hpp>
# include <Siv3D/RandomPoint.hpp>
# include <Siv3D/RandomVec2.hpp>
# include <Siv3D/RandomVec3.hpp>
# include <Siv3D/RandomVec4.hpp>

namespace s3d
{
	using namespace AngelScript;

	void RegisterRandom(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		r = engine->RegisterGlobalFunction("void Reseed(uint64)", asFUNCTIONPR(Reseed, (uint64), void), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double Random()", asFUNCTIONPR(Random, (), double), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("uint8 Random(uint8, uint8)", asFUNCTIONPR(Random, (uint8, uint8), uint8), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint16 Random(uint16, uint16)", asFUNCTIONPR(Random, (uint16, uint16), uint16), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint32 Random(uint32, uint32)", asFUNCTIONPR(Random, (uint32, uint32), uint32), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint64 Random(uint64, uint64)", asFUNCTIONPR(Random, (uint64, uint64), uint64), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int8 Random(int8, int8)", asFUNCTIONPR(Random, (int8, int8), int8), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int16 Random(int16, int16)", asFUNCTIONPR(Random, (int16, int16), int16), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int32 Random(int32, int32)", asFUNCTIONPR(Random, (int32, int32), int32), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int64 Random(int64, int64)", asFUNCTIONPR(Random, (int64, int64), int64), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("float Random(float, float)", asFUNCTIONPR(Random, (float, float), float), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double Random(double, double)", asFUNCTIONPR(Random, (double, double), double), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("uint8 Random(uint8)", asFUNCTIONPR(Random, (uint8), uint8), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint16 Random(uint16)", asFUNCTIONPR(Random, (uint16), uint16), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint32 Random(uint32)", asFUNCTIONPR(Random, (uint32), uint32), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint64 Random(uint64)", asFUNCTIONPR(Random, (uint64), uint64), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int8 Random(int8)", asFUNCTIONPR(Random, (int8), int8), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int16 Random(int16)", asFUNCTIONPR(Random, (int16), int16), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int32 Random(int32)", asFUNCTIONPR(Random, (int32), int32), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int64 Random(int64)", asFUNCTIONPR(Random, (int64), int64), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("float Random(float)", asFUNCTIONPR(Random, (float), float), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double Random(double)", asFUNCTIONPR(Random, (double), double), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("uint8 RandomOpen(uint8, uint8)", asFUNCTIONPR(RandomOpen, (uint8, uint8), uint8), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint16 RandomOpen(uint16, uint16)", asFUNCTIONPR(RandomOpen, (uint16, uint16), uint16), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint32 RandomOpen(uint32, uint32)", asFUNCTIONPR(RandomOpen, (uint32, uint32), uint32), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint64 RandomOpen(uint64, uint64)", asFUNCTIONPR(RandomOpen, (uint64, uint64), uint64), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int8 RandomOpen(int8, int8)", asFUNCTIONPR(RandomOpen, (int8, int8), int8), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int16 RandomOpen(int16, int16)", asFUNCTIONPR(RandomOpen, (int16, int16), int16), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int32 RandomOpen(int32, int32)", asFUNCTIONPR(RandomOpen, (int32, int32), int32), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int64 RandomOpen(int64, int64)", asFUNCTIONPR(RandomOpen, (int64, int64), int64), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("float RandomOpen(float, float)", asFUNCTIONPR(RandomOpen, (float, float), float), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double RandomOpen(double, double)", asFUNCTIONPR(RandomOpen, (double, double), double), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("uint8 RandomClosed(uint8, uint8)", asFUNCTIONPR(RandomClosed, (uint8, uint8), uint8), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint16 RandomClosed(uint16, uint16)", asFUNCTIONPR(RandomClosed, (uint16, uint16), uint16), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint32 RandomClosed(uint32, uint32)", asFUNCTIONPR(RandomClosed, (uint32, uint32), uint32), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint64 RandomClosed(uint64, uint64)", asFUNCTIONPR(RandomClosed, (uint64, uint64), uint64), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int8 RandomClosed(int8, int8)", asFUNCTIONPR(RandomClosed, (int8, int8), int8), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int16 RandomClosed(int16, int16)", asFUNCTIONPR(RandomClosed, (int16, int16), int16), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int32 RandomClosed(int32, int32)", asFUNCTIONPR(RandomClosed, (int32, int32), int32), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int64 RandomClosed(int64, int64)", asFUNCTIONPR(RandomClosed, (int64, int64), int64), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("float RandomClosed(float, float)", asFUNCTIONPR(RandomClosed, (float, float), float), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double RandomClosed(double, double)", asFUNCTIONPR(RandomClosed, (double, double), double), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("uint8 RandomOpenClosed(uint8, uint8)", asFUNCTIONPR(RandomOpenClosed, (uint8, uint8), uint8), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint16 RandomOpenClosed(uint16, uint16)", asFUNCTIONPR(RandomOpenClosed, (uint16, uint16), uint16), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint32 RandomOpenClosed(uint32, uint32)", asFUNCTIONPR(RandomOpenClosed, (uint32, uint32), uint32), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint64 RandomOpenClosed(uint64, uint64)", asFUNCTIONPR(RandomOpenClosed, (uint64, uint64), uint64), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int8 RandomOpenClosed(int8, int8)", asFUNCTIONPR(RandomOpenClosed, (int8, int8), int8), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int16 RandomOpenClosed(int16, int16)", asFUNCTIONPR(RandomOpenClosed, (int16, int16), int16), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int32 RandomOpenClosed(int32, int32)", asFUNCTIONPR(RandomOpenClosed, (int32, int32), int32), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int64 RandomOpenClosed(int64, int64)", asFUNCTIONPR(RandomOpenClosed, (int64, int64), int64), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("float RandomOpenClosed(float, float)", asFUNCTIONPR(RandomOpenClosed, (float, float), float), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double RandomOpenClosed(double, double)", asFUNCTIONPR(RandomOpenClosed, (double, double), double), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("uint8 RandomClosedOpen(uint8, uint8)", asFUNCTIONPR(RandomClosedOpen, (uint8, uint8), uint8), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint16 RandomClosedOpen(uint16, uint16)", asFUNCTIONPR(RandomClosedOpen, (uint16, uint16), uint16), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint32 RandomClosedOpen(uint32, uint32)", asFUNCTIONPR(RandomClosedOpen, (uint32, uint32), uint32), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint64 RandomClosedOpen(uint64, uint64)", asFUNCTIONPR(RandomClosedOpen, (uint64, uint64), uint64), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int8 RandomClosedOpen(int8, int8)", asFUNCTIONPR(RandomClosedOpen, (int8, int8), int8), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int16 RandomClosedOpen(int16, int16)", asFUNCTIONPR(RandomClosedOpen, (int16, int16), int16), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int32 RandomClosedOpen(int32, int32)", asFUNCTIONPR(RandomClosedOpen, (int32, int32), int32), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int64 RandomClosedOpen(int64, int64)", asFUNCTIONPR(RandomClosedOpen, (int64, int64), int64), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("float RandomClosedOpen(float, float)", asFUNCTIONPR(RandomClosedOpen, (float, float), float), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double RandomClosedOpen(double, double)", asFUNCTIONPR(RandomClosedOpen, (double, double), double), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("bool RandomBool(double p = 0.5)", asFUNCTIONPR(RandomBool, (double), bool), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("uint8 RandomUint8()", asFUNCTIONPR(RandomUint8, (), uint8), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint16 RandomUint16()", asFUNCTIONPR(RandomUint16, (), uint16), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint32 RandomUint32()", asFUNCTIONPR(RandomUint32, (), uint32), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint64 RandomUint64()", asFUNCTIONPR(RandomUint64, (), uint64), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int8 RandomInt8()", asFUNCTIONPR(RandomInt8, (), int8), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int16 RandomInt16()", asFUNCTIONPR(RandomInt16, (), int16), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int32 RandomInt32()", asFUNCTIONPR(RandomInt32, (), int32), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int64 RandomInt64()", asFUNCTIONPR(RandomInt64, (), int64), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("Duration Random(const Duration& in)", asFUNCTIONPR(Random, (const Duration&), Duration), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Duration Random(const Duration& in, const Duration& in)", asFUNCTIONPR(Random, (const Duration&, const Duration&), Duration), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("Color RandomColor()", asFUNCTIONPR(RandomColor, (), Color), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Color RandomColor(const Point& in rMinMax, const Point& in gMinMax, const Point& in bMinMax)", asFUNCTIONPR(RandomColor, (const std::pair<uint32, uint32>&, const std::pair<uint32, uint32>&, const std::pair<uint32, uint32>&), Color), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("ColorF RandomColorF()", asFUNCTIONPR(RandomColorF, (), ColorF), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("ColorF RandomColorF(const Vec2& in rMinMax, const Vec2& in gMinMax, const Vec2& in bMinMax)", asFUNCTIONPR(RandomColorF, (const std::pair<double, double>&, const std::pair<double, double>&, const std::pair<double, double>&), ColorF), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("HSV RandomHSV()", asFUNCTIONPR(RandomHSV, (), HSV), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("HSV RandomHSV(const Vec2& in hMinMax, const Vec2& in sMinMax, const Vec2& in vMinMax)", asFUNCTIONPR(RandomHSV, (const std::pair<double, double>&, const std::pair<double, double>&, const std::pair<double, double>&), HSV), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("Point RandomPoint(const Point& in xMinMax, const Point& in yMinMax)", asFUNCTIONPR(RandomPoint, (const std::pair<int32, int32>&, const std::pair<int32, int32>&), Point), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Point RandomPoint(const Rect& in)", asFUNCTIONPR(RandomPoint, (const Rect&), Point), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Point RandomPoint(int32 xMax, int32 yMax)", asFUNCTIONPR(RandomPoint, (int32, int32), Point), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("Vec2 RandomVec2()", asFUNCTIONPR(RandomVec2, (), Vec2), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec2 RandomVec2(double)", asFUNCTIONPR(RandomVec2, (double), Vec2), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec2 RandomVec2(double, const Vec2& in yMinMax)", asFUNCTIONPR(RandomVec2, (double, const std::pair<double, double>&), Vec2), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec2 RandomVec2(const Vec2& in xMinMax, double)", asFUNCTIONPR(RandomVec2, (const std::pair<double, double>&, double), Vec2), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec2 RandomVec2(const Vec2& in xMinMax, const Vec2& in yMinMax)", asFUNCTIONPR(RandomVec2, (const std::pair<double, double>&, const std::pair<double, double>&), Vec2), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec2 RandomVec2(double, double)", asFUNCTIONPR(RandomVec2, (double, double), Vec2), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec2 RandomVec2(const Line& in)", asFUNCTIONPR(RandomVec2, (const Line&), Vec2), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec2 RandomVec2(const Circle& in)", asFUNCTIONPR(RandomVec2, (const Circle&), Vec2), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec2 RandomVec2(const RectF& in)", asFUNCTIONPR(RandomVec2, (const RectF&), Vec2), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec2 RandomVec2(const Triangle& in)", asFUNCTIONPR(RandomVec2, (const Triangle&), Vec2), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec2 RandomVec2(const Quad& in)", asFUNCTIONPR(RandomVec2, (const Quad&), Vec2), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("Vec3 RandomVec3()", asFUNCTIONPR(RandomVec3, (), Vec3), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec3 RandomVec3onUnitSphere()", asFUNCTIONPR(RandomVec3onUnitSphere, (), Vec3), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec3 RandomVec3insideUnitSphere()", asFUNCTIONPR(RandomVec3insideUnitSphere, (), Vec3), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec3 RandomVec3(double)", asFUNCTIONPR(RandomVec3, (double), Vec3), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec3 RandomVec3(double, double, const Vec2& in zMinMax)", asFUNCTIONPR(RandomVec3, (double, double, const std::pair<double, double>&), Vec3), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec3 RandomVec3(double, const Vec2& in yMinMax, double)", asFUNCTIONPR(RandomVec3, (double, const std::pair<double, double>&, double), Vec3), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec3 RandomVec3(const Vec2& in xMinMax, double, double)", asFUNCTIONPR(RandomVec3, (const std::pair<double, double>&, double, double), Vec3), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec3 RandomVec3(double, const Vec2& in yMinMax, const Vec2& in zMinMax)", asFUNCTIONPR(RandomVec3, (double, const std::pair<double, double>&, const std::pair<double, double>&), Vec3), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec3 RandomVec3(const Vec2& in xMinMax, double, const Vec2& in zMinMax)", asFUNCTIONPR(RandomVec3, (const std::pair<double, double>&, double, const std::pair<double, double>&), Vec3), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec3 RandomVec3(const Vec2& in xMinMax, const Vec2& in yMinMax, double)", asFUNCTIONPR(RandomVec3, (const std::pair<double, double>&, const std::pair<double, double>&, double), Vec3), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec3 RandomVec3(const Vec2& in xMinMax, const Vec2& in yMinMax, const Vec2& in zMinMax)", asFUNCTIONPR(RandomVec3, (const std::pair<double, double>&, const std::pair<double, double>&, const std::pair<double, double>&), Vec3), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec3 RandomVec3(double, double, double)", asFUNCTIONPR(RandomVec3, (double, double, double), Vec3), asCALL_CDECL); assert(r >= 0);

		//RandomVec3(Box)
		//RandomVec3(Sphere)

		r = engine->RegisterGlobalFunction("Vec4 RandomVec4(const Vec2& in xMinMax, const Vec2& in yMinMax, const Vec2& in zMinMax, const Vec2& in wMinMax)", asFUNCTIONPR(RandomVec4, (const std::pair<double, double>&, const std::pair<double, double>&, const std::pair<double, double>&, const std::pair<double, double>&), Vec4), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec4 RandomVec4(double, double, double, double)", asFUNCTIONPR(RandomVec4, (double, double, double, double), Vec4), asCALL_CDECL); assert(r >= 0);
	}
}
