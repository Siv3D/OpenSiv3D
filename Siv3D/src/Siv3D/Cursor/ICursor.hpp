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

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/PointVector.hpp>
# include "CursorState.hpp"

namespace s3d
{
	enum class CursorStyle : uint8;
	struct Mat3x2;
	class Image;

	class SIV3D_NOVTABLE ISiv3DCursor
	{
	public:

		static ISiv3DCursor* Create();

		virtual ~ISiv3DCursor() = default;

		virtual void init() = 0;

		virtual bool update() = 0;

		virtual const CursorState& getState() const noexcept = 0;

		virtual void setPos(Point pos) = 0;

		virtual const Mat3x2& getLocalTransform() const noexcept = 0;

		virtual const Mat3x2& getCameraTransform() const noexcept = 0;

		virtual const Mat3x2& getScreenTransform() const noexcept = 0;

		virtual void setLocalTransform(const Mat3x2& matrix) = 0;

		virtual void setCameraTransform(const Mat3x2& matrix) = 0;

		virtual void setScreenTransform(const Mat3x2& matrix) = 0;

		virtual bool isClippedToWindow() const noexcept = 0;

		virtual void clipToWindow(bool clip) = 0;

		virtual void setDefaultStyle(CursorStyle style) = 0;

		virtual void requestStyle(CursorStyle style) = 0;

		virtual bool registerCursor(StringView name, const Image& image, Point hotSpot) = 0;

		virtual void requestStyle(StringView name) = 0;

		virtual void setCapture(bool captured) noexcept = 0;

		virtual bool isCaptured() const noexcept = 0;
	};
}
