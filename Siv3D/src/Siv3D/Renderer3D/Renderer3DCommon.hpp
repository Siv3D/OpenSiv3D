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
	struct VSPerViewConstants3D // (VS slot-1)
	{
		Mat4x4 worldToProjected = Mat4x4::Identity();
	};

	struct VSPerObjectConstants3D // (VS slot-2)
	{
		Mat4x4 localToWorld = Mat4x4::Identity();
	};

	struct PSPerViewConstants3D // (PS slot-1)
	{
		Float4 eyePosition = Float4{ 0.0f, 0.0f, 0.0f, 0.0f };
	};

	struct PSPerMaterialConstants3D // (PS slot-3)
	{
		Float4 diffuseColor = Float4{ 1.0f, 1.0f, 1.0f, 1.0f };
	};

	struct BatchInfoLine3D
	{
		uint32 indexCount = 0;

		uint32 startIndexLocation = 0;

		uint32 baseVertexLocation = 0;
	};
}
