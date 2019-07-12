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

# include <Siv3D/Step2D.hpp>

namespace s3d
{
	Array<Point> Step2D::asArray() const
	{
		Array<Point> new_array;

		if (isEmpty())
		{
			return new_array;
		}

		new_array.reserve(num_elements());

		for (auto it = m_start_iterator; it != m_end_iterator; ++it)
		{
			new_array.push_back(*it);
		}

		return new_array;
	}
}
