//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "AssetHandle.hpp"
# include "Array.hpp"
# include "String.hpp"
# include "ScriptModule.hpp"
# include "ScriptCompileOption.hpp"
# include "ScriptFunction.hpp"

namespace s3d
{
	/// @brief スクリプト
	class Script : public AssetHandle<Script>
	{
	public:

		SIV3D_NODISCARD_CXX20
		Script();

		SIV3D_NODISCARD_CXX20
		explicit Script(FilePathView path, ScriptCompileOption compileOption = ScriptCompileOption::Default);

		SIV3D_NODISCARD_CXX20
		explicit Script(Arg::code_<StringView> code, ScriptCompileOption compileOption = ScriptCompileOption::Default);

		virtual ~Script();

		[[nodiscard]]
		Array<String> getFunctionDeclarations(IncludeParamNames includeParamNames = IncludeParamNames::Yes) const;

		template <class Fty>
		[[nodiscard]]
		ScriptFunction<Fty> getFunction(StringView decl) const;

		[[nodiscard]]
		bool compiled() const;

		bool reload(ScriptCompileOption compileOption = ScriptCompileOption::Default);

		void setSystemUpdateCallback(const std::function<bool(void)>& callback);

		const Array<String>& getMessages() const;

		[[nodiscard]]
		const FilePath& path() const;

		void swap(Script& other) noexcept;

		[[nodiscard]]
		static AngelScript::asIScriptEngine* GetEngine();

	protected:

		const std::shared_ptr<ScriptModule>& _getModule() const;

		AngelScript::asIScriptFunction* _getFunction(StringView decl) const;
	};
}

template <>
inline void std::swap(s3d::Script& a, s3d::Script& b) noexcept;

# include "detail/Script.ipp"
