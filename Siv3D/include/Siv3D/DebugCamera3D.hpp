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
# include "Common.hpp"
# include "BasicCamera3D.hpp"

namespace s3d
{
	class DebugCamera3D : public BasicCamera3D
	{
	public:

		using BasicCamera3D::BasicCamera3D;

		void update(double speed = 1.0);

		void setView(const Vec3& eyePosition, const Vec3& focusPosition, const Vec3& upDirection = Vec3{ 0, 1, 0 }) noexcept;

	private:

		double m_focusY = (BasicCamera3D::m_focusPosition - BasicCamera3D::m_eyePosition).normalized().y;

		double m_phi = std::atan2((BasicCamera3D::m_focusPosition.z - BasicCamera3D::m_eyePosition.z),
			(BasicCamera3D::m_focusPosition.x - BasicCamera3D::m_eyePosition.x));
	};
}
