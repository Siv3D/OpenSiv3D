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
# include <type_traits>
# include "Fwd.hpp"
# include "Array.hpp"
# include "Step.hpp"
# include "BigInt.hpp"

namespace s3d
{
	template <class Type>
	class infinite_list
	{
	private:

		Type m_startValue;

		Type m_step;

	public:

		class infinite_iterator : public std::iterator<std::forward_iterator_tag, Type>
		{
		private:

			Type m_currentValue;

			Type m_step;

			template <class IntegerType, std::enable_if_t<!IsBigInt<IntegerType>::value>* = nullptr>
			void checkOverflow() const
			{
				bool overflow = false;

				if (m_step > 0)
				{
					if (m_currentValue > std::numeric_limits<Type>::max() - m_step)
					{
						overflow = true;
					}
				}
				else if (m_step < 0)
				{
					if (m_step < 0 && m_currentValue < std::numeric_limits<Type>::min() - m_step)
					{
						overflow = true;
					}
				}

				if (overflow)
				{
					throw std::overflow_error("infinite_iterator: integer overflow");
				}
			}

			template <class IntegerType, std::enable_if_t<IsBigInt<IntegerType>::value>* = nullptr>
			void checkOverflow() const {}

		public:

			infinite_iterator()
				: m_currentValue(Type())
				, m_step(Type()) {}

			infinite_iterator(Type startValue, Type step)
				: m_currentValue(startValue)
				, m_step(step) {}

			infinite_iterator& operator ++()
			{
				checkOverflow<Type>();

				m_currentValue += m_step;

				return *this;
			}

			infinite_iterator operator ++(int)
			{
				checkOverflow<Type>();

				infinite_iterator tmp = *this;

				m_currentValue += m_step;

				return tmp;
			}

			const Type& operator *() const { return m_currentValue; }

			const Type* operator ->() const { return &m_currentValue; }

			constexpr bool operator ==(const infinite_iterator&) const { return false; }

			constexpr bool operator !=(const infinite_iterator&) const { return true; }

			Type currentValue() const { return m_currentValue; }

			Type step() const { return m_step; }
		};

		using value_type = Type;
		using iterator = infinite_iterator;

		infinite_list(Type startValue = 0, Type step = 1)
			: m_startValue(startValue)
			, m_step(step) {}

		iterator begin() const { return iterator(m_startValue, m_step); }

		iterator end() const { return iterator(); }

		value_type startValue() const { return m_startValue; }

		value_type step() const { return m_step; }

		template <class Fty>
		auto filter(Fty f) const;

		template <class Fty>
		auto map(Fty f) const;

		Array<value_type> take(size_t n) const
		{
			Array<value_type> new_array;

			for (auto it = begin(); n--; ++it)
			{
				new_array.push_back(*it);
			}

			return new_array;
		}

		template <class Fty>
		Array<value_type> take_while(Fty f) const
		{
			Array<value_type> new_array;

			for (auto it = begin(); f(*it); ++it)
			{
				new_array.push_back(*it);
			}

			return new_array;
		}
	};

	template<class T = int32, class S = int32>
	inline auto InfiniteList(T startValue = 0, S step = 1)
	{
		return infinite_list<std::common_type_t<T, S>>(startValue, step);
	}

	namespace detail
	{
		template <class StepClass, class ValueType, class Tuple>
		class F_InfStep
		{
		private:

			StepClass m_base;

			Tuple m_functions;

		public:

			using value_type = ValueType;

			F_InfStep(StepClass stepClass, Tuple functions)
				: m_base(stepClass)
				, m_functions(functions) {}

			template <class Fty>
			auto filter(Fty f) const
			{
				const auto functions = std::tuple_cat(m_functions, std::make_tuple(FilterFunction<Fty>{ f }));
				return F_InfStep<StepClass, value_type, decltype(functions)>(m_base, functions);
			}

			template <class Fty>
			auto map(Fty f) const
			{
				using Ret = std::result_of_t<Fty(value_type)>;
				const auto functions = std::tuple_cat(m_functions, std::make_tuple(MapFunction<Fty>{ f }));
				return F_InfStep<StepClass, Ret, decltype(functions)>(m_base, functions);
			}

			Array<value_type> take(size_t n) const
			{
				Array<value_type> new_array;

				if (n == 0)
				{
					return new_array;
				}

				auto it = m_base.begin();
				const auto pushFunc = [&new_array](const auto& value) { new_array.push_back(value); };
				const auto functions = m_functions;

				for (;;)
				{
					Apply(pushFunc, *it, functions);

					if (new_array.size() < n)
					{
						++it;
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

				bool finished = false;
				auto it = m_base.begin();
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
					Apply(pushFunc, *it, functions);

					if (!finished)
					{
						++it;
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

	template <class Type>
	template <class Fty>
	inline auto infinite_list<Type>::filter(Fty f) const
	{
		const auto tuple = std::make_tuple(detail::FilterFunction<Fty>{ f });
		return detail::F_InfStep<infinite_list, value_type, decltype(tuple)>(*this, tuple);
	}

	template <class Type>
	template <class Fty>
	inline auto infinite_list<Type>::map(Fty f) const
	{
		using Ret = std::result_of_t<Fty(value_type)>;
		const auto tuple = std::make_tuple(detail::MapFunction<Fty>{ f });
		return detail::F_InfStep<infinite_list, Ret, decltype(tuple)>(*this, tuple);
	}
}
