//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2025 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	inline bool QRContent::isValid() const noexcept
	{
		return (mode != QRMode::Invalid);
	}

	inline QRContent::operator bool() const noexcept
	{
		return isValid();
	}

	inline void QRContent::clear()
	{
		*this = QRContent{};
	}
}
