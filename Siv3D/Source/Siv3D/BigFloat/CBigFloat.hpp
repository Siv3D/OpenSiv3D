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

# include <boost/multiprecision/cpp_dec_float.hpp>
# include <Siv3D/BigFloat.hpp>

namespace s3d
{
	struct BigFloat::CBigFloat
	{
		using value_type = boost::multiprecision::cpp_dec_float_100;

		value_type data;
	};
}
