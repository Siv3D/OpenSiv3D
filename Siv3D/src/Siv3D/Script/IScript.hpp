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

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/Script.hpp>

namespace s3d
{
	class SIV3D_NOVTABLE ISiv3DScript
	{
	public:

		static ISiv3DScript* Create();

		virtual ~ISiv3DScript() = default;

		virtual void init() = 0;

		virtual void shutdown() = 0;

		virtual Script::IDType createFromCode(StringView code, int32 compileOption) = 0;

		virtual Script::IDType createFromFile(FilePathView path, int32 compileOption) = 0;

		virtual void release(Script::IDType handleID) = 0;

		virtual Array<String> retrieveInternalMessages() = 0;
	};
}
