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
# include "Common.hpp"
# include "PointVector.hpp"
# include "Array.hpp"

namespace s3d
{
	class Step2D
	{
	public:

		class Iterator
		{
			int32 m_countX;

			int32 m_startX;

			Size m_step_counter;

			Size m_counter;

			Size m_step;

		public:

			constexpr Iterator() noexcept;

			constexpr Iterator(Size steps_count, Size start, Size step) noexcept;

			constexpr Iterator& operator ++() noexcept;

			constexpr Iterator operator ++(int) noexcept;

			constexpr const Point& operator *() const noexcept;

			constexpr const Point* operator ->() const noexcept;

			constexpr bool operator ==(const Iterator& r) const noexcept;

			constexpr bool operator !=(const Iterator& r) const noexcept;
		};

		using iterator = Iterator;

	private:

		Point m_start;

		Size m_step_count;

		Size m_step_length;

		iterator m_end_iterator;

		iterator m_start_iterator;

	public:

		constexpr Step2D(Point start, Size step_count, Size step) noexcept;

		constexpr iterator begin() const noexcept;

		constexpr iterator end() const noexcept;

		constexpr Point startValue() const noexcept;

		constexpr Size count() const noexcept;

		constexpr int32 num_elements() const noexcept;

		constexpr Size step() const noexcept;

		constexpr bool isEmpty() const noexcept;

		Array<Point> asArray() const;
	};

	[[nodiscard]]
	inline constexpr auto step(Size n) noexcept;

	[[nodiscard]]
	inline constexpr auto step(Point a, Size n) noexcept;

	[[nodiscard]]
	inline constexpr auto step(Point a, Size n, Size s) noexcept;

	[[nodiscard]]
	inline constexpr auto step_backward(Size n) noexcept;

	[[nodiscard]]
	inline constexpr auto Iota2D(Size end) noexcept;

	[[nodiscard]]
	inline constexpr auto Iota2D(int32 xEnd, int32 yEnd) noexcept;
}

# include "detail/Step2D.ipp"
