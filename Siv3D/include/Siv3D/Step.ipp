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
# include "Step.hpp"

namespace s3d
{
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
				if constexpr (Index + 1 == std::tuple_size_v<Tuple>)
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
				if constexpr (Index + 1 == std::tuple_size_v<Tuple>)
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
				if constexpr (Index + 1 == std::tuple_size_v<Tuple>)
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
				if constexpr (Index + 1 == std::tuple_size_v<Tuple>)
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

			using functions_type = Tuple;

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

			template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, ValueType>>* = nullptr>
			size_t count_if(Fty f) const
			{
				size_t sum = 0;
				each([&sum, f = f](const auto& value) { sum += f(value); });
				return sum;
			}

			template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, ValueType>>* = nullptr>
			void each(Fty f) const
			{
				m_base.each([f, functions = m_functions](const auto& value)
					{
						Apply(f, value, functions);
					});
			}

			void evaluate() const
			{
				m_base.each([functions = m_functions](const auto& value)
					{
						Apply(Id, value, functions);
					});
			}

			template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, ValueType>>* = nullptr>
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

			template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, ValueType>>* = nullptr>
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

			String join(const StringView sep = U", ", const StringView begin = U"{", const StringView end = U"}") const
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

			template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, ValueType>>* = nullptr>
			constexpr auto map(Fty f) const
			{
				using Ret = std::decay_t<std::invoke_result_t<Fty, value_type>>;
				const auto functions = std::tuple_cat(m_functions, std::make_tuple(MapFunction<Fty>{ f }));
				return F_Step<StepClass, Ret, decltype(functions)>(m_base, functions);
			}

			template <class Fty, class R = std::decay_t<std::invoke_result_t<Fty, ValueType, ValueType>>>
			constexpr auto reduce(Fty f, R init) const
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

			template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, ValueType, ValueType>>* = nullptr>
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
				std::invoke_result_t<Fty, value_type, value_type> result;

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

			template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, ValueType>>* = nullptr>
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
	inline Step<T, N, S>::operator Array<typename Step<T, N, S>::value_type>() const
	{
		return asArray();
	}

	template <class T, class N, class S>
	inline Array<typename Step<T, N, S>::value_type> Step<T, N, S>::asArray() const
	{
		Array<value_type> new_array;

		if (isEmpty())
		{
			return new_array;
		}

		new_array.reserve(static_cast<size_t>(count()));
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

	template <class T, class N, class S>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, T>>*>
	inline constexpr N Step<T, N, S>::count_if(Fty f) const
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

	template <class T, class N, class S>
	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, T>>*>
	inline void Step<T, N, S>::each(Fty f) const
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

	template <class T, class N, class S>
	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, size_t, T>>*>
	inline void Step<T, N, S>::each_index(Fty f) const
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

	template <class T, class N, class S>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, T>>*>
	inline constexpr auto Step<T, N, S>::filter(Fty f) const
	{
		const auto tuple = std::make_tuple(detail::FilterFunction<Fty>{ f });
		return detail::F_Step<Step, value_type, decltype(tuple)>(*this, tuple);
	}

	template <class T, class N, class S>
	constexpr bool Step<T, N, S>::include(const value_type& x) const
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

	template <class T, class N, class S>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, T>>*>
	constexpr bool Step<T, N, S>::include_if(Fty f) const
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

	template <class T, class N, class S>
	String Step<T, N, S>::join(const StringView sep, const StringView begin, const StringView end) const
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

	template <class T, class N, class S>
	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, T>>*>
	inline constexpr auto Step<T, N, S>::map(Fty f) const
	{
		using Ret = std::decay_t<std::invoke_result_t<Fty, value_type>>;
		const auto tuple = std::make_tuple(detail::MapFunction<Fty>{ f });
		return detail::F_Step<Step, Ret, decltype(tuple)>(*this, tuple);
	}

	template <class T, class N, class S>
	template <class Fty, class R>
	constexpr auto Step<T, N, S>::reduce(Fty f, R init) const
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

	template <class T, class N, class S>
	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, T, T>>*>
	constexpr auto Step<T, N, S>::reduce1(Fty f) const
	{
		if (isEmpty())
		{
			throw std::out_of_range("Step::reduce1() reduce from empty range");
		}

		auto count_ = count();
		auto value = startValue();
		const auto step_ = step();
		std::invoke_result_t<Fty, value_type, value_type> result = value;

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

	template <class T, class N, class S>
	constexpr auto Step<T, N, S>::sum() const
	{
		using result_type = decltype(std::declval<T>() + std::declval<S>());

		if constexpr (std::is_scalar_v<result_type> || IsBigInt_v<result_type>)
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

	template <class T, class N, class S>
	Array<typename Step<T, N, S>::value_type> Step<T, N, S>::take(size_t n) const
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

	template <class T, class N, class S>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, T>>*>
	Array<typename Step<T, N, S>::value_type> Step<T, N, S>::take_while(Fty f) const
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

# ifdef SIV3D_CONCURRENT

	template <class T, class N, class S>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, T>>*>
	N Step<T, N, S>::parallel_count_if(Fty f, size_t numThreads) const
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

	template <class T, class N, class S>
	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, T>>*>
	void Step<T, N, S>::parallel_each(Fty f, size_t numThreads) const
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

# endif
}
