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
# include "BasicCamera3D.hpp"
# include "Stopwatch.hpp"

namespace s3d
{
	class DebugCamera3D : public BasicCamera3D
	{
	public:

		using BasicCamera3D::BasicCamera3D;

		void update(double speed = 1.0);

		void updateTouchUI(const Vec2& pos, double scale = 1.0, double speed = 1.0);

		void drawTouchUI(const Vec2& pos, double scale = 1.0);

		void setView(const Vec3& eyePosition, const Vec3& focusPosition, const Vec3& upDirection = Vec3{ 0, 1, 0 }) noexcept;

	protected:

		double m_focusY = (BasicCamera3D::m_focusPosition - BasicCamera3D::m_eyePosition).normalized().y;

		double m_phi = std::atan2((BasicCamera3D::m_focusPosition.z - BasicCamera3D::m_eyePosition.z),
			(BasicCamera3D::m_focusPosition.x - BasicCamera3D::m_eyePosition.x));

	private:

		double m_fastMove = 1.0;

		bool m_padPressed = false;

		Stopwatch m_wButtonStopwatch{ StartImmediately::Yes };

		Stopwatch m_aButtonStopwatch{ StartImmediately::Yes };

		Stopwatch m_sButtonStopwatch{ StartImmediately::Yes };

		Stopwatch m_dButtonStopwatch{ StartImmediately::Yes };

		Stopwatch m_eButtonStopwatch{ StartImmediately::Yes };

		Stopwatch m_xButtonStopwatch{ StartImmediately::Yes };
	};
}
