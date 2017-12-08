//-----------------------------------------------
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
# include <Siv3D/Fwd.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/Graphics.hpp>

namespace s3d
{
	class ISiv3DGraphics
	{
	public:

		static ISiv3DGraphics* Create();

		virtual ~ISiv3DGraphics() = default;

		virtual bool init() = 0;

		virtual Array<DisplayOutput> enumOutputs() = 0;

		virtual void setClearColor(const ColorF& color) = 0;

		virtual bool setFullScreen(bool fullScreen, const Size& size, size_t displayIndex, double refreshRateHz) = 0;

		virtual bool present() = 0;

		virtual void clear() = 0;

		virtual void beginResize() = 0;

		virtual bool endResize(const Size& size) = 0;

		virtual void setTargetFrameRateHz(const Optional<double>& targetFrameRateHz) = 0;

		virtual Optional<double> getTargetFrameRateHz() const  = 0;

		virtual double getDisplayRefreshRateHz() const = 0;

		virtual bool flush(bool clearGraphics) = 0;

		//virtual const Size& getCurrentRenderTargetSize() const = 0;

		virtual const RenderTexture& getBackBuffer2D() const = 0;
		//
		//virtual void requestScreenCapture() = 0;
		//
		//virtual const Image& getScreenCapture() const = 0;
	};
}
