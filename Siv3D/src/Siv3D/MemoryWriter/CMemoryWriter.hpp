﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Array.hpp>
# include <Siv3D/MemoryWriter.hpp>

namespace s3d
{
	class MemoryWriter::CMemoryWriter
	{
	private:

		Array<Byte> m_data;

		int64 m_pos = 0;

	public:

		CMemoryWriter();

		~CMemoryWriter();

		void release();

		void clear();

		int64 size() const;

		int64 write(const void* src, size_t size);

		const Byte* data();

		int64 setPos(int64 pos);

		int64 getPos() const;
	};
}
