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
# include <memory>
# include "Fwd.hpp"

namespace s3d
{
	class TCPClient
	{
	private:

		class CTCPClient;

		std::shared_ptr<CTCPClient> pImpl;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		TCPClient();

		/// <summary>
		/// デストラクタ
		/// </summary>
		~TCPClient();

		bool open();
	};
}
