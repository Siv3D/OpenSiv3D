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

# include "ModelData.hpp"
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	ModelData::ModelData()
	{
		// [Siv3D ToDo]

		m_initialized = true;
	}

	ModelData::ModelData(const FilePathView path)
	{
		// [Siv3D ToDo]

		m_initialized = true;
	}

	ModelData::~ModelData()
	{

	}

	bool ModelData::isInitialized() const noexcept
	{
		return m_initialized;
	}
}
