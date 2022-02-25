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
	template <class Type>
	inline EasingAB<Type>::EasingAB(const value_type& a, const value_type& b, double easingFunction(double), const double durationMillisec, ISteadyClock* pSteadyClock)
		: m_a{ a }
		, m_b{ b }
		, m_easingFunction{ easingFunction }
		, m_durationMillisec{ durationMillisec }
		, m_stopwatch{ StartImmediately::No, pSteadyClock } {}

	template <class Type>
	inline EasingAB<Type>::EasingAB(const value_type& a, const value_type& b, double easingFunction(double), const Duration& duration, ISteadyClock* pSteadyClock)
		: EasingAB{ a, b, easingFunction, static_cast<double>(duration.count() * 1000.0), pSteadyClock } {}

	template <class Type>
	inline void EasingAB<Type>::start()
	{
		if (m_stopwatch.isStarted()
			&& (m_durationMillisec <= m_stopwatch.ms()))
		{
			m_stopwatch.reset();

			m_aToB = (not m_aToB);
		}

		m_stopwatch.start();
	}

	template <class Type>
	inline void EasingAB<Type>::pause()
	{
		m_stopwatch.pause();
	}

	template <class Type>
	inline void EasingAB<Type>::resume()
	{
		m_stopwatch.resume();
	}

	template <class Type>
	inline void EasingAB<Type>::reset()
	{
		m_aToB = true;

		m_stopwatch.reset();
	}

	template <class Type>
	inline auto EasingAB<Type>::easeIn() const
	{
		if (m_aToB)
		{
			return EaseIn(m_easingFunction, m_a, m_b, elapsed());
		}
		else
		{
			return EaseIn(m_easingFunction, m_b, m_a, elapsed());
		}
	}

	template <class Type>
	inline auto EasingAB<Type>::easeOut() const
	{
		if (m_aToB)
		{
			return EaseOut(m_easingFunction, m_a, m_b, elapsed());
		}
		else
		{
			return EaseOut(m_easingFunction, m_b, m_a, elapsed());
		}
	}

	template <class Type>
	inline auto EasingAB<Type>::easeInOut() const
	{
		if (m_aToB)
		{
			return EaseInOut(m_easingFunction, m_a, m_b, elapsed());
		}
		else
		{
			return EaseInOut(m_easingFunction, m_b, m_a, elapsed());
		}
	}

	template <class Type>
	inline auto EasingAB<Type>::value() const
	{
		return easeInOut();
	}

	template <class Type>
	inline const typename EasingAB<Type>::value_type& EasingAB<Type>::getA() const noexcept
	{
		return m_a;
	}

	template <class Type>
	inline const typename EasingAB<Type>::value_type& EasingAB<Type>::getB() const noexcept
	{
		return m_b;
	}

	template <class Type>
	inline void EasingAB<Type>::setA(const value_type& value)
	{
		m_a = value;
	}

	template <class Type>
	inline void EasingAB<Type>::setB(const value_type& value)
	{
		m_b = value;
	}

	template <class Type>
	inline bool EasingAB<Type>::onA() const
	{
		if (isMoving())
		{
			return false;
		}

		if (m_aToB)
		{
			return (not done());
		}
		else
		{
			return done();
		}
	}

	template <class Type>
	inline bool EasingAB<Type>::onB() const
	{
		if (isMoving())
		{
			return false;
		}

		if (m_aToB)
		{
			return (done());
		}
		else
		{
			return (not done());
		}
	}

	template <class Type>
	inline double EasingAB<Type>::progress0_1() const
	{
		if (m_aToB)
		{
			return elapsed();
		}
		else
		{
			return (1.0 - elapsed());
		}
	}

	template <class Type>
	inline bool EasingAB<Type>::isMoving() const
	{
		return m_stopwatch.isStarted() && (not done());
	}

	template <class Type>
	inline bool EasingAB<Type>::done() const
	{
		return (m_durationMillisec <= m_stopwatch.msF());
	}

	template <class Type>
	inline const Type& EasingAB<Type>::base() const noexcept
	{
		if (m_aToB)
		{
			return done() ? m_b : m_a;
		}
		else
		{
			return done() ? m_a : m_b;
		}
	}

	template <class Type>
	inline void EasingAB<Type>::jumpToA()
	{
		m_stopwatch.reset();

		m_aToB = true;
	}

	template <class Type>
	inline void EasingAB<Type>::jumpToB()
	{
		m_stopwatch.reset();

		m_aToB = false;
	}
}
