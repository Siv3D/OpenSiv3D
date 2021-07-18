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
# include <Siv3D/StringView.hpp>

namespace s3d
{
	class ModelData
	{
	public:

		SIV3D_NODISCARD_CXX20
		explicit ModelData();

		SIV3D_NODISCARD_CXX20
		ModelData(FilePathView path);

		~ModelData();

		[[nodiscard]]
		bool isInitialized() const noexcept;

	private:

		bool m_initialized = false;
	};
}
