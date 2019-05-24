//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Codec/ICodec.hpp>

namespace s3d
{
	class CCodec : public ISiv3DCodec
	{
	private:
		
	public:
		
		CCodec();
		
		~CCodec() override;
		
		void init() override;
		
		Wave decode(IReader& reader) override;
	};
}
