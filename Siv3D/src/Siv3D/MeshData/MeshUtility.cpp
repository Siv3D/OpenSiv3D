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

# include "MeshUtility.hpp"
using namespace DirectX;

namespace s3d
{
    namespace MeshUtility
    {
        ///////////////////////////////////////////////////////////////
        //
        //

        //
        //  DirectX Mesh Geometry Library
        //
        //  Copyright (c) 2014-2021 Microsoft Corp
        //
        //  Permission is hereby granted, free of charge, to any person obtaining a copy of this
        //  software and associated documentation files (the "Software"), to deal in the Software
        //  without restriction, including without limitation the rights to use, copy, modify,
        //  merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
        //  permit persons to whom the Software is furnished to do so, subject to the following
        //  conditions:
        //
        //  The above copyright notice and this permission notice shall be included in all copies
        //  or substantial portions of the Software.
        //
        //  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
        //  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
        //  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
        //  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
        //  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
        //  OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

        # if !SIV3D_PLATFORM(WINDOWS)

        struct aligned_deleter { void operator()(void* p) noexcept { free(p); } };

        using ScopedAlignedArrayFloat = std::unique_ptr<float[], aligned_deleter>;

        inline ScopedAlignedArrayFloat make_AlignedArrayFloat(uint64_t count)
        {
            uint64_t size = sizeof(float) * count;
            size = (size + 15u) & ~0xF;
            if (size > static_cast<uint64_t>(UINT32_MAX))
                return nullptr;

            auto ptr = aligned_alloc(16, static_cast<size_t>(size)      );
            return ScopedAlignedArrayFloat(static_cast<float*>(ptr));
        }

        using ScopedAlignedArrayXMVECTOR = std::unique_ptr<DirectX::XMVECTOR[], aligned_deleter>;

        inline ScopedAlignedArrayXMVECTOR make_AlignedArrayXMVECTOR(uint64_t count)
        {
            uint64_t size = sizeof(DirectX::XMVECTOR) * count;
            if (size > static_cast<uint64_t>(UINT32_MAX))
                return nullptr;
            auto ptr = aligned_alloc(16, static_cast<size_t>(size));
            return ScopedAlignedArrayXMVECTOR(static_cast<DirectX::XMVECTOR*>(ptr));
        }

        # else
        //---------------------------------------------------------------------------------

        struct aligned_deleter { void operator()(void* p) noexcept { _aligned_free(p); } };

        using ScopedAlignedArrayFloat = std::unique_ptr<float[], aligned_deleter>;

        inline ScopedAlignedArrayFloat make_AlignedArrayFloat(uint64_t count)
        {
            uint64_t size = sizeof(float) * count;
            if (size > static_cast<uint64_t>(UINT32_MAX))
                return nullptr;
            auto ptr = _aligned_malloc(static_cast<size_t>(size), 16);
            return ScopedAlignedArrayFloat(static_cast<float*>(ptr));
        }

        using ScopedAlignedArrayXMVECTOR = std::unique_ptr<DirectX::XMVECTOR[], aligned_deleter>;

        inline ScopedAlignedArrayXMVECTOR make_AlignedArrayXMVECTOR(uint64_t count)
        {
            uint64_t size = sizeof(DirectX::XMVECTOR) * count;
            if (size > static_cast<uint64_t>(UINT32_MAX))
                return nullptr;
            auto ptr = _aligned_malloc(static_cast<size_t>(size), 16);
            return ScopedAlignedArrayXMVECTOR(static_cast<DirectX::XMVECTOR*>(ptr));
        }

        #endif // WIN32

        //---------------------------------------------------------------------------------
        // Compute normals with weighting by face area
        //---------------------------------------------------------------------------------
        template<class index_t>
        bool ComputeNormalsWeightedByArea(
            _In_reads_(nFaces * 3) const index_t* indices, size_t nFaces,
            _In_reads_(nVerts) const XMFLOAT3* positions, size_t nVerts,
            bool cw, _Out_writes_(nVerts) XMFLOAT3* normals) noexcept
        {
            auto temp = make_AlignedArrayXMVECTOR(nVerts);
            if (!temp)
                return false;

            XMVECTOR* vertNormals = temp.get();
            memset(vertNormals, 0, sizeof(XMVECTOR) * nVerts);

            for (size_t face = 0; face < nFaces; ++face)
            {
                index_t i0 = indices[face * 3];
                index_t i1 = indices[face * 3 + 1];
                index_t i2 = indices[face * 3 + 2];

                if (i0 == index_t(-1)
                    || i1 == index_t(-1)
                    || i2 == index_t(-1))
                    continue;

                if (i0 >= nVerts
                    || i1 >= nVerts
                    || i2 >= nVerts)
                    return false;

                XMVECTOR p0 = XMLoadFloat3(&positions[i0]);
                XMVECTOR p1 = XMLoadFloat3(&positions[i1]);
                XMVECTOR p2 = XMLoadFloat3(&positions[i2]);

                XMVECTOR u = XMVectorSubtract(p1, p0);
                XMVECTOR v = XMVectorSubtract(p2, p0);

                XMVECTOR faceNormal = XMVector3Normalize(XMVector3Cross(u, v));

                // Corner 0 -> 1 - 0, 2 - 0
                XMVECTOR w0 = XMVector3Cross(u, v);
                w0 = XMVector3Length(w0);

                // Corner 1 -> 2 - 1, 0 - 1
                XMVECTOR c = XMVectorSubtract(p2, p1);
                XMVECTOR d = XMVectorSubtract(p0, p1);
                XMVECTOR w1 = XMVector3Cross(c, d);
                w1 = XMVector3Length(w1);

                // Corner 2 -> 0 - 2, 1 - 2
                XMVECTOR e = XMVectorSubtract(p0, p2);
                XMVECTOR f = XMVectorSubtract(p1, p2);
                XMVECTOR w2 = XMVector3Cross(e, f);
                w2 = XMVector3Length(w2);

                vertNormals[i0] = XMVectorMultiplyAdd(faceNormal, w0, vertNormals[i0]);
                vertNormals[i1] = XMVectorMultiplyAdd(faceNormal, w1, vertNormals[i1]);
                vertNormals[i2] = XMVectorMultiplyAdd(faceNormal, w2, vertNormals[i2]);
            }

            // Store results
            if (cw)
            {
                for (size_t vert = 0; vert < nVerts; ++vert)
                {
                    XMVECTOR n = XMVector3Normalize(vertNormals[vert]);
                    n = XMVectorNegate(n);
                    XMStoreFloat3(&normals[vert], n);
                }
            }
            else
            {
                for (size_t vert = 0; vert < nVerts; ++vert)
                {
                    XMVECTOR n = XMVector3Normalize(vertNormals[vert]);
                    XMStoreFloat3(&normals[vert], n);
                }
            }

            return true;
        }

        //---------------------------------------------------------------------------------
        // Compute normals with equal weighting
        //---------------------------------------------------------------------------------
        template<class index_t>
        bool ComputeNormalsEqualWeight(
            _In_reads_(nFaces * 3) const index_t* indices, size_t nFaces,
            _In_reads_(nVerts) const XMFLOAT3* positions, size_t nVerts,
            bool cw, _Out_writes_(nVerts) XMFLOAT3* normals) noexcept
        {
            auto temp = make_AlignedArrayXMVECTOR(nVerts);
            if (!temp)
                return false;

            XMVECTOR* vertNormals = temp.get();
            memset(vertNormals, 0, sizeof(XMVECTOR) * nVerts);

            for (size_t face = 0; face < nFaces; ++face)
            {
                index_t i0 = indices[face * 3];
                index_t i1 = indices[face * 3 + 1];
                index_t i2 = indices[face * 3 + 2];

                if (i0 == index_t(-1)
                    || i1 == index_t(-1)
                    || i2 == index_t(-1))
                    continue;

                if (i0 >= nVerts
                    || i1 >= nVerts
                    || i2 >= nVerts)
                    return false;

                XMVECTOR p1 = XMLoadFloat3(&positions[i0]);
                XMVECTOR p2 = XMLoadFloat3(&positions[i1]);
                XMVECTOR p3 = XMLoadFloat3(&positions[i2]);

                XMVECTOR u = XMVectorSubtract(p2, p1);
                XMVECTOR v = XMVectorSubtract(p3, p1);

                XMVECTOR faceNormal = XMVector3Normalize(XMVector3Cross(u, v));

                vertNormals[i0] = XMVectorAdd(vertNormals[i0], faceNormal);
                vertNormals[i1] = XMVectorAdd(vertNormals[i1], faceNormal);
                vertNormals[i2] = XMVectorAdd(vertNormals[i2], faceNormal);
            }

            // Store results
            if (cw)
            {
                for (size_t vert = 0; vert < nVerts; ++vert)
                {
                    XMVECTOR n = XMVector3Normalize(vertNormals[vert]);
                    n = XMVectorNegate(n);
                    XMStoreFloat3(&normals[vert], n);
                }
            }
            else
            {
                for (size_t vert = 0; vert < nVerts; ++vert)
                {
                    XMVECTOR n = XMVector3Normalize(vertNormals[vert]);
                    XMStoreFloat3(&normals[vert], n);
                }
            }

            return true;
        }

        //---------------------------------------------------------------------------------
        // Compute normals with weighting by angle
        //---------------------------------------------------------------------------------
        template<class index_t>
        bool ComputeNormalsWeightedByAngle(
            _In_reads_(nFaces * 3) const index_t* indices, size_t nFaces,
            _In_reads_(nVerts) const XMFLOAT3* positions, size_t nVerts,
            bool cw, _Out_writes_(nVerts) XMFLOAT3* normals) noexcept
        {
            auto temp = make_AlignedArrayXMVECTOR(nVerts);
            if (!temp)
                return false;

            XMVECTOR* vertNormals = temp.get();
            memset(vertNormals, 0, sizeof(XMVECTOR) * nVerts);

            for (size_t face = 0; face < nFaces; ++face)
            {
                index_t i0 = indices[face * 3];
                index_t i1 = indices[face * 3 + 1];
                index_t i2 = indices[face * 3 + 2];

                if (i0 == index_t(-1)
                    || i1 == index_t(-1)
                    || i2 == index_t(-1))
                    continue;

                if (i0 >= nVerts
                    || i1 >= nVerts
                    || i2 >= nVerts)
                    return false;

                XMVECTOR p0 = XMLoadFloat3(&positions[i0]);
                XMVECTOR p1 = XMLoadFloat3(&positions[i1]);
                XMVECTOR p2 = XMLoadFloat3(&positions[i2]);

                XMVECTOR u = XMVectorSubtract(p1, p0);
                XMVECTOR v = XMVectorSubtract(p2, p0);

                XMVECTOR faceNormal = XMVector3Normalize(XMVector3Cross(u, v));

                // Corner 0 -> 1 - 0, 2 - 0
                XMVECTOR a = XMVector3Normalize(u);
                XMVECTOR b = XMVector3Normalize(v);
                XMVECTOR w0 = XMVector3Dot(a, b);
                w0 = XMVectorClamp(w0, g_XMNegativeOne, g_XMOne);
                w0 = XMVectorACos(w0);

                // Corner 1 -> 2 - 1, 0 - 1
                XMVECTOR c = XMVector3Normalize(XMVectorSubtract(p2, p1));
                XMVECTOR d = XMVector3Normalize(XMVectorSubtract(p0, p1));
                XMVECTOR w1 = XMVector3Dot(c, d);
                w1 = XMVectorClamp(w1, g_XMNegativeOne, g_XMOne);
                w1 = XMVectorACos(w1);

                // Corner 2 -> 0 - 2, 1 - 2
                XMVECTOR e = XMVector3Normalize(XMVectorSubtract(p0, p2));
                XMVECTOR f = XMVector3Normalize(XMVectorSubtract(p1, p2));
                XMVECTOR w2 = XMVector3Dot(e, f);
                w2 = XMVectorClamp(w2, g_XMNegativeOne, g_XMOne);
                w2 = XMVectorACos(w2);

                vertNormals[i0] = XMVectorMultiplyAdd(faceNormal, w0, vertNormals[i0]);
                vertNormals[i1] = XMVectorMultiplyAdd(faceNormal, w1, vertNormals[i1]);
                vertNormals[i2] = XMVectorMultiplyAdd(faceNormal, w2, vertNormals[i2]);
            }

            // Store results
            if (cw)
            {
                for (size_t vert = 0; vert < nVerts; ++vert)
                {
                    XMVECTOR n = XMVector3Normalize(vertNormals[vert]);
                    n = XMVectorNegate(n);
                    XMStoreFloat3(&normals[vert], n);
                }
            }
            else
            {
                for (size_t vert = 0; vert < nVerts; ++vert)
                {
                    XMVECTOR n = XMVector3Normalize(vertNormals[vert]);
                    XMStoreFloat3(&normals[vert], n);
                }
            }

            return true;
        }

        //=====================================================================================
        // Entry-points
        //=====================================================================================

        _Use_decl_annotations_
        bool ComputeNormals(
            const uint32_t* indices,
            size_t nFaces,
            const XMFLOAT3* positions,
            size_t nVerts,
            CNORM_FLAGS flags,
            XMFLOAT3* normals) noexcept
        {
            if (!indices || !positions || !nFaces || !nVerts || !normals)
                return false;

            if (nVerts >= UINT32_MAX)
                return false;

            if ((uint64_t(nFaces) * 3) >= UINT32_MAX)
                return false;

            bool cw = (flags & CNORM_WIND_CW) ? true : false;

            if (flags & CNORM_WEIGHT_BY_AREA)
            {
                return ComputeNormalsWeightedByArea<uint32_t>(indices, nFaces, positions, nVerts, cw, normals);
            }
            else if (flags & CNORM_WEIGHT_EQUAL)
            {
                return ComputeNormalsEqualWeight<uint32_t>(indices, nFaces, positions, nVerts, cw, normals);
            }
            else
            {
                return ComputeNormalsWeightedByAngle<uint32_t>(indices, nFaces, positions, nVerts, cw, normals);
            }
        }
        //
        //
        ///////////////////////////////////////////////////////////////
    }
}
