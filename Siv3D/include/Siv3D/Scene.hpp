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
# include "Fwd.hpp"
# include "PointVector.hpp"
# include "Color.hpp"
# include "Window.hpp"
# include "SamplerState.hpp"

namespace s3d
{
	enum class ScaleMode
	{
		ResizeFill,

		AspectFit,
	};

	namespace Scene
	{
		inline constexpr s3d::Size DefaultSceneSize(Window::DefaultClientSize);

		void Resize(const s3d::Size& size);

		void Resize(int32 width, int32 height);

		[[nodiscard]] s3d::Size Size();

		[[nodiscard]] int32 Width();

		[[nodiscard]] int32 Height();

		[[nodiscard]] Point Center();

		[[nodiscard]] Vec2 CenterF();

		[[nodiscard]] s3d::Rect Rect();


		inline constexpr ScaleMode DefaultScaleMode = ScaleMode::AspectFit;

		void SetScaleMode(ScaleMode scaleMode);

		[[nodiscard]] ScaleMode GetScaleMode();


		inline constexpr TextureFilter DefaultFilter = TextureFilter::Linear;

		void SetTextureFilter(TextureFilter textureFilter);

		[[nodiscard]] TextureFilter GetTextureFilter();



		inline constexpr ColorF DefaultBackgroundColor(Palette::DefaultBackground);

		void SetBackground(const ColorF& color);


		inline constexpr ColorF DefaultLetterBoxColor(Palette::DefaultLetterbox);

		void SetLetterbox(const ColorF& color);


		inline constexpr double DefaultMaxDeltaTime = 0.1;

		void SetMaxDeltaTime(double timeSec);

		[[nodiscard]] double GetMaxDeltaTime();

		[[nodiscard]] double DeltaTime();

		[[nodiscard]] double Time();


		[[nodiscard]] int32 FrameCount();

		[[nodiscard]] Vec2 ClientToScene(const Vec2& pos);
	}
}
