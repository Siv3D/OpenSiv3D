//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "PointVector.hpp"

namespace s3d
{
	class steps_class2D
	{
	public:

		class steps_iterator : public std::iterator<std::forward_iterator_tag, Size>
		{
			int32 m_countX;
			
			int32 m_startX;
			
			Size m_step_counter;
			
			Size m_counter;
			
			Size m_step;

		public:

			constexpr steps_iterator() noexcept
				: m_countX(0)
				, m_startX(0)
				, m_step_counter(0, 0)
				, m_counter(0, 0)
				, m_step(0, 0) {}

			constexpr steps_iterator(Size steps_count, Size start, Size step) noexcept
				: m_countX(steps_count.x)
				, m_startX(start.x)
				, m_step_counter(steps_count)
				, m_counter(start)
				, m_step(step) {}

			constexpr steps_iterator& operator ++() noexcept
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

			constexpr steps_iterator operator ++(int) noexcept
			{
				steps_iterator it = *this;

				++(*this);

				return it;
			}

			constexpr const Point& operator *() const noexcept
			{
				return m_counter;
			}

			constexpr const Point* operator ->() const noexcept
			{
				return &m_counter;
			}

			constexpr bool operator ==(const steps_iterator& r) const noexcept
			{
				return m_step_counter == r.m_step_counter;
			}

			constexpr bool operator !=(const steps_iterator& r) const noexcept
			{
				return !(m_step_counter == r.m_step_counter);
			}
		};

		typedef steps_iterator iterator;

	private:
		
		Point m_start;
		
		Size m_step_count;
		
		Size m_step_length;
		
		iterator m_end_iterator;
		
		iterator m_start_iterator;

	public:

		constexpr steps_class2D(Point start, Size step_count, Size step)
			: m_start(start)
			, m_step_count(step_count)
			, m_step_length(step)
			, m_end_iterator({ step_count.x, 0 }, Size(0, 0), Size(0, 0))
			, m_start_iterator(step_count, start, step) {}

		constexpr iterator begin() const noexcept
		{
			return m_start_iterator;
		}

		constexpr iterator end() const noexcept { return m_end_iterator; }

		constexpr Point startValue() const noexcept { return m_start; }
		
		constexpr Size count() const noexcept { return m_step_count; }

		constexpr int32 num_elements() const noexcept { return m_step_count.x * m_step_count.y; }

		constexpr Size step() const noexcept { return m_step_length; }

		constexpr bool isEmpty() const { return (m_step_count.x == 0 || m_step_count.y == 0); }

		Array<Point> asArray() const
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
	};

	inline constexpr auto step(Size n) noexcept
	{
		return steps_class2D(Point(0, 0), n, Point(1, 1));
	}

	inline constexpr auto step(Point a, Size n) noexcept
	{
		return steps_class2D(a, n, Point(1, 1));
	}

	inline constexpr auto step(Point a, Size n, Size s) noexcept
	{
		return steps_class2D(a, n, s);
	}

	inline constexpr auto step_backward(Size n) noexcept
	{
		return steps_class2D(n - Point(1, 1), n, Size(-1, -1));
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	//               Iota [beg, end)
	//

	inline constexpr auto Iota2D(Size end)
	{
		return steps_class2D(Point(0, 0), end, Point(1, 1));
	}

	inline constexpr auto Iota2D(int32 xEnd, int32 yEnd)
	{
		return Iota2D(Size(xEnd, yEnd));
	}
}
