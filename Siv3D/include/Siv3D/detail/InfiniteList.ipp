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
	InfiniteList<Type>::Iterator::Iterator()
		: m_currentValue{ Type() }
		, m_step{ Type() } {}

	template <class Type>
	InfiniteList<Type>::Iterator::Iterator(const Type startValue, const Type step)
		: m_currentValue{ startValue }
		, m_step{ step } {}

	template <class Type>
	typename InfiniteList<Type>::Iterator& InfiniteList<Type>::Iterator::operator ++()
	{
		checkOverflow<Type>();

		m_currentValue += m_step;

		return *this;
	}

	template <class Type>
	typename InfiniteList<Type>::Iterator InfiniteList<Type>::Iterator::operator ++(int)
	{
		checkOverflow<Type>();

		Iterator tmp = *this;

		m_currentValue += m_step;

		return tmp;
	}

	template <class Type>
	const Type& InfiniteList<Type>::Iterator::operator *() const
	{
		return m_currentValue;
	}

	template <class Type>
	const Type* InfiniteList<Type>::Iterator::operator ->() const
	{
		return &m_currentValue;
	}

	template <class Type>
	constexpr bool InfiniteList<Type>::Iterator::operator ==(const Iterator&) const noexcept
	{
		return false;
	}

	template <class Type>
	constexpr bool InfiniteList<Type>::Iterator::operator !=(const Iterator&) const noexcept
	{
		return true;
	}

	template <class Type>
	Type InfiniteList<Type>::Iterator::currentValue() const
	{
		return m_currentValue;
	}

	template <class Type>
	Type InfiniteList<Type>::Iterator::step() const
	{
		return m_step;
	}

	template <class Type>
	template <class IntegerType>
	void InfiniteList<Type>::Iterator::checkOverflow() const
	{
		if constexpr (not std::is_same_v<IntegerType, BigInt>)
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
				if (m_currentValue < std::numeric_limits<Type>::min() - m_step)
				{
					overflow = true;
				}
			}

			if (overflow)
			{
				throw std::overflow_error("infinite_iterator: integer overflow");
			}
		}
	}

	template <class Type>
	InfiniteList<Type>::InfiniteList(const Type startValue, const Type step)
		: m_startValue{ startValue }
		, m_step{ step } {}

	template <class Type>
	typename InfiniteList<Type>::iterator InfiniteList<Type>::begin() const
	{
		return iterator{ m_startValue, m_step };
	}

	template <class Type>
	typename InfiniteList<Type>::iterator InfiniteList<Type>::end() const
	{
		return iterator{};
	}

	template <class Type>
	typename InfiniteList<Type>::value_type InfiniteList<Type>::startValue() const
	{
		return m_startValue;
	}

	template <class Type>
	typename InfiniteList<Type>::value_type InfiniteList<Type>::step() const
	{
		return m_step;
	}

	template <class Type>
	Array<typename InfiniteList<Type>::value_type> InfiniteList<Type>::take(size_t n) const
	{
		Array<value_type> new_array;

		for (auto it = begin(); n--; ++it)
		{
			new_array.push_back(*it);
		}

		return new_array;
	}

	template <class Type>
	template <class Fty>
	Array<typename InfiniteList<Type>::value_type> InfiniteList<Type>::take_while(Fty f) const
	{
		Array<value_type> new_array;

		for (auto it = begin(); f(*it); ++it)
		{
			new_array.push_back(*it);
		}

		return new_array;
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
				: m_base{ stepClass }
				, m_functions{ functions } {}

			template <class Fty>
			auto filter(Fty f) const
			{
				const auto functions = std::tuple_cat(m_functions, std::make_tuple(FilterFunction<Fty>{ f }));
				return F_InfStep<StepClass, value_type, decltype(functions)>{ m_base, functions };
			}

			template <class Fty>
			auto map(Fty f) const
			{
				using Ret = std::invoke_result_t<Fty, value_type>;
				const auto functions = std::tuple_cat(m_functions, std::make_tuple(MapFunction<Fty>{ f }));
				return F_InfStep<StepClass, Ret, decltype(functions)>{ m_base, functions };
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

					if (not finished)
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
	inline auto InfiniteList<Type>::filter(Fty f) const
	{
		const auto tuple = std::make_tuple(detail::FilterFunction<Fty>{ f });
		return detail::F_InfStep<InfiniteList, value_type, decltype(tuple)>{ *this, tuple };
	}

	template <class Type>
	template <class Fty>
	inline auto InfiniteList<Type>::map(Fty f) const
	{
		using Ret = std::invoke_result_t<Fty, value_type>;
		const auto tuple = std::make_tuple(detail::MapFunction<Fty>{ f });
		return detail::F_InfStep<InfiniteList, Ret, decltype(tuple)>{ *this, tuple };
	}
}
