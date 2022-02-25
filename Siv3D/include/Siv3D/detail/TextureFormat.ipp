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
	inline constexpr TextureFormat::TextureFormat(TexturePixelFormat value) noexcept
		: m_value{ value } {}

	inline constexpr TexturePixelFormat TextureFormat::value() const noexcept
	{
		return m_value;
	}
}
