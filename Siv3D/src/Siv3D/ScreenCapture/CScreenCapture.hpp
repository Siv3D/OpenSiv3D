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

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Optional.hpp>
# include <Siv3D/ScreenCapture.hpp>
# include "IScreenCapture.hpp"

namespace s3d
{
	class CScreenCapture final : public ISiv3DScreenCapture
	{
	private:

		FilePath m_screenshotDirectory;

		Array<FilePath> m_requestedPaths;

		bool m_hasNewFrame = false;
		
	public:

		CScreenCapture();

		~CScreenCapture() override;

		void init() override;

		void update() override;

		const FilePath& getScreenshotDirectory() const override;

		void setScreenshotDirectory(FilePath&& path) override;

		void requestScreenCapture(FilePath&& path) override;

		bool hasNewFrame() const override;

		const Image& receiveScreenCapture() const override;
	};
}
