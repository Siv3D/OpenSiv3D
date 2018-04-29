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
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include <Siv3D/VideoWriter.hpp>
# include <Siv3D/PointVector.hpp>
# include "../Codec/MF/CCodec_MF.hpp"

namespace s3d
{
	class VideoWriter::CVideoWriter
	{
	private:

		MF_Functions m_functions;

		std::pair<int32, int32> m_fps;

		Size m_frameSize = Size(0, 0);

		UINT32 m_bitRate;

		GUID m_encodingFormat;

		GUID m_inputFormat;

		DWORD m_streamIndex;

		ComPtr<IMFSinkWriter> m_sinkWriter;

		ComPtr<IMFMediaBuffer> m_buffer;

		bool m_initiated = false;

		LONGLONG m_rtStart;

		UINT64 m_rtDuration;

		HRESULT initializeSinkWriter(const FilePath& path);

		bool writeFrame(const Image& image, LONGLONG start, LONGLONG duration);

	public:

		CVideoWriter();

		~CVideoWriter();

		bool open(const FilePath& path, const Size& frameSize, double fps);

		void close();

		bool isOpened() const;

		bool write(const Image& image);

		Size size() const;
	};
}

# endif
