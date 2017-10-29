//----------------------------------------------------------------------------------------
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
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

# ifndef SIV3D_INCLUDED

	# define SIV3D_INCLUDED

# endif

//////////////////////////////////////////////////
//
//	Utilities
//
//////////////////////////////////////////////////

	// Platform
	# include "Siv3D/Platform.hpp"

	// Library version
	# include "Siv3D/Version.hpp"

	// Types
	# include "Siv3D/Types.hpp"

	// Forward declarations
	# include "Siv3D/Fwd.hpp"

	// Place holder
	# include "Siv3D/PlaceHolder.hpp"

	// Non-copyable mixin
	# include "Siv3D/Uncopyable.hpp"

	// Named parameter
	# include "Siv3D/NamedParameter.hpp"

	// Meta
	# include "Siv3D/Meta.hpp"

	// Utilities
	# include "Siv3D/Utility.hpp"

	// Functor
	# include "Siv3D/Functor.hpp"

	// Byte
	# include "Siv3D/Byte.hpp"

	// ByteArray view
	# include "Siv3D/ByteArrayView.hpp"

	// Thread
	# include "Siv3D/Threading.hpp"

	// Task
	# include "Siv3D/ConcurrentTask.hpp"

	// Memory alignment
	# include "Siv3D/AlignedMemory.hpp"	

	// Aligned allocator
	# include "Siv3D/AlignedAllocator.hpp"

	// Array
	# include "Siv3D/Array.hpp"

	// Hash table
	# include "Siv3D/HashTable.hpp"

	// Hash set
	# include "Siv3D/HashSet.hpp"

	// Indexed iterator
	# include "Siv3D/Indexed.hpp"

	//// 範囲
	//# include "Siv3D/Step.hpp"

	//// 二次元の範囲
	//# include "Siv3D/Step2D.hpp"

	//// 無限リスト
	//# include "Siv3D/InfiniteList.hpp"

	//// 二次元配列
	//# include "Siv3D/Grid.hpp"

	// Optional
	# include "Siv3D/Optional.hpp"

	//// unspecified
	//# include "Siv3D/Unspecified.hpp"

	//// 型特性
	//# include "Siv3D/TypeTraits.hpp"

	//// イテレータによる範囲の表現
	//# include "Siv3D/IteratorRange.hpp"

	//// map 省略表記
	//# include "Siv3D/Evaluater.hpp"

//////////////////////////////////////////////////
//
//	String and Value
//
//////////////////////////////////////////////////

	// Character
	# include "Siv3D/Char.hpp"

	// String view
	# include "Siv3D/StringView.hpp"

	// String
	# include "Siv3D/String.hpp"

	// Unicode
	# include "Siv3D/Unicode.hpp"

	// Formatting literal
	# include "Siv3D/FormatLiteral.hpp"

	// Format
	# include "Siv3D/Format.hpp"

	// Number
	# include "Siv3D/Number.hpp"


//////////////////////////////////////////////////
//
//	Random number
//
//////////////////////////////////////////////////

	// Distribution
	# include "Siv3D/Distribution.hpp"
	
	// Hardware RNG
	# include "Siv3D/HardwareRNG.hpp"
	
	// Xorshift RNG
	# include "Siv3D/Xorshift.hpp"
	
	// SFMT RNG
	# include "Siv3D/SFMT.hpp"
	
	// Mersenne Twister RNG
	# include "Siv3D/MersenneTwister.hpp"
	
	// Default RNG
	# include "Siv3D/DefaultRNG.hpp"


//////////////////////////////////////////////////
//
//	Namespace
//
//	* define NO_S3D_USING to avoid using namespace *
//
//////////////////////////////////////////////////

# ifndef NO_S3D_USING

	using namespace s3d;
	using namespace s3d::literals;

# endif
