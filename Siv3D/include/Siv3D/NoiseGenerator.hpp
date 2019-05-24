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
# include <memory>
# include "Fwd.hpp"
# include "PointVector.hpp"

namespace s3d
{
	enum class NoiseType
	{
		Value,
		ValueFractal,
		Perlin,
		PerlinFractal,
		Simplex,
		SimplexFractal,
		WhiteNoise,
		Cellular,
		Cubic,
		CubicFractal
	};

	enum class FractalType
	{
		FBM,
		Billow,
		RigidMulti,
	};

	enum class CellularDistanceFunction
	{
		Euclidean,
		Manhattan,
		Natural,
	};

	enum class CellularReturnType
	{
		CellValue,
		Distance,
		Distance2,
		Distance2Add,
		Distance2Sub,
		Distance2Mul,
		Distance2Div,
		NoiseLookup,
		Distance2Cave,
	};

	enum class PerturbType
	{
		None,
		Gradient,
		GradientFractal,
		Normalize,
		Gradient_Normalize,
		GradientFractal_Normalize,
	};

	class NoiseGenerator
	{
	private:

		class NoiseGeneratorDetail;

		std::shared_ptr<NoiseGeneratorDetail> pImpl;

	public:

		NoiseGenerator();

		NoiseGenerator(int32 xSize, int32 ySize, int32 zSize = 1);

		explicit NoiseGenerator(const Size& size, int32 zSize = 1)
			: NoiseGenerator(size.x, size.y, zSize) {}

		~NoiseGenerator();

		void seed(int32 seed);

		void generate(NoiseType type, double frequency = 0.01,
			double xScale = 1.0, double yScale = 1.0, double zScale = 1.0,
			double xOffset = 0.0, double yOffset = 0.0, double zOffset = 0.0);

		void setFractalParameters(int32 octaves = 3, double lacunarity = 2.0, double gain = 0.5, FractalType fractalType = FractalType::FBM);

		void setCellularParameters(
			CellularDistanceFunction cellularDistanceFunction = CellularDistanceFunction::Euclidean,
			CellularReturnType cellularReturnType = CellularReturnType::Distance,
			NoiseType cellularNoiseLookupType = NoiseType::Simplex,
			double cellularNoiseLookupFrequency = 0.2,
			int32 cellularDistanceIndex0 = 0, int32 cellularDistanceIndex1 = 1, double cellularJitter = 0.45);

		void setPerturbParameters(
			PerturbType perturbType = PerturbType::None,
			double perturbAmp = 1.0, double perturbFrequency = 0.5, double perturbNormalizeLength = 1.0);

		void setFractalPerturbParameters(
			int32 perturbOctaves = 3, double perturbLacunarity = 2.0, double perturbGain = 0.5);

		int32 xSize() const;

		int32 ySize() const;

		int32 zSize() const;

		const float* data() const;
	};
}
