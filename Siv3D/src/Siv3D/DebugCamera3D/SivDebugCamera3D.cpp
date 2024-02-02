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

# include <Siv3D/DebugCamera3D.hpp>
# include <Siv3D/Keyboard.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3D/Math.hpp>
# include <Siv3D/Interpolation.hpp>
# include <Siv3D/Graphics3D.hpp>
# include <Siv3D/Transformer2D.hpp>

namespace s3d
{
	void DebugCamera3D::update(const double speed)
	{
		const double deltaTime = Scene::DeltaTime();
		const double scaledSpeed =
			speed * ((KeyControl | KeyCommand).pressed() ? 20.0 : KeyShift.pressed() ? 5.0 : 1.0)
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
			const double yDelta = deltaTime;

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

	void DebugCamera3D::updateTouchUI(const Vec2& pos, const double scale, const double speed)
	{
		const Transformer2D transformer{ Mat3x2::Identity(), Mat3x2::Scale(scale).translated(pos) };
		constexpr Circle WButton{ 80, 32, 32 };
		constexpr Circle AButton{ 32, 80, 32 };
		constexpr Circle DButton{ 128, 80, 32 };
		constexpr Circle SButton{ 80, 128, 32 };
		constexpr Quad EButton{ 128, 8, 200, 0, 200, 64, 128, 32 };
		constexpr Quad XButton{ 128, 128, 200, 96, 200, 160, 128, 152 };
		constexpr RoundRect DirectionPad{ 20, 180, 160, 60, 10 };

		Vec2 pad{ 0.0,0.0 };

		if (DirectionPad.leftClicked())
		{
			m_padPressed = true;
		}

		if (m_padPressed)
		{
			const Vec2 cursorPos = Cursor::PosF();
			pad.x = Math::Clamp(Math::Map(cursorPos.x, DirectionPad.x, (DirectionPad.x + DirectionPad.w), -1.0, 1.0), -1.0, 1.0);
			pad.y = Math::Clamp(Math::Map(cursorPos.y, DirectionPad.y, (DirectionPad.y + DirectionPad.h), 1.0, -1.0), -1.0, 1.0);

			pad.y = Math::Sign(pad.y) * (pad.y * pad.y);

			if (not MouseL.pressed())
			{
				m_padPressed = false;
			}
		}

		const double deltaTime = Scene::DeltaTime();
		const double scaledSpeed = (m_fastMove * speed * deltaTime);

		{
			m_phi -= (pad.x * 60_deg * deltaTime);

			if (m_phi < 0_deg)
			{
				m_phi += 360_deg;
			}
		}

		const double s = (Math::Cos(m_phi));
		const double c = (Math::Sin(m_phi));

		{
			const double xr = (scaledSpeed * s);
			const double zr = (scaledSpeed * c);

			if (WButton.leftPressed())
			{
				if (WButton.leftClicked())
				{
					m_fastMove = ((m_wButtonStopwatch <= SecondsF{ 0.2 }) ? 4.0 : 1.0);
				}

				m_eyePosition.x += xr;
				m_eyePosition.z += zr;
			}
			else if (WButton.leftReleased())
			{
				m_wButtonStopwatch.restart();
			}

			if (SButton.leftPressed())
			{
				if (SButton.leftClicked())
				{
					m_fastMove = ((m_sButtonStopwatch <= SecondsF{ 0.2 }) ? 4.0 : 1.0);
				}

				m_eyePosition.x -= xr;
				m_eyePosition.z -= zr;
			}
			else if (SButton.leftReleased())
			{
				m_sButtonStopwatch.restart();
			}

			if (AButton.leftPressed())
			{
				if (AButton.leftClicked())
				{
					m_fastMove = ((m_aButtonStopwatch <= SecondsF{ 0.2 }) ? 4.0 : 1.0);
				}

				m_eyePosition.x -= zr;
				m_eyePosition.z += xr;
			}
			else if (AButton.leftReleased())
			{
				m_aButtonStopwatch.restart();
			}

			if (DButton.leftPressed())
			{
				if (DButton.leftClicked())
				{
					m_fastMove = ((m_dButtonStopwatch <= SecondsF{ 0.2 }) ? 4.0 : 1.0);
				}

				m_eyePosition.x += zr;
				m_eyePosition.z -= xr;
			}
			else if (DButton.leftReleased())
			{
				m_dButtonStopwatch.restart();
			}
		}

		{
			const double yDelta = (0.5 * deltaTime);

			m_focusY += (pad.y * yDelta);
		}

		if (EButton.leftPressed())
		{
			if (EButton.leftClicked())
			{
				m_fastMove = ((m_eButtonStopwatch <= SecondsF{ 0.2 }) ? 4.0 : 1.0);
			}

			m_eyePosition.y += scaledSpeed;
		}
		else if (EButton.leftReleased())
		{
			m_eButtonStopwatch.restart();
		}

		if (XButton.leftPressed())
		{
			if (XButton.leftClicked())
			{
				m_fastMove = ((m_xButtonStopwatch <= SecondsF{ 0.2 }) ? 4.0 : 1.0);
			}

			m_eyePosition.y -= scaledSpeed;
		}
		else if (XButton.leftReleased())
		{
			m_xButtonStopwatch.restart();
		}

		const Vec3 focusVector{ s, m_focusY, c };

		setProjection(Graphics3D::GetRenderTargetSize(), m_verticalFOV, m_nearClip);

		BasicCamera3D::setView(m_eyePosition, (m_eyePosition + focusVector), m_upDirection);
	}

	void DebugCamera3D::drawTouchUI(const Vec2& pos, const double scale) const
	{
		const Transformer2D transformer{ Mat3x2::Scale(scale).translated(pos) };
		constexpr Circle WButton{ 80, 32, 32 };
		constexpr Circle AButton{ 32, 80, 32 };
		constexpr Circle DButton{ 128, 80, 32 };
		constexpr Circle SButton{ 80, 128, 32 };
		constexpr Quad EButton{ 128, 8, 200, 0, 200, 64, 128, 32 };
		constexpr Quad XButton{ 128, 128, 200, 96, 200, 160, 128, 152 };
		constexpr RoundRect DirectionPad{ 20, 180, 160, 60, 10 };

		constexpr ColorF CircleInner{ 1.0, 0.4 };
		constexpr ColorF CircleOuter{ 1.0, 0.2 };
		constexpr ColorF ButtonFrame{ 0.9, 0.75 };
		WButton.draw(CircleInner, CircleOuter).drawFrame(2, 0, ButtonFrame);
		AButton.draw(CircleInner, CircleOuter).drawFrame(2, ButtonFrame);
		DButton.draw(CircleInner, CircleOuter).drawFrame(2, ButtonFrame);
		SButton.draw(CircleInner, CircleOuter).drawFrame(2, ButtonFrame);

		EButton
			.draw(CircleOuter, CircleOuter, CircleInner, CircleInner)
			.drawFrame(2, ButtonFrame);
		XButton
			.draw(CircleInner, CircleInner, CircleOuter, CircleOuter)
			.drawFrame(2, ButtonFrame);

		DirectionPad.draw(CircleInner).drawFrame(2, ButtonFrame);
	}

	void DebugCamera3D::setView(const Vec3& eyePosition, const Vec3& focusPosition, const Vec3& upDirection) noexcept
	{
		m_focusY = (focusPosition - eyePosition).normalized().y;
		m_phi = std::atan2((focusPosition.z - eyePosition.z),
			(focusPosition.x - eyePosition.x));

		BasicCamera3D::setView(eyePosition, focusPosition, upDirection);
	}
}
