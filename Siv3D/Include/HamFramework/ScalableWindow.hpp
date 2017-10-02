//-----------------------------------------------
//
//	This file is part of the HamFramework for Siv3D.
//
//	Copyright (C) 2014-2017 HAMSTRO
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D.hpp>

namespace s3d
{
	namespace ScalableWindow
	{
		enum class ContentScale
		{
			EnsureFit,
			
			Maximize,
			
			Default = EnsureFit
		};

		inline void SetBaseSize(const Size& baseSize = Size(640, 480))
		{
			Window::SetBaseSize(baseSize);
		}

		inline void SetBaseSize(int32 width, int32 height)
		{
			return SetBaseSize({ width, height });
		}

		inline Transformer2D CreateTransformer(const Size& baseSize, ContentScale contentScale = ContentScale::Default)
		{
			const double sx = static_cast<double>(Window::Width()) / baseSize.x;

			const double sy = static_cast<double>(Window::Height()) / baseSize.y;

			const double s = (contentScale == ContentScale::EnsureFit) ? Min(sx, sy) : Max(sx, sy);

			if (sx <= sy)
			{
				return Transformer2D(Mat3x2::Scale(s).translated(0, (Window::Height() - baseSize.y * s) * 0.5), true, Transformer2D::Target::PushScreen);
			}
			else
			{
				return Transformer2D(Mat3x2::Scale(s).translated((Window::Width() - baseSize.x * s) * 0.5, 0), true, Transformer2D::Target::PushScreen);
			}
		}

		inline Transformer2D CreateTransformer(int32 width, int32 height, ContentScale contentScale = ContentScale::Default)
		{
			return CreateTransformer({ width, height }, contentScale);
		}

		inline Transformer2D CreateTransformer(ContentScale contentScale = ContentScale::Default)
		{
			return CreateTransformer(Window::BaseSize(), contentScale);
		}

		inline RectF GetVirtualWindowArea(const Size& baseSize = Window::BaseSize())
		{
			const double sx = static_cast<double>(Window::Width()) / baseSize.x;

			const double sy = static_cast<double>(Window::Height()) / baseSize.y;

			const double s = Min(sx, sy);

			if (sx <= sy)
			{
				return RectF(baseSize * s).moveBy(0, (Window::Height() - baseSize.y * s) * 0.5);
			}
			else
			{
				return RectF(baseSize * s).moveBy((Window::Width() - baseSize.x * s) * 0.5, 0);
			}
		}

		inline Array<RectF> GetBlackBars(const Size& baseSize = Window::BaseSize())
		{
			const double sx = static_cast<double>(Window::Width()) / baseSize.x;

			const double sy = static_cast<double>(Window::Height()) / baseSize.y;

			const double s = Min(sx, sy);

			if (sx < sy)
			{
				const double h = (Window::Height() - baseSize.y * s) * 0.5;

				return{ RectF(0, 0, Window::Width(), h), RectF(0, Window::Height() - h,Window::Width(), h) };
			}
			else if (sx > sy)
			{
				const double w = (Window::Width() - baseSize.x * s) * 0.5;

				return{ RectF(0, 0, w, Window::Height()), RectF(Window::Width() - w, 0, w, Window::Height()) };
			}
			else
			{
				return Array<RectF>();
			}
		}

		inline Array<RectF> GetBlackBars(int32 width, int32 height)
		{
			return GetBlackBars({ width, height });
		}

		inline void DrawBlackBars(const ColorF& color = Palette::Black, const Size& baseSize = Window::BaseSize())
		{
			const Transformer2D transformerLocal(Mat3x2::Identity(), Transformer2D::Target::SetLocal);
			const Transformer2D transformerCamera(Mat3x2::Identity(), Transformer2D::Target::SetCamera);
			const Transformer2D transformerScreen(Mat3x2::Identity(), Transformer2D::Target::SetScreen);

			for (const auto& bar : GetBlackBars(baseSize))
			{
				bar.draw(color);
			}
		}

		inline void DrawBlackBars(const ColorF& color, int32 width, int32 height)
		{
			return DrawBlackBars(color, { width, height });
		}
	}
}

/* example
# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	ScalableWindow::SetBaseSize(640, 480);

	Window::Resize(1280, 640);

	const int32 dotSize = 40;

	Grid<int32> dots(Window::BaseSize() / dotSize);

	Graphics::SetBackground(Palette::White);

	while (System::Update())
	{
		const auto transformer = ScalableWindow::CreateTransformer();

		for (auto p : step(dots.size()))
		{
			const Rect rect(p * dotSize, dotSize);

			if (rect.leftClicked())
			{
				++dots[p] %= 4;
			}

			rect.stretched(-1).draw(ColorF(0.95 - dots[p] * 0.3));
		}

		ScalableWindow::DrawBlackBars(HSV(40, 0.2, 0.9));
	}
}
*/
