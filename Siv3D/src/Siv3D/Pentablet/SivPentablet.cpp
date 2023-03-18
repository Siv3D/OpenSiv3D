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

# include <Siv3D/Pentablet.hpp>
# include <Siv3D/Pentablet/IPentablet.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace Pentablet
	{
		bool IsAvailable()
		{
			return SIV3D_ENGINE(Pentablet)->isAvailable();
		}

		bool SupportsPressure()
		{
			return SIV3D_ENGINE(Pentablet)->getState().supportPressure;
		}

		bool SupportsTangentPressure()
		{
			return SIV3D_ENGINE(Pentablet)->getState().supportTangentPressure;
		}

		bool SupportsOrientation()
		{
			return SIV3D_ENGINE(Pentablet)->getState().supportOrientation;
		}

		double Pressure()
		{
			return SIV3D_ENGINE(Pentablet)->getState().pressure;
		}

		double TangentPressure()
		{
			return SIV3D_ENGINE(Pentablet)->getState().tangentPressure;
		}

		double Azimuth()
		{
			return (SIV3D_ENGINE(Pentablet)->getState().azimuth * 360.0);
		}

		double Altitude()
		{
			return (SIV3D_ENGINE(Pentablet)->getState().altitude * 90.0);
		}

		double Twist()
		{
			return SIV3D_ENGINE(Pentablet)->getState().twist;
		}
	}
}
