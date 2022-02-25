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
# include "Stopwatch.hpp"

namespace s3d
{
	template <class Type>
	class EasingAB
	{
	public:

		using value_type = Type;

		SIV3D_NODISCARD_CXX20
		EasingAB() = default;

		SIV3D_NODISCARD_CXX20
		EasingAB(const value_type& a, const value_type& b, double easingFunction(double), double durationMillisec, ISteadyClock* pSteadyClock = nullptr);

		SIV3D_NODISCARD_CXX20
		EasingAB(const value_type& a, const value_type& b, double easingFunction(double), const Duration& duration = SecondsF{ 1.0 }, ISteadyClock* pSteadyClock = nullptr);
	
		void start();

		void pause();

		void resume();

		void reset();

		[[nodiscard]]
		auto easeIn() const;

		[[nodiscard]]
		auto easeOut() const;

		[[nodiscard]]
		auto easeInOut() const;

		[[nodiscard]]
		auto value() const;

		[[nodiscard]]
		const value_type& getA() const noexcept;

		[[nodiscard]]
		const value_type& getB() const noexcept;

		void setA(const value_type& value);

		void setB(const value_type& value);

		[[nodiscard]]
		bool onA() const;

		[[nodiscard]]
		bool onB() const;

		[[nodiscard]]
		double progress0_1() const;

		[[nodiscard]]
		bool isMoving() const;

		[[nodiscard]]
		bool done() const;

		[[nodiscard]]
		const Type& base() const noexcept;

		void jumpToA();

		void jumpToB();

	private:

		value_type m_a;

		value_type m_b;

		double(*m_easingFunction)(double) = nullptr;

		double m_durationMillisec = 1000.0;

		Stopwatch m_stopwatch;

		bool m_aToB = true;

		double elapsed() const
		{
			return (Min<double>(m_stopwatch.msF(), m_durationMillisec) / m_durationMillisec);
		}
	};
}

# include "detail/EasingAB.ipp"
