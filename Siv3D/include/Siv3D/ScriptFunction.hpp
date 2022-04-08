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
# include "PredefinedYesNo.hpp"
# include "Optional.hpp"

namespace s3d
{
	template <class Type>
	struct ScriptFunction;

	/// @brief スクリプト関数
	/// @tparam Ret 戻り値の型
	/// @tparam ...Args 引数の型
	template <class Ret, class... Args>
	struct ScriptFunction<Ret(Args...)>
	{
	public:

		using return_type = Ret;

		static constexpr size_t nargs = (sizeof...(Args));

		template <size_t i>
		struct Arg
		{
			using type = typename std::tuple_element_t<i, std::tuple<Args...>>;
		};

		SIV3D_NODISCARD_CXX20
		ScriptFunction() = default;

		SIV3D_NODISCARD_CXX20
		ScriptFunction(const std::shared_ptr<ScriptModule>& module, AngelScript::asIScriptFunction* function);

		/// @brief スクリプト関数が空でないかを返します。
		/// @return スクリプト関数が空でない場合 true, それ以外の場合は false
		[[nodiscard]]
		explicit operator bool() const noexcept;

		/// @brief スクリプト関数を呼び出します。
		/// @param ...args 引数
		/// @return スクリプト関数の戻り値
		Ret operator ()(Args... args) const;

		/// @brief スクリプト関数を呼び出します。
		/// @param ...args 引数
		/// @param exception スクリプト例外が発生した場合の例外の内容の格納先への参照
		/// @return スクリプト関数の戻り値
		Ret tryCall(Args... args, String& exception) const;

		/// @brief 関数宣言を返します。
		/// @param includeParamNames パラメータ名を含む場合 `IncludeParamNames::Yes`, それ以外の場合は `IncludeParamNames::No`
		/// @return 関数宣言。失敗した場合は空の文字列
		[[nodiscard]]
		String getDeclaration(IncludeParamNames includeParamNames = IncludeParamNames::Yes) const;

	private:

		std::shared_ptr<ScriptModule> m_module;

		AngelScript::asIScriptFunction* m_function = nullptr;

		template <class Type, class ... Args2>
		void setArgs(uint32 argIndex, Type&& value, Args2&&... args) const;

		template <class Type>
		void setArgs(uint32 argIndex, Type&& value) const;

		void setArgs(uint32) const;

		template <class Type>
		void setArg(uint32 argIndex, Type&& value) const;

		[[nodiscard]]
		bool execute() const;

		[[nodiscard]]
		Optional<String> tryExecute() const;

		template <class Type>
		[[nodiscard]]
		Type getReturn() const;
	};
}

# include "detail/ScriptFunction.ipp"
