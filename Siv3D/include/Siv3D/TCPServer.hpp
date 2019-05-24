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

		class TCPServerDetail;

		std::shared_ptr<TCPServerDetail> pImpl;

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

		[[nodiscard]] bool isAccepting() const;

		void disconnect();

		[[nodiscard]] bool hasSession() const;

		[[nodiscard]] bool hasSession(SessionID id) const;

		[[nodiscard]] size_t num_sessions() const;

		[[nodiscard]] Array<SessionID> getSessionIDs() const;

		[[nodiscard]] uint16 port() const;

		[[nodiscard]] size_t available(const Optional<SessionID>& id = unspecified);

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
