//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Model.hpp>
# include <Siv3D/TextureAsset.hpp>
# include <Siv3D/Transformer3D.hpp>
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

	Model::Model(const FilePathView path, const ColorOption colorOption)
		: AssetHandle{ std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Model)->create(path, colorOption)) }
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

	Array<String> Model::diffuseTextureNames() const
	{
		Array<String> results;

		for (const auto& material : materials())
		{
			if (const auto& textureName = material.diffuseTextureName)
			{
				results.push_back(textureName);
			}
		}

		return results.sorted_and_uniqued();
	}

	const Sphere& Model::boundingSphere() const noexcept
	{
		return SIV3D_ENGINE(Model)->getBoundingSphere(m_handle->id());
	}

	const Box& Model::boundingBox() const noexcept
	{
		return SIV3D_ENGINE(Model)->getBoundingBox(m_handle->id());
	}

	void Model::draw() const
	{
		const auto& _materials = materials();

		for (const auto& object : objects())
		{
			object.draw(_materials);
		}
	}

	void Model::draw(const double x, const double y, const double z) const
	{
		draw(Mat4x4::Translate(x, y, z));
	}

	void Model::draw(const Vec3& pos) const
	{
		draw(Mat4x4::Translate(pos));
	}

	void Model::draw(const double x, const double y, const double z, const Quaternion& rotation) const
	{
		draw(Mat4x4::Rotate(rotation).translated(x, y, z));
	}

	void Model::draw(const Vec3& pos, const Quaternion& rotation) const
	{
		draw(Mat4x4::Rotate(rotation).translated(pos));
	}

	void Model::draw(const Mat4x4& mat) const
	{
		const Transformer3D t{ mat };

		const auto& _materials = materials();

		for (const auto& object : objects())
		{
			object.draw(_materials);
		}
	}

	void Model::swap(Model& other) noexcept
	{
		m_handle.swap(other.m_handle);
	}

	bool Model::RegisterDiffuseTextures(const Model& model, const TextureDesc textureDesc)
	{
		bool result = true;

		for (const auto& textureName : model.diffuseTextureNames())
		{
			if (not TextureAsset::IsRegistered(textureName))
			{
				result &= TextureAsset::Register(textureName, textureName, textureDesc);
			}
		}

		return result;
	}
}
