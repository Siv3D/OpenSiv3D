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

# include "NoiseGeneratorDetail.hpp"

namespace s3d
{
	NoiseGenerator::NoiseGeneratorDetail::NoiseGeneratorDetail(int32 xSize, int32 ySize, int32 zSize)
		: m_xSize(xSize)
		, m_ySize(ySize)
		, m_zSize(zSize)
	{
		assert(xSize > 0 && ySize > 0 && zSize > 0);

		m_noise = FastNoiseSIMD::NewFastNoiseSIMD(m_seed);

		m_vectorSet = FastNoiseSIMD::GetVectorSet(zSize, ySize, xSize);

		m_noiseSet = FastNoiseSIMD::GetEmptySet(zSize * ySize * xSize);
	}

	NoiseGenerator::NoiseGeneratorDetail::~NoiseGeneratorDetail()
	{
		if (m_noise)
		{
			delete m_noise;
			m_noise = nullptr;
		}

		if (m_noiseSet)
		{
			FastNoiseSIMD::FreeNoiseSet(m_noiseSet);
			m_noiseSet = nullptr;
		}

		if (m_vectorSet)
		{
			delete m_vectorSet;
			m_vectorSet = nullptr;
		}
	}

	void NoiseGenerator::NoiseGeneratorDetail::seed(const int32 seed)
	{
		m_seed = seed;
	}

	void NoiseGenerator::NoiseGeneratorDetail::generate(NoiseType type, double frequency,
		double xScale, double yScale, double zScale,
		double xOffset, double yOffset, double zOffset)
	{
		if (!m_noise)
		{
			return;
		}

		m_noise->SetSeed(m_seed);
		m_noise->SetNoiseType(static_cast<FastNoiseSIMD::NoiseType>(type));
		m_noise->SetFrequency(static_cast<float>(frequency));
		m_noise->SetAxisScales(static_cast<float>(zScale), static_cast<float>(yScale), static_cast<float>(xScale));

		m_noise->SetFractalOctaves(m_octaves);
		m_noise->SetFractalLacunarity(m_lacunarity);
		m_noise->SetFractalGain(m_gain);
		m_noise->SetFractalType(static_cast<FastNoiseSIMD::FractalType>(m_fractalType));

		m_noise->SetCellularDistanceFunction(static_cast<FastNoiseSIMD::CellularDistanceFunction>(m_cellularDistanceFunction));
		m_noise->SetCellularReturnType(static_cast<FastNoiseSIMD::CellularReturnType>(m_cellularReturnType));
		m_noise->SetCellularNoiseLookupType(static_cast<FastNoiseSIMD::NoiseType>(m_cellularNoiseLookupType));
		m_noise->SetCellularNoiseLookupFrequency(m_cellularNoiseLookupFrequency);
		m_noise->SetCellularDistance2Indicies(m_cellularDistanceIndex0, m_cellularDistanceIndex1);
		m_noise->SetCellularJitter(m_cellularJitter);

		m_noise->SetPerturbType(static_cast<FastNoiseSIMD::PerturbType>(m_perturbType));
		m_noise->SetPerturbAmp(m_perturbAmp);
		m_noise->SetPerturbFrequency(m_perturbFrequency);
		m_noise->SetPerturbNormaliseLength(m_perturbNormalizeLength);

		m_noise->SetPerturbFractalOctaves(m_perturbOctaves);
		m_noise->SetPerturbFractalLacunarity(m_perturbLacunarity);
		m_noise->SetPerturbFractalGain(m_perturbGain);

		m_noise->FillNoiseSet(m_noiseSet, m_vectorSet, static_cast<float>(zOffset), static_cast<float>(yOffset), static_cast<float>(xOffset));
	}

	void NoiseGenerator::NoiseGeneratorDetail::setFractalParameters(int32 octaves, double lacunarity, double gain, FractalType fractalType)
	{
		m_octaves = octaves;
		m_lacunarity = static_cast<float>(lacunarity);
		m_gain = static_cast<float>(gain);
		m_fractalType = fractalType;
	}

	void NoiseGenerator::NoiseGeneratorDetail::setCellularParameters(
		CellularDistanceFunction cellularDistanceFunction,
		CellularReturnType cellularReturnType,
		NoiseType cellularNoiseLookupType,
		double cellularNoiseLookupFrequency,
		int32 cellularDistanceIndex0, int32 cellularDistanceIndex1, double cellularJitter)
	{
		m_cellularDistanceFunction = cellularDistanceFunction;
		m_cellularReturnType = cellularReturnType;
		m_cellularNoiseLookupType = cellularNoiseLookupType;
		m_cellularNoiseLookupFrequency = static_cast<float>(cellularNoiseLookupFrequency);
		m_cellularDistanceIndex0 = cellularDistanceIndex0;
		m_cellularDistanceIndex1 = cellularDistanceIndex1;
		m_cellularJitter = static_cast<float>(cellularJitter);
	}

	void NoiseGenerator::NoiseGeneratorDetail::setPerturbParameters(
		PerturbType perturbType,
		double perturbAmp, double perturbFrequency, double perturbNormalizeLength)
	{
		m_perturbType = perturbType;
		m_perturbAmp = static_cast<float>(perturbAmp);
		m_perturbFrequency = static_cast<float>(perturbFrequency);
		m_perturbNormalizeLength = static_cast<float>(perturbNormalizeLength);
	}

	void NoiseGenerator::NoiseGeneratorDetail::setFractalPerturbParameters(
		int32 perturbOctaves, double perturbLacunarity, double perturbGain)
	{
		m_perturbOctaves = perturbOctaves;
		m_perturbLacunarity = static_cast<float>(perturbLacunarity);
		m_perturbGain = static_cast<float>(perturbGain);
	}

	int32 NoiseGenerator::NoiseGeneratorDetail::xSize() const
	{
		return m_xSize;
	}

	int32 NoiseGenerator::NoiseGeneratorDetail::ySize() const
	{
		return m_ySize;
	}

	int32 NoiseGenerator::NoiseGeneratorDetail::zSize() const
	{
		return m_zSize;
	}

	const float* NoiseGenerator::NoiseGeneratorDetail::data() const
	{
		return m_noiseSet;
	}
}
