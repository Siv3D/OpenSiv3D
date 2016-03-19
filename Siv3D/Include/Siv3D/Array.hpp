//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <vector>

namespace s3d
{
	template <class Type, class Allocator = std::allocator<Type>>
	class Array : protected std::vector<Type, Allocator>
	{
	private:

	public:

		using std::vector<Type, Allocator>::vector;
	};
}
