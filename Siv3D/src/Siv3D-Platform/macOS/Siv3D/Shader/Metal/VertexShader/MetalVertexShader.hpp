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
	class MetalVertexShader
	{
	private:

		Blob m_binary;
		
		id<MTLFunction> m_vsFunction = nil;
		
		bool m_initialized = false;

	public:

		struct Null {};
		
		MetalVertexShader() = default;

		explicit MetalVertexShader(Null);
		
		explicit MetalVertexShader(id<MTLLibrary> library, StringView name);
		
		~MetalVertexShader();

		bool isInitialized() const noexcept;

		const Blob& getBinary() const noexcept;

		id<MTLFunction> getFunction() const;
	};
}
