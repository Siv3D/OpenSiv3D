//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/PointVector.hpp>
# include "CursorState.hpp"

namespace s3d
{
	class Image;

	class SIV3D_NOVTABLE ISiv3DCursor
	{
	public:

		static ISiv3DCursor* Create();

		virtual ~ISiv3DCursor() = default;

		virtual void init() = 0;

		virtual bool update() = 0;

		virtual const CursorState& getState() const noexcept = 0;

		virtual bool registerCursor(StringView name, const Image& image, const Point& hotSpot) = 0;

		virtual void requestStyle(StringView name) = 0;
	};
}
