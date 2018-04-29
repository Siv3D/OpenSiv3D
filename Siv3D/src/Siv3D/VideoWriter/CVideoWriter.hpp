//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/VideoWriter.hpp>

namespace s3d
{
	class VideoWriter::CVideoWriter
	{
	private:

	public:

		CVideoWriter();

		~CVideoWriter();

		bool open(const FilePath& path);

		void close();

		bool isOpened() const;
	};
}
