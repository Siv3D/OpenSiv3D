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
# include "AssetHandle.hpp"
# include "Array.hpp"
# include "String.hpp"
# include "ScriptModule.hpp"
# include "ScriptCompileOption.hpp"
# include "ScriptFunction.hpp"

namespace s3d
{
	/// @brief スクリプト (AngelScript)
	class Script : public AssetHandle<Script>
	{
	public:

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		Script();

		/// @brief スクリプトをファイルからロードしてコンパイルします。
		/// @param path スクリプトファイルのパス
		/// @param compileOption コンパイルオプション
		SIV3D_NODISCARD_CXX20
		explicit Script(FilePathView path, ScriptCompileOption compileOption = ScriptCompileOption::Default);

		/// @brief スクリプトをコードからコンパイルします。
		/// @param code コード
		/// @param compileOption コンパイルオプション
		SIV3D_NODISCARD_CXX20
		explicit Script(Arg::code_<StringView> code, ScriptCompileOption compileOption = ScriptCompileOption::Default);

		/// @brief デストラクタ
		virtual ~Script();

		/// @brief スクリプトに含まれる関数宣言の一覧を返します。
		/// @param includeParamNames パラメータ名を含む場合 `IncludeParamNames::Yes`, それ以外の場合は `IncludeParamNames::No`
		/// @return スクリプトに含まれる関数宣言の一覧
		[[nodiscard]]
		Array<String> getFunctionDeclarations(IncludeParamNames includeParamNames = IncludeParamNames::Yes) const;

		/// @brief スクリプト関数を取得します。
		/// @tparam Fty 関数の型
		/// @param decl 関数の名前または関数宣言
		/// @return スクリプト関数。取得に失敗した場合は空のスクリプト関数
		template <class Fty>
		[[nodiscard]]
		ScriptFunction<Fty> getFunction(StringView decl) const;

		/// @brief ロードしたスクリプトのコンパイルに成功しているかを返します。
		/// @return ロードしたスクリプトのコンパイルに成功している場合 true, それ以外の場合は false
		[[nodiscard]]
		bool compiled() const;

		/// @brief スクリプトをリロードして再コンパイルします。
		/// @param compileOption コンパイルオプション
		/// @return リロードと再コンパイルに成功した場合 true, それ以外の場合は false
		bool reload(ScriptCompileOption compileOption = ScriptCompileOption::Default);

		/// @brief スクリプト内での `System::Update()` で呼び出す関数を登録します。
		/// @param callback 登録する関数
		void setSystemUpdateCallback(const std::function<bool()>& callback);

		/// @brief インクルードされているファイル一覧を返します。
		/// @return  インクルードされているファイル一覧
		const Array<FilePath>& getIncludedFiles() const noexcept;

		/// @brief コンパイル時に出力されたメッセージ一覧を返します。
		/// @return コンパイル時に出力されたメッセージ一覧
		const Array<String>& getMessages() const;

		/// @brief スクリプトのファイルパスを返します。
		/// @return スクリプトのファイルパス。存在しない場合は空の文字列
		[[nodiscard]]
		const FilePath& path() const;

		/// @brief 別のスクリプトと中身を交換します。
		/// @param other 別のスクリプト
		void swap(Script& other) noexcept;

		/// @brief AngelScript の高度な機能にアクセスするためのエンジンポインタを返します（上級者向け）
		/// @return AngelScript の高度な機能にアクセスするためのエンジンポインタ
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
