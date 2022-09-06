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

# include <Siv3D/Camera2D.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3D/Interpolation.hpp>
# include <Siv3D/Mouse.hpp>

namespace s3d
{
	void Camera2D::update(const double deltaTime, const SizeF sceneSize)
	{
		updateWheel(sceneSize);
		updateControls(deltaTime);
		updateMouse(deltaTime);

		{
			const double oldScale = m_scale;
			m_scale = Math::SmoothDamp(m_scale, m_targetScale, m_scaleChangeVelocity, m_parameters.scaleSmoothTime, unspecified, deltaTime);
			
			if (deltaTime && (m_scale != m_targetScale) && (m_scale == oldScale))
			{
				m_scale = m_targetScale;
			}
		}

		if (m_pointedScale)
		{
			const Vec2 v = m_pointedScale->first - (sceneSize * 0.5);
			m_targetCenter = m_center = (m_pointedScale->second - v / m_scale);
		}
		else
		{
			const Vec2 oldCenter = m_center;
			m_center = Math::SmoothDamp(m_center, m_targetCenter, m_positionChangeVelocity, m_parameters.positionSmoothTime, unspecified, deltaTime);

			if (deltaTime && (m_center != m_targetCenter) && (m_center == oldCenter))
			{
				m_center = m_targetCenter;
			}
		}
	}

	void Camera2D::draw(const ColorF& color) const
	{
		if ((not m_grabPos)
			|| m_pointedScale)
		{
			return;
		}

		const auto t1 = Transformer2D{ Mat3x2::Identity(), TransformCursor::Yes, Transformer2D::Target::SetLocal };
		const auto t2 = Transformer2D{ Mat3x2::Identity(), TransformCursor::Yes, Transformer2D::Target::SetCamera };

		const double radius = 12.0;
		const Point delta = (Cursor::Pos() - m_grabPos.value());
		const double length = delta.length();

		Circle{ m_grabPos.value(), radius }.drawFrame(4.0, 2.0, color);

		if ((radius * 2) <= length)
		{
			const Vec2 direction = (delta / length);
			const Vec2 normalDirection{ direction.y, -direction.x };
			const Vec2 leftOffset = (normalDirection * 10);

			const Vec2 p0 = delta;
			const Vec2 p1 = direction.withLength(radius * 1.2) - leftOffset;
			const Vec2 p2 = direction.withLength(radius * 1.8);
			const Vec2 p3 = direction.withLength(radius * 1.2) + leftOffset;

			Quad{ p1, p2, p3, p0 }.moveBy(m_grabPos.value()).draw(color);
		}
	}

	void Camera2D::updateWheel(const SizeF& sceneSize)
	{
		const double wheel = Mouse::Wheel();

		if (wheel == 0.0)
		{
			return;
		}

		m_positionChangeVelocity = Vec2::Zero();

		if (wheel < 0.0)
		{
			m_targetScale *= m_parameters.wheelScaleFactor;
		}
		else
		{
			m_targetScale /= m_parameters.wheelScaleFactor;
		}

		m_targetScale = Clamp(m_targetScale, m_parameters.minScale, m_parameters.maxScale);

		const auto t1 = Transformer2D{ Mat3x2::Identity(), TransformCursor::Yes, Transformer2D::Target::SetLocal };
		const auto t2 = Transformer2D{ Mat3x2::Identity(), TransformCursor::Yes, Transformer2D::Target::SetCamera };

		const Point cursorPos = Cursor::Pos();
		const Vec2 point = (m_center + (cursorPos - (sceneSize * 0.5)) / m_scale);
		m_pointedScale.emplace(cursorPos, point);
	}

	void Camera2D::updateControls(const double deltaTime)
	{
		{
			Vec2 delta{ 0, 0 };

			if (m_parameters.moveToUp
				&& m_parameters.moveToUp())
			{
				delta.y -= 1.0;
			}

			if (m_parameters.moveToLeft
				&& m_parameters.moveToLeft())
			{
				delta.x -= 1.0;
			}

			if (m_parameters.moveToDown
				&& m_parameters.moveToDown())
			{
				delta.y += 1.0;
			}

			if (m_parameters.moveToRight
				&& m_parameters.moveToRight())
			{
				delta.x += 1.0;
			}

			if (not delta.isZero())
			{
				m_pointedScale.reset();
				delta.normalize();
				m_targetCenter += m_parameters.controlSpeedFactor * (deltaTime / 1.0) * (delta / m_targetScale);
			}
		}

		{
			if (m_parameters.zoomIn
				&& m_parameters.zoomIn())
			{
				m_targetScale *= 1.0 + (m_parameters.controlScaleFactor - 1.0) * (deltaTime / 1.0);
				m_targetScale = Min(m_targetScale, m_parameters.maxScale);
			}

			if (m_parameters.zoomOut
				&& m_parameters.zoomOut())
			{
				m_targetScale /= 1.0 + (m_parameters.controlScaleFactor - 1.0) * (deltaTime / 1.0);
				m_targetScale = Max(m_targetScale, m_parameters.minScale);
			}
		}
	}

	void Camera2D::updateMouse(const double deltaTime)
	{
		const auto t1 = Transformer2D{ Mat3x2::Identity(), TransformCursor::Yes, Transformer2D::Target::SetLocal };
		const auto t2 = Transformer2D{ Mat3x2::Identity(), TransformCursor::Yes, Transformer2D::Target::SetCamera };

		if (MouseR.down())
		{
			m_grabPos = Cursor::Pos();
			m_pointedScale.reset();
		}
		else if (m_grabPos)
		{
			const Point delta = (Cursor::Pos() - m_grabPos.value());
			m_targetCenter += m_parameters.grabSpeedFactor * (deltaTime / 1.0) * (delta / m_targetScale);

			if (MouseR.up())
			{
				m_grabPos = none;
			}
		}
	}
}
