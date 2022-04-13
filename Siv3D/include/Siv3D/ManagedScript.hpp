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
# include <memory>
# include "Common.hpp"
# include "Array.hpp"
# include "String.hpp"

namespace s3d
{
	/// @brief 自動管理されるスクリプト
	/// @remark スクリプトファイルの変更を検知し、自動でリロードするスクリプトクラスです
	/// @remark スクリプトコード内の `void Main()` がエントリーポイントです
	class ManagedScript
	{
	public:

		SIV3D_NODISCARD_CXX20
		ManagedScript();

		SIV3D_NODISCARD_CXX20
		explicit ManagedScript(FilePathView path);

		~ManagedScript();

		[[nodiscard]]
		bool isEmpty() const;

		[[nodiscard]]
		explicit operator bool() const;

		/// @brief スクリプトコードのコンパイルに成功したかを返します。
		/// @return コンパイルに成功した場合 true, それ以外の場合は false
		[[nodiscard]]
		bool compiled() const;

		/// @brief スクリプトのリロードを発生させるイベントを設定します。
		/// @param trigger スクリプトのリロードを発生させるイベント。この関数が true を返すとスクリプトをリロードする
		void setTriggerToReload(const std::function<bool()>& trigger);

		/// @brief インクルードされているファイル一覧を返します。
		/// @return  インクルードされているファイル一覧
		const Array<FilePath>& getIncludedFiles() const noexcept;

		/// @brief スクリプトコードを実行します。
		void run() const;

	private:

		class ManagedScriptDetail;

		std::shared_ptr<ManagedScriptDetail> pImpl;
	};
}
