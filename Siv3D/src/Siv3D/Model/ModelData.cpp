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

# include "ModelData.hpp"
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/MeshData.hpp>
# include <Siv3D/Geometry3D.hpp>
# include <Siv3D/SIMDCollision.hpp>
# include <Siv3D/EngineLog.hpp>
# include <ThirdParty/tinyobjloader/tiny_obj_loader.h>

namespace s3d
{
	ModelData::ModelData()
	{
		// [Siv3D ToDo]

		m_initialized = true;
	}

	ModelData::ModelData(const FilePathView path, const ColorOption colorOption)
	{
		tinyobj::ObjReaderConfig reader_config;
		{
			reader_config.vertex_color = false;
			reader_config.mtl_search_path = FileSystem::ParentPath(path).narrow();
		}

		tinyobj::ObjReader reader;
		{
			if (not reader.ParseFromFile(path.narrow(), reader_config))
			{
				if (not reader.Error().empty())
				{
					LOG_FAIL(U"TinyObjReader: " + Unicode::Widen(reader.Error()));

					return;
				}
			}

			if (not reader.Warning().empty())
			{
				LOG_WARNING(U"TinyObjReader: " + Unicode::Widen(reader.Warning()));
			}
		}

		{
			const auto& materials = reader.GetMaterials();
			m_materials.reserve(materials.size());

			for (const auto& m : materials)
			{
				Material mtl;
				mtl.name = Unicode::Widen(m.name);
				mtl.ambient.set(m.ambient[0], m.ambient[1], m.ambient[2]);
				mtl.diffuse.set(m.diffuse[0], m.diffuse[1], m.diffuse[2]);
				mtl.specular.set(m.specular[0], m.specular[1], m.specular[2]);
				mtl.transmittance.set(m.transmittance[0], m.transmittance[1], m.transmittance[2]);
				mtl.emission.set(m.emission[0], m.emission[1], m.emission[2]);
				mtl.shininess = m.shininess;
				mtl.ior = m.ior;
				mtl.dissolve = m.dissolve;
				mtl.illum = m.illum;

				if (colorOption == ColorOption::ApplySRGBCurve)
				{
					mtl.ambient = mtl.ambient.applySRGBCurve();
					mtl.diffuse = mtl.diffuse.applySRGBCurve();
					mtl.specular = mtl.specular.applySRGBCurve();
					mtl.emission = mtl.emission.applySRGBCurve();
				}

				if (not m.ambient_texname.empty())
				{
					mtl.ambientTextureName = Unicode::FromUTF8(reader_config.mtl_search_path + m.ambient_texname);
				}

				if (not m.diffuse_texname.empty())
				{
					mtl.diffuseTextureName = Unicode::FromUTF8(reader_config.mtl_search_path + m.diffuse_texname);
				}

				if (not m.specular_texname.empty())
				{
					mtl.specularTextureName = Unicode::FromUTF8(reader_config.mtl_search_path + m.specular_texname);
				}

				if (not m.normal_texname.empty())
				{
					mtl.normalTextureName = Unicode::FromUTF8(reader_config.mtl_search_path + m.normal_texname);
				}

				m_materials << mtl;
			}
		}

		{
			const auto& attrib = reader.GetAttrib();
			const auto& shapes = reader.GetShapes();
			m_objects.resize(shapes.size());

			for (size_t s = 0; s < shapes.size(); ++s)
			{
				const auto& shape = shapes[s];
				m_objects[s].name = Unicode::FromUTF8(shape.name);

				Array<MeshData> objMeshes(m_materials.size());
				MeshData noMaterialObjMesh;
				Vertex3D::IndexType index_offset = 0;

				for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); ++f)
				{
					const Vertex3D::IndexType fv = Vertex3D::IndexType(shape.mesh.num_face_vertices[f]);

					Vertex3D vertices[3];

					// Loop over vertices in the face.
					for (Vertex3D::IndexType v = 0; v < fv; v++)
					{
						auto& vertex = vertices[v];

						// access to vertex
						const tinyobj::index_t idx = shape.mesh.indices[index_offset + v];
						const tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
						const tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
						const tinyobj::real_t vz = -attrib.vertices[3 * size_t(idx.vertex_index) + 2];

						vertex.pos.set(vx, vy, vz);

						// Check if `normal_index` is zero or positive. negative = no normal data
						if (idx.normal_index >= 0)
						{
							const tinyobj::real_t nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
							const tinyobj::real_t ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
							const tinyobj::real_t nz = -attrib.normals[3 * size_t(idx.normal_index) + 2];

							vertex.normal.set(nx, ny, nz);
						}
						else
						{
							vertex.normal.set(0.0f, 0.0f, 0.0f);
						}

						// Check if `texcoord_index` is zero or positive. negative = no texcoord data
						if (idx.texcoord_index >= 0)
						{
							const tinyobj::real_t tx = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
							const tinyobj::real_t ty = (1.0f - attrib.texcoords[2 * size_t(idx.texcoord_index) + 1]);

							vertex.tex.set(tx, ty);
						}
						else
						{
							vertex.tex.set(0.0f, 0.0f);
						}
					}

					// per-face material
					if (const int32 materialID = shape.mesh.material_ids[f];
						0 <= materialID)
					{
						auto& meshData = objMeshes[materialID];
						const Vertex3D::IndexType baseIndex = static_cast<Vertex3D::IndexType>(meshData.vertices.size());
						meshData.vertices.insert(meshData.vertices.end(), std::begin(vertices), std::end(vertices));
						meshData.indices.insert(meshData.indices.end(), { baseIndex, baseIndex + 2, baseIndex + 1 });
					}
					else
					{
						auto& meshData = noMaterialObjMesh;
						const Vertex3D::IndexType baseIndex = static_cast<Vertex3D::IndexType>(meshData.vertices.size());
						meshData.vertices.insert(meshData.vertices.end(), std::begin(vertices), std::end(vertices));
						meshData.indices.insert(meshData.indices.end(), { baseIndex, baseIndex + 1, baseIndex + 2 });
					}

					index_offset += fv;
				}

				for (size_t materialID = 0; materialID < m_materials.size(); ++materialID)
				{
					auto& meshData = objMeshes[materialID];

					if (meshData.vertices)
					{
						if (meshData.vertices.any([](const Vertex3D& v) { return v.normal.isZero(); }))
						{
							meshData.computeNormals();
						}

						ModelMeshPart part
						{
							.mesh = Mesh{ meshData },
							.materialID = materialID,
						};

						m_objects[s].parts.push_back(std::move(part));
					}
				}

				{
					if (noMaterialObjMesh.vertices)
					{
						if (noMaterialObjMesh.vertices.any([](const Vertex3D& v) { return v.normal.isZero(); }))
						{
							noMaterialObjMesh.computeNormals();
						}

						ModelMeshPart part
						{
							.mesh = Mesh{ noMaterialObjMesh },
							.materialID = none,
						};

						m_objects[s].parts.push_back(std::move(part));
					}
				}
			}
		}

		// bounding spheres & boxes (per object)
		for (auto& object : m_objects)
		{
			if (object.parts)
			{
				DirectX::BoundingSphere sphere = 
					detail::FromSphere(object.parts[0].mesh.boundingSphere());
				DirectX::BoundingBox box =
					detail::FromBox(object.parts[0].mesh.boundingBox());

				for (size_t i = 1; i < object.parts.size(); ++i)
				{
					const auto& mesh = object.parts[i].mesh;
					const DirectX::BoundingSphere currentSphere = detail::FromSphere(mesh.boundingSphere());	
					const DirectX::BoundingBox currentBox = detail::FromBox(mesh.boundingBox());

					DirectX::BoundingSphere::CreateMerged(sphere, sphere, currentSphere);
					DirectX::BoundingBox::CreateMerged(box, box, currentBox);
				}

				object.boundingSphere = detail::ToSphere(sphere);
				object.boundingBox = detail::ToBox(box);
			}
		}

		// bounding spheres & boxes (model)
		{
			if (m_objects)
			{
				DirectX::BoundingSphere sphere =
					detail::FromSphere(m_objects[0].boundingSphere);
				DirectX::BoundingBox box =
					detail::FromBox(m_objects[0].boundingBox);

				for (size_t i = 1; i < m_objects.size(); ++i)
				{
					const auto& object = m_objects[i];
					const DirectX::BoundingSphere currentSphere = detail::FromSphere(object.boundingSphere);
					const DirectX::BoundingBox currentBox = detail::FromBox(object.boundingBox);

					DirectX::BoundingSphere::CreateMerged(sphere, sphere, currentSphere);
					DirectX::BoundingBox::CreateMerged(box, box, currentBox);
				}

				m_boundingSphere = detail::ToSphere(sphere);
				m_boundingBox = detail::ToBox(box);
			}
		}

		m_initialized = true;
	}

	ModelData::~ModelData()
	{

	}

	bool ModelData::isInitialized() const noexcept
	{
		return m_initialized;
	}

	const Array<ModelObject>& ModelData::getObjects() const noexcept
	{
		return m_objects;
	}

	const Array<Material>& ModelData::getMaterials() const noexcept
	{
		return m_materials;
	}

	const Sphere& ModelData::getBoundingSphere() const noexcept
	{
		return m_boundingSphere;
	}

	const Box& ModelData::getBoundingBox() const noexcept
	{
		return m_boundingBox;
	}
}
