//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	template <class PShape, std::enable_if_t<std::is_base_of_v<P2Shape, PShape>>*>
	inline std::shared_ptr<PShape> P2Body::as(const size_t index) const
	{
		if (num_shapes() <= index)
		{
			throw std::out_of_range{ "P2Body::shape(): index out out range" };
		}

		return std::dynamic_pointer_cast<PShape>(getPtr(index));
	}
}
