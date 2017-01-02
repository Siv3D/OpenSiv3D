//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "Fwd.hpp"

namespace s3d
{
	class MathParser
	{
	private:

		class CMathParser;

		std::shared_ptr<CMathParser> pImpl;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		MathParser();
	};
}
