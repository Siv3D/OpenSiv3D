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

namespace s3d
{
	inline ListBoxState::ListBoxState(const Array<String>& _items)
		: items{ _items } {}

	inline ListBoxState::ListBoxState(Array<String>&& _items) noexcept
		: items{ std::move(_items) } {}
}
