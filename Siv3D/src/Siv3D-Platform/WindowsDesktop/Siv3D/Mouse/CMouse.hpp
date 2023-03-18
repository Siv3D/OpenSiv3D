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

# pragma once
# include <mutex>
# include <Siv3D/Mouse/IMouse.hpp>
# include <Siv3D/Input/InputState.hpp>
# include <Siv3D/Windows/Windows.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Optional.hpp>

namespace s3d
{
	class CMouse final : public ISiv3DMouse
	{
	private:

		HWND m_hWnd = nullptr;

		//
		// Buttons
		//

		std::array<InputState, InputState::MouseButtonCount> m_states;

		Array<Input> m_allInputs;

		//
		// Scroll
		//

		std::mutex m_scrollMutex;

		Vec2 m_scrollInternal{ 0.0, 0.0 };

		Vec2 m_scroll{ 0.0, 0.0 };

		//
		// Multi-touch
		//

		bool m_touchAvailable = false;

		std::mutex m_touchMutex;

		Optional<DWORD> m_currentPrimaryTouchID;

		Optional<Point> m_primaryTouchPos; // Screen

	public:

		CMouse();

		~CMouse() override;

		void init() override;

		void update() override;

		bool down(uint32 index) const override;

		bool pressed(uint32 index) const override;

		bool up(uint32 index) const override;

		void clearInput(uint32 index) override;

		bool cleared(uint32 index) const override;

		Duration pressedDuration(uint32 index) const override;

		const Array<Input>& getAllInput() const noexcept override;

		const Vec2& wheel() const noexcept override;

		void onMouseButtonUpdated(int32 index, bool pressed) override;

		void onScroll(double x, double y) override;

		//
		// Windows
		//

		void onTouchInput(const Array<TOUCHINPUT>& touchInputs);

		Optional<Point> getPrimaryTouchPos();
	};
}
