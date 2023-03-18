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
# include <Siv3D/VideoTexture.hpp>
# include <Siv3D/VideoReader.hpp>
# include <Siv3D/DynamicTexture.hpp>

namespace s3d
{
	class VideoTexture::VideoTextureDetail
	{
	public:

		VideoTextureDetail();

		~VideoTextureDetail();

		bool load(FilePathView path, Loop loop, TextureDesc desc);

		void advance(double deltaTimeSec = Scene::DeltaTime());

		void reset();

		[[nodiscard]]
		bool isLoop() const noexcept;

		[[nodiscard]]
		double posSec() const noexcept;

		void setPosSec(double posSec);

		[[nodiscard]]
		const Texture& getTexture() const noexcept;

		[[nodiscard]]
		const VideoReader& getVideoReader() const noexcept;

	private:

		VideoReader m_videoReader;

		bool m_loop = false;

		bool m_isSRGB = false;

		double m_playTimeSec = 0.0;

		Image m_frameImage;

		size_t m_latestTextureIndex = 0;

		std::array<DynamicTexture, 2> m_frameTextures;

		bool m_hasDirty = false;

		void update(bool skipIfBusy);
	};
}
