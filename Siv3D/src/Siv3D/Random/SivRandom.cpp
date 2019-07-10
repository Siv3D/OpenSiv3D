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

# include <Siv3D/Random.hpp>
# include <Siv3D/RandomPoint.hpp>
# include <Siv3D/RandomVec2.hpp>
# include <Siv3D/RandomVec3.hpp>
# include <Siv3D/RandomVec4.hpp>
# include <Siv3D/RandomColor.hpp>
# include <Siv3D/Rectangle.hpp>
# include <Siv3D/Circle.hpp>
# include <Siv3D/Triangle.hpp>

namespace s3d
{
	double Random()
	{
		return GetDefaultRNG().generateReal();
	}

	template <>
	char32 Random<char32>(const char32& min, const char32& max)
	{
		return static_cast<char32>(UniformDistribution<uint32>(min, max)(GetDefaultRNG()));
	}

	template <>
	Duration Random<Duration>(const Duration& min, const Duration& max)
	{
		return Duration(Random(min.count(), max.count()));
	}

	bool RandomBool(const double p)
	{
		return GetDefaultRNG().generateReal() < p;
	}

	uint8 RandomUint8()
	{
		return static_cast<uint8>(UniformDistribution<uint16>(Smallest<uint8>, Largest<uint8>)(GetDefaultRNG()));
	}

	uint16 RandomUint16()
	{
		return UniformDistribution<uint16>(Smallest<uint16>, Largest<uint16>)(GetDefaultRNG());
	}

	uint32 RandomUint32()
	{
		return UniformDistribution<uint32>(Smallest<uint32>, Largest<uint32>)(GetDefaultRNG());
	}

	uint64 RandomUint64()
	{
		return GetDefaultRNG()();
	}

	int8 RandomInt8()
	{
		return static_cast<int8>(UniformDistribution<int16>(Smallest<int8>, Largest<int8>)(GetDefaultRNG()));
	}

	int16 RandomInt16()
	{
		return UniformDistribution<int16>(Smallest<int16>, Largest<int16>)(GetDefaultRNG());
	}

	int32 RandomInt32()
	{
		return UniformDistribution<int32>(Smallest<int32>, Largest<int32>)(GetDefaultRNG());
	}

	int64 RandomInt64()
	{
		return UniformDistribution<int64>(Smallest<int64>, Largest<int64>)(GetDefaultRNG());
	}

	Point RandomPoint(const std::pair<int32, int32>& xMinMax, const std::pair<int32, int32>& yMinMax)
	{
		Point p;
		p.x = Random(xMinMax.first, xMinMax.second);
		p.y = Random(yMinMax.first, yMinMax.second);
		return p;
	}

	Point RandomPoint(const Rect& rect)
	{
		Point p;
		p.x = Random(rect.x, rect.x + rect.w - 1);
		p.y = Random(rect.y, rect.y + rect.h - 1);
		return p;
	}

	Point RandomPoint(const int32 xMax, const int32 yMax)
	{
		return RandomPoint({ 0, xMax }, { 0, yMax });
	}

	Vec2 RandomVec2()
	{
		const double theta = Random(Math::TwoPi);
		return{ std::cos(theta), std::sin(theta) };
	}

	Vec2 RandomVec2(const double length)
	{
		return RandomVec2()* length;
	}

	Vec2 RandomVec2(const double x, const std::pair<double, double>& yMinMax)
	{
		return{ x, Random(yMinMax.first, yMinMax.second) };
	}

	Vec2 RandomVec2(const std::pair<double, double>& xMinMax, const double y)
	{
		return{ Random(xMinMax.first, xMinMax.second), y };
	}

	Vec2 RandomVec2(const std::pair<double, double>& xMinMax, const std::pair<double, double>& yMinMax)
	{
		Vec2 v;
		v.x = Random(xMinMax.first, xMinMax.second);
		v.y = Random(yMinMax.first, yMinMax.second);
		return v;
	}

	Vec2 RandomVec2(const double xMax, const double yMax)
	{
		return RandomVec2({ 0.0, xMax }, { 0.0, yMax });
	}

	Vec2 RandomVec2(const Circle& circle)
	{
		const double r = std::sqrt(Random()) * circle.r;
		const double theta = Random(Math::TwoPi);
		return circle.center.movedBy(std::cos(theta) * r, std::sin(theta) * r);
	}

	Vec2 RandomVec2(const RectF& rect)
	{
		Vec2 p;
		p.x = Random(rect.x, rect.x + rect.w);
		p.y = Random(rect.y, rect.y + rect.h);
		return p;
	}

	Vec2 RandomVec2(const Triangle & triangle)
	{
		const Vec2 v0 = triangle.p1 - triangle.p0;
		const Vec2 v1 = triangle.p2 - triangle.p0;

		double u = Random();
		double v = Random();

		if (u + v > 1.0)
		{
			u = 1.0 - u;
			v = 1.0 - v;
		}

		return triangle.p0 + u * v0 + v * v1;
	}

	Vec3 RandomVec3onUnitSphere()
	{
		const double theta = Random(Math::Pi);
		const double phi = Random(Math::TwoPi);
		const double s = std::sin(theta);
		return{ s * std::cos(phi), s * std::sin(phi), std::cos(theta) };
	}

	Vec3 RandomVec3insideUnitSphere()
	{
		for (;;)
		{
			Vec3 v;
			v.x = 2.0 * Random() - 1.0;
			v.y = 2.0 * Random() - 1.0;
			v.z = 2.0 * Random() - 1.0;

			if (v.lengthSq() < 1.0)
			{
				return v;
			}
		}
	}

	Vec3 RandomVec3()
	{
		return RandomVec3onUnitSphere();
	}

	Vec3 RandomVec3(const double length)
	{
		return RandomVec3()* length;
	}

	Vec3 RandomVec3(
		const double x,
		const double y,
		const std::pair<double, double>& zMinMax)
	{
		Vec3 v;
		v.x = x;
		v.y = y;
		v.z = Random(zMinMax.first, zMinMax.second);
		return v;
	}

	Vec3 RandomVec3(
		const double x,
		const std::pair<double, double>& yMinMax,
		const double z)
	{
		Vec3 v;
		v.x = x;
		v.y = Random(yMinMax.first, yMinMax.second);
		v.z = z;
		return v;
	}

	Vec3 RandomVec3(
		const std::pair<double, double>& xMinMax,
		const double y,
		const double z)
	{
		Vec3 v;
		v.x = Random(xMinMax.first, xMinMax.second);
		v.y = y;
		v.z = z;
		return v;
	}

	Vec3 RandomVec3(
		const double x,
		const std::pair<double, double>& yMinMax,
		const std::pair<double, double>& zMinMax)
	{
		Vec3 v;
		v.x = x;
		v.y = Random(yMinMax.first, yMinMax.second);
		v.z = Random(zMinMax.first, zMinMax.second);
		return v;
	}

	Vec3 RandomVec3(
		const std::pair<double, double>& xMinMax,
		const double y,
		const std::pair<double, double>& zMinMax)
	{
		Vec3 v;
		v.x = Random(xMinMax.first, xMinMax.second);
		v.y = y;
		v.z = Random(zMinMax.first, zMinMax.second);
		return v;
	}

	Vec3 RandomVec3(
		const std::pair<double, double>& xMinMax,
		const std::pair<double, double>& yMinMax,
		const double z)
	{
		Vec3 v;
		v.x = Random(xMinMax.first, xMinMax.second);
		v.y = Random(yMinMax.first, yMinMax.second);
		v.z = z;
		return v;
	}

	Vec3 RandomVec3(
		const std::pair<double, double>& xMinMax,
		const std::pair<double, double>& yMinMax,
		const std::pair<double, double>& zMinMax)
	{
		Vec3 v;
		v.x = Random(xMinMax.first, xMinMax.second);
		v.y = Random(yMinMax.first, yMinMax.second);
		v.z = Random(zMinMax.first, zMinMax.second);
		return v;
	}

	Vec3 RandomVec3(const double xMax, const double yMax, const double zMax)
	{
		return RandomVec3({ 0.0, xMax }, { 0.0, yMax }, { 0.0, zMax });
	}

	Vec4 RandomVec4(
		const std::pair<double, double>& xMinMax,
		const std::pair<double, double>& yMinMax,
		const std::pair<double, double>& zMinMax,
		const std::pair<double, double>& wMinMax)
	{
		Vec4 v;
		v.x = Random(xMinMax.first, xMinMax.second);
		v.y = Random(yMinMax.first, yMinMax.second);
		v.z = Random(zMinMax.first, zMinMax.second);
		v.w = Random(wMinMax.first, wMinMax.second);
		return v;
	}

	Vec4 RandomVec4(const double xMax, const double yMax, const double zMax, const double wMax)
	{
		return RandomVec4({ 0.0, xMax }, { 0.0, yMax }, { 0.0, zMax }, { 0.0, wMax });
	}

	Color RandomColor()
	{
		return HueToColor(Random(360.0));
	}

	Color RandomColor(
		const std::pair<uint32, uint32>& rMinMax,
		const std::pair<uint32, uint32>& gMinMax,
		const std::pair<uint32, uint32>& bMinMax)
	{
		Color c;
		c.r = Random(rMinMax.first, rMinMax.second);
		c.g = Random(gMinMax.first, gMinMax.second);
		c.b = Random(bMinMax.first, bMinMax.second);
		c.a = 255;
		return c;
	}

	ColorF RandomColorF()
	{
		return HueToColorF(Random(360.0));
	}

	ColorF RandomColorF(
		const std::pair<double, double>& rMinMax,
		const std::pair<double, double>& gMinMax,
		const std::pair<double, double>& bMinMax)
	{
		ColorF c;
		c.r = Random(rMinMax.first, rMinMax.second);
		c.g = Random(gMinMax.first, gMinMax.second);
		c.b = Random(bMinMax.first, bMinMax.second);
		c.a = 255;
		return c;
	}

	HSV RandomHSV()
	{
		return{ Random(360.0), 1.0, 1.0 };
	}

	HSV RandomHSV(
		const std::pair<double, double>& hMinMax,
		const std::pair<double, double>& sMinMax,
		const std::pair<double, double>& vMinMax)
	{
		HSV hsv;
		hsv.h = Random(hMinMax.first, hMinMax.second);
		hsv.s = Random(sMinMax.first, sMinMax.second);
		hsv.v = Random(vMinMax.first, vMinMax.second);
		return hsv;
	}
}
