//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include "Common.hpp"
# include "Array.hpp"
# include "Optional.hpp"
# include "Unspecified.hpp"

namespace s3d
{
	using TCPSessionID = uint64;

	/// @brief TCP サーバ
	class TCPServer
	{
	public:

		SIV3D_NODISCARD_CXX20
		TCPServer();

		~TCPServer();

		void startAccept(uint16 port);

		void startAcceptMulti(uint16 port);

		void cancelAccept();

		[[nodiscard]]
		bool isAccepting() const;

		void disconnect();

		[[nodiscard]]
		bool hasSession() const;

		[[nodiscard]]
		bool hasSession(TCPSessionID id) const;

		[[nodiscard]]
		size_t num_sessions() const;

		[[nodiscard]]
		Array<TCPSessionID> getSessionIDs() const;

		[[nodiscard]]
		uint16 port() const;

		[[nodiscard]]
		size_t available(const Optional<TCPSessionID>& id = unspecified);

		bool skip(size_t size, const Optional<TCPSessionID>& id = unspecified);

		bool lookahead(void* dst, size_t size, const Optional<TCPSessionID>& id = unspecified) const;

		SIV3D_CONCEPT_TRIVIALLY_COPYABLE
		bool lookahead(TriviallyCopyable& to, const Optional<TCPSessionID>& id = unspecified);

		bool read(void* dst, size_t size, const Optional<TCPSessionID>& id = unspecified);

		SIV3D_CONCEPT_TRIVIALLY_COPYABLE
		bool read(TriviallyCopyable& to, const Optional<TCPSessionID>& id = unspecified);

		bool send(const void* data, size_t size, const Optional<TCPSessionID>& id = unspecified);

		SIV3D_CONCEPT_TRIVIALLY_COPYABLE
		bool send(const TriviallyCopyable& to, const Optional<TCPSessionID>& id = unspecified);

	private:

		class TCPServerDetail;

		std::shared_ptr<TCPServerDetail> pImpl;
	};
}

# include "detail/TCPServer.ipp"
