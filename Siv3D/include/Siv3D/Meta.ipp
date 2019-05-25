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

# pragma once

namespace s3d
{
	namespace detail
	{
		template <class Default, class AlwaysVoid, template<class...> class Op, class... Args>
		struct Detector
		{
			using value_t = std::false_type;
			using type = Default;
		};

		template <class Default, template<class...> class Op, class... Args>
		struct Detector<Default, std::void_t<Op<Args...>>, Op, Args...>
		{
			using value_t = std::true_type;
			using type = Op<Args...>;
		};
	}
}
