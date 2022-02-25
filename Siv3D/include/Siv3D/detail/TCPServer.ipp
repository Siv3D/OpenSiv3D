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

namespace s3d
{
	SIV3D_CONCEPT_TRIVIALLY_COPYABLE_
	inline bool TCPServer::lookahead(TriviallyCopyable& to, const Optional<TCPSessionID>& id)
	{
		return lookahead(std::addressof(to), sizeof(TriviallyCopyable), id);
	}

	SIV3D_CONCEPT_TRIVIALLY_COPYABLE_
	inline bool TCPServer::read(TriviallyCopyable& to, const Optional<TCPSessionID>& id)
	{
		return read(std::addressof(to), sizeof(TriviallyCopyable), id);
	}

	SIV3D_CONCEPT_TRIVIALLY_COPYABLE_
	inline bool TCPServer::send(const TriviallyCopyable& to, const Optional<TCPSessionID>& id)
	{
		return send(std::addressof(to), sizeof(TriviallyCopyable), id);
	}
}
