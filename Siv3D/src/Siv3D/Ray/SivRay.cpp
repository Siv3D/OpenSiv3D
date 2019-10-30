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

# include <cfloat>
# include <Siv3D/Ray.hpp>
# include <Siv3D/Sphere.hpp>
# include <Siv3D/AABB.hpp>
# include <Siv3D/OBB.hpp>
# include <Siv3D/SIMD_Float4.hpp>
# include <Siv3D/SIMDMath.hpp>

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
	//	Copyright(c) 2011 - 2019 Microsoft Corp
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

	namespace detail
	{
		inline constexpr __m128 m128_RayEpsilon{ 1e-20f, 1e-20f, 1e-20f, 1e-20f };
		inline constexpr __m128 m128_FltMin{ -FLT_MAX, -FLT_MAX, -FLT_MAX, -FLT_MAX };
		inline constexpr __m128 m128_FltMax{ FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX };

		//-----------------------------------------------------------------------------
		// Return true if any of the elements of a 3 vector are equal to 0xffffffff.
		// Slightly more efficient than using XMVector3EqualInt.
		//-----------------------------------------------------------------------------
		inline bool Vector3AnyTrue(__m128 V)
		{
			// Duplicate the fourth element from the first element.
			__m128 C = SIMD::Swizzle<SIMD::constants::SwizzleX, SIMD::constants::SwizzleY, SIMD::constants::SwizzleZ, SIMD::constants::SwizzleX>(V);

			return SIMD::ComparisonAnyTrue(SIMD::Vector4EqualIntR(C, SIMD::TrueInt()));
		}

		inline constexpr __m128 m128_UnitQuaternionEpsilon{ 1.0e-4f, 1.0e-4f, 1.0e-4f, 1.0e-4f };

		inline bool QuaternionIsUnit(__m128 q)
		{
			__m128 Difference = SIMD::Subtract(SIMD::Vector4Length(q), SIMD::One());
			return SIMD::Vector4Less(SIMD::Abs(Difference), m128_UnitQuaternionEpsilon);
		}
	}

	Optional<float> Ray::intersects(const Sphere& sphere) const
	{
		//assert(DirectX::Internal::XMVector3IsUnit(Direction));

		const __m128 Origin = SIMD_Float4(origin, 0.0f);
		const __m128 Direction = SIMD_Float4(direction, 0.0f);

		__m128 vCenter = SIMD_Float4(sphere.center, 0.0f);
		__m128 vRadius = SIMD::SetAll(static_cast<float>(sphere.r));

		// l is the vector from the ray origin to the center of the sphere.
		__m128 l = SIMD::Subtract(vCenter, Origin);

		// s is the projection of the l onto the ray direction.
		__m128 s = SIMD::Vector3Dot(l, Direction);

		__m128 l2 = SIMD::Vector3Dot(l, l);

		__m128 r2 = SIMD::Multiply(vRadius, vRadius);

		// m2 is squared distance from the center of the sphere to the projection.
		__m128 m2 = SIMD::NegativeMultiplySubtract(s, s, l2);

		__m128 NoIntersection;

		// If the ray origin is outside the sphere and the center of the sphere is
		// behind the ray origin there is no intersection.
		NoIntersection = SIMD::AndInt(SIMD::Less(s, SIMD::Zero()), SIMD::Greater(l2, r2));

		// If the squared distance from the center of the sphere to the projection
		// is greater than the radius squared the ray will miss the sphere.
		NoIntersection = SIMD::OrInt(NoIntersection, SIMD::Greater(m2, r2));

		// The ray hits the sphere, compute the nearest intersection point.
		__m128 q = SIMD::Sqrt(SIMD::Subtract(r2, m2));
		__m128 t1 = SIMD::Subtract(s, q);
		__m128 t2 = SIMD::Add(s, q);

		__m128 OriginInside = SIMD::LessOrEqual(l2, r2);
		__m128 t = SIMD::Select(t1, t2, OriginInside);

		if (SIMD::Vector4NotEqualInt(NoIntersection, SIMD::TrueInt()))
		{
			float distance = 0.0f;
			// Store the x-component to *pDist.
			SIMD::StoreFloat(&distance, t);
			return distance;
		}

		return none;
	}

	Optional<float> Ray::intersects(const experimental::AABB& aabb) const
	{
		//assert(SIMD::Internal::Vector3IsUnit(Direction));

		const __m128 Origin = SIMD_Float4(origin, 0.0f);
		const __m128 Direction = SIMD_Float4(direction, 0.0f);

		// Load the box.
		__m128 vCenter = SIMD_Float4(aabb.center, 0.0f);
		__m128 vExtents = SIMD_Float4(aabb.size, 0.0f);
		vExtents = SIMD::Multiply(vExtents, SIMD::constants::m128_OneHalf);

		// Adjust ray origin to be relative to center of the box.
		__m128 TOrigin = SIMD::Subtract(vCenter, Origin);

		// Compute the dot product againt each axis of the box.
		// Since the axii are (1,0,0), (0,1,0), (0,0,1) no computation is necessary.
		__m128 AxisDotOrigin = TOrigin;
		__m128 AxisDotDirection = Direction;

		// if (fabs(AxisDotDirection) <= Epsilon) the ray is nearly parallel to the slab.
		__m128 IsParallel = SIMD::LessOrEqual(SIMD::Abs(AxisDotDirection), detail::m128_RayEpsilon);

		// Test against all three axii simultaneously.
		__m128 InverseAxisDotDirection = SIMD::Reciprocal(AxisDotDirection);
		__m128 t1 = SIMD::Multiply(SIMD::Subtract(AxisDotOrigin, vExtents), InverseAxisDotDirection);
		__m128 t2 = SIMD::Multiply(SIMD::Add(AxisDotOrigin, vExtents), InverseAxisDotDirection);

		// Compute the max of min(t1,t2) and the min of max(t1,t2) ensuring we don't
		// use the results from any directions parallel to the slab.
		__m128 t_min = SIMD::Select(SIMD::Min(t1, t2), detail::m128_FltMin, IsParallel);
		__m128 t_max = SIMD::Select(SIMD::Max(t1, t2), detail::m128_FltMax, IsParallel);

		// t_min.x = maximum( t_min.x, t_min.y, t_min.z );
		// t_max.x = minimum( t_max.x, t_max.y, t_max.z );
		t_min = SIMD::Max(t_min, SIMD::SplatY(t_min));  // x = max(x,y)
		t_min = SIMD::Max(t_min, SIMD::SplatZ(t_min));  // x = max(max(x,y),z)
		t_max = SIMD::Min(t_max, SIMD::SplatY(t_max));  // x = min(x,y)
		t_max = SIMD::Min(t_max, SIMD::SplatZ(t_max));  // x = min(min(x,y),z)

		// if ( t_min > t_max ) return false;
		__m128 NoIntersection = SIMD::Greater(SIMD::SplatX(t_min), SIMD::SplatX(t_max));

		// if ( t_max < 0.0f ) return false;
		NoIntersection = SIMD::OrInt(NoIntersection, SIMD::Less(SIMD::SplatX(t_max), SIMD::Zero()));

		// if (IsParallel && (-Extents > AxisDotOrigin || Extents < AxisDotOrigin)) return false;
		__m128 ParallelOverlap = SIMD::InBounds(AxisDotOrigin, vExtents);
		NoIntersection = SIMD::OrInt(NoIntersection, SIMD::AndCInt(IsParallel, ParallelOverlap));

		if (!detail::Vector3AnyTrue(NoIntersection))
		{
			float distance = 0.0f;
			// Store the x-component to *pDist
			SIMD::StoreFloat(&distance, t_min);
			return distance;
		}
		
		return none;
	}

	Optional<float> Ray::intersects(const experimental::OBB& obb) const
	{
		//assert(SIMD::Internal::Vector3IsUnit(Direction));

		const __m128 Origin = SIMD_Float4(origin, 0.0f);
		const __m128 Direction = SIMD_Float4(direction, 0.0f);

		using SIMD::constants::u_SELECT_0;
		using SIMD::constants::u_SELECT_1;
		static const SIMD::Uint4A SelectY = { { { u_SELECT_0, u_SELECT_1, u_SELECT_0, u_SELECT_0 } } };
		static const SIMD::Uint4A SelectZ = { { { u_SELECT_0, u_SELECT_0, u_SELECT_1, u_SELECT_0 } } };

		// Load the box.
		__m128 vCenter = SIMD_Float4(obb.center, 0.0f);
		__m128 vExtents = SIMD_Float4(obb.size, 0.0f);
		vExtents = SIMD::Multiply(vExtents, SIMD::constants::m128_OneHalf);
		__m128 vOrientation = obb.orientation;

		assert(detail::QuaternionIsUnit(vOrientation));

		// Get the boxes normalized side directions.
		Mat4x4 R = SIMD::MatrixRotationQuaternion(vOrientation);

		// Adjust ray origin to be relative to center of the box.
		__m128 TOrigin = SIMD::Subtract(vCenter, Origin);

		// Compute the dot product againt each axis of the box.
		__m128 AxisDotOrigin = SIMD::Vector3Dot(R.r[0], TOrigin);
		AxisDotOrigin = SIMD::Select(AxisDotOrigin, SIMD::Vector3Dot(R.r[1], TOrigin), SelectY);
		AxisDotOrigin = SIMD::Select(AxisDotOrigin, SIMD::Vector3Dot(R.r[2], TOrigin), SelectZ);

		__m128 AxisDotDirection = SIMD::Vector3Dot(R.r[0], Direction);
		AxisDotDirection = SIMD::Select(AxisDotDirection, SIMD::Vector3Dot(R.r[1], Direction), SelectY);
		AxisDotDirection = SIMD::Select(AxisDotDirection, SIMD::Vector3Dot(R.r[2], Direction), SelectZ);

		// if (fabs(AxisDotDirection) <= Epsilon) the ray is nearly parallel to the slab.
		__m128 IsParallel = SIMD::LessOrEqual(SIMD::Abs(AxisDotDirection), detail::m128_RayEpsilon);

		// Test against all three axes simultaneously.
		__m128 InverseAxisDotDirection = SIMD::Reciprocal(AxisDotDirection);
		__m128 t1 = SIMD::Multiply(SIMD::Subtract(AxisDotOrigin, vExtents), InverseAxisDotDirection);
		__m128 t2 = SIMD::Multiply(SIMD::Add(AxisDotOrigin, vExtents), InverseAxisDotDirection);

		// Compute the max of min(t1,t2) and the min of max(t1,t2) ensuring we don't
		// use the results from any directions parallel to the slab.
		__m128 t_min = SIMD::Select(SIMD::Min(t1, t2), detail::m128_FltMin, IsParallel);
		__m128 t_max = SIMD::Select(SIMD::Max(t1, t2), detail::m128_FltMax, IsParallel);

		// t_min.x = maximum( t_min.x, t_min.y, t_min.z );
		// t_max.x = minimum( t_max.x, t_max.y, t_max.z );
		t_min = SIMD::Max(t_min, SIMD::SplatY(t_min));  // x = max(x,y)
		t_min = SIMD::Max(t_min, SIMD::SplatZ(t_min));  // x = max(max(x,y),z)
		t_max = SIMD::Min(t_max, SIMD::SplatY(t_max));  // x = min(x,y)
		t_max = SIMD::Min(t_max, SIMD::SplatZ(t_max));  // x = min(min(x,y),z)

		// if ( t_min > t_max ) return false;
		__m128 NoIntersection = SIMD::Greater(SIMD::SplatX(t_min), SIMD::SplatX(t_max));

		// if ( t_max < 0.0f ) return false;
		NoIntersection = SIMD::OrInt(NoIntersection, SIMD::Less(SIMD::SplatX(t_max), SIMD::Zero()));

		// if (IsParallel && (-Extents > AxisDotOrigin || Extents < AxisDotOrigin)) return false;
		__m128 ParallelOverlap = SIMD::InBounds(AxisDotOrigin, vExtents);
		NoIntersection = SIMD::OrInt(NoIntersection, SIMD::AndCInt(IsParallel, ParallelOverlap));

		if (!detail::Vector3AnyTrue(NoIntersection))
		{
			float distance = 0.0f;
			// Store the x-component to *pDist
			SIMD::StoreFloat(&distance, t_min);
			return true;
		}

		return none;
	}

	//
	//
	///////////////////////////////////////////////////////////////
}
