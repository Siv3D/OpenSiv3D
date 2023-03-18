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

			auto ptr = static_cast<void*>(AlignedMalloc<DirectX::XMVECTOR>(count));
			return ScopedAlignedArrayFloat(static_cast<float*>(ptr));
		}

# ifdef __GNUC__
#	pragma GCC diagnostic push
#	pragma GCC diagnostic ignored "-Wignored-attributes"
# endif
		using ScopedAlignedArrayXMVECTOR = std::unique_ptr<DirectX::XMVECTOR[], aligned_deleter>;

# ifdef __GNUC__
#	pragma GCC diagnostic pop
# endif

		inline ScopedAlignedArrayXMVECTOR make_AlignedArrayXMVECTOR(uint64_t count)
		{
			uint64_t size = sizeof(DirectX::XMVECTOR) * count;
			if (size > static_cast<uint64_t>(UINT32_MAX))
				return nullptr;
			auto ptr = static_cast<void*>(AlignedMalloc<DirectX::XMVECTOR>(count));
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

		//---------------------------------------------------------------------------------
		// Utilities
		//---------------------------------------------------------------------------------
		struct vertexHashEntry
		{
			XMFLOAT3            v;
			uint32_t            index;
			vertexHashEntry *   next;
		};

		struct edgeHashEntry
		{
			uint32_t        v1;
			uint32_t        v2;
			uint32_t        vOther;
			uint32_t        face;
			edgeHashEntry* next;
		};

		constexpr uint32_t UNUSED32 = uint32_t(-1);
		constexpr size_t c_MaxStride = 2048;

		// <algorithm> std::make_heap doesn't match D3DX10 so we use the same algorithm here
		void MakeXHeap(
			_Out_writes_(nVerts) uint32_t *index,
			_In_reads_(nVerts) const XMFLOAT3* positions, size_t nVerts) noexcept
		{
			for (uint32_t vert = 0; vert < nVerts; ++vert)
			{
				index[vert] = vert;
			}

			if (nVerts > 1)
			{
				// Create the heap
				uint32_t iulLim = uint32_t(nVerts);

				for (uint32_t vert = uint32_t(nVerts >> 1); --vert != uint32_t(-1); )
				{
					// Percolate down
					uint32_t iulI = vert;
					uint32_t iulJ = vert + vert + 1;
					uint32_t ulT = index[iulI];

					while (iulJ < iulLim)
					{
						uint32_t ulJ = index[iulJ];

						if (iulJ + 1 < iulLim)
						{
							uint32_t ulJ1 = index[iulJ + 1];
							if (positions[ulJ1].x <= positions[ulJ].x)
							{
								iulJ++;
								ulJ = ulJ1;
							}
						}

						if (positions[ulJ].x > positions[ulT].x)
							break;

						index[iulI] = index[iulJ];
						iulI = iulJ;
						iulJ += iulJ + 1;
					}

					index[iulI] = ulT;
				}

				// Sort the heap
				while (--iulLim != uint32_t(-1))
				{
					uint32_t ulT = index[iulLim];
					index[iulLim] = index[0];

					// Percolate down
					uint32_t iulI = 0;
					uint32_t iulJ = 1;

					while (iulJ < iulLim)
					{
						_Analysis_assume_(iulJ < nVerts);
						uint32_t ulJ = index[iulJ];

						if (iulJ + 1 < iulLim)
						{
							uint32_t ulJ1 = index[iulJ + 1];
							if (positions[ulJ1].x <= positions[ulJ].x)
							{
								iulJ++;
								ulJ = ulJ1;
							}
						}

						if (positions[ulJ].x > positions[ulT].x)
							break;

						index[iulI] = index[iulJ];
						iulI = iulJ;
						iulJ += iulJ + 1;
					}

					assert(iulI < nVerts);
					_Analysis_assume_(iulI < nVerts);
					index[iulI] = ulT;
				}
			}
		}

		//---------------------------------------------------------------------------------
		// PointRep computation
		//---------------------------------------------------------------------------------
		template<class index_t>
		bool GeneratePointReps(
			_In_reads_(nFaces * 3) const index_t* indices, size_t nFaces,
			_In_reads_(nVerts) const XMFLOAT3* positions, size_t nVerts,
			float epsilon,
			_Out_writes_(nVerts) uint32_t* pointRep) noexcept
		{
			std::unique_ptr<uint32_t[]> temp(new (std::nothrow) uint32_t[nVerts + nFaces * 3]);
			if (!temp)
				return false;

			uint32_t* vertexToCorner = temp.get();
			uint32_t* vertexCornerList = temp.get() + nVerts;

			memset(vertexToCorner, 0xff, sizeof(uint32_t) * nVerts);
			memset(vertexCornerList, 0xff, sizeof(uint32_t) * nFaces * 3);

			// build initial lists and validate indices
			for (size_t j = 0; j < (nFaces * 3); ++j)
			{
				index_t k = indices[j];
				if (k == index_t(-1))
					continue;

				if (k >= nVerts)
					return false;

				vertexCornerList[j] = vertexToCorner[k];
				vertexToCorner[k] = uint32_t(j);
			}

			if (epsilon == 0.f)
			{
				auto hashSize = std::max<size_t>(nVerts / 3, 1);

				std::unique_ptr<vertexHashEntry*[]> hashTable(new (std::nothrow) vertexHashEntry*[hashSize]);
				if (!hashTable)
					return false;

				memset(hashTable.get(), 0, sizeof(vertexHashEntry*) * hashSize);

				std::unique_ptr<vertexHashEntry[]> hashEntries(new (std::nothrow) vertexHashEntry[nVerts]);
				if (!hashEntries)
					return false;

				uint32_t freeEntry = 0;

				for (size_t vert = 0; vert < nVerts; ++vert)
				{
					auto px = reinterpret_cast<const uint32_t*>(&positions[vert].x);
					auto py = reinterpret_cast<const uint32_t*>(&positions[vert].y);
					auto pz = reinterpret_cast<const uint32_t*>(&positions[vert].z);
					uint32_t hashKey = (*px + *py + *pz) % uint32_t(hashSize);

					uint32_t found = UNUSED32;

					for (auto current = hashTable[hashKey]; current != nullptr; current = current->next)
					{
						if (current->v.x == positions[vert].x
							&& current->v.y == positions[vert].y
							&& current->v.z == positions[vert].z)
						{
							uint32_t head = vertexToCorner[vert];

							bool ispresent = false;

							while (head != UNUSED32)
							{
								uint32_t face = head / 3;
								assert(face < nFaces);
								_Analysis_assume_(face < nFaces);

								assert((indices[face * 3] == vert) || (indices[face * 3 + 1] == vert) || (indices[face * 3 + 2] == vert));

								if ((indices[face * 3] == current->index) || (indices[face * 3 + 1] == current->index) || (indices[face * 3 + 2] == current->index))
								{
									ispresent = true;
									break;
								}

								head = vertexCornerList[head];
							}

							if (!ispresent)
							{
								found = current->index;
								break;
							}
						}
					}

					if (found != UNUSED32)
					{
						pointRep[vert] = found;
					}
					else
					{
						assert(freeEntry < nVerts);
						_Analysis_assume_(freeEntry < nVerts);

						auto newEntry = &hashEntries[freeEntry];
						++freeEntry;

						newEntry->v = positions[vert];
						newEntry->index = uint32_t(vert);
						newEntry->next = hashTable[hashKey];
						hashTable[hashKey] = newEntry;

						pointRep[vert] = uint32_t(vert);
					}
				}

				assert(freeEntry <= nVerts);

				return true;
			}
			else
			{
				std::unique_ptr<uint32_t[]> xorder(new (std::nothrow) uint32_t[nVerts]);
				if (!xorder)
					return false;

				// order in descending order
				MakeXHeap(xorder.get(), positions, nVerts);

				memset(pointRep, 0xff, sizeof(uint32_t) * nVerts);

				XMVECTOR vepsilon = XMVectorReplicate(epsilon * epsilon);

				uint32_t head = 0;
				uint32_t tail = 0;

				while (tail < nVerts)
				{
					// move head until just out of epsilon
					while ((head < nVerts)
						&& ((positions[tail].x - positions[head].x) <= epsilon))
					{
						++head;
					}

					// check new tail against all points up to the head
					uint32_t tailIndex = xorder[tail];
					assert(tailIndex < nVerts);
					_Analysis_assume_(tailIndex < nVerts);
					if (pointRep[tailIndex] == UNUSED32)
					{
						pointRep[tailIndex] = tailIndex;

						XMVECTOR outer = XMLoadFloat3(&positions[tailIndex]);

						for (uint32_t current = tail + 1; current < head; ++current)
						{
							uint32_t curIndex = xorder[current];
							assert(curIndex < nVerts);
							_Analysis_assume_(curIndex < nVerts);

							// if the point is already assigned, ignore it
							if (pointRep[curIndex] == UNUSED32)
							{
								XMVECTOR inner = XMLoadFloat3(&positions[curIndex]);

								XMVECTOR diff = XMVector3LengthSq(XMVectorSubtract(inner, outer));

								if (XMVector2Less(diff, vepsilon))
								{
									uint32_t headvc = vertexToCorner[tailIndex];

									bool ispresent = false;

									while (headvc != UNUSED32)
									{
										uint32_t face = headvc / 3;
										assert(face < nFaces);
										_Analysis_assume_(face < nFaces);

										assert((indices[face * 3] == tailIndex) || (indices[face * 3 + 1] == tailIndex) || (indices[face * 3 + 2] == tailIndex));

										if ((indices[face * 3] == curIndex) || (indices[face * 3 + 1] == curIndex) || (indices[face * 3 + 2] == curIndex))
										{
											ispresent = true;
											break;
										}

										headvc = vertexCornerList[headvc];
									}

									if (!ispresent)
									{
										pointRep[curIndex] = tailIndex;
									}
								}
							}
						}
					}

					++tail;
				}

				return true;
			}
		}


		//---------------------------------------------------------------------------------
		// Convert PointRep to Adjacency
		//---------------------------------------------------------------------------------
		template<class index_t>
		bool ConvertPointRepsToAdjacencyImpl(
			_In_reads_(nFaces * 3) const index_t* indices, size_t nFaces,
			_In_reads_(nVerts) const XMFLOAT3* positions, size_t nVerts,
			_In_reads_(nVerts) const uint32_t* pointRep,
			_Out_writes_(nFaces * 3) uint32_t* adjacency) noexcept
		{
			auto hashSize = std::max<size_t>(nVerts / 3, 1);

			std::unique_ptr<edgeHashEntry*[]> hashTable(new (std::nothrow) edgeHashEntry*[hashSize]);
			if (!hashTable)
				return false;

			memset(hashTable.get(), 0, sizeof(edgeHashEntry*) * hashSize);

			std::unique_ptr<edgeHashEntry[]> hashEntries(new (std::nothrow) edgeHashEntry[3 * nFaces]);
			if (!hashEntries)
				return false;

			uint32_t freeEntry = 0;

			// add face edges to hash table and validate indices
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

				uint32_t v1 = pointRep[i0];
				uint32_t v2 = pointRep[i1];
				uint32_t v3 = pointRep[i2];

				// filter out degenerate triangles
				if (v1 == v2 || v1 == v3 || v2 == v3)
					continue;

				for (uint32_t point = 0; point < 3; ++point)
				{
					uint32_t va = pointRep[indices[face * 3 + point]];
					uint32_t vb = pointRep[indices[face * 3 + ((point + 1) % 3)]];
					uint32_t vOther = pointRep[indices[face * 3 + ((point + 2) % 3)]];

					uint32_t hashKey = va % hashSize;

					assert(freeEntry < (3 * nFaces));
					_Analysis_assume_(freeEntry < (3 * nFaces));

					auto newEntry = &hashEntries[freeEntry];
					++freeEntry;

					newEntry->v1 = va;
					newEntry->v2 = vb;
					newEntry->vOther = vOther;
					newEntry->face = uint32_t(face);
					newEntry->next = hashTable[hashKey];
					hashTable[hashKey] = newEntry;
				}
			}

			assert(freeEntry <= (3 * nFaces));

			memset(adjacency, 0xff, sizeof(uint32_t) * nFaces * 3);

			for (size_t face = 0; face < nFaces; ++face)
			{
				index_t i0 = indices[face * 3];
				index_t i1 = indices[face * 3 + 1];
				index_t i2 = indices[face * 3 + 2];

				// filter out unused triangles
				if (i0 == index_t(-1)
					|| i1 == index_t(-1)
					|| i2 == index_t(-1))
					continue;

				assert(i0 < nVerts);
				assert(i1 < nVerts);
				assert(i2 < nVerts);

				_Analysis_assume_(i0 < nVerts);
				_Analysis_assume_(i1 < nVerts);
				_Analysis_assume_(i2 < nVerts);

				uint32_t v1 = pointRep[i0];
				uint32_t v2 = pointRep[i1];
				uint32_t v3 = pointRep[i2];

				// filter out degenerate triangles
				if (v1 == v2 || v1 == v3 || v2 == v3)
					continue;

				for (uint32_t point = 0; point < 3; ++point)
				{
					if (adjacency[face * 3 + point] != UNUSED32)
						continue;

					// see if edge already entered, if not then enter it
					uint32_t va = pointRep[indices[face * 3 + ((point + 1) % 3)]];
					uint32_t vb = pointRep[indices[face * 3 + point]];
					uint32_t vOther = pointRep[indices[face * 3 + ((point + 2) % 3)]];

					uint32_t hashKey = va % hashSize;

					edgeHashEntry* current = hashTable[hashKey];
					edgeHashEntry* prev = nullptr;

					uint32_t foundFace = UNUSED32;

					while (current != nullptr)
					{
						if ((current->v2 == vb) && (current->v1 == va))
						{
							foundFace = current->face;
							break;
						}

						prev = current;
						current = current->next;
					}

					edgeHashEntry* found = current;
					edgeHashEntry* foundPrev = prev;

					float bestDiff = -2.f;

					// Scan for additional matches
					if (current)
					{
						prev = current;
						current = current->next;

						// find 'better' match
						while (current != nullptr)
						{
							if ((current->v2 == vb) && (current->v1 == va))
							{
								XMVECTOR pB1 = XMLoadFloat3(&positions[vb]);
								XMVECTOR pB2 = XMLoadFloat3(&positions[va]);
								XMVECTOR pB3 = XMLoadFloat3(&positions[vOther]);

								XMVECTOR v12 = XMVectorSubtract(pB1, pB2);
								XMVECTOR v13 = XMVectorSubtract(pB1, pB3);

								XMVECTOR bnormal = XMVector3Normalize(XMVector3Cross(v12, v13));

								if (bestDiff == -2.f)
								{
									XMVECTOR pA1 = XMLoadFloat3(&positions[found->v1]);
									XMVECTOR pA2 = XMLoadFloat3(&positions[found->v2]);
									XMVECTOR pA3 = XMLoadFloat3(&positions[found->vOther]);

									v12 = XMVectorSubtract(pA1, pA2);
									v13 = XMVectorSubtract(pA1, pA3);

									XMVECTOR anormal = XMVector3Normalize(XMVector3Cross(v12, v13));

									bestDiff = XMVectorGetX(XMVector3Dot(anormal, bnormal));
								}

								XMVECTOR pA1 = XMLoadFloat3(&positions[current->v1]);
								XMVECTOR pA2 = XMLoadFloat3(&positions[current->v2]);
								XMVECTOR pA3 = XMLoadFloat3(&positions[current->vOther]);

								v12 = XMVectorSubtract(pA1, pA2);
								v13 = XMVectorSubtract(pA1, pA3);

								XMVECTOR anormal = XMVector3Normalize(XMVector3Cross(v12, v13));

								float diff = XMVectorGetX(XMVector3Dot(anormal, bnormal));

								// if face normals are closer, use new match
								if (diff > bestDiff)
								{
									found = current;
									foundPrev = prev;
									foundFace = current->face;
									bestDiff = diff;
								}
							}

							prev = current;
							current = current->next;
						}
					}

					if (foundFace != UNUSED32)
					{
						assert(found != nullptr);

						// remove found face from hash table
						if (foundPrev != nullptr)
						{
							foundPrev->next = found->next;
						}
						else
						{
							hashTable[hashKey] = found->next;
						}

						assert(adjacency[face * 3 + point] == UNUSED32);
						adjacency[face * 3 + point] = foundFace;

						// Check for other edge
						uint32_t hashKey2 = vb % hashSize;

						current = hashTable[hashKey2];
						prev = nullptr;

						while (current != nullptr)
						{
							if ((current->face == uint32_t(face)) && (current->v2 == va) && (current->v1 == vb))
							{
								// trim edge from hash table
								if (prev != nullptr)
								{
									prev->next = current->next;
								}
								else
								{
									hashTable[hashKey2] = current->next;
								}
								break;
							}

							prev = current;
							current = current->next;
						}

						// mark neighbor to point back
						bool linked = false;

						for (uint32_t point2 = 0; point2 < point; ++point2)
						{
							if (foundFace == adjacency[face * 3 + point2])
							{
								linked = true;
								adjacency[face * 3 + point] = UNUSED32;
								break;
							}
						}

						if (!linked)
						{
							uint32_t point2 = 0;
							for (; point2 < 3; ++point2)
							{
								index_t k = indices[foundFace * 3 + point2];
								if (k == index_t(-1))
									continue;

								assert(k < nVerts);
								_Analysis_assume_(k < nVerts);

								if (pointRep[k] == va)
									break;
							}

							if (point2 < 3)
							{
							#ifndef NDEBUG
								uint32_t testPoint = indices[foundFace * 3 + ((point2 + 1) % 3)];
								testPoint = pointRep[testPoint];
								assert(testPoint == vb);
							#endif
								assert(adjacency[foundFace * 3 + point2] == UNUSED32);

								// update neighbor to point back to this face match edge
								adjacency[foundFace * 3 + point2] = uint32_t(face);
							}
						}
					}
				}
			}

			return true;
		}

		_Use_decl_annotations_
		bool GenerateAdjacencyAndPointReps(
			const uint32_t* indices,
			size_t nFaces,
			const XMFLOAT3* positions,
			size_t nVerts,
			float epsilon,
			uint32_t* pointRep,
			uint32_t* adjacency)
		{
			if (!indices || !nFaces || !positions || !nVerts)
				return false;

			if (!pointRep && !adjacency)
				return false;

			if (nVerts >= UINT32_MAX)
				return false;

			if ((uint64_t(nFaces) * 3) >= UINT32_MAX)
				return false;

			std::unique_ptr<uint32_t[]> temp;
			if (!pointRep)
			{
				temp.reset(new (std::nothrow) uint32_t[nVerts]);
				if (!temp)
					return false;

				pointRep = temp.get();
			}

			bool r = GeneratePointReps<uint32_t>(indices, nFaces, positions, nVerts, epsilon, pointRep);
			if (not r)
				return r;

			if (!adjacency)
				return true;

			return ConvertPointRepsToAdjacencyImpl<uint32_t>(indices, nFaces, positions, nVerts, pointRep, adjacency);
		}


		template<class index_t>
		bool WeldVerticesImpl(
			_Inout_updates_all_(nFaces * 3) index_t* indices, size_t nFaces,
			size_t nVerts, _In_reads_(nVerts) const uint32_t* pointRep,
			_Out_writes_opt_(nVerts) uint32_t* vertexRemap,
			const std::function<bool(uint32_t v0, uint32_t v1)>& weldTest)
		{
			std::unique_ptr<uint32_t[]> temp(new (std::nothrow) uint32_t[nVerts * 2]);
			if (!temp)
				return false;

			auto vertexRemapInverse = temp.get();

			auto wedgeList = temp.get() + nVerts;

			for (uint32_t j = 0; j < nVerts; ++j)
			{
				vertexRemapInverse[j] = j;
				wedgeList[j] = j;

				if (vertexRemap)
					vertexRemap[j] = j;
			}

			// Generate wedge list
			bool identity = true;

			for (uint32_t j = 0; j < nVerts; ++j)
			{
				uint32_t pr = pointRep[j];
				if (pr == UNUSED32)
					continue;

				if (pr >= nVerts)
					return false;

				if (pr != j)
				{
					identity = false;

					wedgeList[j] = wedgeList[pr];
					wedgeList[pr] = j;
				}
			}

			if (identity)
			{
				// No candidates for welding, so return now
				return true;
			}

			bool weld = false;

			for (uint32_t vert = 0; vert < nVerts; ++vert)
			{
				if (pointRep[vert] == vert && wedgeList[vert] != vert)
				{
					uint32_t curOuter = vert;
					do
					{
						// if a remapping for the vertex hasn't been found, check to see if it matches any other vertices
						assert(curOuter < nVerts);
						_Analysis_assume_(curOuter < nVerts);
						if (vertexRemapInverse[curOuter] == curOuter)
						{
							uint32_t curInner = wedgeList[vert];
							assert(curInner < nVerts);
							_Analysis_assume_(curInner < nVerts);
							do
							{
								// don't check for equalivalence if indices the same (had better be equal then)
								// and/or if the one being checked is already being remapped
								if ((curInner != curOuter) && (vertexRemapInverse[curInner] == curInner))
								{
									// if the two vertices are equal, then remap one to the other
									if (weldTest(curOuter, curInner))
									{
										// remap the inner vertices to the outer...
										vertexRemapInverse[curInner] = curOuter;

										weld = true;
									}
								}

								curInner = wedgeList[curInner];
							} while (curInner != vert);
						}

						curOuter = wedgeList[curOuter];
					} while (curOuter != vert);
				}
			}

			if (!weld)
				return true;

			// Apply map to indices
			for (uint32_t j = 0; j < nFaces * 3; ++j)
			{
				index_t i = indices[j];
				if (i == index_t(-1))
					continue;

				indices[j] = index_t(vertexRemapInverse[i]);
			}

			// Generate inverse map if requested
			if (vertexRemap)
			{
				memset(vertexRemap, 0xff, sizeof(uint32_t) * nVerts);

				for (uint32_t j = 0; j < nVerts; ++j)
				{
					if (vertexRemapInverse[j] != UNUSED32)
					{
						vertexRemap[vertexRemapInverse[j]] = j;
					}
				}
			}

			return true;
		}

		bool WeldVertices(
			uint32_t* indices, size_t nFaces,
			size_t nVerts, const uint32_t* pointRep,
			uint32_t* vertexRemap,
			std::function<bool(uint32_t v0, uint32_t v1)> weldTest)
		{
			if (!indices || !nFaces || !nVerts || !pointRep)
				return false;

			if (nVerts >= UINT32_MAX)
				return false;

			if ((uint64_t(nFaces) * 3) >= UINT32_MAX)
				return false;

			return WeldVerticesImpl<uint32_t>(indices, nFaces, nVerts, pointRep, vertexRemap, weldTest);
		}











		template<class index_t>
		bool OptimizeVerticesImpl(
			_In_reads_(nFaces * 3) const index_t* indices, size_t nFaces,
			size_t nVerts, _Out_writes_(nVerts) uint32_t* vertexRemap,
			_Out_opt_ size_t* trailingUnused) noexcept
		{
			if (!indices || !nFaces || !nVerts || !vertexRemap)
				return false;

			if (nVerts >= index_t(-1))
				return false;

			if (trailingUnused)
			{
				*trailingUnused = 0;
			}

			if ((uint64_t(nFaces) * 3) >= UINT32_MAX)
				return false;

			std::unique_ptr<uint32_t[]> tempRemap(new (std::nothrow) uint32_t[nVerts]);
			if (!tempRemap)
				return false;

			memset(tempRemap.get(), 0xff, sizeof(uint32_t) * nVerts);

			uint32_t curvertex = 0;
			for (size_t j = 0; j < (nFaces * 3); ++j)
			{
				index_t curindex = indices[j];
				if (curindex == index_t(-1))
					continue;

				if (curindex >= nVerts)
					return false;

				if (tempRemap[curindex] == UNUSED32)
				{
					tempRemap[curindex] = curvertex;
					++curvertex;
				}
			}

			// inverse lookup
			memset(vertexRemap, 0xff, sizeof(uint32_t) * nVerts);

			size_t unused = 0;

			for (uint32_t j = 0; j < nVerts; ++j)
			{
				uint32_t vertindex = tempRemap[j];
				if (vertindex == UNUSED32)
				{
					++unused;
				}
				else
				{
					if (vertindex >= nVerts)
						return false;

					vertexRemap[vertindex] = j;
				}
			}

			if (trailingUnused)
			{
				*trailingUnused = unused;
			}

			return true;
		}

		_Use_decl_annotations_
		bool OptimizeVertices(
			const uint32_t* indices,
			size_t nFaces,
			size_t nVerts,
			uint32_t* vertexRemap,
			size_t* trailingUnused) noexcept
		{
			return OptimizeVerticesImpl<uint32_t>(indices, nFaces, nVerts, vertexRemap, trailingUnused);
		}



		_Use_decl_annotations_
			bool CompactVB(
				const void* vbin,
				size_t stride,
				size_t nVerts,
				size_t trailingUnused,
				const uint32_t* vertexRemap,
				void* vbout) noexcept
		{
			if (!vbin || !stride || !nVerts || !vbout || !vertexRemap)
				return false;

			if (nVerts >= UINT32_MAX || trailingUnused >= UINT32_MAX)
				return false;

			if (stride > c_MaxStride)
				return false;

			if (trailingUnused >= nVerts)
				return false;

			if (vbin == vbout)
				return false;

			size_t newVerts = nVerts - trailingUnused;

			auto sptr = static_cast<const uint8_t*>(vbin);
			auto dptr = static_cast<uint8_t*>(vbout);

		#ifdef _DEBUG
			memset(vbout, 0, newVerts * stride);
		#endif

			for (size_t j = 0; j < newVerts; ++j)
			{
				uint32_t src = vertexRemap[j];

				if (src == UNUSED32)
				{
					// remap entry is unused
				}
				else if (src < nVerts)
				{
					memcpy(dptr, sptr + src * stride, stride);
				}
				else
					return false;

				dptr += stride;
			}

			return true;
		}
		//
		//
		///////////////////////////////////////////////////////////////
	}
}
