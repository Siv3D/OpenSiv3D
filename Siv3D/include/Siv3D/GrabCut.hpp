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

# pragma once
# include <memory>
# include "Common.hpp"
# include "2DShapes.hpp"
# include "Grid.hpp"
# include "GrabCutClass.hpp"

namespace s3d
{
	/// @brief 画像からの背景抽出
	class GrabCut
	{
	public:

		SIV3D_NODISCARD_CXX20
		GrabCut();

		SIV3D_NODISCARD_CXX20
		explicit GrabCut(const Image& image, GrabCutClass defaultMask = GrabCutClass::PossibleForeground);

		SIV3D_NODISCARD_CXX20
		GrabCut(const Image& image, const Rect& backgroundRect, size_t iterations = 2);

		void update(const Image& maskImage, const Color& foreground, const Color& background, size_t iterations = 2);

		void getResult(Grid<GrabCutClass>& result);

	private:

		class GrabCutDetail;

		std::shared_ptr<GrabCutDetail> pImpl;
	};
}
