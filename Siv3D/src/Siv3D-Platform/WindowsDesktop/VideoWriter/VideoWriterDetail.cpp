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

# include <Siv3D/String.hpp>
# include <Siv3D/Math.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3DEngine.hpp>
# include "VideoWriterDetail.hpp"

namespace s3d
{
	VideoWriter::VideoWriterDetail::VideoWriterDetail()
	{
		if (auto mf = dynamic_cast<CCodec*>(Siv3DEngine::Get<ISiv3DCodec>()))
		{
			mf->getFunctions(m_functions);
		}
	}

	VideoWriter::VideoWriterDetail::~VideoWriterDetail()
	{
		close();
	}

	bool VideoWriter::VideoWriterDetail::open(const FilePath& path, const Size& frameSize, const double fps)
	{
		if (isOpen())
		{
			close();
		}

		if (!(fps > 0.0))
		{
			return false;
		}

		m_frameSize = frameSize;

		m_fps = (Math::Fraction(fps) == 0.0) ? std::make_pair(1, static_cast<int32>(fps))
			: std::make_pair(1000, static_cast<int32>(fps * 1000));

		m_bitRate = static_cast<uint32>(static_cast<double>(m_fps.second) / m_fps.first)*m_frameSize.x*m_frameSize.y; // 1-bit per pixel

		m_encodingFormat = MFVideoFormat_H264;

		m_inputFormat = MFVideoFormat_RGB32;

		HRESULT hr = m_functions.p_MFStartup(MF_VERSION, 0);

		if (SUCCEEDED(hr))
		{
			FileSystem::CreateParentDirectories(path);

			hr = initializeSinkWriter(path);

			if (SUCCEEDED(hr))
			{
				m_initiated = true;

				m_rtStart = 0;

				m_functions.p_MFFrameRateToAverageTimePerFrame(m_fps.second, m_fps.first, &m_rtDuration);
			}
			else
			{
				//LOG_FAIL(L"failed: initializeSinkWriter()");
			}
		}
		else
		{
			//LOG_FAIL(L"failed: MFStartup()");
		}

		return SUCCEEDED(hr);
	}

	void VideoWriter::VideoWriterDetail::close()
	{
		if (!m_initiated)
		{
			return;
		}

		m_initiated = false;

		m_sinkWriter->Finalize();

		m_functions.p_MFShutdown();

		m_frameSize.set(0, 0);

		m_fps = { 0,0 };
	}

	bool VideoWriter::VideoWriterDetail::isOpen() const
	{
		return m_initiated;
	}

	bool VideoWriter::VideoWriterDetail::write(const Image& image)
	{
		if (!m_initiated)
		{
			return false;
		}

		if (!image || image.size() != m_frameSize)
		{
			return false;
		}

		if (!writeFrame(image, m_rtStart, m_rtDuration))
		{
			return false;
		}

		m_rtStart += m_rtDuration;

		return true;
	}

	Size VideoWriter::VideoWriterDetail::size() const
	{
		return m_frameSize;
	}

	HRESULT VideoWriter::VideoWriterDetail::initializeSinkWriter(const FilePath& path)
	{
		ComPtr<IMFAttributes> spAttr;
		ComPtr<IMFMediaType> mediaTypeOut;
		ComPtr<IMFMediaType> mediaTypeIn;
		ComPtr<IMFByteStream> spByteStream;
		m_functions.p_MFCreateAttributes(&spAttr, 10);
		spAttr->SetUINT32(MF_READWRITE_ENABLE_HARDWARE_TRANSFORMS, true);
		HRESULT hr = m_functions.p_MFCreateSinkWriterFromURL(path.toWstr().c_str(), NULL, spAttr.Get(), &m_sinkWriter);
		// Set the output media type.
		if (SUCCEEDED(hr))
		{
			hr = m_functions.p_MFCreateMediaType(&mediaTypeOut);
		}
		if (SUCCEEDED(hr))
		{
			hr = mediaTypeOut->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);
		}
		if (SUCCEEDED(hr))
		{
			hr = mediaTypeOut->SetGUID(MF_MT_SUBTYPE, m_encodingFormat);
		}
		if (SUCCEEDED(hr))
		{
			hr = mediaTypeOut->SetUINT32(MF_MT_AVG_BITRATE, m_bitRate);
		}
		if (SUCCEEDED(hr))
		{
			hr = mediaTypeOut->SetUINT32(MF_MT_INTERLACE_MODE, MFVideoInterlace_Progressive);
		}
		if (SUCCEEDED(hr))
		{
			hr = MFSetAttributeSize(mediaTypeOut.Get(), MF_MT_FRAME_SIZE, m_frameSize.x, m_frameSize.y);
		}
		if (SUCCEEDED(hr))
		{
			hr = MFSetAttributeRatio(mediaTypeOut.Get(), MF_MT_FRAME_RATE, m_fps.second, m_fps.first);
		}
		if (SUCCEEDED(hr))
		{
			hr = MFSetAttributeRatio(mediaTypeOut.Get(), MF_MT_PIXEL_ASPECT_RATIO, 1, 1);
		}
		if (SUCCEEDED(hr))
		{
			hr = m_sinkWriter->AddStream(mediaTypeOut.Get(), &m_streamIndex);
		}

		// Set the input media type.
		if (SUCCEEDED(hr))
		{
			hr = m_functions.p_MFCreateMediaType(&mediaTypeIn);
		}
		if (SUCCEEDED(hr))
		{
			hr = mediaTypeIn->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);
		}
		if (SUCCEEDED(hr))
		{
			hr = mediaTypeIn->SetGUID(MF_MT_SUBTYPE, m_inputFormat);
		}
		if (SUCCEEDED(hr))
		{
			hr = mediaTypeIn->SetUINT32(MF_MT_INTERLACE_MODE, MFVideoInterlace_Progressive);
		}
		if (SUCCEEDED(hr))
		{
			hr = MFSetAttributeSize(mediaTypeIn.Get(), MF_MT_FRAME_SIZE, m_frameSize.x, m_frameSize.y);
		}
		if (SUCCEEDED(hr))
		{
			hr = MFSetAttributeRatio(mediaTypeIn.Get(), MF_MT_FRAME_RATE, m_fps.second, m_fps.first);
		}
		if (SUCCEEDED(hr))
		{
			hr = MFSetAttributeRatio(mediaTypeIn.Get(), MF_MT_PIXEL_ASPECT_RATIO, 1, 1);
		}
		if (SUCCEEDED(hr))
		{
			hr = m_sinkWriter->SetInputMediaType(m_streamIndex, mediaTypeIn.Get(), NULL);
		}
		// Tell the sink writer to start accepting data.
		if (SUCCEEDED(hr))
		{
			hr = m_sinkWriter->BeginWriting();
		}
		return hr;
	}

	bool VideoWriter::VideoWriterDetail::writeFrame(const Image& image, const LONGLONG start, const LONGLONG duration)
	{
		const LONG cbWidth = 4 * m_frameSize.x;
		const DWORD cbBuffer = cbWidth * m_frameSize.y;

		if (!m_buffer)
		{
			if (FAILED(m_functions.p_MFCreateMemoryBuffer(cbBuffer, &m_buffer)))
			{
				return false;
			}
		}

		BYTE *pData = nullptr;

		HRESULT hr = m_buffer->Lock(&pData, nullptr, nullptr);

		if (SUCCEEDED(hr))
		{
			uint32* pDst = (uint32*)pData;
			const int32 height = image.height();
			const int32 width = image.width();
			const size_t stride = image.stride();

			const uint8* pLine = (const uint8*)image[height - 1];

			for (int32 y = 0; y < height; ++y)
			{
				const uint8* p = pLine;

				for (int x = 0; x < width; ++x)
				{
					const uint8 b = p[2];
					const uint8 g = p[1];
					const uint8 r = p[0];
					*pDst = (r << 16) + (g << 8) + b;

					p += 4;
					++pDst;
				}

				pLine -= stride;
			}

			m_buffer->Unlock();
		}

		// Set the data length of the buffer.
		if (SUCCEEDED(hr))
		{
			hr = m_buffer->SetCurrentLength(cbBuffer);
		}

		ComPtr<IMFSample> sample;

		// Create a media sample and add the buffer to the sample.
		if (SUCCEEDED(hr))
		{
			hr = m_functions.p_MFCreateSample(&sample);
		}

		if (SUCCEEDED(hr))
		{
			hr = sample->AddBuffer(m_buffer.Get());
		}

		// Set the time stamp and the duration.
		if (SUCCEEDED(hr))
		{
			hr = sample->SetSampleTime(start);
		}

		if (SUCCEEDED(hr))
		{
			hr = sample->SetSampleDuration(duration);
		}

		// Send the sample to the Sink Writer.
		if (SUCCEEDED(hr))
		{
			hr = m_sinkWriter->WriteSample(m_streamIndex, sample.Get());
		}

		return SUCCEEDED(hr);
	}
}
