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
# include <Siv3D/Fwd.hpp>
# include <Siv3D/VertexShader.hpp>
# include <Siv3D/PixelShader.hpp>

namespace s3d
{
	class ISiv3DShader
	{
	public:

		static ISiv3DShader* Create();

		virtual ~ISiv3DShader() = default;

		virtual bool compileHLSL(IReader& reader, ByteArray& to, const char* filePath, const char* entryPoint, const char* target) = 0;

		virtual VertexShader::IDType createVS(ByteArray&& binary) = 0;

		virtual VertexShader::IDType createVSFromFile(const FilePath& path) = 0;

		virtual PixelShader::IDType createPS(ByteArray&& binary) = 0;

		virtual PixelShader::IDType createPSFromFile(const FilePath& path) = 0;

		virtual void releaseVS(VertexShader::IDType handleID) = 0;

		virtual void releasePS(PixelShader::IDType handleID) = 0;

		virtual ByteArrayView getBinaryViewVS(VertexShader::IDType handleID) = 0;

		virtual ByteArrayView getBinaryViewPS(PixelShader::IDType handleID) = 0;

		virtual const VertexShader& getStandardVS(size_t index) const = 0;

		virtual const PixelShader& getStandardPS(size_t index) const = 0;

		virtual void setVS(VertexShader::IDType handleID) = 0;

		virtual void setPS(PixelShader::IDType handleID) = 0;
	};
}
