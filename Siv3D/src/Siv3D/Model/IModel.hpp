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
# include <Siv3D/Model.hpp>

namespace s3d
{
	class SIV3D_NOVTABLE ISiv3DModel
	{
	public:

		static ISiv3DModel* Create();

		virtual ~ISiv3DModel() = default;

		virtual void init() = 0;

		virtual Model::IDType create(FilePathView path, ColorOption colorOption) = 0;

		virtual void release(Model::IDType handleID) = 0;

		virtual const Array<ModelObject>& getObjects(Model::IDType handleID) = 0;

		virtual const Array<Material>& getMaterials(Model::IDType handleID) = 0;

		virtual const Sphere& getBoundingSphere(Model::IDType handleID) = 0;

		virtual const Box& getBoundingBox(Model::IDType handleID) = 0;
	};
}
