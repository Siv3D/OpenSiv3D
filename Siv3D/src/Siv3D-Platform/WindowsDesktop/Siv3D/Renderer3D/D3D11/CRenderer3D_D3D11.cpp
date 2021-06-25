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

# include "CRenderer3D_D3D11.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/Resource.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/ScopeGuard.hpp>
# include <Siv3D/ShaderCommon.hpp>
# include <Siv3D/Vertex3D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Renderer/D3D11/CRenderer_D3D11.hpp>
# include <Siv3D/Shader/D3D11/CShader_D3D11.hpp>
# include <Siv3D/Texture/D3D11/CTexture_D3D11.hpp>



# include <Siv3D/Cylindrical.hpp>
# include <Siv3D/Periodic.hpp>

//*
#	define LOG_COMMAND(...) LOG_TRACE(__VA_ARGS__)
/*/
#	define LOG_COMMAND(...) ((void)0)
//*/

namespace s3d
{
	class alignas(16) BasicCamera3D
	{
	public:

		static constexpr double DefaultNearClip = 0.1;

		BasicCamera3D() = default;

		BasicCamera3D(const BasicCamera3D&) = default;

		BasicCamera3D& operator=(const BasicCamera3D&) = default;

		BasicCamera3D(BasicCamera3D&&) = default;

		BasicCamera3D& operator=(BasicCamera3D&&) = default;

		BasicCamera3D(const Size& sceneSize, double verticalFOV, const Vec3& eyePosition, const Vec3& focusPosition, const Vec3& upDirection = Vec3{ 0, 1, 0 }, double nearClip = DefaultNearClip) noexcept
			: m_sceneSize{ sceneSize }
			, m_verticalFOV{ verticalFOV }
			, m_nearClip{ nearClip }
			, m_eyePosition{ eyePosition }
			, m_focusPosition{ focusPosition }
			, m_upDirection{ upDirection }
		{
			updateProj();
			updateView();
			updateViewProj();
		}

		virtual ~BasicCamera3D() = default;

		void setSceneSize(const Size& sceneSize)
		{
			m_sceneSize = sceneSize;

			updateProj();
			updateViewProj();
		}

		void setProjection(const Size& sceneSize, double verticalFOV, double nearClip = DefaultNearClip) noexcept
		{
			m_sceneSize = sceneSize;
			m_verticalFOV = verticalFOV;
			m_nearClip = nearClip;

			updateProj();
			updateViewProj();
		}

		void setView(const Vec3& eyePosition, const Vec3& focusPosition, const Vec3& upDirection = Vec3{ 0, 1, 0 }) noexcept
		{
			m_eyePosition = eyePosition;
			m_focusPosition = focusPosition;
			m_upDirection = upDirection;

			updateView();
			updateViewProj();
		}

		[[nodiscard]]
		const Size& getSceneSize() const noexcept
		{
			return m_sceneSize;
		}

		[[nodiscard]]
		double getVerticlaFOV() const noexcept
		{
			return m_verticalFOV;
		}

		[[nodiscard]]
		double getNearClip() const noexcept
		{
			return m_nearClip;
		}

		[[nodiscard]]
		const Vec3& getEyePosition() const noexcept
		{
			return m_eyePosition;
		}

		[[nodiscard]]
		const Vec3& getFocusPosition() const noexcept
		{
			return m_focusPosition;
		}

		[[nodiscard]]
		const Vec3& getUpDirection() const noexcept
		{
			return m_upDirection;
		}

		[[nodiscard]]
		const Mat4x4& SIV3D_VECTOR_CALL getProj() const noexcept
		{
			return m_proj;
		}

		[[nodiscard]]
		const Mat4x4& SIV3D_VECTOR_CALL getView() const noexcept
		{
			return m_view;
		}

		[[nodiscard]]
		const Mat4x4& SIV3D_VECTOR_CALL getViewProj() const noexcept
		{
			return m_viewProj;
		}

		[[nodiscard]]
		const Mat4x4& SIV3D_VECTOR_CALL getMat4x4() const noexcept
		{
			return m_viewProj;
		}

		[[nodiscard]]
		const Mat4x4& SIV3D_VECTOR_CALL getInvViewProj() const noexcept
		{
			return m_invViewProj;
		}

		[[nodiscard]]
		Float3 worldToScreenPoint(const Float3& pos) const noexcept
		{
			Float3 v = SIMD_Float4{ DirectX::XMVector3TransformCoord(SIMD_Float4{ pos, 0.0f }, m_viewProj) }.xyz();
			v.x += 1.0f;
			v.y += 1.0f;
			v.x *= 0.5f * m_sceneSize.x;
			v.y *= 0.5f;
			v.y = 1.0f - v.y;
			v.y *= m_sceneSize.y;
			return v;
		}

		[[nodiscard]]
		Float3 screenToWorldPoint(const Float2& pos, float depth) const noexcept;

		//[[nodiscard]]
		//Ray screenToRay(const Vec2& pos) const noexcept;

	protected:

		Mat4x4 m_proj = Mat4x4::Identity();

		Mat4x4 m_view = Mat4x4::Identity();

		Mat4x4 m_viewProj = Mat4x4::Identity();

		Mat4x4 m_invViewProj = Mat4x4::Identity();

		//
		// Proj
		//
		Size m_sceneSize = Scene::Size();

		double m_verticalFOV = 30_deg;

		double m_nearClip = DefaultNearClip;

		//
		// View
		//
		Vec3 m_eyePosition = Vec3{ 0, 4, -4 };

		Vec3 m_focusPosition = Vec3{ 0, 0, 0 };

		Vec3 m_upDirection = Vec3{ 0, 1, 0 };

		void updateProj() noexcept
		{
			const double g = (1.0 / std::tan(m_verticalFOV * 0.5));
			const double s = (static_cast<double>(m_sceneSize.x) / m_sceneSize.y);
			constexpr float e = 0.000001f;

			m_proj = Mat4x4{
				static_cast<float>(g / s), 0.0f, 0.0f, 0.0f,
				0.0f, static_cast<float>(g), 0.0f, 0.0f,
				0.0f, 0.0f, e, 1.0f,
				0.0f, 0.0f, static_cast<float>(m_nearClip * (1.0 - e)), 0.0f
			};
		}

		void updateView() noexcept
		{
			const SIMD_Float4 eyePosition{ m_eyePosition, 0.0f };
			const SIMD_Float4 focusPosition{ m_focusPosition, 0.0f };
			const SIMD_Float4 upDirection{ m_upDirection, 0.0f };
			m_view = DirectX::XMMatrixLookAtLH(eyePosition, focusPosition, upDirection);
		}

		void updateViewProj() noexcept
		{
			m_viewProj = (m_view * m_proj);
			m_invViewProj = m_viewProj.inverse();
		}
	};


	CRenderer3D_D3D11::CRenderer3D_D3D11() {}

	CRenderer3D_D3D11::~CRenderer3D_D3D11()
	{
		LOG_SCOPED_TRACE(U"CRenderer3D_D3D11::~CRenderer3D_D3D11()");
	}

	void CRenderer3D_D3D11::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer3D_D3D11::init()");
		
		// 各種ポインタを保存
		{
			pRenderer	= dynamic_cast<CRenderer_D3D11*>(SIV3D_ENGINE(Renderer)); assert(pRenderer);
			pShader		= dynamic_cast<CShader_D3D11*>(SIV3D_ENGINE(Shader)); assert(pShader);
			pTexture	= dynamic_cast<CTexture_D3D11*>(SIV3D_ENGINE(Texture)); assert(pTexture);
			m_device	= pRenderer->getDevice(); assert(m_device);
			m_context	= pRenderer->getContext(); assert(m_context);
		}

		// 標準 VS をロード
		{
			LOG_INFO(U"📦 Loading vertex shaders for CRenderer3D_D3D11:");
			m_standardVS = std::make_unique<D3D11StandardVS3D>();
			m_standardVS->forward = HLSL{ U"engine/shader/d3d11/forward3d.hlsl", U"VS" };
			
			if (not m_standardVS->setup())
			{
				throw EngineError{ U"CRenderer3D_D3D11::m_standardVS initialization failed" };
			}
		}

		// 標準 PS をロード
		{
			LOG_INFO(U"📦 Loading pixel shaders for CRenderer3D_D3D11:");
			m_standardPS = std::make_unique<D3D11StandardPS3D>();
			m_standardPS->forward = HLSL{ U"engine/shader/d3d11/forward3d.hlsl", U"PS" };
			
			if (not m_standardPS->setup())
			{
				throw EngineError{ U"CRenderer3D_D3D11::m_standardPS initialization failed" };
			}
		}

		// 標準 InputLayout を作成
		{
			const D3D11_INPUT_ELEMENT_DESC layout[4] = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "NORMAL"  , 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TANGENT" , 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};

			const Blob& binary = m_standardVS->forward.getBinary();
			if (FAILED(m_device->CreateInputLayout(layout, static_cast<UINT>(std::size(layout)), binary.data(), binary.size(), &m_inputLayout)))
			{
				throw EngineError{ U"ID3D11Device::CreateInputLayout() failed" };
			}
		}

		// テスト用描画データ
		{
			// Vertex Buffer
			{
				const D3D11_BUFFER_DESC desc =
				{
					.ByteWidth				= (sizeof(Vertex3D) * TestBuffer::VertexBufferSize),
					.Usage					= D3D11_USAGE_DYNAMIC,
					.BindFlags				= D3D11_BIND_VERTEX_BUFFER,
					.CPUAccessFlags			= D3D11_CPU_ACCESS_WRITE,
					.MiscFlags				= 0,
					.StructureByteStride	= 0, 
				};

				if (FAILED(m_device->CreateBuffer(&desc, nullptr, &m_testBuffer.vertexBuffer)))
				{
					throw EngineError{ U"ID3D11Device::CreateBuffer() failed" };
				}
			}

			// Index Buffer
			{
				const D3D11_BUFFER_DESC desc =
				{
					.ByteWidth				= (sizeof(Vertex3D::IndexType) * TestBuffer::IndexBufferSize),
					.Usage					= D3D11_USAGE_DYNAMIC,
					.BindFlags				= D3D11_BIND_INDEX_BUFFER,
					.CPUAccessFlags			= D3D11_CPU_ACCESS_WRITE,
					.MiscFlags				= 0,
					.StructureByteStride	= 0,
				};

				if (FAILED(m_device->CreateBuffer(&desc, nullptr, &m_testBuffer.indexBuffer)))
				{
					throw EngineError{ U"ID3D11Device::CreateBuffer() failed" };
				}
			}

			// Update VB
			{
				D3D11_MAP mapType = D3D11_MAP_WRITE_DISCARD;
				D3D11_MAPPED_SUBRESOURCE res;

				if (SUCCEEDED(m_context->Map(m_testBuffer.vertexBuffer.Get(), 0, mapType, 0, &res)))
				{
					if (Vertex3D* const p = static_cast<Vertex3D*>(res.pData))
					{
						p[0] = Vertex3D{ .pos = { -10.0f, 0.0f,  10.0f }, .normal = { 0.0f, 1.0f, 0.0f }, .tangent = Float4{ 0, 0, 0, 0}, .tex = { 0.0f, 0.0f } };
						p[1] = Vertex3D{ .pos = {  10.0f, 0.0f,  10.0f }, .normal = { 0.0f, 1.0f, 0.0f }, .tangent = Float4{ 0, 0, 0, 0}, .tex = { 1.0f, 0.0f } };
						p[2] = Vertex3D{ .pos = { -10.0f, 0.0f, -10.0f }, .normal = { 0.0f, 1.0f, 0.0f }, .tangent = Float4{ 0, 0, 0, 0}, .tex = { 0.0f, 1.0f } };
					}
					m_context->Unmap(m_testBuffer.vertexBuffer.Get(), 0);
				}
			}

			// Update IB
			{
				D3D11_MAP mapType = D3D11_MAP_WRITE_DISCARD;
				D3D11_MAPPED_SUBRESOURCE res;

				if (SUCCEEDED(m_context->Map(m_testBuffer.indexBuffer.Get(), 0, mapType, 0, &res)))
				{
					if (Vertex3D::IndexType* const p = static_cast<Vertex3D::IndexType*>(res.pData))
					{
						p[0] = 0;
						p[1] = 1;
						p[2] = 2;
					}
					m_context->Unmap(m_testBuffer.indexBuffer.Get(), 0);
				}
			}
		}
	}


	void CRenderer3D_D3D11::flush()
	{
		ScopeGuard cleanUp = [this]()
		{
			m_commandManager.reset();
		};

		m_commandManager.flush();

		m_context->IASetInputLayout(m_inputLayout.Get());
		pShader->setConstantBufferVS(0, m_vsConstants3D.base());
		pShader->setConstantBufferPS(0, m_psConstants3D.base());

		// [Siv3D ToDo: remove]
		pShader->setVS(m_standardVS->forwardID);
		pShader->setPS(m_standardPS->forwardID);

		const Size currentRenderTargetSize = SIV3D_ENGINE(Renderer)->getSceneBufferSize();

		{
			const CD3D11_VIEWPORT viewport{
				0.0f, 0.0f,
				static_cast<float>(currentRenderTargetSize.x), static_cast<float>(currentRenderTargetSize.y) };
			m_context->RSSetViewports(1, &viewport);
		}

		//Mat3x2 transform = Mat3x2::Identity();
		//Mat3x2 screenMat = Mat3x2::Screen(currentRenderTargetSize);

		pRenderer->getBackBuffer().setRenderTargetToScene();

		LOG_COMMAND(U"----");

		{
			ID3D11Buffer* const pBuf[1] = { m_testBuffer.vertexBuffer.Get() };
			const UINT stride = sizeof(Vertex3D);
			const UINT offset = 0;
			m_context->IASetVertexBuffers(0, 1, pBuf, &stride, &offset);

			constexpr auto indexFormat = ((sizeof(Vertex3D::IndexType) == 2) ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT);
			m_context->IASetIndexBuffer(m_testBuffer.indexBuffer.Get(), indexFormat, 0);
		}

		for (const auto& command : m_commandManager.getCommands())
		{
			switch (command.type)
			{
			case D3D11Renderer3DCommandType::Null:
				{
					LOG_COMMAND(U"Null");
					break;
				}
			case D3D11Renderer3DCommandType::BlendState:
				{
					const auto& blendState = m_commandManager.getBlendState(command.index);
					pRenderer->getBlendState().set(blendState);
					LOG_COMMAND(U"BlendState[{}]"_fmt(command.index));
					break;
				}
			case D3D11Renderer3DCommandType::RasterizerState:
				{
					const auto& rasterizerState = m_commandManager.getRasterizerState(command.index);
					pRenderer->getRasterizerState().set(rasterizerState);
					LOG_COMMAND(U"RasterizerState[{}]"_fmt(command.index));
					break;
				}
			case D3D11Renderer3DCommandType::SetRT:
				{
					const auto& rt = m_commandManager.getRT(command.index);
					
					if (rt)
					{
						ID3D11RenderTargetView* const rtv = pTexture->getRTV(rt->id());
						pRenderer->getBackBuffer().setRenderTarget(rtv);

						LOG_COMMAND(U"SetRT[{}] (texture {})"_fmt(command.index, rt->id().value()));
					}
					else
					{
						pRenderer->getBackBuffer().setRenderTargetToScene();
						
						LOG_COMMAND(U"SetRT[{}] (default scene)"_fmt(command.index));
					}

					break;
				}
			}
		}

		// test draw
		{
			constexpr double verticlaFOV = 30_deg;
			constexpr Vec3 focusPosition(0, 0, 0);
			Vec3 eyePosition(0, 10, 0);
			BasicCamera3D camera{ Scene::Size(), verticlaFOV, eyePosition, focusPosition };
			eyePosition = Cylindrical{ 20, Scene::Time() * 30_deg, 8 + Periodic::Sine0_1(SecondsF{4}) * 8 };
			camera.setView(eyePosition, focusPosition);
			camera.setSceneSize(Scene::Size());
			m_vsConstants3D->viewProjectionMatrix = camera.getViewProj();

			m_vsConstants3D._update_if_dirty();
			m_psConstants3D._update_if_dirty();
			m_context->DrawIndexed(3, 0, 0);
		}
	}
}
