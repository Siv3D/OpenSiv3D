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

# include "CRenderer3D_Null.hpp"
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	CRenderer3D_Null::CRenderer3D_Null() {}

	CRenderer3D_Null::~CRenderer3D_Null()
	{
		LOG_SCOPED_TRACE(U"CRenderer3D_Null::~CRenderer3D_Null()");
	}

	void CRenderer3D_Null::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer3D_Null::init()");
	}

	const Renderer3DStat& CRenderer3D_Null::getStat() const
	{
		return m_stat;
	}

	void CRenderer3D_Null::addMesh(const Mesh&, const Mat4x4&, const Float4&) {}

	void CRenderer3D_Null::addTexturedMesh(const Mesh&, const Texture&, const Mat4x4&, const Float4&) {}

	BlendState CRenderer3D_Null::getBlendState() const
	{
		return BlendState::Default;
	}

	RasterizerState CRenderer3D_Null::getRasterizerState() const
	{
		return RasterizerState::Default3D;
	}

	DepthStencilState CRenderer3D_Null::getDepthStencilState() const
	{
		return DepthStencilState::Default3D;
	}

	SamplerState CRenderer3D_Null::getSamplerState(ShaderStage, uint32) const
	{
		return SamplerState::Default3D;
	}

	void CRenderer3D_Null::setBlendState(const BlendState&) {}

	void CRenderer3D_Null::setRasterizerState(const RasterizerState&) {}

	void CRenderer3D_Null::setDepthStencilState(const DepthStencilState&) {}

	void CRenderer3D_Null::setSamplerState(ShaderStage, uint32, const SamplerState&) {}

	void CRenderer3D_Null::setScissorRect(const Rect&) {}

	Rect CRenderer3D_Null::getScissorRect() const
	{
		return Rect{ 0 };
	}

	void CRenderer3D_Null::setViewport(const Optional<Rect>&) {}

	Optional<Rect> CRenderer3D_Null::getViewport() const
	{
		return none;
	}

	Optional<VertexShader> CRenderer3D_Null::getCustomVS() const
	{
		return none;
	}

	Optional<PixelShader> CRenderer3D_Null::getCustomPS() const
	{
		return none;
	}

	void CRenderer3D_Null::setCustomVS(const Optional<VertexShader>&) {}

	void CRenderer3D_Null::setCustomPS(const Optional<PixelShader>&) {}

	const Mat4x4& CRenderer3D_Null::getCameraTransform() const
	{
		static const Mat4x4 m = Mat4x4::Identity();
		return m;
	}

	void CRenderer3D_Null::setCameraTransform(const Mat4x4&) {}

	void CRenderer3D_Null::setVSTexture(uint32, const Optional<Texture>&) {}
	
	void CRenderer3D_Null::setPSTexture(uint32, const Optional<Texture>&) {}

	void CRenderer3D_Null::setRenderTarget(const Optional<RenderTexture>&) {}

	Optional<RenderTexture> CRenderer3D_Null::getRenderTarget() const
	{
		return none;
	}

	void CRenderer3D_Null::setConstantBuffer(ShaderStage, uint32, const ConstantBufferBase&, const float*, uint32) {}

	void CRenderer3D_Null::flush() {}
}
