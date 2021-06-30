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
# include "IPrimitiveMesh.hpp"

namespace s3d
{
	class CPrimitiveMesh final : public ISiv3DPrimitiveMesh
	{
	public:

		CPrimitiveMesh();

		~CPrimitiveMesh() override;

		void init() override;

	private:

	};
}
