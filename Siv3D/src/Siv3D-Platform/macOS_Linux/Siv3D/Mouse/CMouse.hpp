//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Mouse/IMouse.hpp>
# include <Siv3D/Input/InputState.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Common/OpenGL.hpp>

namespace s3d
{
	class CMouse final : public ISiv3DMouse
	{
	private:

		GLFWwindow* m_window = nullptr;

		std::array<InputState, InputState::MouseButtonCount> m_states;

		Array<Input> m_allInputs;

		Vec2 m_scroll{ 0.0, 0.0 };

	public:

		CMouse();

		~CMouse() override;

		void init() override;

		void update() override;

		bool down(uint32 index) const override;

		bool pressed(uint32 index) const override;

		bool up(uint32 index) const override;

		Duration pressedDuration(uint32 index) const override;

		const Array<Input>& getAllInput() const noexcept override;

		const Vec2& wheel() const noexcept override;

		void onMouseButtonUpdated(int32 index, bool pressed) override;

		void onScroll(double v, double h) override;
	};
}
