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

# include <Siv3D/Common.hpp>
# include <Siv3D/HTTPResponse.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/Parse.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static bool IsDelimiter(char ch) noexcept
		{
			return ((ch == '\r') || (ch == '\n'));
		}

		[[nodiscard]]
		static std::string GetLastResponseHeader(const std::string& responseHeaders)
		{
			if (responseHeaders.empty())
			{
				return{};
			}

			constexpr std::string_view Delimiter = "\r\n\r\n";

			size_t pos = responseHeaders.size();

			while ((0 < pos) && IsDelimiter(responseHeaders[pos - 1]))
			{
				--pos;
			}

			const size_t start = responseHeaders.rfind(Delimiter, (pos - 1));

			if (start == std::string::npos)
			{
				return (responseHeaders.substr(0, pos) + "\r\n");
			}
			else
			{
				return (responseHeaders.substr((start + Delimiter.size()), (pos - start - Delimiter.size())) + "\r\n");
			}
		}

		[[nodiscard]]
		static std::string GetStatusLine(const std::string& responseHeader)
		{
			if (not responseHeader.starts_with("HTTP/"))
			{
				return{};
			}

			const size_t endOfStatusLine = responseHeader.find("\r\n");

			if (endOfStatusLine == std::string::npos)
			{
				return responseHeader;
			}
			else
			{
				return responseHeader.substr(0, endOfStatusLine);
			}
		}

		[[nodiscard]]
		static int32 GetStatusCode(const std::string& statusLine)
		{
			if (statusLine.empty())
			{
				return 0;
			}

			const size_t statusCodePos = statusLine.find(' ');

			if (statusCodePos == std::string::npos)
			{
				return 0;
			}

			// statusLine からステータスコードを抽出して整数に変換
			try
			{
				return std::stoi(statusLine.substr((statusCodePos + 1), 3));
			}
			catch (const std::exception&)
			{
				return 0;
			}
		}

		[[nodiscard]]
		static std::string GetHeaders(const std::string& responseHeader)
		{
			const size_t endOfStatusLine = responseHeader.find("\r\n");

			if (endOfStatusLine == std::string::npos)
			{
				return{};
			}
			else
			{
				return responseHeader.substr(endOfStatusLine + 2); // 2 を足して、\r\n をスキップ
			}
		}
	}

	HTTPResponse::HTTPResponse(const std::string& responseHeaders)
	{
		// 最後のレスポンスヘッダ（リダイレクト発生時、responseHeaders には複数のレスポンスが含まれる）
		const std::string lastResponseHeader = detail::GetLastResponseHeader(responseHeaders);

		// ステータスライン
		const std::string statusLine = detail::GetStatusLine(lastResponseHeader);

		// ステータスコード
		const int32 statusCode = detail::GetStatusCode(statusLine);

		if (statusCode == 0)
		{
			return;
		}

		// ステータスラインを除いたヘッダ部分
		const std::string headers = detail::GetHeaders(lastResponseHeader);

		m_statusLine = Unicode::WidenAscii(statusLine);

		m_statusCode = ToEnum<HTTPStatusCode>(statusCode);

		m_header = Unicode::WidenAscii(headers);
	}

	HTTPStatusCode HTTPResponse::getStatusCode() const noexcept
	{
		return m_statusCode;
	}

	int32 HTTPResponse::getStatusCodeInt() const noexcept
	{
		return static_cast<int32>(m_statusCode);
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