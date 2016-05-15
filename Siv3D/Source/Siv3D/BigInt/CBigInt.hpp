//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2016 Ryo Suzuki
//	Copyright (c) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <boost/multiprecision/cpp_int.hpp>
# include <Siv3D/BigInt.hpp>

namespace s3d
{
	struct BigInt::CBigInt
	{
		using value_type = boost::multiprecision::cpp_int;

		value_type data;
	};
}
