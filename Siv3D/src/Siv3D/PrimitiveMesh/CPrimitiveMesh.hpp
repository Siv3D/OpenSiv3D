//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2025 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "IPrimitiveMesh.hpp"
# include <Siv3D/Mesh.hpp>

namespace s3d
{
	class CPrimitiveMesh final : public ISiv3DPrimitiveMesh
	{
	public:

		CPrimitiveMesh();

		~CPrimitiveMesh() override;

		void init() override;

		const Mesh& getMesh(PrimitiveMeshType meshType) const noexcept override;

	private:

		Array<Mesh> m_meshes;
	};
}
