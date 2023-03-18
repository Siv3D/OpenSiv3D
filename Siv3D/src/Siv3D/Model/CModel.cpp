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

# include "CModel.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Browser.hpp>

namespace s3d
{
	CModel::CModel()
	{
		// do nothing
	}

	CModel::~CModel()
	{
		LOG_SCOPED_TRACE(U"CModel::~CModel()");

		m_models.destroy();
	}

	void CModel::init()
	{
		LOG_SCOPED_TRACE(U"CModel::init()");

		// null Model を管理に登録
		{
			// null Model を作成
			auto nullModel = std::make_unique<ModelData>();

			if (not nullModel->isInitialized()) // もし作成に失敗していたら
			{
				throw EngineError{ U"Null Model initialization failed" };
			}

			// 管理に登録
			m_models.setNullData(std::move(nullModel));
		}
	}

	Model::IDType CModel::create(const FilePathView path, const ColorOption colorOption)
	{
	# if SIV3D_PLATFORM(WEB)
		Platform::Web::FetchFile(path);
	# endif

		auto model = std::make_unique<ModelData>(path, colorOption);

		if (not model->isInitialized())
		{
			return Model::IDType::NullAsset();
		}

		return m_models.add(std::move(model), U"");
	}

	void CModel::release(const Model::IDType handleID)
	{
		m_models.erase(handleID);
	}

	const Array<ModelObject>& CModel::getObjects(const Model::IDType handleID)
	{
		return m_models[handleID]->getObjects();
	}

	const Array<Material>& CModel::getMaterials(const Model::IDType handleID)
	{
		return m_models[handleID]->getMaterials();
	}

	const Sphere& CModel::getBoundingSphere(const Model::IDType handleID)
	{
		return m_models[handleID]->getBoundingSphere();
	}
	
	const Box& CModel::getBoundingBox(const Model::IDType handleID)
	{
		return m_models[handleID]->getBoundingBox();
	}
}
