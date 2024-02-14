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
# include <Siv3D/Optional.hpp>

namespace s3d
{
	class SIV3D_NOVTABLE ISiv3DFrameRateLimit
	{
	public:

		static ISiv3DFrameRateLimit* Create();

		virtual ~ISiv3DFrameRateLimit() = default;

		virtual void update() = 0;

		virtual void setTargetFrameRate(const Optional<double>& fps) = 0;

		virtual Optional<double> getTargetFrameRate() const = 0;
	};
}
