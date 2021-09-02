//
//  File:       Splines.cpp
//
//  Function:   Various cubic spline utilities
//
//  Copyright:  Andrew Willmott 2018
//

#include <cfloat>
#include "Splines.h"
#include <Siv3D/Utility.hpp>
#include <Siv3D/MathConstants.hpp>
using s3d::Min;
using s3d::Max;
using s3d::Clamp;

using namespace SplineLib;

namespace
{
	// Mini VL
	inline double sqr(double x) { return x * x; }
	inline double lerp(double a, double b, double t) { return (1.0 - t) * a + t * b; }

	inline double dot(Vec2 a, Vec2 b) { return a.x * b.x + a.y * b.y; }
	inline double len(Vec2 v) { return std::sqrt(v.x * v.x + v.y * v.y); }
	inline double sqrlen(Vec2 v) { return v.x * v.x + v.y * v.y; }
	inline Vec2 norm_safe(Vec2 v) { return (1.0 / (len(v) + 1e-8)) * v; }
	inline Vec2 cross(Vec2 v) { return { -v.y, v.x }; }
	inline Vec2 abs(Vec2 v) { return { std::abs(v.x), std::abs(v.y) }; }

	inline double dot(Vec3 a, Vec3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
	inline double len(Vec3 v) { return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z); }
	inline double sqrlen(Vec3 v) { return v.x * v.x + v.y * v.y + v.z * v.z; }
	inline Vec3 norm(Vec3 v) { return (1.0 / len(v)) * v; }
	inline Vec3 norm_safe(Vec3 v) { return (1.0 / (len(v) + 1e-8)) * v; }
	inline Vec3 abs(Vec3 v) { return { std::abs(v.x), std::abs(v.y), std::abs(v.z) }; }
	inline Vec3 cross(Vec3 a, Vec3 b) { return { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x }; }
	inline Vec3 cross_z(Vec3 v) { return { v.y, -v.x, 0.0 }; }

	inline double dot(Vec4 a, Vec4 b) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }

	inline double InvSqrtFast(double x)
	{
		double y = x;
		double xhalf = y * 0.5;
		std::int64_t i = *(std::int64_t*)&y;

		i = 0x5fe6eb50c7b537a9 - (i >> 1);
		y = *(double*)&i;
		y = y * (1.5 - (xhalf * y * y));   // 1st iteration
		//y = y * (1.5 - (xhalf * y * y));   // 2nd iteration, this can be removed
		return y;
	}

	inline bool Larger(const Bounds2f& bb, double t) { Vec2 d = bb.max - bb.min; return d.x > t || d.y > t; }
	inline bool Larger(const Bounds3f& bb, double t) { Vec3 d = bb.max - bb.min; return d.x > t || d.y > t || d.z > t; }
	inline bool Intersects(const Bounds2f& a, const Bounds2f& b)
	{
		return a.max.x >= b.min.x && a.min.x <= b.max.x
			&& a.max.y >= b.min.y && a.min.y <= b.max.y;
	}
	inline bool Intersects(const Bounds3f& a, const Bounds3f& b)
	{
		return a.max.x >= b.min.x && a.min.x <= b.max.x
			&& a.max.y >= b.min.y && a.min.y <= b.max.y
			&& a.max.z >= b.min.z && a.min.z <= b.max.z;
	}
	inline void Add(Bounds2f& a, const Bounds2f& b)
	{
		if (a.min.x > b.min.x) a.min.x = b.min.x; else if (a.max.x < b.max.x) a.max.x = b.max.x;
		if (a.min.y > b.min.y) a.min.y = b.min.y; else if (a.max.y < b.max.y) a.max.y = b.max.y;
	}
	inline void Add(Bounds3f& a, const Bounds3f& b)
	{
		if (a.min.x > b.min.x) a.min.x = b.min.x; else if (a.max.x < b.max.x) a.max.x = b.max.x;
		if (a.min.y > b.min.y) a.min.y = b.min.y; else if (a.max.y < b.max.y) a.max.y = b.max.y;
		if (a.min.z > b.min.z) a.min.z = b.min.z; else if (a.max.z < b.max.z) a.max.z = b.max.z;
	}

	template<class T> inline int size_i(const T& container) { return int(container.size()); }
}

namespace
{
	// Utilities

	inline Vec4 BezierWeights(double t)
		/// Returns Bezier basis weights for 't'
	{
		double s = 1.0 - t;

		double t2 = t * t;
		double t3 = t2 * t;

		double s2 = s * s;
		double s3 = s2 * s;

		return Vec4(s3, 3.0 * s2 * t, 3.0 * s * t2, t3);
	}

	inline Vec4 BezierWeights(const Vec4& t)
		/// Vector version useful for derivatives
	{
		return Vec4
		(
			t.x - 3.0 * t.y + 3.0 * t.z - t.w,
			3.0 * t.y - 6.0 * t.z + 3.0 * t.w,
			3.0 * t.z - 3.0 * t.w,
			t.w
		);
	}

	inline Vec4 CubicCoeffs(const Vec4& b)
		/// Returns cubic coefficients for the given Bezier weights
	{
		return Vec4
		(
			b.x,
			-3.0 * b.x + 3.0 * b.y,
			3.0 * b.x - 6.0 * b.y + 3.0 * b.z,
			-b.x + 3.0 * b.y - 3.0 * b.z + b.w
		);
	}

	inline Vec2 HullBounds(const Vec4& s)
		/// Returns bounds of the convex hull
	{
		Vec2 b01;

		if (s.x <= s.y)
			b01 = Vec2(s.x, s.y);
		else
			b01 = Vec2(s.y, s.x);

		Vec2 b23;

		if (s.z <= s.w)
			b23 = Vec2(s.z, s.w);
		else
			b23 = Vec2(s.w, s.z);

		return Vec2
		(
			Min(b01.x, b23.x),
			Max(b01.y, b23.y)
		);
	}

	Vec2 ExactBounds(const Vec4& spline)
		/// Returns accurate bounds taking extrema into account.
	{
		Vec2 bounds;

		// First take endpoints into account
		if (spline.x <= spline.w)
		{
			bounds.x = spline.x;
			bounds.y = spline.w;
		}
		else
		{
			bounds.x = spline.w;
			bounds.y = spline.x;
		}

		// Now find extrema via standard quadratic equation: c.t' = 0
		Vec4 c = CubicCoeffs(spline);

		double c33 = 3.0 * c.w;
		double cx2 = c.z * c.z - c33 * c.y;

		if (cx2 < 0.0)
			return bounds;  // no roots!

		double invC33 = 1.0 / c33;
		double ct = -c.z * invC33;
		double cx = std::sqrt(cx2) * invC33;

		double t0 = ct + cx;
		double t1 = ct - cx;

		// Must make sure the roots are within the spline interval
		if (t0 > 0.0 && t0 < 1.0)
		{
			double x = c.x + (c.y + (c.z + c.w * t0) * t0) * t0;

			if (bounds.x > x)
				bounds.x = x;
			else if (bounds.y < x)
				bounds.y = x;
		}


		if (t1 > 0.0 && t1 < 1.0)
		{
			double x = c.x + (c.y + (c.z + c.w * t1) * t1) * t1;

			if (bounds.x > x)
				bounds.x = x;
			else if (bounds.y < x)
				bounds.y = x;
		}

		return bounds;
	}

	// This is based on one step of De Casteljau's algorithm
	inline void Split(double t, const Vec4& spline, Vec4* spline0, Vec4* spline1)
	{
		// assumption: seg = (P0, P1, P2, P3)
		double q0 = lerp(spline.x, spline.y, t);
		double q1 = lerp(spline.y, spline.z, t);
		double q2 = lerp(spline.z, spline.w, t);

		double r0 = lerp(q0, q1, t);
		double r1 = lerp(q1, q2, t);

		double s0 = lerp(r0, r1, t);

		double sx = spline.x;    // support aliasing
		double sw = spline.w;

		*spline0 = Vec4(sx, q0, r0, s0);
		*spline1 = Vec4(s0, r1, q2, sw);
	}

	// Optimised for t=0.5
	inline void Split(const Vec4& spline, Vec4* spline0, Vec4* spline1)
	{
		double q0 = (spline.x + spline.y) * 0.5;    // x + y / 2
		double q1 = (spline.y + spline.z) * 0.5;    // y + z / 2
		double q2 = (spline.z + spline.w) * 0.5;    // z + w / 2

		double r0 = (q0 + q1) * 0.5;    // x + 2y + z / 4
		double r1 = (q1 + q2) * 0.5;    // y + 2z + w / 4

		double s0 = (r0 + r1) * 0.5;    // q0 + 2q1 + q2 / 4 = x+y + 2(y+z) + z+w / 8 = x + 3y + 3z + w

		double sx = spline.x;    // support aliasing
		double sw = spline.w;

		*spline0 = Vec4(sx, q0, r0, s0);
		*spline1 = Vec4(s0, r1, q2, sw);
	}

	bool Join(const Vec4& s0, const Vec4& s1, Vec4* sOut)
	{
		if (s0.w != s1.x) // early out
			return false;

		// assumes t = 0.5

		// backwards solve from left
		double x0 = s0.x;
		double y0 = 2 * s0.y - x0;
		double z0 = 4 * s0.z - x0 - 2 * y0;
		double w0 = 8 * s0.w - x0 - 3 * (y0 + z0);

		// backwards solve from right
		double w1 = s1.w;
		double z1 = 2 * s1.z - w1;
		double y1 = 4 * s1.y - w1 - 2 * z1;
		double x1 = 8 * s1.x - w1 - 3 * (y1 + z1);

		double dp = sqr(x0 - x1) + sqr(y0 - y1) + sqr(z0 - z1) + sqr(w0 - w1);

		if (dp < 1e-4) // do left and right reconstructions agree?
		{
			*sOut = Vec4(x0, y0, z1, w1);   // use most stable terms
			return true;
		}

		return false;
	}

	inline Vec2 ArcError2(Vec4 s)
		/// Returns squared displacement from linear (b0_b3) for hull points b1/b2
	{
		double w = s.w - s.x;

		double ty = s.x + w * 1.0 / 3.0 - s.y;
		double tz = s.x + w * 2.0 / 3.0 - s.z;
		double d2 = 1.0 / (sqr(w) + 1.0);

		return Vec2(sqr(ty) * d2, sqr(tz) * d2);
	}

	bool AdvanceAgent(int* indexInOut, double* tInOut, int numSplines)
		/// Update index for t if necessary, but don't run off array
	{
		int& index = *indexInOut;
		double& t = *tInOut;

		while (t < 0.0)
		{
			if (index <= 0)
				return false;

			t += 1.0;
			index--;
		}

		while (t > 1.0)
		{
			if (index >= numSplines - 1)
				return false;

			t -= 1.0;
			index++;
		}

		return true;
	}
}



////////////////////////////////////////////////////////////////////////////////
// 2D
////////////////////////////////////////////////////////////////////////////////


cSpline2 SplineLib::BezierSpline(const Vec2& p0, const Vec2& p1, const Vec2& p2, const Vec2& p3)
{
	return cSpline2
	{
		Vec4(p0.x, p1.x, p2.x, p3.x),
		Vec4(p0.y, p1.y, p2.y, p3.y),
	};
}

cSpline2 SplineLib::HermiteSpline(const Vec2& p0, const Vec2& p1, const Vec2& v0, const Vec2& v1)
{
	Vec2 pb1 = p0 + (1.0 / 3.0) * v0;
	Vec2 pb2 = p1 - (1.0 / 3.0) * v1;

	return BezierSpline(p0, pb1, pb2, p1);
}

cSpline2 SplineLib::CatmullRomSpline(const Vec2& p0, const Vec2& p1, const Vec2& p2, const Vec2& p3)
{
	Vec2 pb1 = p1 + (1.0 / 6.0) * (p2 - p0);
	Vec2 pb2 = p2 - (1.0 / 6.0) * (p3 - p1);

	return BezierSpline(p1, pb1, pb2, p2);
}

namespace
{
	const double kCircleOffset = 4.0 / 3.0 * (s3d::Math::Sqrt2 - 1.0);

	const Vec4 kQuarterB0(1.0, 1.0, kCircleOffset, 0.0);
	const Vec4 kQuarterB1(0.0, kCircleOffset, 1.0, 1.0);
}

cSpline2 SplineLib::QuadrantSpline(const Vec2& p, double r, int quadrant)
{
	SL_ASSERT(quadrant >= 0 && quadrant < 4);
	cSpline2 s;

	switch (quadrant)
	{
	case 0:
		s.xb = kQuarterB0;
		s.yb = kQuarterB1;
		break;
	case 1:
		s.xb = -kQuarterB1;
		s.yb = kQuarterB0;
		break;
	case 2:
		s.xb = -kQuarterB0;
		s.yb = -kQuarterB1;
		break;
	case 3:
		s.xb = kQuarterB1;
		s.yb = -kQuarterB0;
		break;
	}

	s.xb = r * s.xb + Vec4(p.x, p.x, p.x, p.x);
	s.yb = r * s.yb + Vec4(p.y, p.y, p.y, p.y);

	return s;
}

void SplineLib::CircleSplines(const Vec2& p, double r, cSpline2 splines[4])
{
	for (int i = 0; i < 4; i++)
		splines[i] = QuadrantSpline(p, r, i);
}

namespace
{
	inline cSpline2 SplineFromPoints2(const char* p8, size_t stride, int i0, int i1, int i2, int i3, double tension)
	{
		Vec2 p0 = *(Vec2*)(p8 + i0 * stride);
		Vec2 p1 = *(Vec2*)(p8 + i1 * stride);
		Vec2 p2 = *(Vec2*)(p8 + i2 * stride);
		Vec2 p3 = *(Vec2*)(p8 + i3 * stride);

		double s = (1.0 - tension) * (1.0 / 6.0);

		Vec2 pb1 = p1 + s * (p2 - p0);
		Vec2 pb2 = p2 - s * (p3 - p1);

		return BezierSpline(p1, pb1, pb2, p2);
	}
}

int SplineLib::SplinesFromPoints(int numPoints, const Vec2 pi[], [[maybe_unused]] int maxSplines, cSpline2 splines[], double tension, size_t stride)
{
	SL_ASSERT(numPoints >= 0);
	SL_ASSERT(maxSplines >= 0 && maxSplines >= NumSplinesForPoints(numPoints));

	const char* p8 = (const char*)pi;

	switch (numPoints)
	{
	case 0:
		return 0;
	case 1:
		*splines = SplineFromPoints2(p8, stride, 0, 0, 0, 0, tension);
		return 1;
	case 2:
		*splines = SplineFromPoints2(p8, stride, 0, 0, 1, 1, tension);
		return 1;
	}

	*splines++ = SplineFromPoints2(p8, stride, 0, 0, 1, 2, tension);

	for (int i = 0; i < numPoints - 3; i++)
	{
		*splines++ = SplineFromPoints2(p8, stride, 0, 1, 2, 3, tension);
		p8 += stride;
	}

	*splines++ = SplineFromPoints2(p8, stride, 0, 1, 2, 2, tension);

	return numPoints - 1;
}

int SplineLib::SplinesFromBezier(int numPoints, const Vec2 points[], const Vec2 hullPoints[], cSpline2 splines[], bool split)
{
	int numSplines = split ? numPoints / 2 : numPoints - 1;
	int advance = split ? 2 : 1;

	for (int i = 0; i < numSplines; i++)
	{
		splines[i] = BezierSpline(points[0], hullPoints[0], hullPoints[1], points[1]);
		points += advance;
		hullPoints += advance;
	}

	return numSplines;
}

int SplineLib::SplinesFromHermite(int numPoints, const Vec2 points[], const Vec2 tangents[], cSpline2 splines[], bool split)
{
	int numSplines = split ? numPoints / 2 : numPoints - 1;
	int advance = split ? 2 : 1;

	for (int i = 0; i < numSplines; i++)
	{
		splines[i] = HermiteSpline(points[0], points[1], tangents[0], tangents[1]);
		points += advance;
		tangents += advance;
	}

	return numSplines;
}

namespace
{
	inline Vec2 Evaluate(const cSpline2& spline, const Vec4& w)
		/// Evaluate spline with given weights
	{
		return Vec2
		(
			dot(spline.xb, w),
			dot(spline.yb, w)
		);
	}
}

Vec2 SplineLib::Position(const cSpline2& spline, double t)
{
	return Evaluate(spline, BezierWeights(t));
}

Vec2 SplineLib::Velocity(const cSpline2& spline, double t)
{
	Vec4 dt4(0, 1, 2 * t, 3 * t * t);

	return Evaluate(spline, BezierWeights(dt4));
}

Vec2 SplineLib::Acceleration(const cSpline2& spline, double t)
{
	Vec4 ddt4(0, 0, 2, 6 * t);

	return Evaluate(spline, BezierWeights(ddt4));
}

double SplineLib::Curvature(const cSpline2& spline, double t)
{
	Vec2 v = Velocity(spline, t);
	Vec2 a = Acceleration(spline, t);

	double avCrossLen = std::abs(v.x * a.y - v.y * a.x);
	double vLen = len(v);

	if (vLen == 0.0)
		return 1e10;

	return avCrossLen / (vLen * vLen * vLen);
}

void SplineLib::Frame(const cSpline2& spline, double t, Mat2f* frameOut)
{
	Vec2 v = Velocity(spline, t);

	Mat2f& frame = *frameOut;

	frame.rows[0] = norm_safe(v);
	frame.rows[1] = cross(frame.rows[0]);
}

double SplineLib::LengthEstimate(const cSpline2& s, double* error)
{
	// Our convex hull is p0, p1, p2, p3, so p0_p3 is our minimum possible length, and p0_p1 + p1_p2 + p2_p3 our maximum.
	double d03 = sqr(s.xb.x - s.xb.w) + sqr(s.yb.x - s.yb.w);

	double d01 = sqr(s.xb.x - s.xb.y) + sqr(s.yb.x - s.yb.y);
	double d12 = sqr(s.xb.y - s.xb.z) + sqr(s.yb.y - s.yb.z);
	double d23 = sqr(s.xb.z - s.xb.w) + sqr(s.yb.z - s.yb.w);

	double minLength = std::sqrt(d03);
	double maxLength = std::sqrt(d01) + std::sqrt(d12) + std::sqrt(d23);

	minLength *= 0.5;
	maxLength *= 0.5;

	*error = maxLength - minLength;
	return minLength + maxLength;
}

double SplineLib::Length(const cSpline2& s, double maxError)
{
	double error;
	double length = LengthEstimate(s, &error);

	if (error > maxError)
	{
		cSpline2 s0;
		cSpline2 s1;

		Split(s, &s0, &s1);

		return Length(s0, maxError) + Length(s1, maxError);
	}

	return length;
}

double SplineLib::Length(const cSpline2& s, double t0, double t1, double maxError)
{
	SL_ASSERT(t0 >= 0.0 && t0 < 1.0);
	SL_ASSERT(t1 >= 0.0 && t1 <= 1.0);
	SL_ASSERT(t0 <= t1);

	cSpline2 s0, s1;

	if (t0 == 0.0)
	{
		if (t1 == 1.0)
			return Length(s, maxError);

		Split(s, t1, &s0, &s1);
		return Length(s0, maxError);
	}
	else
	{
		Split(s, t0, &s0, &s1);

		if (t1 == 1.0)
			return Length(s1, maxError);

		Split(s1, (t1 - t0) / (1.0 - t0), &s0, &s1);
		return Length(s0, maxError);
	}
}

Bounds2f SplineLib::FastBounds(const cSpline2& spline)
{
	Vec2 bx = HullBounds(spline.xb);
	Vec2 by = HullBounds(spline.yb);

	Bounds2f result = { { bx.x, by.x }, { bx.y, by.y } };
	return result;
}

Bounds2f SplineLib::ExactBounds(const cSpline2& spline)
{
	Vec2 bx = ::ExactBounds(spline.xb);
	Vec2 by = ::ExactBounds(spline.yb);

	Bounds2f result = { { bx.x, by.x }, { bx.y, by.y } };
	return result;
}


void SplineLib::Split(const cSpline2& spline, cSpline2* spline0, cSpline2* spline1)
{
	::Split(spline.xb, &spline0->xb, &spline1->xb);
	::Split(spline.yb, &spline0->yb, &spline1->yb);
}

void SplineLib::Split(const cSpline2& spline, double t, cSpline2* spline0, cSpline2* spline1)
{
	::Split(t, spline.xb, &spline0->xb, &spline1->xb);
	::Split(t, spline.yb, &spline0->yb, &spline1->yb);
}

bool SplineLib::Join(const cSpline2& s0, const cSpline2& s1, cSpline2* splineOut)
{
	return
		::Join(s0.xb, s1.xb, &splineOut->xb)
		&& ::Join(s0.yb, s1.yb, &splineOut->yb);
}

void SplineLib::Split(vector<cSpline2>* splinesIn)
{
	vector<cSpline2> splines;

	for (const cSpline2& s : *splinesIn)
	{
		cSpline2 s0, s1;

		Split(s, &s0, &s1);
		splines.push_back(s0);
		splines.push_back(s1);
	}

	splinesIn->swap(splines);
}

void SplineLib::Split(vector<cSpline2>* splinesIn, int n)
{
	vector<cSpline2> splines;

	for (const cSpline2& s : *splinesIn)
	{
		cSpline2 ss(s);
		cSpline2 s0;

		for (int i = n; i > 1; i--)
		{
			Split(ss, 1.0 / i, &s0, &ss);
			splines.push_back(s0);
		}
		splines.push_back(ss);
	}

	splinesIn->swap(splines);
}

void SplineLib::Join(vector<cSpline2>* splinesIn)
{
	vector<cSpline2> splines;
	const cSpline2* prevS = 0;

	for (const cSpline2& s : *splinesIn)
	{
		if (!prevS)
		{
			prevS = &s;
			continue;
		}

		cSpline2 sj;
		if (Join(*prevS, s, &sj))
			splines.push_back(sj);
		else
		{
			splines.push_back(*prevS);
			splines.push_back(s);
		}

		prevS = 0;
	}

	if (prevS)
		splines.push_back(*prevS);

	splinesIn->swap(splines);
}

namespace
{
	void SubdivideForLength(const cSpline2& s, vector<cSpline2>* splines, double tolerance)
	{
		double error;
		double length = LengthEstimate(s, &error);

		if (error <= tolerance * length)
			splines->push_back(s);
		else
		{
			cSpline2 s1, s2;
			SplineLib::Split(s, &s1, &s2);

			SubdivideForLength(s1, splines, tolerance);
			SubdivideForLength(s2, splines, tolerance);
		}
	}
}

void SplineLib::SubdivideForLength(vector<cSpline2>* splinesIn, double tolerance)
{
	vector<cSpline2> splines;

	for (const cSpline2& s : *splinesIn)
		::SubdivideForLength(s, &splines, tolerance);

	splinesIn->swap(splines);
}

namespace
{
	inline double ArcError(const cSpline2& s, double* tSplit)
	{
		Vec2 ex = ArcError2(s.xb);
		Vec2 ey = ArcError2(s.yb);

		double e0 = ex.x + ey.x;
		double e1 = ex.y + ey.y;
		double es2 = e0 + e1;

		double f = (es2 < 1e-6) ? 0.5 : std::sqrt(e0 / es2);

		*tSplit = (1.0 / 3.0) * (1.0 + f);

		return std::sqrt(es2);
	}

	void SubdivideForT(const cSpline2& s, vector<cSpline2>* splines, double tolerance)
	{
		double splitT;
		double err = ArcError(s, &splitT);

		if (err <= tolerance)
			splines->push_back(s);
		else
		{
			cSpline2 s1, s2;
			SplineLib::Split(s, splitT, &s1, &s2);

			SubdivideForT(s1, splines, tolerance);
			SubdivideForT(s2, splines, tolerance);
		}
	}
}

void SplineLib::SubdivideForT(vector<cSpline2>* splinesIn, double tolerance)
{
	vector<cSpline2> splines;

	for (const cSpline2& s : *splinesIn)
		::SubdivideForT(s, &splines, tolerance);

	splinesIn->swap(splines);
}

namespace
{
	inline double ClosestPoint(const Vec2& p, const Vec2& p0, const Vec2& p1)
	{
		Vec2 w = p1 - p0;
		Vec2 v = p - p0;

		double dvw = dot(v, w);

		if (dvw <= 0.0)
			return 0.0;

		double dww = dot(w, w);

		if (dvw >= dww)
			return 1.0;

		return dvw / dww;
	}

	void FindClosestPointNewtonRaphson(const cSpline2& spline, Vec2 p, double sIn, int maxIterations, double* tOut, double* dOut)
	{
		SL_ASSERT(sIn >= 0.0 && sIn <= 1.0);
		const double maxS = 1.0 - 1e-6;

		//double skLast = sIn;
		double sk = sIn;

		double dk = len(Position(spline, sk) - p);

		constexpr double width = 1e-3;

		double maxJump = 0.5;   // avoid jumping too far, leads to oscillation

		for (int i = 0; i < maxIterations; i++)
		{
			double ss = Clamp(sk, width, 1.0 - width); // so can interpolate points for Newtons method

			double d1 = len(Position(spline, ss - width) - p);
			double d2 = len(Position(spline, ss) - p);
			double d3 = len(Position(spline, ss + width) - p);

			double g1 = (d2 - d1) / width;
			double g2 = (d3 - d2) / width;

			double grad = (d3 - d1) / (2.0 * width);
			double curv = (g2 - g1) / width;

			double sn;   // next candidate

			if (curv > 0.0)    // if d' is heading towards a minima, apply NR for d'
				sn = ss - grad / curv;
			else if (grad != 0.0)
				sn = ss - d2 / grad; // otherwise, apply for D.
			else
				sn = sk;

			sn = Clamp(sn, sk - maxJump, sk + maxJump);   // avoid large steps, often unstable.

			// only update our estimate if the new value is in range and closer.
			if (sn >= 0.0 && sn < maxS)
			{
				double dn = len(Position(spline, sn) - p);

				if (dn < dk)    // only update sk if d actually gets smaller
				{
					sk = sn;
					dk = dn;
				}
			}

			maxJump *= 0.5;    // reduce on a schedule -- helps binary search back towards a jump that is valid.

			//skLast = sk;
		}

		(*tOut) = sk;
		(*dOut) = dk;
	}
}

double SplineLib::FindClosestPoint(const Vec2& p, const cSpline2& spline)
{
	// Approximate s from straight line between the start and end.
	double s = ClosestPoint(p, Position0(spline), Position1(spline));

	// Use this as starting point for Newton-Raphson solve.
	double d;
	FindClosestPointNewtonRaphson(spline, p, s, 8, &s, &d);

	return s;
}

double SplineLib::FindClosestPoint(const Vec2& p, int numSplines, const cSpline2 splines[], int* index)
{
	vector<cSubSpline2> nearbyInfo;

	FindNearbySplines(p, numSplines, splines, &nearbyInfo);
	return FindClosestPoint(p, numSplines, splines, nearbyInfo, index);
}


namespace
{
	void FindMinMaxDistance2s(const Vec2& p, const Bounds2f& bbox, double* minD2, double* maxD2)
	{
		const Vec2& p0 = bbox.min;
		const Vec2& p1 = bbox.max;

		// Find the nearest point to p inside the bbox
		// This can be a bbox vertex, a point on an edge or face, or p itself if it's inside the box
		double minX = Clamp(p.x, p0.x, p1.x);
		double minY = Clamp(p.y, p0.y, p1.y);

		// Find the farthest point from p inside the bbox
		// This is always a bbox vertex.
		Vec2 d0(abs(p - p0));
		Vec2 d1(abs(p - p1));

		double maxX = d0.x > d1.x ? p0.x : p1.x; // select the coordinate we're farthest from
		double maxY = d0.y > d1.y ? p0.y : p1.y;

		// return len2
		*minD2 = sqr(p.x - minX) + sqr(p.y - minY);
		*maxD2 = sqr(p.x - maxX) + sqr(p.y - maxY);
	}

	void FindMinMaxDistance2s(const Vec2& p, const cSpline2& spline, double* minD2, double* maxD2)
	{
		Bounds2f bbox = FastBounds(spline);

		FindMinMaxDistance2s(p, bbox, minD2, maxD2);
	}

	void Split(const cSubSpline2& s, cSubSpline2* s0, cSubSpline2* s1)
	{
		::Split(s.mSpline.xb, &s0->mSpline.xb, &s1->mSpline.xb);
		::Split(s.mSpline.yb, &s0->mSpline.yb, &s1->mSpline.yb);

		s0->mParent = s.mParent;
		s1->mParent = s.mParent;
	}
}

int SplineLib::FindNearbySplines(const Vec2& p, int numSplines, const cSpline2 splines[], vector<cSubSpline2>* results, double* smallestFarOut, int numIter)
{
	vector<cSubSpline2>& nearSplines = *results;

	nearSplines.clear();

	double smallestFar = DBL_MAX;
	double smallestNear = DBL_MAX;

	// Find initial list

	int maxSize = 0;

	for (int i = 0; i < numSplines; i++)
	{
		double near;
		double far;
		FindMinMaxDistance2s(p, splines[i], &near, &far);

		if (near < smallestFar)
		{
			// we at least overlap the current set.
			if (near < smallestNear)
				smallestNear = near;

			if (far < smallestFar)
			{
				// we bring in the 'best' far distance
				smallestFar = far;

				// compact list to reject any segments that now cannot be closest.
				int dj = 0;

				for (int j = 0, nj = size_i(nearSplines); j < nj; j++)
					if (nearSplines[j].mD2 < smallestFar)
					{
						if (dj < j)
							nearSplines[dj] = nearSplines[j];

						dj++;
					}

				nearSplines.resize(dj);
			}

			cSubSpline2 ss = { splines[i], i, near };
			nearSplines.push_back(ss);

			if (maxSize < size_i(nearSplines))
				maxSize = size_i(nearSplines);
		}
	}

	// Subdivide + refine

	int numNearSplines = size_i(nearSplines);

	for (int i = 0; i < numIter; i++)
	{
		int numNearSplines2 = numNearSplines * 2;

		nearSplines.resize(numNearSplines2);

		for (int k = numNearSplines - 1; k >= 0; k--)
			::Split(nearSplines[k], &nearSplines[2 * k], &nearSplines[2 * k + 1]);

		smallestNear = DBL_MAX; // this may actually increase on subdivision.

		for (int k = 0; k < numNearSplines2; k++)
		{
			double near;
			double far;
			FindMinMaxDistance2s(p, nearSplines[k].mSpline, &near, &far);

			if (far < smallestFar)
				smallestFar = far;
			if (near < smallestNear)
				smallestNear = near;

			nearSplines[k].mD2 = near;
		}

		int di = 0;
		for (int k = 0; k < numNearSplines2; k++)
			if (nearSplines[k].mD2 < smallestFar)
			{
				if (di < k)
					nearSplines[di] = nearSplines[k];

				di++;
			}

		nearSplines.resize(di);
		numNearSplines = di;
	}

	if (smallestFarOut)
		*smallestFarOut = smallestFar;

	return numNearSplines;
}

double SplineLib::FindClosestPoint(const Vec2& p, [[maybe_unused]] int numSplines, const cSpline2 splines[], const vector<cSubSpline2>& nearbySplines, int* index)
{
	int prevParent = -1;
	double minD = DBL_MAX;
	double minT = 0.0;

	*index = -1;

	for (const cSubSpline2& subSpline : nearbySplines)
	{
		if (subSpline.mParent != prevParent)
		{
			SL_ASSERT(subSpline.mParent >= 0 && subSpline.mParent < numSplines);

			const cSpline2& spline = splines[subSpline.mParent];

			double t = ClosestPoint(p, Position0(spline), Position1(spline));
			double d;

			FindClosestPointNewtonRaphson(spline, p, t, 8, &t, &d);

			if (minD > d)
			{
				minD = d;
				*index = subSpline.mParent;
				minT = t;
			}
		}
	}

	return minT;
}

namespace
{
	struct cSubSplineT2
	{
		cSpline2 mSpline;
		double   mT0;
		double   mT1;
	};

	inline void Split(const cSubSplineT2& s, cSubSplineT2* s0, cSubSplineT2* s1)
	{
		::Split(s.mSpline.xb, &s0->mSpline.xb, &s1->mSpline.xb);
		::Split(s.mSpline.yb, &s0->mSpline.yb, &s1->mSpline.yb);

		double midT = 0.5 * (s.mT0 + s.mT1);

		s0->mT0 = s.mT0;
		s0->mT1 = midT;

		s1->mT0 = midT;
		s1->mT1 = s.mT1;
	}

	int FindSubSplineIntersections
	(
		const cSubSplineT2& spline0,
		const cSubSplineT2& spline1,
		int   dest,
		int   maxDest,
		double results[][2],
		double tolerance
	)
	{
		SL_ASSERT(dest < maxDest);

		Bounds2f bbox0 = SplineLib::ExactBounds(spline0.mSpline);
		Bounds2f bbox1 = SplineLib::ExactBounds(spline1.mSpline);

		if (!Intersects(bbox0, bbox1))
			return dest;

		if (Larger(bbox0, tolerance))
		{
			cSubSplineT2 spline00, spline01;
			Split(spline0, &spline00, &spline01);

			if (Larger(bbox1, tolerance))
			{
				cSubSplineT2 spline10, spline11;
				Split(spline1, &spline10, &spline11);

				dest = FindSubSplineIntersections(spline00, spline10, dest, maxDest, results, tolerance);
				if (dest < maxDest)
					dest = FindSubSplineIntersections(spline01, spline10, dest, maxDest, results, tolerance);
				if (dest < maxDest)
					dest = FindSubSplineIntersections(spline00, spline11, dest, maxDest, results, tolerance);
				if (dest < maxDest)
					dest = FindSubSplineIntersections(spline01, spline11, dest, maxDest, results, tolerance);
			}
			else
			{
				dest = FindSubSplineIntersections(spline00, spline1, dest, maxDest, results, tolerance);
				if (dest < maxDest)
					dest = FindSubSplineIntersections(spline01, spline1, dest, maxDest, results, tolerance);
			}

			return dest;
		}

		if (Larger(bbox1, tolerance))
		{
			cSubSplineT2 spline10, spline11;
			Split(spline1, &spline10, &spline11);

			dest = FindSubSplineIntersections(spline0, spline10, dest, maxDest, results, tolerance);
			if (dest < maxDest)
				dest = FindSubSplineIntersections(spline0, spline11, dest, maxDest, results, tolerance);

			return dest;
		}

		double t0 = 0.5 * (spline0.mT0 + spline0.mT1);
		double t1 = 0.5 * (spline1.mT0 + spline1.mT1);

		// debounce
		for (int i = 0; i < dest; i++)
			if (std::abs(results[i][0] - t0) < 1e-2
				&& std::abs(results[i][1] - t1) < 1e-2)
			{
				return dest;
			}

		results[dest][0] = t0;
		results[dest][1] = t1;
		return dest + 1;
	}
}

int SplineLib::FindSplineIntersections(const cSpline2& spline0, const cSpline2& spline1, int maxResults, double results[][2], double tolerance)
{
	if (maxResults <= 0)
		return 0;

	cSubSplineT2 subSpline0 = { spline0, 0.0, 1.0 };
	cSubSplineT2 subSpline1 = { spline1, 0.0, 1.0 };

	return FindSubSplineIntersections(subSpline0, subSpline1, 0, maxResults, results, tolerance);
}

namespace
{
	int FindSplineIntersections
	(
		int   is0, int numSplines0, const cSpline2 splines0[],
		int   is1, int numSplines1, const cSpline2 splines1[],
		int   maxResults,
		int   resultsI[][2],
		double resultsT[][2],
		double tolerance
	)
	{
		if (maxResults <= 0 || numSplines0 == 0 || numSplines1 == 0)
			return 0;

		int count = 0;

		// once the lists are small enough, brute-force the remainder, as recalculating the bounds is not free
		if (numSplines0 >= 4 || numSplines1 >= 4)
		{
			// Terminate if the lists don't overlap
			Bounds2f b0 = FastBounds(splines0[0]);
			Bounds2f b1 = FastBounds(splines1[0]);

			for (int i = 1; i < numSplines0; i++)
				Add(b0, FastBounds(splines0[i]));
			for (int i = 1; i < numSplines1; i++)
				Add(b1, FastBounds(splines1[i]));

			if (!Intersects(b0, b1))
				return 0;

			// Divide each spline list into two, and recurse
			int n00 = numSplines0 / 2;
			int n01 = numSplines0 - n00;
			int n10 = numSplines1 / 2;
			int n11 = numSplines1 - n10;

			count += FindSplineIntersections(is0 + 0, n00, splines0 + 0, is1 + 0, n10, splines1 + 0, maxResults - count, resultsI + count, resultsT + count, tolerance);
			count += FindSplineIntersections(is0 + 0, n00, splines0 + 0, is1 + n10, n11, splines1 + n10, maxResults - count, resultsI + count, resultsT + count, tolerance);
			count += FindSplineIntersections(is0 + n00, n01, splines0 + n00, is1 + 0, n10, splines1 + 0, maxResults - count, resultsI + count, resultsT + count, tolerance);
			count += FindSplineIntersections(is0 + n00, n01, splines0 + n00, is1 + n10, n11, splines1 + n10, maxResults - count, resultsI + count, resultsT + count, tolerance);

			return count;
		}

		cSubSplineT2 st0, st1;

		st0.mT0 = 0.0;
		st0.mT1 = 1.0;
		st1.mT0 = 0.0;
		st1.mT1 = 1.0;

		for (int i0 = 0; i0 < numSplines0; i0++)
			for (int i1 = 0; i1 < numSplines1; i1++)
			{
				st0.mSpline = splines0[i0];
				st1.mSpline = splines1[i1];

				int numIntersections = FindSubSplineIntersections(st0, st1, 0, maxResults - count, resultsT + count, tolerance);

				for (int k = 0; k < numIntersections; k++)
				{
					resultsI[k + count][0] = is0 + i0;
					resultsI[k + count][1] = is1 + i1;
				}

				count += numIntersections;
				SL_ASSERT(count <= maxResults);

				if (count == maxResults)
					return count;
			}

		return count;
	}
}

int SplineLib::FindSplineIntersections
(
	int   numSplines0, const cSpline2 splines0[],
	int   numSplines1, const cSpline2 splines1[],
	int   maxResults,
	int   resultsI[][2],
	double resultsT[][2],
	double tolerance
)
{
	return ::FindSplineIntersections(0, numSplines0, splines0, 0, numSplines1, splines1, maxResults, resultsI, resultsT, tolerance);
}

int SplineLib::FindSplineIntersections
(
	int   numSplines, const cSpline2 splines[],
	int   maxResults,
	int   resultsI[][2],
	double resultsT[][2],
	double tolerance
)
// Find self-intersections
{
	if (maxResults <= 0 || numSplines == 0)
		return 0;

	int count = 0;

	if (numSplines >= 8)
	{
		const int n0 = numSplines / 2;
		const int n1 = numSplines - n0;

		// Find intersections between the two halves
		count += ::FindSplineIntersections(0, n0, splines, 0, n1, splines + n0, maxResults - count, resultsI + count, resultsT + count, tolerance);

		for (int i = 0; i < count; i++)
		{
			// ignore spurious intersections between endpoint of first and start of second
			if (resultsI[i][1] == 0 && resultsI[i][0] == n0 - 1)
				if (resultsT[i][0] > 0.95f && resultsT[i][1] < 0.05f)
				{
					resultsT[i][0] = resultsT[count - 1][0];
					resultsT[i][1] = resultsT[count - 1][1];
					resultsI[i][0] = resultsI[count - 1][0];
					resultsI[i][1] = resultsI[count - 1][1];

					i--;
					count--;
					continue;
				}

			resultsI[i][1] += n0;           // adjust second half indices
		}

		// Find self-intersections in the first half
		count += FindSplineIntersections(n0, splines + 0, maxResults - count, resultsI + count, resultsT + count, tolerance);

		// Find self-intersections in the second half
		int prevCount = count;
		count += FindSplineIntersections(n1, splines + n0, maxResults - count, resultsI + count, resultsT + count, tolerance);

		for (int i = prevCount; i < count; i++)
		{
			resultsI[i][0] += n0;   // adjust second half indices
			resultsI[i][1] += n0;
		}

		return count;
	}

	cSubSplineT2 st0, st1;

	st0.mT0 = 0.0;
	st0.mT1 = 1.0;
	st1.mT0 = 0.0;
	st1.mT1 = 1.0;

	for (int i0 = 0; i0 < numSplines; i0++)
		for (int i1 = i0 + 1; i1 < numSplines; i1++)
		{
			st0.mSpline = splines[i0];
			st1.mSpline = splines[i1];

			int numIntersections = FindSubSplineIntersections(st0, st1, 0, maxResults, resultsT, tolerance);

			if (i1 == i0 + 1)   // ignore spurious intersections between endpoint of i0 and start of i1
			{
				for (int k = 0; k < numIntersections; k++)
				{
					if (resultsT[k][0] > 0.95f && resultsT[k][1] < 0.05f)
					{
						resultsT[k][0] = resultsT[numIntersections - 1][0];
						resultsT[k][1] = resultsT[numIntersections - 1][1];

						k--;
						numIntersections--;
					}
				}
			}

			for (int k = 0; k < numIntersections; k++)
			{
				resultsI[k][0] = i0;
				resultsI[k][1] = i1;
			}

			count += numIntersections;
			maxResults -= numIntersections;

			if (maxResults <= 0)
				return count;

			resultsT += numIntersections;
			resultsI += numIntersections;
		}

	return count;
}

double SplineLib::AdvanceAgent(const cSpline2& spline, double t, double ds)
{
	Vec2 v = Velocity(spline, t);
	double v2 = sqrlen(v);
	double dt = ds;

	if (v2 > 0.01)
		dt *= InvSqrtFast(v2);
	else
		dt *= 10.0;

	return t + dt;
}

bool SplineLib::AdvanceAgent(int* index, double* t, int numSplines, const cSpline2 splines[], double ds)
{
	*t = AdvanceAgent(splines[*index], *t, ds);

	return ::AdvanceAgent(index, t, numSplines);
}

cSpline2 SplineLib::Reverse(const cSpline2& spline)
{
	return
	{
		Vec4(spline.xb.w, spline.xb.z, spline.xb.y, spline.xb.x),
		Vec4(spline.yb.w, spline.yb.z, spline.yb.y, spline.yb.x)
	};
}

void SplineLib::Reverse(vector<cSpline2>* splines)
{
	int n = int(splines->size());
	int h = n / 2;

	for (int i = 0; i < h; i++)
	{
		cSpline2& s0 = (*splines)[i];
		cSpline2& s1 = (*splines)[n - i - 1];

		cSpline2 sr0 = Reverse(s1);
		cSpline2 sr1 = Reverse(s0);

		s0 = sr0;
		s1 = sr1;
	}

	if (2 * h < n)
		(*splines)[h] = Reverse((*splines)[h]);
}

cSpline2 SplineLib::Offset(const cSpline2& spline, double offset)
{
	double sx0 = spline.xb.y - spline.xb.x;
	double sy0 = spline.yb.y - spline.yb.x;
	double sd0 = InvSqrtFast(sx0 * sx0 + sy0 * sy0) * offset;

	double sx1 = spline.xb.z - spline.xb.x;
	double sy1 = spline.yb.z - spline.yb.x;
	double sd1 = InvSqrtFast(sx1 * sx1 + sy1 * sy1) * offset;

	double sx2 = spline.xb.w - spline.xb.y;
	double sy2 = spline.yb.w - spline.yb.y;
	double sd2 = InvSqrtFast(sx2 * sx2 + sy2 * sy2) * offset;

	double sx3 = spline.xb.w - spline.xb.z;
	double sy3 = spline.yb.w - spline.yb.z;
	double sd3 = InvSqrtFast(sx3 * sx3 + sy3 * sy3) * offset;

	return
	{
		spline.xb + Vec4(sy0 * sd0, sy1 * sd1, sy2 * sd2, sy3 * sd3),
		spline.yb - Vec4(sx0 * sd0, sx1 * sd1, sx2 * sd2, sx3 * sd3)
	};
}

void SplineLib::Offset(vector<cSpline2>* splines, double offset)
{
	for (cSpline2& s : *splines)
		s = Offset(s, offset);
}








////////////////////////////////////////////////////////////////////////////////
// 3D
////////////////////////////////////////////////////////////////////////////////


cSpline3 SplineLib::BezierSpline(const Vec3& p0, const Vec3& p1, const Vec3& p2, const Vec3& p3)
{
	return cSpline3
	{
		Vec4(p0.x, p1.x, p2.x, p3.x),
		Vec4(p0.y, p1.y, p2.y, p3.y),
		Vec4(p0.z, p1.z, p2.z, p3.z)
	};
}

cSpline3 SplineLib::HermiteSpline(const Vec3& p0, const Vec3& p1, const Vec3& v0, const Vec3& v1)
{
	Vec3 pb1 = p0 + (1.0 / 3.0) * v0;
	Vec3 pb2 = p1 - (1.0 / 3.0) * v1;

	return BezierSpline(p0, pb1, pb2, p1);
}

cSpline3 SplineLib::CatmullRomSpline(const Vec3& p0, const Vec3& p1, const Vec3& p2, const Vec3& p3)
{
	Vec3 pb1 = p1 + (1.0 / 6.0) * (p2 - p0);
	Vec3 pb2 = p2 - (1.0 / 6.0) * (p3 - p1);

	return BezierSpline(p1, pb1, pb2, p2);
}

namespace
{
	inline cSpline3 SplineFromPoints3(const char* p8, size_t stride, int i0, int i1, int i2, int i3, double tension)
	{
		Vec3 p0 = *(Vec3*)(p8 + i0 * stride);
		Vec3 p1 = *(Vec3*)(p8 + i1 * stride);
		Vec3 p2 = *(Vec3*)(p8 + i2 * stride);
		Vec3 p3 = *(Vec3*)(p8 + i3 * stride);

		double s = (1.0 - tension) * (1.0 / 6.0);

		Vec3 pb1 = p1 + s * (p2 - p0);
		Vec3 pb2 = p2 - s * (p3 - p1);

		return BezierSpline(p1, pb1, pb2, p2);
	}
}

int SplineLib::SplinesFromPoints(int numPoints, const Vec3 pi[], [[maybe_unused]] int maxSplines, cSpline3 splines[], double tension, size_t stride)
{
	SL_ASSERT(numPoints >= 0);
	SL_ASSERT(maxSplines >= 0 && maxSplines >= NumSplinesForPoints(numPoints));

	const char* p8 = (const char*)pi;

	switch (numPoints)
	{
	case 0:
		return 0;
	case 1:
		*splines = SplineFromPoints3(p8, stride, 0, 0, 0, 0, tension);
		return 1;
	case 2:
		*splines = SplineFromPoints3(p8, stride, 0, 0, 1, 1, tension);
		return 1;
	}

	*splines++ = SplineFromPoints3(p8, stride, 0, 0, 1, 2, tension);

	for (int i = 0; i < numPoints - 3; i++)
	{
		*splines++ = SplineFromPoints3(p8, stride, 0, 1, 2, 3, tension);
		p8 += stride;
	}

	*splines++ = SplineFromPoints3(p8, stride, 0, 1, 2, 2, tension);

	return numPoints - 1;
}

int SplineLib::SplinesFromBezier(int numPoints, const Vec3 points[], const Vec3 hullPoints[], cSpline3 splines[], bool split)
{
	int numSplines = split ? numPoints / 2 : numPoints - 1;
	int advance = split ? 2 : 1;

	for (int i = 0; i < numSplines; i++)
	{
		splines[i] = BezierSpline(points[0], hullPoints[0], hullPoints[1], points[1]);
		points += advance;
		hullPoints += advance;
	}

	return numSplines;
}

int SplineLib::SplinesFromHermite(int numPoints, const Vec3 points[], const Vec3 tangents[], cSpline3 splines[], bool split)
{
	int numSplines = split ? numPoints / 2 : numPoints - 1;
	int advance = split ? 2 : 1;

	for (int i = 0; i < numSplines; i++)
	{
		splines[i] = HermiteSpline(points[0], points[1], tangents[0], tangents[1]);
		points += advance;
		tangents += advance;
	}

	return numSplines;
}

namespace
{
	inline Vec3 Evaluate(const cSpline3& spline, const Vec4& w)
		/// Evaluate spline with given weights
	{
		return Vec3
		(
			dot(spline.xb, w),
			dot(spline.yb, w),
			dot(spline.zb, w)
		);
	}
}

Vec3 SplineLib::Position(const cSpline3& spline, double t)
{
	return Evaluate(spline, BezierWeights(t));
}

Vec3 SplineLib::Velocity(const cSpline3& spline, double t)
{
	Vec4 dt4(0, 1, 2 * t, 3 * t * t);

	return Evaluate(spline, BezierWeights(dt4));
}

Vec3 SplineLib::Acceleration(const cSpline3& spline, double t)
{
	Vec4 ddt4(0, 0, 2, 6 * t);

	return Evaluate(spline, BezierWeights(ddt4));
}

double SplineLib::Curvature(const cSpline3& spline, double t)
{
	Vec3 v = Velocity(spline, t);
	Vec3 a = Acceleration(spline, t);

	double avCrossLen = len(cross(v, a));
	double vLen = len(v);

	if (vLen == 0.0)
		return 1e10;

	return avCrossLen / (vLen * vLen * vLen);
}

void SplineLib::Frame(const cSpline3& spline, double t, Mat3f* frameOut)
{
	Vec3 v = Velocity(spline, t);
	Vec3 a = Acceleration(spline, t);

	Vec3 g = norm_safe(v);             // tangent
	Vec3 b = norm_safe(cross(v, a));
	Vec3 n = cross(g, b);

	Mat3f& frame = *frameOut;

	frame.rows[0] = n;   // x = right
	frame.rows[1] = g;   // y = forward
	frame.rows[2] = b;   // z = up = normal
}

void SplineLib::FrameSmooth(const cSpline3& spline, double t, Mat3f* frameOut)
{
	// Issues:
	//   'b' can flip sign as 'a' moves from one side of the curve to the other
	//   'a' can go to zero on flat sections of the curve. (In which case we should maintain previous values.)
	//   'v' can go to zero at inflection points (ditto).
	// Generally we want to preserve the tangent direction above everything, then the up vector, and last the right vector.
	// E.g., if agent is going into a point and coming back out, we desire that the right vector flips.

	Vec3 v = Velocity(spline, t);
	Vec3 a = Acceleration(spline, t);

	Mat3f& frame = *frameOut;

	Vec3 g;
	if (sqrlen(v) >= 1e-3)
		g = norm(v);
	else
		g = frame.rows[0];   // fall back to keeping existing tangent

	Vec3 ga = cross(g, a);
	Vec3 b;
	if (sqrlen(ga) >= 1e-3)
	{
		b = norm(ga);

		if (dot(b, frame.rows[2]) < 0.0)
			b = -b; // correct b
	}
	else
		b = frame.rows[2];   // fall back to previous up

	Vec3 n = cross(g, b);

	frame.rows[0] = n;   // x = right
	frame.rows[1] = g;   // y = forward
	frame.rows[2] = b;   // z = up = normal
}


void SplineLib::FrameUp(const cSpline3& spline, double t, const Vec3& up, Mat3f* frameOut)
{
	Vec3 v = Velocity(spline, t);

	Vec3 g = norm_safe(v);             // tangent
	Vec3 n = norm_safe(cross(g, up));
	Vec3 b = cross(n, g);

	Mat3f& frame = *frameOut;

	frame.rows[0] = n;   // x = right
	frame.rows[1] = g;   // y = forward
	frame.rows[2] = b;   // z = up = normal
}

void SplineLib::FrameZUp(const cSpline3& spline, double t, Mat3f* frameOut)
{
	Vec3 v = Velocity(spline, t);

	Vec3 g = norm_safe(v);             // tangent
	Vec3 n = norm_safe(cross_z(g));
	Vec3 b = cross(n, g);

	Mat3f& frame = *frameOut;

	frame.rows[0] = n;   // x = right
	frame.rows[1] = g;   // y = forward
	frame.rows[2] = b;   // z = up = normal
}

double SplineLib::LengthEstimate(const cSpline3& s, double* error)
{
	// Our convex hull is p0, p1, p2, p3, so p0_p3 is our minimum possible length, and p0_p1 + p1_p2 + p2_p3 our maximum.
	double d03 = sqr(s.xb.x - s.xb.w) + sqr(s.yb.x - s.yb.w) + sqr(s.zb.x - s.zb.w);

	double d01 = sqr(s.xb.x - s.xb.y) + sqr(s.yb.x - s.yb.y) + sqr(s.zb.x - s.zb.y);
	double d12 = sqr(s.xb.y - s.xb.z) + sqr(s.yb.y - s.yb.z) + sqr(s.zb.y - s.zb.z);
	double d23 = sqr(s.xb.z - s.xb.w) + sqr(s.yb.z - s.yb.w) + sqr(s.zb.z - s.zb.w);

	double minLength = std::sqrt(d03);
	double maxLength = std::sqrt(d01) + std::sqrt(d12) + std::sqrt(d23);

	minLength *= 0.5;
	maxLength *= 0.5;

	*error = maxLength - minLength;
	return minLength + maxLength;
}

double SplineLib::Length(const cSpline3& s, double maxError)
{
	double error;
	double length = LengthEstimate(s, &error);

	if (error > maxError)
	{
		cSpline3 s0;
		cSpline3 s1;

		Split(s, &s0, &s1);

		return Length(s0, maxError) + Length(s1, maxError);
	}

	return length;
}

double SplineLib::Length(const cSpline3& s, double t0, double t1, double maxError)
{
	SL_ASSERT(t0 >= 0.0 && t0 < 1.0);
	SL_ASSERT(t1 >= 0.0 && t1 <= 1.0);
	SL_ASSERT(t0 <= t1);

	cSpline3 s0, s1;

	if (t0 == 0.0)
	{
		if (t1 == 1.0)
			return Length(s, maxError);

		Split(s, t1, &s0, &s1);
		return Length(s0, maxError);
	}
	else
	{
		Split(s, t0, &s0, &s1);

		if (t1 == 1.0)
			return Length(s1, maxError);

		Split(s1, (t1 - t0) / (1.0 - t0), &s0, &s1);
		return Length(s0, maxError);
	}
}

Bounds3f SplineLib::FastBounds(const cSpline3& spline)
{
	Vec2 bx = HullBounds(spline.xb);
	Vec2 by = HullBounds(spline.yb);
	Vec2 bz = HullBounds(spline.zb);

	Bounds3f result = { { bx.x, by.x, bz.x }, { bx.y, by.y, bz.y } };
	return result;
}

Bounds3f SplineLib::ExactBounds(const cSpline3& spline)
{
	Vec2 bx = ::ExactBounds(spline.xb);
	Vec2 by = ::ExactBounds(spline.yb);
	Vec2 bz = ::ExactBounds(spline.zb);

	Bounds3f result = { { bx.x, by.x, bz.x }, { bx.y, by.y, bz.y } };
	return result;
}


void SplineLib::Split(const cSpline3& spline, cSpline3* spline0, cSpline3* spline1)
{
	::Split(spline.xb, &spline0->xb, &spline1->xb);
	::Split(spline.yb, &spline0->yb, &spline1->yb);
	::Split(spline.zb, &spline0->zb, &spline1->zb);
}

void SplineLib::Split(const cSpline3& spline, double t, cSpline3* spline0, cSpline3* spline1)
{
	::Split(t, spline.xb, &spline0->xb, &spline1->xb);
	::Split(t, spline.yb, &spline0->yb, &spline1->yb);
	::Split(t, spline.zb, &spline0->zb, &spline1->zb);
}

bool SplineLib::Join(const cSpline3& s0, const cSpline3& s1, cSpline3* splineOut)
{
	return
		::Join(s0.xb, s1.xb, &splineOut->xb)
		&& ::Join(s0.yb, s1.yb, &splineOut->yb)
		&& ::Join(s0.zb, s1.zb, &splineOut->zb);
}

void SplineLib::Split(vector<cSpline3>* splinesIn)
{
	vector<cSpline3> splines;

	for (const cSpline3& s : *splinesIn)
	{
		cSpline3 s0, s1;

		Split(s, &s0, &s1);
		splines.push_back(s0);
		splines.push_back(s1);
	}

	splinesIn->swap(splines);
}

void SplineLib::Split(vector<cSpline3>* splinesIn, int n)
{
	vector<cSpline3> splines;

	for (const cSpline3& s : *splinesIn)
	{
		cSpline3 ss(s);
		cSpline3 s0;

		for (int i = n; i > 1; i--)
		{
			Split(ss, 1.0 / i, &s0, &ss);
			splines.push_back(s0);
		}
		splines.push_back(ss);
	}

	splinesIn->swap(splines);
}

void SplineLib::Join(vector<cSpline3>* splinesIn)
{
	vector<cSpline3> splines;
	const cSpline3* prevS = 0;

	for (const cSpline3& s : *splinesIn)
	{
		if (!prevS)
		{
			prevS = &s;
			continue;
		}

		cSpline3 sj;
		if (Join(*prevS, s, &sj))
			splines.push_back(sj);
		else
		{
			splines.push_back(*prevS);
			splines.push_back(s);
		}

		prevS = 0;
	}

	if (prevS)
		splines.push_back(*prevS);

	splinesIn->swap(splines);
}

namespace
{
	void SubdivideForLength(const cSpline3& s, vector<cSpline3>* splines, double tolerance)
	{
		double error;
		double length = LengthEstimate(s, &error);

		if (error <= tolerance * length)
			splines->push_back(s);
		else
		{
			cSpline3 s1, s2;
			Split(s, &s1, &s2);

			SubdivideForLength(s1, splines, tolerance);
			SubdivideForLength(s2, splines, tolerance);
		}
	}
}

void SplineLib::SubdivideForLength(vector<cSpline3>* splinesIn, double tolerance)
{
	vector<cSpline3> splines;

	for (const cSpline3& s : *splinesIn)
		::SubdivideForLength(s, &splines, tolerance);

	splinesIn->swap(splines);
}

namespace
{
	double ArcError(const cSpline3& s, double* tSplit)
	{
		Vec2 ex = ArcError2(s.xb);
		Vec2 ey = ArcError2(s.yb);
		Vec2 ez = ArcError2(s.zb);

		double e0 = ex.x + ey.x + ez.x;
		double e1 = ex.y + ey.y + ez.y;
		double es2 = e0 + e1;

		double f = (es2 < 1e-6) ? 0.5 : std::sqrt(e0 / es2);

		*tSplit = (1.0 / 3.0) * (1.0 + f);

		return std::sqrt(es2);
	}

	void SubdivideForT(const cSpline3& s, vector<cSpline3>* splines, double tolerance)
	{
		double splitT;
		double err = ArcError(s, &splitT);

		if (err <= tolerance)
			splines->push_back(s);
		else
		{
			cSpline3 s1, s2;
			Split(s, splitT, &s1, &s2);

			SubdivideForT(s1, splines, tolerance);
			SubdivideForT(s2, splines, tolerance);
		}
	}
}

void SplineLib::SubdivideForT(vector<cSpline3>* splinesIn, double tolerance)
{
	vector<cSpline3> splines;

	for (const cSpline3& s : *splinesIn)
		::SubdivideForT(s, &splines, tolerance);

	splinesIn->swap(splines);
}

namespace
{
	inline double ClosestPoint(const Vec3& p, const Vec3& p0, const Vec3& p1)
	{
		Vec3 w = p1 - p0;
		Vec3 v = p - p0;

		double dvw = dot(v, w);

		if (dvw <= 0.0)
			return 0.0;

		double dww = dot(w, w);

		if (dvw >= dww)
			return 1.0;

		return dvw / dww;
	}

	void FindClosestPointNewtonRaphson(const cSpline3& spline, Vec3 p, double sIn, int maxIterations, double* tOut, double* dOut)
	{
		SL_ASSERT(sIn >= 0.0 && sIn <= 1.0);
		const double maxS = 1.0 - 1e-6;

		//double skLast = sIn;
		double sk = sIn;

		double dk = len(Position(spline, sk) - p);

		constexpr double width = 1e-3;

		double maxJump = 0.5;   // avoid jumping too far, leads to oscillation

		for (int i = 0; i < maxIterations; i++)
		{
			double ss = Clamp(sk, width, 1.0 - width); // so can interpolate points for Newtons method

			double d1 = len(Position(spline, ss - width) - p);
			double d2 = len(Position(spline, ss) - p);
			double d3 = len(Position(spline, ss + width) - p);

			double g1 = (d2 - d1) / width;
			double g2 = (d3 - d2) / width;

			double grad = (d3 - d1) / (2.0 * width);
			double curv = (g2 - g1) / width;

			double sn;   // next candidate

			if (curv > 0.0)    // if d' is heading towards a minima, apply NR for d'
				sn = ss - grad / curv;
			else if (grad != 0.0)
				sn = ss - d2 / grad; // otherwise, apply for D.
			else
				sn = sk;

			sn = Clamp(sn, sk - maxJump, sk + maxJump);   // avoid large steps, often unstable.

			// only update our estimate if the new value is in range and closer.
			if (sn >= 0.0 && sn < maxS)
			{
				double dn = len(Position(spline, sn) - p);

				if (dn < dk)    // only update sk if d actually gets smaller
				{
					sk = sn;
					dk = dn;
				}
			}

			maxJump *= 0.5;    // reduce on a schedule -- helps binary search back towards a jump that is valid.

			//skLast = sk;
		}

		(*tOut) = sk;
		(*dOut) = dk;
	}
}

double SplineLib::FindClosestPoint(const Vec3& p, const cSpline3& spline)
{
	// Approximate s from straight line between the start and end.
	double s = ClosestPoint(p, Position0(spline), Position1(spline));

	// Use this as starting point for Newton-Raphson solve.
	double d;
	FindClosestPointNewtonRaphson(spline, p, s, 8, &s, &d);

	return s;
}

double SplineLib::FindClosestPoint(const Vec3& p, int numSplines, const cSpline3 splines[], int* index)
{
	vector<cSubSpline3> nearbyInfo;

	FindNearbySplines(p, numSplines, splines, &nearbyInfo);
	return FindClosestPoint(p, numSplines, splines, nearbyInfo, index);
}


namespace
{
	void FindMinMaxDistance2s(const Vec3& p, const Bounds3f& bbox, double* minD2, double* maxD2)
	{
		const Vec3& p0 = bbox.min;
		const Vec3& p1 = bbox.max;

		// Find the nearest point to p inside the bbox
		// This can be a bbox vertex, a point on an edge or face, or p itself if it's inside the box
		double minX = Clamp(p.x, p0.x, p1.x);
		double minY = Clamp(p.y, p0.y, p1.y);
		double minZ = Clamp(p.z, p0.z, p1.z);

		// Find the farthest point from p inside the bbox
		// This is always a bbox vertex.
		Vec3 d0(abs(p - p0));
		Vec3 d1(abs(p - p1));

		double maxX = d0.x > d1.x ? p0.x : p1.x; // select the coordinate we're farthest from
		double maxY = d0.y > d1.y ? p0.y : p1.y;
		double maxZ = d0.z > d1.z ? p0.z : p1.z;

		// return len2
		*minD2 = sqr(p.x - minX) + sqr(p.y - minY) + sqr(p.z - minZ);
		*maxD2 = sqr(p.x - maxX) + sqr(p.y - maxY) + sqr(p.z - maxZ);
	}

	void FindMinMaxDistance2s(const Vec3& p, const cSpline3& spline, double* minD2, double* maxD2)
	{
		Bounds3f bbox = FastBounds(spline);

		FindMinMaxDistance2s(p, bbox, minD2, maxD2);
	}

	void Split(const cSubSpline3& s, cSubSpline3* s0, cSubSpline3* s1)
	{
		::Split(s.mSpline.xb, &s0->mSpline.xb, &s1->mSpline.xb);
		::Split(s.mSpline.yb, &s0->mSpline.yb, &s1->mSpline.yb);
		::Split(s.mSpline.zb, &s0->mSpline.zb, &s1->mSpline.zb);

		s0->mParent = s.mParent;
		s1->mParent = s.mParent;
	}
}

int SplineLib::FindNearbySplines(const Vec3& p, int numSplines, const cSpline3 splines[], vector<cSubSpline3>* results, double* smallestFarOut, int numIter)
{
	vector<cSubSpline3>& nearSplines = *results;

	nearSplines.clear();

	double smallestFar = DBL_MAX;
	double smallestNear = DBL_MAX;

	// Find initial list

	int maxSize = 0;

	for (int i = 0; i < numSplines; i++)
	{
		double near;
		double far;
		FindMinMaxDistance2s(p, splines[i], &near, &far);

		if (near < smallestFar)
		{
			// we at least overlap the current set.
			if (near < smallestNear)
				smallestNear = near;

			if (far < smallestFar)
			{
				// we bring in the 'best' far distance
				smallestFar = far;

				// compact list to reject any segments that now cannot be closest.
				int dj = 0;

				for (int j = 0, nj = size_i(nearSplines); j < nj; j++)
					if (nearSplines[j].mD2 < smallestFar)
					{
						if (dj < j)
							nearSplines[dj] = nearSplines[j];

						dj++;
					}

				nearSplines.resize(dj);
			}

			cSubSpline3 ss = { splines[i], i, near };
			nearSplines.push_back(ss);

			if (maxSize < size_i(nearSplines))
				maxSize = size_i(nearSplines);
		}
	}

	// Subdivide + refine

	int numNearSplines = size_i(nearSplines);

	for (int i = 0; i < numIter; i++)
	{
		int numNearSplines2 = numNearSplines * 2;

		nearSplines.resize(numNearSplines2);

		for (int k = numNearSplines - 1; k >= 0; k--)
			::Split(nearSplines[k], &nearSplines[2 * k], &nearSplines[2 * k + 1]);

		smallestNear = DBL_MAX; // this may actually increase on subdivision.

		for (int k = 0; k < numNearSplines2; k++)
		{
			double near;
			double far;
			FindMinMaxDistance2s(p, nearSplines[k].mSpline, &near, &far);

			if (far < smallestFar)
				smallestFar = far;
			if (near < smallestNear)
				smallestNear = near;

			nearSplines[k].mD2 = near;
		}

		int di = 0;
		for (int k = 0; k < numNearSplines2; k++)
			if (nearSplines[k].mD2 < smallestFar)
			{
				if (di < k)
					nearSplines[di] = nearSplines[k];

				di++;
			}

		nearSplines.resize(di);
		numNearSplines = di;
	}

	if (smallestFarOut)
		*smallestFarOut = smallestFar;

	return numNearSplines;
}

double SplineLib::FindClosestPoint(const Vec3& p, [[maybe_unused]] int numSplines, const cSpline3 splines[], const vector<cSubSpline3>& nearbySplines, int* index)
{
	int prevParent = -1;
	double minD = DBL_MAX;
	double minT = 0.0;

	*index = -1;

	for (const cSubSpline3& subSpline : nearbySplines)
	{
		if (subSpline.mParent != prevParent)
		{
			SL_ASSERT(subSpline.mParent >= 0 && subSpline.mParent < numSplines);

			const cSpline3& spline = splines[subSpline.mParent];

			double t = ClosestPoint(p, Position0(spline), Position1(spline));
			double d;

			FindClosestPointNewtonRaphson(spline, p, t, 8, &t, &d);

			if (minD > d)
			{
				minD = d;
				*index = subSpline.mParent;
				minT = t;
			}
		}
	}

	return minT;
}

namespace
{
	struct cSubSplineT3
	{
		cSpline3 mSpline;
		double   mT0;
		double   mT1;
	};

	inline void Split(const cSubSplineT3& s, cSubSplineT3* s0, cSubSplineT3* s1)
	{
		::Split(s.mSpline.xb, &s0->mSpline.xb, &s1->mSpline.xb);
		::Split(s.mSpline.yb, &s0->mSpline.yb, &s1->mSpline.yb);
		::Split(s.mSpline.zb, &s0->mSpline.zb, &s1->mSpline.zb);

		double midT = 0.5 * (s.mT0 + s.mT1);

		s0->mT0 = s.mT0;
		s0->mT1 = midT;

		s1->mT0 = midT;
		s1->mT1 = s.mT1;
	}

	int FindSubSplineIntersections
	(
		const cSubSplineT3& spline0,
		const cSubSplineT3& spline1,
		int   dest,
		int   maxDest,
		double results[][2],
		double tolerance
	)
	{
		SL_ASSERT(dest < maxDest);

		Bounds3f bbox0 = ExactBounds(spline0.mSpline);
		Bounds3f bbox1 = ExactBounds(spline1.mSpline);

		if (!Intersects(bbox0, bbox1))
			return dest;

		if (Larger(bbox0, tolerance))
		{
			cSubSplineT3 spline00, spline01;
			Split(spline0, &spline00, &spline01);

			if (Larger(bbox1, tolerance))
			{
				cSubSplineT3 spline10, spline11;
				Split(spline1, &spline10, &spline11);

				dest = FindSubSplineIntersections(spline00, spline10, dest, maxDest, results, tolerance);
				if (dest < maxDest)
					dest = FindSubSplineIntersections(spline01, spline10, dest, maxDest, results, tolerance);
				if (dest < maxDest)
					dest = FindSubSplineIntersections(spline00, spline11, dest, maxDest, results, tolerance);
				if (dest < maxDest)
					dest = FindSubSplineIntersections(spline01, spline11, dest, maxDest, results, tolerance);
			}
			else
			{
				dest = FindSubSplineIntersections(spline00, spline1, dest, maxDest, results, tolerance);
				if (dest < maxDest)
					dest = FindSubSplineIntersections(spline01, spline1, dest, maxDest, results, tolerance);
			}

			return dest;
		}

		if (Larger(bbox1, tolerance))
		{
			cSubSplineT3 spline10, spline11;
			Split(spline1, &spline10, &spline11);

			dest = FindSubSplineIntersections(spline0, spline10, dest, maxDest, results, tolerance);
			if (dest < maxDest)
				dest = FindSubSplineIntersections(spline0, spline11, dest, maxDest, results, tolerance);

			return dest;
		}

		double t0 = 0.5 * (spline0.mT0 + spline0.mT1);
		double t1 = 0.5 * (spline1.mT0 + spline1.mT1);

		// debounce
		for (int i = 0; i < dest; i++)
			if (std::abs(results[i][0] - t0) < 1e-2
				&& std::abs(results[i][1] - t1) < 1e-2)
			{
				return dest;
			}

		results[dest][0] = t0;
		results[dest][1] = t1;
		return dest + 1;
	}
}

int SplineLib::FindSplineIntersections(const cSpline3& spline0, const cSpline3& spline1, int maxResults, double results[][2], double tolerance)
{
	if (maxResults <= 0)
		return 0;

	cSubSplineT3 subSpline0 = { spline0, 0.0, 1.0 };
	cSubSplineT3 subSpline1 = { spline1, 0.0, 1.0 };

	return FindSubSplineIntersections(subSpline0, subSpline1, 0, maxResults, results, tolerance);
}

namespace
{
	int FindSplineIntersections
	(
		int   is0, int numSplines0, const cSpline3 splines0[],
		int   is1, int numSplines1, const cSpline3 splines1[],
		int   maxResults,
		int   resultsI[][2],
		double resultsT[][2],
		double tolerance
	)
	{
		if (maxResults <= 0 || numSplines0 == 0 || numSplines1 == 0)
			return 0;

		int count = 0;

		// once the lists are small enough, brute-force the remainder, as recalculating the bounds is not free
		if (numSplines0 >= 4 || numSplines1 >= 4)
		{
			// Terminate if the lists don't overlap
			Bounds3f b0 = FastBounds(splines0[0]);
			Bounds3f b1 = FastBounds(splines1[0]);

			for (int i = 1; i < numSplines0; i++)
				Add(b0, FastBounds(splines0[i]));
			for (int i = 1; i < numSplines1; i++)
				Add(b1, FastBounds(splines1[i]));

			if (!Intersects(b0, b1))
				return 0;

			// Divide each spline list into two, and recurse
			int n00 = numSplines0 / 2;
			int n01 = numSplines0 - n00;
			int n10 = numSplines1 / 2;
			int n11 = numSplines1 - n10;

			count += FindSplineIntersections(is0 + 0, n00, splines0 + 0, is1 + 0, n10, splines1 + 0, maxResults - count, resultsI + count, resultsT + count, tolerance);
			count += FindSplineIntersections(is0 + 0, n00, splines0 + 0, is1 + n10, n11, splines1 + n10, maxResults - count, resultsI + count, resultsT + count, tolerance);
			count += FindSplineIntersections(is0 + n00, n01, splines0 + n00, is1 + 0, n10, splines1 + 0, maxResults - count, resultsI + count, resultsT + count, tolerance);
			count += FindSplineIntersections(is0 + n00, n01, splines0 + n00, is1 + n10, n11, splines1 + n10, maxResults - count, resultsI + count, resultsT + count, tolerance);

			return count;
		}

		cSubSplineT3 st0, st1;

		st0.mT0 = 0.0;
		st0.mT1 = 1.0;
		st1.mT0 = 0.0;
		st1.mT1 = 1.0;

		for (int i0 = 0; i0 < numSplines0; i0++)
			for (int i1 = 0; i1 < numSplines1; i1++)
			{
				st0.mSpline = splines0[i0];
				st1.mSpline = splines1[i1];

				int numIntersections = FindSubSplineIntersections(st0, st1, 0, maxResults - count, resultsT + count, tolerance);

				for (int k = 0; k < numIntersections; k++)
				{
					resultsI[k + count][0] = is0 + i0;
					resultsI[k + count][1] = is1 + i1;
				}

				count += numIntersections;
				SL_ASSERT(count <= maxResults);

				if (count == maxResults)
					return count;
			}

		return count;
	}
}

int SplineLib::FindSplineIntersections
(
	int   numSplines0, const cSpline3 splines0[],
	int   numSplines1, const cSpline3 splines1[],
	int   maxResults,
	int   resultsI[][2],
	double resultsT[][2],
	double tolerance
)
{
	return ::FindSplineIntersections(0, numSplines0, splines0, 0, numSplines1, splines1, maxResults, resultsI, resultsT, tolerance);
}

int SplineLib::FindSplineIntersections
(
	int   numSplines, const cSpline3 splines[],
	int   maxResults,
	int   resultsI[][2],
	double resultsT[][2],
	double tolerance
)
// Find self-intersections
{
	if (maxResults <= 0 || numSplines == 0)
		return 0;

	int count = 0;

	if (numSplines >= 8)
	{
		const int n0 = numSplines / 2;
		const int n1 = numSplines - n0;

		// Find intersections between the two halves
		count += ::FindSplineIntersections(0, n0, splines, 0, n1, splines + n0, maxResults - count, resultsI + count, resultsT + count, tolerance);

		for (int i = 0; i < count; i++)
		{
			// ignore spurious intersections between endpoint of first and start of second
			if (resultsI[i][1] == 0 && resultsI[i][0] == n0 - 1)
				if (resultsT[i][0] > 0.95f && resultsT[i][1] < 0.05f)
				{
					resultsT[i][0] = resultsT[count - 1][0];
					resultsT[i][1] = resultsT[count - 1][1];
					resultsI[i][0] = resultsI[count - 1][0];
					resultsI[i][1] = resultsI[count - 1][1];

					i--;
					count--;
					continue;
				}

			resultsI[i][1] += n0;           // adjust second half indices
		}

		// Find self-intersections in the first half
		count += FindSplineIntersections(n0, splines + 0, maxResults - count, resultsI + count, resultsT + count, tolerance);

		// Find self-intersections in the second half
		int prevCount = count;
		count += FindSplineIntersections(n1, splines + n0, maxResults - count, resultsI + count, resultsT + count, tolerance);

		for (int i = prevCount; i < count; i++)
		{
			resultsI[i][0] += n0;   // adjust second half indices
			resultsI[i][1] += n0;
		}

		return count;
	}

	cSubSplineT3 st0, st1;

	st0.mT0 = 0.0;
	st0.mT1 = 1.0;
	st1.mT0 = 0.0;
	st1.mT1 = 1.0;

	for (int i0 = 0; i0 < numSplines; i0++)
		for (int i1 = i0 + 1; i1 < numSplines; i1++)
		{
			st0.mSpline = splines[i0];
			st1.mSpline = splines[i1];

			int numIntersections = FindSubSplineIntersections(st0, st1, 0, maxResults, resultsT, tolerance);

			if (i1 == i0 + 1)   // ignore spurious intersections between endpoint of i0 and start of i1
			{
				for (int k = 0; k < numIntersections; k++)
				{
					if (resultsT[k][0] > 0.95f && resultsT[k][1] < 0.05f)
					{
						resultsT[k][0] = resultsT[numIntersections - 1][0];
						resultsT[k][1] = resultsT[numIntersections - 1][1];

						k--;
						numIntersections--;
					}
				}
			}

			for (int k = 0; k < numIntersections; k++)
			{
				resultsI[k][0] = i0;
				resultsI[k][1] = i1;
			}

			count += numIntersections;
			maxResults -= numIntersections;

			if (maxResults <= 0)
				return count;

			resultsT += numIntersections;
			resultsI += numIntersections;
		}

	return count;
}

double SplineLib::AdvanceAgent(const cSpline3& spline, double t, double ds)
{
	Vec3 v = Velocity(spline, t);
	double v2 = sqrlen(v);
	double dt = ds;

	if (v2 > 0.01)
		dt *= InvSqrtFast(v2);
	else
		dt *= 10.0;

	return t + dt;
}

bool SplineLib::AdvanceAgent(int* index, double* t, int numSplines, const cSpline3 splines[], double ds)
{
	*t = AdvanceAgent(splines[*index], *t, ds);

	return ::AdvanceAgent(index, t, numSplines);
}

cSpline3 SplineLib::Reverse(const cSpline3& spline)
{
	return
	{
		Vec4(spline.xb.w, spline.xb.z, spline.xb.y, spline.xb.x),
		Vec4(spline.yb.w, spline.yb.z, spline.yb.y, spline.yb.x),
		Vec4(spline.zb.w, spline.zb.z, spline.zb.y, spline.zb.x)
	};
}

void SplineLib::Reverse(vector<cSpline3>* splines)
{
	int n = int(splines->size());
	int h = n / 2;

	for (int i = 0; i < h; i++)
	{
		cSpline3& s0 = (*splines)[i];
		cSpline3& s1 = (*splines)[n - i - 1];

		cSpline3 sr0 = Reverse(s1);
		cSpline3 sr1 = Reverse(s0);

		s0 = sr0;
		s1 = sr1;
	}

	if (2 * h < n)
		(*splines)[h] = Reverse((*splines)[h]);
}

cSpline3 SplineLib::Offset(const cSpline3& spline, double offset)
{
	double sx0 = spline.xb.y - spline.xb.x;
	double sy0 = spline.yb.y - spline.yb.x;
	double sd0 = InvSqrtFast(sx0 * sx0 + sy0 * sy0) * offset;

	double sx1 = spline.xb.z - spline.xb.x;
	double sy1 = spline.yb.z - spline.yb.x;
	double sd1 = InvSqrtFast(sx1 * sx1 + sy1 * sy1) * offset;

	double sx2 = spline.xb.w - spline.xb.y;
	double sy2 = spline.yb.w - spline.yb.y;
	double sd2 = InvSqrtFast(sx2 * sx2 + sy2 * sy2) * offset;

	double sx3 = spline.xb.w - spline.xb.z;
	double sy3 = spline.yb.w - spline.yb.z;
	double sd3 = InvSqrtFast(sx3 * sx3 + sy3 * sy3) * offset;

	return
	{
		spline.xb + Vec4(sy0 * sd0, sy1 * sd1, sy2 * sd2, sy3 * sd3),
		spline.yb - Vec4(sx0 * sd0, sx1 * sd1, sx2 * sd2, sx3 * sd3),
		spline.zb
	};
}

void SplineLib::Offset(vector<cSpline3>* splines, double offset)
{
	for (cSpline3& s : *splines)
		s = Offset(s, offset);
}
