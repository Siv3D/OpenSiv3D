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
# include "Fwd.hpp"
# include "String.hpp"

namespace s3d
{
	enum class CPUVendor
	{
		Intel,

		AMD,

		Unknown,
	};

	struct CPUFeature
	{
		String vendorName;

		String name;

		CPUVendor vendor;

		/// <summary>
		/// SSE
		/// </summary>
		bool SSE;

		/// <summary>
		/// SSE2
		/// </summary>
		bool SSE2;

		/// <summary>
		/// SSE3
		/// </summary>
		bool SSE3;

		/// <summary>
		/// SSSE3
		/// </summary>
		bool SSSE3;

		/// <summary>
		/// SSE4.1
		/// </summary>
		bool SSE41;

		/// <summary>
		/// SSE4.2
		/// </summary>
		bool SSE42;

		/// <summary>
		/// SSE4a
		/// </summary>
		bool SSE4a;

		/// <summary>
		/// AES-NI
		/// </summary>
		bool AES;

		/// <summary>
		/// Intel SHA Extensions
		/// </summary>
		bool SHA;

		/// <summary>
		/// AVX
		/// </summary>
		bool AVX;

		/// <summary>
		/// XOP
		/// </summary>
		bool XOP;

		/// <summary>
		/// FMA4
		/// </summary>
		bool FMA4;

		/// <summary>
		/// FMA3
		/// </summary>
		bool FMA3;

		/// <summary>
		/// AVX2
		/// </summary>
		bool AVX2;

		/// <summary>
		/// AVX-512 F
		/// </summary>
		bool AVX512_F;
	};

	namespace CPU
	{
		const CPUFeature& GetFeature();

		void SetFeature(const CPUFeature& feature);
	}
}
