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

		bool connect(const IPv4& ip, uint16 port);

		void cancelConnect();

		bool isConnected() const;

		void disconnect();

		uint16 port() const;

		bool hasError() const;

		//NetworkErrorCode getError() const;

		size_t available() const;

		bool skip(size_t size);

		bool lookahead(void* dst, size_t size) const;

		template <class Type, std::enable_if_t<std::is_trivially_copyable_v<Type>>* = nullptr>
		bool lookahead(Type& to)
		{
			return lookahead(std::addressof(to), sizeof(Type), id);
		}

		bool read(void* dst, size_t size);

		template <class Type, std::enable_if_t<std::is_trivially_copyable_v<Type>>* = nullptr>
		bool read(Type& to)
		{
			return read(std::addressof(to), sizeof(Type), id);
		}

		bool send(const void* data, size_t size);

		template <class Type, std::enable_if_t<std::is_trivially_copyable_v<Type>>* = nullptr>
		bool send(const Type& to)
		{
			return send(std::addressof(to), sizeof(Type), id);
		}
	};
}
