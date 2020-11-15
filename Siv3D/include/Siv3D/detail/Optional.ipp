//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	template <class Type>
	inline constexpr Optional<Type>& Optional<Type>::operator=(const Optional& other)
	{
		if (other)
		{
			base_type::operator =(*other);
		}
		else
		{
			reset();
		}

		return *this;
	}

	template <class Type>
	inline constexpr Optional<Type>& Optional<Type>::operator=(Optional&& other) noexcept(std::is_nothrow_move_assignable_v<Type>&& std::is_nothrow_move_constructible_v<Type>)
	{
		if (other)
		{
			base_type::operator =(std::move(*other));
		}
		else
		{
			reset();
		}

		return *this;
	}

	template <class Type>
	template <class U>
	inline Optional<Type>& Optional<Type>::operator =(U&& value)
	{
		base_type::operator =(std::move(value));
		return *this;
	}

	template <class Type>
	template <class U>
	inline Optional<Type>& Optional<Type>::operator =(const Optional<U>& other)
	{
		if (other)
		{
			base_type::operator =(*other);
		}
		else
		{
			reset();
		}

		return *this;
	}

	template <class Type>
	template <class U>
	inline Optional<Type>& Optional<Type>::operator =(Optional<U>&& other)
	{
		if (other)
		{
			base_type::operator =(std::move(*other));
		}
		else
		{
			reset();
		}

		return *this;
	}

	template <class Type>
	inline void Optional<Type>::swap(Optional& other) noexcept(std::is_nothrow_move_constructible_v<Type>&& std::is_nothrow_swappable_v<Type>)
	{
		base_type::swap(other);
	}

	template <class Type>
	template <class... Args, std::enable_if_t<std::conjunction_v<std::is_copy_constructible<Type>, std::is_constructible<Type, Args...>>>*>
	[[nodiscard]]
	inline constexpr typename Optional<Type>::value_type Optional<Type>::value_or_construct(Args&&... args) const&
	{
		return static_cast<bool>(*this) ? **this : Type(std::forward<Args>(args)...);
	}

	template <class Type>
	template <class... Args, std::enable_if_t<std::conjunction_v<std::is_move_constructible<Type>, std::is_constructible<Type, Args...>>>*>
	[[nodiscard]]
	inline constexpr typename Optional<Type>::value_type Optional<Type>::value_or_construct(Args&&... args)&&
	{
		return static_cast<bool>(*this) ? std::move(**this) : Type(std::forward<Args>(args)...);
	}

	template <class Type>
	template <class Fty, std::enable_if_t<std::conjunction_v<std::is_copy_constructible<Type>, std::is_convertible<std::invoke_result_t<Fty>, Type>>>*>
	inline constexpr typename Optional<Type>::value_type Optional<Type>::value_or_eval(Fty&& f) const&
	{
		return static_cast<bool>(*this) ? **this : std::forward<Fty>(f)();
	}

	template <class Type>
	template <class Fty, std::enable_if_t<std::conjunction_v<std::is_move_constructible<Type>, std::is_convertible<std::invoke_result_t<Fty>, Type>>>*>
	inline constexpr typename Optional<Type>::value_type Optional<Type>::value_or_eval(Fty&& f)&&
	{
		return static_cast<bool>(*this) ? std::move(**this) : std::forward<Fty>(f)();
	}

	template <class Type>
	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type&>>*>
	inline constexpr void Optional<Type>::then(Fty&& f)
	{
		if (has_value())
		{
			std::forward<Fty>(f)(value());
		}
	}

	template <class Type>
	template <class Fty, std::enable_if_t<std::is_invocable_v<Fty, Type>>*>
	inline constexpr void Optional<Type>::then(Fty&& f) const
	{
		if (has_value())
		{
			std::forward<Fty>(f)(value());
		}
	}

	template <class Type>
	template <class Fty, class R>
	inline Optional<R> Optional<Type>::map(Fty f)
	{
		if (has_value())
		{
			return f(value());
		}
		else
		{
			return none;
		}
	}

	template <class Type>
	template <class Fty, class R>
	inline Optional<R> Optional<Type>::map(Fty f) const
	{
		if (has_value())
		{
			return f(value());
		}
		else
		{
			return none;
		}
	}

	template <class Type>
	inline constexpr bool operator ==(const Optional<Type>& lhs, const Optional<Type>& rhs)
	{
		const bool lhs_has_value = lhs.has_value();
		return lhs_has_value == rhs.has_value() && (!lhs_has_value || (*lhs == *rhs));
	}

	template <class Type>
	inline constexpr bool operator !=(const Optional<Type>& lhs, const Optional<Type>& rhs)
	{
		const bool lhs_has_value = lhs.has_value();
		return lhs_has_value != rhs.has_value() || (lhs_has_value && (*lhs != *rhs));
	}

	template <class Type>
	inline constexpr bool operator <(const Optional<Type>& lhs, const Optional<Type>& rhs)
	{
		return rhs.has_value() && (!lhs.has_value() || (*lhs < *rhs));
	}

	template <class Type>
	inline constexpr bool operator <=(const Optional<Type>& lhs, const Optional<Type>& rhs)
	{
		return !lhs.has_value() || (rhs.has_value() && (*lhs <= *rhs));
	}

	template <class Type>
	inline constexpr bool operator >(const Optional<Type>& lhs, const Optional<Type>& rhs)
	{
		return lhs.has_value() && (!rhs.has_value() || (*lhs > * rhs));
	}

	template <class Type>
	inline constexpr bool operator >=(const Optional<Type>& lhs, const Optional<Type>& rhs)
	{
		return !rhs.has_value() || (lhs.has_value() && (*lhs >= *rhs));
	}


	template <class Type>
	inline constexpr bool operator ==(const Optional<Type>& opt, None_t) noexcept
	{
		return !opt.has_value();
	}

	template <class Type>
	inline constexpr bool operator ==(None_t, const Optional<Type>& opt) noexcept
	{
		return !opt.has_value();
	}

	template <class Type>
	inline constexpr bool operator !=(const Optional<Type>& opt, None_t) noexcept
	{
		return opt.has_value();
	}

	template <class Type>
	inline constexpr bool operator !=(None_t, const Optional<Type>& opt) noexcept
	{
		return opt.has_value();
	}

	template <class Type>
	inline constexpr bool operator <(const Optional<Type>&, None_t) noexcept
	{
		return false;
	}

	template <class Type>
	inline constexpr bool operator <(None_t, const Optional<Type>& opt) noexcept
	{
		return opt.has_value();
	}

	template <class Type>
	inline constexpr bool operator <=(const Optional<Type>& opt, None_t) noexcept
	{
		return !opt.has_value();
	}

	template <class Type>
	inline constexpr bool operator <=(None_t, const Optional<Type>&) noexcept
	{
		return true;
	}

	template <class Type>
	inline constexpr bool operator >(const Optional<Type>& opt, None_t) noexcept
	{
		return opt.has_value();
	}

	template <class Type>
	inline constexpr bool operator >(None_t, const Optional<Type>&) noexcept
	{
		return false;
	}

	template <class Type>
	inline constexpr bool operator >=(const Optional<Type>&, None_t) noexcept
	{
		return true;
	}

	template <class Type>
	inline constexpr bool operator >=(None_t, const Optional<Type>& opt) noexcept
	{
		return !opt.has_value();
	}


	template <class Type, class U>
	inline constexpr bool operator ==(const Optional<Type>& opt, const U& value)
	{
		return opt ? *opt == value : false;
	}

	template <class Type, class U>
	inline constexpr bool operator ==(const U& value, const Optional<Type>& opt)
	{
		return opt ? value == *opt : false;
	}

	template <class Type, class U>
	inline constexpr bool operator !=(const Optional<Type>& opt, const U& value)
	{
		return opt ? *opt != value : true;
	}

	template <class Type, class U>
	inline constexpr bool operator !=(const U& value, const Optional<Type>& opt)
	{
		return opt ? value != *opt : true;
	}

	template <class Type, class U>
	inline constexpr bool operator <(const Optional<Type>& opt, const U& value)
	{
		return opt ? *opt < value : true;
	}

	template <class Type, class U>
	inline constexpr bool operator <(const U& value, const Optional<Type>& opt)
	{
		return opt ? value < *opt : false;
	}

	template <class Type, class U>
	inline constexpr bool operator <=(const Optional<Type>& opt, const U& value)
	{
		return opt ? *opt <= value : true;
	}

	template <class Type, class U>
	inline constexpr bool operator <=(const U& value, const Optional<Type>& opt)
	{
		return opt ? value <= *opt : false;
	}

	template <class Type, class U>
	inline constexpr bool operator >(const Optional<Type>& opt, const U& value)
	{
		return opt ? *opt > value : false;
	}

	template <class Type, class U>
	inline constexpr bool operator >(const U& value, const Optional<Type>& opt)
	{
		return opt ? value > * opt : true;
	}

	template <class Type, class U>
	inline constexpr bool operator >=(const Optional<Type>& opt, const U& value)
	{
		return opt ? *opt >= value : false;
	}

	template <class Type, class U>
	inline constexpr bool operator >=(const U& value, const Optional<Type>& opt)
	{
		return opt ? value >= *opt : true;
	}


	template <class Type>
	inline constexpr Optional<std::decay_t<Type>> MakeOptional(Type&& v)
	{
		return Optional<std::decay_t<Type>>{ std::forward<Type>(v) };
	}

	template <class Type, class... Args>
	inline constexpr Optional<Type> MakeOptional(Args&&... args)
	{
		return Optional<Type>{ std::in_place, std::forward<Args>(args)... };
	}

	template< class Type, class U, class... Args >
	inline constexpr Optional<Type> MakeOptional(std::initializer_list<U> il, Args&&... args)
	{
		return Optional<Type>{ std::in_place, il, std::forward<Args>(args)... };
	}

	template <class Type>
	inline void swap(Optional<Type>& a, Optional<Type>& b) noexcept(noexcept(a.swap(b)))
	{
		a.swap(b);
	}
}
