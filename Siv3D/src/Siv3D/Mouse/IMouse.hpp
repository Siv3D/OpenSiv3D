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
# include <Siv3D/Array.hpp>
# include <Siv3D/InputGroups.hpp>

namespace s3d
{
	class SIV3D_NOVTABLE ISiv3DMouse
	{
	public:

		static ISiv3DMouse* Create();

		virtual ~ISiv3DMouse() = default;

		virtual void init() = 0;

		virtual void update() = 0;

		virtual bool down(uint32 index) const = 0;

		virtual bool pressed(uint32 index) const = 0;

		virtual bool up(uint32 index) const = 0;

		virtual void clearInput(uint32 index) = 0;

		virtual bool cleared(uint32 index) const = 0;

		virtual Duration pressedDuration(uint32 index) const = 0;

		virtual const Array<Input>& getAllInput() const noexcept = 0;

		virtual const Vec2& wheel() const noexcept = 0;

		virtual void onMouseButtonUpdated(int32 index, bool pressed) = 0;

		virtual void onScroll(double x, double y) = 0;
	};
}
