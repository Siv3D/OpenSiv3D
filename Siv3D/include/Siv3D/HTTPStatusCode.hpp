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
# include "Common.hpp"

namespace s3d
{
	/// @brief HTTP ステータスコード
	/// @remark https://tools.ietf.org/html/rfc7231#section-6
	enum class HTTPStatusCode : uint32
	{
		Invalid						= 0,

		// Informational 1xx
		Continue					= 100,
		SwitchingProtocols			= 101,

		// Successful 2xx
		OK							= 200,
		Created						= 201,
		Accepted					= 202,
		NonAuthoritativeInformation	= 203,
		NoContent					= 204,
		ResetContent				= 205,
		PartialContent				= 206,

		// Redirection 3xx
		MultipleChoices				= 300,
		movedPermanently			= 301,
		Found						= 302,
		SeeOther					= 303,
		NotModified					= 304,
		UseProxy					= 305,
		TemporaryRedirect			= 307,

		// Client Error 4xx
		BadRequest					= 400,
		Unauthorized				= 401,
		PaymentRequied				= 402,
		Forbidden					= 403,
		NotFound					= 404,
		MethodNotAllowed			= 405,
		NotAcceptable				= 406,
		ProxyAuthenticationRequied	= 407,
		RequestTimeout				= 408,
		Conflict					= 409,
		Gone						= 410,
		LengthRequied				= 411,
		Preconditionfailed			= 412,
		PayloadTooLarge				= 413,
		URITooLong					= 414,
		UnsupportedMediaType		= 415,
		RangeNotSatisfiable			= 416,
		ExpectationFailed			= 417,
		UpgradeRequied				= 426,

		// Server Error 5xx
		InternalServerError			= 500,
		NotImplemented				= 501,
		BadGateway					= 502,
		ServiceUnavailable			= 503,
		GatewayTimeout				= 504,
		HTTPVersionNotSupported		= 505,
	};
}