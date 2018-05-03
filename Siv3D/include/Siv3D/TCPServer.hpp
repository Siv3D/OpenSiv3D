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
# include "Array.hpp"
# include "Optional.hpp"
# include "Unspecified.hpp"

namespace s3d
{
	using SessionID = uint64;

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

		void startAccept(uint16 port);

		void startAcceptMulti(uint16 port);

		void cancelAccept();

		bool isAccepting() const;

		void disconnect();

		bool hasSession() const;

		bool hasSession(SessionID id) const;

		size_t num_sessions() const;

		Array<SessionID> getSessionIDs() const;

		uint16 port() const;

		size_t available(const Optional<SessionID>& id = unspecified);

		bool skip(size_t size, const Optional<SessionID>& id = unspecified);

		bool lookahead(void* dst, size_t size, const Optional<SessionID>& id = unspecified) const;

		template <class Type, std::enable_if_t<std::is_trivially_copyable_v<Type>>* = nullptr>
		bool lookahead(Type& to, const Optional<SessionID>& id = unspecified)
		{
			return lookahead(std::addressof(to), sizeof(Type), id);
		}

		bool read(void* dst, size_t size, const Optional<SessionID>& id = unspecified);

		template <class Type, std::enable_if_t<std::is_trivially_copyable_v<Type>>* = nullptr>
		bool read(Type& to, const Optional<SessionID>& id = unspecified)
		{
			return read(std::addressof(to), sizeof(Type), id);
		}

		bool send(const void* data, size_t size, const Optional<SessionID>& id = unspecified);

		template <class Type, std::enable_if_t<std::is_trivially_copyable_v<Type>>* = nullptr>
		bool send(const Type& to, const Optional<SessionID>& id = unspecified)
		{
			return send(std::addressof(to), sizeof(Type), id);
		}
	};
}
