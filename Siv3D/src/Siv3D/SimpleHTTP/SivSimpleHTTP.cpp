//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Common.hpp>
# include <Siv3D/HTTPResponse.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/Parse.hpp>

namespace s3d
{
	HTTPResponse::HTTPResponse(const std::string& response)
	{
		const size_t statusLineEnd = response.find(U'\n');
		{
			if (statusLineEnd == std::string::npos)
			{
				return;
			}

			m_statusLine = Unicode::Widen(std::string_view(response.data(), (statusLineEnd + 1)));
		}

		{
			// Status-Line = HTTP-Version SP Status-Code SP Reason-Phrase CRLF
			if (not m_statusLine.starts_with(U"HTTP"))
			{
				return;
			}

			const Array<String> elements = m_statusLine.split(U' ');

			if (elements.size() < 2)
			{
				return;
			}

			m_statusCode = HTTPStatusCode{ ParseOr<uint32>(elements[1], 0) };
		}

		const size_t headerEnd = response.find("\r\n\r\n", statusLineEnd, 4);
		{
			if (headerEnd == std::string::npos)
			{
				return;
			}

			const std::string_view view(response.data() + (statusLineEnd + 1),
				(headerEnd + 2) - (statusLineEnd + 1));
			m_header = Unicode::Widen(view);
		}
	}

	HTTPStatusCode HTTPResponse::getStatusCode() const noexcept
	{
		return m_statusCode;
	}

	const String& HTTPResponse::getStatusLine() const noexcept
	{
		return m_statusLine;
	}

	const String& HTTPResponse::getHeader() const noexcept
	{
		return m_header;
	}

	HTTPResponse::operator bool() const noexcept
	{
		return (not isInvalid());
	}

	bool HTTPResponse::isInvalid() const noexcept
	{
		return (FromEnum(m_statusCode) < 100)
			|| (600 <= FromEnum(m_statusCode));
	}

	bool HTTPResponse::isInformational() const noexcept
	{
		return InRange(FromEnum(m_statusCode), 100u, 199u);
	}

	bool HTTPResponse::isSuccessful() const noexcept
	{
		return InRange(FromEnum(m_statusCode), 200u, 299u);
	}

	bool HTTPResponse::isRedirection() const noexcept
	{
		return InRange(FromEnum(m_statusCode), 300u, 399u);
	}

	bool HTTPResponse::isClientError() const noexcept
	{
		return InRange(FromEnum(m_statusCode), 400u, 499u);
	}

	bool HTTPResponse::isServerError() const noexcept
	{
		return InRange(FromEnum(m_statusCode), 500u, 599u);
	}

	bool HTTPResponse::isOK() const noexcept
	{
		return (m_statusCode == HTTPStatusCode::OK);
	}

	bool HTTPResponse::isNotFound() const noexcept
	{
		return (m_statusCode == HTTPStatusCode::NotFound);
	}
}