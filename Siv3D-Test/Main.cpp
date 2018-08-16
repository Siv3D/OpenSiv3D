
# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);
	Image image(580, 720, Palette::Black);
	NoiseGenerator noise(image.size());
	DynamicTexture texture(image);
	const Font font(16, Typeface::Bold);

	const Array<String> options = {
		U"Value",
		U"ValueFractal",
		U"Perlin",
		U"PerlinFractal",
		U"Simplex",
		U"SimplexFractal",
		U"WhiteNoise",
		U"Cellular",
		U"Cubic",
		U"CubicFractal",
	};
	size_t coloring = 0;
	int32 seed = 1337;
	size_t type = 0;
	double frequencyExp2 = -6.0;
	double xScale = 1.0, yScale = 1.0;
	double octaves = 3, lacunarity = 2.0, gain = 0.5;
	size_t fractalType = 0;
	size_t distanceFunction = 0;
	size_t returnType = 1;
	size_t noiseLookupType = 4;
	double luFreqExp2 = -6.0;
	double jitter = 0.45;
	size_t perturbType = 0;
	double perturbAmp = 1.0, perturbFrequency = 0.5;
	Vec3 offset(0, 0, 0);

	while (System::Update())
	{
		const double speed = KeyShift.pressed() ? 5.0 : 1.0;
		const Vec3 previousOffset = offset;
		offset.x += (KeyD.pressed() - KeyA.pressed()) * speed;
		offset.y += (KeyS.pressed() - KeyW.pressed()) * speed;
		offset.z += (KeyE.pressed() - KeyX.pressed()) * speed;
		bool changed = (offset != previousOffset);

		if (KeyR.down())
		{
			seed = Random(0, Largest<int32>());
			changed = true;
		}

		font(U"Offset{}\nSeed:{}"_fmt(offset, seed)).draw(590, 10);
		changed |= SimpleGUI::RadioButtons(type, options, Vec2(590, 60), 190);
		changed |= SimpleGUI::RadioButtons(coloring, { U"Grayscale", U"HSV", U"HSVW" }, Vec2(1070, 140), 190);

		const bool isFractal = (static_cast<NoiseType>(type) == NoiseType::ValueFractal)
			|| (static_cast<NoiseType>(type) == NoiseType::PerlinFractal)
			|| (static_cast<NoiseType>(type) == NoiseType::SimplexFractal);
		const bool isCellular = (static_cast<NoiseType>(type) == NoiseType::Cellular);
		const bool isNoiseLookup = (isCellular && static_cast<CellularReturnType>(returnType) == CellularReturnType::NoiseLookup);
		const bool isPerturb = (static_cast<PerturbType>(perturbType) != PerturbType::None);

		changed |= SimpleGUI::Slider(U"freq: {:.3f}"_fmt(Exp2(frequencyExp2)), frequencyExp2, -12.0, 0.0, Vec2(790, 20), 150);
		changed |= SimpleGUI::Slider(U"xScale: {:.2f}"_fmt(xScale), xScale, 0.0, 8.0, Vec2(790, 60), 150);
		changed |= SimpleGUI::Slider(U"yScale: {:.2f}"_fmt(yScale), yScale, 0.0, 8.0, Vec2(790, 100), 150);
		changed |= SimpleGUI::Slider(U"octaves: {}"_fmt(static_cast<int32>(octaves)), octaves, 1.0, 8.0, Vec2(790, 140), 150, 120, isFractal);
		changed |= SimpleGUI::Slider(U"lacunarity: {:.1f}"_fmt(lacunarity), lacunarity, 0.0, 16.0, Vec2(790, 180), 150, 120, isFractal);
		changed |= SimpleGUI::Slider(U"gain: {:.2f}"_fmt(gain), gain, 0.0, 1.0, Vec2(790, 220), 150, 120, isFractal);
		changed |= SimpleGUI::RadioButtons(fractalType, { U"FBM", U"Billow", U"RigidMulti" }, Vec2(590, 460), 190, isFractal);
		changed |= SimpleGUI::RadioButtons(distanceFunction, { U"Euclidean", U"Manhattan", U"Natural" }, Vec2(590, 580), 190, isCellular);
		changed |= SimpleGUI::RadioButtons(returnType, { U"CellValue", U"Distance", U"Distance2", U"Distance2Add", U"Distance2Sub", U"Distance2Mul", U"Distance2Div", U"NoiseLookup", U"Distance2Cave" }, Vec2(790, 260), 190, isCellular);
		changed |= SimpleGUI::RadioButtons(noiseLookupType, { U"Value", U"ValueFractal", U"Perlin", U"PerlinFractal", U"Simplex", U"SimplexFractal" }, Vec2(990, 260), 190, isNoiseLookup);
		changed |= SimpleGUI::Slider(U"luFreq: {:.3f}"_fmt(Exp2(luFreqExp2)), luFreqExp2, -12.0, 0.0, Vec2(990, 500), 150, 120, isNoiseLookup);
		changed |= SimpleGUI::Slider(U"jitter: {:.2f}"_fmt(jitter), jitter, -3.0, 3.0, Vec2(990, 540), 150, 120, isCellular);
		changed |= SimpleGUI::RadioButtons(perturbType, { U"None", U"Gradient", U"GradFractal" }, Vec2(1070, 20), 200);
		changed |= SimpleGUI::Slider(U"pAmp: {:.2f}"_fmt(perturbAmp), perturbAmp, 0.0, 8.0, Vec2(790, 620), 150, 280, isPerturb);
		changed |= SimpleGUI::Slider(U"pFreq: {:.2f}"_fmt(perturbFrequency), perturbFrequency, 0.0, 8.0, Vec2(790, 660), 150, 280, isPerturb);

		if (changed || System::FrameCount() == 1)
		{
			noise.seed(seed);
			noise.setFractalParameters(static_cast<int32>(octaves), lacunarity, gain, static_cast<FractalType>(fractalType));
			noise.setCellularParameters(static_cast<CellularDistanceFunction>(distanceFunction), static_cast<CellularReturnType>(returnType),
				static_cast<NoiseType>(noiseLookupType), luFreqExp2, 0, 1, jitter);
			noise.setPerturbParameters(static_cast<PerturbType>(perturbType), perturbAmp, perturbFrequency);

			noise.generate(static_cast<NoiseType>(type), Exp2(frequencyExp2), xScale, yScale, 1.0, offset.x, offset.y, offset.z);
			{
				const float* pSrc = noise.data();
				Color* pDst = image.data();
				const Color* const pDstEnd = pDst + image.num_pixels();

				if (isCellular && (static_cast<CellularReturnType>(returnType) != CellularReturnType::CellValue))
				{
					if (coloring == 0)
					{
						while (pDst != pDstEnd)
						{
							const float value = *pSrc++;
							*pDst++ = ToColor(value);
						}
					}
					else if (coloring == 1)
					{
						while (pDst != pDstEnd)
						{
							const float value = *pSrc++;
							*pDst++ = HueToColor(value * 360);
						}
					}
					else
					{
						while (pDst != pDstEnd)
						{
							const float value = *pSrc++;
							*pDst++ = value > 0.0 ? HueToColor(value * 360) : Palette::White;
						}
					}
				}
				else
				{
					if (coloring == 0)
					{
						while (pDst != pDstEnd)
						{
							const float value = *pSrc++ * 0.5f + 0.5f;
							*pDst++ = ToColor(value);
						}
					}
					else if (coloring == 1)
					{
						while (pDst != pDstEnd)
						{
							const float value = *pSrc++ * 0.5f + 0.5f;
							*pDst++ = HueToColor(value * 360);
						}
					}
					else
					{
						while (pDst != pDstEnd)
						{
							const float value = *pSrc++ * 0.5f + 0.5f;
							*pDst++ = value > 0.0 ? HueToColor(value * 360) : Palette::White;
						}
					}
				}
			}

			texture.fill(image);
		}

		texture.draw();
	}
}
