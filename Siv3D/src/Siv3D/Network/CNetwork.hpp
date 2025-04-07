//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2025 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "INetwork.hpp"

namespace s3d
{
	class CNetwork final : public ISiv3DNetwork
	{
	public:

		CNetwork();

		~CNetwork() override;

		void init() override;

	private:

		bool m_curlInitialized = false;
	};
}
