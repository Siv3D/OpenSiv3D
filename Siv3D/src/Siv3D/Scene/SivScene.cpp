//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Scene.hpp>
# include <Siv3D/Scene/IScene.hpp>
# include <Siv3D/Renderer/IRenderer.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace Scene
	{
		void Resize(const s3d::Size size)
		{
			SIV3D_ENGINE(Renderer)->setSceneBufferSize(size);
		}

		void Resize(const int32 width, const int32 height)
		{
			Resize(s3d::Size{ width, height });
		}

		s3d::Size Size() noexcept
		{
			return SIV3D_ENGINE(Renderer)->getSceneBufferSize();
		}

		int32 Width() noexcept
		{
			return Size().x;
		}

		int32 Height() noexcept
		{
			return Size().y;
		}

		Point Center() noexcept
		{
			return (Size() / 2);
		}

		Vec2 CenterF() noexcept
		{
			return (Size() * 0.5);
		}

		s3d::Rect Rect() noexcept
		{
			return s3d::Rect{ Size() };
		}

		void SetResizeMode(const ResizeMode resizeMode)
		{
			return SIV3D_ENGINE(Renderer)->setSceneResizeMode(resizeMode);
		}

		ResizeMode GetResizeMode() noexcept
		{
			return SIV3D_ENGINE(Renderer)->getSceneResizeMode();
		}

		void SetTextureFilter(const TextureFilter textureFilter)
		{
			SIV3D_ENGINE(Renderer)->setSceneTextureFilter(textureFilter);
		}

		TextureFilter GetTextureFilter() noexcept
		{
			return SIV3D_ENGINE(Renderer)->getSceneTextureFilter();
		}

		void SetBackground(const ColorF& color)
		{
			SIV3D_ENGINE(Renderer)->setBackgroundColor(color);
		}

		const ColorF& GetBackground() noexcept
		{
			return SIV3D_ENGINE(Renderer)->getBackgroundColor();
		}

		void SetLetterbox(const ColorF& color)
		{
			SIV3D_ENGINE(Renderer)->setLetterboxColor(color);
		}

		const ColorF& GetLetterBox() noexcept
		{
			return SIV3D_ENGINE(Renderer)->getLetterboxColor();
		}

		void SetMaxDeltaTime(const double timeSec)
		{
			SIV3D_ENGINE(Scene)->getFrameTimer().setMaxDeltaTimeSec(timeSec);
		}

		double GetMaxDeltaTime() noexcept
		{
			return SIV3D_ENGINE(Scene)->getFrameTimer().getMaxDeltaTimeSec();
		}

		double DeltaTime() noexcept
		{
			return SIV3D_ENGINE(Scene)->getFrameTimer().getDeltaTimeSec();
		}

		double Time() noexcept
		{
			return SIV3D_ENGINE(Scene)->getFrameTimer().getTimeSec();
		}

		int32 FrameCount() noexcept
		{
			return SIV3D_ENGINE(Scene)->getFrameCounter().getUserFrameCount();
		}

		Vec2 ClientToScene(const Vec2 pos) noexcept
		{
			auto [s, viewRect] = SIV3D_ENGINE(Renderer)->getLetterboxComposition();
			return (pos - viewRect.pos) / s;
		}
	}
}
