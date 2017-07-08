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
# include <stdexcept>
# include <memory>
# include <cassert>
# include "Platform.hpp"

//////////////////////////////////////////////////////////////////////////////
//
//	Copyright (C) 2011 - 2012 Andrzej Krzemienski.
//
//	Use, modification, and distribution is subject to the Boost Software
//	License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//	http://www.boost.org/LICENSE_1_0.txt)
//

# define OPTIONAL_REQUIRES(...) typename std::enable_if_t<__VA_ARGS__::value, bool> = false

namespace s3d
{
	template <class Type> class Optional;

	template <class Type> class Optional<Type&>;

	// workaround: std utility functions aren't constexpr yet
	template <class Type>
	inline constexpr Type&& constexpr_forward(typename std::remove_reference_t<Type>& t) noexcept
	{
		return static_cast<Type&&>(t);
	}

	template <class Type>
	inline constexpr Type&& constexpr_forward(typename std::remove_reference_t<Type>&& t) noexcept
	{
		static_assert(!std::is_lvalue_reference<Type>::value);
		return static_cast<Type&&>(t);
	}

	template <class Type>
	inline constexpr typename std::remove_reference_t<Type>&& constexpr_move(Type&& t) noexcept
	{
		return static_cast<typename std::remove_reference_t<Type>&&>(t);
	}

	namespace detail
	{
		template <class Type>
		struct has_overloaded_addressof
		{
			template <class U>
			static constexpr bool has_overload(...) { return false; }

			template <class U, size_t S = sizeof(std::declval<U&>().operator&())>
			static constexpr bool has_overload(bool) { return true; }

			constexpr static bool value = has_overload<Type>(true);
		};

		template <class Type, OPTIONAL_REQUIRES(!has_overloaded_addressof<Type>)>
		constexpr Type* static_addressof(Type& ref)
		{
			return &ref;
		}

		template <class Type, OPTIONAL_REQUIRES(has_overloaded_addressof<Type>)>
		Type* static_addressof(Type& ref)
		{
			return std::addressof(ref);
		}

		template <class U>
		constexpr U convert(U v)
		{
			return v;
		}
	}

	constexpr struct trivial_init_t {} trivial_init{};

	constexpr struct in_place_t {} in_place{};

	struct None_t
	{
		struct init {};

		constexpr explicit None_t(init) {}
	};

	/// <summary>
	/// 無効値
	/// </summary>
	constexpr None_t none{ None_t::init() };

	class S3D_EXCEPTION_ABI bad_optional_access : public std::logic_error
	{
	public:
		explicit bad_optional_access(const std::string& what_arg)
			: logic_error{ what_arg } {}

		explicit bad_optional_access(const char* what_arg)
			: logic_error{ what_arg } {}
	};

	template <class Type>
	union storage_t
	{
		unsigned char dummy_;
		
		Type value_;

		constexpr storage_t(trivial_init_t) noexcept
			: dummy_() {};

		template <class... Args>
		constexpr storage_t(Args&&... args)
			: value_(constexpr_forward<Args>(args)...) {}

		~storage_t() {}
	};

	template <class Type>
	union constexpr_storage_t
	{
		unsigned char dummy_;
		
		Type value_;

		constexpr constexpr_storage_t(trivial_init_t) noexcept
			: dummy_() {};

		template <class... Args>
		constexpr constexpr_storage_t(Args&&... args)
			: value_(constexpr_forward<Args>(args)...) {}

		~constexpr_storage_t() = default;
	};

	template <class Type>
	struct optional_base
	{
		bool init_;
		
		storage_t<Type> storage_;

		constexpr optional_base() noexcept
			: init_(false)
			, storage_(trivial_init) {};

		explicit constexpr optional_base(const Type& v)
			: init_(true)
			, storage_(v) {}

		explicit constexpr optional_base(Type&& v)
			: init_(true)
			, storage_(constexpr_move(v)) {}

		template <class... Args> explicit optional_base(in_place_t, Args&&... args)
			: init_(true)
			, storage_(constexpr_forward<Args>(args)...) {}

		template <class U, class... Args, OPTIONAL_REQUIRES(std::is_constructible<Type, std::initializer_list<U>>)>
		explicit optional_base(in_place_t, std::initializer_list<U> il, Args&&... args)
			: init_(true)
			, storage_(il, std::forward<Args>(args)...) {}

		~optional_base()
		{
			if (init_)
			{
				storage_.value_.~Type();
			}
		}
	};

	template <class Type>
	struct constexpr_optional_base
	{
		bool init_;

		constexpr_storage_t<Type> storage_;

		constexpr constexpr_optional_base() noexcept
			: init_(false)
			, storage_(trivial_init) {};

		explicit constexpr constexpr_optional_base(const Type& v)
			: init_(true)
			, storage_(v) {}

		explicit constexpr constexpr_optional_base(Type&& v)
			: init_(true)
			, storage_(constexpr_move(v)) {}

		template <class... Args> explicit constexpr constexpr_optional_base(in_place_t, Args&&... args)
			: init_(true)
			, storage_(constexpr_forward<Args>(args)...) {}

		template <class U, class... Args, OPTIONAL_REQUIRES(std::is_constructible<Type, std::initializer_list<U>>)>
		constexpr explicit constexpr_optional_base(in_place_t, std::initializer_list<U> il, Args&&... args)
			: init_(true)
			, storage_(il, std::forward<Args>(args)...) {}

		~constexpr_optional_base() = default;
	};

	template <class Type>
	using OptionalBase = std::conditional_t<std::is_trivially_destructible<Type>::value, constexpr_optional_base<typename std::remove_const_t<Type>>, optional_base<typename std::remove_const_t<Type>>>;

	namespace detail
	{
		template <class Type>
		struct is_optional : std::false_type {};

		template <class Type>
		struct is_optional<Optional<Type>> : std::true_type {};

		template <>
		struct is_optional<None_t> : std::true_type {};
	}

	/// <summary>
	/// Optional
	/// </summary>
	template <class Type>
	class Optional : private OptionalBase<Type>
	{
		static_assert(!std::is_same<std::decay_t<Type>, None_t>::value, "bad Type");
		static_assert(!std::is_same<std::decay_t<Type>, in_place_t>::value, "bad Type");

		Type* dataptr()
		{
			return std::addressof(OptionalBase<Type>::storage_.value_);
		}
		
		constexpr const Type* dataptr() const
		{
			return detail::static_addressof(OptionalBase<Type>::storage_.value_);
		}

		constexpr const Type& contained_val() const&
		{
			return OptionalBase<Type>::storage_.value_;
		}
		
		Type& contained_val() &
		{
			return OptionalBase<Type>::storage_.value_;
		}
		
		Type&& contained_val() &&
		{
			return std::move(OptionalBase<Type>::storage_.value_);
		}

		void clear() noexcept
		{
			if (has_value())
			{
				dataptr()->~Type();
			}

			OptionalBase<Type>::init_ = false;
		}

		template <class... Args>
		void initialize(Args&&... args) noexcept(noexcept(Type(std::forward<Args>(args)...)))
		{
			assert(!OptionalBase<Type>::init_);
			::new (static_cast<void*>(dataptr())) Type(std::forward<Args>(args)...);
			OptionalBase<Type>::init_ = true;
		}

		template <class U, class... Args>
		void initialize(std::initializer_list<U> il, Args&&... args) noexcept(noexcept(Type(il, std::forward<Args>(args)...)))
		{
			assert(!OptionalBase<Type>::init_);
			::new (static_cast<void*>(dataptr())) Type(il, std::forward<Args>(args)...);
			OptionalBase<Type>::init_ = true;
		}

	public:

		using value_type = Type;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		constexpr Optional() noexcept
			: OptionalBase<Type>() {};
		
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param>
		/// 無効値
		/// </param>
		constexpr Optional(None_t) noexcept
			: OptionalBase<Type>() {};

		/// <summary>
		/// コピーコンストラクタ
		/// </summary>
		/// <param name="rhs">
		/// 他の Optional オブジェクト
		/// </param>
		Optional(const Optional& rhs)
			: OptionalBase<Type>()
		{
			if (rhs.has_value()) {
				::new (static_cast<void*>(dataptr())) Type(*rhs);
				OptionalBase<Type>::init_ = true;
			}
		}

		/// <summary>
		/// ムーブコンストラクタ
		/// </summary>
		/// <param name="rhs">
		/// 他の Optional オブジェクト
		/// </param>
		Optional(Optional&& rhs) noexcept(std::is_nothrow_move_constructible<Type>::value)
			: OptionalBase<Type>()
		{
			if (rhs.has_value())
			{
				::new (static_cast<void*>(dataptr())) Type(std::move(*rhs));
				OptionalBase<Type>::init_ = true;
			}
		}

		/// <summary>
		/// コピーコンストラクタ
		/// </summary>
		/// <param name="rhs">
		/// 他の Optional オブジェクト
		/// </param>
		constexpr Optional(const Type& v)
			: OptionalBase<Type>(v) {}

		/// <summary>
		/// ムーブコンストラクタ
		/// </summary>
		/// <param name="rhs">
		/// 他の Optional オブジェクト
		/// </param>
		constexpr Optional(Type&& v)
			: OptionalBase<Type>(constexpr_move(v)) {}

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="args">
		/// 値のコンストラクタ引数
		/// </param>
		template <class... Args>
		constexpr explicit Optional(in_place_t, Args&&... args)
			: OptionalBase<Type>(in_place_t{}, constexpr_forward<Args>(args)...) {}

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="args">
		/// 値のコンストラクタ引数
		/// </param>
		template <class U, class... Args, OPTIONAL_REQUIRES(std::is_constructible<Type, std::initializer_list<U>>)>
		constexpr explicit Optional(in_place_t, std::initializer_list<U> il, Args&&... args)
			: OptionalBase<Type>(in_place_t{}, il, constexpr_forward<Args>(args)...) {}

		/// <summary>
		/// デストラクタ
		/// </summary>
		~Optional() = default;

		/// <summary>
		/// 代入演算子
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		Optional& operator = (None_t) noexcept
		{
			clear();
			return *this;
		}

		/// <summary>
		/// 代入演算子
		/// </summary>
		/// <param name="rhs">
		/// 他の Optional オブジェクト
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		Optional& operator = (const Optional& rhs)
		{
			if (has_value() == true && rhs.has_value() == false) clear();
			else if (has_value() == false && rhs.has_value() == true) initialize(*rhs);
			else if (has_value() == true && rhs.has_value() == true) contained_val() = *rhs;
			return *this;
		}

		/// <summary>
		/// ムーブ代入演算子
		/// </summary>
		/// <param name="rhs">
		/// 他の Optional オブジェクト
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		Optional& operator = (Optional&& rhs)
			noexcept(std::is_nothrow_move_assignable<Type>::value && std::is_nothrow_move_constructible<Type>::value)
		{
			if (has_value() == true && rhs.has_value() == false) clear();
			else if (has_value() == false && rhs.has_value() == true) initialize(std::move(*rhs));
			else if (has_value() == true && rhs.has_value() == true) contained_val() = std::move(*rhs);
			return *this;
		}

		/// <summary>
		/// ムーブ代入演算子
		/// </summary>
		/// <param name="v">
		/// 他のオブジェクト
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		template <class U>
		auto operator = (U&& v)
			-> typename std::enable_if_t<std::is_same<std::decay_t<U>, Type>::value, Optional&>
		{
			if (has_value()) { contained_val() = std::forward<U>(v); }
			else { initialize(std::forward<U>(v)); }
			return *this;
		}

		/// <summary>
		/// Optional オブジェクトを初期化します。
		/// </summary>
		/// <param name="args">
		/// 値のコンストラクタ引数
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		template <class... Args>
		void emplace(Args&&... args)
		{
			clear();
			initialize(std::forward<Args>(args)...);
		}

		/// <summary>
		/// Optional オブジェクトを初期化します。
		/// </summary>
		/// <param name="il">
		/// 値のコンストラクタ引数
		/// </param>
		/// <param name="args">
		/// 値のコンストラクタ引数
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		template <class U, class... Args>
		void emplace(std::initializer_list<U> il, Args&&... args)
		{
			clear();
			initialize<U, Args...>(il, std::forward<Args>(args)...);
		}

		/// <summary>
		/// 別の Optional オブジェクトと中身を入れ替えます。
		/// </summary>
		/// <param name="another">
		/// 別の Optional オブジェクト
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void swap(Optional<Type>& rhs) noexcept(std::is_nothrow_move_constructible<Type>::value && noexcept(std::swap(std::declval<Type&>(), std::declval<Type&>())))
		{
			if (has_value() == true && rhs.has_value() == false) { rhs.initialize(std::move(**this)); clear(); }
			else if (has_value() == false && rhs.has_value() == true) { initialize(std::move(*rhs)); rhs.clear(); }
			else if (has_value() == true && rhs.has_value() == true) { using std::swap; swap(**this, *rhs); }
		}

		/// <summary>
		/// 中身があるかを返します。
		/// </summary>
		/// <returns>
		/// 中身が none ではない場合 true, それ以外の場合は false
		/// </returns>
		constexpr explicit operator bool() const noexcept
		{
			return has_value();
		}

		/// <summary>
		/// 中身があるかを返します。
		/// </summary>
		/// <returns>
		/// 中身が none ではない場合 true, それ以外の場合は false
		/// </returns>
		constexpr bool has_value() const noexcept
		{
			return OptionalBase<Type>::init_;
		}

		/// <summary>
		/// 中身へのポインタを返します。
		/// </summary>
		/// <remarks>
		/// 中身が none の場合の動作は未定義です。
		/// </remarks>
		/// <returns>
		/// 中身へのポインタ
		/// </returns>
		constexpr Type const* operator -> () const
		{
			assert(has_value());
			return dataptr();
		}

		/// <summary>
		/// 中身へのポインタを返します。
		/// </summary>
		/// <remarks>
		/// 中身が none の場合の動作は未定義です。
		/// </remarks>
		/// <returns>
		/// 中身へのポインタ
		/// </returns>
		Type* operator -> ()
		{
			assert(has_value());
			return dataptr();
		}

		/// <summary>
		/// 中身の参照を返します。
		/// </summary>
		/// <remarks>
		/// 中身が none の場合の動作は未定義です。
		/// </remarks>
		/// <returns>
		/// 中身の参照
		/// </returns>
		constexpr Type const& operator * () const
		{
			assert(has_value());
			return contained_val();
		}

		/// <summary>
		/// 中身の参照を返します。
		/// </summary>
		/// <remarks>
		/// 中身が none の場合の動作は未定義です。
		/// </remarks>
		/// <returns>
		/// 中身の参照
		/// </returns>
		Type& operator * ()
		{
			assert(has_value());
			return contained_val();
		}

		/// <summary>
		/// 中身の参照を返します。
		/// </summary>
		/// <exception cref="bad_optional_access">
		/// 中身が none の場合 throw されます。
		/// </exception>
		/// <returns>
		/// 中身の参照
		/// </returns>
		constexpr Type const& value() const
		{
			if (!has_value())
			{
				throw bad_optional_access("bad Optional access");
			}

			return contained_val();
		}

		/// <summary>
		/// 中身の参照を返します。
		/// </summary>
		/// <exception cref="bad_optional_access">
		/// 中身が none の場合 throw されます。
		/// </exception>
		/// <returns>
		/// 中身の参照
		/// </returns>
		Type& value()
		{
			if (!has_value())
			{
				throw bad_optional_access("bad Optional access");
			}

			return contained_val();
		}

		/// <summary>
		/// 中身がある場合はその値を、それ以外の場合は v を返します。
		/// </summary>
		/// <param name="v">
		/// 中身が none の場合に返ってくる値
		/// </param>
		/// <returns>
		/// 中身がある場合はその値、それ以外の場合は v
		/// </returns>
		template <class V>
		constexpr Type value_or(V&& v) const&
		{
			return *this ? **this : detail::convert<Type>(constexpr_forward<V>(v));
		}

		/// <summary>
		/// 中身がある場合はその値を、それ以外の場合は v を返します。
		/// </summary>
		/// <param name="v">
		/// 中身が none の場合に返ってくる値
		/// </param>
		/// <returns>
		/// 中身がある場合はその値、それ以外の場合は v
		/// </returns>
		template <class V>
		Type value_or(V&& v) &&
		{
			return *this ? constexpr_move(const_cast<Optional<Type>&>(*this).contained_val()) : detail::convert<Type>(constexpr_forward<V>(v));
		}

		/// <summary>
		/// 中身を none にします。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void reset() noexcept
		{
			clear();
		}

		/// <summary>
		/// 中身に別の値を代入します。
		/// </summary>
		/// <param name="v">
		/// コピーする値
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void reset(const Type& v)
		{
			emplace(v);
		}

		/// <summary>
		/// 中身がある場合に、その値を引数に関数 f を呼びます。
		/// </summary>
		/// <param name="f">
		/// 中身の値と同じ型を引数にとる関数
		/// </param>
		/// <returns>
		/// 中身がある場合は関数 f の戻り値の Optional, それ以外の場合は none
		/// </returns>
		template <class Fty, std::enable_if_t<detail::is_optional<std::result_of_t<Fty(Type)>>::value>* = nullptr>
		std::result_of_t<Fty(Type)> then(Fty f)
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

		/// <summary>
		/// 中身がある場合に、その値を引数に関数 f を呼びます。
		/// </summary>
		/// <param name="f">
		/// 中身の値と同じ型を引数にとる関数
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		template <class Fty, std::enable_if_t<
			   !detail::is_optional<std::result_of_t<Fty(Type)>>::value
			&& std::is_void<std::result_of_t<Fty(Type)>>::value>* = nullptr>
		void then(Fty f)
		{
			if (has_value())
			{
				f(value());
			}
		}

		/// <summary>
		/// 中身がある場合に、その値を引数に関数 f を呼びます。
		/// </summary>
		/// <param name="f">
		/// 中身の値と同じ型を引数にとる関数
		/// </param>
		/// <returns>
		/// 中身がある場合は関数 f の戻り値の Optional, それ以外の場合は none
		/// </returns>
		template <class Fty, std::enable_if_t<
			   !detail::is_optional<std::result_of_t<Fty(Type)>>::value
			&& !std::is_void<std::result_of_t<Fty(Type)>>::value>* = nullptr>
		Optional<std::result_of_t<Fty(Type)>> then(Fty f)
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

		/// <summary>
		/// 中身がある場合に、その値を引数に関数 f を呼びます。
		/// </summary>
		/// <param name="f">
		/// 中身の値と同じ型を引数にとる関数
		/// </param>
		/// <returns>
		/// 中身がある場合は関数 f の戻り値, それ以外の場合は none
		/// </returns>
		template <class Fty, std::enable_if_t<detail::is_optional<std::result_of_t<Fty(Type)>>::value>* = nullptr>
		std::result_of_t<Fty(Type)> then(Fty f) const
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

		/// <summary>
		/// 中身がある場合に、その値を引数に関数 f を呼びます。
		/// </summary>
		/// <param name="f">
		/// 中身の値と同じ型を引数にとる関数
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		template <class Fty, std::enable_if_t<
			   !detail::is_optional<std::result_of_t<Fty(Type)>>::value
			&& std::is_void<std::result_of_t<Fty(Type)>>::value>* = nullptr>
		void then(Fty f) const
		{
			if (has_value())
			{
				f(value());
			}
		}

		/// <summary>
		/// 中身がある場合に、その値を引数に関数 f を呼びます。
		/// </summary>
		/// <param name="f">
		/// 中身の値と同じ型を引数にとる関数
		/// </param>
		/// <returns>
		/// 中身がある場合は関数 f の戻り値の Optional, それ以外の場合は none
		/// </returns>
		template <class Fty, std::enable_if_t<
			   !detail::is_optional<std::result_of_t<Fty(Type)>>::value
			&& !std::is_void<std::result_of_t<Fty(Type)>>::value>* = nullptr>
		Optional<std::result_of_t<Fty(Type)>> then(Fty f) const
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

		/// <summary>
		/// 中身がある場合に、その値を引数に関数 f1 を呼び、それ以外の場合に関数 f2 を呼びます。
		/// </summary>
		/// <param name="f1">
		/// 中身があるときに呼び出す関数
		/// </param>
		/// </summary>
		/// <param name="f2">
		/// 中身が無いときに呼び出す関数
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		template <class HasFty, class NoneFty>
		void then(HasFty f1, NoneFty f2)
		{
			if (has_value())
			{
				f1(value());
			}
			else
			{
				f2();
			}
		}

		/// <summary>
		/// 中身がある場合に、その値を引数に関数 f1 を呼び、それ以外の場合に関数 f2 を呼びます。
		/// </summary>
		/// <param name="f1">
		/// 中身があるときに呼び出す関数
		/// </param>
		/// </summary>
		/// <param name="f2">
		/// 中身が無いときに呼び出す関数
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		template <class HasFty, class NoneFty>
		void then(HasFty f1, NoneFty f2) const
		{
			if (has_value())
			{
				f1(value());
			}
			else
			{
				f2();
			}
		}
	};

	/// <summary>
	/// Optional
	/// </summary>
	template <class Type>
	class Optional<Type&>
	{
		static_assert(!std::is_same<Type, None_t>::value, "bad Type");
		static_assert(!std::is_same<Type, in_place_t>::value, "bad Type");
			
		Type* ref;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		constexpr Optional() noexcept
			: ref(nullptr) {}

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param>
		/// 無効値
		/// </param>
		constexpr Optional(None_t) noexcept
			: ref(nullptr) {}

		/// <summary>
		/// コピーコンストラクタ
		/// </summary>
		/// <param name="rhs">
		/// 他の Optional オブジェクト
		/// </param>
		constexpr Optional(Type& v) noexcept
			: ref(detail::static_addressof(v)) {}

		Optional(Type&&) = delete;

		/// <summary>
		/// コピーコンストラクタ
		/// </summary>
		/// <param name="rhs">
		/// 他の Optional オブジェクト
		/// </param>
		constexpr Optional(const Optional& rhs) noexcept
			: ref(rhs.ref) {}

		/// <summary>
		/// コピーコンストラクタ
		/// </summary>
		/// <param name="rhs">
		/// 他の Optional オブジェクト
		/// </param>
		explicit constexpr Optional(in_place_t, Type& v) noexcept
			: ref(detail::static_addressof(v)) {}

		explicit Optional(in_place_t, Type&&) = delete;

		/// <summary>
		/// デストラクタ
		/// </summary>
		~Optional() = default;

		/// <summary>
		/// 代入演算子
		/// </summary>
		/// <returns>
		/// *this
		/// </returns>
		Optional& operator = (None_t) noexcept
		{
			ref = nullptr;
			return *this;
		}

		//	Optional& operator = (const Optional& rhs) noexcept
		//	{
		//		ref = rhs.ref;
		//		return *this;
		//	}

		//	Optional& operator = (Optional&& rhs) noexcept
		//	{
		//		ref = rhs.ref;
		//		return *this;
		//	}

		/// <summary>
		/// 代入演算子
		/// </summary>
		/// <param name="rhs">
		/// 他の Optional オブジェクト
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		template <class U>
		auto operator = (U&& rhs) noexcept
			-> typename std::enable_if_t<std::is_same<std::decay_t<U>, Optional<Type&>>::value, Optional&>
		{
			ref = rhs.ref;
			return *this;
		}

		/// <summary>
		/// ムーブ代入演算子
		/// </summary>
		/// <param name="rhs">
		/// 他の Optional オブジェクト
		/// </param>
		/// <returns>
		/// *this
		/// </returns>
		template <class U>
		auto operator =(U&& rhs) noexcept
			-> typename std::enable_if_t<!std::is_same<std::decay_t<U>, Optional<Type&>>::value, Optional&> = delete;

		/// <summary>
		/// Optional オブジェクトを初期化します。
		/// </summary>
		/// <param name="v">
		/// 新しい値
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void emplace(Type& v) noexcept
		{
			ref = detail::static_addressof(v);
		}

		void emplace(Type&&) = delete;

		/// <summary>
		/// 別の Optional オブジェクトと中身を入れ替えます。
		/// </summary>
		/// <param name="another">
		/// 別の Optional オブジェクト
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void swap(Optional<Type&>& rhs) noexcept
		{
			std::swap(ref, rhs.ref);
		}

		/// <summary>
		/// 中身があるかを返します。
		/// </summary>
		/// <returns>
		/// 中身が none ではない場合 true, それ以外の場合は false
		/// </returns>
		explicit constexpr operator bool() const noexcept
		{
			return has_value();
		}

		/// <summary>
		/// 中身があるかを返します。
		/// </summary>
		/// <returns>
		/// 中身が none ではない場合 true, それ以外の場合は false
		/// </returns>
		constexpr bool has_value() const noexcept
		{
			return ref != nullptr;
		}

		/// <summary>
		/// 中身へのポインタを返します。
		/// </summary>
		/// <remarks>
		/// 中身が none の場合の動作は未定義です。
		/// </remarks>
		/// <returns>
		/// 中身へのポインタ
		/// </returns>
		constexpr Type* operator -> () const
		{
			assert(ref);
			return ref;
		}

		/// <summary>
		/// 中身の参照を返します。
		/// </summary>
		/// <remarks>
		/// 中身が none の場合の動作は未定義です。
		/// </remarks>
		/// <returns>
		/// 中身の参照
		/// </returns>
		constexpr Type& operator * () const
		{
			assert(ref);
			return *ref;
		}

		/// <summary>
		/// 中身の参照を返します。
		/// </summary>
		/// <exception cref="bad_optional_access">
		/// 中身が none の場合 throw されます。
		/// </exception>
		/// <returns>
		/// 中身の参照
		/// </returns>
		constexpr Type& value() const
		{
			if (!ref)
			{
				throw bad_optional_access("bad Optional access");		
			}

			return *ref;
		}

		/// <summary>
		/// 中身がある場合はその値を、それ以外の場合は v を返します。
		/// </summary>
		/// <param name="v">
		/// 中身が none の場合に返ってくる値
		/// </param>
		/// <returns>
		/// 中身がある場合はその値、それ以外の場合は v
		/// </returns>
		template <class V>
		constexpr std::decay_t<Type> value_or(V&& v) const
		{
			return *this ? **this : detail::convert<std::decay_t<Type>>(constexpr_forward<V>(v));
		}

		/// <summary>
		/// 中身を none にします。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void reset() noexcept
		{
			ref = nullptr;
		}

		/// <summary>
		/// 中身に別の値を代入します。
		/// </summary>
		/// <param name="v">
		/// コピーする値
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void reset(Type& v) noexcept
		{
			emplace(v);
		}

		/// <summary>
		/// 中身がある場合に、その値を引数に関数 f を呼びます。
		/// </summary>
		/// <param name="f">
		/// 中身の値と同じ型を引数にとる関数
		/// </param>
		/// <returns>
		/// 中身がある場合は関数 f の戻り値の Optional, それ以外の場合は none
		/// </returns>
		template <class Fty, std::enable_if_t<detail::is_optional<std::result_of_t<Fty(Type&)>>::value>* = nullptr>
		std::result_of_t<Fty(Type&)> then(Fty f)
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

		/// <summary>
		/// 中身がある場合に、その値を引数に関数 f を呼びます。
		/// </summary>
		/// <param name="f">
		/// 中身の値と同じ型を引数にとる関数
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		template <class Fty, std::enable_if_t<
			   !detail::is_optional<std::result_of_t<Fty(Type&)>>::value
			&& std::is_void<std::result_of_t<Fty(Type&)>>::value>* = nullptr>
		void then(Fty f)
		{
			if (has_value())
			{
				f(value());
			}
		}

		/// <summary>
		/// 中身がある場合に、その値を引数に関数 f を呼びます。
		/// </summary>
		/// <param name="f">
		/// 中身の値と同じ型を引数にとる関数
		/// </param>
		/// <returns>
		/// 中身がある場合は関数 f の戻り値の Optional, それ以外の場合は none
		/// </returns>
		template <class Fty, std::enable_if_t<
			   !detail::is_optional<std::result_of_t<Fty(Type&)>>::value
			&& !std::is_void<std::result_of_t<Fty(Type&)>>::value>* = nullptr>
		Optional<std::result_of_t<Fty(Type&)>> then(Fty f)
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

		/// <summary>
		/// 中身がある場合に、その値を引数に関数 f を呼びます。
		/// </summary>
		/// <param name="f">
		/// 中身の値と同じ型を引数にとる関数
		/// </param>
		/// <returns>
		/// 中身がある場合は関数 f の戻り値, それ以外の場合は none
		/// </returns>
		template <class Fty, std::enable_if_t<detail::is_optional<std::result_of_t<Fty(Type&)>>::value>* = nullptr>
		std::result_of_t<Fty(Type&)> then(Fty f) const
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

		/// <summary>
		/// 中身がある場合に、その値を引数に関数 f を呼びます。
		/// </summary>
		/// <param name="f">
		/// 中身の値と同じ型を引数にとる関数
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		template <class Fty, std::enable_if_t<
			   !detail::is_optional<std::result_of_t<Fty(Type&)>>::value
			&& std::is_void<std::result_of_t<Fty(Type&)>>::value>* = nullptr>
		void then(Fty f) const
		{
			if (has_value())
			{
				f(value());
			}
		}

		/// <summary>
		/// 中身がある場合に、その値を引数に関数 f を呼びます。
		/// </summary>
		/// <param name="f">
		/// 中身の値と同じ型を引数にとる関数
		/// </param>
		/// <returns>
		/// 中身がある場合は関数 f の戻り値の Optional, それ以外の場合は none
		/// </returns>
		template <class Fty, std::enable_if_t<
			   !detail::is_optional<std::result_of_t<Fty(Type&)>>::value
			&& !std::is_void<std::result_of_t<Fty(Type&)>>::value>* = nullptr>
		Optional<std::result_of_t<Fty(Type&)>> then(Fty f) const
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

		/// <summary>
		/// 中身がある場合に、その値を引数に関数 f1 を呼び、それ以外の場合に関数 f2 を呼びます。
		/// </summary>
		/// <param name="f1">
		/// 中身があるときに呼び出す関数
		/// </param>
		/// </summary>
		/// <param name="f2">
		/// 中身が無いときに呼び出す関数
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		template <class HasFty, class NoneFty>
		void then(HasFty f1, NoneFty f2)
		{
			if (has_value())
			{
				f1(value());
			}
			else
			{
				f2();
			}
		}

		/// <summary>
		/// 中身がある場合に、その値を引数に関数 f1 を呼び、それ以外の場合に関数 f2 を呼びます。
		/// </summary>
		/// <param name="f1">
		/// 中身があるときに呼び出す関数
		/// </param>
		/// </summary>
		/// <param name="f2">
		/// 中身が無いときに呼び出す関数
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		template <class HasFty, class NoneFty>
		void then(HasFty f1, NoneFty f2) const
		{
			if (has_value())
			{
				f1(value());
			}
			else
			{
				f2();
			}
		}
	};

	template <class Type>
	class Optional<Type&&>
	{
		static_assert(sizeof(Type) == 0, "Optional rvalue referencs disallowed");
	};

	template <class Type>
	constexpr bool operator == (const Optional<Type>& x, const Optional<Type>& y)
	{
		return static_cast<bool>(x) != static_cast<bool>(y) ? false : static_cast<bool>(x) == false ? true : *x == *y;
	}

	template <class Type>
	constexpr bool operator != (const Optional<Type>& x, const Optional<Type>& y)
	{
		return !(x == y);
	}

	template <class Type>
	constexpr bool operator < (const Optional<Type>& x, const Optional<Type>& y)
	{
		return (!y) ? false : (!x) ? true : *x < *y;
	}

	template <class Type>
	constexpr bool operator > (const Optional<Type>& x, const Optional<Type>& y)
	{
		return (y < x);
	}

	template <class Type>
	constexpr bool operator <= (const Optional<Type>& x, const Optional<Type>& y)
	{
		return !(y < x);
	}

	template <class Type>
	constexpr bool operator >= (const Optional<Type>& x, const Optional<Type>& y)
	{
		return !(x < y);
	}

	template <class Type>
	constexpr bool operator == (const Optional<Type>& x, None_t) noexcept
	{
		return (!x);
	}

	template <class Type>
	constexpr bool operator == (None_t, const Optional<Type>& x) noexcept
	{
		return (!x);
	}

	template <class Type>
	constexpr bool operator != (const Optional<Type>& x, None_t) noexcept
	{
		return static_cast<bool>(x);
	}

	template <class Type>
	constexpr bool operator != (None_t, const Optional<Type>& x) noexcept
	{
		return static_cast<bool>(x);
	}

	template <class Type>
	constexpr bool operator < (const Optional<Type>&, None_t) noexcept
	{
		return false;
	}

	template <class Type>
	constexpr bool operator < (None_t, const Optional<Type>& x) noexcept
	{
		return static_cast<bool>(x);
	}

	template <class Type>
	constexpr bool operator <= (const Optional<Type>& x, None_t) noexcept
	{
		return (!x);
	}

	template <class Type>
	constexpr bool operator <= (None_t, const Optional<Type>&) noexcept
	{
		return true;
	}

	template <class Type>
	constexpr bool operator > (const Optional<Type>& x, None_t) noexcept
	{
		return static_cast<bool>(x);
	}

	template <class Type>
	constexpr bool operator > (None_t, const Optional<Type>&) noexcept
	{
		return false;
	}

	template <class Type>
	constexpr bool operator >= (const Optional<Type>&, None_t) noexcept
	{
		return true;
	}

	template <class Type>
	constexpr bool operator >= (None_t, const Optional<Type>& x) noexcept
	{
		return (!x);
	}

	template <class Type>
	constexpr bool operator == (const Optional<Type>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x == v : false;
	}

	template <class Type>
	constexpr bool operator == (const Type& v, const Optional<Type>& x)
	{
		return static_cast<bool>(x) ? v == *x : false;
	}

	template <class Type>
	constexpr bool operator != (const Optional<Type>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x != v : true;
	}

	template <class Type>
	constexpr bool operator != (const Type& v, const Optional<Type>& x)
	{
		return static_cast<bool>(x) ? v != *x : true;
	}

	template <class Type>
	constexpr bool operator < (const Optional<Type>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x < v : true;
	}

	template <class Type>
	constexpr bool operator > (const Type& v, const Optional<Type>& x)
	{
		return static_cast<bool>(x) ? v > *x : true;
	}

	template <class Type>
	constexpr bool operator > (const Optional<Type>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x > v : false;
	}

	template <class Type>
	constexpr bool operator < (const Type& v, const Optional<Type>& x)
	{
		return static_cast<bool>(x) ? v < *x : false;
	}

	template <class Type>
	constexpr bool operator >= (const Optional<Type>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x >= v : false;
	}

	template <class Type>
	constexpr bool operator <= (const Type& v, const Optional<Type>& x)
	{
		return static_cast<bool>(x) ? v <= *x : false;
	}

	template <class Type>
	constexpr bool operator <= (const Optional<Type>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x <= v : true;
	}

	template <class Type>
	constexpr bool operator >= (const Type& v, const Optional<Type>& x)
	{
		return static_cast<bool>(x) ? v >= *x : true;
	}

	template <class Type>
	constexpr bool operator == (const Optional<Type&>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x == v : false;
	}

	template <class Type>
	constexpr bool operator == (const Type& v, const Optional<Type&>& x)
	{
		return static_cast<bool>(x) ? v == *x : false;
	}

	template <class Type>
	constexpr bool operator != (const Optional<Type&>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x != v : true;
	}

	template <class Type>
	constexpr bool operator !=(const Type& v, const Optional<Type&>& x)
	{
		return static_cast<bool>(x) ? v != *x : true;
	}

	template <class Type>
	constexpr bool operator < (const Optional<Type&>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x < v : true;
	}

	template <class Type>
	constexpr bool operator > (const Type& v, const Optional<Type&>& x)
	{
		return static_cast<bool>(x) ? v > *x : true;
	}

	template <class Type>
	constexpr bool operator > (const Optional<Type&>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x > v : false;
	}

	template <class Type>
	constexpr bool operator < (const Type& v, const Optional<Type&>& x)
	{
		return static_cast<bool>(x) ? v < *x : false;
	}

	template <class Type>
	constexpr bool operator >= (const Optional<Type&>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x >= v : false;
	}

	template <class Type>
	constexpr bool operator <=(const Type& v, const Optional<Type&>& x)
	{
		return static_cast<bool>(x) ? v <= *x : false;
	}

	template <class Type>
	constexpr bool operator <= (const Optional<Type&>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x <= v : true;
	}

	template <class Type>
	constexpr bool operator >= (const Type& v, const Optional<Type&>& x)
	{
		return static_cast<bool>(x) ? v >= *x : true;
	}

	template <class Type>
	constexpr bool operator == (const Optional<const Type&>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x == v : false;
	}

	template <class Type>
	constexpr bool operator == (const Type& v, const Optional<const Type&>& x)
	{
		return static_cast<bool>(x) ? v == *x : false;
	}

	template <class Type>
	constexpr bool operator != (const Optional<const Type&>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x != v : true;
	}

	template <class Type>
	constexpr bool operator != (const Type& v, const Optional<const Type&>& x)
	{
		return static_cast<bool>(x) ? v != *x : true;
	}

	template <class Type>
	constexpr bool operator < (const Optional<const Type&>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x < v : true;
	}

	template <class Type>
	constexpr bool operator > (const Type& v, const Optional<const Type&>& x)
	{
		return static_cast<bool>(x) ? v > *x : true;
	}

	template <class Type>
	constexpr bool operator > (const Optional<const Type&>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x > v : false;
	}

	template <class Type>
	constexpr bool operator < (const Type& v, const Optional<const Type&>& x)
	{
		return static_cast<bool>(x) ? v < *x : false;
	}

	template <class Type>
	constexpr bool operator >= (const Optional<const Type&>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x >= v : false;
	}

	template <class Type>
	constexpr bool operator <= (const Type& v, const Optional<const Type&>& x)
	{
		return static_cast<bool>(x) ? v <= *x : false;
	}

	template <class Type>
	constexpr bool operator <= (const Optional<const Type&>& x, const Type& v)
	{
		return static_cast<bool>(x) ? *x <= v : true;
	}

	template <class Type>
	constexpr bool operator >= (const Type& v, const Optional<const Type&>& x)
	{
		return static_cast<bool>(x) ? v >= *x : true;
	}

	template <class Type>
	constexpr Optional<std::decay_t<Type>> make_Optional(Type&& v)
	{
		return Optional<std::decay_t<Type>>(constexpr_forward<Type>(v));
	}

	template <class U>
	constexpr Optional<U&> make_Optional(std::reference_wrapper<U> v)
	{
		return Optional<U&>(v.get());
	}

	template <class Type>
	struct IsOptional : std::false_type {};

	template <class Type>
	struct IsOptional<Optional<Type>> : std::true_type {};

	template <>
	struct IsOptional<None_t> : std::true_type {};
}

namespace std
{
	template <class Type>
	void swap(s3d::Optional<Type>& a, s3d::Optional<Type>& b) noexcept(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

	template <class Type>
	struct hash<s3d::Optional<Type>>
	{
		using result_type = typename hash<Type>::result_type;
		using argument_type = s3d::Optional<Type>;

		constexpr result_type operator()(argument_type const& arg) const {
			return arg ? std::hash<Type>{}(*arg) : result_type{};
		}
	};

	template <class Type>
	struct hash<s3d::Optional<Type&>>
	{
		using result_type = typename hash<Type>::result_type;
		using argument_type = s3d::Optional<Type&>;

		constexpr result_type operator()(argument_type const& arg) const
		{
			return arg ? std::hash<Type>{}(*arg) : result_type{};
		}
	};
}

# undef OPTIONAL_REQUIRES

//
//////////////////////////////////////////////////////////////////////////////
