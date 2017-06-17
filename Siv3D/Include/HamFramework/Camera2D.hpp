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
			return Mat3x2::Scale(m_scale).translate(Window::BaseSize() * 0.5 - m_scale * m_pos);
		}

		Transformer2D createTransformer() const
		{
			return Transformer2D(getMat3x2(), true);
		}
	};

	class Camera2D : public BasicCamera2D
	{
	private:

		void controlWithKeyboard(double speed, double scaleRatio)
		{
			if (m_keyConfig[0].pressed())
			{
				m_targetPos.y -= (speed / m_targetScale);
			}

			if (m_keyConfig[1].pressed())
			{
				m_targetPos.x -= (speed / m_targetScale);
			}

			if (m_keyConfig[2].pressed())
			{
				m_targetPos.y += (speed / m_targetScale);
			}

			if (m_keyConfig[3].pressed())
			{
				m_targetPos.x += (speed / m_targetScale);
			}

			if (m_keyConfig[4].pressed())
			{
				m_targetScale *= scaleRatio;
			}

			if (m_keyConfig[5].pressed())
			{
				m_targetScale /= scaleRatio;
			}
		}

		void controlWithMouse(bool useMouseControl, double speed, double scaleRatio, double mouseSpeedRatio)
		{
			if (!useMouseControl)
			{
				m_grabPos = none;

				return;
			}

			{
				const Transformer2D transformer(Mat3x2::Identity(), Cursor::GetTransform().inverse());

				if (MouseR.down())
				{
					m_grabPos = Cursor::Pos();
				}
				else if (m_grabPos)
				{
					const Point delta = Cursor::Pos() - m_grabPos.value();

					m_targetPos += mouseSpeedRatio * speed * delta / m_targetScale;

					if (MouseR.up())
					{
						m_grabPos = none;
					}
				}
			}

			const double wheel = Mouse::Wheel();

			if (wheel < 0.0)
			{
				m_targetScale *= scaleRatio;
			}
			else if (wheel > 0.0)
			{
				m_targetScale /= scaleRatio;
			}
		}

	protected:

		Vec2 m_targetPos = BasicCamera2D::m_pos;

		double m_targetScale = BasicCamera2D::m_scale;

		std::array<Key, 6> m_keyConfig =
		{
			KeyW, KeyA, KeyS, KeyD,
			KeyUp, KeyDown
		};

		Optional<Point> m_grabPos;

	public:

		Camera2D() = default;

		Camera2D(const Vec2& pos, double scale)
			: BasicCamera2D(pos, scale)
			, m_targetPos(pos)
			, m_targetScale(scale)
		{

		}

		virtual ~Camera2D() {}

		void update(double speed = 10.0, double scaleRatio = 1.1, double mouseSpeedRatio = 0.01, double lerpRatio = 0.2, bool useKeyControl = true, bool useMouseControl = true)
		{
			if (useKeyControl)
			{
				controlWithKeyboard(speed, scaleRatio);
			}

			if (useMouseControl)
			{
				controlWithMouse(useMouseControl, speed, scaleRatio, mouseSpeedRatio);
			}

			m_pos = Math::Lerp(m_pos, m_targetPos, lerpRatio);

			m_scale = Math::Lerp(m_scale, m_targetScale, lerpRatio);
		}

		void draw(const ColorF& color = Palette::White) const
		{
			if (!m_grabPos)
			{
				return;
			}

			const Transformer2D transformer(Graphics2D::GetTransform().inverse(), true);

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

		void setKeyConfig(const std::array<Key, 6>& keys)
		{
			m_keyConfig = keys;
		}

		void setTargetPos(const Vec2& targetPos)
		{
			m_targetPos = targetPos;
		}

		void setTargetScale(const double targetScale)
		{
			m_targetScale = targetScale;
		}
	};
}

/* example


*/
