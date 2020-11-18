//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "CRenderer2D_Null.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	CRenderer2D_Null::CRenderer2D_Null() = default;

	CRenderer2D_Null::~CRenderer2D_Null()
	{
		LOG_SCOPED_TRACE(U"CRenderer2D_Null::~CRenderer2D_Null()");
	}

	void CRenderer2D_Null::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer2D_Null::init()");
	}

	void CRenderer2D_Null::addLine(const Float2&, const Float2&, float, const Float4(&)[2])
	{

	}

	void CRenderer2D_Null::addRect(const FloatRect&, const Float4&)
	{

	}

	void CRenderer2D_Null::addCircle(const Float2&, const float, const Float4&, const Float4&)
	{

	}

	void CRenderer2D_Null::addPolygon(const Array<Float2>&, const Array<TriangleIndex>&, const Optional<Float2>&, const Float4&)
	{

	}

	void CRenderer2D_Null::addPolygon(const Vertex2D*, const size_t, const TriangleIndex*, const size_t)
	{

	}

	float CRenderer2D_Null::getMaxScaling() const noexcept
	{
		return 1.0f;
	}
}
