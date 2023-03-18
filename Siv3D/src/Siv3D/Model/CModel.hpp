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
# include <Siv3D/Common.hpp>
# include <Siv3D/Model/IModel.hpp>
# include <Siv3D/AssetHandleManager/AssetHandleManager.hpp>
# include "ModelData.hpp"

namespace s3d
{
	class CModel final : public ISiv3DModel
	{
	public:

		CModel();

		~CModel() override;

		virtual void init() override;

		Model::IDType create(FilePathView path, ColorOption colorOption) override;

		void release(Model::IDType handleID) override;

		const Array<ModelObject>& getObjects(Model::IDType handleID) override;

		const Array<Material>& getMaterials(Model::IDType handleID) override;

		const Sphere& getBoundingSphere(Model::IDType handleID) override;

		const Box& getBoundingBox(Model::IDType handleID) override;

	private:

		// Model の管理
		AssetHandleManager<Model::IDType, ModelData> m_models{ U"Model" };
	};
}
