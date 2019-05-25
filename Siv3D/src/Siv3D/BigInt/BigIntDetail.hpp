//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <boost/multiprecision/cpp_int.hpp>
# include <Siv3D/BigInt.hpp>

namespace s3d
{
	struct BigInt::BigIntDetail
	{
		using value_type = boost::multiprecision::cpp_int;

		value_type data;
	};
}
