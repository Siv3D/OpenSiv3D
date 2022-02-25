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
	template <class Type, std::enable_if_t<!std::is_same_v<std::decay_t<Type>, JSON> && std::is_constructible_v<JSON, Type>>*>
	inline JSON::JSON(const Array<Type>& arr)
		: JSON(arr.map([](auto&& v) { return JSON(v); })) {}

	template <class Type, std::enable_if_t<std::is_constructible_v<JSON, Type>>*>
	inline JSON::JSON(const std::initializer_list<Type>& list)
		: JSON(Array(list)) {}

	template <class StringViewish, std::enable_if_t<std::is_constructible_v<StringView, StringViewish>>*>
	inline JSON::JSON(const StringViewish& value)
		: JSON(StringView(value)) {}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline JSON::JSON(const SignedInt value)
		: JSON(static_cast<int64>(value)) {}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline JSON::JSON(const UnsignedInt value)
		: JSON(static_cast<uint64>(value)) {}

	SIV3D_CONCEPT_FLOATING_POINT_
	inline JSON::JSON(const Float value)
		: JSON(static_cast<double>(value)) {}

	template <class Type, std::enable_if_t<!std::is_constructible_v<StringView, Type> && !std::is_arithmetic_v<Type>>*>
	inline JSON::JSON(const Type& value)
		: JSON(Format(value)) {}

	template <class Type, std::enable_if_t<!std::is_same_v<std::decay_t<Type>, JSON> && std::is_constructible_v<JSON, Type>>*>
	inline JSON& JSON::operator =(const Array<Type>& arr)
	{
		return (*this = arr.map([](auto&& v) { return JSON(v); }));
	}

	// JSONValueType::Array
	template <class Type, std::enable_if_t<std::is_constructible_v<JSON, Type>>*>
	inline JSON& JSON::operator =(const std::initializer_list<Type>& list)
	{
		return (*this = Array(list));
	}

	template <class StringViewish, std::enable_if_t<std::is_constructible_v<StringView, StringViewish>>*>
	inline JSON& JSON::operator =(const StringViewish& value)
	{
		return operator =(StringView(value));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline JSON& JSON::operator =(const SignedInt value)
	{
		return operator =(static_cast<int64>(value));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline JSON& JSON::operator =(const UnsignedInt value)
	{
		return operator =(static_cast<uint64>(value));
	}

	SIV3D_CONCEPT_FLOATING_POINT_
	inline JSON& JSON::operator =(const Float value)
	{
		return operator =(static_cast<double>(value));
	}

	template <class Type,
		std::enable_if_t<!std::is_constructible_v<StringView, Type> && !std::is_arithmetic_v<Type>>*,
		class>
	inline JSON& JSON::operator =(const Type& value)
	{
		return operator =(Format(value));
	}

	template <class Type>
	inline Type JSON::get() const
	{
		if (const auto opt = getOpt<Type>())
		{
			return opt.value();
		}
		else
		{
			throw Error{ U"JSON::get(): Invalid JSON type. value: " + Format(*this) };
		}
	}

	template <class Type, class U>
	inline Type JSON::getOr(U&& defaultValue) const
	{
		return getOpt<Type>().value_or(std::forward<U>(defaultValue));
	}

	template <class Type>
	inline Optional<Type> JSON::getOpt() const
	{
		if constexpr (std::is_same_v<Type, String>)
		{
			return getOptString();
		}
		else if constexpr (std::is_same_v<Type, int64>)
		{
			return getOptInt64();
		}
		else if constexpr (std::is_same_v<Type, double>)
		{
			return getOptDouble();
		}
		else if constexpr (std::is_same_v<Type, bool>)
		{
			return getOptBool();
		}
		else
		{
			return getOpt_<Type>();
		}
	}

	template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader>>*>
	inline JSON JSON::Load(Reader&& reader, const AllowExceptions allowExceptions)
	{
		return Load(std::make_shared<Reader>(std::move(reader)), allowExceptions);
	}

	SIV3D_CONCEPT_INTEGRAL_
	inline Optional<Int> JSON::getOpt_() const
	{
		if (const auto opt = getOptInt64())
		{
			return static_cast<Int>(*opt);
		}

		return none;
	}

	SIV3D_CONCEPT_FLOATING_POINT_
	inline Optional<Float> JSON::getOpt_() const
	{
		if (const auto opt = getOptDouble())
		{
			return static_cast<Float>(*opt);
		}

		return none;
	}

	template <class Type, std::enable_if_t<!std::is_arithmetic_v<Type>>*>
	inline Optional<Type> JSON::getOpt_() const
	{
		if (const auto opt = getOptString())
		{
			return ParseOpt<Type>(*opt);
		}

		return none;
	}
}
