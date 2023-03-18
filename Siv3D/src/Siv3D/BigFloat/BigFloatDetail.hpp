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
# include <Siv3D/BigFloat.hpp>

# ifdef __clang__
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wunused-parameter"
# endif
# include <boost/multiprecision/cpp_dec_float.hpp>
# ifdef __clang__
#	pragma clang diagnostic pop
# endif

namespace s3d
{
	struct BigFloat::BigFloatDetail
	{
		using value_type = boost::multiprecision::cpp_dec_float_100;

		value_type data;
	};
}
