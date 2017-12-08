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

		virtual VertexShaderID createVS(ByteArray&& binary) = 0;

		virtual VertexShaderID createVSFromFile(const FilePath& path, const Array<BindingPoint>& bindingPoints) = 0;
		
		virtual VertexShaderID createVSFromSource(const String& source, const Array<BindingPoint>& bindingPoints) = 0;

		virtual PixelShaderID createPS(ByteArray&& binary) = 0;

		virtual PixelShaderID createPSFromFile(const FilePath& path, const Array<BindingPoint>& bindingPoints) = 0;
		
		virtual PixelShaderID createPSFromSource(const String& source, const Array<BindingPoint>& bindingPoints) = 0;

		virtual void releaseVS(VertexShaderID handleID) = 0;

		virtual void releasePS(PixelShaderID handleID) = 0;

		virtual ByteArrayView getBinaryViewVS(VertexShaderID handleID) = 0;

		virtual ByteArrayView getBinaryViewPS(PixelShaderID handleID) = 0;

		virtual const VertexShader& getStandardVS(size_t index) const = 0;

		virtual const PixelShader& getStandardPS(size_t index) const = 0;

		virtual void setVS(VertexShaderID handleID) = 0;

		virtual void setPS(PixelShaderID handleID) = 0;
	};
}
