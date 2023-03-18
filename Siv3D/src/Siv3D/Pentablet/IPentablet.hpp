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
# include <Siv3D/Pentablet.hpp>

namespace s3d
{
	struct PentabletState
	{
		double pressure = 0.0;
		
		double tangentPressure = 0.0;

		double azimuth = 0.0;

		double altitude = 0.0;
		
		double twist = 0.0;

		bool supportPressure = false;

		bool supportTangentPressure = false;

		bool supportOrientation = false;
	};

	class SIV3D_NOVTABLE ISiv3DPentablet
	{
	public:

		static ISiv3DPentablet* Create();

		virtual ~ISiv3DPentablet() = default;

		virtual void init() = 0;

		virtual void update() = 0;

		virtual bool isAvailable() = 0;

		virtual const PentabletState& getState() = 0;
	};
}
