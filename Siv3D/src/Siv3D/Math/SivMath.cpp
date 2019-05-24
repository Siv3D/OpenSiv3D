//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Math.hpp>

namespace s3d
{
	namespace Math
	{
		//////////////////////////////////////////////////
		//
		//	Fmod
		//
		//////////////////////////////////////////////////

		Float2 Fmod(const Float2& v1, const Float2& v2)
		{
			return{ Fmod(v1.x, v2.x), Fmod(v1.y, v2.y) };
		}

		Float3 Fmod(const Float3& v1, const Float3& v2)
		{
			return{ Fmod(v1.x, v2.x), Fmod(v1.y, v2.y), Fmod(v1.z, v2.z) };
		}

		Float4 Fmod(const Float4& v1, const Float4& v2)
		{
			return{ Fmod(v1.x, v2.x), Fmod(v1.y, v2.y), Fmod(v1.z, v2.z), Fmod(v1.w, v2.w) };
		}

		Vec2 Fmod(const Vec2& v1, const Vec2& v2)
		{
			return{ Fmod(v1.x, v2.x), Fmod(v1.y, v2.y) };
		}

		Vec3 Fmod(const Vec3& v1, const Vec3& v2)
		{
			return{ Fmod(v1.x, v2.x), Fmod(v1.y, v2.y), Fmod(v1.z, v2.z) };
		}

		Vec4 Fmod(const Vec4& v1, const Vec4& v2)
		{
			return{ Fmod(v1.x, v2.x), Fmod(v1.y, v2.y), Fmod(v1.z, v2.z), Fmod(v1.w, v2.w) };
		}

		//////////////////////////////////////////////////
		//
		//	Fraction
		//
		//////////////////////////////////////////////////

		Float2 Fraction(const Float2& v)
		{
			return{ Fraction(v.x), Fraction(v.y) };
		}

		Float3 Fraction(const Float3& v)
		{
			return{ Fraction(v.x), Fraction(v.y), Fraction(v.z) };
		}

		Float4 Fraction(const Float4& v)
		{
			return{ Fraction(v.x), Fraction(v.y), Fraction(v.z), Fraction(v.w) };
		}

		Vec2 Fraction(const Vec2& v)
		{
			return{ Fraction(v.x), Fraction(v.y) };
		}

		Vec3 Fraction(const Vec3& v)
		{
			return{ Fraction(v.x), Fraction(v.y), Fraction(v.z) };
		}

		Vec4 Fraction(const Vec4& v)
		{
			return{ Fraction(v.x), Fraction(v.y), Fraction(v.z), Fraction(v.w) };
		}

		//////////////////////////////////////////////////
		//
		//	Frexp
		//
		//////////////////////////////////////////////////

		Float2 Frexp(const Float2& x, Float2& exp)
		{
			int32 ex, ey;
			const auto tx = std::frexp(x.x, &ex);
			const auto ty = std::frexp(x.y, &ey);
			exp.set(static_cast<float>(ex), static_cast<float>(ey));
			return{ tx, ty };
		}

		Float3 Frexp(const Float3& x, Float3& exp)
		{
			int32 ex, ey, ez;
			const auto tx = std::frexp(x.x, &ex);
			const auto ty = std::frexp(x.y, &ey);
			const auto tz = std::frexp(x.z, &ez);
			exp.set(static_cast<float>(ex), static_cast<float>(ey), static_cast<float>(ez));
			return{ tx, ty, tz };
		}

		Float4 Frexp(const Float4& x, Float4& exp)
		{
			int32 ex, ey, ez, ew;
			const auto tx = std::frexp(x.x, &ex);
			const auto ty = std::frexp(x.y, &ey);
			const auto tz = std::frexp(x.z, &ez);
			const auto tw = std::frexp(x.w, &ew);
			exp.set(static_cast<float>(ex), static_cast<float>(ey), static_cast<float>(ez), static_cast<float>(ew));
			return{ tx, ty, tz, tw };
		}

		Vec2 Frexp(const Vec2& x, Vec2& exp)
		{
			int32 ex, ey;
			const auto tx = std::frexp(x.x, &ex);
			const auto ty = std::frexp(x.y, &ey);
			exp.set(ex, ey);
			return{ tx, ty };
		}

		Vec3 Frexp(const Vec3& x, Vec3& exp)
		{
			int32 ex, ey, ez;
			const auto tx = std::frexp(x.x, &ex);
			const auto ty = std::frexp(x.y, &ey);
			const auto tz = std::frexp(x.z, &ez);
			exp.set(ex, ey, ez);
			return{ tx, ty, tz };
		}

		Vec4 Frexp(const Vec4& x, Vec4& exp)
		{
			int32 ex, ey, ez, ew;
			const auto tx = std::frexp(x.x, &ex);
			const auto ty = std::frexp(x.y, &ey);
			const auto tz = std::frexp(x.z, &ez);
			const auto tw = std::frexp(x.w, &ew);
			exp.set(ex, ey, ez, ew);
			return{ tx, ty, tz, tw };
		}

		//////////////////////////////////////////////////
		//
		//	Ldexp
		//
		//////////////////////////////////////////////////

		Float2 Ldexp(const Float2& x, const Float2& exp)
		{
			return{ Ldexp(x.x, exp.x), Ldexp(x.y, exp.y) };
		}

		Float3 Ldexp(const Float3& x, const Float3& exp)
		{
			return{ Ldexp(x.x, exp.x), Ldexp(x.y, exp.y), Ldexp(x.z, exp.z) };
		}

		Float4 Ldexp(const Float4& x, const Float4& exp)
		{
			return{ Ldexp(x.x, exp.x), Ldexp(x.y, exp.y), Ldexp(x.z, exp.z), Ldexp(x.w, exp.w) };
		}

		Vec2 Ldexp(const Vec2& x, const Vec2& exp)
		{
			return{ Ldexp(x.x, exp.x), Ldexp(x.y, exp.y) };
		}

		Vec3 Ldexp(const Vec3& x, const Vec3& exp)
		{
			return{ Ldexp(x.x, exp.x), Ldexp(x.y, exp.y), Ldexp(x.z, exp.z) };
		}

		Vec4 Ldexp(const Vec4& x, const Vec4& exp)
		{
			return{ Ldexp(x.x, exp.x), Ldexp(x.y, exp.y), Ldexp(x.z, exp.z), Ldexp(x.w, exp.w) };
		}

		//////////////////////////////////////////////////
		//
		//	Log
		//
		//////////////////////////////////////////////////

		Vec2 Log(const Point& v)
		{
			return{ Log(v.x), Log(v.y) };
		}

		Float2 Log(const Float2& v)
		{
			return{ Log(v.x), Log(v.y) };
		}

		Float3 Log(const Float3& v)
		{
			return{ Log(v.x), Log(v.y), Log(v.z) };
		}

		Float4 Log(const Float4& v)
		{
			return{ Log(v.x), Log(v.y), Log(v.z), Log(v.w) };
		}

		Vec2 Log(const Vec2& v)
		{
			return{ Log(v.x), Log(v.y) };
		}

		Vec3 Log(const Vec3& v)
		{
			return{ Log(v.x), Log(v.y), Log(v.z) };
		}

		Vec4 Log(const Vec4& v)
		{
			return{ Log(v.x), Log(v.y), Log(v.z), Log(v.w) };
		}

		//////////////////////////////////////////////////
		//
		//	Log2
		//
		//////////////////////////////////////////////////

		Vec2 Log2(const Point& v)
		{
			return{ Log2(v.x), Log2(v.y) };
		}

		Float2 Log2(const Float2& v)
		{
			return{ Log2(v.x), Log2(v.y) };
		}

		Float3 Log2(const Float3& v)
		{
			return{ Log2(v.x), Log2(v.y), Log2(v.z) };
		}

		Float4 Log2(const Float4& v)
		{
			return{ Log2(v.x), Log2(v.y), Log2(v.z), Log2(v.w) };
		}

		Vec2 Log2(const Vec2& v)
		{
			return{ Log2(v.x), Log2(v.y) };
		}

		Vec3 Log2(const Vec3& v)
		{
			return{ Log2(v.x), Log2(v.y), Log2(v.z) };
		}

		Vec4 Log2(const Vec4& v)
		{
			return{ Log2(v.x), Log2(v.y), Log2(v.z), Log2(v.w) };
		}

		//////////////////////////////////////////////////
		//
		//	Log10
		//
		//////////////////////////////////////////////////

		Vec2 Log10(const Point& v)
		{
			return{ Log10(v.x), Log10(v.y) };
		}

		Float2 Log10(const Float2& v)
		{
			return{ Log10(v.x), Log10(v.y) };
		}

		Float3 Log10(const Float3& v)
		{
			return{ Log10(v.x), Log10(v.y), Log10(v.z) };
		}

		Float4 Log10(const Float4& v)
		{
			return{ Log10(v.x), Log10(v.y), Log10(v.z), Log10(v.w) };
		}

		Vec2 Log10(const Vec2& v)
		{
			return{ Log10(v.x), Log10(v.y) };
		}

		Vec3 Log10(const Vec3& v)
		{
			return{ Log10(v.x), Log10(v.y), Log10(v.z) };
		}

		Vec4 Log10(const Vec4& v)
		{
			return{ Log10(v.x), Log10(v.y), Log10(v.z), Log10(v.w) };
		}

		//////////////////////////////////////////////////
		//
		//	Modf
		//
		//////////////////////////////////////////////////

		Float2 Modf(const Float2& x, Float2& i)
		{
			return{ Modf(x.x, i.x), Modf(x.y, i.y) };
		}

		Float3 Modf(const Float3& x, Float3& i)
		{
			return{ Modf(x.x, i.x), Modf(x.y, i.y), Modf(x.z, i.z) };
		}

		Float4 Modf(const Float4& x, Float4& i)
		{
			return{ Modf(x.x, i.x), Modf(x.y, i.y), Modf(x.z, i.z), Modf(x.w, i.w) };
		}

		Vec2 Modf(const Vec2& x, Vec2& i)
		{
			return{ Modf(x.x, i.x), Modf(x.y, i.y) };
		}

		Vec3 Modf(const Vec3& x, Vec3& i)
		{
			return{ Modf(x.x, i.x), Modf(x.y, i.y), Modf(x.z, i.z) };
		}

		Vec4 Modf(const Vec4& x, Vec4& i)
		{
			return{ Modf(x.x, i.x), Modf(x.y, i.y), Modf(x.z, i.z), Modf(x.w, i.w) };
		}

		//////////////////////////////////////////////////
		//
		//	Sign
		//
		//////////////////////////////////////////////////

		Vec2 Sign(const Point& v) noexcept
		{
			return{ Sign(v.x), Sign(v.y) };
		}

		Float2 Sign(const Float2& v) noexcept
		{
			return{ Sign(v.x), Sign(v.y) };
		}

		Float3 Sign(const Float3& v) noexcept
		{
			return{ Sign(v.x), Sign(v.y), Sign(v.z) };
		}

		Float4 Sign(const Float4& v) noexcept
		{
			return{ Sign(v.x), Sign(v.y), Sign(v.z), Sign(v.w) };
		}

		Vec2 Sign(const Vec2& v) noexcept
		{
			return{ Sign(v.x), Sign(v.y) };
		}

		Vec3 Sign(const Vec3& v) noexcept
		{
			return{ Sign(v.x), Sign(v.y), Sign(v.z) };
		}

		Vec4 Sign(const Vec4& v) noexcept
		{
			return{ Sign(v.x), Sign(v.y), Sign(v.z), Sign(v.w) };
		}

		//////////////////////////////////////////////////
		//
		//	ToRadians
		//
		//////////////////////////////////////////////////

		Vec2 ToRadians(const Point& v) noexcept
		{
			return{ ToRadians(v.x), ToRadians(v.y) };
		}

		Float2 ToRadians(const Float2& v) noexcept
		{
			return{ ToRadians(v.x), ToRadians(v.y) };
		}

		Float3 ToRadians(const Float3& v) noexcept
		{
			return{ ToRadians(v.x), ToRadians(v.y), ToRadians(v.z) };
		}

		Float4 ToRadians(const Float4& v) noexcept
		{
			return{ ToRadians(v.x), ToRadians(v.y), ToRadians(v.z), ToRadians(v.w) };
		}

		Vec2 ToRadians(const Vec2& v) noexcept
		{
			return{ ToRadians(v.x), ToRadians(v.y) };
		}

		Vec3 ToRadians(const Vec3& v) noexcept
		{
			return{ ToRadians(v.x), ToRadians(v.y), ToRadians(v.z) };
		}

		Vec4 ToRadians(const Vec4& v) noexcept
		{
			return{ ToRadians(v.x), ToRadians(v.y), ToRadians(v.z), ToRadians(v.w) };
		}

		//////////////////////////////////////////////////
		//
		//	ToDegrees
		//
		//////////////////////////////////////////////////

		Vec2 ToDegrees(const Point& v) noexcept
		{
			return{ ToDegrees(v.x), ToDegrees(v.y) };
		}

		Float2 ToDegrees(const Float2& v) noexcept
		{
			return{ ToDegrees(v.x), ToDegrees(v.y) };
		}

		Float3 ToDegrees(const Float3& v) noexcept
		{
			return{ ToDegrees(v.x), ToDegrees(v.y), ToDegrees(v.z) };
		}

		Float4 ToDegrees(const Float4& v) noexcept
		{
			return{ ToDegrees(v.x), ToDegrees(v.y), ToDegrees(v.z), ToDegrees(v.w) };
		}

		Vec2 ToDegrees(const Vec2& v) noexcept
		{
			return{ ToDegrees(v.x), ToDegrees(v.y) };
		}

		Vec3 ToDegrees(const Vec3& v) noexcept
		{
			return{ ToDegrees(v.x), ToDegrees(v.y), ToDegrees(v.z) };
		}

		Vec4 ToDegrees(const Vec4& v) noexcept
		{
			return{ ToDegrees(v.x), ToDegrees(v.y), ToDegrees(v.z), ToDegrees(v.w) };
		}

		//////////////////////////////////////////////////
		//
		//	Abs
		//
		//////////////////////////////////////////////////

		Point Abs(const Point& v) noexcept
		{
			return{ Abs(v.x), Abs(v.y) };
		}

		Float2 Abs(const Float2& v) noexcept
		{
			return{ Abs(v.x), Abs(v.y) };
		}

		Float3 Abs(const Float3& v) noexcept
		{
			return{ Abs(v.x), Abs(v.y), Abs(v.z) };
		}

		Float4 Abs(const Float4& v) noexcept
		{
			return{ Abs(v.x), Abs(v.y), Abs(v.z), Abs(v.w) };
		}

		Vec2 Abs(const Vec2& v) noexcept
		{
			return{ Abs(v.x), Abs(v.y) };
		}

		Vec3 Abs(const Vec3& v) noexcept
		{
			return{ Abs(v.x), Abs(v.y), Abs(v.z) };
		}

		Vec4 Abs(const Vec4& v) noexcept
		{
			return{ Abs(v.x), Abs(v.y), Abs(v.z), Abs(v.w) };
		}

		//////////////////////////////////////////////////
		//
		//	AbsDiff
		//
		//////////////////////////////////////////////////

		Float2 AbsDiff(const Float2& v1, const Float2& v2)
		{
			return{ AbsDiff(v1.x, v2.x), AbsDiff(v1.y, v2.y) };
		}

		Float3 AbsDiff(const Float3& v1, const Float3& v2)
		{
			return{ AbsDiff(v1.x, v2.x), AbsDiff(v1.y, v2.y), AbsDiff(v1.z, v2.z) };
		}

		Float4 AbsDiff(const Float4& v1, const Float4& v2)
		{
			return{ AbsDiff(v1.x, v2.x), AbsDiff(v1.y, v2.y), AbsDiff(v1.z, v2.z), AbsDiff(v1.w, v2.w) };
		}

		Vec2 AbsDiff(const Vec2& v1, const Vec2& v2)
		{
			return{ AbsDiff(v1.x, v2.x), AbsDiff(v1.y, v2.y) };
		}

		Vec3 AbsDiff(const Vec3& v1, const Vec3& v2)
		{
			return{ AbsDiff(v1.x, v2.x), AbsDiff(v1.y, v2.y), AbsDiff(v1.z, v2.z) };
		}

		Vec4 AbsDiff(const Vec4& v1, const Vec4& v2)
		{
			return{ AbsDiff(v1.x, v2.x), AbsDiff(v1.y, v2.y), AbsDiff(v1.z, v2.z), AbsDiff(v1.w, v2.w) };
		}

		//////////////////////////////////////////////////
		//
		//	Exp
		//
		//////////////////////////////////////////////////

		Vec2 Exp(const Point& v)
		{
			return{ Exp(v.x), Exp(v.y) };
		}

		Float2 Exp(const Float2& v)
		{
			return{ Exp(v.x), Exp(v.y) };
		}

		Float3 Exp(const Float3& v)
		{
			return{ Exp(v.x), Exp(v.y), Exp(v.z) };
		}

		Float4 Exp(const Float4& v)
		{
			return{ Exp(v.x), Exp(v.y), Exp(v.z), Exp(v.w) };
		}

		Vec2 Exp(const Vec2& v)
		{
			return{ Exp(v.x), Exp(v.y) };
		}

		Vec3 Exp(const Vec3& v)
		{
			return{ Exp(v.x), Exp(v.y), Exp(v.z) };
		}

		Vec4 Exp(const Vec4& v)
		{
			return{ Exp(v.x), Exp(v.y), Exp(v.z), Exp(v.w) };
		}

		//////////////////////////////////////////////////
		//
		//	Exp2
		//
		//////////////////////////////////////////////////

		Vec2 Exp2(const Point& v)
		{
			return{ Exp2(v.x), Exp2(v.y) };
		}

		Float2 Exp2(const Float2& v)
		{
			return{ Exp2(v.x), Exp2(v.y) };
		}

		Float3 Exp2(const Float3& v)
		{
			return{ Exp2(v.x), Exp2(v.y), Exp2(v.z) };
		}

		Float4 Exp2(const Float4& v)
		{
			return{ Exp2(v.x), Exp2(v.y), Exp2(v.z), Exp2(v.w) };
		}

		Vec2 Exp2(const Vec2& v)
		{
			return{ Exp2(v.x), Exp2(v.y) };
		}

		Vec3 Exp2(const Vec3& v)
		{
			return{ Exp2(v.x), Exp2(v.y), Exp2(v.z) };
		}

		Vec4 Exp2(const Vec4& v)
		{
			return{ Exp2(v.x), Exp2(v.y), Exp2(v.z), Exp2(v.w) };
		}

		//////////////////////////////////////////////////
		//
		//	Rsqrt
		//
		//////////////////////////////////////////////////

		Vec2 Rsqrt(const Point& v)
		{
			return{ Rsqrt(v.x), Rsqrt(v.y) };
		}

		Float2 Rsqrt(const Float2& v)
		{
			return{ Rsqrt(v.x), Rsqrt(v.y) };
		}

		Float3 Rsqrt(const Float3& v)
		{
			return{ Rsqrt(v.x), Rsqrt(v.y), Rsqrt(v.z) };
		}

		Float4 Rsqrt(const Float4& v)
		{
			return{ Rsqrt(v.x), Rsqrt(v.y), Rsqrt(v.z), Rsqrt(v.w) };
		}

		Vec2 Rsqrt(const Vec2& v)
		{
			return{ Rsqrt(v.x), Rsqrt(v.y) };
		}

		Vec3 Rsqrt(const Vec3& v)
		{
			return{ Rsqrt(v.x), Rsqrt(v.y), Rsqrt(v.z) };
		}

		Vec4 Rsqrt(const Vec4& v)
		{
			return{ Rsqrt(v.x), Rsqrt(v.y), Rsqrt(v.z), Rsqrt(v.w) };
		}

		//////////////////////////////////////////////////
		//
		//	Sqrt
		//
		//////////////////////////////////////////////////

		Vec2 Sqrt(const Point& v)
		{
			return{ Sqrt(v.x), Sqrt(v.y) };
		}

		Float2 Sqrt(const Float2& v)
		{
			return{ Sqrt(v.x), Sqrt(v.y) };
		}

		Float3 Sqrt(const Float3& v)
		{
			return{ Sqrt(v.x), Sqrt(v.y), Sqrt(v.z) };
		}

		Float4 Sqrt(const Float4& v)
		{
			return{ Sqrt(v.x), Sqrt(v.y), Sqrt(v.z), Sqrt(v.w) };
		}

		Vec2 Sqrt(const Vec2& v)
		{
			return{ Sqrt(v.x), Sqrt(v.y) };
		}

		Vec3 Sqrt(const Vec3& v)
		{
			return{ Sqrt(v.x), Sqrt(v.y), Sqrt(v.z) };
		}

		Vec4 Sqrt(const Vec4& v)
		{
			return{ Sqrt(v.x), Sqrt(v.y), Sqrt(v.z), Sqrt(v.w) };
		}

		//////////////////////////////////////////////////
		//
		//	Ceil
		//
		//////////////////////////////////////////////////

		Float2 Ceil(const Float2& v)
		{
			return{ Ceil(v.x), Ceil(v.y) };
		}

		Float3 Ceil(const Float3& v)
		{
			return{ Ceil(v.x), Ceil(v.y), Ceil(v.z) };
		}

		Float4 Ceil(const Float4& v)
		{
			return{ Ceil(v.x), Ceil(v.y), Ceil(v.z), Ceil(v.w) };
		}

		Vec2 Ceil(const Vec2& v)
		{
			return{ Ceil(v.x), Ceil(v.y) };
		}

		Vec3 Ceil(const Vec3& v)
		{
			return{ Ceil(v.x), Ceil(v.y), Ceil(v.z) };
		}

		Vec4 Ceil(const Vec4& v)
		{
			return{ Ceil(v.x), Ceil(v.y), Ceil(v.z), Ceil(v.w) };
		}

		//////////////////////////////////////////////////
		//
		//	Floor
		//
		//////////////////////////////////////////////////

		Float2 Floor(const Float2& v)
		{
			return{ Floor(v.x), Floor(v.y) };
		}

		Float3 Floor(const Float3& v)
		{
			return{ Floor(v.x), Floor(v.y), Floor(v.z) };
		}

		Float4 Floor(const Float4& v)
		{
			return{ Floor(v.x), Floor(v.y), Floor(v.z), Floor(v.w) };
		}

		Vec2 Floor(const Vec2& v)
		{
			return{ Floor(v.x), Floor(v.y) };
		}

		Vec3 Floor(const Vec3& v)
		{
			return{ Floor(v.x), Floor(v.y), Floor(v.z) };
		}

		Vec4 Floor(const Vec4& v)
		{
			return{ Floor(v.x), Floor(v.y), Floor(v.z), Floor(v.w) };
		}

		//////////////////////////////////////////////////
		//
		//	Round
		//
		//////////////////////////////////////////////////

		Float2 Round(const Float2& v)
		{
			return{ Round(v.x), Round(v.y) };
		}

		Float3 Round(const Float3& v)
		{
			return{ Round(v.x), Round(v.y), Round(v.z) };
		}

		Float4 Round(const Float4& v)
		{
			return{ Round(v.x), Round(v.y), Round(v.z), Round(v.w) };
		}

		Vec2 Round(const Vec2& v)
		{
			return{ Round(v.x), Round(v.y) };
		}

		Vec3 Round(const Vec3& v)
		{
			return{ Round(v.x), Round(v.y), Round(v.z) };
		}

		Vec4 Round(const Vec4& v)
		{
			return{ Round(v.x), Round(v.y), Round(v.z), Round(v.w) };
		}

		//////////////////////////////////////////////////
		//
		//	Clamp
		//
		//////////////////////////////////////////////////

		Point Clamp(const Point& v, int32 min, int32 max)
		{
			return{ s3d::Clamp(v.x, min, max), s3d::Clamp(v.y, min, max) };
		}

		Float2 Clamp(const Float2& v, float min, float max)
		{
			return{ s3d::Clamp(v.x, min, max), s3d::Clamp(v.y, min, max) };
		}

		Float3 Clamp(const Float3& v, float min, float max)
		{
			return{ s3d::Clamp(v.x, min, max), s3d::Clamp(v.y, min, max), s3d::Clamp(v.z, min, max) };
		}

		Float4 Clamp(const Float4& v, float min, float max)
		{
			return{ s3d::Clamp(v.x, min, max), s3d::Clamp(v.y, min, max), s3d::Clamp(v.z, min, max), s3d::Clamp(v.w, min, max) };
		}

		Vec2 Clamp(const Vec2& v, double min, double max)
		{
			return{ s3d::Clamp(v.x, min, max), s3d::Clamp(v.y, min, max) };
		}

		Vec3 Clamp(const Vec3& v, double min, double max)
		{
			return{ s3d::Clamp(v.x, min, max), s3d::Clamp(v.y, min, max), s3d::Clamp(v.z, min, max) };
		}

		Vec4 Clamp(const Vec4& v, double min, double max)
		{
			return{ s3d::Clamp(v.x, min, max), s3d::Clamp(v.y, min, max), s3d::Clamp(v.z, min, max), s3d::Clamp(v.w, min, max) };
		}

		//////////////////////////////////////////////////
		//
		//	Saturate
		//
		//////////////////////////////////////////////////

		Vec2 Saturate(const Point& v)
		{
			return{ s3d::Clamp(v.x, 0 , 1),  s3d::Clamp(v.y, 0, 1) };
		}

		Float2 Saturate(const Float2& v)
		{
			return{ Saturate(v.x), Saturate(v.y) };
		}

		Float3 Saturate(const Float3& v)
		{
			return{ Saturate(v.x), Saturate(v.y), Saturate(v.z) };
		}

		Float4 Saturate(const Float4& v)
		{
			return{ Saturate(v.x), Saturate(v.y), Saturate(v.z), Saturate(v.w) };
		}

		Vec2 Saturate(const Vec2& v)
		{
			return{ Saturate(v.x), Saturate(v.y) };
		}

		Vec3 Saturate(const Vec3& v)
		{
			return{ Saturate(v.x), Saturate(v.y), Saturate(v.z) };
		}

		Vec4 Saturate(const Vec4& v)
		{
			return{ Saturate(v.x), Saturate(v.y), Saturate(v.z), Saturate(v.w) };
		}

		//////////////////////////////////////////////////
		//
		//	Acos
		//
		//////////////////////////////////////////////////

		Vec2 Acos(const Point& v)
		{
			return{ Acos(v.x), Acos(v.y) };
		}

		Float2 Acos(const Float2& v)
		{
			return{ Acos(v.x), Acos(v.y) };
		}

		Float3 Acos(const Float3& v)
		{
			return{ Acos(v.x), Acos(v.y), Acos(v.z) };
		}

		Float4 Acos(const Float4& v)
		{
			return{ Acos(v.x), Acos(v.y), Acos(v.z), Acos(v.w) };
		}

		Vec2 Acos(const Vec2& v)
		{
			return{ Acos(v.x), Acos(v.y) };
		}

		Vec3 Acos(const Vec3& v)
		{
			return{ Acos(v.x), Acos(v.y), Acos(v.z) };
		}

		Vec4 Acos(const Vec4& v)
		{
			return{ Acos(v.x), Acos(v.y), Acos(v.z), Acos(v.w) };
		}

		//////////////////////////////////////////////////
		//
		//	Asin
		//
		//////////////////////////////////////////////////

		Vec2 Asin(const Point& v)
		{
			return{ Asin(v.x), Asin(v.y) };
		}

		Float2 Asin(const Float2& v)
		{
			return{ Asin(v.x), Asin(v.y) };
		}

		Float3 Asin(const Float3& v)
		{
			return{ Asin(v.x), Asin(v.y), Asin(v.z) };
		}

		Float4 Asin(const Float4& v)
		{
			return{ Asin(v.x), Asin(v.y), Asin(v.z), Asin(v.w) };
		}

		Vec2 Asin(const Vec2& v)
		{
			return{ Asin(v.x), Asin(v.y) };
		}

		Vec3 Asin(const Vec3& v)
		{
			return{ Asin(v.x), Asin(v.y), Asin(v.z) };
		}

		Vec4 Asin(const Vec4& v)
		{
			return{ Asin(v.x), Asin(v.y), Asin(v.z), Asin(v.w) };
		}

		//////////////////////////////////////////////////
		//
		//	Atan
		//
		//////////////////////////////////////////////////

		Vec2 Atan(const Point& v)
		{
			return{ Atan(v.x), Atan(v.y) };
		}

		Float2 Atan(const Float2& v)
		{
			return{ Atan(v.x), Atan(v.y) };
		}

		Float3 Atan(const Float3& v)
		{
			return{ Atan(v.x), Atan(v.y), Atan(v.z) };
		}

		Float4 Atan(const Float4& v)
		{
			return{ Atan(v.x), Atan(v.y), Atan(v.z), Atan(v.w) };
		}

		Vec2 Atan(const Vec2& v)
		{
			return{ Atan(v.x), Atan(v.y) };
		}

		Vec3 Atan(const Vec3& v)
		{
			return{ Atan(v.x), Atan(v.y), Atan(v.z) };
		}

		Vec4 Atan(const Vec4& v)
		{
			return{ Atan(v.x), Atan(v.y), Atan(v.z), Atan(v.w) };
		}

		//////////////////////////////////////////////////
		//
		//	Cos
		//
		//////////////////////////////////////////////////

		Vec2 Cos(const Point& v)
		{
			return{ Cos(v.x), Cos(v.y) };
		}

		Float2 Cos(const Float2& v)
		{
			return{ Cos(v.x), Cos(v.y) };
		}

		Float3 Cos(const Float3& v)
		{
			return{ Cos(v.x), Cos(v.y), Cos(v.z) };
		}

		Float4 Cos(const Float4& v)
		{
			return{ Cos(v.x), Cos(v.y), Cos(v.z), Cos(v.w) };
		}

		Vec2 Cos(const Vec2& v)
		{
			return{ Cos(v.x), Cos(v.y) };
		}

		Vec3 Cos(const Vec3& v)
		{
			return{ Cos(v.x), Cos(v.y), Cos(v.z) };
		}

		Vec4 Cos(const Vec4& v)
		{
			return{ Cos(v.x), Cos(v.y), Cos(v.z), Cos(v.w) };
		}

		//////////////////////////////////////////////////
		//
		//	Cosh
		//
		//////////////////////////////////////////////////

		Vec2 Cosh(const Point& v)
		{
			return{ Cosh(v.x), Cosh(v.y) };
		}

		Float2 Cosh(const Float2& v)
		{
			return{ Cosh(v.x), Cosh(v.y) };
		}

		Float3 Cosh(const Float3& v)
		{
			return{ Cosh(v.x), Cosh(v.y), Cosh(v.z) };
		}

		Float4 Cosh(const Float4& v)
		{
			return{ Cosh(v.x), Cosh(v.y), Cosh(v.z), Cosh(v.w) };
		}

		Vec2 Cosh(const Vec2& v)
		{
			return{ Cosh(v.x), Cosh(v.y) };
		}

		Vec3 Cosh(const Vec3& v)
		{
			return{ Cosh(v.x), Cosh(v.y), Cosh(v.z) };
		}

		Vec4 Cosh(const Vec4& v)
		{
			return{ Cosh(v.x), Cosh(v.y), Cosh(v.z), Cosh(v.w) };
		}

		//////////////////////////////////////////////////
		//
		//	Sin
		//
		//////////////////////////////////////////////////

		Vec2 Sin(const Point& v)
		{
			return{ Sin(v.x), Sin(v.y) };
		}

		Float2 Sin(const Float2& v)
		{
			return{ Sin(v.x), Sin(v.y) };
		}

		Float3 Sin(const Float3& v)
		{
			return{ Sin(v.x), Sin(v.y), Sin(v.z) };
		}

		Float4 Sin(const Float4& v)
		{
			return{ Sin(v.x), Sin(v.y), Sin(v.z), Sin(v.w) };
		}

		Vec2 Sin(const Vec2& v)
		{
			return{ Sin(v.x), Sin(v.y) };
		}

		Vec3 Sin(const Vec3& v)
		{
			return{ Sin(v.x), Sin(v.y), Sin(v.z) };
		}

		Vec4 Sin(const Vec4& v)
		{
			return{ Sin(v.x), Sin(v.y), Sin(v.z), Sin(v.w) };
		}

		//////////////////////////////////////////////////
		//
		//	Sinh
		//
		//////////////////////////////////////////////////

		Vec2 Sinh(const Point& v)
		{
			return{ Sinh(v.x), Sinh(v.y) };
		}

		Float2 Sinh(const Float2& v)
		{
			return{ Sinh(v.x), Sinh(v.y) };
		}

		Float3 Sinh(const Float3& v)
		{
			return{ Sinh(v.x), Sinh(v.y), Sinh(v.z) };
		}

		Float4 Sinh(const Float4& v)
		{
			return{ Sinh(v.x), Sinh(v.y), Sinh(v.z), Sinh(v.w) };
		}

		Vec2 Sinh(const Vec2& v)
		{
			return{ Sinh(v.x), Sinh(v.y) };
		}

		Vec3 Sinh(const Vec3& v)
		{
			return{ Sinh(v.x), Sinh(v.y), Sinh(v.z) };
		}

		Vec4 Sinh(const Vec4& v)
		{
			return{ Sinh(v.x), Sinh(v.y), Sinh(v.z), Sinh(v.w) };
		}

		//////////////////////////////////////////////////
		//
		//	Tan
		//
		//////////////////////////////////////////////////

		Vec2 Tan(const Point& v)
		{
			return{ Tan(v.x), Tan(v.y) };
		}

		Float2 Tan(const Float2& v)
		{
			return{ Tan(v.x), Tan(v.y) };
		}

		Float3 Tan(const Float3& v)
		{
			return{ Tan(v.x), Tan(v.y), Tan(v.z) };
		}

		Float4 Tan(const Float4& v)
		{
			return{ Tan(v.x), Tan(v.y), Tan(v.z), Tan(v.w) };
		}

		Vec2 Tan(const Vec2& v)
		{
			return{ Tan(v.x), Tan(v.y) };
		}

		Vec3 Tan(const Vec3& v)
		{
			return{ Tan(v.x), Tan(v.y), Tan(v.z) };
		}

		Vec4 Tan(const Vec4& v)
		{
			return{ Tan(v.x), Tan(v.y), Tan(v.z), Tan(v.w) };
		}

		//////////////////////////////////////////////////
		//
		//	Tanh
		//
		//////////////////////////////////////////////////

		Vec2 Tanh(const Point& v)
		{
			return{ Tanh(v.x), Tanh(v.y) };
		}

		Float2 Tanh(const Float2& v)
		{
			return{ Tanh(v.x), Tanh(v.y) };
		}

		Float3 Tanh(const Float3& v)
		{
			return{ Tanh(v.x), Tanh(v.y), Tanh(v.z) };
		}

		Float4 Tanh(const Float4& v)
		{
			return{ Tanh(v.x), Tanh(v.y), Tanh(v.z), Tanh(v.w) };
		}

		Vec2 Tanh(const Vec2& v)
		{
			return{ Tanh(v.x), Tanh(v.y) };
		}

		Vec3 Tanh(const Vec3& v)
		{
			return{ Tanh(v.x), Tanh(v.y), Tanh(v.z) };
		}

		Vec4 Tanh(const Vec4& v)
		{
			return{ Tanh(v.x), Tanh(v.y), Tanh(v.z), Tanh(v.w) };
		}
	}
}
