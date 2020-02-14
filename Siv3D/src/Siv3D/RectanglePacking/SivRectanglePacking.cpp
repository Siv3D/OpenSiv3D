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

# include <Siv3D/RectanglePacking.hpp>
# include <rectpack2D/finders_interface.h>

namespace s3d
{
	namespace RectanglePacking
	{
		[[nodiscard]] std::pair<Array<Rect>, Size> Pack(const Array<Rect>& rects, const int32 maxSide)
		{
			using namespace rectpack2D;
			constexpr bool AllowFlip = false;
			using SpacesType = empty_spaces<AllowFlip, default_empty_spaces>;
			using RectType = output_rect_t<SpacesType>;
			auto reportSuccessful = [](RectType&) {
				return callback_result::CONTINUE_PACKING;
			};
			auto reportUnsuccessful = [](RectType&) {
				return callback_result::ABORT_PACKING;
			};
			const int32 DiscardStep = 1;

			std::vector<RectType> rectangles(rects.size());
			{
				for (size_t i = 0; i < rects.size(); ++i)
				{
					const auto& rect = rects[i];
					rectangles[i] = rect_xywh(0, 0, rect.w, rect.h);
				}
			}

			const auto resultSize = find_best_packing<SpacesType>(
				rectangles,
				make_finder_input(
					maxSide,
					DiscardStep,
					reportSuccessful,
					reportUnsuccessful,
					flipping_option::DISABLED));

			Array<Rect> results(rectangles.size());
			{
				for (size_t i = 0; i < rectangles.size(); ++i)
				{
					const auto& r = rectangles[i];
					results[i].set(r.x, r.y, r.w, r.h);
				}
			}

			return{ results, Size(resultSize.w, resultSize.h) };
		}
	}
}
