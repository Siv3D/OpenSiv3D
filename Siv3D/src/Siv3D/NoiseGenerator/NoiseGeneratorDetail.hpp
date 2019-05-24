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
# include <Siv3D/NoiseGenerator.hpp>
# include <Siv3D/Image.hpp>
# include <FastNoiseSIMD/FastNoiseSIMD.h>

namespace s3d
{
	class NoiseGenerator::NoiseGeneratorDetail
	{
	private:

		int32 m_xSize = 0;

		int32 m_ySize = 0;

		int32 m_zSize = 0;

		int32 m_seed = 1337;

		FastNoiseVectorSet* m_vectorSet = nullptr;

		float* m_noiseSet = nullptr;

		FastNoiseSIMD* m_noise = nullptr;

		//
		// Fractal
		//

		int32 m_octaves = 3;

		float m_lacunarity = 2.0f;

		float m_gain = 0.5f;

		FractalType m_fractalType = FractalType::FBM;

		//
		// Cellular
		//

		CellularDistanceFunction m_cellularDistanceFunction = CellularDistanceFunction::Euclidean;

		CellularReturnType m_cellularReturnType = CellularReturnType::Distance;

		NoiseType m_cellularNoiseLookupType = NoiseType::Simplex;

		float m_cellularNoiseLookupFrequency = 0.2f;

		int32 m_cellularDistanceIndex0 = 0;

		int32 m_cellularDistanceIndex1 = 1;

		float m_cellularJitter = 0.45f;

		//
		// Perturb
		//

		PerturbType m_perturbType = PerturbType::None;

		float m_perturbAmp = 1.0f;

		float m_perturbFrequency = 1.0f;

		float m_perturbNormalizeLength = 1.0f;

		//
		// Fractal Perturb
		//

		int32 m_perturbOctaves = 3;

		float m_perturbLacunarity = 2.0f;

		float m_perturbGain = 0.5f;

	public:

		NoiseGeneratorDetail() = default;

		NoiseGeneratorDetail(int32 xSize, int32 ySize, int32 zSize);

		~NoiseGeneratorDetail();

		void seed(const int32 seed);

		void generate(NoiseType type, double frequency,
			double xScale, double yScale, double zScale,
			double xOffset, double yOffset, double zOffset);

		void setFractalParameters(int32 octaves, double lacunarity, double gain, FractalType fractalType);

		void setCellularParameters(
			CellularDistanceFunction cellularDistanceFunction,
			CellularReturnType cellularReturnType,
			NoiseType cellularNoiseLookupType,
			double cellularNoiseLookupFrequency,
			int32 cellularDistanceIndex0, int32 cellularDistanceIndex1, double cellularJitter);

		void setPerturbParameters(
			PerturbType perturbType,
			double perturbAmp, double perturbFrequency, double perturbNormalizeLength);

		void setFractalPerturbParameters(
			int32 perturbOctaves, double perturbLacunarity, double perturbGain);

		int32 xSize() const;

		int32 ySize() const;

		int32 zSize() const;

		const float* data() const;
	};
}
