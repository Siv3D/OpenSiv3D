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
# include <Siv3D/StringView.hpp>
# include <Siv3D/ModelObject.hpp>
# include <Siv3D/Material.hpp>
# include <Siv3D/ColorOption.hpp>

namespace s3d
{
	class ModelData
	{
	public:

		SIV3D_NODISCARD_CXX20
		explicit ModelData();

		SIV3D_NODISCARD_CXX20
		ModelData(FilePathView path, ColorOption colorOption);

		~ModelData();

		[[nodiscard]]
		bool isInitialized() const noexcept;

		[[nodiscard]]
		const Array<ModelObject>& getObjects() const noexcept;

		[[nodiscard]]
		const Array<Material>& getMaterials() const noexcept;

		[[nodiscard]]
		const Sphere& getBoundingSphere() const noexcept;

		[[nodiscard]]
		const Box& getBoundingBox() const noexcept;

	private:

		Array<ModelObject> m_objects;

		Array<Material> m_materials;

		Sphere m_boundingSphere{ 0.0 };

		Box m_boundingBox{ 0.0 };

		bool m_initialized = false;
	};
}
