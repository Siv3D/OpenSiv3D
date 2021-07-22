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

# include <Siv3D/DebugCamera3D.hpp>
# include <Siv3D/Keyboard.hpp>
# include <Siv3D/Math.hpp>
# include <Siv3D/Graphics3D.hpp>

namespace s3d
{
	void DebugCamera3D::update(const double speed)
	{
		const double deltaTime = Scene::DeltaTime();
		const double scaledSpeed =
			speed * (KeyControl.pressed() ? 20.0 : KeyShift.pressed() ? 5.0 : 1.0)
			* deltaTime;

		if (KeyLeft.pressed())
		{
			m_phi += (60_deg * deltaTime);

			if (m_phi < 0_deg)
			{
				m_phi += 360_deg;
			}
		}

		if (KeyRight.pressed())
		{
			m_phi -= (60_deg * deltaTime);

			if (360_deg < m_phi)
			{
				m_phi -= 360_deg;
			}
		}

		const double s = (Math::Cos(m_phi));
		const double c = (Math::Sin(m_phi));

		{
			const double xr = (scaledSpeed * s);
			const double zr = (scaledSpeed * c);

			if (KeyW.pressed())
			{
				m_eyePosition.x += xr;
				m_eyePosition.z += zr;
			}

			if (KeyS.pressed())
			{
				m_eyePosition.x -= xr;
				m_eyePosition.z -= zr;
			}

			if (KeyA.pressed())
			{
				m_eyePosition.x -= zr;
				m_eyePosition.z += xr;
			}

			if (KeyD.pressed())
			{
				m_eyePosition.x += zr;
				m_eyePosition.z -= xr;
			}
		}

		{
			const double yDelta = (1.0 * deltaTime);

			if (KeyUp.pressed())
			{
				m_focusY += yDelta;
			}

			if (KeyDown.pressed())
			{
				m_focusY -= yDelta;
			}
		}

		if (KeyE.pressed())
		{
			m_eyePosition.y += scaledSpeed;
		}

		if (KeyX.pressed())
		{
			m_eyePosition.y -= scaledSpeed;
		}

		const Vec3 focusVector{ s, m_focusY, c };

		setProjection(Graphics3D::GetRenderTargetSize(), m_verticalFOV, m_nearClip);

		BasicCamera3D::setView(m_eyePosition, (m_eyePosition + focusVector), m_upDirection);
	}

	void DebugCamera3D::setView(const Vec3& eyePosition, const Vec3& focusPosition, const Vec3& upDirection) noexcept
	{
		m_focusY = (focusPosition - eyePosition).normalized().y;
		m_phi = std::atan2((focusPosition.z - eyePosition.z),
			(focusPosition.x - eyePosition.x));

		BasicCamera3D::setView(eyePosition, focusPosition, upDirection);
	}
}
