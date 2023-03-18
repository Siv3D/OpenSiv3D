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

# pragma once

namespace s3d
{
	namespace detail
	{
		struct JSONIteratorDetail;
		struct JSONConstIteratorDetail;
		struct JSONIterationProxyDetail;
		class JSONDetail;
		struct JSONPointerDetail;
		struct JSONValidatorDetail;
	}

	class JSONIterator;
	class JSONConstIterator;
	class JSONIterationProxy;
	class JSONArrayView;
	class JSON;
	struct JSONItem;
	struct JSONPointer;
	struct JSONValidator;
}
