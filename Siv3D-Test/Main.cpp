# include <Siv3D.hpp> // OpenSiv3D v0.1.7
# include <HamFramework.hpp>
# include "Test/Siv3DTest.hpp"

namespace s3d::detail
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
		{
			*this = other;

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

			if constexpr (std::is_same_v<Ret, void>)
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
			isFinal = false;

			return m_step;
		}
	};
}

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

void Main()
{
	Range(0, 10) >> Square >> Multiplies(0.1) >> Print;

	Print << InfiniteList().map(Square).map(Plus(1)).filter(IsPrime).take(20);

	while (System::Update())
	{
		Range(0, 5) >> [](auto n) { Circle(n * 50, n * 50, 20).draw(HSV(n * 30)); };
	}
}
