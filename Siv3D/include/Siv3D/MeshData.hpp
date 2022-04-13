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

# pragma once
# include "Common.hpp"
# include "Array.hpp"
# include "Vertex3D.hpp"
# include "TriangleIndex.hpp"
# include "Sphere.hpp"
# include "Box.hpp"
# include "NormalComputation.hpp"
# include "Quaternion.hpp"

namespace s3d
{
	struct MeshData
	{
		Array<Vertex3D> vertices;

		Array<TriangleIndex32> indices;

		SIV3D_NODISCARD_CXX20
		MeshData() = default;

		SIV3D_NODISCARD_CXX20
		MeshData(size_t vertexCount, size_t triangleCount);

		SIV3D_NODISCARD_CXX20
		MeshData(Array<Vertex3D> _vertices, Array<TriangleIndex32> _indices);

		MeshData& computeNormals(NormalComputation normalComputation = NormalComputation::Default);

		MeshData& flipTriangles() noexcept;

		MeshData& weld(std::function<bool(const Vertex3D&, const Vertex3D&)> weldTest);

		MeshData& scale(double s);

		MeshData& scale(double sx, double sy, double sz);

		MeshData& scale(Float3 s);

		MeshData& translate(double x, double y, double z);

		MeshData& translate(Float3 v);

		MeshData& rotate(Quaternion quaternion);

		[[nodiscard]]
		s3d::Sphere computeBoundingSphere() const;

		[[nodiscard]]
		s3d::Box computeBoundingBox() const;

		[[nodiscard]]
		static MeshData Billboard(Float2 uvScale = Float2{ 1.0f, 1.0f }, Float2 uvOffset = Float2{ 0.0f, 0.0f });

		[[nodiscard]]
		static MeshData OneSidedPlane(double size, Float2 uvScale = Float2{ 1.0f, 1.0f }, Float2 uvOffset = Float2{ 0.0f, 0.0f });

		[[nodiscard]]
		static MeshData OneSidedPlane(Float3 center, double size, Float2 uvScale = Float2{ 1.0f, 1.0f }, Float2 uvOffset = Float2{ 0.0f, 0.0f });

		[[nodiscard]]
		static MeshData OneSidedPlane(Float2 size, Float2 uvScale = Float2{ 1.0f, 1.0f }, Float2 uvOffset = Float2{ 0.0f, 0.0f });

		[[nodiscard]]
		static MeshData OneSidedPlane(Float3 center, Float2 size, Float2 uvScale = Float2{ 1.0f, 1.0f }, Float2 uvOffset = Float2{ 0.0f, 0.0f });

		[[nodiscard]]
		static MeshData TwoSidedPlane(double size);

		[[nodiscard]]
		static MeshData TwoSidedPlane(Float3 center, double size);

		[[nodiscard]]
		static MeshData TwoSidedPlane(Float2 size);

		[[nodiscard]]
		static MeshData TwoSidedPlane(Float3 center, Float2 size);

		[[nodiscard]]
		static MeshData Box(double size);

		[[nodiscard]]
		static MeshData Box(Float3 size);

		[[nodiscard]]
		static MeshData Box(Float3 center, Float3 size);

		[[nodiscard]]
		static MeshData Sphere(double r, uint32 quality = 12);

		[[nodiscard]]
		static MeshData Sphere(Float3 center, double r, uint32 quality = 12);

		[[nodiscard]]
		static MeshData SubdividedSphere(double r, uint32 subdivisions = 2);

		[[nodiscard]]
		static MeshData SubdividedSphere(Float3 center, double r, uint32 subdivisions = 2);

		[[nodiscard]]
		static MeshData RoundedBox(double r, Float3 size, uint32 quality = 3);

		[[nodiscard]]
		static MeshData Disc(double r, uint32 quality = 24);

		[[nodiscard]]
		static MeshData Disc(Float3 center, double r, uint32 quality = 24);

		[[nodiscard]]
		static MeshData Cylinder(double r, double h, uint32 quality = 24);

		[[nodiscard]]
		static MeshData Cylinder(Float3 center, double r, double h, uint32 quality = 24);

		[[nodiscard]]
		static MeshData Cone(double r, double h, uint32 quality = 24);

		[[nodiscard]]
		static MeshData Cone(Float3 bottomCenter, double r, double h, uint32 quality = 24);

		[[nodiscard]]
		static MeshData Pyramid(double w, double h);

		[[nodiscard]]
		static MeshData Pyramid(Float3 bottomCenter, double w, double h);

		//[[nodiscard]]
		//static MeshData Capsule();

		//[[nodiscard]]
		//static MeshData OneSidedPolygon();

		//[[nodiscard]]
		//static MeshData TwoSidedPolygon();

		//[[nodiscard]]
		//static MeshData ThickPolygon();

		[[nodiscard]]
		static MeshData Grid(Float2 sizeXZ, int32 gridX, int32 gridZ, Float2 uvScale = { 1.0f, 1.0f }, Float2 uvOffset = { 0.0f, 0.0f });

		[[nodiscard]]
		static MeshData Grid(Float3 center, Float2 sizeXZ, int32 gridX, int32 gridZ, Float2 uvScale = { 1.0f, 1.0f }, Float2 uvOffset = { 0.0f, 0.0f });

		[[nodiscard]]
		static MeshData Torus(double radius, double tubeRadius, uint32 ringQuality = 24, uint32 tubeQuality = 12);

		[[nodiscard]]
		static MeshData Torus(Float3 center, double radius, double tubeRadius, uint32 ringQuality = 24, uint32 tubeQuality = 12);

		[[nodiscard]]
		static MeshData Hemisphere(double r, uint32 phiQuality = 24, uint32 thetaQuality = 12);

		[[nodiscard]]
		static MeshData Hemisphere(Float3 center, double r, uint32 phiQuality = 24, uint32 thetaQuality = 12);

		[[nodiscard]]
		static MeshData Tetrahedron(double size);

		[[nodiscard]]
		static MeshData Tetrahedron(Float3 center, double size);

		[[nodiscard]]
		static MeshData Octahedron(double size);

		[[nodiscard]]
		static MeshData Octahedron(Float3 center, double size);

		[[nodiscard]]
		static MeshData Dodecahedron(double size);

		[[nodiscard]]
		static MeshData Dodecahedron(Float3 center, double size);

		[[nodiscard]]
		static MeshData Icosahedron(double size);

		[[nodiscard]]
		static MeshData Icosahedron(Float3 center, double size);
	};
}
