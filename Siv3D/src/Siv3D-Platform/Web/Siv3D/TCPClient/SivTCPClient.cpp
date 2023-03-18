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

# include <Siv3D/TCPClient.hpp>
# include <Siv3D/TCPClient/TCPClientDetail.hpp>

namespace s3d
{
	TCPClient::TCPClient()
		: pImpl{ std::make_shared<TCPClientDetail>() } {}
	
	TCPClient::~TCPClient() {}

	bool TCPClient::connect(const IPv4Address& ip, const uint16 port)
	{
		return pImpl->connect(ip, port);
	}

	void TCPClient::cancelConnect()
	{
		pImpl->cancelConnect();
	}

	bool TCPClient::isConnected() const
	{
		return pImpl->isConnected();
	}

	void TCPClient::disconnect()
	{
		pImpl->disconnect();
	}

	uint16 TCPClient::port() const
	{
		return pImpl->port();
	}

	bool TCPClient::hasError() const
	{
		return pImpl->hasError();
	}

	TCPError TCPClient::getError() const
	{
		return pImpl->getError();
	}

	size_t TCPClient::available() const
	{
		return pImpl->available();
	}

	bool TCPClient::skip(const size_t size)
	{
		return pImpl->skip(size);
	}

	bool TCPClient::lookahead(void* dst, const size_t size) const
	{
		return pImpl->lookahead(dst, size);
	}

	bool TCPClient::read(void* dst, const size_t size)
	{
		return pImpl->read(dst, size);
	}

	bool TCPClient::send(const void* data, const size_t size)
	{
		return pImpl->send(data, size);
	}
}
