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

		virtual Point clientDelta() const = 0;

		virtual const Vec2& previousClientPosF() const = 0;

		virtual const Vec2& clientPosF() const = 0;

		virtual Vec2 clientDeltaF() const = 0;

		virtual void setPos(int32 x, int32 y) = 0;

		virtual void setTransform(const Mat3x2& matrix) = 0;

		virtual const Mat3x2& getTransform() const = 0;

		virtual void clipClientRect(bool clip) = 0;

		virtual void clip(const Optional<Rect>& rect) = 0;

		virtual void setStyle(CursorStyle style) = 0;

		virtual CursorStyle getStyle() = 0;
	};
}
