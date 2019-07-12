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
# include <Siv3D/Fwd.hpp>

namespace s3d
{
	template <class VectorType>
	struct CursorState
	{
		using value_type = typename VectorType::value_type;

		VectorType previous = { 0,0 };

		VectorType current = { 0,0 };

		VectorType delta = { 0,0 };

		void update(value_type x, value_type y)
		{
			previous = current;
			current.set(x, y);
			delta = (current - previous);
		}
	};
}
