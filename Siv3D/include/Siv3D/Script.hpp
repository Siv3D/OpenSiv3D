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
# include "Common.hpp"
# include "AssetHandle.hpp"
# include "String.hpp"
# include "ScriptModule.hpp"

namespace s3d
{
	struct ScriptCompileOption
	{
		enum Option
		{
			BuildWithLineCues = 0b00001,
		};
	};

	/// @brief スクリプト
	class Script : public AssetHandle<Script>
	{
	public:

		SIV3D_NODISCARD_CXX20
		Script();

		SIV3D_NODISCARD_CXX20
		explicit Script(FilePathView path, int32 compileOption = 0);

		virtual ~Script();

		void swap(Script& other) noexcept;
	};
}

template <>
inline void std::swap(s3d::Script& a, s3d::Script& b) noexcept;

# include "detail/Script.ipp"
