//-----------------------------------------------
//
//	This file is part of the HamFramework for Siv3D.
//
//	Copyright (C) 2014-2017 HAMSTRO
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D.hpp>

namespace s3d
{
	class BasicCamera2D
	{
	protected:

		Vec2 m_pos = Window::BaseSize() * 0.5;

		double m_scale = 1.0;

	public:

		BasicCamera2D() = default;

		constexpr BasicCamera2D(const Vec2& pos, double scale) noexcept
			: m_pos(pos)
			, m_scale(scale) {}

		virtual ~BasicCamera2D() = default;

		void setPos(const Vec2& pos) noexcept
		{
			m_pos = pos;
		}

		const Vec2& getPos() const noexcept
		{
			return m_pos;
		}

		void setScale(double scale) noexcept
		{
			m_scale = scale;
		}

		double getScale() const noexcept
		{
			return m_scale;
		}

		RectF getCameraArea() const
		{
			return RectF(m_pos - Window::BaseSize() * 0.5 / m_scale, Window::BaseSize() / m_scale);
		}

		Mat3x2 getMat3x2() const
		{
			return Mat3x2::Scale(m_scale).translated(Window::BaseSize() * 0.5 - m_scale * m_pos);
		}

		Transformer2D createTransformer() const
		{
			return Transformer2D(getMat3x2(), true, Transformer2D::Target::PushCamera);
		}
	};

	class Camera2D : public BasicCamera2D
	{
	private:

		bool m_keyControlEnabled = true;

		bool m_mouseControlEnabled = true;

		double m_speed = 10.0;

		double m_scaleRatio = 1.1;

		double m_mouseSpeedRatio = 0.01;

		double m_lerpRatio = 0.2;

		void controlWithKeyboard()
		{
			if (!m_keyControlEnabled)
			{
				return;
			}

			if (m_controls[0]())
			{
				m_targetPos.y -= (m_speed / m_targetScale);
			}

			if (m_controls[1]())
			{
				m_targetPos.x -= (m_speed / m_targetScale);
			}

			if (m_controls[2]())
			{
				m_targetPos.y += (m_speed / m_targetScale);
			}

			if (m_controls[3]())
			{
				m_targetPos.x += (m_speed / m_targetScale);
			}

			if (m_controls[4]())
			{
				m_targetScale *= m_scaleRatio;
			}

			if (m_controls[5]())
			{
				m_targetScale /= m_scaleRatio;
			}
		}

		void controlWithMouse()
		{
			if (!m_mouseControlEnabled)
			{
				m_grabPos = none;

				return;
			}

			{
				const Transformer2D transformerLocal(Mat3x2::Identity(), true, Transformer2D::Target::SetLocal);
				const Transformer2D transformerCamera(Mat3x2::Identity(), true, Transformer2D::Target::SetCamera);
				const Transformer2D transformerScreen(Mat3x2::Identity(), true, Transformer2D::Target::SetScreen);

				if (MouseR.down())
				{
					m_grabPos = Cursor::Pos();
				}
				else if (m_grabPos)
				{
					const Point delta = Cursor::Pos() - m_grabPos.value();

					m_targetPos += m_mouseSpeedRatio * m_speed * delta / m_targetScale;

					if (MouseR.up())
					{
						m_grabPos = none;
					}
				}
			}

			const double wheel = Mouse::Wheel();

			if (wheel < 0.0)
			{
				m_targetScale *= m_scaleRatio;
			}
			else if (wheel > 0.0)
			{
				m_targetScale /= m_scaleRatio;
			}
		}

	protected:

		Vec2 m_targetPos = BasicCamera2D::m_pos;

		double m_targetScale = BasicCamera2D::m_scale;

		std::array<std::function<bool()>, 6> m_controls =
		{{ [](){ return KeyW.pressed(); }
		,  [](){ return KeyA.pressed(); }
		,  [](){ return KeyS.pressed(); }
		,  [](){ return KeyD.pressed(); }
		,  [](){ return KeyUp.pressed(); }
		,  [](){ return KeyDown.pressed(); }}};

		Optional<Point> m_grabPos;

	public:

		Camera2D() = default;


		Camera2D(const Vec2& pos, double scale, bool keyControlEnabled = true, bool mouseControlEnabled = true, double speed = 10.0, double scaleRatio = 1.1, double lerpRatio = 0.2)
			: BasicCamera2D(pos, scale)
			, m_keyControlEnabled(keyControlEnabled)
			, m_mouseControlEnabled(mouseControlEnabled)
			, m_speed(speed)
			, m_scaleRatio(scaleRatio)
			, m_lerpRatio(lerpRatio)
			, m_targetPos(pos)
			, m_targetScale(scale)
		{

		}

		virtual ~Camera2D() = default;


		void update()
		{
			controlWithKeyboard();

			controlWithMouse();

			m_pos = Math::Lerp(m_pos, m_targetPos, m_lerpRatio);

			m_scale = Math::Lerp(m_scale, m_targetScale, m_lerpRatio);
		}

		void draw(const ColorF& color = Palette::White) const
		{
			if (!m_grabPos)
			{
				return;
			}

			const Transformer2D transformerLocal(Mat3x2::Identity(), true, Transformer2D::Target::SetLocal);
			const Transformer2D transformerCamera(Mat3x2::Identity(), true, Transformer2D::Target::SetCamera);
			const Transformer2D transformerScreen(Mat3x2::Identity(), true, Transformer2D::Target::SetScreen);

			const double radius = 12.0;
			const Point delta = Cursor::Pos() - m_grabPos.value();
			const double length = delta.length();

			Circle(m_grabPos.value(), radius).drawFrame(2.0, 2.0, color);

			if (length >= radius * 2)
			{
				const Vec2 direction = delta / length;
				const Vec2 normalDirection{ direction.y, -direction.x };
				const Vec2 leftOffset = normalDirection * 10;

				const Vec2 p0 = delta;
				const Vec2 p1 = Vec2(direction).setLength(radius * 1.2) - leftOffset;
				const Vec2 p2 = Vec2(direction).setLength(radius * 1.8);
				const Vec2 p3 = Vec2(direction).setLength(radius * 1.2) + leftOffset;

				Quad(p1, p2, p3, p0).moveBy(m_grabPos.value()).draw(color);
			}
		}

		void setControls(const std::array<std::function<bool()>, 6>& controls)
		{
			m_controls = controls;
		}

		void setTargetPos(const Vec2& targetPos) noexcept
		{
			m_targetPos = targetPos;
		}

		void setTargetScale(double targetScale) noexcept
		{
			m_targetScale = targetScale;
		}

		void setSpeed(double speed) noexcept
		{
			m_speed = speed;
		}

		double getSpeed() const noexcept
		{
			return m_speed;
		}

		void setScaleRatio(double scaleRatio) noexcept
		{
			m_scaleRatio = scaleRatio;
		}

		double getScaleRatio() const noexcept
		{
			return m_scaleRatio;
		}

		void setMouseSpeedRatio(double mouseSpeedRatio) noexcept
		{
			m_mouseSpeedRatio = mouseSpeedRatio;
		}

		double getMouseSpeedRatio() const noexcept
		{
			return m_mouseSpeedRatio;
		}

		void setLerpRatio(double lerpRatio) noexcept
		{
			m_lerpRatio = lerpRatio;
		}

		double getLerpRatio() const noexcept
		{
			return m_lerpRatio;
		}

		void enableKeyControl(bool enable) noexcept
		{
			m_keyControlEnabled = enable;
		}

		bool keyControlEnabled() const noexcept
		{
			return m_keyControlEnabled;
		}

		void enableMouseControl(bool enable) noexcept
		{
			m_mouseControlEnabled = enable;
		}

		bool mouseControlEnabled() const noexcept
		{
			return m_mouseControlEnabled;
		}
	};
}

/* example


*/
