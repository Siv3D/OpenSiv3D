//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "NoiseDetail.hpp"
# include <Siv3D/Noise.hpp>

namespace s3d
{
	NoiseGenerator::NoiseGenerator()
		: pImpl(std::make_shared<NoiseGeneratorDetail>())
	{

	}

	NoiseGenerator::NoiseGenerator(const int32 xSize, const int32 ySize, const int32 zSize)
		: pImpl(std::make_shared<NoiseGeneratorDetail>(xSize, ySize, zSize))
	{

	}

	NoiseGenerator::~NoiseGenerator()
	{

	}

	void NoiseGenerator::seed(const int32 seed)
	{
		pImpl->seed(seed);
	}

	void NoiseGenerator::generate(const NoiseType type, const double frequency,
		const double xScale, const double yScale, const double zScale,
		const double xOffset, const double yOffset, const double zOffset)
	{
		pImpl->generate(type, frequency, xScale, yScale, zScale, xOffset, yOffset, zOffset);
	}

	void NoiseGenerator::setFractalParameters(const int32 octaves, const double lacunarity, const double gain, const FractalType fractalType)
	{
		pImpl->setFractalParameters(octaves, lacunarity, gain, fractalType);
	}

	void NoiseGenerator::setCellularParameters(
		const CellularDistanceFunction cellularDistanceFunction,
		const CellularReturnType cellularReturnType,
		const NoiseType cellularNoiseLookupType,
		const double cellularNoiseLookupFrequency,
		const int32 cellularDistanceIndex0, const int32 cellularDistanceIndex1, const double cellularJitter)
	{
		pImpl->setCellularParameters(cellularDistanceFunction, cellularReturnType, cellularNoiseLookupType, cellularNoiseLookupFrequency, cellularDistanceIndex0, cellularDistanceIndex1, cellularJitter);
	}

	void NoiseGenerator::setPerturbParameters(
		const PerturbType perturbType,
		const double perturbAmp, const double perturbFrequency, const double perturbNormalizeLength)
	{
		pImpl->setPerturbParameters(perturbType, perturbAmp, perturbFrequency, perturbNormalizeLength);
	}

	void NoiseGenerator::setFractalPerturbParameters(
		const int32 perturbOctaves, const double perturbLacunarity, const double perturbGain)
	{
		pImpl->setFractalPerturbParameters(perturbOctaves, perturbLacunarity, perturbGain);
	}

	int32 NoiseGenerator::xSize() const
	{
		return pImpl->xSize();
	}

	int32 NoiseGenerator::ySize() const
	{
		return pImpl->ySize();
	}

	int32 NoiseGenerator::zSize() const
	{
		return pImpl->zSize();
	}

	const float* NoiseGenerator::data() const
	{
		return pImpl->data();
	}
}
