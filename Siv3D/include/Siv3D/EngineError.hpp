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
# include "Fwd.hpp"
# include "Error.hpp"

namespace s3d
{
	class EngineError : public Error
	{
	public:

		explicit EngineError(StringView what)
			: Error(what) {}
	};
}
