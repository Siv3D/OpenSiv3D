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
# include <atomic>
# include <Siv3D/System/ISystem.hpp>

namespace s3d
{
	class CSystem final : public ISiv3DSystem
	{
	public:

		CSystem();

		~CSystem() override;

		void init() override;

		void init2();

		bool update() override;

		void onDeviceChange();

	private:

		std::atomic<bool> m_onDeviceChange = { false };
	};
}
