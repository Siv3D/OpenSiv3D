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

# include <Siv3D/RectanglePacking.hpp>
# include <ThirdParty/rectpack2D/finders_interface.h>

namespace s3d
{
	namespace detail
	{
		template <bool AllowFlip>
		[[nodiscard]]
		RectanglePack Pack(const Array<Rect>& rects, const int32 maxSide)
		{
			constexpr int32 DiscardStep = 1;
			using SpacesType = rectpack2D::empty_spaces<AllowFlip, rectpack2D::default_empty_spaces>;
			using RectType = rectpack2D::output_rect_t<SpacesType>;
			auto reportSuccessful = [](RectType&) {
				return rectpack2D::callback_result::CONTINUE_PACKING;
			};
			auto reportUnsuccessful = [](RectType&) {
				return rectpack2D::callback_result::ABORT_PACKING;
			};

			std::vector<RectType> rectangles(rects.size());
			{
				for (size_t i = 0; i < rects.size(); ++i)
				{
					const auto& rect = rects[i];
					rectangles[i] = rectpack2D::rect_xywh(0, 0, rect.w, rect.h);
				}
			}

			const auto resultSize = rectpack2D::find_best_packing<SpacesType>(
				rectangles,
				make_finder_input(
					maxSide,
					DiscardStep,
					reportSuccessful,
					reportUnsuccessful,
					(AllowFlip ? rectpack2D::flipping_option::ENABLED : rectpack2D::flipping_option::DISABLED)));

			Array<Rect> results(rectangles.size());
			{
				for (size_t i = 0; i < rectangles.size(); ++i)
				{
					const auto& r = rectangles[i];
					results[i].set(r.x, r.y, r.w, r.h);
				}
			}

			return{ results, Size{ resultSize.w, resultSize.h } };
		}
	}

	namespace RectanglePacking
	{
		RectanglePack Pack(const Array<Rect>& rects, const int32 maxSide, const AllowFlip allowFlip)
		{
			if (allowFlip)
			{
				return detail::Pack<true>(rects, maxSide);
			}
			else
			{
				return detail::Pack<false>(rects, maxSide);
			}
		}
	}
}
