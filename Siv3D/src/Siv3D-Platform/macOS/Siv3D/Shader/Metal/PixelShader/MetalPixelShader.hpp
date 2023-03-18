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
# include <Siv3D/Blob.hpp>
# import <Metal/Metal.h>

namespace s3d
{
	class MetalPixelShader
	{
	private:

		Blob m_binary;
		
		id<MTLFunction> m_psFunction = nil;
		
		bool m_initialized = false;

	public:

		struct Null {};

		MetalPixelShader() = default;

		explicit MetalPixelShader(Null);
		
		MetalPixelShader(id<MTLLibrary> library, StringView name);
		
		~MetalPixelShader();

		bool isInitialized() const noexcept;

		const Blob& getBinary() const noexcept;

		id<MTLFunction> getFunction() const;
	};
}
