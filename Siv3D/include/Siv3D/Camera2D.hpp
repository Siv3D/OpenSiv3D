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
# include "BasicCamera2D.hpp"
# include "Scene.hpp"
# include "Keyboard.hpp"

namespace s3d
{
	struct Camera2DParameters
	{
		double minScale = (1.0 / 128.0);
		
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

		std::function<bool()> moveToUp		= ([]{ return KeyW.pressed(); });
		
		std::function<bool()> moveToLeft	= ([]{ return KeyA.pressed(); });
		
		std::function<bool()> moveToDown	= ([]{ return KeyS.pressed(); });
		
		std::function<bool()> moveToRight	= ([]{ return KeyD.pressed(); });
		
		std::function<bool()> zoomIn		= ([]{ return KeyUp.pressed(); });
		
		std::function<bool()> zoomOut		= ([]{ return KeyDown.pressed(); });

		[[nodiscard]]
		static Camera2DParameters Default();

		[[nodiscard]]
		static Camera2DParameters MouseOnly();

		[[nodiscard]]
		static Camera2DParameters KeyboardOnly();

		[[nodiscard]]
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

		Camera2DParameters m_parameters;

		void updateWheel(const SizeF& sceneSize);

		void updateControls(const double deltaTime);

		void updateMouse(const double deltaTime);

	public:

		SIV3D_NODISCARD_CXX20
		Camera2D() = default;

		SIV3D_NODISCARD_CXX20
		Camera2D(Vec2 center, double scale = 1.0, const Camera2DParameters& parameters = Camera2DParameters::Default()) noexcept;

		void setParameters(const Camera2DParameters& parameters) noexcept;

		[[nodiscard]]
		const Camera2DParameters& getParameters() const noexcept;

		void setTargetCenter(Vec2 targetCenter) noexcept;

		void setTargetScale(double targetScale) noexcept;

		void jumpTo(Vec2 center, double scale) noexcept;

		void update(double deltaTime = Scene::DeltaTime(), SizeF sceneSize = Graphics2D::GetRenderTargetSize());

		void draw(const ColorF& color = Palette::White) const;
	};
}

# include "detail/Camera2D.ipp"
