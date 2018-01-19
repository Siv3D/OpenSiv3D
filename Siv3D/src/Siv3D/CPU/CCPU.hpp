//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "ICPU.hpp"
# include <Siv3D/CPU.hpp>

namespace s3d
{
	class CCPU : public ISiv3DCPU
	{
	private:

		CPUFeature m_feature;

	public:

		CCPU();

		~CCPU() override;

		bool init() override;

		void setFeature(const CPUFeature& feature) override;

		const CPUFeature& getFeature() const override;
	};
}
