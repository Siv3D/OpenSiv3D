//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------
// s3d::Camera2D is originally created by Takuto Takahashi (HAMSTRO)
//-----------------------------------------------

# include <Siv3D/Camera2D.hpp>
# include <Siv3D/Transformer2D.hpp>
# include <Siv3D/Interpolation.hpp>
# include <Siv3D/Circle.hpp>
# include <Siv3D/Keyboard.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Cursor.hpp>

namespace s3d
{
	RectF BasicCamera2D::getRegion() const
	{
		return RectF(m_center - (Scene::CenterF() / m_scale), Scene::Size() / m_scale);
	}

	Mat3x2 BasicCamera2D::getMat3x2() const
	{
		return Mat3x2::Scale(m_scale).translated(Scene::CenterF() - m_scale * m_center);
	}

	Transformer2D BasicCamera2D::createTransformer() const
	{
		return Transformer2D(getMat3x2(), true, Transformer2D::Target::PushCamera);
	}

	Camera2DParameters::Camera2DParameters()
		: moveToUp([]() { return KeyW.pressed(); })
		, moveToLeft([]() { return KeyA.pressed(); })
		, moveToDown([]() { return KeyS.pressed(); })
		, moveToRight([]() { return KeyD.pressed(); })
		, zoomIn([]() { return KeyUp.pressed(); })
		, zoomOut([]() { return KeyDown.pressed(); })
	{

	}

	Camera2DParameters::~Camera2DParameters()
	{

	}

	Camera2DParameters Camera2DParameters::Default()
	{
		return Camera2DParameters();
	}

	Camera2DParameters Camera2DParameters::MouseOnly()
	{
		Camera2DParameters params;
		params.moveToUp = {};
		params.moveToLeft = {};
		params.moveToDown = {};
		params.moveToRight = {};
		params.zoomIn = {};
		params.zoomOut = {};
		return params;
	}

	Camera2D::Camera2D(const double scale, const Camera2DParameters& setting) noexcept
		: Camera2D(Scene::CenterF(), scale, setting)
	{
	
	}

	Camera2D::Camera2D(const Vec2& center, const double scale, const Camera2DParameters& setting) noexcept
		: BasicCamera2D(center, scale)
		, m_setting(setting)
	{
	
	}

	void Camera2D::setParameters(const Camera2DParameters& setting) noexcept
	{
		m_setting = setting;
	}

	[[nodiscard]] const Camera2DParameters& Camera2D::getParameters() const noexcept
	{
		return m_setting;
	}

	void Camera2D::setTargetCenter(const Vec2& targetCenter) noexcept
	{
		m_grabPos.reset();
		m_pointedScale.reset();
		m_targetCenter = targetCenter;
	}

	void Camera2D::setTargetScale(const double targetScale) noexcept
	{
		m_grabPos.reset();
		m_pointedScale.reset();
		m_targetScale = targetScale;
	}

	void Camera2D::jumpTo(const Vec2& center, const double scale) noexcept
	{
		m_grabPos.reset();
		m_pointedScale.reset();
		m_targetCenter = m_center = center;
		m_targetScale = m_scale = scale;
		m_positionChangeVelocity = Vec2::Zero();
		m_scaleChangeVelocity = 0.0;
	}

	void Camera2D::update(const double deltaTime)
	{
		updateWheel();
		updateControls(deltaTime);
		updateMouse(deltaTime);

		m_scale = Math::SmoothDamp(m_scale, m_targetScale, m_scaleChangeVelocity, m_setting.scaleSmoothTime, deltaTime);

		if (m_pointedScale)
		{
			const Vec2 v = m_pointedScale->first - Scene::CenterF();
			m_targetCenter = m_center = (m_pointedScale->second - v / m_scale);
		}
		else
		{
			m_center = Math::SmoothDamp(m_center, m_targetCenter, m_positionChangeVelocity, m_setting.positionSmoothTime, deltaTime);
		}
	}

	void Camera2D::draw(const ColorF & color) const
	{
		if (!m_grabPos || m_pointedScale)
		{
			return;
		}

		const auto t1 = Transformer2D(Mat3x2::Identity(), true, Transformer2D::Target::SetLocal);
		const auto t2 = Transformer2D(Mat3x2::Identity(), true, Transformer2D::Target::SetCamera);

		const double radius = 12.0;
		const Point delta = Cursor::Pos() - m_grabPos.value();
		const double length = delta.length();

		Circle(m_grabPos.value(), radius).drawFrame(4.0, 2.0, color);

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

	void Camera2D::updateWheel()
	{
		const double wheel = Mouse::Wheel();

		if (wheel == 0.0)
		{
			return;
		}

		m_positionChangeVelocity = Vec2::Zero();

		if (wheel < 0.0)
		{
			m_targetScale *= m_setting.wheelScaleFactor;
		}
		else
		{
			m_targetScale /= m_setting.wheelScaleFactor;
		}

		m_targetScale = Clamp(m_targetScale, m_setting.minScale, m_setting.maxScale);

		const auto t1 = Transformer2D(Mat3x2::Identity(), true, Transformer2D::Target::SetLocal);
		const auto t2 = Transformer2D(Mat3x2::Identity(), true, Transformer2D::Target::SetCamera);

		const Point cursorPos = Cursor::Pos();
		const Vec2 point = m_center + (cursorPos - Scene::CenterF()) / m_scale;
		m_pointedScale.emplace(cursorPos, point);
	}

	void Camera2D::updateControls(const double deltaTime)
	{
		{
			Vec2 delta(0, 0);

			if (m_setting.moveToUp && m_setting.moveToUp())
			{
				delta.y -= 1.0;
			}

			if (m_setting.moveToLeft && m_setting.moveToLeft())
			{
				delta.x -= 1.0;
			}

			if (m_setting.moveToDown && m_setting.moveToDown())
			{
				delta.y += 1.0;
			}

			if (m_setting.moveToRight && m_setting.moveToRight())
			{
				delta.x += 1.0;
			}

			if (!delta.isZero())
			{
				m_pointedScale.reset();
				delta.normalize();
				m_targetCenter += m_setting.controlSpeedFactor * (deltaTime / 1.0) * (delta / m_targetScale);
			}
		}

		{
			if (m_setting.zoomIn && m_setting.zoomIn())
			{
				m_targetScale *= 1.0 + (m_setting.controlScaleFactor - 1.0) * (deltaTime / 1.0);
			}

			if (m_setting.zoomOut && m_setting.zoomOut())
			{
				m_targetScale /= 1.0 + (m_setting.controlScaleFactor - 1.0) * (deltaTime / 1.0);
			}
		}
	}

	void Camera2D::updateMouse(const double deltaTime)
	{
		const auto t1 = Transformer2D(Mat3x2::Identity(), true, Transformer2D::Target::SetLocal);
		const auto t2 = Transformer2D(Mat3x2::Identity(), true, Transformer2D::Target::SetCamera);

		if (MouseR.down())
		{
			m_grabPos = Cursor::Pos();
			m_pointedScale.reset();
		}
		else if (m_grabPos)
		{
			const Point delta = Cursor::Pos() - m_grabPos.value();
			m_targetCenter += m_setting.grabSpeedFactor * (deltaTime / 1.0) * (delta / m_targetScale);

			if (MouseR.up())
			{
				m_grabPos = none;
			}
		}
	}
}
