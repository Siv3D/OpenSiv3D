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
# include "Array.hpp"
# include "Step.hpp"

namespace s3d
{
	template <class Type, class Allocator, class Fty, class Ret = std::invoke_result_t<Fty, Type>>
	auto operator >>(const Array<Type, Allocator>& array, Fty f)
	{
		if constexpr (std::is_same_v<Ret, void>)
		{
			array.each(f);
		}
		else
		{
			return array.map(f);
		}
	}

	namespace detail
	{
		template <class StepClass, class ValueType, class Tuple>
		class Evaluater_impl
		{
		private:
			
			F_Step<StepClass, ValueType, Tuple> m_step;
			
			bool m_isFinal = true;
			
		public:
			
			Evaluater_impl() = default;
			
			explicit Evaluater_impl(const F_Step<StepClass, ValueType, Tuple>& step)
				: m_step(step) {}
			
			Evaluater_impl(Evaluater_impl&& other)
				: m_step(other.m_step)
			{
				other.m_isFinal = false;
			}
			
			~Evaluater_impl()
			{
				if (m_isFinal)
				{
					m_step.evaluate();
				}
			}
			
			template <class Fty, class Ret = std::invoke_result_t<Fty, ValueType>, std::enable_if_t<std::is_void_v<Ret>>* = nullptr>
			void operator >>(Fty f)
			{
				m_isFinal = false;
				
				m_step.each(f);		
			}

			template <class Fty, class Ret = std::invoke_result_t<Fty, ValueType>, std::enable_if_t<!std::is_void_v<Ret>>* = nullptr>
			auto operator >>(Fty f)
			{
				m_isFinal = false;

				return Evaluater_impl<StepClass, Ret, typename decltype(m_step.map(f))::functions_type>{ m_step.map(f) };
			}
			
			auto get()
			{
				m_isFinal = false;
				
				return m_step;
			}
		};
	}

	template <class T, class N, class S, class Fty, class Ret = std::invoke_result_t<Fty, T>, std::enable_if_t<std::is_void_v<Ret>>* = nullptr>
	inline constexpr void operator >>(const Step<T, N, S>& s, Fty f)
	{
		s.each(f);
	}

	template <class T, class N, class S, class Fty, class Ret = std::invoke_result_t<Fty, T>, std::enable_if_t<!std::is_void_v<Ret>>* = nullptr>
	inline constexpr auto operator >>(const Step<T, N, S>& s, Fty f)
	{	
		return detail::Evaluater_impl<Step<T, N, S>, Ret, typename decltype(s.map(f))::functions_type>{ s.map(f) };
	}
}
