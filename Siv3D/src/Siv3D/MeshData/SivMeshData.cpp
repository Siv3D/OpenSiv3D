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

# include <Siv3D/MeshData.hpp>
# include <Siv3D/Math.hpp>
# include <Siv3D/FastMath.hpp>
# include <Siv3D/MathConstants.hpp>
# include <Siv3D/ScopeGuard.hpp>

# define PAR_SHAPES_IMPLEMENTATION
# define PAR_SHAPES_T uint32_t
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4018)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4100)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4244)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4305)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4389)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4456)
# include <ThirdParty/par_shapes/par_shapes.h>
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_MSVC_WARNINGS_POP()

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

		[[nodiscard]]
		Array<Vertex3D> ToVertices(const par_shapes_mesh& mesh, const Float3 center)
		{
			Array<Vertex3D> vertices(mesh.npoints);
			{
				Vertex3D* pDst = vertices.data();
				const float* pSrcPoints = mesh.points;
				const float* pSrcNormal = mesh.normals;
				const float* pSrcTex = mesh.tcoords;

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
	}

	MeshData::MeshData(Array<Vertex3D> _vertices, Array<TriangleIndex32> _indices)
		: vertices{ std::move(_vertices) }
		, indices{ std::move(_indices) } {}

	MeshData MeshData::OneSidedPlane(const Float2 size)
	{
		return OneSidedPlane(Float3::Zero(), size);
	}

	MeshData MeshData::OneSidedPlane(const Float3 center, const Float2 size)
	{
		const Float2 s = (size * 0.5f);

		Array<Vertex3D> vertices =
		{
			{ .pos = { -s.x, 0.0f,  s.y }, .normal = { 0.0f, 1.0f, 0.0f }, .tex = { 0.0f, 0.0f } },
			{ .pos = {  s.x, 0.0f,  s.y }, .normal = { 0.0f, 1.0f, 0.0f }, .tex = { 1.0f, 0.0f } },
			{ .pos = { -s.x, 0.0f, -s.y }, .normal = { 0.0f, 1.0f, 0.0f }, .tex = { 0.0f, 1.0f } },
			{ .pos = {  s.x, 0.0f, -s.y }, .normal = { 0.0f, 1.0f, 0.0f }, .tex = { 1.0f, 1.0f } },
		};

		for (auto& vertex : vertices)
		{
			vertex.pos += center;
		}

		return{ std::move(vertices), detail::OneSidedPlaceIndices };
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

		for (auto& vertex : vertices)
		{
			vertex.pos += center;
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
		const uint32 vertexCount = (xCount * yCount);
		const uint32 triangleCount = ((phiQuality * thetaQuality) * 2);

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
