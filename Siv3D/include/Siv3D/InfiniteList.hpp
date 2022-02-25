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
# include "BigInt.hpp"

namespace s3d
{
	template <class Type>
	class InfiniteList
	{
	public:

		class Iterator
		{
		public:

			SIV3D_NODISCARD_CXX20
			Iterator();

			SIV3D_NODISCARD_CXX20
			Iterator(Type startValue, Type step);

			Iterator& operator ++();

			Iterator operator ++(int);

			[[nodiscard]]
			const Type& operator *() const;

			[[nodiscard]]
			const Type* operator ->() const;

			[[nodiscard]]
			constexpr bool operator ==(const Iterator&) const noexcept;

			[[nodiscard]]
			constexpr bool operator !=(const Iterator&) const noexcept;

			[[nodiscard]]
			Type currentValue() const;

			[[nodiscard]]
			Type step() const;

		private:

			Type m_currentValue;

			Type m_step;

			template <class IntegerType>
			void checkOverflow() const;
		};

		using value_type = Type;
		using iterator = Iterator;

		SIV3D_NODISCARD_CXX20
		InfiniteList(Type startValue = 0, Type step = 1);

		[[nodiscard]]
		iterator begin() const;

		[[nodiscard]]
		iterator end() const;

		[[nodiscard]]
		value_type startValue() const;

		[[nodiscard]]
		value_type step() const;

		template <class Fty>
		auto filter(Fty f) const;

		template <class Fty>
		auto map(Fty f) const;

		[[nodiscard]]
		Array<value_type> take(size_t n) const;

		template <class Fty>
		[[nodiscard]]
		Array<value_type> take_while(Fty f) const;

	private:

		Type m_startValue;

		Type m_step;
	};
}

# include "detail/InfiniteList.ipp"
