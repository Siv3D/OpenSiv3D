﻿//-----------------------------------------------
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
	template <class VectorType>
	struct CursorState
	{
		VectorType previous = { 0,0 };

		VectorType current = { 0,0 };

		VectorType delta = { 0,0 };
	};

	class ISiv3DCursor
	{
	public:

		static ISiv3DCursor* Create();

		virtual ~ISiv3DCursor() = default;

		virtual bool init() = 0;

		virtual void update() = 0;

		virtual const CursorState<Point>& screen() const = 0;

		virtual const CursorState<Point>& clientRaw() const = 0;

		virtual const CursorState<Vec2>& clientTransformedF() const = 0;

		virtual const CursorState<Point>& clientTransformed() const = 0;

		virtual void setPos(int32 x, int32 y) = 0;

		virtual void setTransformLocal(const Mat3x2& matrix) = 0;

		virtual void setTransformCamera(const Mat3x2& matrix) = 0;

		virtual void setTransformScreen(const Mat3x2& matrix) = 0;

		virtual const Mat3x2& getTransformLocal() const = 0;

		virtual const Mat3x2& getTransformCamera() const = 0;

		virtual const Mat3x2& getTransformScreen() const = 0;

		virtual void clipClientRect(bool clip) = 0;

		virtual void clip(const Optional<Rect>& rect) = 0;

		virtual void setStyle(CursorStyle style) = 0;

		virtual CursorStyle getStyle() = 0;
	};
}
