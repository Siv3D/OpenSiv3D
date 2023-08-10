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

# include <Siv3D/SimpleFollowCamera3D.hpp>
# include <Siv3D/Interpolation.hpp>
# include <Siv3D/Cylindrical.hpp>

namespace s3d
{
	namespace detail
	{
		static Vec3 CalculateFollowOffset(const double angle, const double distance, const double height) noexcept
		{
			return Cylindrical{ distance, (-90_deg - angle), height };
		}
	}

	SimpleFollowCamera3D::SimpleFollowCamera3D(const Size& sceneSize, const double verticalFOV, const Vec3& focusPosition, const double followAngle, const double followDistance, const double followHeight) noexcept
		: BasicCamera3D{ sceneSize, verticalFOV, (focusPosition + detail::CalculateFollowOffset(followAngle, followDistance, followHeight)), focusPosition }
		, m_currentFocus{ focusPosition }
		, m_targetFocus{ focusPosition }
		, m_followAngle{ followAngle }
		, m_followDistance{ followDistance }
		, m_followHeight{ followHeight } {}

	void SimpleFollowCamera3D::update(const double smoothTime, const double deltaTime)
	{
		m_currentFocus = Math::SmoothDamp(m_currentFocus, m_targetFocus, m_focusVelocity, smoothTime, unspecified, deltaTime);
		BasicCamera3D::setView((m_currentFocus + getFollowOffset()), m_currentFocus, m_upDirection);
	}

	void SimpleFollowCamera3D::setTarget(const Vec3& targetFocus, const double followAngle) noexcept
	{
		m_targetFocus = targetFocus;
		m_followAngle = followAngle;
	}

	void SimpleFollowCamera3D::jumpToTarget(const Vec3& targetFocus, const double followAngle) noexcept
	{
		m_currentFocus = m_targetFocus = targetFocus;
		m_focusVelocity = Vec3{ 0, 0, 0 };
		m_followAngle = followAngle;
		BasicCamera3D::setView((m_currentFocus + getFollowOffset()), m_currentFocus, m_upDirection);
	}

	void SimpleFollowCamera3D::setFollowOffset(const double followDistance, const double followHeight) noexcept
	{
		m_followDistance = followDistance;
		m_followHeight = followHeight;
	}

	Vec3 SimpleFollowCamera3D::getFollowOffset() const noexcept
	{
		return detail::CalculateFollowOffset(m_followAngle, m_followDistance, m_followHeight);
	}
}
