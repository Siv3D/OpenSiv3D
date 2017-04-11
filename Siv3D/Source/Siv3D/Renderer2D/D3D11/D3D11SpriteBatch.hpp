//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include <wrl.h>
using namespace Microsoft::WRL;
# include <d3d11.h>
# include <d3dcompiler.h>
# include "../IRenderer2D.hpp"

# include <Siv3D/Array.hpp>
# include <Siv3D/PointVector.hpp>

namespace s3d
{
	using IndexType = uint32;

	/// <summary>
	/// スプライトの頂点データ
	/// </summary>
	struct SpriteVertex
	{
		/// <summary>
		/// 位置
		/// </summary>
		Float2 pos;

		/// <summary>
		/// UV 座標
		/// </summary>
		Float2 tex;

		/// <summary>
		/// 色
		/// </summary>
		Float4 color;
	};

	class D3D11SpriteBatch
	{
	private:

		ID3D11Device* m_device = nullptr;

		ID3D11DeviceContext* m_context = nullptr;

		ComPtr<ID3D11Buffer> m_vertexBuffer;

		ComPtr<ID3D11Buffer> m_indexBuffer;

		Array<SpriteVertex> m_vertices;

		Array<IndexType> m_indices;

		uint32 m_indexBufferWritePos = 0;

		uint32 m_vertexBufferWritePos = 0;

		uint32 m_vertexPos = 0;

		uint32 m_indexPos = 0;


		// 仮の値
		static constexpr uint32 MaxVertexSize	= 65536;
		static constexpr uint32 MaxIndexSize	= 65536 * 8;

		static constexpr uint32 VertexBufferSize	= 65536;
		static constexpr uint32 IndexBufferSize		= 65536 * 8;

	public:

		D3D11SpriteBatch()
			: m_vertices(MaxVertexSize)
			, m_indices(MaxIndexSize)
		{

		}

		bool init(ID3D11Device* const device, ID3D11DeviceContext* const context)
		{
			m_device = device;
			m_context = context;

			{
				D3D11_BUFFER_DESC desc;
				desc.ByteWidth				= sizeof(SpriteVertex) * VertexBufferSize;
				desc.Usage					= D3D11_USAGE_DYNAMIC;
				desc.BindFlags				= D3D11_BIND_VERTEX_BUFFER;
				desc.CPUAccessFlags			= D3D11_CPU_ACCESS_WRITE;
				desc.MiscFlags				= 0;
				desc.StructureByteStride	= 0;

				if (FAILED(m_device->CreateBuffer(&desc, nullptr, &m_vertexBuffer)))
				{
					return false;
				}
			}

			{
				D3D11_BUFFER_DESC desc;
				desc.ByteWidth				= sizeof(IndexType) * IndexBufferSize;
				desc.Usage					= D3D11_USAGE_DYNAMIC;
				desc.BindFlags				= D3D11_BIND_INDEX_BUFFER;
				desc.CPUAccessFlags			= D3D11_CPU_ACCESS_WRITE;
				desc.MiscFlags				= 0;
				desc.StructureByteStride	= 0;

				if (FAILED(m_device->CreateBuffer(&desc, nullptr, &m_indexBuffer)))
				{
					return false;
				}
			}

			return true;
		}

		void setBuffers()
		{
			ID3D11Buffer* const pBuf[3] = { m_vertexBuffer.Get(), nullptr, nullptr };

			const UINT stride[3] = { sizeof(SpriteVertex), 0, 0 };

			const UINT offset[3] = { 0, 0, 0 };

			m_context->IASetVertexBuffers(0, 3, pBuf, stride, offset);

			m_context->IASetIndexBuffer(m_indexBuffer.Get(), sizeof(IndexType) == 2 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT, 0);
		}

		void clear()
		{
			m_vertexPos = 0;

			m_indexPos = 0;
		}
	};
}

# endif
