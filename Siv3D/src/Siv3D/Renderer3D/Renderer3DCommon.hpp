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
# include <Siv3D/Common.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Mat4x4.hpp>

namespace s3d
{
	struct VSConstants3D
	{
		Mat4x4 localToWorld = Mat4x4::Identity();
		Mat4x4 worldToProjected = Mat4x4::Identity();
		Float4 diffuse = Float4{ 1.0f, 1.0f, 1.0f, 1.0f };
	};

	struct PSConstants3D
	{
		Float4 placeholder{ 1.0f, 1.0f, 1.0f, 1.0f };
	};
}
