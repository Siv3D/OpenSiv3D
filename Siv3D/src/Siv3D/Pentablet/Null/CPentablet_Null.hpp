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
# include <Siv3D/Pentablet/IPentablet.hpp>

namespace s3d
{
	class CPentablet_Null final : public ISiv3DPentablet
	{
	public:

		CPentablet_Null();

		~CPentablet_Null() override;

		void init() override;

		void update() override;

		bool isAvailable() override;

		const PentabletState& getState() override;

	private:

		PentabletState nullState;
	};
}
