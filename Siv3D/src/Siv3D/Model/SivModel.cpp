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

# include <Siv3D/Model.hpp>
# include <Siv3D/Model/IModel.hpp>
# include <Siv3D/AssetMonitor/IAssetMonitor.hpp>
# include <Siv3D/Renderer3D/IRenderer3D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/FreestandingMessageBox/FreestandingMessageBox.hpp>

namespace s3d
{
	template <>
	AssetIDWrapper<AssetHandle<Model>>::AssetIDWrapper()
	{
		if (not Siv3DEngine::isActive())
		{
			FreestandingMessageBox::ShowError(U"`Model` must be initialized after engine-setup. Please fix the C++ code.");
			std::abort();
		}
	}

	template <>
	AssetIDWrapper<AssetHandle<Model>>::~AssetIDWrapper()
	{
		if (not Siv3DEngine::isActive())
		{
			return;
		}

		if (auto p = SIV3D_ENGINE(Model))
		{
			p->release(m_id);
		}
	}

	Model::Model() {}

	Model::Model(const FilePathView path)
		: AssetHandle{ std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Model)->create(path)) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Model::~Model() {}

	const Array<ModelObject>& Model::objects() const noexcept
	{
		return SIV3D_ENGINE(Model)->getObjects(m_handle->id());
	}

	const Array<Material>& Model::materials() const noexcept
	{
		return SIV3D_ENGINE(Model)->getMaterials(m_handle->id());
	}

	void Model::swap(Model& other) noexcept
	{
		m_handle.swap(other.m_handle);
	}
}
