//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "Array.hpp"
# include "String.hpp"

//
// このヘッダは、コマンドライン引数を取得するための API を提供します。主な関数は以下の通りです。
//
//	System::GetArgc() - プログラムに渡されたコマンドライン引数の個数を返します。
//	System::GetArgv() - コマンドライン引数へのポインタの配列を返します。
//	System::GetCommandLineArgs() - コマンドライン引数を配列で返します。
//
// This header provides an API for obtaining command-line arguments. The main functions are as follows:
//
//	System::GetArgc() - Returns the number of command-line arguments passed to the program.
//	System::GetArgv() - Returns a pointer to an array of pointers to the command-line arguments.
//	System::GetCommandLineArgs() - Returns an array of the command-line arguments.
//

namespace s3d
{
	namespace System
	{
		/// @brief プログラムに渡されたコマンドライン引数の個数を返します。 | Returns the number of command-line arguments passed to the program.
		/// @return コマンドライン引数の個数 | The number of command-line arguments.
		[[nodiscard]]
		int32 GetArgc() noexcept;

		/// @brief コマンドライン引数へのポインタの配列を返します。 | Returns a pointer to an array of pointers to the command-line arguments.
		/// @return コマンドライン引数へのポインタの配列の先頭要素へのポインタ | A pointer to the first element in the array of pointers to the command-line arguments.
		/// @note 返される配列の最初の要素は、プログラム自体の名前を表します。 | The first element in the array returned represents the name of the program itself.
		[[nodiscard]]
		char** GetArgv() noexcept;

		/// @brief コマンドライン引数を配列で返します。 | Returns an array of the command-line arguments.
		/// @return コマンドライン引数を格納した配列 | An array containing the command-line arguments.
		[[nodiscard]]
		const Array<String>& GetCommandLineArgs() noexcept;
	}
}
