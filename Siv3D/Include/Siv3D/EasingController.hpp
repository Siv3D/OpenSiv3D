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
# include "Easing.hpp"
# include "Stopwatch.hpp"

namespace s3d
{
	template <class Type>
	class EasingController
	{
	private:

		double(*m_easingFunction)(double) = nullptr;

		double m_durationMillisec;

		Type m_a, m_b;

		Stopwatch m_stopwatch;

		bool m_swapped = false;

		double elapsed() const
		{
			return std::min<double>(m_stopwatch.msF(), m_durationMillisec) / m_durationMillisec;
		}

	public:

		EasingController() = default;

		EasingController(double easingFunction(double), const Type& a, const Type& b, double durationMillisec)
			: m_easingFunction(easingFunction)
			, m_durationMillisec(durationMillisec)
			, m_a(a)
			, m_b(b) {}

		EasingController(double easingFunction(double), const Type& a, const Type& b, const MillisecondsF& duration = Milliseconds(1000))
			: m_easingFunction(easingFunction)
			, m_durationMillisec(static_cast<double>(duration.count()))
			, m_a(a)
			, m_b(b) {}

		void start()
		{
			if (m_stopwatch.isStarted() && m_stopwatch.ms() >= m_durationMillisec)
			{
				m_stopwatch.reset();

				m_swapped = !m_swapped;
			}

			m_stopwatch.start();
		}

		void pause()
		{
			m_stopwatch.pause();
		}

		void resume()
		{
			m_stopwatch.resume();
		}

		void reset()
		{
			m_swapped = false;

			m_stopwatch.reset();
		}

		Type easeIn() const
		{
			if (m_swapped)
			{
				return EaseIn(m_easingFunction, m_b, m_a, elapsed());
			}
			else
			{
				return EaseIn(m_easingFunction, m_a, m_b, elapsed());
			}			
		}

		Type easeOut() const
		{
			if (m_swapped)
			{
				return EaseOut(m_easingFunction, m_b, m_a, elapsed());
			}
			else
			{
				return EaseIn(m_easingFunction, m_a, m_b, elapsed());
			}
		}

		Type easeInOut() const
		{
			if (m_swapped)
			{
				return EaseInOut(m_easingFunction, m_b, m_a, elapsed());
			}
			else
			{
				return EaseInOut(m_easingFunction, m_a, m_b, elapsed());
			}
		}

		const Type& getA() const
		{
			return m_a;
		}

		const Type& getB() const
		{
			return m_b;
		}

		void setA(const Type& value)
		{
			m_a = value;
		}

		void setB(const Type& value)
		{
			m_b = value;
		}

		bool isMoving() const
		{
			return m_stopwatch.isStarted() && !done();
		}

		bool done() const
		{
			return m_stopwatch.msF() >= m_durationMillisec;
		}

		Type base() const
		{
			if (m_swapped)
			{
				return done() ? m_a : m_b;
			}
			else
			{
				return done() ? m_b : m_a;
			}
		}

		void jumpToA()
		{
			m_stopwatch.reset();

			m_swapped = false;
		}

		void jumpToB()
		{
			m_stopwatch.reset();

			m_swapped = true;
		}
	};
}
