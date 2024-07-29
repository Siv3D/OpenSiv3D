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

# include <Siv3D/Physics2D/P2LineString.hpp>
# include "P2Common.hpp"

namespace s3d
{
	P2LineString::P2LineString(b2Body& body, const LineString& lines, const CloseRing closeRing, const OneSided oneSided, const P2Material& material, const P2Filter& filter, const bool isSensor)
		: m_pShape{ std::make_unique<b2ChainShape>() }
		, m_lineString(lines.size())
		, m_closeRing{ closeRing }
		, m_oneSided{ oneSided }
	{
		if (m_closeRing)
		{
			if (m_oneSided)
			{
				Array<b2Vec2> points(lines.size());
				for (size_t i = 0; i < lines.size(); ++i)
				{
					points[i].Set(static_cast<float>(lines[i].x), static_cast<float>(lines[i].y));
				}
				m_pShape->CreateLoop(points.data(), static_cast<int32>(points.size()));
			}
			else
			{
				const size_t num_points = lines.size();
				Array<b2Vec2> points(num_points * 2 + 1);
				for (size_t i = 0; i < num_points; ++i)
				{
					points[i].Set(static_cast<float>(lines[i].x), static_cast<float>(lines[i].y));
				}
				points[num_points] = points[0];
				for (size_t i = 0; i < num_points; ++i)
				{
					points[num_points + 1 + i]
						.Set(static_cast<float>(lines[num_points - 1 - i].x),
							 static_cast<float>(lines[num_points - 1 - i].y));
				}
				m_pShape->CreateChain(points.data(), static_cast<int32>(points.size()), points.front(), points.back());
			}
		}
		else
		{
			if (m_oneSided)
			{
				Array<b2Vec2> points(lines.size());
				for (size_t i = 0; i < lines.size(); ++i)
				{
					points[i].Set(static_cast<float>(lines[i].x), static_cast<float>(lines[i].y));
				}
				m_pShape->CreateChain(points.data(), static_cast<int32>(points.size()), points.front(), points.back());
			}
			else
			{
				const size_t num_points = lines.size();
				Array<b2Vec2> points(num_points + (num_points - 1));
				for (size_t i = 0; i < num_points; ++i)
				{
					points[i].Set(static_cast<float>(lines[i].x), static_cast<float>(lines[i].y));
				}
				for (size_t i = 0; i < (num_points - 1); ++i)
				{
					points[num_points + i]
						.Set(static_cast<float>(lines[num_points - 2 - i].x),
							 static_cast<float>(lines[num_points - 2 - i].y));
				}
				m_pShape->CreateChain(points.data(), static_cast<int32>(points.size()), points.front(), points.back());
			}
		}

		const b2FixtureDef fixtureDef = detail::MakeFixtureDef(m_pShape.get(), material, filter, isSensor);

		m_fixtures.push_back(body.CreateFixture(&fixtureDef));
	}

	P2ShapeType P2LineString::getShapeType() const noexcept
	{
		return P2ShapeType::LineString;
	}

	bool P2LineString::isClosed() const noexcept
	{
		return m_closeRing;
	}

	bool P2LineString::isOneSided() const noexcept
	{
		return m_oneSided;
	}

	const P2Shape& P2LineString::draw(const ColorF& color) const
	{
		if (m_closeRing)
		{
			getLineString().drawClosed(detail::AdjustThickness(detail::P2LineThickness), color);
		}
		else
		{
			getLineString().draw(detail::AdjustThickness(detail::P2LineThickness), color);
		}

		return *this;
	}

	const P2Shape& P2LineString::drawFrame(const double thickness, const ColorF& color) const
	{
		if (m_closeRing)
		{
			getLineString().drawClosed(detail::AdjustThickness(thickness), color);
		}
		else
		{
			getLineString().draw(detail::AdjustThickness(thickness), color);
		}

		return *this;
	}

	const P2Shape& P2LineString::drawWireframe(const double thickness, const ColorF& color) const
	{
		return drawFrame(thickness, color);
	}

	const LineString& P2LineString::getLineString() const
	{
		const b2Transform& transform = m_fixtures.front()->GetBody()->GetTransform();
		Vec2* pDst = m_lineString.data();
		const b2Vec2* pSrc = m_pShape->m_vertices;

		for (size_t i = 0; i < m_lineString.size(); ++i)
		{
			*pDst++ = detail::CalcVec2(*pSrc++, transform);
		}

		return m_lineString;
	}
}
