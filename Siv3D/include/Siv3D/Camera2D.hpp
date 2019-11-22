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

# pragma once
# include "Fwd.hpp"
# include "Graphics2D.hpp"
# include "Scene.hpp"
# include "Transformer2D.hpp"

namespace s3d
{
	class BasicCamera2D
	{
	protected:

		Vec2 m_center = Scene::CenterF();

		double m_scale = 1.0;

	public:

		BasicCamera2D() = default;

		explicit BasicCamera2D(double scale) noexcept
			: BasicCamera2D(Scene::CenterF(), scale) {}

		BasicCamera2D(const Vec2& center, double scale = 1.0) noexcept
			: m_center(center)
			, m_scale(scale) {}

		~BasicCamera2D() = default;

		void setCenter(const Vec2& center) noexcept
		{
			m_center = center;
		}

		[[nodiscard]] const Vec2& getCenter() const noexcept
		{
			return m_center;
		}

		void setScale(double scale) noexcept
		{
			m_scale = scale;
		}

		[[nodiscard]] double getScale() const noexcept
		{
			return m_scale;
		}

		[[nodiscard]] RectF getRegion() const;

		[[nodiscard]] Mat3x2 getMat3x2() const;

		[[nodiscard]] Transformer2D createTransformer() const;
	};

	struct Camera2DParameters
	{
		double minScale = 1.0 / 128.0;
		double maxScale = 128.0;
		double scaleSmoothTime = 0.2;
		double positionSmoothTime = 0.2;

		// wheel
		double wheelScaleFactor = 1.125;

		// mouse
		double grabSpeedFactor = 4.0;

		// controls
		double controlScaleFactor = 2.0;
		double controlSpeedFactor = 400.0;

		std::function<bool()> moveToUp;
		std::function<bool()> moveToLeft;
		std::function<bool()> moveToDown;
		std::function<bool()> moveToRight;
		std::function<bool()> zoomIn;
		std::function<bool()> zoomOut;

		Camera2DParameters();

		~Camera2DParameters();

		static Camera2DParameters Default();

		static Camera2DParameters MouseOnly();

		static Camera2DParameters NoControl();
	};

	class Camera2D : public BasicCamera2D
	{
	protected:

		double m_targetScale = BasicCamera2D::m_scale;
		double m_scaleChangeVelocity = 0.0;

		Vec2 m_targetCenter = BasicCamera2D::m_center;
		Vec2 m_positionChangeVelocity = Vec2::Zero();

		Optional<Point> m_grabPos;
		Optional<std::pair<Point, Vec2>> m_pointedScale;

		Camera2DParameters m_setting;

		void updateWheel();

		void updateControls(const double deltaTime);

		void updateMouse(const double deltaTime);

	public:

		Camera2D() = default;

		explicit Camera2D(double scale, const Camera2DParameters& setting = Camera2DParameters::Default()) noexcept;

		Camera2D(const Vec2& center, double scale = 1.0, const Camera2DParameters& setting = Camera2DParameters::Default()) noexcept;

		~Camera2D() = default;

		void setParameters(const Camera2DParameters& setting) noexcept;

		[[nodiscard]] const Camera2DParameters& getParameters() const noexcept;

		void setTargetCenter(const Vec2& targetCenter) noexcept;

		void setTargetScale(double targetScale) noexcept;

		void jumpTo(const Vec2& center, double scale) noexcept;

		void update(double deltaTime = Scene::DeltaTime());

		void draw(const ColorF& color = Palette::White) const;
	};
}
