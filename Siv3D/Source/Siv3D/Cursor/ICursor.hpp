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

namespace s3d
{
	class ISiv3DCursor
	{
	public:

		static ISiv3DCursor* Create();

		virtual ~ISiv3DCursor() = default;

		virtual bool init() = 0;

		virtual void update() = 0;

		virtual const Point& previousScreenPos() const = 0;

		virtual const Point& screenPos() const = 0;

		virtual const Point& screenDelta() const = 0;

		virtual const Point& previousClientPos() const = 0;

		virtual const Point& clientPos() const = 0;

		virtual const Point& clientDelta() const = 0;

		virtual void setPos(int32 x, int32 y) = 0;

		virtual void clipClientRect(bool clip) = 0;

		virtual void clip(const Optional<Rect>& rect) = 0;
	};
}
