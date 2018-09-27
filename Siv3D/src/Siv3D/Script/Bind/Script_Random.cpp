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
# include <Siv3D/Random.hpp>
# include <Siv3D/RandomPoint.hpp>
# include <Siv3D/RandomVec2.hpp>
# include <Siv3D/RandomVec3.hpp>
# include <Siv3D/RandomVec4.hpp>
# include <Siv3D/RandomColor.hpp>
# include "ScriptBind.hpp"

namespace s3d
{
	using namespace AngelScript;

	template <class Type>
	static Type RandomPrimitive(Type min, Type max) noexcept
	{
		return UniformDistribution<Type>(min, max)(GetDefaultRNG());
	}

	template <class Type>
	static Type RandomMaxPrimitive(Type max) noexcept
	{
		return UniformDistribution<Type>(0, max)(GetDefaultRNG());
	}

	static uint8 RandomUint8Primitive(uint8 min, uint8 max) noexcept
	{
		return UniformDistribution<uint16>(min, max)(GetDefaultRNG()) & 0xFF;
	}

	static uint8 RandomUint8MaxPrimitive(uint8 max) noexcept
	{
		return UniformDistribution<uint16>(0, max)(GetDefaultRNG()) & 0xFF;
	}

	static int8 RandomInt8Primitive(int8 min, int8 max) noexcept
	{
		return static_cast<int8>(UniformDistribution<int16>(min, max)(GetDefaultRNG()));
	}

	static int8 RandomInt8MaxPrimitive(int8 max) noexcept
	{
		return static_cast<int8>(UniformDistribution<int16>(0, max)(GetDefaultRNG()));
	}
	
	void RegisterRandom(asIScriptEngine* engine)
	{
		int32 r = 0;

		r = engine->RegisterGlobalFunction("double Random()", asFUNCTIONPR(Random, (), double), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("uint8 Random(uint8, uint8)", asFUNCTION(RandomUint8Primitive), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint16 Random(uint16, uint16)", asFUNCTION(RandomPrimitive<uint16>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint32 Random(uint32, uint32)", asFUNCTION(RandomPrimitive<uint32>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint64 Random(uint64, uint64)", asFUNCTION(RandomPrimitive<uint64>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int8 Random(int8, int8)", asFUNCTION(RandomInt8Primitive), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int16 Random(int16, int16)", asFUNCTION(RandomPrimitive<int16>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int32 Random(int32, int32)", asFUNCTION(RandomPrimitive<int32>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int64 Random(int64, int64)", asFUNCTION(RandomPrimitive<int64>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("float Random(float, float)", asFUNCTION(RandomPrimitive<float>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double Random(double, double)", asFUNCTION(RandomPrimitive<double>), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("uint8 Random(uint8)", asFUNCTION(RandomUint8MaxPrimitive), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint16 Random(uint16)", asFUNCTION(RandomMaxPrimitive<uint16>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint32 Random(uint32)", asFUNCTION(RandomMaxPrimitive<uint32>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint64 Random(uint64)", asFUNCTION(RandomMaxPrimitive<uint64>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int8 Random(int8)", asFUNCTION(RandomInt8MaxPrimitive), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int16 Random(int16)", asFUNCTION(RandomMaxPrimitive<int16>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int32 Random(int32)", asFUNCTION(RandomMaxPrimitive<int32>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int64 Random(int64)", asFUNCTION(RandomMaxPrimitive<int64>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("float Random(float)", asFUNCTION(RandomMaxPrimitive<float>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double Random(double)", asFUNCTION(RandomMaxPrimitive<double>), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("bool RandomBool(double p =0.5)", asFUNCTION(RandomBool), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("Point RandomPoint(const Point& in xMinMax, const Point& in yMinMax)", asFUNCTIONPR(RandomPoint, (const std::pair<int32, int32>&, const std::pair<int32, int32>&), Point), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Point RandomPoint(const Rect& in)", asFUNCTIONPR(RandomPoint, (const Rect&), Point), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Point RandomPoint(int32 xMax, int32 yMax)", asFUNCTIONPR(RandomPoint, (int32, int32), Point), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("Vec2 RandomVec2()", asFUNCTIONPR(RandomVec2, (), Vec2), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec2 RandomVec2(double)", asFUNCTIONPR(RandomVec2, (double), Vec2), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec2 RandomVec2(double, const Vec2& in yMinMax)", asFUNCTIONPR(RandomVec2, (double, const std::pair<double, double>&), Vec2), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec2 RandomVec2(const Vec2& in xMinMax, double)", asFUNCTIONPR(RandomVec2, (const std::pair<double, double>&, double), Vec2), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec2 RandomVec2(const Vec2& in xMinMax, const Vec2& in yMinMax)", asFUNCTIONPR(RandomVec2, (const std::pair<double, double>&, const std::pair<double, double>&), Vec2), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec2 RandomVec2(double, double)", asFUNCTIONPR(RandomVec2, (double, double), Vec2), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec2 RandomVec2(const RectF& in)", asFUNCTIONPR(RandomVec2, (const RectF&), Vec2), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec2 RandomVec2(const Circle& in)", asFUNCTIONPR(RandomVec2, (const Circle&), Vec2), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec2 RandomVec2(const Triangle& in)", asFUNCTIONPR(RandomVec2, (const Triangle&), Vec2), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("Vec3 RandomVec3onUnitSphere()", asFUNCTION(RandomVec3onUnitSphere), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec3 RandomVec3insideUnitSphere()", asFUNCTION(RandomVec3insideUnitSphere), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec3 RandomVec3()", asFUNCTIONPR(RandomVec3, (), Vec3), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec3 RandomVec3(double)", asFUNCTIONPR(RandomVec3, (double), Vec3), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec3 RandomVec3(double, double, const Vec2& in zMinMax)", asFUNCTIONPR(RandomVec3, (double, double, const std::pair<double, double>&), Vec3), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec3 RandomVec3(double, const Vec2& in yMinMax, double)", asFUNCTIONPR(RandomVec3, (double, const std::pair<double, double>&, double), Vec3), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec3 RandomVec3(const Vec2& in xMinMax, double, double)", asFUNCTIONPR(RandomVec3, (const std::pair<double, double>&, double, double), Vec3), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec3 RandomVec3(double, const Vec2& in yMinMax, const Vec2& in zMinMax)", asFUNCTIONPR(RandomVec3, (double, const std::pair<double, double>&, const std::pair<double, double>&), Vec3), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec3 RandomVec3(const Vec2& in xMinMax, double, const Vec2& in zMinMax)", asFUNCTIONPR(RandomVec3, (const std::pair<double, double>&, double, const std::pair<double, double>&), Vec3), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec3 RandomVec3(const Vec2& in xMinMax, const Vec2& in yMinMax, double)", asFUNCTIONPR(RandomVec3, (const std::pair<double, double>&, const std::pair<double, double>&, double), Vec3), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec3 RandomVec3(const Vec2& in xMinMax, const Vec2& in yMinMax, const Vec2& in zMinMax)", asFUNCTIONPR(RandomVec3, (const std::pair<double, double>&, const std::pair<double, double>&, const std::pair<double, double>&), Vec3), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec3 RandomVec3(double, double, double)", asFUNCTIONPR(RandomVec3, (double, double, double), Vec3), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("Vec4 RandomVec4(const Vec2& in xMinMax, const Vec2& in yMinMax, const Vec2& in zMinMax, const Vec2& in wMinMax)", asFUNCTIONPR(RandomVec4, (const std::pair<double, double>&, const std::pair<double, double>&, const std::pair<double, double>&, const std::pair<double, double>&), Vec4), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Vec4 RandomVec4(double, double, double, double)", asFUNCTIONPR(RandomVec4, (double, double, double, double), Vec4), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("Color RandomColor()", asFUNCTIONPR(RandomColor, (), Color), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("Color RandomColor(const Point& in rMinMax, const Point& in gMinMax, const Point& in bMinMax)", asFUNCTIONPR(RandomColor, (const std::pair<uint32, uint32>&, const std::pair<uint32, uint32>&, const std::pair<uint32, uint32>&), Color), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("ColorF RandomColorF()", asFUNCTIONPR(RandomColorF, (), ColorF), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("ColorF RandomColorF(const Vec2& in rMinMax, const Vec2& in gMinMax, const Vec2& in bMinMax)", asFUNCTIONPR(RandomColorF, (const std::pair<double, double>&, const std::pair<double, double>&, const std::pair<double, double>&), ColorF), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("HSV RandomHSV()", asFUNCTIONPR(RandomHSV, (), HSV), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("HSV RandomHSV(const Vec2& in hMinMax, const Vec2& in sMinMax, const Vec2& in vMinMax)", asFUNCTIONPR(RandomHSV, (const std::pair<double, double>&, const std::pair<double, double>&, const std::pair<double, double>&), HSV), asCALL_CDECL); assert(r >= 0);
	}
}
