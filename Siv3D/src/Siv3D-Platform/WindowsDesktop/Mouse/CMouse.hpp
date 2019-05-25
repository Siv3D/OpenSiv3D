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

# pragma once
# include <array>
# include <mutex>
# include <Siv3D/Windows.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/Optional.hpp>
# include <Siv3D/PointVector.hpp>
# include <Mouse/IMouse.hpp>

namespace s3d
{
	class CMouse : public ISiv3DMouse
	{
	private:

		HWND m_hWnd = nullptr;

		std::array<InputState, MouseButtonCount> m_states;

		std::mutex m_scrollMutex;

		std::mutex m_touchMutex;

		Vec2 m_scrollInternal{ 0.0, 0.0 };

		Vec2 m_scroll{ 0.0, 0.0 };

		bool m_touchAvailable = false;

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

		Duration pressedDuration(uint32 index) const override;
		
		const Vec2& wheel() const override;
		
		void onScroll(double v, double h) override;

		void onMouseButtonUpdated(int32 index, bool pressed) override;

		void onTouchInput(const Array<TOUCHINPUT>& touchInputs);

		Optional<Point> getPrimaryTouchPos();

	};
}
