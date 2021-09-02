//
//  File:       Splines.h
//
//  Function:   Various cubic spline utilities
//
//  Copyright:  Andrew Willmott 2018
//

#ifndef SPLINES_H
#define SPLINES_H

# include <Siv3D/PointVector.hpp>
# include <Siv3D/Spline2D.hpp>
using s3d::Vec2;
using s3d::Vec3;
using s3d::Vec4;

#ifndef SL_ASSERT
	#define SL_ASSERT(X)
#endif

namespace SplineLib
{
	// Types
	struct Mat2f { Vec2 rows[2]; };
	struct Mat3f { Vec3 rows[3]; };
	struct Bounds2f { Vec2 min; Vec2 max; };
	struct Bounds3f { Vec3 min; Vec3 max; };

	using std::vector;


	// 2D
	using cSpline2 = s3d::Spline2D::CSpline2;

	// Spline creation
	cSpline2 BezierSpline(const Vec2& p0, const Vec2& p1, const Vec2& p2, const Vec2& p3);  ///< Return Bezier spline from p0 to p3 with guide points p1, p2
	cSpline2 HermiteSpline(const Vec2& p0, const Vec2& p1, const Vec2& v0, const Vec2& v1);  ///< Return Hermite spline from p0 to p1 with corresponding tangents v0, v1.
	cSpline2 CatmullRomSpline(const Vec2& p0, const Vec2& p1, const Vec2& p2, const Vec2& p3);  ///< Return Catmull-Rom spline passing through p1 and p2, with tangents affected by p0 and p3.
	cSpline2 QuadrantSpline(const Vec2& p, double r, int quadrant);        ///< Returns a spline representing the given quadrant (quarter circle) of radius 'r' at 'p'
	void     CircleSplines(const Vec2& p, double r, cSpline2 splines[4]); ///< Fills 'splines' with four splines representing a circle of radius 'r' at 'p'

	int   NumSplinesForPoints(int numPoints);     ///< Returns number of splines needed to represent the given number of points; generally n-1 except for n < 2.
	int   SplinesFromPoints(int numPoints, const Vec2 p[], int maxSplines, cSpline2 splines[], double tension = 0.0, size_t stride = sizeof(Vec2));
	///< Fills 'splines' with splines that interpolate the points in 'p', and returns the number of these splines.
	///< 'tension' controls the interpolation -- the default value of 0 specifies Catmull-Rom splines that
	///< guarantee tangent continuity. With +1 you get straight lines, and -1 gives more of a circular appearance.

	int   SplinesFromBezier(int numPoints, const Vec2 points[], const Vec2 hullPoints[], cSpline2 splines[], bool split = false); ///< Creates splines from the given points and Bezier hull points. If 'split' is false the splines are assumed to be continous and numPoints - 1 splinea are output. Otherwise the points are assumed to come in pairs, and numPoints / 2 splines output.
	int   SplinesFromHermite(int numPoints, const Vec2 points[], const Vec2 tangents[], cSpline2 splines[], bool split = false); ///< Creates splines from the given points and tangents. If 'split' is false the splines are assumed to be continous and numPoints - 1 splinea are output. Otherwise the points are assumed to come in pairs, and numPoints / 2 splines output.

	// Queries
	Vec2 Position0(const cSpline2& spline);    ///< Starting position of spline
	Vec2 Position1(const cSpline2& spline);    ///< End position of spline

	Vec2 Velocity0(const cSpline2& spline);    ///< Starting (tangential) velocity
	Vec2 Velocity1(const cSpline2& spline);    ///< End velocity

	Vec2 Position(const cSpline2& spline, double t); ///< Returns interpolated position
	Vec2 Velocity(const cSpline2& spline, double t); ///< Returns interpolated velocity
	Vec2 Acceleration(const cSpline2& spline, double t); ///< Returns interpolated acceleration
	double Curvature(const cSpline2& spline, double t); ///< Returns interpolated curvature. Curvature = 1 / r where r is the radius of the local turning circle, so 0 for flat.

	void  Frame(const cSpline2& spline, double t, Mat2f* frame);  ///< Returns interpolated orientation matrix representing the full frame at 't'

	double LengthEstimate(const cSpline2& s, double* error);              ///< Returns estimate of length of s and optionally in 'error' the maximum error of that length.
	double Length(const cSpline2& s, double maxError = 0.01);    ///< Returns length of spline accurate to the given tolerance, using multiple LengthEstimate() calls.
	double Length(const cSpline2& s, double t0, double t1, double maxError = 0.01);    ///< Returns length of spline segment over [t0, t1].

	Bounds2f FastBounds(const cSpline2& spline);               ///< Returns fast, convervative bounds based off the convex hull of the spline.
	Bounds2f ExactBounds(const cSpline2& spline);               ///< Returns exact bounds, taking into account extrema, requires solving a quadratic

	// Subdivision
	void Split(const cSpline2& spline, cSpline2* spline0, cSpline2* spline1);  ///< Splits 'spline' into two halves (at t = 0.5) and stores the results in 'subSplines'
	void Split(const cSpline2& spline, double t, cSpline2* spline0, cSpline2* spline1);  ///< Fills 'subSplines' with the splines corresponding to [0, t] and [t, 1]
	bool Join(const cSpline2& spline0, const cSpline2& spline1, cSpline2* spline);     ///< Joins two splines that were formerly Split(). Assumes t=0.5, returns false if the source splines don't match up.

	void Split(vector<cSpline2>* splines);          ///< Subdivide each spline into two pieces
	void Split(vector<cSpline2>* splines, int n);   ///< Subdivide each spline into 'n' pieces
	void Join(vector<cSpline2>* splines);          ///< Join adjacent splines where possible

	void SubdivideForLength(vector<cSpline2>* splines, double relativeError = 0.01);    ///< Subdivide splines to be close to linear, according to relativeError.
	void SubdivideForT(vector<cSpline2>* splines, double error = 0.01);            ///< Subdivide splines to be close to linear in t, i.e., arcLength

	// Nearest point
	double FindClosestPoint(const Vec2& p, const cSpline2& spline); ///< Returns t value of the closest point on s to 'p'
	double FindClosestPoint(const Vec2& p, int numSplines, const cSpline2 splines[], int* index); ///< Returns index of nearest spline, and 't' value of nearest point on that spline.

	struct cSubSpline2
	{
		cSpline2 mSpline;
		int      mParent;
		double   mD2;
	};

	int   FindNearbySplines(const Vec2& p, int numSplines, const cSpline2 splines[], vector<cSubSpline2>* nearbySplines, double* smallestFarOut = 0, int maxIter = 2);
	double FindClosestPoint(const Vec2& p, int numSplines, const cSpline2 splines[], const vector<cSubSpline2>& nearbySplines, int* index);

	int   FindSplineIntersections(const cSpline2& spline0, const cSpline2& spline1, int maxResults, double results[][2], double tolerance = 0.1);
	///< Returns up to 'maxResults' intersections between the two splines, accurate to the given tolerance.
	int   FindSplineIntersections(int numSplines0, const cSpline2 splines0[], int numSplines1, const cSpline2 splines1[], int maxResults, int resultsI[][2], double resultsT[][2], double tolerance = 0.1);
	///< Returns up to 'maxResults' intersections between the two spline lists, accurate to the given tolerance.
	int   FindSplineIntersections(int numSplines, const cSpline2 splines[], int maxResults, int resultsI[][2], double resultsT[][2], double tolerance = 0.1);
	///< Returns up to 'maxResults' self-intersections in the given spline list, accurate to the given tolerance.

	// Linear point movement along spline set
	double AdvanceAgent(const cSpline2& spline, double t, double dl); ///< Advances 'agent' at 't' on the given spline, by dl (delta length), returning t' of the new location.

	bool  AdvanceAgent(int* index, double* t, int numSplines, const cSpline2 splines[], double dl); ///< Version of AdvanceAgent for a set of splines, assumed to be continuous. Returns false if the agent has gone off the end, in which case call ClampAgent/WrapAgent/ReverseAgent.
	void  ClampAgent(int* index, double* t, int numSplines);    ///< Clamps agent position back to the nearest endpoint.
	void  WrapAgent(int* index, double* t, int numSplines);    ///< Wraps the agent from the end back to the start, or vice versa.
	void  ReverseAgent(int* index, double* t);                    ///< Reverses the agent. (You must also negate the sign of dl yourself.)

	// Misc operations
	cSpline2 Reverse(const cSpline2& spline);                    ///< Reverses spline endpoints and tangents so that g(t) = f(1 - t).
	cSpline2 Offset(const cSpline2& spline, double offset);      ///< Offset spline, e.g., for stroking, +ve = to the right.

	void     Reverse(vector<cSpline2>* splines);                 ///< Reverses entire spline list
	void     Offset(vector<cSpline2>* splines, double offset);   ///< Offset splines, e.g., for stroking, +ve = to the right.



	// 3D
	struct cSpline3
	{
		Vec4 xb;   // x cubic bezier coefficients
		Vec4 yb;   // y cubic bezier coefficients
		Vec4 zb;   // z cubic bezier coefficients
	};

	// Spline creation
	cSpline3 BezierSpline(const Vec3& p0, const Vec3& p1, const Vec3& p2, const Vec3& p3);  ///< Return Bezier spline from p0 to p3 with guide points p1, p2
	cSpline3 HermiteSpline(const Vec3& p0, const Vec3& p1, const Vec3& v0, const Vec3& v1);  ///< Return Hermite spline from p0 to p1 with corresponding tangents v0, v1.
	cSpline3 CatmullRomSpline(const Vec3& p0, const Vec3& p1, const Vec3& p2, const Vec3& p3);  ///< Return Catmull-Rom spline passing through p1 and p2, with tangents affected by p0 and p3.

	int   NumSplinesForPoints(int numPoints);     ///< Returns number of splines needed to represent the given number of points; generally n-1 except for n < 2.
	int   SplinesFromPoints(int numPoints, const Vec3 p[], int maxSplines, cSpline3 splines[], double tension = 0.0, size_t stride = sizeof(Vec3));
	///< Fills 'splines' with splines that interpolate the points in 'p', and returns the number of these splines.
	///< 'tension' controls the interpolation -- the default value of 0 specifies Catmull-Rom splines that
	///< guarantee tangent continuity. With +1 you get straight lines, and -1 gives more of a circular appearance.

	int   SplinesFromBezier(int numPoints, const Vec3 points[], const Vec3 hullPoints[], cSpline3 splines[], bool split = false); ///< Creates splines from the given points and Bezier hull points. If 'split' is false the splines are assumed to be continous and numPoints - 1 splinea are output. Otherwise the points are assumed to come in pairs, and numPoints / 2 splines output.
	int   SplinesFromHermite(int numPoints, const Vec3 points[], const Vec3 tangents[], cSpline3 splines[], bool split = false); ///< Creates splines from the given points and tangents. If 'split' is false the splines are assumed to be continous and numPoints - 1 splinea are output. Otherwise the points are assumed to come in pairs, and numPoints / 2 splines output.

	// Queries
	Vec3 Position0(const cSpline3& spline);    ///< Starting position of spline
	Vec3 Position1(const cSpline3& spline);    ///< End position of spline

	Vec3 Velocity0(const cSpline3& spline);    ///< Starting (tangential) velocity
	Vec3 Velocity1(const cSpline3& spline);    ///< End velocity

	Vec3 Position(const cSpline3& spline, double t); ///< Returns interpolated position
	Vec3 Velocity(const cSpline3& spline, double t); ///< Returns interpolated velocity
	Vec3 Acceleration(const cSpline3& spline, double t); ///< Returns interpolated acceleration
	double Curvature(const cSpline3& spline, double t); ///< Returns interpolated curvature. Curvature = 1 / r where r is the radius of the local turning circle, so 0 for flat.

	void  Frame(const cSpline3& spline, double t, Mat3f* frame); ///< Returns interpolated orientation matrix representing the full frame at 't' (z-up/y-forward/x-right)
	void  FrameSmooth(const cSpline3& spline, double t, Mat3f* frame); ///< As per Frame(), but uses the previous value of 'frame' to avoid inversions and other issues. 'frame' must be initialised on first call, to an approximation of the desired initial frame, or the identity.
	void  FrameZUp(const cSpline3& spline, double t, Mat3f* frame); ///< Returns frame with Z-up
	void  FrameUp(const cSpline3& spline, double t, const Vec3& up, Mat3f* frame); ///< Returns frame with the given up vector.

	double LengthEstimate(const cSpline3& s, double* error);              ///< Returns estimate of length of s and optionally in 'error' the maximum error of that length.
	double Length(const cSpline3& s, double maxError = 0.01);    ///< Returns length of spline accurate to the given tolerance
	double Length(const cSpline3& s, double t0, double t1, double maxError = 0.01);    ///< Returns length of spline segment over [t0, t1].

	Bounds3f FastBounds(const cSpline3& spline);               ///< Returns fast, convervative bounds based off the convex hull of the spline.
	Bounds3f ExactBounds(const cSpline3& spline);               ///< Returns exact bounds, taking into account extrema, requires solving a quadratic

	// Subdivision
	void Split(const cSpline3& spline, cSpline3* spline0, cSpline3* spline1);  ///< Splits 'spline' into two halves (at t = 0.5) and stores the results in 'subSplines'
	void Split(const cSpline3& spline, double t, cSpline3* spline0, cSpline3* spline1);  ///< Fills 'subSplines' with the splines corresponding to [0, t] and [t, 1]
	bool Join(const cSpline3& spline0, const cSpline3& spline1, cSpline3* spline);     ///< Joins two splines that were formerly Split(). Assumes t=0.5, returns false if the source splines don't match up.

	void Split(vector<cSpline3>* splines);          ///< Subdivide each spline into two pieces
	void Split(vector<cSpline3>* splines, int n);   ///< Subdivide each spline into 'n' pieces
	void Join(vector<cSpline3>* splines);          ///< Join adjacent splines where possible

	void SubdivideForLength(vector<cSpline3>* splines, double relativeError = 0.01);    ///< Subdivide splines to be close to linear, according to relativeError.
	void SubdivideForT(vector<cSpline3>* splines, double error = 0.01);            ///< Subdivide splines to be close to linear in t, i.e., arcLength

	// Nearest point
	double FindClosestPoint(const Vec3& p, const cSpline3& spline); ///< Returns t value of the closest point on s to 'p'
	double FindClosestPoint(const Vec3& p, int numSplines, const cSpline3 splines[], int* index); ///< Returns index of nearest spline, and 't' value of nearest point on that spline.

	struct cSubSpline3
	{
		cSpline3 mSpline;
		int      mParent;
		double   mD2;
	};

	int   FindNearbySplines(const Vec3& p, int numSplines, const cSpline3 splines[], vector<cSubSpline3>* nearbySplines, double* smallestFarOut = 0, int maxIter = 2);
	double FindClosestPoint(const Vec3& p, int numSplines, const cSpline3 splines[], const vector<cSubSpline3>& nearbySplines, int* index);

	int   FindSplineIntersections(const cSpline3& spline0, const cSpline3& spline1, int maxResults, double results[][2], double tolerance = 0.1);
	///< Returns up to 'maxResults' intersections between the two splines, accurate to the given tolerance.
	int   FindSplineIntersections(int numSplines0, const cSpline3 splines0[], int numSplines1, const cSpline3 splines1[], int maxResults, int resultsI[][2], double resultsT[][2], double tolerance = 0.1);
	///< Returns up to 'maxResults' intersections between the two spline lists, accurate to the given tolerance.
	int   FindSplineIntersections(int numSplines, const cSpline3 splines[], int maxResults, int resultsI[][2], double resultsT[][2], double tolerance = 0.1);
	///< Returns up to 'maxResults' self-intersections in the given spline list, accurate to the given tolerance.

	// Linear point movement along spline set
	double AdvanceAgent(const cSpline3& spline, double t, double dl); ///< Advances 'agent' at 't' on the given spline, by dl (delta length), returning t' of the new location.

	bool  AdvanceAgent(int* index, double* t, int numSplines, const cSpline3 splines[], double dl); ///< Version of AdvanceAgent for a set of splines, assumed to be continuous. Returns false if the agent has gone off the end, in which case call ClampAgent/WrapAgent/ReverseAgent.
//  void  ClampAgent  (int* index, double* t, int numSplines);    ///< Clamps agent position back to the nearest endpoint.
//  void  WrapAgent   (int* index, double* t, int numSplines);    ///< Wraps the agent from the end back to the start, or vice versa.
//  void  ReverseAgent(int* index, double* t);                    ///< Reverses the agent. (You must also negate the sign of dl yourself.)

	// Misc operations
	cSpline3 Reverse(const cSpline3& spline);                    ///< Reverses spline endpoints and tangents so that g(t) = f(1 - t).
	cSpline3 Offset(const cSpline3& spline, double offset);      ///< Offset spline, e.g., for stroking, +ve = to the right.

	void     Reverse(vector<cSpline3>* splines);                 ///< Reverses entire spline list
	void     Offset(vector<cSpline3>* splines, double offset);   ///< Offset splines, e.g., for stroking, +ve = to the right.

}

	// --- Inlines -----------------------------------------------------------------

	inline int SplineLib::NumSplinesForPoints(int numPoints)
	{
		if (numPoints < 2)
			return numPoints;

		return numPoints - 1;
	}

	// 2D

	inline Vec2 SplineLib::Position0(const cSpline2& spline)
	{
		return Vec2(spline.xb.x, spline.yb.x);
	}
	inline Vec2 SplineLib::Position1(const cSpline2& spline)
	{
		return Vec2(spline.xb.w, spline.yb.w);
	}

	inline Vec2 SplineLib::Velocity0(const cSpline2& spline)
	{
		return Vec2
		(
			3.0 * (spline.xb.y - spline.xb.x),
			3.0 * (spline.yb.y - spline.yb.x)
		);
	}
	inline Vec2 SplineLib::Velocity1(const cSpline2& spline)
	{
		return Vec2
		(
			3.0 * (spline.xb.w - spline.xb.z),
			3.0 * (spline.yb.w - spline.yb.z)
		);
	}

	inline void SplineLib::ClampAgent(int* index, double* t, int numSplines)
	{
		if (*index < 0)
		{
			*index = 0;
			*t = 0.0;
		}
		else if (*index >= numSplines)
		{
			*index = numSplines - 1;
			*t = 1.0;
		}
		else if (*t < 0.0)
			*t = 0.0;
		else if (*t > 1.0)
			*t = 1.0;
	}

	inline void SplineLib::WrapAgent(int* indexInOut, double* tInOut, int numSplines)
	{
		int& index = *indexInOut;
		double& t = *tInOut;

		SL_ASSERT(!IsNAN(t));
		SL_ASSERT(index == 0 || index == numSplines - 1);

		t -= std::floor(t);
		index ^= numSplines - 1;
	}

	inline void SplineLib::ReverseAgent(int*, double* t)
	{
		*t = std::ceil(*t) - *t;
	}

	// 3D

	inline Vec3 SplineLib::Position0(const cSpline3& spline)
	{
		return Vec3(spline.xb.x, spline.yb.x, spline.zb.x);
	}
	inline Vec3 SplineLib::Position1(const cSpline3& spline)
	{
		return Vec3(spline.xb.w, spline.yb.w, spline.zb.w);
	}

	inline Vec3 SplineLib::Velocity0(const cSpline3& spline)
	{
		return Vec3
		(
			3.0 * (spline.xb.y - spline.xb.x),
			3.0 * (spline.yb.y - spline.yb.x),
			3.0 * (spline.zb.y - spline.zb.x)
		);
	}
	inline Vec3 SplineLib::Velocity1(const cSpline3& spline)
	{
		return Vec3
		(
			3.0 * (spline.xb.w - spline.xb.z),
			3.0 * (spline.yb.w - spline.yb.z),
			3.0 * (spline.zb.w - spline.zb.z)
		);
	}

#endif
