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

# include "CPrimitiveMesh.hpp"

namespace s3d
{
	ISiv3DPrimitiveMesh* ISiv3DPrimitiveMesh::Create()
	{
		return new CPrimitiveMesh;
	}
}
