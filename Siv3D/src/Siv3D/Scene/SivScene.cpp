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

# include <Siv3D/Scene.hpp>
# include <Siv3D/Rectangle.hpp>
# include <Siv3D/FloatRect.hpp>
# include <Siv3DEngine.hpp>
# include <Window/IWindow.hpp>
# include <Graphics/IGraphics.hpp>
# include <Renderer2D/IRenderer2D.hpp>
# include <System/ISystem.hpp>

namespace s3d
{
	namespace Scene
	{
		void Resize(const s3d::Size& size)
		{
			Siv3DEngine::Get<ISiv3DGraphics>()->setSceneSize(size);
		}

		void Resize(int32 width, int32 height)
		{
			Resize(s3d::Size(width, height));
		}

		s3d::Size Size()
		{
			return Siv3DEngine::Get<ISiv3DGraphics>()->getSceneSize();
		}

		int32 Width()
		{
			return Size().x;
		}

		int32 Height()
		{
			return Size().y;
		}

		Point Center()
		{
			return Size() / 2;
		}

		Vec2 CenterF()
		{
			return Size() * 0.5;
		}

		s3d::Rect Rect()
		{
			return s3d::Rect(Size());
		}

		void SetScaleMode(const ScaleMode scaleMode)
		{
			Siv3DEngine::Get<ISiv3DWindow>()->setScaleMode(scaleMode);
		}

		ScaleMode GetScaleMode()
		{
			return Siv3DEngine::Get<ISiv3DWindow>()->getScaleMode();
		}

		void SetTextureFilter(const TextureFilter textureFilter)
		{
			Siv3DEngine::Get<ISiv3DGraphics>()->setSceneTextureFilter(textureFilter);
		}

		TextureFilter GetTextureFilter()
		{
			return Siv3DEngine::Get<ISiv3DGraphics>()->getSceneTextureFilter();
		}

		void SetBackground(const ColorF& color)
		{
			Siv3DEngine::Get<ISiv3DGraphics>()->setBackgroundColor(color);
		}

		void SetLetterbox(const ColorF& color)
		{
			Siv3DEngine::Get<ISiv3DGraphics>()->setLetterboxColor(color);
		}

		void SetMaxDeltaTime(const double timeSec)
		{
			Siv3DEngine::Get<ISiv3DSystem>()->getFrameDelta().setMaxDeltaTimeSec(timeSec);
		}

		double GetMaxDeltaTime()
		{
			return Siv3DEngine::Get<ISiv3DSystem>()->getFrameDelta().getMaxDeltaTimeSec();
		}

		double DeltaTime()
		{
			return Siv3DEngine::Get<ISiv3DSystem>()->getFrameDelta().getDeltaTimeSec();
		}

		double Time()
		{
			return Siv3DEngine::Get<ISiv3DSystem>()->getFrameDelta().getTimeSec();
		}

		int32 FrameCount()
		{
			return Siv3DEngine::Get<ISiv3DSystem>()->getUserFrameCount();
		}

		Vec2 ClientToScene(const Vec2& pos)
		{
			if (Siv3DEngine::Get<ISiv3DWindow>()->getScaleMode() == ScaleMode::ResizeFill)
			{
				return pos;
			}

			auto [s, viewRect] = Siv3DEngine::Get<ISiv3DRenderer2D>()->getLetterboxingTransform();
			return (pos - Vec2(viewRect.left, viewRect.top)) / s;
		}
	}
}
