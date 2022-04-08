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
# include "Concepts.hpp"
# include "TCPError.hpp"

namespace s3d
{
	class IPv4Address;

	/// @brief TCP クライアント
	class TCPClient
	{
	public:

		SIV3D_NODISCARD_CXX20
		TCPClient();

		~TCPClient();

		bool connect(const IPv4Address& ip, uint16 port);

		void cancelConnect();

		[[nodiscard]]
		bool isConnected() const;

		void disconnect();

		[[nodiscard]]
		uint16 port() const;

		[[nodiscard]]
		bool hasError() const;

		[[nodiscard]]
		TCPError getError() const;

		[[nodiscard]]
		size_t available() const;

		bool skip(size_t size);

		bool lookahead(void* dst, size_t size) const;

		SIV3D_CONCEPT_TRIVIALLY_COPYABLE
		bool lookahead(TriviallyCopyable& to);

		bool read(void* dst, size_t size);

		SIV3D_CONCEPT_TRIVIALLY_COPYABLE
		bool read(TriviallyCopyable& to);

		bool send(const void* src, size_t size);

		SIV3D_CONCEPT_TRIVIALLY_COPYABLE
		bool send(const TriviallyCopyable& from);

	private:

		class TCPClientDetail;

		std::shared_ptr<TCPClientDetail> pImpl;
	};
}

# include "detail/TCPClient.ipp"
