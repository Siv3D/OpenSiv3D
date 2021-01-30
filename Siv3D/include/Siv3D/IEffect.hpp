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
# include <memory>
# include "Common.hpp"
# include "AssetHandle.hpp"
# include "Uncopyable.hpp"

namespace s3d
{
	struct IEffect : private Uncopyable
	{
		virtual ~IEffect() = default;

		virtual bool update(double timeSec) = 0;
	};
}
