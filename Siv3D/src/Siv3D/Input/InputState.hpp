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
# include <Siv3D/Common.hpp>
# include <Siv3D/Stopwatch.hpp>

namespace s3d
{
	struct InputState
	{
		static constexpr size_t KeyCount = 256;

		static constexpr size_t MouseButtonCount = 8;

		Duration pressedDuration{ 0 };

		Stopwatch stopwatch;

		void update(bool currentPressed);

		void reset();

		void clearInput();

		bool cleared() const noexcept;

		bool up() const noexcept;

		bool pressed() const noexcept;

		bool down() const noexcept;

	private:

		bool m_up = false;

		bool m_pressed = false;

		bool m_down = false;

		bool m_cleared = false;
	};
}
