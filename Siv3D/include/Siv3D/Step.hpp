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
# include "Common.hpp"
# include "Array.hpp"

namespace s3d
{
	template <class T, class N, class S>
	class Step
	{
	private:

		class Iterator
		{
		public:

			constexpr Iterator();

			constexpr Iterator(T startValue, N count, S step);

			constexpr Iterator& operator ++();

			constexpr Iterator operator ++(int);

			constexpr const T& operator *() const;

			constexpr const T* operator ->() const;

			constexpr bool operator ==(const Iterator& other) const;

			constexpr bool operator !=(const Iterator& other) const;

			constexpr T currentValue() const;

			constexpr N count() const;

			constexpr S step() const;

		private:

			T m_currentValue;

			N m_count;

			S m_step;
		};

	public:

		using value_type = T;
		using iterator = Iterator;

		SIV3D_NODISCARD_CXX20
		constexpr Step(T startValue, N count, S step);

		[[nodiscard]]
		constexpr iterator begin() const;

		[[nodiscard]]
		constexpr iterator end() const;

		[[nodiscard]]
		constexpr value_type startValue() const;

		[[nodiscard]]
		constexpr N count() const;

		[[nodiscard]]
		constexpr S step() const;

		[[nodiscard]]
		constexpr bool isEmpty() const;

		[[nodiscard]]
		operator Array<value_type>() const;

		[[nodiscard]]
		Array<value_type> asArray() const;

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, T>>* = nullptr>
		constexpr auto operator >>(Fty f) const;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, T>>* = nullptr>
		[[nodiscard]]
		constexpr N count_if(Fty f) const;

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, T>>* = nullptr>
		void each(Fty f) const;

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, size_t, T>>* = nullptr>
		void each_index(Fty f) const;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, T>>* = nullptr>
		[[nodiscard]]
		constexpr auto filter(Fty f) const;

		[[nodiscard]]
		constexpr bool include(const value_type& x) const;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, T>>* = nullptr>
		[[nodiscard]]
		constexpr bool include_if(Fty f) const;

		[[nodiscard]]
		String join(StringView sep = U", ", StringView begin = U"{", StringView end = U"}") const;

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, T>>* = nullptr>
		constexpr auto map(Fty f) const;

		template <class Fty, class R = std::decay_t<std::invoke_result_t<Fty, T, T>>>
		[[nodiscard]]
		constexpr auto reduce(Fty f, R init) const;

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, T, T>>* = nullptr>
		[[nodiscard]]
		constexpr auto reduce1(Fty f) const;

		[[nodiscard]]
		constexpr auto sum() const;

		[[nodiscard]]
		Array<value_type> take(size_t n) const;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, T>>* = nullptr>
		[[nodiscard]]
		Array<value_type> take_while(Fty f) const;

	# ifndef SIV3D_NO_CONCURRENT_API

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<bool, Fty, T>>* = nullptr>
		[[nodiscard]]
		N parallel_count_if(Fty f, size_t numThreads = Threading::GetConcurrency()) const;

		template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, T>>* = nullptr>
		void parallel_each(Fty f, size_t numThreads = Threading::GetConcurrency()) const;

		// parallel_map

	# endif

		/// @brief 
		/// @tparam CharType 
		/// @param output 
		/// @param value 
		/// @return 
		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Step& value)
		{
			return output << value.join();
		}

		/// @brief 
		/// @param formatData 
		/// @param value 
		friend void Formatter(FormatData& formatData, const Step& value)
		{
			formatData.string.append(value.join());
		}

	private:

		iterator m_end_iterator;

		iterator m_start_iterator;
	};

	template <class T, class N, class S = int32, std::enable_if_t<std::is_integral_v<N>>* = nullptr>
	[[nodiscard]]
	inline constexpr auto step(T a, N n, S s = 1);

	SIV3D_CONCEPT_INTEGRAL
	[[nodiscard]]
	inline constexpr auto step(Int n);

	SIV3D_CONCEPT_INTEGRAL
	[[nodiscard]]
	inline constexpr auto step_backward(Int n);

	template <class T, class U, class S = int32, class StartType = std::common_type_t<T, U>, class CounterType = std::common_type_t<std::size_t, StartType>, std::enable_if_t<std::is_integral_v<StartType>>* = nullptr>
	[[nodiscard]]
	inline constexpr auto step_to(T a, U b, S s = 1);

	template<class T, class U, class S = int32, class StartType = std::common_type_t<T, U>, class CounterType = std::common_type_t<std::size_t, StartType>, std::enable_if_t<std::is_integral_v<StartType>>* = nullptr>
	[[nodiscard]]
	inline constexpr auto step_until(T a, U b, S s = 1);

	////////////////////////////////////////////////////////////////////////////////
	//
	//               Iota [beg, end)
	//

	SIV3D_CONCEPT_INTEGRAL
	[[nodiscard]]
	inline constexpr auto Iota(Int end);

	template<class T, class U, class S = int32, class StartType = std::common_type_t<T, U>, class CounterType = std::common_type_t<std::size_t, StartType>, std::enable_if_t<std::is_integral_v<StartType>>* = nullptr>
	[[nodiscard]]
	inline constexpr auto Iota(T beg, U end, S step = 1);

	////////////////////////////////////////////////////////////////////////////////
	//
	//               Range [beg, end]
	//

	template<class T, class U, class S = int32, class StartType = std::common_type_t<T, U>, class CounterType = std::common_type_t<std::size_t, StartType>, std::enable_if_t<std::is_integral_v<StartType>>* = nullptr>
	[[nodiscard]]
	inline constexpr auto Range(T beg, U end, S step = 1);
}

# include "detail/Step.ipp"
