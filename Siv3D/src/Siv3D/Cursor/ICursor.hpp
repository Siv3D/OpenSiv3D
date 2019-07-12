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
# include <Siv3D/Fwd.hpp>
# include "CursorState.hpp"

namespace s3d
{
	class ISiv3DCursor
	{
	public:

		static ISiv3DCursor* Create();

		virtual ~ISiv3DCursor() = default;

		virtual void init() = 0;

		virtual void update() = 0;

		virtual void onMouseMove(int32 x, int32 y) = 0;

		virtual void onAltPressed() = 0;

		virtual const CursorState<Point>& screen() const = 0;

		virtual const CursorState<Point>& clientRaw() const = 0;

		virtual const CursorState<Vec2>& clientTransformedF() const = 0;

		virtual const CursorState<Point>& clientTransformed() const = 0;

		virtual const Array<std::pair<Point, uint64>>& getBufferTransformed() const = 0;

		virtual void setPos(const Point& pos) = 0;

		virtual void setLocalTransform(const Mat3x2& matrix) = 0;

		virtual void setCameraTransform(const Mat3x2& matrix) = 0;

		virtual void setScreenTransform(const Mat3x2& matrix) = 0;

		virtual const Mat3x2& getLocalTransform() const = 0;

		virtual const Mat3x2& getCameraTransform() const = 0;

		virtual const Mat3x2& getScreenTransform() const = 0;

		virtual void clipToWindow(bool clip) = 0;

		virtual void requestStyle(CursorStyle style) = 0;

		virtual void setDefaultStyle(CursorStyle style) = 0;

		virtual void applyStyleImmediately(CursorStyle style) = 0;

		virtual CursorStyle getRequestedStyle() const = 0;

		virtual CursorStyle getDefaultStyle() const = 0;
	};
}
