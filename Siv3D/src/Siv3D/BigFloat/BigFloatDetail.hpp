//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <boost/multiprecision/cpp_dec_float.hpp>
# include <Siv3D/BigFloat.hpp>

namespace s3d
{
	struct BigFloat::BigFloatDetail
	{
		using value_type = boost::multiprecision::cpp_dec_float_100;

		value_type data;
	};
}
