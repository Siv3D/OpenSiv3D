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

# include <Siv3D/Physics2D/P2Shape.hpp>
# include "P2Common.hpp"

namespace s3d
{
	void P2Shape::setDensity(const double density) noexcept
	{
		const double scaledDensity = (density * detail::P2DensityScale);

		for (auto& fixture : m_fixtures)
		{
			fixture->SetDensity(static_cast<float>(scaledDensity));
		}
	}

	double P2Shape::getDensity() const noexcept
	{
		return (m_fixtures.front()->GetDensity() * detail::P2DensityScaleInv);
	}

	void P2Shape::setRestitution(const double restitution) noexcept
	{
		for (auto& fixture : m_fixtures)
		{
			fixture->SetRestitution(static_cast<float>(restitution));
		}
	}

	double P2Shape::getRestitution() const noexcept
	{
		return m_fixtures.front()->GetRestitution();
	}

	void P2Shape::setFriction(const double friction) noexcept
	{
		for (auto& fixture : m_fixtures)
		{
			fixture->SetFriction(static_cast<float>(friction));
		}
	}

	double P2Shape::getFriction() const noexcept
	{
		return m_fixtures.front()->GetFriction();
	}

	void P2Shape::setRestitutionThreshold(const double restitutionThreshold) noexcept
	{
		for (auto& fixture : m_fixtures)
		{
			fixture->SetRestitutionThreshold(static_cast<float>(restitutionThreshold * detail::P2RestitutionThresholdScale));
		}
	}

	double P2Shape::getRestitutionThreshold() const noexcept
	{
		return (m_fixtures.front()->GetRestitutionThreshold() * detail::P2RestitutionThresholdScaleInv);
	}

	void P2Shape::setFilter(const P2Filter& filter) noexcept
	{
		b2Filter filterData;
		filterData.categoryBits	= filter.categoryBits;
		filterData.maskBits		= filter.maskBits;
		filterData.groupIndex	= filter.groupIndex;

		for (auto& fixture : m_fixtures)
		{
			fixture->SetFilterData(filterData);
		}
	}

	P2Filter P2Shape::getFilter() const noexcept
	{
		const auto& filterData = m_fixtures.front()->GetFilterData();
		P2Filter filter;
		filter.categoryBits	= filterData.categoryBits;
		filter.maskBits		= filterData.maskBits;
		filter.groupIndex	= filterData.groupIndex;
		return filter;
	}
}
