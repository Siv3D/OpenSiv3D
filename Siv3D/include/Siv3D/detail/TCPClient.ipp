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
	inline bool TCPClient::lookahead(TriviallyCopyable& to)
	{
		return lookahead(std::addressof(to), sizeof(TriviallyCopyable));
	}

	SIV3D_CONCEPT_TRIVIALLY_COPYABLE_
	inline bool TCPClient::read(TriviallyCopyable& to)
	{
		return read(std::addressof(to), sizeof(TriviallyCopyable));
	}

	SIV3D_CONCEPT_TRIVIALLY_COPYABLE_
	inline bool TCPClient::send(const TriviallyCopyable& from)
	{
		return send(std::addressof(from), sizeof(TriviallyCopyable));
	}
}
