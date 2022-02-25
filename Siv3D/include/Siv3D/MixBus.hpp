//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"

namespace s3d
{
	enum class MixBus : int32
	{
		Index0,
		Index1,
		Index2,
		Index3
	};

	inline static constexpr MixBus MixBus0 = MixBus::Index0;
	inline static constexpr MixBus MixBus1 = MixBus::Index1;
	inline static constexpr MixBus MixBus2 = MixBus::Index2;
	inline static constexpr MixBus MixBus3 = MixBus::Index3;
}
