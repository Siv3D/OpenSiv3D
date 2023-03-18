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

# pragma once
# include <Siv3D/Common.hpp>

namespace s3d
{
	enum class PrimitiveMeshType
	{
		OneSidedPlane,

		TwoSidedPlane,

		Box1,

		Sphere,

		Disc,

		Cylinder,

		Cone,

		Hemisphere,
	};

	class Mesh;

	class SIV3D_NOVTABLE ISiv3DPrimitiveMesh
	{
	public:

		static ISiv3DPrimitiveMesh* Create();

		virtual ~ISiv3DPrimitiveMesh() = default;

		virtual void init() = 0;

		virtual const Mesh& getMesh(PrimitiveMeshType meshType) const noexcept = 0;
	};
}
