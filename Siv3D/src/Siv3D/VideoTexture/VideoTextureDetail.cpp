//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "VideoTextureDetail.hpp"
# include <Siv3D/Math.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	VideoTexture::VideoTextureDetail::VideoTextureDetail() {}

	VideoTexture::VideoTextureDetail::~VideoTextureDetail() {}

	bool VideoTexture::VideoTextureDetail::load(const FilePathView path, const Loop loop)
	{
		if (not m_videoReader.open(path))
		{
			return false;
		}

		m_loop = loop.getBool();
		m_videoReader.readFrame(m_frameImage);
		m_frameTextures[m_latestTextureIndex].fill(m_frameImage);

		return true;
	}

	void VideoTexture::VideoTextureDetail::advance(const double deltaTimeSec)
	{
		if (not m_videoReader)
		{
			return;
		}

		m_playTimeSec += deltaTimeSec;

		if (const double lengthSec = m_videoReader.getLengthSec();
			lengthSec <= m_playTimeSec)
		{
			if (m_loop)
			{
				m_playTimeSec = Math::Fmod(m_playTimeSec, lengthSec);
			}
			else
			{
				m_playTimeSec = lengthSec;
			}
		}

		update(true);
	}

	void VideoTexture::VideoTextureDetail::reset()
	{
		if (not m_videoReader)
		{
			return;
		}

		m_playTimeSec = 0.0;

		update(false);
	}

	bool VideoTexture::VideoTextureDetail::isLoop() const noexcept
	{
		return m_loop;
	}

	double VideoTexture::VideoTextureDetail::posSec() const noexcept
	{
		return m_playTimeSec;
	}

	void VideoTexture::VideoTextureDetail::setPosSec(const double posSec)
	{
		m_playTimeSec = Clamp(posSec, 0.0, m_videoReader.getLengthSec());
	}

	const Texture& VideoTexture::VideoTextureDetail::getTexture() const noexcept
	{
		return m_frameTextures[m_latestTextureIndex];
	}

	const VideoReader& VideoTexture::VideoTextureDetail::getVideoReader() const noexcept
	{
		return m_videoReader;
	}

	void VideoTexture::VideoTextureDetail::update(const bool skipIfBusy)
	{
		int32 targetFrameIndex = static_cast<int32>(m_playTimeSec / m_videoReader.getFrameDeltaSec());
		targetFrameIndex = Min(targetFrameIndex, static_cast<int32>(m_videoReader.getFrameCount()));

		const int32 currentFrameIndex = static_cast<int32>(m_videoReader.getCurrentFrameIndex());

		if (targetFrameIndex == currentFrameIndex)
		{
			if (m_hasDirty)
			{
				if (m_frameTextures[!m_latestTextureIndex].fillIfNotBusy(m_frameImage))
				{
					m_latestTextureIndex = !m_latestTextureIndex;
					m_hasDirty = false;
				}
			}

			return;
		}
		else if (targetFrameIndex != (currentFrameIndex + 1))
		{
			m_videoReader.setCurrentFrameIndex(targetFrameIndex);
		}

		m_videoReader.readFrame(m_frameImage);

		if (skipIfBusy)
		{
			if (m_frameTextures[!m_latestTextureIndex].fillIfNotBusy(m_frameImage))
			{
				m_latestTextureIndex = !m_latestTextureIndex;
			}
			else
			{
				m_hasDirty = true;
			}
		}
		else
		{
			m_frameTextures[!m_latestTextureIndex].fill(m_frameImage);
			m_latestTextureIndex = !m_latestTextureIndex;
		}
	}
}
