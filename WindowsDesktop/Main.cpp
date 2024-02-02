# include <Siv3D.hpp> // Siv3D v0.6.14

/// @brief シャドウマップ
class ShadowMap
{
public:

	/// @brief シャドウマップの設定
	struct Config
	{
		/// @brief シャドウマップの解像度
		Size resolution = Size{ 1024, 1024 };

		/// @brief 光の漏れを軽減する係数 [0.0, 1.0]
		/// @remark 大きいと光の漏れが軽減されますが、影のソフトさが低下します。
		double lightBleedingReduction = 0.8;

		/// @brief シャドウマップ生成に MSAA を使用するか
		bool useMSAA = false;

		/// @brief フィルタオプション [0, 3]
		/// @remark 0: フィルタなし, 1: 5x5, 2: 9x9, 3: 13x13
		size_t filter = 0;

		/// @brief シャドウマップにミップマップを使用するか
		bool useMipMap = false;
	};

	/// @brief シャドウマップ用の平行光源
	struct Light
	{
		/// @brief メイン平行光源の注視点
		Vec3 focusPos{ 0, 0, 0 };

		/// @brief メイン平行光源の位置
		Vec3 sunPos = (focusPos + Graphics3D::DefaultSunDirection * 64.0);

		/// @brief メイン平行光源の上方向
		Vec3 upDirection{ 0, 1, 0 };

		/// @brief シャドウマップのビューのサイズ
		/// @remark 大きいと広い範囲をカバーできますが、詳細が失われます。
		double viewSize = 64.0;

		/// @brief シャドウマップの近面までの距離
		double nearZ = 1.0;

		/// @brief シャドウマップの遠面までの距離
		double farZ = 1024.0;
	};

	ShadowMap() = default;

	explicit ShadowMap(const Config& config)
		: m_config{ config }
		, m_initialized{ true }
	{
		updateTextures();
	}

	/// @brief デプスパスを開始します。
	/// @param light 平行光源の設定
	void beginDepth(const Light& light)
	{
		if (not m_initialized)
		{
			throw Error{ U"ShadowMap::beginDepth() called before initialization" };
		}

		if (m_depthPass)
		{
			throw Error{ U"ShadowMap::beginDepth() called twice" };
		}

		if (m_shadowPass)
		{
			throw Error{ U"ShadowMap::beginDepth() called while shadow pass is active" };
		}

		m_depthPass.emplace();
		m_depthPass->oldCameraMat = FromMat4x4(Graphics3D::GetCameraTransform());
		m_depthPass->oldEyePosition = Graphics3D::GetEyePosition();
		m_depthPass->renderTarget = std::make_unique<ScopedRenderTarget3D>(m_textures[0]->clear(ColorF{ 0.0 }));
		m_depthPass->renderStates = std::make_unique<ScopedRenderStates3D>(BlendState::Opaque);

		m_camera.update(light);
		Graphics3D::SetCameraTransform(m_camera.viewProj, light.sunPos);

		Mat4x4 worldToShadowMap = (m_camera.viewProj * Mat4x4::Scale(Float3{ 0.5, 0.5, 1.0 }) * Mat4x4::Translate(Float3{ 0.5, 0.5, 0.0 }));

		if (System::GetRendererType() != EngineOption::Renderer::Direct3D11)
		{
			worldToShadowMap = worldToShadowMap.transposed();
		}

		m_cbp->worldToShadowMap = worldToShadowMap;
		m_cbp->sunPosition = light.sunPos;
		m_cbp->lightBleedingReduction = static_cast<float>(m_config.lightBleedingReduction);
		Graphics3D::SetPSConstantBuffer(4, m_cbp);
	}

	/// @brief デプスパスを終了します。
	void endDepth()
	{
		if (not m_depthPass)
		{
			throw Error{ U"ShadowMap::endDepth() called without beginDepth()" };
		}

		if (m_shadowPass)
		{
			throw Error{ U"ShadowMap::endDepth() called while shadow pass is active" };
		}

		Graphics3D::SetCameraTransform(Mat4x4{ m_depthPass->oldCameraMat.data() }, m_depthPass->oldEyePosition);

		m_depthPass.reset();
		Graphics3D::Flush();

		if (m_config.useMSAA)
		{
			dynamic_cast<MSRenderTexture*>(m_textures[0].get())->resolve();
		}

		if (m_config.filter)
		{
			const BoxFilterSize filterSize = ToBoxFilterSize(m_config.filter);

			if (m_config.useMSAA)
			{
				Shader::GaussianBlur(*m_textures[0], *m_textures[1], *m_textures[2], filterSize);
			}
			else
			{
				Shader::GaussianBlur(*m_textures[0], *m_textures[1], *m_textures[0], filterSize);
			}

			Graphics2D::Flush();
		}

		if (m_config.useMipMap)
		{
			getDepthTexture().generateMips();
		}
	}

	/// @brief シャドウパスを開始します。
	void beginShadow()
	{
		if (not m_initialized)
		{
			throw Error{ U"ShadowMap::beginShadow() called before initialization" };
		}

		if (m_shadowPass)
		{
			throw Error{ U"ShadowMap::beginShadow() called twice" };
		}

		if (m_depthPass)
		{
			throw Error{ U"ShadowMap::beginShadow() called while depth pass is active" };
		}

		m_shadowPass.emplace();
		m_shadowPass->pRenderStates = std::make_unique<ScopedRenderStates3D>(ScopedRenderStates3D::SamplerStateInfo{ ShaderStage::Pixel, 3, (m_config.useMipMap ? SamplerState::ClampAniso : SamplerState::ClampLinear) });
		Graphics3D::SetPSTexture(1, getDepthTexture());
		Graphics3D::SetPSConstantBuffer(4, m_cbp);
	}

	/// @brief シャドウパスを終了します。
	void endShadow()
	{
		if (not m_shadowPass)
		{
			throw Error{ U"ShadowMap::endShadow() called without beginShadow()" };
		}

		if (m_depthPass)
		{
			throw Error{ U"ShadowMap::endShadow() called while depth pass is active" };
		}

		Graphics3D::SetPSTexture(1, none);
		m_shadowPass.reset();
	}

	/// @brief シャドウマップの設定を変更します。
	/// @param config シャドウマップの設定
	void setConfig(const Config& config)
	{
		if (m_depthPass || m_shadowPass)
		{
			throw Error{ U"ShadowMap::setConfig() called while depth or shadow pass is active" };
		}

		m_config = config;
		updateTextures();
	}

	/// @brief 深度テクスチャを取得します。
	/// @return 深度テクスチャ
	[[nodiscard]]
	const RenderTexture& getDepthTexture() const noexcept
	{
		return *m_textures[getDepthTextureIndex()];
	}

private:

	struct TextureState
	{
		Size resolution{ 0, 0 };
		bool isRequired = false;
		bool useMSAA = false;
		bool useDepth = false;
		bool useMipMap = false;

		[[nodiscard]]
		bool operator ==(const TextureState&) const = default;
	};

	struct DepthCamera
	{
		Mat4x4 viewProj = Mat4x4::Identity();

		void update(const Light& light)
		{
			const SIMD_Float4 eyePosition{ light.sunPos, 0.0f };
			const SIMD_Float4 focusPosition{ light.focusPos, 0.0f };
			const SIMD_Float4 upDirection{ light.upDirection, 0.0f };
			const Mat4x4 view = DirectX::XMMatrixLookAtLH(eyePosition, focusPosition, upDirection);
			const float viewF = static_cast<float>(light.viewSize);
			const Mat4x4 proj = DirectX::XMMatrixOrthographicLH(viewF, viewF, static_cast<float>(light.farZ), static_cast<float>(light.nearZ));
			viewProj = (view * proj);
		}
	};

	struct DepthPass
	{
		std::array<float, 16> oldCameraMat = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
		Float3 oldEyePosition{ 0, 0, 0 };
		std::unique_ptr<ScopedRenderTarget3D> renderTarget;
		std::unique_ptr<ScopedRenderStates3D> renderStates;
	};

	struct ShadowPass
	{
		std::unique_ptr<ScopedRenderStates3D> pRenderStates;
	};

	struct PSShadow
	{
		Mat4x4 worldToShadowMap;
		Float3 sunPosition{ 0,0,0 };
		float lightBleedingReduction = 0.8f;
	};

	static constexpr TextureFormat DepthFormat = TextureFormat::R32G32_Float;

	Config m_config;

	std::array<TextureState, 3> m_currentTextureStates;

	std::array<std::unique_ptr<RenderTexture>, 3> m_textures;

	DepthCamera m_camera;

	Optional<DepthPass> m_depthPass;

	Optional<ShadowPass> m_shadowPass;

	ConstantBuffer<PSShadow> m_cbp;

	bool m_initialized = false;

	static void CreateDepthTexture(std::unique_ptr<RenderTexture>& depthTexture, const Config& config)
	{
		if (depthTexture)
		{
			const bool currentMSAA = (dynamic_cast<const MSRenderTexture*>(depthTexture.get()) != nullptr);
			const bool currentMipMap = depthTexture->hasMipMap();
			const Size currentResolution = depthTexture->size();

			if ((config.useMSAA == currentMSAA)
				&& (config.useMipMap == currentMipMap)
				&& (config.resolution == currentResolution))
			{
				return;
			}
		}

		depthTexture.reset();

		if (config.useMSAA)
		{
			depthTexture = std::make_unique<MSRenderTexture>(config.resolution, DepthFormat, HasDepth::Yes, HasMipMap{ config.useMipMap });
		}
		else
		{
			depthTexture = std::make_unique<RenderTexture>(config.resolution, DepthFormat, HasDepth::Yes, HasMipMap{ config.useMipMap });
		}
	}

	static void CreateInternalTexture(std::unique_ptr<RenderTexture>& internalTexture1, std::unique_ptr<RenderTexture>& internalTexture2, const Config& config)
	{
		{
			if (internalTexture1)
			{
				const Size currentResolution = internalTexture1->size();

				if (config.resolution == currentResolution)
				{
					return;
				}
			}

			internalTexture1.reset();
			internalTexture1 = std::make_unique<RenderTexture>(config.resolution, DepthFormat);
		}

		{
			if (not config.useMSAA)
			{
				if (internalTexture2)
				{
					internalTexture2.reset();
					return;
				}
			}

			if (internalTexture2)
			{
				const Size currentResolution = internalTexture2->size();

				if (config.resolution == currentResolution)
				{
					return;
				}
			}

			internalTexture2.reset();
			internalTexture2 = std::make_unique<RenderTexture>(config.resolution, DepthFormat);
		}
	}

	[[nodiscard]]
	size_t getDepthTextureIndex() const noexcept
	{
		if (m_config.filter)
		{
			return (m_config.useMSAA ? 2 : 1);
		}
		else
		{
			return 0;
		}
	}

	[[nodiscard]]
	static std::unique_ptr<RenderTexture> CreateRenderTexture(const TextureState& textureState)
	{
		if (not textureState.isRequired)
		{
			return nullptr;
		}

		if (textureState.useMSAA)
		{
			return std::make_unique<MSRenderTexture>(
				textureState.resolution,
				DepthFormat,
				HasDepth{ textureState.useDepth },
				HasMipMap{ textureState.useMipMap });
		}
		else
		{
			return std::make_unique<RenderTexture>(
				textureState.resolution,
				DepthFormat,
				HasDepth{ textureState.useDepth },
				HasMipMap{ textureState.useMipMap });
		}
	}

	void updateTextures()
	{
		if (not m_initialized)
		{
			return;
		}

		const size_t depthTextureIndex = getDepthTextureIndex();

		std::array<TextureState, 3> requiredTextureStates;

		// [0]
		{
			requiredTextureStates[0] =
			{
				.resolution = m_config.resolution,
				.isRequired = true,
				.useMSAA = m_config.useMSAA,
				.useDepth = true,
				.useMipMap = (m_config.useMipMap && (depthTextureIndex == 0)),
			};
		}

		// [1]
		{
			requiredTextureStates[1] =
			{
				.resolution = m_config.resolution,
				.isRequired = static_cast<bool>(m_config.filter),
				.useMSAA = false,
				.useDepth = false,
				.useMipMap = (m_config.useMipMap && (depthTextureIndex == 1)),
			};
		}

		// [2]
		{
			requiredTextureStates[2] =
			{
				.resolution = m_config.resolution,
				.isRequired = (m_config.filter && m_config.useMSAA),
				.useMSAA = false,
				.useDepth = false,
				.useMipMap = (m_config.useMipMap && (depthTextureIndex == 2)),
			};
		}

		for (size_t i = 0; i < 3; ++i)
		{
			if (m_currentTextureStates[i] == requiredTextureStates[i])
			{
				continue;
			}

			m_textures[i] = CreateRenderTexture(requiredTextureStates[i]);
			m_currentTextureStates[i] = requiredTextureStates[i];
		}
	}

	static std::array<float, 16> FromMat4x4(const Mat4x4& mat)
	{
		std::array<float, 16> result{};
		std::memcpy(result.data(), &mat, (sizeof(float) * 16));
		return result;
	}

	static BoxFilterSize ToBoxFilterSize(const size_t filter)
	{
		if (3 <= filter)
		{
			return BoxFilterSize::BoxFilter13x13;
		}
		else if (filter == 2)
		{
			return BoxFilterSize::BoxFilter9x9;
		}
		else
		{
			return BoxFilterSize::BoxFilter5x5;
		}
	}
};

void DrawObjects(double time)
{
	Box::FromPoints({ -8, 0, 5 }, { 0, 0.5, 7 }).draw();
	Box::FromPoints({ -0.5, 0, 5 }, { 0, 1.8, 7 }).draw();
	Box::FromPoints({ -0.5, 1.8, 5 }, { 6, 2.0, 7 }).draw();

	for (int32 x = -2; x <= 2; ++x)
	{
		Cylinder{ Vec3{ (x * 4), 0, 4 }, Vec3{ (x * 4), 4, 4 }, 0.3 }.draw(HSV{ x * 80, 0.3, 1.0 }.removeSRGBCurve());
	}

	for (int32 y = 2; y < 8; ++y)
	{
		Cylinder{ Vec3{ 0, y, -4 }, Vec3{ 4, y, -4 }, 0.1 }.draw(HSV{ 80, 0.3, 1.0 }.removeSRGBCurve());
	}

	Cylinder{ Vec3{ 0, 0, -4 }, Vec3{ 0, 8, -4 }, 0.1 }.draw(HSV{ 80, 0.3, 1.0 }.removeSRGBCurve());
	Cylinder{ Vec3{ 0, 0, -4 }, Vec3{ 0, 0.2, -4 }, 0.5 }.draw(HSV{ 80, 0.3, 1.0 }.removeSRGBCurve());
	Cylinder{ Vec3{ 4, 0, -4 }, Vec3{ 4, 8, -4 }, 0.1 }.draw(HSV{ 80, 0.3, 1.0 }.removeSRGBCurve());
	Cylinder{ Vec3{ 4, 0, -4 }, Vec3{ 4, 0.2, -4 }, 0.5 }.draw(HSV{ 80, 0.3, 1.0 }.removeSRGBCurve());
	Cylinder{ Vec3{ 8, 1.0, -5 }, Vec3{ 8, 9.0, -5 }, 0.1 }.draw(HSV{ 160, 0.3, 1.0 }.removeSRGBCurve());
	Cylinder{ Vec3{ 8, 1.0, -5 }, Vec3{ 8, 1.2, -5 }, 0.5 }.draw(HSV{ 160, 0.3, 1.0 }.removeSRGBCurve());
	Box::FromPoints({ -8, 0, -2 }, { -7, 8, 2 }).draw();
	Box::FromPoints({ -6, 0, -8 }, { -5.5, 6, -4 }).oriented(Quaternion::RotateY(-45_deg)).draw(Linear::Palette::Limegreen);
	Box::FromPoints({ 6, 0, -6 }, { 9, 1, -3 }).oriented(Quaternion::RotateY(-45_deg)).draw(Linear::Palette::Skyblue);

	const double sphereY = (2 + Periodic::Jump0_1(1.6s, time) * 4);
	Sphere{ Vec3{ 1, sphereY, 0 }, 2.0 }.draw();

	OrientedBox{ Arg::bottomCenter(6, 0, 0), { 4, 1.5, 0.2 },  Quaternion::RotateY(time * 50_deg) }.draw();
	Cylinder{ Vec3{ 6, 0, 0 }, Vec3{ 6, 2, 0 }, 0.2 }.draw(Linear::Palette::Purple);

	OrientedBox{ Vec3{ -2, 6, -6 }, 1, 8, 1, Quaternion::RollPitchYaw(0, 45_deg, time * 60_deg) }.draw(Linear::Palette::Skyblue);
	OrientedBox{ Vec3{ -2, 6, -6 }, 8, 1, 1, Quaternion::RollPitchYaw(0, 45_deg, time * 60_deg) }.draw(Linear::Palette::Skyblue);
}

void Main()
{
	Window::Resize(1280, 720);
	const ColorF backgroundColor = ColorF{ 0.4, 0.6, 0.8 }.removeSRGBCurve();
	const Texture uvChecker{ U"example/texture/uv.png", TextureDesc::MippedSRGB };
	const MSRenderTexture renderTexture{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes };
	DebugCamera3D camera{ renderTexture.size(), 30_deg, Vec3{ 10, 16, -32 } };

	// シャドウマップの設定
	ShadowMap::Config config
	{
		.resolution = Size{ 1024, 1024 },
		.lightBleedingReduction = 0.8,
		.useMSAA = false,
		.filter = 0,
		.useMipMap = false,
	};

	// シャドウマップ用の平行光源設定
	ShadowMap::Light light
	{
		.focusPos = Vec3{ 0, 0, 0 },
		.viewSize = 22.0,
	};

	// シャドウマップ
	ShadowMap shadowMap{ config };

	// シャドウマップ用のシェーダ
	const PixelShader psDepth = HLSL{ U"example/shader/hlsl/default3d_forward_shadow.hlsl", U"Depth_PS" }
		| GLSL{ U"example/shader/glsl/default3d_forward_shadow_depth.frag", {{ U"PSPerFrame", 0 }, { U"PSPerView", 1 }, { U"PSPerMaterial", 3 }, { U"PSShadow", 4 }} };
	const PixelShader psShadow = HLSL{ U"example/shader/hlsl/default3d_forward_shadow.hlsl", U"Shading_PS" }
		| GLSL{ U"example/shader/glsl/default3d_forward_shadow_shading.frag", {{ U"PSPerFrame", 0 }, { U"PSPerView", 1 }, { U"PSPerMaterial", 3 }, { U"PSShadow", 4 }} };
	if ((not psDepth) || (not psShadow))
	{
		throw Error{ U"Failed to load shader" };
	}

	size_t resolutionOption = 4;
	double time = 8.0;
	bool paused = false;
	bool showDepth = true;
	bool showUI = true;

	while (System::Update())
	{
		if (not paused)
		{
			time += Scene::DeltaTime();
		}

		camera.update(2.0);
		Graphics3D::SetCameraTransform(camera);

		// メイン光源の位置を更新する
		double halfDay0_1 = Periodic::Sawtooth0_1(60s, time);
		const Quaternion q = (Quaternion::RotateY(halfDay0_1 * 180_deg) * Quaternion::RotateX(50_deg));
		const Vec3 sunDirection = (q * Vec3::Right());
		Graphics3D::SetSunDirection(sunDirection);
		Graphics3D::SetGlobalAmbientColor(ColorF{ 0.25 });
		light.sunPos = (light.focusPos + sunDirection * 64.0);

		// デプスパス（シャドウマップの生成）
		{
			shadowMap.beginDepth(light);
			{
				const ScopedCustomShader3D shader{ psDepth };
				Plane{ 64 }.draw(); // デプスパスではテクスチャを使用しない
				DrawObjects(time);
			}
			shadowMap.endDepth();
		}

		// シャドウパス（シャドウマップを使用した描画）
		{
			const ScopedRenderTarget3D target{ renderTexture.clear(backgroundColor) };
			shadowMap.beginShadow();
			{
				const ScopedCustomShader3D shader{ psShadow };
				Plane{ 64 }.draw(uvChecker);
				DrawObjects(time);
			}
			shadowMap.endShadow();
		}

		{
			Graphics3D::Flush();
			renderTexture.resolve();
			Shader::LinearToScreen(renderTexture);
		}

		// UI
		if (showUI)
		{
			if (SimpleGUI::Slider(U"lightBleedingReduction: {:.2f}"_fmt(config.lightBleedingReduction), config.lightBleedingReduction, 0.0, 1.0, Vec2{ 860, 40 }, 280, 120))
			{
				shadowMap.setConfig(config);
			}

			if (SimpleGUI::RadioButtons(config.filter, { U"none", U"5x5", U"9x9", U"13x13" }, Vec2{ 936, 80 }, 160))
			{
				shadowMap.setConfig(config);
			}

			if (SimpleGUI::CheckBox(config.useMSAA, U"MSAA", Vec2{ 1100, 80 }, 160))
			{
				shadowMap.setConfig(config);
			}

			if (SimpleGUI::CheckBox(config.useMipMap, U"MipMap", Vec2{ 1100, 120 }, 160))
			{
				shadowMap.setConfig(config);
			}

			if (SimpleGUI::RadioButtons(resolutionOption, { U"256x256", U"256x512", U"512x512", U"512x1024", U"1024x1024", U"1024x2048", U"2048x2048", U"2048x4096", U"4096x4096" }, Vec2{ 1100, 160 }, 160))
			{
				config.resolution =
					(resolutionOption == 0) ? Size{ 256, 256 }
					: (resolutionOption == 1) ? Size{ 256, 512 }
					: (resolutionOption == 2) ? Size{ 512, 512 }
					: (resolutionOption == 3) ? Size{ 512, 1024 }
					: (resolutionOption == 4) ? Size{ 1024, 1024 }
					: (resolutionOption == 5) ? Size{ 1024, 2048 }
					: (resolutionOption == 6) ? Size{ 2048, 2048 }
					: (resolutionOption == 7) ? Size{ 2048, 4096 }
				: Size{ 4096, 4096 };
				shadowMap.setConfig(config);
			}

			SimpleGUI::CheckBox(showDepth, U"Show depth", Vec2{ 1100, 520 }, 160);
			SimpleGUI::CheckBox(paused, U"Pause", Vec2{ 1100, 560 }, 160);

			if (showDepth)
			{
				shadowMap.getDepthTexture().resized(512, 512).draw(0, 0, ColorF{ 1 / 100.0, 1 / 10000.0, 0.0 });

				PutText(U"sun {:.1f}, focus {:.1f}, {}x{}"_fmt(light.sunPos, light.focusPos,
					shadowMap.getDepthTexture().width(), shadowMap.getDepthTexture().height()), Arg::bottomRight(506, 510));

				SimpleGUI::Slider(U"viewSize: {:.1f}"_fmt(light.viewSize), light.viewSize, 4.0, 100.0, Vec2{ 180, 640 }, 150.0, 240);

				if (SimpleGUI::Button(U"←", Vec2{ 40, 600 }, 40))
				{
					light.focusPos.x -= 1.0;
				}

				if (SimpleGUI::Button(U"→", Vec2{ 120, 600 }, 40))
				{
					light.focusPos.x += 1.0;
				}

				if (SimpleGUI::Button(U"↑", Vec2{ 80, 560 }, 40))
				{
					light.focusPos.z += 1.0;
				}

				if (SimpleGUI::Button(U"↓", Vec2{ 80, 640 }, 40))
				{
					light.focusPos.z -= 1.0;
				}
			}
		}
	}
}
