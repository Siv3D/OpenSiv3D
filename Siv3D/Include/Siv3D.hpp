//----------------------------------------------------------------------------------------
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files(the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions :
//	
//	The above copyright notice and this permission notice shall be included in
//	all copies or substantial portions of the Software.
//	
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//	THE SOFTWARE.
//
//----------------------------------------------------------------------------------------

# pragma once
# pragma comment (linker, "/entry:\"wWinMainCRTStartup\"")

# ifdef _WIN64
	# ifdef _DEBUG
		# pragma comment (lib, "x64/Siv3D_d")
	# else
		# pragma comment (lib, "x64/Siv3D")
	# endif
# else
	# ifdef _DEBUG
		# pragma comment (lib, "x86/Siv3D_d")
	# else
		# pragma comment (lib, "x86/Siv3D")
	# endif
# endif


//
// ユーティリティ
//
	// 型
	# include "Siv3D/Types.hpp"
	// メモリ
	# include "Siv3D/Memory.hpp"

