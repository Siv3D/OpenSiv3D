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
# include <Siv3D/PointVector.hpp>
# include <Siv3D/ColorHSV.hpp>
# include <Siv3D/ResizeMode.hpp>
# include <Siv3D/FloatRect.hpp>
# include <Siv3D/TextureFilter.hpp>
# include <Siv3D/EngineOptions.hpp>

namespace s3d
{
	class SIV3D_NOVTABLE ISiv3DRenderer
	{
	public:

		static ISiv3DRenderer* Create();

		virtual ~ISiv3DRenderer() = default;

		virtual EngineOption::Renderer getRendererType() const noexcept = 0;

		virtual void init() = 0;

		virtual StringView getName() const = 0;

		virtual void clear() = 0;

		virtual void flush() = 0;

		virtual bool present() = 0;

		virtual void setVSyncEnabled(bool enabled) = 0;

		virtual bool isVSyncEnabled() const = 0;

		virtual void captureScreenshot() = 0;

		virtual const Image& getScreenCapture() const = 0;

		virtual void setSceneResizeMode(ResizeMode resizeMode) = 0;

		virtual ResizeMode getSceneResizeMode() const noexcept = 0;

		virtual void setSceneBufferSize(Size size) = 0;

		virtual Size getSceneBufferSize() const noexcept = 0;

		virtual void setSceneTextureFilter(TextureFilter textureFilter) = 0;

		virtual TextureFilter getSceneTextureFilter() const noexcept = 0;

		virtual void setBackgroundColor(const ColorF& color) = 0;

		virtual const ColorF& getBackgroundColor() const noexcept = 0;

		virtual void setLetterboxColor(const ColorF& color) = 0;

		virtual const ColorF& getLetterboxColor() const noexcept = 0;

		virtual std::pair<float, RectF> getLetterboxComposition() const noexcept = 0;

		virtual void updateSceneSize() = 0;
	};
}
