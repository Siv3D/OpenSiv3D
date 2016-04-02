//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

//
// `steps_class` and `step` are based on
// http://www.codeproject.com/Articles/876156/Convenient-Constructs-For-Stepping-Through-a-Range
//
// <author>Mikhail Semenov</author>
// <date>2015-03-14</date>
// <summary>Implementation of the steps functions</summary>
//
// Licenced with the Code Project Open Licence (CPOL)
// http://www.codeproject.com/info/cpol10.aspx
//

# pragma once
# include <iterator>
# include <type_traits>
# include "Platform.hpp"
# include "Types.hpp"
# include "String.hpp"

namespace s3d
{
	template <class T, class N, class S
		# if defined(SIV3D_TARGET_WINDOWS) // constexpr workaround for MSVC2015
			, bool isScalar = std::is_scalar<T>::value
		# endif
		>
	class steps_class
	{
	public:

		class steps_iterator : public std::iterator<std::forward_iterator_tag, T>
		{
		private:

			T m_currentValue;

			N m_count;

			S m_step;

		public:

			constexpr steps_iterator()
				: m_currentValue(T())
				, m_count(N())
				, m_step(S()) {}

			constexpr steps_iterator(T startValue, N count, S step)
				: m_currentValue(startValue)
				, m_count(count)
				, m_step(step) {}

			steps_iterator& operator ++()
			{
				--m_count;
				m_currentValue += m_step;
				return *this;
			}

			steps_iterator operator ++(int)
			{
				steps_iterator tmp = *this;
				--m_count;
				m_currentValue += m_step;
				return tmp;
			}

			constexpr const T& operator *() const { return m_currentValue; }

			constexpr const T* operator ->() const { return &m_currentValue; }

			constexpr bool operator ==(const steps_iterator& other) const { return m_count == other.m_count; }

			constexpr bool operator !=(const steps_iterator& other) const { return !(m_count == other.m_count); }

			constexpr T currentValue() const { return m_currentValue; }

			constexpr N count() const { return m_count; }

			constexpr S step() const { return m_step; }
		};

		using iterator = steps_iterator;

		constexpr steps_class(T startValue, N count, S step)
			: m_start_iterator(startValue, count, step) {}

		constexpr iterator begin() const { return m_start_iterator; }

		constexpr iterator end() const { return m_end_iterator; }

		constexpr T startValue() const { return m_start_iterator.currentValue(); }

		constexpr N count() const { return m_start_iterator.count(); }

		constexpr S step() const { return m_start_iterator.step(); }

		constexpr bool isEmpty() const { return count() == 0; }

		template <class Fty>
		void each(Fty f) const
		{
			if (isEmpty())
			{
				return;
			}

			auto count_ = count();
			auto value = startValue();
			const auto step_ = step();

			for (;;)
			{
				f(value);

				if (--count_)
				{
					value += step_;
				}
				else
				{
					break;
				}
			}
		}

		template <class Fty>
		auto reduce(Fty f, decltype(std::declval<Fty>()(std::declval<T>(), std::declval<T>())) init) const
		{
			if (isEmpty())
			{
				return init;
			}

			auto count_ = count();
			auto value = startValue();
			const auto step_ = step();

			for (;;)
			{
				init = f(init, value);

				if (--count_)
				{
					value += step_;
				}
				else
				{
					return init;
				}
			}
		}

		template <class Fty>
		auto reduce1(Fty f) const
		{
			if (isEmpty())
			{
				throw std::out_of_range("steps_class::reduce1() reduce from empty range");
			}

			auto count_ = count();
			auto value = startValue();
			const auto step_ = step();
			decltype(std::declval<Fty>()(std::declval<T>(), std::declval<T>())) result = value;

			for (;;)
			{
				if (--count_)
				{
					value += step_;
				}
				else
				{
					break;
				}

				result = f(result, value);
			}

			return result;
		}

	private:

		iterator m_end_iterator;

		iterator m_start_iterator;
	};

# if defined(SIV3D_TARGET_WINDOWS) // constexpr workaround for MSVC2015
	template <class T, class N, class S>
	class steps_class<T, N, S, false>
	{
	public:

		class steps_iterator : public std::iterator<std::forward_iterator_tag, T>
		{
		private:

			T m_currentValue;

			N m_count;

			S m_step;

		public:

			constexpr steps_iterator()
				: m_currentValue(T())
				, m_count(N())
				, m_step(S()) {}

			steps_iterator(T startValue, N count, S step)
				: m_currentValue(startValue)
				, m_count(count)
				, m_step(step) {}

			steps_iterator& operator ++()
			{
				--m_count;
				m_currentValue += m_step;
				return *this;
			}

			steps_iterator operator ++(int)
			{
				steps_iterator tmp = *this;
				--m_count;
				m_currentValue += m_step;
				return tmp;
			}

			constexpr const T& operator *() const { return m_currentValue; }

			constexpr const T* operator ->() const { return &m_currentValue; }

			constexpr bool operator ==(const steps_iterator& other) const { return m_count == other.m_count; }

			constexpr bool operator !=(const steps_iterator& other) const { return !(m_count == other.m_count); }

			T currentValue() const { return m_currentValue; }

			constexpr N count() const { return m_count; }

			constexpr S step() const { return m_step; }
		};

		using iterator = steps_iterator;

		constexpr steps_class(T startValue, N count, S step)
			: m_start_iterator(startValue, count, step) {}

		constexpr iterator begin() const { return m_start_iterator; }

		constexpr iterator end() const { return m_end_iterator; }

		constexpr T startValue() const { return m_start_iterator.currentValue(); }

		constexpr N count() const { return m_start_iterator.count(); }

		constexpr S step() const { return m_start_iterator.step(); }

		constexpr bool isEmpty() const { return count() == 0; }

		template <class Fty>
		void each(Fty f) const
		{
			if (isEmpty())
			{
				return;
			}

			auto count_ = count();
			auto value = startValue();
			const auto step_ = step();

			for (;;)
			{
				f(value);

				if (--count_)
				{
					value += step_;
				}
				else
				{
					break;
				}
			}
		}

		template <class Fty>
		auto reduce(Fty f, decltype(std::declval<Fty>()(std::declval<T>(), std::declval<T>())) init) const
		{
			if (isEmpty())
			{
				return init;
			}

			auto count_ = count();
			auto value = startValue();
			const auto step_ = step();

			for (;;)
			{
				init = f(init, value);

				if (--count_)
				{
					value += step_;
				}
				else
				{
					return init;
				}
			}
		}

		template <class Fty>
		auto reduce1(Fty f) const
		{
			if (isEmpty())
			{
				throw std::out_of_range("steps_class::reduce1() reduce from empty range");
			}

			auto count_ = count();
			auto value = startValue();
			const auto step_ = step();
			decltype(std::declval<Fty>()(std::declval<T>(), std::declval<T>())) result = value;

			for (;;)
			{
				if (--count_)
				{
					value += step_;
				}
				else
				{
					break;
				}

				result = f(result, value);
			}

			return result;
		}

	private:

		iterator m_end_iterator;

		iterator m_start_iterator;
	};
# endif

	template <class T, class N, class S = int32>
	inline constexpr auto step(T a, N n, S s = 1)
	{
		static_assert(std::is_integral<N>::value, "step: the second parameter should be of integral type");
		return steps_class<decltype(a + s), N, S>(a, n, s);
	}

	template <class N>
	inline constexpr auto step(N n)
	{
		static_assert(std::is_integral<N>::value, "step: parameter should be of integral type");
		return steps_class<N, N, int32>(N(0), n, 1);
	}

	template <class N>
	inline constexpr auto step_backward(N n)
	{
		static_assert(std::is_integral<N>::value, "step_backward: parameter should be of integral type");
		return steps_class<N, N, int32>(n + int32(-1), n, int32(-1));
	}

	template <class T, class U, class S = int32, class StartType = std::common_type_t<T, U>, class CounterType = std::common_type_t<std::size_t, StartType>>
	inline auto step_to(T a, U b, S s = 1)
	{
		static_assert(std::is_integral<StartType>::value, "step_to requires integral parameters");
		CounterType  n = 0;

		if (s == 0 || b != a && (b < a) != (s < 0))
		{
			n = 0;
		}
		else
		{
			S abs_s = s > 0 ? s : -s;
			CounterType diff = b > a ? (int64)b - (int64)a : (int64)a - (int64)b;

			if (abs_s == 1)
				n = diff;
			else
				n = diff / abs_s;

			n++;
		}

		return steps_class<StartType, CounterType, S>(a, n, s);
	}

	template<class T, class U, class S = int32, class StartType = std::common_type_t<T, U>, class CounterType = std::common_type_t<std::size_t, StartType>>
	inline auto step_until(T a, U b, S s = 1)
	{
		static_assert(std::is_integral<StartType>::value, "step_until requires integral parameters");
		CounterType  n;

		if (b == a || s == 0 || (b < a) != (s < 0))
		{
			n = 0;
		}
		else
		{
			S abs_s = s > 0 ? s : -s;
			CounterType diff = b > a ? (int64)b - (int64)a : (int64)a - (int64)b;

			if (abs_s == 1)
				n = diff;
			else
				n = diff / abs_s;

			CounterType finish = a + n*s;
			if (finish != b)
			{
				n++;
			}
		}

		return steps_class<StartType, CounterType, S>(a, n, s);
	}

	template <class N>
	inline constexpr auto Iota(N n)
	{
		static_assert(std::is_integral<N>::value, "step: parameter should be of integral type");
		return steps_class<N, N, int32>(N(0), n, 1);
	}

	template<class T, class U, class S = int32, class StartType = std::common_type_t<T, U>, class CounterType = std::common_type_t<std::size_t, StartType>>
	inline auto Iota(T a, U b, S s = 1)
	{
		return step_until(a, b, s);
	}
}
