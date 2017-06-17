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

# include "CCPU.hpp"
# include "../../ThirdParty/FeatureDetector/cpu_x86.h"
# include <Siv3D/Logger.hpp>
# include <Siv3D/Array.hpp>

namespace s3d
{
	CCPU::CCPU()
	{

	}

	CCPU::~CCPU()
	{

	}

	bool CCPU::init()
	{
		FeatureDetector::cpu_x86 cpuFeature;

		cpuFeature.detect_host();

		m_feature.vendor = cpuFeature.Vendor_Intel ? CPUVendor::Intel : cpuFeature.Vendor_AMD ? CPUVendor::AMD : CPUVendor::Unknown;

		m_feature.vendorName = CharacterSet::FromUTF8(cpuFeature.get_vendor_string());

		{
			int32 cpui[4] = {};
			cpuFeature.cpuid(cpui, 0x80000000);
			const int32 nExIDs = cpui[0];
			Array<int32> extData;

			for (int32 i = 0x80000000; i <= nExIDs; ++i)
			{
				cpuFeature.cpuid(cpui, i);

				extData.insert(extData.end(), std::begin(cpui), std::end(cpui));
			}

			char brand[0x40] = {};

			if (nExIDs >= 0x80000004)
			{
				::memcpy(brand, &extData[8], sizeof(cpui));
				::memcpy(brand + 16, &extData[12], sizeof(cpui));
				::memcpy(brand + 32, &extData[16], sizeof(cpui));
			}

			m_feature.name = CharacterSet::FromUTF8(brand);
		}

		LOG_INFO(L"ℹ️ CPU vendor: {0}"_fmt(m_feature.vendorName));
		LOG_INFO(L"ℹ️ CPU name: {0}"_fmt(m_feature.name));

		m_feature.SSE		= cpuFeature.HW_SSE;
		m_feature.SSE2		= cpuFeature.HW_SSE2;
		m_feature.SSE3		= cpuFeature.HW_SSE3;
		m_feature.SSSE3		= cpuFeature.HW_SSSE3;
		m_feature.SSE41		= cpuFeature.HW_SSE41;
		m_feature.SSE42		= cpuFeature.HW_SSE42;
		m_feature.SSE4a		= cpuFeature.HW_SSE4a;
		m_feature.AES		= cpuFeature.HW_AES;
		m_feature.SHA		= cpuFeature.HW_SHA;
		m_feature.AVX		= cpuFeature.HW_AVX && cpuFeature.OS_AVX;
		m_feature.XOP		= cpuFeature.HW_XOP;
		m_feature.FMA4		= cpuFeature.HW_FMA4;
		m_feature.FMA3		= cpuFeature.HW_FMA3;
		m_feature.AVX2		= cpuFeature.HW_AVX2 && cpuFeature.OS_AVX;
		m_feature.AVX512_F	= cpuFeature.HW_AVX512_F && cpuFeature.OS_AVX512;

		Array<String> features;

		if (m_feature.SSE)
		{
			features.emplace_back(L"SSE");
		}

		if (m_feature.SSE2)
		{
			features.emplace_back(L"SSE2");
		}

		if (m_feature.SSE3)
		{
			features.emplace_back(L"SSE3");
		}

		if (m_feature.SSSE3)
		{
			features.emplace_back(L"SSSE3");
		}

		if (m_feature.SSE41)
		{
			features.emplace_back(L"SSE4.1");
		}

		if (m_feature.SSE42)
		{
			features.emplace_back(L"SSE4.2");
		}

		if (m_feature.SSE4a)
		{
			features.emplace_back(L"SSE4a");
		}

		if (m_feature.AES)
		{
			features.emplace_back(L"AES-NI");
		}

		if (m_feature.SHA)
		{
			features.emplace_back(L"SHA");
		}

		if (m_feature.AVX)
		{
			features.emplace_back(L"AVX");
		}

		if (m_feature.XOP)
		{
			features.emplace_back(L"XOP");
		}

		if (m_feature.FMA4)
		{
			features.emplace_back(L"FMA4");
		}

		if (m_feature.FMA3)
		{
			features.emplace_back(L"FMA3");
		}

		if (m_feature.AVX2)
		{
			features.emplace_back(L"AVX2");
		}

		if (m_feature.AVX512_F)
		{
			features.emplace_back(L"AVX-512 F");
		}

		LOG_INFO(L"ℹ️ Instruction set extensions: {0}"_fmt(features.join(L", ", L"", L"")));

		return true;
	}

	void CCPU::setFeature(const CPUFeature& feature)
	{
		m_feature = feature;
	}

	const CPUFeature& CCPU::getFeature() const
	{
		return m_feature;
	}
}
