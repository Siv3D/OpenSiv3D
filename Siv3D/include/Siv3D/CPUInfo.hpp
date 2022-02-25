//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "String.hpp"

namespace s3d
{
	/// @brief 対応命令セット
	struct X86Features
	{
        int fpu : 1;
        int tsc : 1;
        int cx8 : 1;
        int clfsh : 1;
        int mmx : 1;
        int aes : 1;
        int erms : 1;
        int f16c : 1;
        int fma4 : 1;
        int fma3 : 1;
        int vaes : 1;
        int vpclmulqdq : 1;
        int bmi1 : 1;
        int hle : 1;
        int bmi2 : 1;
        int rtm : 1;
        int rdseed : 1;
        int clflushopt : 1;
        int clwb : 1;

        int sse : 1;
        int sse2 : 1;
        int sse3 : 1;
        int ssse3 : 1;
        int sse4_1 : 1;
        int sse4_2 : 1;
        int sse4a : 1;

        int avx : 1;
        int avx2 : 1;

        int avx512f : 1;
        int avx512cd : 1;
        int avx512er : 1;
        int avx512pf : 1;
        int avx512bw : 1;
        int avx512dq : 1;
        int avx512vl : 1;
        int avx512ifma : 1;
        int avx512vbmi : 1;
        int avx512vbmi2 : 1;
        int avx512vnni : 1;
        int avx512bitalg : 1;
        int avx512vpopcntdq : 1;
        int avx512_4vnniw : 1;
        int avx512_4vbmi2 : 1;
        int avx512_second_fma : 1;
        int avx512_4fmaps : 1;
        int avx512_bf16 : 1;
        int avx512_vp2intersect : 1;
        int amx_bf16 : 1;
        int amx_tile : 1;
        int amx_int8 : 1;

        int pclmulqdq : 1;
        int smx : 1;
        int sgx : 1;
        int cx16 : 1;
        int sha : 1;
        int popcnt : 1;
        int movbe : 1;
        int rdrnd : 1;

        int dca : 1;
        int ss : 1;
	};

    /// @brief CPU 情報
    struct CPUInfo
    {
        /// @brief 対応命令セット
        X86Features features;

        /// @brief 
        int32 family;
        
        /// @brief 
        int32 model;
        
        /// @brief 
        int32 stepping;
        
        /// @brief 
        String vendor;
        
        /// @brief 
        String brand;
    };

    /// @brief ユーザの CPU の情報を返します。
    /// @return ユーザの CPU の情報
	[[nodiscard]]
	const CPUInfo& GetCPUInfo() noexcept;
}
