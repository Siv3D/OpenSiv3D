//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"

namespace s3d
{
	class IAddon
	{
	public:

		virtual ~IAddon() = default;

		virtual bool init() { return true; }

		virtual bool update() { return true; }

		virtual void draw() const {}
	};
}
