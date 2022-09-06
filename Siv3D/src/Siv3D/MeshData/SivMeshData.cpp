//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Common.hpp>
# define PAR_SHAPES_IMPLEMENTATION
# define PAR_SHAPES_T uint32_t
# define PAR_OCTASPHERE_IMPLEMENTATION
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4018)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4100)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4244)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4305)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4389)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4456)
# ifdef __GNUC__
#	pragma GCC diagnostic push
#	pragma GCC diagnostic ignored "-Wsign-compare"
# endif
# include <ThirdParty/par_shapes/par_shapes.h>
# include <ThirdParty/par_octasphere/par_octasphere.h>
# ifdef __GNUC__
#	pragma GCC diagnostic pop
# endif
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_MSVC_WARNINGS_POP()
# include <Siv3D/MeshData.hpp>
# include <Siv3D/Math.hpp>
# include <Siv3D/FastMath.hpp>
# include <Siv3D/MathConstants.hpp>
# include <Siv3D/ScopeGuard.hpp>
# include <Siv3D/SIMD_Float4.hpp>
# include <Siv3D/SIMDCollision.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/HashTable.hpp>
# include <Siv3D/Mat4x4.hpp>
# include "MeshUtility.hpp"

namespace s3d
{
	namespace detail
	{
		static const Array<TriangleIndex32> OneSidedPlaceIndices
		{
			{0,1,2}, {2,1,3}
		};

		static const Array<TriangleIndex32> TwoSidedPlaceIndices
		{
			{0,1,2}, {2,1,3},
			{4,5,6}, {6,5,7}
		};

		static const Array<TriangleIndex32> BoxIndices
		{
			{0, 1, 2}, {2, 1, 3},
			{4, 5, 6}, {6, 5, 7},
			{8, 9, 10}, {10, 9, 11},
			{12, 13, 14}, {14, 13, 15},
			{16, 17, 18}, {18, 17, 19},
			{20, 21, 22}, {22, 21, 23}
		};

		static const Array<TriangleIndex32> PyramidIndices
		{
			{0,1,2}, {3,4,5},
			{6,7,8}, {9,10,11}
		};

		[[nodiscard]]
		Array<Vertex3D> ToVertices(const par_shapes_mesh& mesh, const Float3 center)
		{
			Array<Vertex3D> vertices(mesh.npoints);
			{
				Vertex3D* pDst = vertices.data();
				const float* pSrcPoints = mesh.points;
				const float* pSrcNormal = mesh.normals;
				const float* pSrcTex = mesh.tcoords;

				if (pSrcNormal)
				{
					if (pSrcTex)
					{
						for (int32 i = 0; i < mesh.npoints; ++i)
						{
							pDst->pos.set(pSrcPoints[0], pSrcPoints[2], -pSrcPoints[1]);
							pDst->normal.set(pSrcNormal[0], pSrcNormal[2], -pSrcNormal[1]);
							pDst->tex.set(pSrcTex[0], pSrcTex[1]);

							++pDst;
							pSrcPoints += 3;
							pSrcNormal += 3;
							pSrcTex += 2;
						}
					}
					else
					{
						for (int32 i = 0; i < mesh.npoints; ++i)
						{
							pDst->pos.set(pSrcPoints[0], pSrcPoints[2], -pSrcPoints[1]);
							pDst->normal.set(pSrcNormal[0], pSrcNormal[2], -pSrcNormal[1]);
							pDst->tex.set(0.0f, 0.0f);

							++pDst;
							pSrcPoints += 3;
							pSrcNormal += 3;
						}
					}
				}
				else
				{
					if (pSrcTex)
					{
						for (int32 i = 0; i < mesh.npoints; ++i)
						{
							pDst->pos.set(pSrcPoints[0], pSrcPoints[2], -pSrcPoints[1]);
							pDst->normal.set(0.0f, 1.0f, 0.0f);
							pDst->tex.set(pSrcTex[0], pSrcTex[1]);

							++pDst;
							pSrcPoints += 3;
							pSrcTex += 2;
						}
					}
					else
					{
						for (int32 i = 0; i < mesh.npoints; ++i)
						{
							pDst->pos.set(pSrcPoints[0], pSrcPoints[2], -pSrcPoints[1]);
							pDst->normal.set(0.0f, 1.0f, 0.0f);
							pDst->tex.set(0.0f, 0.0f);

							++pDst;
							pSrcPoints += 3;
						}
					}
				}
			}

			if (not center.isZero())
			{
				for (auto& vertex : vertices)
				{
					vertex.pos += center;
				}
			}

			return vertices;
		}

		[[nodiscard]]
		Array<Vertex3D> ToVertices2(const par_shapes_mesh& mesh, const Float3 center)
		{
			Array<Vertex3D> vertices(mesh.npoints);
			{
				Vertex3D* pDst = vertices.data();
				const float* pSrcPoints = mesh.points;
				const float* pSrcNormal = mesh.normals;
				const float* pSrcTex = mesh.tcoords;

				if (pSrcNormal)
				{
					if (pSrcTex)
					{
						for (int32 i = 0; i < mesh.npoints; ++i)
						{
							pDst->pos.set(pSrcPoints[0], pSrcPoints[1], pSrcPoints[2]);
							pDst->normal.set(pSrcNormal[0], pSrcNormal[1], pSrcNormal[2]);
							pDst->tex.set(pSrcTex[0], pSrcTex[1]);

							++pDst;
							pSrcPoints += 3;
							pSrcNormal += 3;
							pSrcTex += 2;
						}
					}
					else
					{
						for (int32 i = 0; i < mesh.npoints; ++i)
						{
							pDst->pos.set(pSrcPoints[0], pSrcPoints[1], pSrcPoints[2]);
							pDst->normal.set(pSrcNormal[0], pSrcNormal[1], pSrcNormal[2]);
							pDst->tex.set(0.0f, 0.0f);

							++pDst;
							pSrcPoints += 3;
							pSrcNormal += 3;
						}
					}
				}
				else
				{
					if (pSrcTex)
					{
						for (int32 i = 0; i < mesh.npoints; ++i)
						{
							pDst->pos.set(pSrcPoints[0], pSrcPoints[1], pSrcPoints[2]);
							pDst->normal.set(0.0f, 1.0f, 0.0f);
							pDst->tex.set(pSrcTex[0], pSrcTex[1]);

							++pDst;
							pSrcPoints += 3;
							pSrcTex += 2;
						}
					}
					else
					{
						for (int32 i = 0; i < mesh.npoints; ++i)
						{
							pDst->pos.set(pSrcPoints[0], pSrcPoints[1], pSrcPoints[2]);
							pDst->normal.set(0.0f, 1.0f, 0.0f);
							pDst->tex.set(0.0f, 0.0f);

							++pDst;
							pSrcPoints += 3;
						}
					}
				}
			}

			if (not center.isZero())
			{
				for (auto& vertex : vertices)
				{
					vertex.pos += center;
				}
			}

			return vertices;
		}

		[[nodiscard]]
		Array<TriangleIndex32> ToIndices(const par_shapes_mesh& mesh)
		{
			Array<TriangleIndex32> indices(mesh.ntriangles);
			{
				std::memcpy(indices.data(), mesh.triangles, indices.size_bytes());
			}

			return indices;
		}

		bool ComputeNormals(const Array<Float3>& positions, const Array<TriangleIndex32>& indices, Array<Float3>& normals, const NormalComputation normalComputation)
		{
			const uint32* pIndices = &indices.front().i0;

			const DirectX::XMFLOAT3* pPositions = static_cast<const DirectX::XMFLOAT3*>(static_cast<const void*>(positions.data()));
			
			DirectX::XMFLOAT3* pNormals = static_cast<DirectX::XMFLOAT3*>(static_cast<void*>(normals.data()));

			return MeshUtility::ComputeNormals(pIndices, indices.size(), pPositions, positions.size(), MeshUtility::CNORM_FLAGS(FromEnum(normalComputation)), pNormals);
		}
	}

	MeshData::MeshData(const size_t vertexCount, const size_t triangleCount)
		: vertices(vertexCount, Vertex3D{})
		, indices(triangleCount, TriangleIndex32::Zero()) {}

	MeshData::MeshData(Array<Vertex3D> _vertices, Array<TriangleIndex32> _indices)
		: vertices{ std::move(_vertices) }
		, indices{ std::move(_indices) } {}

	MeshData& MeshData::computeNormals(const NormalComputation normalComputation)
	{
		if ((not vertices) || (not indices))
		{
			return *this;
		}

		const Array<Float3> positions = vertices.map([](const Vertex3D& v) {return v.pos; });
		Array<Float3> outNormals(vertices.size());

		if (not detail::ComputeNormals(positions, indices, outNormals, normalComputation))
		{
			return *this;
		}

		{
			Vertex3D* pDst = vertices.data();
			Vertex3D* const pDstEnd = pDst + vertices.size();
			const Float3* pSrc = outNormals.data();

			while (pDst != pDstEnd)
			{
				(pDst++)->normal = *pSrc++;
			}
		}

		return *this;
	}

	MeshData& MeshData::flipTriangles() noexcept
	{
		for (auto& vertex : vertices)
		{
			vertex.normal = -vertex.normal;
		}

		for (auto& triangle : indices)
		{
			std::swap(triangle.i1, triangle.i2);
		}

		return *this;
	}

	MeshData& MeshData::weld(std::function<bool(const Vertex3D&, const Vertex3D&)> weldTest)
	{
		const size_t nFaces = indices.size();
		const size_t nVerts = vertices.size();

		Array<DirectX::XMFLOAT3> pos = vertices.map([](const Vertex3D& v)
			{ return DirectX::XMFLOAT3{ v.pos.x, v.pos.y, v.pos.z }; });

		auto preps = std::make_unique<Vertex3D::IndexType[]>(nVerts);
		if (not MeshUtility::GenerateAdjacencyAndPointReps(&indices.front().i0, nFaces,
			pos.data(), nVerts, 0.f, preps.get(), nullptr))
		{
			return *this;
		}

		Array<Vertex3D::IndexType> newIndices(nFaces * 3);
		std::memcpy(newIndices.data(), indices.data(), sizeof(Vertex3D::IndexType) * nFaces * 3);
		if (not MeshUtility::WeldVertices(newIndices.data(), nFaces, nVerts, preps.get(), nullptr,
			[&](uint32 v0, uint32 v1) -> bool
			{
				return weldTest(vertices[v0], vertices[v1]);
			}))
		{
			return *this;
		}

		Array<Vertex3D::IndexType> vertRemap(nVerts);
		size_t trailingUnused = 0;
		if (not MeshUtility::OptimizeVertices(newIndices.data(), nFaces, nVerts,
			vertRemap.data(), &trailingUnused))
		{
			return *this;
		}

		// 頂点バッファの再構築
		{
			Array<Vertex3D> vb(nVerts - trailingUnused);
			if (not MeshUtility::CompactVB(vertices.data(),
				sizeof(Vertex3D),
				nVerts, trailingUnused, vertRemap.data(), vb.data()))
			{
				return *this;
			}

			vertices.assign(vb.data(), vb.data() + (nVerts - trailingUnused));
		}

		// インデックスバッファの再構築
		{
			HashTable<Vertex3D::IndexType, Vertex3D::IndexType> table;
			{
				for (Vertex3D::IndexType i = 0; i < vertRemap.size(); ++i)
				{
					const uint32 t = vertRemap[i];

					if (t == uint32(-1))
					{
						break;
					}

					table.emplace(t, i);
				}
			}

			{
				TriangleIndex32* pDst = indices.data();
				const Vertex3D::IndexType* pSrc = newIndices.data();

				for (size_t i = 0; i < nFaces; ++i)
				{
					pDst->i0 = table[*pSrc++];
					pDst->i1 = table[*pSrc++];
					pDst->i2 = table[*pSrc++];
					++pDst;
				}
			}
		}

		return *this;
	}

	MeshData& MeshData::scale(const double s)
	{
		return scale(Float3::All(static_cast<float>(s)));
	}

	MeshData& MeshData::scale(const double sx, const double sy, const double sz)
	{
		return scale(Float3{ sx, sy, sz });
	}

	MeshData& MeshData::scale(const Float3 s)
	{
		for (auto& vertex : vertices)
		{
			vertex.pos *= s;
		}

		if ((s.x != s.y) || (s.x != s.z))
		{
			const Mat4x4 mat = Mat4x4::Scale(s);

			mat.transformPoints(&vertices.front().normal, sizeof(Vertex3D),
				&vertices.front().normal, sizeof(Vertex3D), vertices.size());

			for (auto& vertex : vertices)
			{
				vertex.normal.normalize();
			}
		}

		return *this;
	}

	MeshData& MeshData::translate(const double x, const double y, const double z)
	{
		return translate(Float3{ x, y, z });
	}

	MeshData& MeshData::translate(const Float3 v)
	{
		for (auto& vertex : vertices)
		{
			vertex.pos += v;
		}

		return *this;
	}

	MeshData& MeshData::rotate(const Quaternion quaternion)
	{
		for (auto& vertex : vertices)
		{
			vertex.pos = (quaternion * vertex.pos);
			vertex.normal = (quaternion * vertex.normal);
		}

		return *this;
	}

	Sphere MeshData::computeBoundingSphere() const
	{
		if (not vertices)
		{
			return s3d::Sphere{ 0 };
		}

		DirectX::BoundingSphere sphere;

		DirectX::BoundingSphere::CreateFromPoints(
			sphere,
			vertices.size(),
			static_cast<const DirectX::XMFLOAT3*>(static_cast<const void*>(vertices.data())),
			sizeof(Vertex3D)
		);

		return{
			{ sphere.Center.x, sphere.Center.y, sphere.Center.z },
			sphere.Radius
		};
	}

	Box MeshData::computeBoundingBox() const
	{
		if (not vertices)
		{
			return s3d::Box{ 0 };
		}

		DirectX::BoundingBox box;

		DirectX::BoundingBox::CreateFromPoints(
			box,
			vertices.size(),
			static_cast<const DirectX::XMFLOAT3*>(static_cast<const void*>(vertices.data())),
			sizeof(Vertex3D)
		);

		return{
			{ box.Center.x, box.Center.y, box.Center.z },
			{ (box.Extents.x * 2.0), (box.Extents.y * 2.0), (box.Extents.z * 2.0) }
		};
	}

	MeshData MeshData::Billboard(const Float2 uvScale, const Float2 uvOffset)
	{
		Array<Vertex3D> vertices =
		{
			{ .pos = { -0.5f,  0.5f, 0.0f }, .normal = { 0.0f, 0.0f, -1.0f }, .tex = uvOffset },
			{ .pos = {  0.5f,  0.5f, 0.0f }, .normal = { 0.0f, 0.0f, -1.0f }, .tex = { (uvOffset.x + uvScale.x), 0.0f } },
			{ .pos = { -0.5f, -0.5f, 0.0f }, .normal = { 0.0f, 0.0f, -1.0f }, .tex = { 0.0, (uvOffset.y + uvScale.y) } },
			{ .pos = {  0.5f, -0.5f, 0.0f }, .normal = { 0.0f, 0.0f, -1.0f }, .tex = (uvOffset + uvScale) },
		};

		return{ std::move(vertices), detail::OneSidedPlaceIndices };
	}

	MeshData MeshData::OneSidedPlane(const double size, const Float2 uvScale, const Float2 uvOffset)
	{
		return OneSidedPlane(Float3::Zero(), Float2::All(static_cast<float>(size)), uvScale, uvOffset);
	}

	MeshData MeshData::OneSidedPlane(const Float3 center, const double size, const Float2 uvScale, const Float2 uvOffset)
	{
		return OneSidedPlane(center, Float2::All(static_cast<float>(size)), uvScale, uvOffset);
	}

	MeshData MeshData::OneSidedPlane(const Float2 size, const Float2 uvScale, const Float2 uvOffset)
	{
		return OneSidedPlane(Float3::Zero(), size, uvScale, uvOffset);
	}

	MeshData MeshData::OneSidedPlane(const Float3 center, const Float2 size, const Float2 uvScale, const Float2 uvOffset)
	{
		const Float2 s = (size * 0.5f);

		Array<Vertex3D> vertices =
		{
			{ .pos = { -s.x, 0.0f,  s.y }, .normal = { 0.0f, 1.0f, 0.0f }, .tex = uvOffset },
			{ .pos = {  s.x, 0.0f,  s.y }, .normal = { 0.0f, 1.0f, 0.0f }, .tex = { (uvOffset.x + uvScale.x), 0.0f } },
			{ .pos = { -s.x, 0.0f, -s.y }, .normal = { 0.0f, 1.0f, 0.0f }, .tex = { 0.0, (uvOffset.y + uvScale.y) } },
			{ .pos = {  s.x, 0.0f, -s.y }, .normal = { 0.0f, 1.0f, 0.0f }, .tex = (uvOffset + uvScale) },
		};

		for (auto& vertex : vertices)
		{
			vertex.pos += center;
		}

		return{ std::move(vertices), detail::OneSidedPlaceIndices };
	}

	MeshData MeshData::TwoSidedPlane(const double size)
	{
		return TwoSidedPlane(Float3::Zero(), Float2::All(static_cast<float>(size)));
	}

	MeshData MeshData::TwoSidedPlane(const Float3 center, const double size)
	{
		return TwoSidedPlane(center, Float2::All(static_cast<float>(size)));
	}

	MeshData MeshData::TwoSidedPlane(const Float2 size)
	{
		return TwoSidedPlane(Float3::Zero(), size);
	}

	MeshData MeshData::TwoSidedPlane(const Float3 center, const Float2 size)
	{
		const Float2 s = (size * 0.5f);

		Array<Vertex3D> vertices =
		{
			{ .pos = { -s.x, 0.0f,  s.y }, .normal = { 0.0f, 1.0f, 0.0f }, .tex = { 0.0f, 0.0f } },
			{ .pos = {  s.x, 0.0f,  s.y }, .normal = { 0.0f, 1.0f, 0.0f }, .tex = { 1.0f, 0.0f } },
			{ .pos = { -s.x, 0.0f, -s.y }, .normal = { 0.0f, 1.0f, 0.0f }, .tex = { 0.0f, 1.0f } },
			{ .pos = {  s.x, 0.0f, -s.y }, .normal = { 0.0f, 1.0f, 0.0f }, .tex = { 1.0f, 1.0f } },

			{ .pos = {  s.x, 0.0f,  s.y }, .normal = { 0.0f, -1.0f, 0.0f }, .tex = { 0.0f, 0.0f } },
			{ .pos = { -s.x, 0.0f,  s.y }, .normal = { 0.0f, -1.0f, 0.0f }, .tex = { 1.0f, 0.0f } },
			{ .pos = {  s.x, 0.0f, -s.y }, .normal = { 0.0f, -1.0f, 0.0f }, .tex = { 0.0f, 1.0f } },
			{ .pos = { -s.x, 0.0f, -s.y }, .normal = { 0.0f, -1.0f, 0.0f }, .tex = { 1.0f, 1.0f } },
		};

		if (not center.isZero())
		{
			for (auto& vertex : vertices)
			{
				vertex.pos += center;
			}
		}

		return{ std::move(vertices), detail::TwoSidedPlaceIndices };
	}

	MeshData MeshData::Box(const double size)
	{
		return Box(Float3::Zero(), Float3::All(static_cast<float>(size)));
	}

	MeshData MeshData::Box(const Float3 size)
	{
		return Box(Float3::Zero(), size);
	}

	MeshData MeshData::Box(const Float3 center, const Float3 size)
	{
		const Float3 s = (size * 0.5f);

		Array<Vertex3D> vertices =
		{
			{ { -s.x, s.y, -s.z }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f } },
			{ { s.x, s.y, -s.z }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f } },
			{ { -s.x, -s.y, -s.z }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f } },
			{ { s.x, -s.y, -s.z }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f } },

			{ { s.x, s.y, -s.z }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
			{ { s.x, s.y, s.z }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } },
			{ { s.x, -s.y, -s.z }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },
			{ { s.x, -s.y, s.z }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } },

			{ { s.x, s.y, s.z }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } },
			{ { -s.x, s.y, s.z }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f } },
			{ { s.x, -s.y, s.z }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f } },
			{ { -s.x, -s.y, s.z }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },

			{ { -s.x, s.y, s.z }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f } },
			{ { s.x, s.y, s.z }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
			{ { -s.x, s.y, -s.z }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } },
			{ { s.x, s.y, -s.z }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f } },

			{ { -s.x, s.y, s.z }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
			{ { -s.x, s.y, -s.z }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } },
			{ { -s.x, -s.y, s.z }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },
			{ { -s.x, -s.y, -s.z }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } },

			{ { -s.x, -s.y, -s.z }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f } },
			{ { s.x, -s.y, -s.z }, { 0.0f, -1.0f, 0.0f }, { 1.0f, 0.0f } },
			{ { -s.x, -s.y, s.z }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 1.0f } },
			{ { s.x, -s.y, s.z }, { 0.0f, -1.0f, 0.0f }, { 1.0f, 1.0f } },
		};

		if (not center.isZero())
		{
			for (auto& vertex : vertices)
			{
				vertex.pos += center;
			}
		}

		return{ std::move(vertices), detail::BoxIndices };
	}

	MeshData MeshData::Sphere(const double r, const uint32 _quality)
	{
		return Sphere(Float3::Zero(), r, _quality);
	}

	MeshData MeshData::Sphere(const Float3 center, const double r, const uint32 quality)
	{
		const uint32 phiQuality = (quality * 2);
		const uint32 thetaQuality = quality;
		const uint32 xCount = (phiQuality + 1);
		const uint32 yCount = (thetaQuality + 1);
		const uint32 vertexRemoved = 2;
		const uint32 vertexCount = (xCount * yCount) - vertexRemoved;
		const uint32 triangleRemoved = (phiQuality * 2);
		const uint32 triangleCount = ((phiQuality * thetaQuality) * 2) - triangleRemoved;

		Array<std::pair<float, float>> thetaSCs(yCount);
		{
			const float deltaTheta = (Math::PiF / thetaQuality);

			for (uint32 y = 0; y < yCount; ++y)
			{
				const float angle = (deltaTheta * y);
				thetaSCs[y] = { std::sin(angle), std::cos(angle) };
			}
		}

		Array<std::pair<float, float>> phiSCs(xCount);
		{
			const float deltaPhi = (Math::TwoPiF / phiQuality);

			for (uint32 x = 0; x < xCount; ++x)
			{
				const float angle = (90_degF + (deltaPhi * x));
				phiSCs[x] = { std::sin(angle), std::cos(angle) };
			}
		}

		Array<Vertex3D> vertices(vertexCount);
		{
			const float deltaU = (1.0f / phiQuality);
			const float deltaV = (1.0f / thetaQuality);
			const float rf = static_cast<float>(r);
			Vertex3D* pDst = vertices.data();

			for (uint32 y = 0; y < yCount; ++y)
			{
				const float ts = thetaSCs[y].first;
				const float tc = thetaSCs[y].second;
				const float v = (deltaV * y);

				for (uint32 x = 0; x < xCount; ++x)
				{
					if ((y == 0 && x == 0)
						|| (y == (yCount - 1) && x == (xCount - 1)))
					{
						continue;
					}

					const float ps = phiSCs[x].first;
					const float pc = phiSCs[x].second;
					const Float3 normal{ (ts * pc), tc, (ts * ps) };
					const float u = (deltaU * x);

					pDst->pos = (normal * rf);
					pDst->normal = normal;
					pDst->tex.set(u, v);
					++pDst;
				}
			}

			if (not center.isZero())
			{
				for (auto& vertex : vertices)
				{
					vertex.pos += center;
				}
			}
		}

		Array<TriangleIndex32> indices(triangleCount);
		{
			TriangleIndex32* pDst = indices.data();

			for (uint32 y = 0; y < thetaQuality; ++y)
			{
				const uint32 yBaseIndex = (xCount * y);

				if (y == 0)
				{
					for (uint32 x = 0; x < phiQuality; ++x)
					{
						const uint32 baseIndex = (yBaseIndex + x);
						pDst->i0 = (baseIndex + xCount) - 1;
						pDst->i1 = (baseIndex + 1) - 1;
						pDst->i2 = (baseIndex + xCount + 1) - 1;
						++pDst;
					}
				}
				else if (y == (thetaQuality - 1))
				{
					for (uint32 x = 0; x < phiQuality; ++x)
					{
						const uint32 baseIndex = (yBaseIndex + x) - 1;
						pDst->i0 = baseIndex;
						pDst->i1 = (baseIndex + 1);
						pDst->i2 = (baseIndex + xCount);
						++pDst;
					}
				}
				else
				{
					for (uint32 x = 0; x < phiQuality; ++x)
					{
						const uint32 baseIndex = (yBaseIndex + x) - 1;

						pDst->i0 = baseIndex;
						pDst->i1 = (baseIndex + 1);
						pDst->i2 = (baseIndex + xCount);
						++pDst;

						pDst->i0 = (baseIndex + xCount);
						pDst->i1 = (baseIndex + 1);
						pDst->i2 = (baseIndex + xCount + 1);
						++pDst;
					}
				}
			}
		}

		return{ std::move(vertices), std::move(indices) };
	}

	MeshData MeshData::SubdividedSphere(const double r, const uint32 subdivisions)
	{
		return SubdividedSphere(Float3::Zero(), r, subdivisions);
	}

	MeshData MeshData::SubdividedSphere(const Float3 center, const double r, const uint32 subdivisions)
	{
		par_shapes_mesh* mesh = par_shapes_create_subdivided_sphere(subdivisions);
		{
			const float scale = static_cast<float>(r);
			par_shapes_scale(mesh, scale, scale, scale);
		}

		ScopeGuard guard = [mesh]() { par_shapes_free_mesh(mesh); };
		return{ detail::ToVertices(*mesh, center), detail::ToIndices(*mesh) };
	}

	MeshData MeshData::RoundedBox(const double r, const Float3 size, const uint32 quality)
	{
        const par_octasphere_config config = {
            .corner_radius		= static_cast<float>(r),
            .width				= size.x,
            .height				= size.y,
            .depth				= size.z,
			.num_subdivisions	= static_cast<int>(quality),
			.uv_mode			= PAR_OCTASPHERE_UV_LATLONG,
			.normals_mode		= PAR_OCTASPHERE_NORMALS_SMOOTH,
        };

		uint32 numIndices = 0;
		uint32 numVertices = 0;
		par_octasphere_get_counts(&config, &numIndices, &numVertices);

		if ((numIndices == 0) || (numVertices == 0))
		{
			return{};
		}

		Array<Float3> positions(numVertices);
		Array<Float3> normals(numVertices);
		Array<Float2> texcoords(numVertices);
		Array<uint16> indices(numIndices);

		par_octasphere_mesh mesh = {
			.positions		= static_cast<float*>(static_cast<void*>(positions.data())),
			.normals		= static_cast<float*>(static_cast<void*>(normals.data())),
			.texcoords		= static_cast<float*>(static_cast<void*>(texcoords.data())),
			.indices		= indices.data(),
			.num_indices	= 0,
			.num_vertices	= 0,
		};
		
		par_octasphere_populate(&config, &mesh);

		MeshData meshData{ numVertices, (numIndices / 3) };
		{
			Vertex3D* pDst = meshData.vertices.data();
			const Float3* pSrcPositions = positions.data();
			const Float3* pSrcNormal = normals.data();
			const Float2* pSrcTexcoords = texcoords.data();

			for (uint32 i = 0; i < numVertices; ++i)
			{
				pDst->pos.set(pSrcPositions->x, pSrcPositions->y, -pSrcPositions->z);
				pDst->normal.set(pSrcNormal->x, pSrcNormal->y, -pSrcNormal->z);
				pDst->tex = *pSrcTexcoords++;

				++pSrcPositions;
				++pSrcNormal;
				++pDst;
			}
		}

		{
			TriangleIndex32* pDst = meshData.indices.data();
			const uint16* pSrc = indices.data();

			for (uint32 i = 0; i < (numIndices / 3); ++i)
			{
				pDst->i0 = *pSrc++;
				pDst->i2 = *pSrc++;
				pDst->i1 = *pSrc++;
				++pDst;
			}
		}

		return meshData;
	}

	MeshData MeshData::Disc(const double r, const uint32 quality)
	{
		return Disc(Float3::Zero(), r, quality);
	}

	MeshData MeshData::Disc(const Float3 center, const double r, uint32 quality)
	{
		quality = Max(quality, 3u);

		const uint32 triangleCount = quality;
		const uint32 vertexCount = (1 + (quality + 1));
		const float rf = static_cast<float>(r);

		Array<Vertex3D> vertices(vertexCount);
		{
			constexpr Float3 normal{ 0, 1, 0 };
			const float angleDelta = (Math::TwoPiF / quality);
			Vertex3D* pDst = vertices.data();

			pDst->pos.set(0.0f, 0.0f, 0.0f);
			pDst->normal = normal;
			pDst->tex.set(0.5f, 0.5f);
			++pDst;

			for (uint32 i = 0; i <= quality; ++i)
			{
				const float angle = (angleDelta * i);
				const float s = std::sin(angle);
				const float c = std::cos(angle);

				pDst->pos.set((s * rf), 0, (c * rf));
				pDst->normal = normal;
				pDst->tex.set(s * 0.5f + 0.5f, c * -0.5f + 0.5f);
				++pDst;
			}

			if (not center.isZero())
			{
				for (auto& vertex : vertices)
				{
					vertex.pos += center;
				}
			}
		}

		Array<TriangleIndex32> indices(triangleCount);
		{
			TriangleIndex32* pDst = indices.data();

			for (uint32 i = 0; i < triangleCount; ++i)
			{
				pDst->i0 = 0;
				pDst->i1 = (i + 1);
				pDst->i2 = (i + 2);
				++pDst;
			}
		}

		return{ std::move(vertices), std::move(indices) };
	}

	MeshData MeshData::Cylinder(const double r, const double h, const uint32 quality)
	{
		return Cylinder(Float3::Zero(), r, h, quality);
	}

	MeshData MeshData::Cylinder(const Float3 center, const double r, const double h, uint32 quality)
	{
		quality = Max(quality, 3u);

		const uint32 discTriangleCount = quality;
		const uint32 discVertexCount = (1 + (quality + 1));
		const uint32 sideTriangleCount = (quality * 2);
		const uint32 sideVertexCount = ((quality + 1) * 2);
		const uint32 vertexCount = (discVertexCount * 2 + sideVertexCount);
		const uint32 triangleCount = (discTriangleCount * 2 + sideTriangleCount);

		const float rf = static_cast<float>(r);

		Array<std::pair<float, float>> scs(quality + 1);
		{
			const float deltaAngle = (Math::TwoPiF / quality);

			for (uint32 i = 0; i <= quality; ++i)
			{
				const float angle = (deltaAngle * i);
				scs[i] = { std::sin(angle), std::cos(angle) };
			}
		}

		Array<Vertex3D> vertices(vertexCount);
		{
			constexpr Float3 normalTop{ 0,1,0 };
			constexpr Float3 normalBottom{ 0,-1,0 };
			const float hu = static_cast<float>(h * 0.5);
			const float hb = static_cast<float>(-h * 0.5);
			const float uDelta = (1.0f / quality);

			Vertex3D* pDst0 = vertices.data();
			Vertex3D* pDst1 = vertices.data() + discVertexCount;
			Vertex3D* pDst2 = vertices.data() + discVertexCount + sideVertexCount;

			{
				pDst0->pos.set(0.0f, hu, 0.0f);
				pDst0->normal = normalTop;
				pDst0->tex.set(0.5f, 0.5f);
				++pDst0;
			}

			{
				pDst2->pos.set(0.0f, hb, 0.0f);
				pDst2->normal = normalBottom;
				pDst2->tex.set(0.5f, 0.5f);
				++pDst2;
			}

			for (uint32 i = 0; i <= quality; ++i)
			{
				const float s = scs[i].first;
				const float c = scs[i].second;
				const float px = s * rf;
				const float pz = c * rf;

				pDst0->pos.set(px, hu, pz);
				pDst0->normal = normalTop;
				pDst0->tex.set(s * 0.5f + 0.5f, c * -0.5f + 0.5f);
				++pDst0;

				pDst2->pos.set(px, hb, pz);
				pDst2->normal = normalBottom;
				pDst2->tex.set(s * 0.5f + 0.5f, c * -0.5f + 0.5f);
				++pDst2;
			}

			for (uint32 i = 0; i <= quality; ++i)
			{
				const float s = scs[quality - i].first;
				const float c = scs[quality - i].second;
				const float px = s * rf;
				const float pz = c * rf;

				pDst1->pos.set(px, hu, pz);
				pDst1->normal.set(s, 0.0f, c);
				pDst1->tex.set((uDelta * i), 0.0f);
				++pDst1;

				pDst1->pos.set(px, hb, pz);
				pDst1->normal.set(s, 0.0f, c);
				pDst1->tex.set((uDelta * i), 1.0f);
				++pDst1;
			}

			if (not center.isZero())
			{
				for (auto& vertex : vertices)
				{
					vertex.pos += center;
				}
			}
		}

		Array<TriangleIndex32> indices(triangleCount);
		{
			const uint32 sideBaseIndex = discVertexCount;

			TriangleIndex32* pDst = indices.data();

			for (uint32 i = 0; i < discTriangleCount; ++i)
			{
				pDst->i0 = 0;
				pDst->i1 = (i + 1);
				pDst->i2 = (i + 2);
				++pDst;
			}

			for (uint32 i = 0; i < quality; ++i)
			{
				pDst->i0 = (sideBaseIndex + i * 2);
				pDst->i1 = (sideBaseIndex + i * 2 + 2);
				pDst->i2 = (sideBaseIndex + i * 2 + 1);
				++pDst;

				pDst->i0 = (sideBaseIndex + i * 2 + 1);
				pDst->i1 = (sideBaseIndex + i * 2 + 2);
				pDst->i2 = (sideBaseIndex + i * 2 + 3);
				++pDst;
			}

			const uint32 bottomDiscBaseIndex = discVertexCount + sideVertexCount;

			for (uint32 i = 0; i < discTriangleCount; ++i)
			{
				pDst->i0 = bottomDiscBaseIndex;
				pDst->i1 = (bottomDiscBaseIndex + i + 2);
				pDst->i2 = (bottomDiscBaseIndex + i + 1);
				++pDst;
			}
		}

		return{ std::move(vertices), std::move(indices) };
	}

	MeshData MeshData::Cone(const double r, const double h, const uint32 quality)
	{
		return Cone(Float3::Zero(), r, h, quality);
	}

	MeshData MeshData::Cone(const Float3 bottomCenter, const double r, const double h, uint32 quality)
	{
		quality = Max(quality, 3u);

		const uint32 discTriangleCount = quality;
		const uint32 discVertexCount = (1 + (quality + 1));
		const uint32 sideTriangleCount = quality;
		const uint32 sideVertexCount = ((quality + 1) * 2);
		const uint32 vertexCount = (discVertexCount + sideVertexCount);
		const uint32 triangleCount = (discTriangleCount + sideTriangleCount);

		const float rf = static_cast<float>(r);
		const float hf = static_cast<float>(h);

		Array<std::pair<float, float>> scs(quality + 1);
		{
			const float deltaAngle = (Math::TwoPiF / quality);

			for (uint32 i = 0; i <= quality; ++i)
			{
				const float angle = (deltaAngle * i);
				scs[i] = { std::sin(angle), std::cos(angle) };
			}
		}

		Array<Vertex3D> vertices(vertexCount);
		{
			constexpr Float3 normalBottom{ 0,-1,0 };

			Vertex3D* pDst0 = vertices.data();
			Vertex3D* pDst1 = vertices.data() + discVertexCount;

			{
				pDst0->pos.set(0.0f, 0.0f, 0.0f);
				pDst0->normal = normalBottom;
				pDst0->tex.set(0.5f, 0.5f);
				++pDst0;
			}

			for (uint32 i = 0; i <= quality; ++i)
			{
				const float s = scs[i].first;
				const float c = scs[i].second;
				const float px = s * rf;
				const float pz = c * rf;

				pDst0->pos.set(px, 0.0f, pz);
				pDst0->normal = normalBottom;
				pDst0->tex.set(s * 0.5f + 0.5f, c * -0.5f + 0.5f);
				++pDst0;
			}

			for (uint32 i = 0; i <= quality; ++i)
			{
				const float s = scs[quality - i].first;
				const float c = scs[quality - i].second;
				const float px = s * rf;
				const float pz = c * rf;

				pDst1->pos.set(0.0f, hf, 0.0f);
				pDst1->normal.set(0.0f, 0.0f, 0.0f);
				pDst1->tex.set(0.5f, 0.5f);
				++pDst1;

				pDst1->pos.set(px, 0.0f, pz);
				pDst1->normal.set(0.0f, 0.0f, 0.0f);
				pDst1->tex.set(s * 0.5f + 0.5f, c * -0.5f + 0.5f);
				++pDst1;
			}

			if (not bottomCenter.isZero())
			{
				for (auto& vertex : vertices)
				{
					vertex.pos += bottomCenter;
				}
			}
		}

		Array<TriangleIndex32> indices(triangleCount);
		{
			TriangleIndex32* pDst = indices.data();

			for (uint32 i = 0; i < discTriangleCount; ++i)
			{
				pDst->i0 = 0;
				pDst->i1 = (i + 2);
				pDst->i2 = (i + 1);
				++pDst;
			}

			const uint32 sideBaseIndex = discVertexCount;

			for (uint32 i = 0; i < quality; ++i)
			{
				pDst->i0 = (sideBaseIndex + i * 2 + 1);
				pDst->i1 = (sideBaseIndex + i * 2 + 0);
				pDst->i2 = (sideBaseIndex + i * 2 + 3);
				++pDst;
			}
		}

		MeshData meshData{ std::move(vertices), std::move(indices) };

		meshData.computeNormals();

		return meshData;
	}

	MeshData MeshData::Pyramid(const double w, const double h)
	{
		return Pyramid(Float3::Zero(), w, h);
	}

	MeshData MeshData::Pyramid(const Float3 bottomCenter, const double w, const double h)
	{
		const float wh = static_cast<float>(w * 0.5);
		const float hh = static_cast<float>(h);

		Array<Vertex3D> vertices =
		{
			{ .pos = { -wh, 0.0f,  wh }, .normal = { 0.0f, 0.0f, 0.0f }, .tex = { 1.0f, 1.0f } },
			{ .pos = {  wh, 0.0f,  wh }, .normal = { 0.0f, 0.0f, 0.0f }, .tex = { 0.0f, 1.0f } },
			{ .pos = { 0.0f, hh,  0.0f }, .normal = { 0.0f, 0.0f, 0.0f }, .tex = { 0.5f, 0.0f } },

			{ .pos = {  wh, 0.0f,  wh }, .normal = { 0.0f, 0.0f, 0.0f }, .tex = { 1.0f, 1.0f } },
			{ .pos = {  wh, 0.0f, -wh }, .normal = { 0.0f, 0.0f, 0.0f }, .tex = { 0.0f, 1.0f } },
			{ .pos = { 0.0f, hh,  0.0f }, .normal = { 0.0f, 0.0f, 0.0f }, .tex = { 0.5f, 0.0f } },

			{ .pos = {  wh, 0.0f, -wh }, .normal = { 0.0f, 0.0f, 0.0f }, .tex = { 1.0f, 1.0f } },
			{ .pos = { -wh, 0.0f, -wh }, .normal = { 0.0f, 0.0f, 0.0f }, .tex = { 0.0f, 1.0f } },
			{ .pos = { 0.0f, hh,  0.0f }, .normal = { 0.0f, 0.0f, 0.0f }, .tex = { 0.5f, 0.0f } },

			{ .pos = { -wh, 0.0f, -wh }, .normal = { 0.0f, 0.0f, 0.0f }, .tex = { 1.0f, 1.0f } },
			{ .pos = { -wh, 0.0f,  wh }, .normal = { 0.0f, 0.0f, 0.0f }, .tex = { 0.0f, 1.0f } },
			{ .pos = { 0.0f, hh,  0.0f }, .normal = { 0.0f, 0.0f, 0.0f }, .tex = { 0.5f, 0.0f } },
		};

		if (not bottomCenter.isZero())
		{
			for (auto& vertex : vertices)
			{
				vertex.pos += bottomCenter;
			}
		}

		MeshData mesh{ std::move(vertices), detail::PyramidIndices };
		
		mesh.computeNormals();

		return mesh;
	}

	MeshData MeshData::Grid(const Float2 sizeXZ, const int32 gridX, const int32 gridZ, const Float2 uvScale, const Float2 uvOffset)
	{
		return Grid(Float3::Zero(), sizeXZ, gridX, gridZ, uvScale, uvOffset);
	}

	MeshData MeshData::Grid(const Float3 center, const Float2 sizeXZ, int32 gridX, int32 gridZ, const Float2 uvScale, const Float2 uvOffset)
	{
		if ((not InRange(gridX, 1, 1024))
			|| (not InRange(gridZ, 1, 1024)))
		{
			return{};
		}

		const size_t vertexCount = (gridX + 1) * (gridZ + 1);
		Array<Vertex3D> vertices(vertexCount);
		{
			Vertex3D* pDst = vertices.data();

			for (int32 iz = 0; iz < (gridZ + 1); ++iz)
			{
				const float z = -(iz - gridZ * 0.5f) / gridZ * sizeXZ.y;

				for (int32 ix = 0; ix < (gridX + 1); ++ix)
				{
					const float x = (ix - gridX * 0.5f) / gridX * sizeXZ.x;
					pDst->pos.set(x, 0.0f, z);
					pDst->normal.set(0.0f, 1.0f, 0.0f);
					pDst->tex.set(
						static_cast<float>(ix) / gridX * uvScale.x + uvOffset.x,
						static_cast<float>(iz) / gridZ * uvScale.y + uvOffset.y);
					++pDst;
				}
			}

			if (not center.isZero())
			{
				for (auto& vertex : vertices)
				{
					vertex.pos += center;
				}
			}
		}

		const size_t triangleCount = (gridX * gridZ * 2);
		Array<TriangleIndex32> indices(triangleCount);
		{
			TriangleIndex32* pDst = indices.data();

			for (int32 iz = 0; iz < gridZ; ++iz)
			{
				for (int32 ix = 0; ix < gridX; ++ix)
				{
					const Vertex3D::IndexType baseIndex = (iz * (gridX + 1) + ix);

					pDst->i0 = baseIndex;
					pDst->i1 = (baseIndex + 1);
					pDst->i2 = (baseIndex + (gridX + 1));
					++pDst;

					pDst->i0 = (baseIndex + (gridX + 1));
					pDst->i1 = (baseIndex + 1);
					pDst->i2 = (baseIndex + (gridX + 2));
					++pDst;
				}
			}
		}

		return{ std::move(vertices), std::move(indices) };
	}

	MeshData MeshData::Torus(const double radius, const double tubeRadius, const uint32 ringQuality, const uint32 tubeQuality)
	{
		return Torus(Float3::Zero(), radius, tubeRadius, ringQuality, tubeQuality);
	}

	MeshData MeshData::Torus(const Float3 center, const double radius, const double tubeRadius, const uint32 ringQuality, const uint32 tubeQuality)
	{
		par_shapes_mesh* mesh = par_shapes_create_torus(tubeQuality, ringQuality, static_cast<float>(tubeRadius / radius));
		if (not mesh)
		{
			return{};
		}

		ScopeGuard guard = [mesh]() { par_shapes_free_mesh(mesh); };
		const float scale = static_cast<float>(radius);
		par_shapes_scale(mesh, scale, scale, scale);

		return{ detail::ToVertices(*mesh, center), detail::ToIndices(*mesh) };
	}

	MeshData MeshData::Hemisphere(const double r, const uint32 phiQuality, const uint32 thetaQuality)
	{
		return Hemisphere(Float3::Zero(), r, phiQuality, thetaQuality);
	}

	MeshData MeshData::Hemisphere(const Float3 center, const double r, const uint32 phiQuality, const uint32 thetaQuality)
	{
		const uint32 xCount = (phiQuality + 1);
		const uint32 yCount = (thetaQuality + 1);
		const uint32 vertexCount = (xCount * yCount);
		const uint32 triangleCount = ((phiQuality * thetaQuality) * 2);

		Array<std::pair<float, float>> thetaSCs(yCount);
		{
			const float deltaTheta = (Math::HalfPiF / thetaQuality);

			for (uint32 y = 0; y < yCount; ++y)
			{
				const float angle = (deltaTheta * y);
				thetaSCs[y] = { std::sin(angle), std::cos(angle) };
			}
		}

		Array<std::pair<float, float>> phiSCs(xCount);
		{
			const float deltaPhi = (Math::TwoPiF / phiQuality);

			for (uint32 x = 0; x < xCount; ++x)
			{
				const float angle = (90_degF + (deltaPhi * x));
				phiSCs[x] = { std::sin(angle), std::cos(angle) };
			}
		}

		Array<Vertex3D> vertices(vertexCount);
		{
			const float deltaU = (1.0f / phiQuality);
			const float deltaV = (1.0f / thetaQuality);
			const float rf = static_cast<float>(r);
			Vertex3D* pDst = vertices.data();

			for (uint32 y = 0; y < yCount; ++y)
			{
				const float ts = thetaSCs[y].first;
				const float tc = thetaSCs[y].second;
				const float v = (deltaV * y);

				for (uint32 x = 0; x < xCount; ++x)
				{
					const float ps = phiSCs[x].first;
					const float pc = phiSCs[x].second;
					const Float3 normal{ (ts * pc), tc, (ts * ps) };
					const float u = (deltaU * x);

					pDst->pos = (normal * rf);
					pDst->normal = normal;
					pDst->tex.set(u, v);
					++pDst;
				}
			}
		}

		if (not center.isZero())
		{
			for (auto& vertex : vertices)
			{
				vertex.pos += center;
			}
		}

		Array<TriangleIndex32> indices(triangleCount);
		{
			TriangleIndex32* pDst = indices.data();

			for (uint32 y = 0; y < thetaQuality; ++y)
			{
				const uint32 yBaseIndex = (xCount * y);

				for (uint32 x = 0; x < phiQuality; ++x)
				{
					const uint32 baseIndex = (yBaseIndex + x);

					pDst->i0 = baseIndex;
					pDst->i1 = (baseIndex + 1);
					pDst->i2 = (baseIndex + xCount);
					++pDst;

					pDst->i0 = (baseIndex + xCount);
					pDst->i1 = (baseIndex + 1);
					pDst->i2 = (baseIndex + xCount + 1);
					++pDst;
				}
			}
		}

		return{ std::move(vertices), std::move(indices) };
	}

	MeshData MeshData::Tetrahedron(const double size)
	{
		return Tetrahedron(Float3::Zero(), size);
	}

	MeshData MeshData::Tetrahedron(const Float3 center, const double size)
	{
		par_shapes_mesh* mesh = par_shapes_create_tetrahedron();
		{
			const float axisY[3] = { 0,1,0 };
			par_shapes_rotate(mesh, Math::HalfPiF, axisY);
			const float axisX[3] = { 1,0,0 };
			par_shapes_rotate(mesh, Math::HalfPiF, axisX);
			const float scale = static_cast<float>(size);
			par_shapes_scale(mesh, scale, scale, scale);
			par_shapes_unweld(mesh, true);
			par_shapes_compute_normals(mesh);
		}

		ScopeGuard guard = [mesh]() { par_shapes_free_mesh(mesh); };
		return{ detail::ToVertices(*mesh, center), detail::ToIndices(*mesh) };
	}

	MeshData MeshData::Octahedron(const double size)
	{
		return Octahedron(Float3::Zero(), size);
	}

	MeshData MeshData::Octahedron(const Float3 center, const double size)
	{
		par_shapes_mesh* mesh = par_shapes_create_octahedron();
		{
			const float scale = static_cast<float>(size);
			par_shapes_scale(mesh, scale, scale, scale);
			par_shapes_unweld(mesh, true);
			par_shapes_compute_normals(mesh);
		}

		ScopeGuard guard = [mesh]() { par_shapes_free_mesh(mesh); };
		return{ detail::ToVertices(*mesh, center), detail::ToIndices(*mesh) };
	}

	MeshData MeshData::Dodecahedron(const double size)
	{
		return Dodecahedron(Float3::Zero(), size);
	}

	MeshData MeshData::Dodecahedron(const Float3 center, const double size)
	{
		par_shapes_mesh* mesh = par_shapes_create_dodecahedron();
		{
			const float axis[3] = { 0,0,1 };
			par_shapes_rotate(mesh, Math::HalfPiF, axis);
			const float scale = static_cast<float>(size);
			par_shapes_scale(mesh, scale, scale, scale);
			par_shapes_unweld(mesh, true);
			par_shapes_compute_normals(mesh);
		}

		ScopeGuard guard = [mesh]() { par_shapes_free_mesh(mesh); };
		return{ detail::ToVertices(*mesh, center), detail::ToIndices(*mesh) };
	}

	MeshData MeshData::Icosahedron(const double size)
	{
		return Icosahedron(Float3::Zero(), size);
	}

	MeshData MeshData::Icosahedron(const Float3 center, const double size)
	{
		par_shapes_mesh* mesh = par_shapes_create_icosahedron();
		{
			const float scale = static_cast<float>(size);
			par_shapes_scale(mesh, scale, scale, scale);
			par_shapes_unweld(mesh, true);
			par_shapes_compute_normals(mesh);
		}

		ScopeGuard guard = [mesh]() { par_shapes_free_mesh(mesh); };
		return{ detail::ToVertices(*mesh, center), detail::ToIndices(*mesh) };
	}
}
