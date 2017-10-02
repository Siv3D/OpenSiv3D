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
# include "Step.hpp"

namespace s3d
{
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
			
			template <class Fty, class Ret = std::result_of_t<Fty(ValueType)>>
			auto operator >>(Fty f)
			{
				m_isFinal = false;
				
				if constexpr (std::is_same<Ret, void>::value)
				{
					m_step.each(f);
				}
				else
				{
					return Evaluater_impl<StepClass, Ret, typename decltype(m_step.map(f))::functions_type>{ m_step.map(f) };
				}
			}
			
			auto get()
			{
				m_isFinal = false;
				
				return m_step;
			}
		};
	}
	
# if defined(SIV3D_TARGET_WINDOWS)
	
	template <class T, class N, class S, bool isScalar, class Fty, class Ret = std::result_of_t<Fty(T)>>
	constexpr auto operator >>(const steps_class<T, N, S, isScalar>& s, Fty f)
	{
		if constexpr (std::is_same_v<Ret, void>)
		{
			s.each(f);
		}
		else
		{
			return detail::Evaluater_impl<steps_class<T, N, S, isScalar>, Ret, typename decltype(s.map(f))::functions_type>{ s.map(f) };
		}
	}
	
# else
	
	template <class T, class N, class S, class Fty, class Ret = std::result_of_t<Fty(T)>>
	constexpr auto operator >>(const steps_class<T, N, S>& s, Fty f)
	{
		if constexpr (std::is_same<Ret, void>::value)
		{
			s.each(f);
		}
		else
		{
			return detail::Evaluater_impl<steps_class<T, N, S>, Ret, typename decltype(s.map(f))::functions_type>{ s.map(f) };
		}
	}
	
# endif
}
