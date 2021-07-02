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

# pragma once
# include "Common.hpp"
# include "Array.hpp"
# include "Vertex3D.hpp"
# include "TriangleIndex.hpp"
# include "Sphere.hpp"
# include "Box.hpp"
# include "NormalComputation.hpp"

namespace s3d
{
	struct MeshData
	{
		Array<Vertex3D> vertices;

		Array<TriangleIndex32> indices;

		SIV3D_NODISCARD_CXX20
		MeshData() = default;

		SIV3D_NODISCARD_CXX20
		MeshData(Array<Vertex3D> _vertices, Array<TriangleIndex32> _indices);

		bool computeNormals(NormalComputation normalComputation = NormalComputation::Default);

		[[nodiscard]]
		s3d::Sphere computeBoundingSphere() const;

		[[nodiscard]]
		s3d::Box computeBoundingBox() const;

		[[nodiscard]]
		static MeshData OneSidedPlane(Float2 size);

		[[nodiscard]]
		static MeshData OneSidedPlane(Float3 center, Float2 size);

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
		static MeshData Disc(double r, uint32 quality = 24);

		[[nodiscard]]
		static MeshData Disc(Float3 center, double r, uint32 quality = 24);

		[[nodiscard]]
		static MeshData Cylinder(double r, double h, uint32 quality = 24);

		[[nodiscard]]
		static MeshData Cylinder(Float3 center, double r, double h, uint32 quality = 24);

		//[[nodiscard]]
		//static MeshData Cone();

		//[[nodiscard]]
		//static MeshData Pyramid();

		//[[nodiscard]]
		//static MeshData Capsule();

		//[[nodiscard]]
		//static MeshData FromPolygon();

		//[[nodiscard]]
		//static MeshData Grid();

		[[nodiscard]]
		static MeshData Torus(double radius, double tubeRadius, uint32 ringQuality = 24, uint32 tubeQuality = 12);

		[[nodiscard]]
		static MeshData Torus(Float3 center, double radius, double tubeRadius, uint32 ringQuality = 24, uint32 tubeQuality = 12);

		[[nodiscard]]
		static MeshData Hemisphere(double r, uint32 phiQuality, uint32 thetaQuality = 12);

		[[nodiscard]]
		static MeshData Hemisphere(Float3 center, double r, uint32 phiQuality, uint32 thetaQuality = 12);

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
