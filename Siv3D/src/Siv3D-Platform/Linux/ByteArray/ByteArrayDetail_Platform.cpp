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

# include <ByteArray/ByteArrayDetail.hpp>

namespace s3d
{
	bool ByteArray::ByteArrayDetail::createFromFile(const FilePathView path)
	{
		release();

		if (!m_memoryMapping.open(path))
		{
			return false;
		}

		m_view = m_memoryMapping.data();
		m_size = m_memoryMapping.fileSize();

		return true;
	}
}
