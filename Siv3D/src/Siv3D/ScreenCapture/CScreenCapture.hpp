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
# include <Siv3D/Common.hpp>
# include <Siv3D/Optional.hpp>
# include <Siv3D/ScreenCapture.hpp>
# include <Siv3D/Keyboard.hpp>
# include "IScreenCapture.hpp"

namespace s3d
{
	class CScreenCapture final : public ISiv3DScreenCapture
	{
	public:

		CScreenCapture();

		~CScreenCapture() override;

		void init() override;

		void update() override;

		const FilePath& getScreenshotDirectory() const override;

		void setScreenshotDirectory(FilePathView path) override;

		void requestScreenCapture(FilePathView path) override;

		bool hasNewFrame() const override;

		const Image& receiveScreenCapture() const override;

		void setScreenshotShortcutKeys(const Array<InputGroup>& screenshotShortcutKeys) override;

	private:

		FilePath m_screenshotDirectory;

		Array<FilePath> m_requestedPaths;

		Array<InputGroup> m_screenshotShortcutKeys = { KeyPrintScreen, KeyF12 };

		bool m_hasNewFrame = false;
	};
}
