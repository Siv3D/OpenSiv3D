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
# include <Siv3D/VertexShader.hpp>
# include <Siv3D/PixelShader.hpp>
# include <Siv3D/Blob.hpp>
# include <Siv3D/ConstantBuffer.hpp>

namespace s3d
{
	struct Mat3x3;
	struct VS2DQuadWarp;
	struct PS2DQuadWarp;

	enum class EngineVS
	{
		QuadWarp,
	};

	enum class EnginePS
	{
		Copy,

		GaussianBlur_5,

		GaussianBlur_9,

		GaussianBlur_13,

		ApplySrgbCurve,

		QuadWarp,
	};

	class SIV3D_NOVTABLE ISiv3DShader
	{
	public:

		static ISiv3DShader* Create();

		virtual ~ISiv3DShader() = default;

		virtual void init() = 0;

		virtual VertexShader::IDType createVSFromFile(FilePathView path, StringView entryPoint, const Array<ConstantBufferBinding>& bindings) = 0;

		virtual VertexShader::IDType createVSFromSource(StringView source, StringView entryPoint, const Array<ConstantBufferBinding>& bindings) = 0;

		virtual PixelShader::IDType createPSFromFile(FilePathView path, StringView entryPoint, const Array<ConstantBufferBinding>& bindings) = 0;
		
		virtual PixelShader::IDType createPSFromSource(StringView source, StringView entryPoint, const Array<ConstantBufferBinding>& bindings) = 0;

		virtual void releaseVS(VertexShader::IDType handleID) = 0;

		virtual void releasePS(PixelShader::IDType handleID) = 0;

		virtual void setVS(VertexShader::IDType handleID) = 0;

		virtual void setPS(PixelShader::IDType handleID) = 0;

		virtual const Blob& getBinaryVS(VertexShader::IDType handleID) = 0;

		virtual const Blob& getBinaryPS(PixelShader::IDType handleID) = 0;

		virtual void setConstantBufferVS(uint32 slot, const ConstantBufferBase& cb) = 0;

		virtual void setConstantBufferPS(uint32 slot, const ConstantBufferBase& cb) = 0;


		virtual const VertexShader& getEngineVS(EngineVS vs) const = 0;

		virtual const PixelShader& getEnginePS(EnginePS ps) const = 0;

		virtual void setQuadWarpCB(const VS2DQuadWarp& vsCB, const PS2DQuadWarp& psCB) = 0;
	};
}
