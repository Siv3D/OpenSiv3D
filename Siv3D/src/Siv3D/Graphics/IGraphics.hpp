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

# pragma once
# include <Siv3D/Fwd.hpp>

namespace s3d
{
	class ISiv3DGraphics
	{
	public:

		static ISiv3DGraphics* Create();

		virtual ~ISiv3DGraphics() = default;

		virtual void init() = 0;

		virtual bool present() = 0;

		virtual void clear() = 0;

		virtual void flush() = 0;

		virtual void setSceneTextureFilter(TextureFilter textureFilter) = 0;

		virtual TextureFilter getSceneTextureFilter() const = 0;

		virtual void setBackgroundColor(const ColorF& color) = 0;

		virtual void setLetterboxColor(const ColorF& color) = 0;

		virtual void setTargetFrameRateHz(const Optional<double>& targetFrameRateHz) = 0;

		virtual Optional<double> getTargetFrameRateHz() const = 0;

		virtual double getDPIScaling() const = 0;

		virtual double getDisplayRefreshRateHz() const = 0;

		virtual void skipClearScreen() = 0;

		virtual const Size& getBackBufferSize() const = 0;

		virtual const Size& getSceneSize() const = 0;

		virtual void setSceneSize(const Size& sceneSize) = 0;

		virtual void resizeBuffers(const Size& backBufferSize, const Size& sceneSize) = 0;

		virtual Optional<Rect> getFullscreenRect() = 0;

		virtual void requestScreenCapture() = 0;

		virtual const Image& getScreenCapture() const = 0;
	};
}
