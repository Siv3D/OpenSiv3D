//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Ray.hpp>
# include <Siv3D/Sphere.hpp>
# include <Siv3D/Box.hpp>
# include <Siv3D/OrientedBox.hpp>
# include <Siv3D/FormatFloat.hpp>

namespace s3d
{
	///////////////////////////////////////////////////////////////
	//
	//

	//
	//	DirectXMath
	//
	//	The MIT License(MIT)
	//
	//	Copyright(c) 2011 - 2020 Microsoft Corp
	//
	//	Permission is hereby granted, free of charge, to any person obtaining a copy of this
	//	softwareand associated documentation files(the "Software"), to deal in the Software
	//	without restriction, including without limitation the rights to use, copy, modify,
	//	merge, publish, distribute, sublicense, and /or sell copies of the Software, and to
	//	permit persons to whom the Software is furnished to do so, subject to the following
	//	conditions :
	//
	//	The above copyright noticeand this permission notice shall be included in all copies
	//	or substantial portions of the Software.
	//
	//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
	//	INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
	//	PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	//	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
	//	CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
	//	OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

	Optional<float> Ray::intersects(const Triangle3D& triangle) const
	{
		float dist;

		if (DirectX::TriangleTests::Intersects(origin, direction, triangle.p0, triangle.p1, triangle.p2, dist))
		{
			return dist;
		}
		else
		{
			return none;
		}
	}

	Optional<float> Ray::intersects(const Sphere& sphere) const
	{
		using namespace DirectX;

		assert(DirectX::Internal::XMVector3IsUnit(direction));

		XMVECTOR vCenter = SIMD_Float4{ sphere.center, 0.0f };
		XMVECTOR vRadius = SIMD_Float4{ static_cast<float>(sphere.r) };

		// l is the vector from the ray origin to the center of the sphere.
		XMVECTOR l = XMVectorSubtract(vCenter, origin);

		// s is the projection of the l onto the ray direction.
		XMVECTOR s = XMVector3Dot(l, direction);

		XMVECTOR l2 = XMVector3Dot(l, l);

		XMVECTOR r2 = XMVectorMultiply(vRadius, vRadius);

		// m2 is squared distance from the center of the sphere to the projection.
		XMVECTOR m2 = XMVectorNegativeMultiplySubtract(s, s, l2);

		XMVECTOR NoIntersection;

		// If the ray origin is outside the sphere and the center of the sphere is
		// behind the ray origin there is no intersection.
		NoIntersection = XMVectorAndInt(XMVectorLess(s, XMVectorZero()), XMVectorGreater(l2, r2));

		// If the squared distance from the center of the sphere to the projection
		// is greater than the radius squared the ray will miss the sphere.
		NoIntersection = XMVectorOrInt(NoIntersection, XMVectorGreater(m2, r2));

		// The ray hits the sphere, compute the nearest intersection point.
		XMVECTOR q = XMVectorSqrt(XMVectorSubtract(r2, m2));
		XMVECTOR t1 = XMVectorSubtract(s, q);
		XMVECTOR t2 = XMVectorAdd(s, q);

		XMVECTOR OriginInside = XMVectorLessOrEqual(l2, r2);
		XMVECTOR t = XMVectorSelect(t1, t2, OriginInside);

		if (XMVector4NotEqualInt(NoIntersection, XMVectorTrueInt()))
		{
			// Store the x-component to *pDist.
			float dist;
			XMStoreFloat(&dist, t);
			return dist;
		}

		return none;
	}

	Optional<float> Ray::intersects(const Box& aabb) const
	{
		using namespace DirectX;

		assert(DirectX::Internal::XMVector3IsUnit(direction));

		// Load the box.
		XMVECTOR vCenter = SIMD_Float4{ aabb.center, 0.0f };
		XMVECTOR vExtents = SIMD_Float4{ aabb.size, 0.0f };

		// Adjust ray origin to be relative to center of the box.
		XMVECTOR TOrigin = XMVectorSubtract(vCenter, origin);

		// Compute the dot product againt each axis of the box.
		// Since the axii are (1,0,0), (0,1,0), (0,0,1) no computation is necessary.
		XMVECTOR AxisDotOrigin = TOrigin;
		XMVECTOR AxisDotDirection = direction;

		// if (fabs(AxisDotDirection) <= Epsilon) the ray is nearly parallel to the slab.
		XMVECTOR IsParallel = XMVectorLessOrEqual(XMVectorAbs(AxisDotDirection), g_RayEpsilon);

		// Test against all three axii simultaneously.
		XMVECTOR InverseAxisDotDirection = XMVectorReciprocal(AxisDotDirection);
		XMVECTOR t1 = XMVectorMultiply(XMVectorSubtract(AxisDotOrigin, vExtents), InverseAxisDotDirection);
		XMVECTOR t2 = XMVectorMultiply(XMVectorAdd(AxisDotOrigin, vExtents), InverseAxisDotDirection);

		// Compute the max of min(t1,t2) and the min of max(t1,t2) ensuring we don't
		// use the results from any directions parallel to the slab.
		XMVECTOR t_min = XMVectorSelect(XMVectorMin(t1, t2), g_FltMin, IsParallel);
		XMVECTOR t_max = XMVectorSelect(XMVectorMax(t1, t2), g_FltMax, IsParallel);

		// t_min.x = maximum( t_min.x, t_min.y, t_min.z );
		// t_max.x = minimum( t_max.x, t_max.y, t_max.z );
		t_min = XMVectorMax(t_min, XMVectorSplatY(t_min));  // x = max(x,y)
		t_min = XMVectorMax(t_min, XMVectorSplatZ(t_min));  // x = max(max(x,y),z)
		t_max = XMVectorMin(t_max, XMVectorSplatY(t_max));  // x = min(x,y)
		t_max = XMVectorMin(t_max, XMVectorSplatZ(t_max));  // x = min(min(x,y),z)

		// if ( t_min > t_max ) return false;
		XMVECTOR NoIntersection = XMVectorGreater(XMVectorSplatX(t_min), XMVectorSplatX(t_max));

		// if ( t_max < 0.0f ) return false;
		NoIntersection = XMVectorOrInt(NoIntersection, XMVectorLess(XMVectorSplatX(t_max), XMVectorZero()));

		// if (IsParallel && (-Extents > AxisDotOrigin || Extents < AxisDotOrigin)) return false;
		XMVECTOR ParallelOverlap = XMVectorInBounds(AxisDotOrigin, vExtents);
		NoIntersection = XMVectorOrInt(NoIntersection, XMVectorAndCInt(IsParallel, ParallelOverlap));

		if (!DirectX::Internal::XMVector3AnyTrue(NoIntersection))
		{
			// Store the x-component to *pDist
			float dist;
			XMStoreFloat(&dist, t_min);
			return dist;
		}

		return none;
	}

	Optional<float> Ray::intersects(const OrientedBox& obb) const
	{
		using namespace DirectX;

		assert(DirectX::Internal::XMVector3IsUnit(direction));

		static const XMVECTORU32 SelectY = { { { XM_SELECT_0, XM_SELECT_1, XM_SELECT_0, XM_SELECT_0 } } };
		static const XMVECTORU32 SelectZ = { { { XM_SELECT_0, XM_SELECT_0, XM_SELECT_1, XM_SELECT_0 } } };

		// Load the box.
		XMVECTOR vCenter = SIMD_Float4{ obb.center, 0.0f };
		XMVECTOR vExtents = SIMD_Float4{ obb.size, 0.0f };
		XMVECTOR vOrientation = obb.orientation;

		assert(DirectX::Internal::XMQuaternionIsUnit(vOrientation));

		// Get the boxes normalized side directions.
		XMMATRIX R = XMMatrixRotationQuaternion(vOrientation);

		// Adjust ray origin to be relative to center of the box.
		XMVECTOR TOrigin = XMVectorSubtract(vCenter, origin);

		// Compute the dot product againt each axis of the box.
		XMVECTOR AxisDotOrigin = XMVector3Dot(R.r[0], TOrigin);
		AxisDotOrigin = XMVectorSelect(AxisDotOrigin, XMVector3Dot(R.r[1], TOrigin), SelectY);
		AxisDotOrigin = XMVectorSelect(AxisDotOrigin, XMVector3Dot(R.r[2], TOrigin), SelectZ);

		XMVECTOR AxisDotDirection = XMVector3Dot(R.r[0], direction);
		AxisDotDirection = XMVectorSelect(AxisDotDirection, XMVector3Dot(R.r[1], direction), SelectY);
		AxisDotDirection = XMVectorSelect(AxisDotDirection, XMVector3Dot(R.r[2], direction), SelectZ);

		// if (fabs(AxisDotDirection) <= Epsilon) the ray is nearly parallel to the slab.
		XMVECTOR IsParallel = XMVectorLessOrEqual(XMVectorAbs(AxisDotDirection), g_RayEpsilon);

		// Test against all three axes simultaneously.
		XMVECTOR InverseAxisDotDirection = XMVectorReciprocal(AxisDotDirection);
		XMVECTOR t1 = XMVectorMultiply(XMVectorSubtract(AxisDotOrigin, vExtents), InverseAxisDotDirection);
		XMVECTOR t2 = XMVectorMultiply(XMVectorAdd(AxisDotOrigin, vExtents), InverseAxisDotDirection);

		// Compute the max of min(t1,t2) and the min of max(t1,t2) ensuring we don't
		// use the results from any directions parallel to the slab.
		XMVECTOR t_min = XMVectorSelect(XMVectorMin(t1, t2), g_FltMin, IsParallel);
		XMVECTOR t_max = XMVectorSelect(XMVectorMax(t1, t2), g_FltMax, IsParallel);

		// t_min.x = maximum( t_min.x, t_min.y, t_min.z );
		// t_max.x = minimum( t_max.x, t_max.y, t_max.z );
		t_min = XMVectorMax(t_min, XMVectorSplatY(t_min));  // x = max(x,y)
		t_min = XMVectorMax(t_min, XMVectorSplatZ(t_min));  // x = max(max(x,y),z)
		t_max = XMVectorMin(t_max, XMVectorSplatY(t_max));  // x = min(x,y)
		t_max = XMVectorMin(t_max, XMVectorSplatZ(t_max));  // x = min(min(x,y),z)

		// if ( t_min > t_max ) return false;
		XMVECTOR NoIntersection = XMVectorGreater(XMVectorSplatX(t_min), XMVectorSplatX(t_max));

		// if ( t_max < 0.0f ) return false;
		NoIntersection = XMVectorOrInt(NoIntersection, XMVectorLess(XMVectorSplatX(t_max), XMVectorZero()));

		// if (IsParallel && (-Extents > AxisDotOrigin || Extents < AxisDotOrigin)) return false;
		XMVECTOR ParallelOverlap = XMVectorInBounds(AxisDotOrigin, vExtents);
		NoIntersection = XMVectorOrInt(NoIntersection, XMVectorAndCInt(IsParallel, ParallelOverlap));

		if (!DirectX::Internal::XMVector3AnyTrue(NoIntersection))
		{
			// Store the x-component to *pDist
			float dist;
			XMStoreFloat(&dist, t_min);
			return dist;
		}

		return none;
	}

	//
	//
	///////////////////////////////////////////////////////////////

	void Ray::_Formatter(FormatData& formatData, const Ray& value)
	{
		const Float4 o = value.origin.toFloat4();
		const Float4 d = value.direction.toFloat4();

		formatData.string.append(U"(("_sv);

		formatData.string.append(ToString(o.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(o.y, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(o.z, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(o.w, formatData.decimalPlaces.value));
		formatData.string.append(U"), ("_sv);

		formatData.string.append(ToString(d.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(d.y, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(d.z, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(d.w, formatData.decimalPlaces.value));

		formatData.string.append(U"))"_sv);
	}
}
