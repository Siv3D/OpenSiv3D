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

# pragma once
# include "Fwd.hpp"
# include "Format.hpp"

namespace s3d
{
	namespace detail
	{
		struct Log_impl
		{
			void operator()(const String& text) const;

			template <class... Args>
			void operator()(const Args&... args) const
			{
				return operator()(Format(args...));
			}
		};
	}

	constexpr auto Log = detail::Log_impl();
}
