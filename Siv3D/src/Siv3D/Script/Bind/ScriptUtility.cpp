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

namespace s3d
{
	using namespace AngelScript;

	template <class Type>
	inline constexpr Type MaxPrimitive(Type a, Type b) noexcept
	{
		return (a < b) ? b : a;
	}

	template <class Type>
	inline constexpr Type MinPrimitive(Type a, Type b) noexcept
	{
		return (b < a) ? b : a;
	}

	template <class Type>
	inline constexpr Type ClampPrimitive(Type value, Type min, Type max) noexcept
	{
		return (value < min) ? min : ((max < value) ? max : value);
	}

	template <class Type>
	inline constexpr bool InRangePrimitive(Type value, Type min, Type max) noexcept
	{
		return (min <= value) && (value <= max);
	}

	template <class Type>
	inline constexpr bool InOpenRangePrimitive(Type value, Type min, Type max) noexcept
	{
		return (min < value) && (value < max);
	}

	template <class Type>
	inline constexpr Type AbsPrimitive(Type x) noexcept
	{
		if (x < 0)
		{
			return -x;
		}
		else
		{
			return x;
		}
	}

	template <class Type>
	inline constexpr Type AbsDiffPrimitive(Type a, Type b) noexcept
	{
		return static_cast<Type>(AbsDiff(a, b));
	}

	template <class Type>
	inline constexpr bool IsOddPrimitive(Type x) noexcept
	{
		return (x % 2) != 0;
	}
	
	template <class Type>
	inline constexpr bool IsEvenPrimitive(Type x) noexcept
	{
		return (x % 2) == 0;
	}

	void RegisterUtility(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		r = engine->RegisterGlobalFunction("uint8 Max(uint8, uint8)", asFUNCTION(MaxPrimitive<uint8>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint16 Max(uint16, uint16)", asFUNCTION(MaxPrimitive<uint16>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint32 Max(uint32, uint32)", asFUNCTION(MaxPrimitive<uint32>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint64 Max(uint64, uint64)", asFUNCTION(MaxPrimitive<uint64>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int8 Max(int8, int8)", asFUNCTION(MaxPrimitive<int8>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int16 Max(int16, int16)", asFUNCTION(MaxPrimitive<int16>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int32 Max(int32, int32)", asFUNCTION(MaxPrimitive<int32>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int64 Max(int64, int64)", asFUNCTION(MaxPrimitive<int64>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("float Max(float, float)", asFUNCTION(MaxPrimitive<float>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double Max(double, double)", asFUNCTION(MaxPrimitive<double>), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("uint8 Min(uint8, uint8)", asFUNCTION(MinPrimitive<uint8>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint16 Min(uint16, uint16)", asFUNCTION(MinPrimitive<uint16>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint32 Min(uint32, uint32)", asFUNCTION(MinPrimitive<uint32>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint64 Min(uint64, uint64)", asFUNCTION(MinPrimitive<uint64>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int8 Min(int8, int8)", asFUNCTION(MinPrimitive<int8>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int16 Min(int16, int16)", asFUNCTION(MinPrimitive<int16>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int32 Min(int32, int32)", asFUNCTION(MinPrimitive<int32>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int64 Min(int64, int64)", asFUNCTION(MinPrimitive<int64>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("float Min(float, float)", asFUNCTION(MinPrimitive<float>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double Min(double, double)", asFUNCTION(MinPrimitive<double>), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("uint8 Clamp(uint8, uint8, uint8)", asFUNCTION(ClampPrimitive<uint8>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint16 Clamp(uint16, uint16, uint16)", asFUNCTION(ClampPrimitive<uint16>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint32 Clamp(uint32, uint32, uint32)", asFUNCTION(ClampPrimitive<uint32>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint64 Clamp(uint64, uint64, uint64)", asFUNCTION(ClampPrimitive<uint64>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int8 Clamp(int8, int8, int8)", asFUNCTION(ClampPrimitive<int8>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int16 Clamp(int16, int16, int16)", asFUNCTION(ClampPrimitive<int16>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int32 Clamp(int32, int32, int32)", asFUNCTION(ClampPrimitive<int32>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int64 Clamp(int64, int64, int64)", asFUNCTION(ClampPrimitive<int64>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("float Clamp(float, float, float)", asFUNCTION(ClampPrimitive<float>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double Clamp(double, double, double)", asFUNCTION(ClampPrimitive<double>), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("bool InRange(uint8, uint8, uint8)", asFUNCTION(InRangePrimitive<uint8>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool InRange(uint16, uint16, uint16)", asFUNCTION(InRangePrimitive<uint16>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool InRange(uint32, uint32, uint32)", asFUNCTION(InRangePrimitive<uint32>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool InRange(uint64, uint64, uint64)", asFUNCTION(InRangePrimitive<uint64>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool InRange(int8, int8, int8)", asFUNCTION(InRangePrimitive<int8>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool InRange(int16, int16, int16)", asFUNCTION(InRangePrimitive<int16>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool InRange(int32, int32, int32)", asFUNCTION(InRangePrimitive<int32>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool InRange(int64, int64, int64)", asFUNCTION(InRangePrimitive<int64>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool InRange(float, float, float)", asFUNCTION(InRangePrimitive<float>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool InRange(double, double, double)", asFUNCTION(InRangePrimitive<double>), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("bool InOpenRange(uint8, uint8, uint8)", asFUNCTION(InOpenRangePrimitive<uint8>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool InOpenRange(uint16, uint16, uint16)", asFUNCTION(InOpenRangePrimitive<uint16>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool InOpenRange(uint32, uint32, uint32)", asFUNCTION(InOpenRangePrimitive<uint32>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool InOpenRange(uint64, uint64, uint64)", asFUNCTION(InOpenRangePrimitive<uint64>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool InOpenRange(int8, int8, int8)", asFUNCTION(InOpenRangePrimitive<int8>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool InOpenRange(int16, int16, int16)", asFUNCTION(InOpenRangePrimitive<int16>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool InOpenRange(int32, int32, int32)", asFUNCTION(InOpenRangePrimitive<int32>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool InOpenRange(int64, int64, int64)", asFUNCTION(InOpenRangePrimitive<int64>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool InOpenRange(float, float, float)", asFUNCTION(InOpenRangePrimitive<float>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool InOpenRange(double, double, double)", asFUNCTION(InOpenRangePrimitive<double>), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("int8 Abs(int8)", asFUNCTION(AbsPrimitive<int8>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int16 Abs(int16)", asFUNCTION(AbsPrimitive<int16>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int32 Abs(int32)", asFUNCTION(AbsPrimitive<int32>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int64 Abs(int64)", asFUNCTION(AbsPrimitive<int64>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("float Abs(float)", asFUNCTION(AbsPrimitive<float>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double Abs(double)", asFUNCTION(AbsPrimitive<double>), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("uint8 AbsDiff(uint8, uint8)", asFUNCTION(AbsDiffPrimitive<uint8>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint16 AbsDiff(uint16, uint16)", asFUNCTION(AbsDiffPrimitive<uint16>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint32 AbsDiff(uint32, uint32)", asFUNCTION(AbsDiffPrimitive<uint32>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("uint64 AbsDiff(uint64, uint64)", asFUNCTION(AbsDiffPrimitive<uint64>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int8 AbsDiff(int8, int8)", asFUNCTION(AbsDiffPrimitive<int8>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int16 AbsDiff(int16, int16)", asFUNCTION(AbsDiffPrimitive<int16>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int32 AbsDiff(int32, int32)", asFUNCTION(AbsDiffPrimitive<int32>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("int64 AbsDiff(int64, int64)", asFUNCTION(AbsDiffPrimitive<int64>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("float AbsDiff(float, float)", asFUNCTION(AbsDiffPrimitive<float>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("double AbsDiff(double, double)", asFUNCTION(AbsDiffPrimitive<double>), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("bool IsOdd(uint8)", asFUNCTION(IsOddPrimitive<uint8>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool IsOdd(uint16)", asFUNCTION(IsOddPrimitive<uint16>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool IsOdd(uint32)", asFUNCTION(IsOddPrimitive<uint32>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool IsOdd(uint64)", asFUNCTION(IsOddPrimitive<uint64>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool IsOdd(int8)", asFUNCTION(IsOddPrimitive<int8>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool IsOdd(int16)", asFUNCTION(IsOddPrimitive<int16>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool IsOdd(int32)", asFUNCTION(IsOddPrimitive<int32>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool IsOdd(int64)", asFUNCTION(IsOddPrimitive<int64>), asCALL_CDECL); assert(r >= 0);

		r = engine->RegisterGlobalFunction("bool IsEven(uint8)", asFUNCTION(IsEvenPrimitive<uint8>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool IsEven(uint16)", asFUNCTION(IsEvenPrimitive<uint16>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool IsEven(uint32)", asFUNCTION(IsEvenPrimitive<uint32>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool IsEven(uint64)", asFUNCTION(IsEvenPrimitive<uint64>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool IsEven(int8)", asFUNCTION(IsEvenPrimitive<int8>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool IsEven(int16)", asFUNCTION(IsEvenPrimitive<int16>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool IsEven(int32)", asFUNCTION(IsEvenPrimitive<int32>), asCALL_CDECL); assert(r >= 0);
		r = engine->RegisterGlobalFunction("bool IsEven(int64)", asFUNCTION(IsEvenPrimitive<int64>), asCALL_CDECL); assert(r >= 0);

		r = engine->SetDefaultNamespace("std"); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("void swap(uint8&, uint8&)", asFUNCTIONPR(std::swap, (uint8&, uint8&), void), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void swap(uint16&, uint16&)", asFUNCTIONPR(std::swap, (uint16&, uint16&), void), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void swap(uint32&, uint32&)", asFUNCTIONPR(std::swap, (uint32&, uint32&), void), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void swap(uint64&, uint64&)", asFUNCTIONPR(std::swap, (uint64&, uint64&), void), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void swap(int8&, int8&)", asFUNCTIONPR(std::swap, (int8&, int8&), void), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void swap(int16&, int16&)", asFUNCTIONPR(std::swap, (int16&, int16&), void), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void swap(int32&, int32&)", asFUNCTIONPR(std::swap, (int32&, int32&), void), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void swap(int64&, int64&)", asFUNCTIONPR(std::swap, (int64&, int64&), void), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void swap(float&, float&)", asFUNCTIONPR(std::swap, (float&, float&), void), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("void swap(double&, double&)", asFUNCTIONPR(std::swap, (double&, double&), void), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
