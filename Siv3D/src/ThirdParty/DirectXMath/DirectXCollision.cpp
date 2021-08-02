
# include <Siv3D/Common.hpp> 

# if SIV3D_INTRINSIC(SSE)
    # define _XM_SSE4_INTRINSICS_
# endif

# if SIV3D_PLATFORM(WEB) && defined(__clang__)
#   pragma clang attribute push (__attribute__((noinline)), apply_to = function)
# endif

# include <ThirdParty/DirectXMath/DirectXCollision.h>

# if SIV3D_PLATFORM(WEB) && defined(__clang__)
#   pragma clang attribute pop
# endif

//
// Web 版ビルドにおけるコンパイラのバグ回避のため、一部の関数を .cpp ファイルに移動。
//

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

namespace DirectX
{


//-----------------------------------------------------------------------------
// Exact frustum vs frustum test.
//-----------------------------------------------------------------------------
_Use_decl_annotations_
bool BoundingFrustum::Intersects(const BoundingFrustum& fr) const noexcept
{
    // Load origin and orientation of frustum B.
    XMVECTOR OriginB = XMLoadFloat3(&Origin);
    XMVECTOR OrientationB = XMLoadFloat4(&Orientation);

    assert(DirectX::Internal::XMQuaternionIsUnit(OrientationB));

    // Build the planes of frustum B.
    XMVECTOR AxisB[6];
    AxisB[0] = XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);
    AxisB[1] = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
    AxisB[2] = XMVectorSet(1.0f, 0.0f, -RightSlope, 0.0f);
    AxisB[3] = XMVectorSet(-1.0f, 0.0f, LeftSlope, 0.0f);
    AxisB[4] = XMVectorSet(0.0f, 1.0f, -TopSlope, 0.0f);
    AxisB[5] = XMVectorSet(0.0f, -1.0f, BottomSlope, 0.0f);

    XMVECTOR PlaneDistB[6];
    PlaneDistB[0] = XMVectorNegate(XMVectorReplicatePtr(&Near));
    PlaneDistB[1] = XMVectorReplicatePtr(&Far);
    PlaneDistB[2] = XMVectorZero();
    PlaneDistB[3] = XMVectorZero();
    PlaneDistB[4] = XMVectorZero();
    PlaneDistB[5] = XMVectorZero();

    // Load origin and orientation of frustum A.
    XMVECTOR OriginA = XMLoadFloat3(&fr.Origin);
    XMVECTOR OrientationA = XMLoadFloat4(&fr.Orientation);

    assert(DirectX::Internal::XMQuaternionIsUnit(OrientationA));

    // Transform frustum A into the space of the frustum B in order to
    // minimize the number of transforms we have to do.
    OriginA = XMVector3InverseRotate(XMVectorSubtract(OriginA, OriginB), OrientationB);
    OrientationA = XMQuaternionMultiply(OrientationA, XMQuaternionConjugate(OrientationB));

    // Build the corners of frustum A (in the local space of B).
    XMVECTOR RightTopA = XMVectorSet(fr.RightSlope, fr.TopSlope, 1.0f, 0.0f);
    XMVECTOR RightBottomA = XMVectorSet(fr.RightSlope, fr.BottomSlope, 1.0f, 0.0f);
    XMVECTOR LeftTopA = XMVectorSet(fr.LeftSlope, fr.TopSlope, 1.0f, 0.0f);
    XMVECTOR LeftBottomA = XMVectorSet(fr.LeftSlope, fr.BottomSlope, 1.0f, 0.0f);
    XMVECTOR NearA = XMVectorReplicatePtr(&fr.Near);
    XMVECTOR FarA = XMVectorReplicatePtr(&fr.Far);

    RightTopA = XMVector3Rotate(RightTopA, OrientationA);
    RightBottomA = XMVector3Rotate(RightBottomA, OrientationA);
    LeftTopA = XMVector3Rotate(LeftTopA, OrientationA);
    LeftBottomA = XMVector3Rotate(LeftBottomA, OrientationA);

    XMVECTOR CornersA[CORNER_COUNT];
    CornersA[0] = XMVectorMultiplyAdd(RightTopA, NearA, OriginA);
    CornersA[1] = XMVectorMultiplyAdd(RightBottomA, NearA, OriginA);
    CornersA[2] = XMVectorMultiplyAdd(LeftTopA, NearA, OriginA);
    CornersA[3] = XMVectorMultiplyAdd(LeftBottomA, NearA, OriginA);
    CornersA[4] = XMVectorMultiplyAdd(RightTopA, FarA, OriginA);
    CornersA[5] = XMVectorMultiplyAdd(RightBottomA, FarA, OriginA);
    CornersA[6] = XMVectorMultiplyAdd(LeftTopA, FarA, OriginA);
    CornersA[7] = XMVectorMultiplyAdd(LeftBottomA, FarA, OriginA);

    // Check frustum A against each plane of frustum B.
    XMVECTOR Outside = XMVectorFalseInt();
    XMVECTOR InsideAll = XMVectorTrueInt();

    for (size_t i = 0; i < 6; ++i)
    {
        // Find the min/max projection of the frustum onto the plane normal.
        XMVECTOR Min, Max;

        Min = Max = XMVector3Dot(AxisB[i], CornersA[0]);

        for (size_t j = 1; j < CORNER_COUNT; j++)
        {
            XMVECTOR Temp = XMVector3Dot(AxisB[i], CornersA[j]);
            Min = XMVectorMin(Min, Temp);
            Max = XMVectorMax(Max, Temp);
        }

        // Outside the plane?
        Outside = XMVectorOrInt(Outside, XMVectorGreater(Min, PlaneDistB[i]));

        // Fully inside the plane?
        InsideAll = XMVectorAndInt(InsideAll, XMVectorLessOrEqual(Max, PlaneDistB[i]));
    }

    // If the frustum A is outside any of the planes of frustum B it is outside.
    if (XMVector4EqualInt(Outside, XMVectorTrueInt()))
        return false;

    // If frustum A is inside all planes of frustum B it is fully inside.
    if (XMVector4EqualInt(InsideAll, XMVectorTrueInt()))
        return true;

    // Build the corners of frustum B.
    XMVECTOR RightTopB = XMVectorSet(RightSlope, TopSlope, 1.0f, 0.0f);
    XMVECTOR RightBottomB = XMVectorSet(RightSlope, BottomSlope, 1.0f, 0.0f);
    XMVECTOR LeftTopB = XMVectorSet(LeftSlope, TopSlope, 1.0f, 0.0f);
    XMVECTOR LeftBottomB = XMVectorSet(LeftSlope, BottomSlope, 1.0f, 0.0f);
    XMVECTOR NearB = XMVectorReplicatePtr(&Near);
    XMVECTOR FarB = XMVectorReplicatePtr(&Far);

    XMVECTOR CornersB[BoundingFrustum::CORNER_COUNT];
    CornersB[0] = XMVectorMultiply(RightTopB, NearB);
    CornersB[1] = XMVectorMultiply(RightBottomB, NearB);
    CornersB[2] = XMVectorMultiply(LeftTopB, NearB);
    CornersB[3] = XMVectorMultiply(LeftBottomB, NearB);
    CornersB[4] = XMVectorMultiply(RightTopB, FarB);
    CornersB[5] = XMVectorMultiply(RightBottomB, FarB);
    CornersB[6] = XMVectorMultiply(LeftTopB, FarB);
    CornersB[7] = XMVectorMultiply(LeftBottomB, FarB);

    // Build the planes of frustum A (in the local space of B).
    XMVECTOR AxisA[6];
    XMVECTOR PlaneDistA[6];

    AxisA[0] = XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);
    AxisA[1] = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
    AxisA[2] = XMVectorSet(1.0f, 0.0f, -fr.RightSlope, 0.0f);
    AxisA[3] = XMVectorSet(-1.0f, 0.0f, fr.LeftSlope, 0.0f);
    AxisA[4] = XMVectorSet(0.0f, 1.0f, -fr.TopSlope, 0.0f);
    AxisA[5] = XMVectorSet(0.0f, -1.0f, fr.BottomSlope, 0.0f);

    AxisA[0] = XMVector3Rotate(AxisA[0], OrientationA);
    AxisA[1] = XMVectorNegate(AxisA[0]);
    AxisA[2] = XMVector3Rotate(AxisA[2], OrientationA);
    AxisA[3] = XMVector3Rotate(AxisA[3], OrientationA);
    AxisA[4] = XMVector3Rotate(AxisA[4], OrientationA);
    AxisA[5] = XMVector3Rotate(AxisA[5], OrientationA);

    PlaneDistA[0] = XMVector3Dot(AxisA[0], CornersA[0]);  // Re-use corner on near plane.
    PlaneDistA[1] = XMVector3Dot(AxisA[1], CornersA[4]);  // Re-use corner on far plane.
    PlaneDistA[2] = XMVector3Dot(AxisA[2], OriginA);
    PlaneDistA[3] = XMVector3Dot(AxisA[3], OriginA);
    PlaneDistA[4] = XMVector3Dot(AxisA[4], OriginA);
    PlaneDistA[5] = XMVector3Dot(AxisA[5], OriginA);

    // Check each axis of frustum A for a seperating plane (5).
    for (size_t i = 0; i < 6; ++i)
    {
        // Find the minimum projection of the frustum onto the plane normal.
        XMVECTOR Min;

        Min = XMVector3Dot(AxisA[i], CornersB[0]);

        for (size_t j = 1; j < CORNER_COUNT; j++)
        {
            XMVECTOR Temp = XMVector3Dot(AxisA[i], CornersB[j]);
            Min = XMVectorMin(Min, Temp);
        }

        // Outside the plane?
        Outside = XMVectorOrInt(Outside, XMVectorGreater(Min, PlaneDistA[i]));
    }

    // If the frustum B is outside any of the planes of frustum A it is outside.
    if (XMVector4EqualInt(Outside, XMVectorTrueInt()))
        return false;

    // Check edge/edge axes (6 * 6).
    XMVECTOR FrustumEdgeAxisA[6];
    FrustumEdgeAxisA[0] = RightTopA;
    FrustumEdgeAxisA[1] = RightBottomA;
    FrustumEdgeAxisA[2] = LeftTopA;
    FrustumEdgeAxisA[3] = LeftBottomA;
    FrustumEdgeAxisA[4] = XMVectorSubtract(RightTopA, LeftTopA);
    FrustumEdgeAxisA[5] = XMVectorSubtract(LeftBottomA, LeftTopA);

    XMVECTOR FrustumEdgeAxisB[6];
    FrustumEdgeAxisB[0] = RightTopB;
    FrustumEdgeAxisB[1] = RightBottomB;
    FrustumEdgeAxisB[2] = LeftTopB;
    FrustumEdgeAxisB[3] = LeftBottomB;
    FrustumEdgeAxisB[4] = XMVectorSubtract(RightTopB, LeftTopB);
    FrustumEdgeAxisB[5] = XMVectorSubtract(LeftBottomB, LeftTopB);

    for (size_t i = 0; i < 6; ++i)
    {
        for (size_t j = 0; j < 6; j++)
        {
            // Compute the axis we are going to test.
            XMVECTOR Axis = XMVector3Cross(FrustumEdgeAxisA[i], FrustumEdgeAxisB[j]);

            // Find the min/max values of the projection of both frustums onto the axis.
            XMVECTOR MinA, MaxA;
            XMVECTOR MinB, MaxB;

            MinA = MaxA = XMVector3Dot(Axis, CornersA[0]);
            MinB = MaxB = XMVector3Dot(Axis, CornersB[0]);

            for (size_t k = 1; k < CORNER_COUNT; k++)
            {
                XMVECTOR TempA = XMVector3Dot(Axis, CornersA[k]);
                MinA = XMVectorMin(MinA, TempA);
                MaxA = XMVectorMax(MaxA, TempA);

                XMVECTOR TempB = XMVector3Dot(Axis, CornersB[k]);
                MinB = XMVectorMin(MinB, TempB);
                MaxB = XMVectorMax(MaxB, TempB);
            }

            // if (MinA > MaxB || MinB > MaxA) reject
            Outside = XMVectorOrInt(Outside, XMVectorGreater(MinA, MaxB));
            Outside = XMVectorOrInt(Outside, XMVectorGreater(MinB, MaxA));
        }
    }

    // If there is a seperating plane, then the frustums do not intersect.
    if (XMVector4EqualInt(Outside, XMVectorTrueInt()))
        return false;

    // If we did not find a separating plane then the frustums intersect.
    return true;
}


//-----------------------------------------------------------------------------
// Point in frustum test.
//-----------------------------------------------------------------------------
_Use_decl_annotations_
ContainmentType XM_CALLCONV BoundingFrustum::Contains(FXMVECTOR Point) const noexcept
{
    // Build frustum planes.
    XMVECTOR Planes[6];
    Planes[0] = XMVectorSet(0.0f, 0.0f, -1.0f, Near);
    Planes[1] = XMVectorSet(0.0f, 0.0f, 1.0f, -Far);
    Planes[2] = XMVectorSet(1.0f, 0.0f, -RightSlope, 0.0f);
    Planes[3] = XMVectorSet(-1.0f, 0.0f, LeftSlope, 0.0f);
    Planes[4] = XMVectorSet(0.0f, 1.0f, -TopSlope, 0.0f);
    Planes[5] = XMVectorSet(0.0f, -1.0f, BottomSlope, 0.0f);

    // Load origin and orientation.
    XMVECTOR vOrigin = XMLoadFloat3(&Origin);
    XMVECTOR vOrientation = XMLoadFloat4(&Orientation);

    assert(DirectX::Internal::XMQuaternionIsUnit(vOrientation));

    // Transform point into local space of frustum.
    XMVECTOR TPoint = XMVector3InverseRotate(XMVectorSubtract(Point, vOrigin), vOrientation);

    // Set w to one.
    TPoint = XMVectorInsert<0, 0, 0, 0, 1>(TPoint, XMVectorSplatOne());

    XMVECTOR Zero = XMVectorZero();
    XMVECTOR Outside = Zero;

    // Test point against each plane of the frustum.
    for (size_t i = 0; i < 6; ++i)
    {
        XMVECTOR Dot = XMVector4Dot(TPoint, Planes[i]);
        Outside = XMVectorOrInt(Outside, XMVectorGreater(Dot, Zero));
    }

    return XMVector4NotEqualInt(Outside, XMVectorTrueInt()) ? CONTAINS : DISJOINT;
}


//-----------------------------------------------------------------------------
// Triangle vs frustum test.
//-----------------------------------------------------------------------------
_Use_decl_annotations_
ContainmentType XM_CALLCONV BoundingFrustum::Contains(FXMVECTOR V0, FXMVECTOR V1, FXMVECTOR V2) const noexcept
{
    // Load origin and orientation of the frustum.
    XMVECTOR vOrigin = XMLoadFloat3(&Origin);
    XMVECTOR vOrientation = XMLoadFloat4(&Orientation);

    // Create 6 planes (do it inline to encourage use of registers)
    XMVECTOR NearPlane = XMVectorSet(0.0f, 0.0f, -1.0f, Near);
    NearPlane = DirectX::Internal::XMPlaneTransform(NearPlane, vOrientation, vOrigin);
    NearPlane = XMPlaneNormalize(NearPlane);

    XMVECTOR FarPlane = XMVectorSet(0.0f, 0.0f, 1.0f, -Far);
    FarPlane = DirectX::Internal::XMPlaneTransform(FarPlane, vOrientation, vOrigin);
    FarPlane = XMPlaneNormalize(FarPlane);

    XMVECTOR RightPlane = XMVectorSet(1.0f, 0.0f, -RightSlope, 0.0f);
    RightPlane = DirectX::Internal::XMPlaneTransform(RightPlane, vOrientation, vOrigin);
    RightPlane = XMPlaneNormalize(RightPlane);

    XMVECTOR LeftPlane = XMVectorSet(-1.0f, 0.0f, LeftSlope, 0.0f);
    LeftPlane = DirectX::Internal::XMPlaneTransform(LeftPlane, vOrientation, vOrigin);
    LeftPlane = XMPlaneNormalize(LeftPlane);

    XMVECTOR TopPlane = XMVectorSet(0.0f, 1.0f, -TopSlope, 0.0f);
    TopPlane = DirectX::Internal::XMPlaneTransform(TopPlane, vOrientation, vOrigin);
    TopPlane = XMPlaneNormalize(TopPlane);

    XMVECTOR BottomPlane = XMVectorSet(0.0f, -1.0f, BottomSlope, 0.0f);
    BottomPlane = DirectX::Internal::XMPlaneTransform(BottomPlane, vOrientation, vOrigin);
    BottomPlane = XMPlaneNormalize(BottomPlane);

    return TriangleTests::ContainedBy(V0, V1, V2, NearPlane, FarPlane, RightPlane, LeftPlane, TopPlane, BottomPlane);
}


//-----------------------------------------------------------------------------
_Use_decl_annotations_
ContainmentType BoundingFrustum::Contains(const BoundingSphere& sh) const noexcept
{
    // Load origin and orientation of the frustum.
    XMVECTOR vOrigin = XMLoadFloat3(&Origin);
    XMVECTOR vOrientation = XMLoadFloat4(&Orientation);

    // Create 6 planes (do it inline to encourage use of registers)
    XMVECTOR NearPlane = XMVectorSet(0.0f, 0.0f, -1.0f, Near);
    NearPlane = DirectX::Internal::XMPlaneTransform(NearPlane, vOrientation, vOrigin);
    NearPlane = XMPlaneNormalize(NearPlane);

    XMVECTOR FarPlane = XMVectorSet(0.0f, 0.0f, 1.0f, -Far);
    FarPlane = DirectX::Internal::XMPlaneTransform(FarPlane, vOrientation, vOrigin);
    FarPlane = XMPlaneNormalize(FarPlane);

    XMVECTOR RightPlane = XMVectorSet(1.0f, 0.0f, -RightSlope, 0.0f);
    RightPlane = DirectX::Internal::XMPlaneTransform(RightPlane, vOrientation, vOrigin);
    RightPlane = XMPlaneNormalize(RightPlane);

    XMVECTOR LeftPlane = XMVectorSet(-1.0f, 0.0f, LeftSlope, 0.0f);
    LeftPlane = DirectX::Internal::XMPlaneTransform(LeftPlane, vOrientation, vOrigin);
    LeftPlane = XMPlaneNormalize(LeftPlane);

    XMVECTOR TopPlane = XMVectorSet(0.0f, 1.0f, -TopSlope, 0.0f);
    TopPlane = DirectX::Internal::XMPlaneTransform(TopPlane, vOrientation, vOrigin);
    TopPlane = XMPlaneNormalize(TopPlane);

    XMVECTOR BottomPlane = XMVectorSet(0.0f, -1.0f, BottomSlope, 0.0f);
    BottomPlane = DirectX::Internal::XMPlaneTransform(BottomPlane, vOrientation, vOrigin);
    BottomPlane = XMPlaneNormalize(BottomPlane);

    return sh.ContainedBy(NearPlane, FarPlane, RightPlane, LeftPlane, TopPlane, BottomPlane);
}


//-----------------------------------------------------------------------------
_Use_decl_annotations_
ContainmentType BoundingFrustum::Contains(const BoundingBox& box) const noexcept
{
    // Load origin and orientation of the frustum.
    XMVECTOR vOrigin = XMLoadFloat3(&Origin);
    XMVECTOR vOrientation = XMLoadFloat4(&Orientation);

    // Create 6 planes (do it inline to encourage use of registers)
    XMVECTOR NearPlane = XMVectorSet(0.0f, 0.0f, -1.0f, Near);
    NearPlane = DirectX::Internal::XMPlaneTransform(NearPlane, vOrientation, vOrigin);
    NearPlane = XMPlaneNormalize(NearPlane);

    XMVECTOR FarPlane = XMVectorSet(0.0f, 0.0f, 1.0f, -Far);
    FarPlane = DirectX::Internal::XMPlaneTransform(FarPlane, vOrientation, vOrigin);
    FarPlane = XMPlaneNormalize(FarPlane);

    XMVECTOR RightPlane = XMVectorSet(1.0f, 0.0f, -RightSlope, 0.0f);
    RightPlane = DirectX::Internal::XMPlaneTransform(RightPlane, vOrientation, vOrigin);
    RightPlane = XMPlaneNormalize(RightPlane);

    XMVECTOR LeftPlane = XMVectorSet(-1.0f, 0.0f, LeftSlope, 0.0f);
    LeftPlane = DirectX::Internal::XMPlaneTransform(LeftPlane, vOrientation, vOrigin);
    LeftPlane = XMPlaneNormalize(LeftPlane);

    XMVECTOR TopPlane = XMVectorSet(0.0f, 1.0f, -TopSlope, 0.0f);
    TopPlane = DirectX::Internal::XMPlaneTransform(TopPlane, vOrientation, vOrigin);
    TopPlane = XMPlaneNormalize(TopPlane);

    XMVECTOR BottomPlane = XMVectorSet(0.0f, -1.0f, BottomSlope, 0.0f);
    BottomPlane = DirectX::Internal::XMPlaneTransform(BottomPlane, vOrientation, vOrigin);
    BottomPlane = XMPlaneNormalize(BottomPlane);

    return box.ContainedBy(NearPlane, FarPlane, RightPlane, LeftPlane, TopPlane, BottomPlane);
}


//-----------------------------------------------------------------------------
_Use_decl_annotations_
ContainmentType BoundingFrustum::Contains(const BoundingOrientedBox& box) const noexcept
{
    // Load origin and orientation of the frustum.
    XMVECTOR vOrigin = XMLoadFloat3(&Origin);
    XMVECTOR vOrientation = XMLoadFloat4(&Orientation);

    // Create 6 planes (do it inline to encourage use of registers)
    XMVECTOR NearPlane = XMVectorSet(0.0f, 0.0f, -1.0f, Near);
    NearPlane = DirectX::Internal::XMPlaneTransform(NearPlane, vOrientation, vOrigin);
    NearPlane = XMPlaneNormalize(NearPlane);

    XMVECTOR FarPlane = XMVectorSet(0.0f, 0.0f, 1.0f, -Far);
    FarPlane = DirectX::Internal::XMPlaneTransform(FarPlane, vOrientation, vOrigin);
    FarPlane = XMPlaneNormalize(FarPlane);

    XMVECTOR RightPlane = XMVectorSet(1.0f, 0.0f, -RightSlope, 0.0f);
    RightPlane = DirectX::Internal::XMPlaneTransform(RightPlane, vOrientation, vOrigin);
    RightPlane = XMPlaneNormalize(RightPlane);

    XMVECTOR LeftPlane = XMVectorSet(-1.0f, 0.0f, LeftSlope, 0.0f);
    LeftPlane = DirectX::Internal::XMPlaneTransform(LeftPlane, vOrientation, vOrigin);
    LeftPlane = XMPlaneNormalize(LeftPlane);

    XMVECTOR TopPlane = XMVectorSet(0.0f, 1.0f, -TopSlope, 0.0f);
    TopPlane = DirectX::Internal::XMPlaneTransform(TopPlane, vOrientation, vOrigin);
    TopPlane = XMPlaneNormalize(TopPlane);

    XMVECTOR BottomPlane = XMVectorSet(0.0f, -1.0f, BottomSlope, 0.0f);
    BottomPlane = DirectX::Internal::XMPlaneTransform(BottomPlane, vOrientation, vOrigin);
    BottomPlane = XMPlaneNormalize(BottomPlane);

    return box.ContainedBy(NearPlane, FarPlane, RightPlane, LeftPlane, TopPlane, BottomPlane);
}


//-----------------------------------------------------------------------------
_Use_decl_annotations_
ContainmentType BoundingFrustum::Contains(const BoundingFrustum& fr) const noexcept
{
    // Load origin and orientation of the frustum.
    XMVECTOR vOrigin = XMLoadFloat3(&Origin);
    XMVECTOR vOrientation = XMLoadFloat4(&Orientation);

    // Create 6 planes (do it inline to encourage use of registers)
    XMVECTOR NearPlane = XMVectorSet(0.0f, 0.0f, -1.0f, Near);
    NearPlane = DirectX::Internal::XMPlaneTransform(NearPlane, vOrientation, vOrigin);
    NearPlane = XMPlaneNormalize(NearPlane);

    XMVECTOR FarPlane = XMVectorSet(0.0f, 0.0f, 1.0f, -Far);
    FarPlane = DirectX::Internal::XMPlaneTransform(FarPlane, vOrientation, vOrigin);
    FarPlane = XMPlaneNormalize(FarPlane);

    XMVECTOR RightPlane = XMVectorSet(1.0f, 0.0f, -RightSlope, 0.0f);
    RightPlane = DirectX::Internal::XMPlaneTransform(RightPlane, vOrientation, vOrigin);
    RightPlane = XMPlaneNormalize(RightPlane);

    XMVECTOR LeftPlane = XMVectorSet(-1.0f, 0.0f, LeftSlope, 0.0f);
    LeftPlane = DirectX::Internal::XMPlaneTransform(LeftPlane, vOrientation, vOrigin);
    LeftPlane = XMPlaneNormalize(LeftPlane);

    XMVECTOR TopPlane = XMVectorSet(0.0f, 1.0f, -TopSlope, 0.0f);
    TopPlane = DirectX::Internal::XMPlaneTransform(TopPlane, vOrientation, vOrigin);
    TopPlane = XMPlaneNormalize(TopPlane);

    XMVECTOR BottomPlane = XMVectorSet(0.0f, -1.0f, BottomSlope, 0.0f);
    BottomPlane = DirectX::Internal::XMPlaneTransform(BottomPlane, vOrientation, vOrigin);
    BottomPlane = XMPlaneNormalize(BottomPlane);

    return fr.ContainedBy(NearPlane, FarPlane, RightPlane, LeftPlane, TopPlane, BottomPlane);
}


}

//
//
///////////////////////////////////////////////////////////////
