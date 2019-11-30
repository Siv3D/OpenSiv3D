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
# include <iterator>
# include "Fwd.hpp"
# include "Threading.hpp"

namespace s3d
{
	template <class T, class N, class S>
	class Step
	{
	public:

		class Iterator
		{
		private:

			T m_currentValue;

			N m_count;

			S m_step;

		public:

			constexpr Iterator()
				: m_currentValue(T())
				, m_count(N())
				, m_step(S()) {}

			constexpr Iterator(T startValue, N count, S step)
				: m_currentValue(startValue)
				, m_count(count)
				, m_step(step) {}

			constexpr Iterator& operator ++()
			{
				--m_count;
				m_currentValue += m_step;
				return *this;
			}

			constexpr Iterator operator ++(int)
			{
				Iterator tmp = *this;
				--m_count;
				m_currentValue += m_step;
				return tmp;
			}

			constexpr const T& operator *() const { return m_currentValue; }

			constexpr const T* operator ->() const { return &m_currentValue; }

			constexpr bool operator ==(const Iterator& other) const { return m_count == other.m_count; }

			constexpr bool operator !=(const Iterator& other) const { return !(m_count == other.m_count); }

			constexpr T currentValue() const { return m_currentValue; }

			constexpr N count() const { return m_count; }

			constexpr S step() const { return m_step; }
		};

		using value_type	= T;
		using iterator		= Iterator;

		constexpr Step(T startValue, N count, S step)
			: m_start_iterator(startValue, count, step) {}

		constexpr iterator begin() const { return m_start_iterator; }

		constexpr iterator end() const { return m_end_iterator; }

		constexpr value_type startValue() const { return m_start_iterator.currentValue(); }

		constexpr N count() const { return m_start_iterator.count(); }

		constexpr S step() const { return m_start_iterator.step(); }

		constexpr bool isEmpty() const { return count() == 0; }

		operator Array<value_type>() const;

		Array<value_type> asArray() const;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, T>>* = nullptr>
		constexpr N count_if(Fty f) const;

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, T>>* = nullptr>
		void each(Fty f) const;

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, size_t, T>>* = nullptr>
		void each_index(Fty f) const;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, T>>* = nullptr>
		constexpr auto filter(Fty f) const;

		constexpr bool include(const value_type& x) const;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, T>>* = nullptr>
		constexpr bool include_if(Fty f) const;

		String join(StringView sep = U", ", StringView begin = U"{", StringView end = U"}") const;

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, T>>* = nullptr>
		constexpr auto map(Fty f) const;

		template <class Fty, class R = std::decay_t<std::invoke_result_t<Fty, T, T>>>
		constexpr auto reduce(Fty f, R init) const;

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, T, T>>* = nullptr>
		constexpr auto reduce1(Fty f) const;

		constexpr auto sum() const;

		Array<value_type> take(size_t n) const;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, T>>* = nullptr>
		Array<value_type> take_while(Fty f) const;

	# ifdef SIV3D_CONCURRENT

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, T>>* = nullptr>
		N parallel_count_if(Fty f, size_t numThreads = Threading::GetConcurrency()) const;

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, T>>* = nullptr>
		void parallel_each(Fty f, size_t numThreads = Threading::GetConcurrency()) const;

		// parallel_map

	# endif

	private:

		iterator m_end_iterator;

		iterator m_start_iterator;
	};

	template <class T, class N, class S = int32,
		std::enable_if_t<std::is_integral_v<N> || IsBigInt_v<N>>* = nullptr>
	inline constexpr auto step(T a, N n, S s = 1)
	{
		return Step<decltype(a + s), N, S>(a, n, s);
	}

	template <class N,
		std::enable_if_t<std::is_integral_v<N> || IsBigInt_v<N>>* = nullptr>
	inline constexpr auto step(N n)
	{
		return Step<N, N, int32>(N(0), n, 1);
	}

	template <class N,
		std::enable_if_t<std::is_integral_v<N> || IsBigInt_v<N>>* = nullptr>
	inline constexpr auto step_backward(N n)
	{
		return Step<N, N, int32>(n + int32(-1), n, int32(-1));
	}

	template <class T, class U, class S = int32, class StartType = std::common_type_t<T, U>, class CounterType = std::common_type_t<std::size_t, StartType>,
		std::enable_if_t<std::is_integral_v<StartType> || IsBigInt_v<StartType>>* = nullptr>
	inline constexpr auto step_to(T a, U b, S s = 1)
	{
		CounterType  n = 0;
		using DiffType = std::common_type_t<int64, StartType>;

		if (s == 0 || (b != a && (b < a) != (s < 0)))
		{
			n = 0;
		}
		else
		{
			S abs_s = s > 0 ? s : -s;
			CounterType diff = b > a ? DiffType(b) - DiffType(a) : DiffType(a) - DiffType(b);

			if (abs_s == 1)
			{
				n = diff;
			}
			else
			{
				n = diff / abs_s;
			}

			n++;
		}

		return Step<StartType, CounterType, S>(a, n, s);
	}

	template<class T, class U, class S = int32, class StartType = std::common_type_t<T, U>, class CounterType = std::common_type_t<std::size_t, StartType>,
		std::enable_if_t<std::is_integral_v<StartType> || IsBigInt_v<StartType>>* = nullptr>
	inline constexpr auto step_until(T a, U b, S s = 1)
	{	
		CounterType n;
		using DiffType = std::common_type_t<int64, StartType>;

		if (b == a || s == 0 || (b < a) != (s < 0))
		{
			n = 0;
		}
		else
		{
			S abs_s = s > 0 ? s : -s;
			CounterType diff = b > a ? DiffType(b) - DiffType(a) : DiffType(a) - DiffType(b);

			if (abs_s == 1)
			{
				n = diff;
			}
			else
			{
				n = diff / abs_s;
			}

			CounterType finish = a + n * s;
			if (finish != static_cast<CounterType>(b))
			{
				n++;
			}
		}

		return Step<StartType, CounterType, S>(a, n, s);
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	//               Iota [beg, end)
	//

	template <class N,
		std::enable_if_t<std::is_integral_v<N> || IsBigInt_v<N>>* = nullptr>
	inline constexpr auto Iota(N end)
	{
		return Step<N, N, int32>(N(0), end, 1);
	}

	template<class T, class U, class S = int32, class StartType = std::common_type_t<T, U>, class CounterType = std::common_type_t<std::size_t, StartType>,
		std::enable_if_t<std::is_integral_v<StartType> || IsBigInt_v<StartType>>* = nullptr>
	inline constexpr auto Iota(T beg, U end, S step = 1)
	{
		return step_until(beg, end, step);
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	//               Range [beg, end]
	//

	template<class T, class U, class S = int32, class StartType = std::common_type_t<T, U>, class CounterType = std::common_type_t<std::size_t, StartType>,
		std::enable_if_t<std::is_integral_v<StartType> || IsBigInt_v<StartType>>* = nullptr>
	inline constexpr auto Range(T beg, U end, S step = 1)
	{
		return step_to(beg, end, step);
	}
}

# include "Step.ipp"

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	template <class T, class N, class S>
	inline void Formatter(FormatData& formatData, const Step<T, N, S>& s)
	{
		Formatter(formatData, s.join());
	}

	template <class StepClass, class ValueType, class Tuple>
	inline void Formatter(FormatData& formatData, const detail::F_Step<StepClass, ValueType, Tuple>& s)
	{
		Formatter(formatData, s.join());
	}

	template <class T, class N, class S>
	inline std::ostream& operator <<(std::ostream& output, const Step<T, N, S>& value)
	{
		return output << value.join().narrow();
	}

	template <class T, class N, class S>
	inline std::wostream& operator <<(std::wostream& output, const Step<T, N, S>& value)
	{
		return output << value.join().toWstr();
	}

	template <class StepClass, class ValueType, class Tuple>
	inline std::ostream& operator <<(std::ostream& output, const detail::F_Step<StepClass, ValueType, Tuple>& value)
	{
		return output << value.join().narrow();
	}

	template <class StepClass, class ValueType, class Tuple>
	inline std::wostream& operator <<(std::wostream& output, const detail::F_Step<StepClass, ValueType, Tuple>& value)
	{
		return output << value.join().toWstr();
	}
}
