/* cpu_x86.h
 * 
 * Author           : Alexander J. Yee
 * Date Created     : 04/12/2014
 * Last Modified    : 04/12/2014
 * 
 */

#pragma once
#ifndef _cpu_x86_H
#define _cpu_x86_H
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Dependencies
#include <stdint.h>
#include <string>
namespace FeatureDetector{
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
struct cpu_x86{
    //  Vendor
    bool Vendor_AMD;
    bool Vendor_Intel;

    //  OS Features
    bool OS_x64;
    bool OS_AVX;
    bool OS_AVX512;

    //  Misc.
    bool HW_MMX;
    bool HW_x64;
    bool HW_ABM;
    bool HW_RDRAND;
    bool HW_BMI1;
    bool HW_BMI2;
    bool HW_ADX;
    bool HW_PREFETCHWT1;
    bool HW_MPX;

    //  SIMD: 128-bit
    bool HW_SSE;
    bool HW_SSE2;
    bool HW_SSE3;
    bool HW_SSSE3;
    bool HW_SSE41;
    bool HW_SSE42;
    bool HW_SSE4a;
    bool HW_AES;
    bool HW_SHA;

    //  SIMD: 256-bit
    bool HW_AVX;
    bool HW_XOP;
    bool HW_FMA3;
    bool HW_FMA4;
    bool HW_AVX2;

    //  SIMD: 512-bit
    bool HW_AVX512_F;
    bool HW_AVX512_PF;
    bool HW_AVX512_ER;
    bool HW_AVX512_CD;
    bool HW_AVX512_VL;
    bool HW_AVX512_BW;
    bool HW_AVX512_DQ;
    bool HW_AVX512_IFMA;
    bool HW_AVX512_VBMI;

public:
    cpu_x86();
    void detect_host();

    void print() const;
    static void print_host();

    static void cpuid(int32_t out[4], int32_t x);
    static std::string get_vendor_string();

private:
    static void print(const char* label, bool yes);

    static bool detect_OS_x64();
    static bool detect_OS_AVX();
    static bool detect_OS_AVX512();
};
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
}
#endif
