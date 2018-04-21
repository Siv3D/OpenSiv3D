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
	class TCPServer
	{
	private:

		class CTCPServer;

		std::shared_ptr<CTCPServer> pImpl;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		TCPServer();

		/// <summary>
		/// デストラクタ
		/// </summary>
		~TCPServer();

		void start(uint16 port);
	};
}
