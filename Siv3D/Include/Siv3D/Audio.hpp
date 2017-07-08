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
# include <memory>
# include "Fwd.hpp"
# include "AssetHandle.hpp"
# include "Wave.hpp"

namespace s3d
{
	class Audio
	{
	protected:

		class Handle {};

		using AudioHandle = AssetHandle<Handle>;

		friend AudioHandle::~AssetHandle();

		std::shared_ptr<AudioHandle> m_handle;

	public:

		using IDType = AudioHandle::IDType;

		static constexpr IDType NullHandleID = AudioHandle::NullID;
	};
}
