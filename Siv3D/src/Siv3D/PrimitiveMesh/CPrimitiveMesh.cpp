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

# include "CPrimitiveMesh.hpp"
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	CPrimitiveMesh::CPrimitiveMesh() {}

	CPrimitiveMesh::~CPrimitiveMesh()
	{
		LOG_SCOPED_TRACE(U"CPrimitiveMesh::~CPrimitiveMesh()");
	}

	void CPrimitiveMesh::init()
	{
		LOG_SCOPED_TRACE(U"CPrimitiveMesh::init()");
	}
}
