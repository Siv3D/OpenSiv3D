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
# include "Common.hpp"
# include "Optional.hpp"
# include "Mesh.hpp"

namespace s3d
{
	/// @brief 3D モデルを構成するモデルのパーツ
	struct ModelMeshPart
	{
		/// @brief メッシュ
		Mesh mesh;

		/// @brief 親となる 3D モデルにおける、マテリアルインデックス
		Optional<size_t> materialID;
	};
}
