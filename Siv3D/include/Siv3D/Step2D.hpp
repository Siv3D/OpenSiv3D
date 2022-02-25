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
		public:

			SIV3D_NODISCARD_CXX20
			constexpr Iterator() noexcept;

			SIV3D_NODISCARD_CXX20
			constexpr Iterator(Size steps_count, Size start, Size step) noexcept;

			constexpr Iterator& operator ++() noexcept;

			constexpr Iterator operator ++(int) noexcept;

			[[nodiscard]]
			constexpr const Point& operator *() const noexcept;

			[[nodiscard]]
			constexpr const Point* operator ->() const noexcept;

			[[nodiscard]]
			constexpr bool operator ==(const Iterator& r) const noexcept;

			[[nodiscard]]
			constexpr bool operator !=(const Iterator& r) const noexcept;

		private:

			int32 m_countX;

			int32 m_startX;

			Size m_step_counter;

			Size m_counter;

			Size m_step;
		};

		using iterator = Iterator;

		SIV3D_NODISCARD_CXX20
		constexpr Step2D(Point start, Size step_count, Size step) noexcept;

		[[nodiscard]]
		constexpr iterator begin() const noexcept;

		[[nodiscard]]
		constexpr iterator end() const noexcept;

		[[nodiscard]]
		constexpr Point startValue() const noexcept;

		[[nodiscard]]
		constexpr Size count() const noexcept;

		[[nodiscard]]
		constexpr int32 num_elements() const noexcept;

		[[nodiscard]]
		constexpr Size step() const noexcept;

		[[nodiscard]]
		constexpr bool isEmpty() const noexcept;

		/// @brief 範囲の値を配列に変換します。
		/// @return 配列
		[[nodiscard]]
		Array<Point> asArray() const;

	private:

		Point m_start;

		Size m_step_count;

		Size m_step_length;

		iterator m_end_iterator;

		iterator m_start_iterator;
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
