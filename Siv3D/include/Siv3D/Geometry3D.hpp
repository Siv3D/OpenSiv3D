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
# include "Vertex3D.hpp"
# include "Sphere.hpp"
# include "Box.hpp"
# include "OrientedBox.hpp"
# include "Mat4x4.hpp"

namespace s3d
{
	namespace Geometry3D
	{
		[[nodiscard]]
		Sphere BoundingSphere(const Array<Float3>& points) noexcept;

		[[nodiscard]]
		Sphere BoundingSphere(const Vertex3D* vertices, size_t count) noexcept;

		[[nodiscard]]
		Sphere BoundingSphere(const Array<Vertex3D>& vertices) noexcept;

		[[nodiscard]]
		Box BoundingBox(const Array<Float3>& points) noexcept;

		[[nodiscard]]
		Box BoundingBox(const Vertex3D* vertices, size_t count) noexcept;

		[[nodiscard]]
		Box BoundingBox(const Array<Vertex3D>& vertices) noexcept;

		[[nodiscard]]
		OrientedBox BoundingOrientedBox(const Array<Float3>& points) noexcept;

		[[nodiscard]]
		OrientedBox BoundingOrientedBox(const Vertex3D* vertices, size_t count) noexcept;

		[[nodiscard]]
		OrientedBox BoundingOrientedBox(const Array<Vertex3D>& vertices) noexcept;

		[[nodiscard]]
		Sphere TransformBoundingSphere(const Sphere& sphere, const Mat4x4& matrix) noexcept;

		[[nodiscard]]
		Box TransformBoundingBox(const Box& box, const Mat4x4& matrix) noexcept;

		[[nodiscard]]
		OrientedBox TransformBoundingOrientedBox(const OrientedBox& box, const Mat4x4& matrix) noexcept;

		[[nodiscard]]
		Sphere MergeBoundingSpheres(const Sphere& a, const Sphere& b) noexcept;

		[[nodiscard]]
		Box MergeBoundingBoxes(const Box& a, const Box& b) noexcept;
	}
}

# include "detail/Geometry3D.ipp"
