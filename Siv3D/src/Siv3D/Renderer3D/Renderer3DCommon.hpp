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
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Mat4x4.hpp>
# include <Siv3D/PhongMaterial.hpp>
# include <Siv3D/Graphics3D.hpp>

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

	struct VSPerMaterialConstants3D // (VS slot-3)
	{
		Float4 uvTransform = Float4{ 1.0f, 1.0f, 0.0f, 0.0f };
	};

	struct PSPerFrameConstants3D // (PS slot-0)
	{
		Float4 globalAmbientColor = Float4{ Graphics3D::DefaultGlobalAmbientColor.rgb(), 0.0f };
		Float4 sunColor = Float4{ Graphics3D::DefaultSunColor.rgb(), 0.0f };
		Float4 sunDirection = Float4{ Graphics3D::DefaultSunDirection, 0.0f };
	};

	struct PSPerViewConstants3D // (PS slot-1)
	{
		Float4 eyePosition = Float4{ 0.0f, 0.0f, 0.0f, 0.0f };
	};

	struct PSPerMaterialConstants3D // (PS slot-3)
	{
		PhongMaterialInternal material;
	};

	struct BatchInfoLine3D
	{
		uint32 indexCount = 0;

		uint32 startIndexLocation = 0;

		uint32 baseVertexLocation = 0;
	};
}
