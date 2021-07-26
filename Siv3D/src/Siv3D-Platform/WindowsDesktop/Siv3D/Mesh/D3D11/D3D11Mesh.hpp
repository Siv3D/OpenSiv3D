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
# include <Siv3D/Common.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/Vertex3D.hpp>
# include <Siv3D/TriangleIndex.hpp>
# include <Siv3D/MeshData.hpp>
# include <Siv3D/Common/D3D11.hpp>

namespace s3d
{
	class D3D11Mesh
	{
	public:

		SIV3D_NODISCARD_CXX20
		explicit D3D11Mesh(ID3D11Device* device, const MeshData& meshData);

		SIV3D_NODISCARD_CXX20
		D3D11Mesh(ID3D11Device* device, const Array<Vertex3D>& vertices, const Array<TriangleIndex32>& indices);

		[[nodiscard]]
		bool isInitialized() const noexcept;

		[[nodiscard]]
		ID3D11Buffer* getVertexBuffer();

		[[nodiscard]]
		ID3D11Buffer* getIndexBuffer();

		[[nodiscard]]
		uint32 getVertexCount() const noexcept;

		[[nodiscard]]
		uint32 getIndexCount() const noexcept;

		[[nodiscard]]
		const Sphere& getBoundingSphere() const noexcept;

		[[nodiscard]]
		const Box& getBoundingBox() const noexcept;

		void bindToContext(ID3D11DeviceContext* context);

	private:

		ComPtr<ID3D11Buffer> m_vertexBuffer;

		ComPtr<ID3D11Buffer> m_indexBuffer;

		uint32 m_vertexCount = 0;

		uint32 m_indexCount = 0;

		uint32 m_vertexStride = 0;

		Sphere m_boundingSphere{ 0.0 };

		Box m_boundingBox{ 0.0 };

		bool m_initialized = false;
	};
}
