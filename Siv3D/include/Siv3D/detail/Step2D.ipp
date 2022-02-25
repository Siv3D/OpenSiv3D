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

# pragma once

namespace s3d
{
	inline constexpr Step2D::Iterator::Iterator() noexcept
		: m_countX{ 0 }
		, m_startX{ 0 }
		, m_step_counter{ 0, 0 }
		, m_counter{ 0, 0 }
		, m_step{ 0, 0 } {}

	inline constexpr Step2D::Iterator::Iterator(const Size steps_count, const Size start, const Size step) noexcept
		: m_countX{ steps_count.x }
		, m_startX{ start.x }
		, m_step_counter{ steps_count }
		, m_counter{ start }
		, m_step{ step } {}

	inline constexpr Step2D::Iterator& Step2D::Iterator::operator ++() noexcept
	{
		if (m_step_counter.x == 1)
		{
			m_step_counter.x = m_countX;

			--m_step_counter.y;

			m_counter.x = m_startX;

			m_counter.y = m_counter.y + m_step.y;
		}
		else
		{
			--m_step_counter.x;

			m_counter.x = m_counter.x + m_step.x;
		}

		return *this;
	}

	inline constexpr Step2D::Iterator Step2D::Iterator::operator ++(int) noexcept
	{
		Iterator it = *this;

		++(*this);

		return it;
	}

	inline constexpr const Point& Step2D::Iterator::operator *() const noexcept
	{
		return m_counter;
	}

	inline constexpr const Point* Step2D::Iterator::operator ->() const noexcept
	{
		return &m_counter;
	}

	inline constexpr bool Step2D::Iterator::operator ==(const Iterator& r) const noexcept
	{
		return m_step_counter == r.m_step_counter;
	}

	inline constexpr bool Step2D::Iterator::operator !=(const Iterator& r) const noexcept
	{
		return !(m_step_counter == r.m_step_counter);
	}

	inline constexpr Step2D::Step2D(const Point start, const Size step_count, const Size step) noexcept
		: m_start{ start }
		, m_step_count{ step_count }
		, m_step_length{ step }
		, m_end_iterator{ { step_count.x, 0 }, Size{ 0, 0 }, Size{ 0, 0 } }
		, m_start_iterator{ step_count, start, step } {}

	inline constexpr Step2D::iterator Step2D::begin() const noexcept
	{
		return m_start_iterator;
	}

	inline constexpr Step2D::iterator Step2D::end() const noexcept
	{
		return m_end_iterator;
	}

	inline constexpr Point Step2D::startValue() const noexcept
	{
		return m_start;
	}

	inline constexpr Size Step2D::count() const noexcept
	{
		return m_step_count;
	}

	inline constexpr int32 Step2D::num_elements() const noexcept
	{
		return (m_step_count.x * m_step_count.y);
	}

	inline constexpr Size Step2D::step() const noexcept
	{
		return m_step_length;
	}

	inline constexpr bool Step2D::isEmpty() const noexcept
	{
		return ((m_step_count.x == 0)
			|| (m_step_count.y == 0));
	}

	inline Array<Point> Step2D::asArray() const
	{
		Array<Point> new_array;

		if (isEmpty())
		{
			return new_array;
		}

		new_array.reserve(num_elements());

		for (auto it = m_start_iterator; it != m_end_iterator; ++it)
		{
			new_array.push_back(*it);
		}

		return new_array;
	}

	inline constexpr auto step(const Size n) noexcept
	{
		return Step2D{ Point{ 0, 0 }, n, Point{ 1, 1 } };
	}

	inline constexpr auto step(const Point a, const Size n) noexcept
	{
		return Step2D{ a, n, Point{ 1, 1 } };
	}

	inline constexpr auto step(const Point a, const Size n, const Size s) noexcept
	{
		return Step2D{ a, n, s };
	}

	inline constexpr auto step_backward(const Size n) noexcept
	{
		return Step2D{ Point{ (n.x - 1), (n.y - 1) }, n, Size{ -1, -1 } };
	}

	inline constexpr auto Iota2D(const Size end) noexcept
	{
		return Step2D{ Point{ 0, 0 }, end, Point{ 1, 1 } };
	}

	inline constexpr auto Iota2D(const int32 xEnd, const int32 yEnd) noexcept
	{
		return Iota2D(Size{ xEnd, yEnd });
	}
}
