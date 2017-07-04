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

//
// `steps_class` and `step` functions are based on
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
# include "Platform.hpp"

# if defined(SIV3D_TARGET_WINDOWS)
	# include "Step_MSVC.hpp" // constexpr workaround for MSVC2015
# else

# include <iterator>
# include <type_traits>
# include "Types.hpp"
# include "BigInt.hpp"
# include "Format.hpp"

namespace s3d
{
	template <class T, class N, class S>
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

			constexpr steps_iterator& operator ++()
			{
				--m_count;
				m_currentValue += m_step;
				return *this;
			}

			constexpr steps_iterator operator ++(int)
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

		using value_type = T;
		using iterator = steps_iterator;

		constexpr steps_class(T startValue, N count, S step)
			: m_start_iterator(startValue, count, step) {}

		constexpr iterator begin() const { return m_start_iterator; }

		constexpr iterator end() const { return m_end_iterator; }

		constexpr value_type startValue() const { return m_start_iterator.currentValue(); }

		constexpr N count() const { return m_start_iterator.count(); }

		constexpr S step() const { return m_start_iterator.step(); }

		constexpr bool isEmpty() const { return count() == 0; }

		operator Array<value_type>() const
		{
			return asArray();
		}

		Array<value_type> asArray() const
		{
			Array<value_type> new_array;

			if (isEmpty())
			{
				return new_array;
			}

			new_array.reserve(size_t(count()));
			auto count_ = count();
			auto value = startValue();
			const auto step_ = step();

			for (;;)
			{
				new_array.push_back(value);

				if (--count_)
				{
					value += step_;
				}
				else
				{
					break;
				}
			}

			return new_array;
		}

		template <class Fty>
		constexpr N count_if(Fty f) const
		{
			if (isEmpty())
			{
				return 0;
			}

			N result = 0;
			auto count_ = count();
			auto value = startValue();
			const auto step_ = step();

			for (;;)
			{
				if (f(value))
				{
					++result;
				}

				if (--count_)
				{
					value += step_;
				}
				else
				{
					break;
				}
			}

			return result;
		}

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
		void each_index(Fty f) const
		{
			if (isEmpty())
			{
				return;
			}

			auto count_ = count();
			auto value = startValue();
			const auto step_ = step();
			size_t index = 0;

			for (;;)
			{
				f(index++, value);

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
		constexpr auto filter(Fty f) const;

		constexpr bool include(const value_type& x) const
		{
			if (isEmpty())
			{
				return false;
			}

			auto count_ = count();
			auto value = startValue();
			const auto step_ = step();

			for (;;)
			{
				if (x == value)
				{
					return true;
				}

				if (--count_)
				{
					value += step_;
				}
				else
				{
					break;
				}
			}

			return false;
		}

		template <class Fty>
		constexpr bool include_if(Fty f) const
		{
			if (isEmpty())
			{
				return false;
			}

			auto count_ = count();
			auto value = startValue();
			const auto step_ = step();

			for (;;)
			{
				if (f(value))
				{
					return true;
				}

				if (--count_)
				{
					value += step_;
				}
				else
				{
					break;
				}
			}

			return false;
		}

		String join(const String& sep = S3DSTR(","), const String& begin = S3DSTR("{"), const String& end = S3DSTR("}")) const
		{
			String s;

			s.append(begin);

			if (isEmpty())
			{
				s.append(end);

				return s;
			}

			bool isFirst = true;
			auto count_ = count();
			auto value = startValue();
			const auto step_ = step();

			for (;;)
			{
				if (isFirst)
				{
					isFirst = false;
				}
				else
				{
					s.append(sep);
				}

				s.append(Format(value));

				if (--count_)
				{
					value += step_;
				}
				else
				{
					break;
				}
			}

			s.append(end);

			return s;
		}

		template <class Fty>
		constexpr auto map(Fty f) const;

		template <class Fty>
		constexpr auto reduce(Fty f, std::result_of_t<Fty(value_type, value_type)> init) const
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
		constexpr auto reduce1(Fty f) const
		{
			if (isEmpty())
			{
				throw std::out_of_range("steps_class::reduce1() reduce from empty range");
			}

			auto count_ = count();
			auto value = startValue();
			const auto step_ = step();
			std::result_of_t<Fty(value_type, value_type)> result = value;

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

		constexpr auto sum() const
		{
			using result_type = decltype(std::declval<T>() + std::declval<S>());

			if constexpr (std::is_scalar<result_type>::value)
			{
				const auto n = count();
				const auto a = startValue();
				const auto d = step();
				return n * (2 * a + (n - 1) * d) / 2;
			}
			else
			{
				return reduce(Plus<result_type>(), result_type{});
			}
		}

		Array<value_type> take(size_t n) const
		{
			Array<value_type> new_array;

			if (isEmpty() || n == 0)
			{
				return new_array;
			}

			auto count_ = count();
			auto value = startValue();
			const auto step_ = step();

			for (;;)
			{
				new_array.push_back(value);

				if (--count_ && new_array.size() < n)
				{
					value += step_;
				}
				else
				{
					break;
				}
			}

			return new_array;
		}

		template <class Fty>
		Array<value_type> take_while(Fty f) const
		{
			Array<value_type> new_array;

			if (isEmpty())
			{
				return new_array;
			}

			auto count_ = count();
			auto value = startValue();
			const auto step_ = step();

			for (;;)
			{
				if (f(value))
				{
					new_array.push_back(value);
				}
				else
				{
					break;
				}

				if (--count_)
				{
					value += step_;
				}
				else
				{
					break;
				}
			}

			return new_array;
		}

		template <class Fty>
		N parallel_count_if(Fty f, size_t numThreads = Threading::GetConcurrency()) const
		{
			if (isEmpty())
			{
				return 0;
			}

			N result = 0;
			auto count_ = count();
			auto value = startValue();
			const auto step_ = step();

			numThreads = std::max<size_t>(1, numThreads);

			const auto n = std::max<N>(1, count_ / numThreads);

			N num_processed = 0;
			const N num_all = count_;

			Array<std::future<std::size_t>> futures;

			for (; num_processed < num_all - n; num_processed += n)
			{
				futures.emplace_back(std::async(std::launch::async, [=, &f]() mutable
				{
					size_t t_result = 0;

					for (N i = 0; i < n; ++i)
					{
						t_result += f(value);

						value += step_;
					}

					return t_result;
				}));

				value += static_cast<T>(n * step_);
			}

			for (; num_processed < num_all; ++num_processed)
			{
				result += f(value);

				value += step_;
			}

			for (auto& future : futures)
			{
				result += future.get();
			}

			return result;
		}

		template <class Fty>
		void parallel_each(Fty f, size_t numThreads = Threading::GetConcurrency()) const
		{
			if (isEmpty())
			{
				return;
			}

			auto count_ = count();
			auto value = startValue();
			const auto step_ = step();

			numThreads = std::max<size_t>(1, numThreads);

			const auto n = std::max<N>(1, count_ / numThreads);

			N num_processed = 0;
			const N num_all = count_;

			Array<std::future<void>> futures;

			for (; num_processed < num_all - n; num_processed += n)
			{
				futures.emplace_back(std::async(std::launch::async, [=, &f]() mutable
				{
					for (N i = 0; i < n; ++i)
					{
						f(value);

						value += step_;
					}
				}));

				value += static_cast<T>(n * step_);
			}

			for (; num_processed < num_all; ++num_processed)
			{
				f(value);

				value += step_;
			}

			for (auto& future : futures)
			{
				future.wait();
			}
		}

		// parallel_map

	private:

		iterator m_end_iterator;

		iterator m_start_iterator;
	};

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
	inline constexpr auto step_to(T a, U b, S s = 1)
	{
		static_assert(std::is_integral<StartType>::value || IsBigInt<StartType>::value, "step_to requires integral parameters");
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
				n = diff;
			else
				n = diff / abs_s;

			n++;
		}

		return steps_class<StartType, CounterType, S>(a, n, s);
	}

	template<class T, class U, class S = int32, class StartType = std::common_type_t<T, U>, class CounterType = std::common_type_t<std::size_t, StartType>>
	inline constexpr auto step_until(T a, U b, S s = 1)
	{
		static_assert(std::is_integral<StartType>::value || IsBigInt<StartType>::value, "step_until requires integral parameters");
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
				n = diff;
			else
				n = diff / abs_s;

			CounterType finish = a + n*s;
			if (finish != static_cast<CounterType>(b))
			{
				n++;
			}
		}

		return steps_class<StartType, CounterType, S>(a, n, s);
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	//               Iota [beg, end)
	//

	template <class N>
	inline constexpr auto Iota(N end)
	{
		static_assert(std::is_integral<N>::value, "Iota: parameter should be of integral type");
		return steps_class<N, N, int32>(N(0), end, 1);
	}

	template<class T, class U, class S = int32, class StartType = std::common_type_t<T, U>, class CounterType = std::common_type_t<std::size_t, StartType>>
	inline constexpr auto Iota(T beg, U end, S step = 1)
	{
		return step_until(beg, end, step);
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	//               Range [beg, end]
	//

	template<class T, class U, class S = int32, class StartType = std::common_type_t<T, U>, class CounterType = std::common_type_t<std::size_t, StartType>>
	inline constexpr auto Range(T beg, U end, S step = 1)
	{
		return step_to(beg, end, step);
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	//               Lazy evaluation
	//
	namespace detail
	{
		template <class Fty>
		struct FilterFunction
		{
			using isMap = std::false_type;

			Fty function;

			template <class T>
			constexpr auto operator() (const T& value) const
			{
				return function(value);
			}
		};

		template <class Fty>
		struct MapFunction
		{
			using isMap = std::true_type;

			Fty function;

			template <class T>
			constexpr auto operator() (const T& value) const
			{
				return function(value);
			}
		};

		template <class F>
		struct IsMap : std::conditional_t<F::isMap::value, std::true_type, std::false_type> {};

		template <class Fty, class ValueType, size_t Index, class Tuple, class Next>
		constexpr void Apply_impl(Fty f, const ValueType& value, const Tuple& tuple)
		{
			if constexpr (IsMap<Next>::value)
			{
				if constexpr (Index + 1 == std::tuple_size<Tuple>::value)
				{
					f(std::get<Index>(tuple)(value));
				}
				else
				{
					Apply_impl<Fty, decltype(std::get<Index>(tuple)(value)), Index + 1, Tuple, std::decay_t<decltype(std::get<Index + 1>(std::declval<Tuple>()))>>(f, std::get<Index>(tuple)(value), tuple);
				}
			}
			else
			{
				if constexpr (Index + 1 == std::tuple_size<Tuple>::value)
				{
					if (std::get<Index>(tuple)(value))
					{
						f(value);
					}
				}
				else
				{
					if (std::get<Index>(tuple)(value))
					{
						Apply_impl<Fty, ValueType, Index + 1, Tuple, std::decay_t<decltype(std::get<Index + 1>(std::declval<Tuple>()))>>(f, value, tuple);
					}
				}
			}
		}

		template <class Fty, class ValueType, class Tuple>
		constexpr void Apply(Fty f, const ValueType& value, const Tuple& tuple)
		{
			Apply_impl<Fty, ValueType, 0, Tuple, std::decay_t<decltype(std::get<0>(std::declval<Tuple>()))>>(f, value, tuple);
		}

		template <class Fty, class ResultType, class ValueType, size_t Index, class Tuple, class Next>
		constexpr void Reduce_impl(Fty f, ResultType& result, const ValueType& value, const Tuple& tuple)
		{
			if constexpr (IsMap<Next>::value)
			{
				if constexpr (Index + 1 == std::tuple_size<Tuple>::value)
				{
					result = f(result, std::get<Index>(tuple)(value));
				}
				else
				{
					Reduce_impl<Fty, ResultType, decltype(std::get<Index>(tuple)(value)), Index + 1, Tuple, std::decay_t<decltype(std::get<Index + 1>(std::declval<Tuple>()))>>(f, result, std::get<Index>(tuple)(value), tuple);
				}
			}
			else
			{
				if constexpr (Index + 1 == std::tuple_size<Tuple>::value)
				{
					if (std::get<Index>(tuple)(value))
					{
						result = f(result, value);
					}
				}
				else
				{
					if (std::get<Index>(tuple)(value))
					{
						Reduce_impl<Fty, ResultType, ValueType, Index + 1, Tuple, std::decay_t<decltype(std::get<Index + 1>(std::declval<Tuple>()))>>(f, result, value, tuple);
					}
				}
			}
		}
		
		template <class Fty, class ResultType, class ValueType, class Tuple>
		constexpr void Reduce(Fty f, ResultType& result, const ValueType& value, const Tuple& tuple)
		{
			Reduce_impl<Fty, ResultType, ValueType, 0, Tuple, std::decay_t<decltype(std::get<0>(std::declval<Tuple>()))>>(f, result, value, tuple);
		}

		template <class StepClass, class ValueType, class Tuple>
		class F_Step
		{
		private:

			StepClass m_base;

			Tuple m_functions;

		public:

			using value_type = ValueType;

			constexpr F_Step(StepClass stepClass, Tuple functions)
				: m_base(stepClass)
				, m_functions(functions) {}

			operator Array<value_type>() const
			{
				return asArray();
			}

			Array<value_type> asArray() const
			{
				Array<value_type> new_array;
				each([&new_array](const auto& value) { new_array.push_back(value); });
				return new_array;
			}

			size_t count() const
			{
				size_t sum = 0;
				each([&sum](const auto) { ++sum; });
				return sum;
			}

			template <class Fty>
			size_t count_if(Fty f) const
			{
				size_t sum = 0;
				each([&sum, f = f](const auto& value) { sum += f(value); });
				return sum;
			}

			template <class Fty>
			void each(Fty f) const
			{
				m_base.each([f, functions = m_functions](const auto& value)
				{
					Apply(f, value, functions);
				});
			}

			template <class Fty>
			constexpr auto filter(Fty f) const
			{
				const auto functions = std::tuple_cat(m_functions, std::make_tuple(FilterFunction<Fty>{ f }));
				return F_Step<StepClass, value_type, decltype(functions)>(m_base, functions);
			}

			bool include(const value_type& x) const
			{
				if (m_base.isEmpty())
				{
					return false;
				}

				bool hasValue = false;
				auto count_ = m_base.count();
				auto value = m_base.startValue();
				const auto step_ = m_base.step();
				const auto includeFunc = [&hasValue, x](const auto& value) { hasValue = (value == x); };
				const auto functions = m_functions;

				for (;;)
				{
					Apply(includeFunc, value, functions);

					if (hasValue)
					{
						return true;
					}

					if (--count_)
					{
						value += step_;
					}
					else
					{
						break;
					}
				}

				return false;
			}

			template <class Fty>
			bool include_if(Fty f) const
			{
				if (m_base.isEmpty())
				{
					return false;
				}

				bool hasValue = false;
				auto count_ = m_base.count();
				auto value = m_base.startValue();
				const auto step_ = m_base.step();
				const auto includeFunc = [&hasValue, f](const auto& value) { hasValue = f(value); };
				const auto functions = m_functions;

				for (;;)
				{
					Apply(includeFunc, value, functions);

					if (hasValue)
					{
						return true;
					}

					if (--count_)
					{
						value += step_;
					}
					else
					{
						break;
					}
				}

				return false;
			}

			String join(const String& sep = S3DSTR(","), const String& begin = S3DSTR("{"), const String& end = S3DSTR("}")) const
			{
				String s;
				s.append(begin);
				bool isFirst = true;
				each([&s, &isFirst, sep = sep](const auto& value)
				{
					if (isFirst)
					{
						isFirst = false;
					}
					else
					{
						s.append(sep);
					}

					s.append(Format(value));
				});
				s.append(end);
				return s;
			}

			template <class Fty>
			constexpr auto map(Fty f) const
			{
				using Ret = std::result_of_t<Fty(value_type)>;
				const auto functions = std::tuple_cat(m_functions, std::make_tuple(MapFunction<Fty>{ f }));
				return F_Step<StepClass, Ret, decltype(functions)>(m_base, functions);
			}

			template <class Fty>
			constexpr auto reduce(Fty f, std::result_of_t<Fty(value_type, value_type)> init) const
			{
				auto result = init;

				if (m_base.isEmpty())
				{
					return result;
				}

				auto count_ = m_base.count();
				auto value = m_base.startValue();
				const auto step_ = m_base.step();
				const auto functions = m_functions;

				for (;;)
				{
					Reduce(f, result, value, functions);

					if (--count_)
					{
						value += step_;
					}
					else
					{
						break;
					}
				}

				return result;
			}

			template <class Fty>
			auto reduce1(Fty f) const
			{
				if (m_base.isEmpty())
				{
					throw std::out_of_range("F_Step::reduce1() reduce from empty range");
				}

				auto count_ = m_base.count();
				auto value = m_base.startValue();
				const auto step_ = m_base.step();
				const auto functions = m_functions;
				std::result_of_t<Fty(value_type, value_type)> result;

				Apply([&result](const auto& v) { result = v; }, value, functions);

				if (--count_ == 0)
				{
					return result;
				}

				value += step_;

				for (;;)
				{
					Reduce(f, result, value, functions);

					if (--count_)
					{
						value += step_;
					}
					else
					{
						break;
					}
				}

				return result;
			}

			template <class Type = value_type>
			Type sum() const
			{
				return reduce(Plus<Type>(), Type{});
			}

			Array<value_type> take(size_t n) const
			{
				Array<value_type> new_array;

				if (m_base.isEmpty() || n == 0)
				{
					return new_array;
				}

				auto count_ = m_base.count();
				auto value = m_base.startValue();
				const auto step_ = m_base.step();
				const auto pushFunc = [&new_array](const auto& value) { new_array.push_back(value); };
				const auto functions = m_functions;

				for (;;)
				{
					Apply(pushFunc, value, functions);

					if (--count_ && new_array.size() < n)
					{
						value += step_;
					}
					else
					{
						break;
					}
				}

				return new_array;
			}

			template <class Fty>
			Array<value_type> take_while(Fty f) const
			{
				Array<value_type> new_array;

				if (m_base.isEmpty())
				{
					return new_array;
				}

				bool finished = false;
				auto count_ = m_base.count();
				auto value = m_base.startValue();
				const auto step_ = m_base.step();
				const auto pushFunc = [&new_array, &finished, f = f](const auto& value)
				{
					if (f(value))
					{
						new_array.push_back(value);
					}
					else
					{
						finished = true;
					}
				};
				const auto functions = m_functions;

				for (;;)
				{
					Apply(pushFunc, value, functions);

					if (--count_ && !finished)
					{
						value += step_;
					}
					else
					{
						break;
					}
				}

				return new_array;
			}
		};
	}

	template <class T, class N, class S>
	template <class Fty>
	inline constexpr auto steps_class<T, N, S>::filter(Fty f) const
	{
		const auto tuple = std::make_tuple(detail::FilterFunction<Fty>{ f });
		return detail::F_Step<steps_class, value_type, decltype(tuple)>(*this, tuple);
	}

	template <class T, class N, class S>
	template <class Fty>
	inline constexpr auto steps_class<T, N, S>::map(Fty f) const
	{
		using Ret = std::result_of_t<Fty(value_type)>;
		const auto tuple = std::make_tuple(detail::MapFunction<Fty>{ f });
		return detail::F_Step<steps_class, Ret, decltype(tuple)>(*this, tuple);
	}

	template <class T, class N, class S>
	inline void Formatter(FormatData& formatData, const steps_class<T, N, S>& s)
	{
		Formatter(formatData, s.join());
	}

	template <class StepClass, class ValueType, class Tuple>
	inline void Formatter(FormatData& formatData, const detail::F_Step<StepClass, ValueType, Tuple>& s)
	{
		Formatter(formatData, s.join());
	}
}

# endif
