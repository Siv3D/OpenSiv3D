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

namespace s3d
{
	class ISiv3DNetwork
	{
	public:

		static ISiv3DNetwork* Create();

		virtual ~ISiv3DNetwork() = default;

		virtual void init() = 0;

		virtual Optional<IPv4> getMachineIP() const = 0;
	};
}
