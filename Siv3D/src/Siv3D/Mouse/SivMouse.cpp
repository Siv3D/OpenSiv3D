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

# include <Siv3D/Mouse.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Mouse/IMouse.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace Mouse
	{
		const Array<Input>& GetAllInputs() noexcept
		{
			return SIV3D_ENGINE(Mouse)->getAllInput();
		}

		double Wheel() noexcept
		{
			return SIV3D_ENGINE(Mouse)->wheel().y;
		}

		double WheelH() noexcept
		{
			return SIV3D_ENGINE(Mouse)->wheel().x;
		}
	}
}
