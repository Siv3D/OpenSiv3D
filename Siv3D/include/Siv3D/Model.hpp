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
# include "StringView.hpp"

namespace s3d
{
	class Model : public AssetHandle<Model>
	{
	public:

		SIV3D_NODISCARD_CXX20
		Model();

		SIV3D_NODISCARD_CXX20
		explicit Model(const FilePathView path);

		virtual ~Model();


		void swap(Model& other) noexcept;
	};
}

template <>
inline void std::swap(s3d::Model& a, s3d::Model& b) noexcept;

# include "detail/Model.ipp"
