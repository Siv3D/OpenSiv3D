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
# include "Array.hpp"
# include "ModelObject.hpp"
# include "Material.hpp"
# include "AssetHandle.hpp"
# include "StringView.hpp"
# include "ColorOption.hpp"
# include "TextureDesc.hpp"
# include "TextureAsset.hpp"

namespace s3d
{
	/// @brief 3D モデル
	class Model : public AssetHandle<Model>
	{
	public:

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		Model();

		/// @brief 3D モデルを読み込みます。
		/// @param path ファイルのパス（対応している形式は Wavefront OBJ）
		/// @param colorOption 色空間
		SIV3D_NODISCARD_CXX20
		explicit Model(FilePathView path, ColorOption colorOption = ColorOption::Default);

		/// @brief デストラクタ
		virtual ~Model();

		/// @brief 3D モデルを構成するモデルパーツ一覧を返します。
		/// @return 3D モデルを構成するモデルパーツ一覧
		[[nodiscard]]
		const Array<ModelObject>& objects() const noexcept;

		/// @brief 3D モデルに登録されているマテリアル一覧を返します。
		/// @return 3D モデルに登録されているマテリアル一覧
		[[nodiscard]]
		const Array<Material>& materials() const noexcept;

		/// @brief 3D モデルに登録されているディフューズテクスチャの名前（パス）を返します。
		/// @return 3D モデルに登録されているディフューズテクスチャの名前（パス）一覧
		[[nodiscard]]
		Array<String> diffuseTextureNames() const;

		/// @brief 3D モデルのバウンディングスフィアを返します。
		/// @remark バウンディングスフィアは計算済みであるため、この関数のコストは小さいです。
		/// @return 3D モデルのバウンディングスフィア
		[[nodiscard]]
		const Sphere& boundingSphere() const noexcept;

		/// @brief 3D モデルのバウンディングボックスを返します。
		/// @remark バウンディングボックスは計算済みであるため、この関数のコストは小さいです。
		/// @return 3D モデルのバウンディングボックス
		[[nodiscard]]
		const Box& boundingBox() const noexcept;

		/// @brief 3D モデルを描画します。
		void draw() const;

		/// @brief 3D モデルを描画します。
		/// @param x ワールドの X 座標
		/// @param y ワールドの Y 座標
		/// @param z ワールドの Z 座標
		void draw(double x, double y, double z) const;
		
		/// @brief 3D モデルを描画します。
		/// @param pos ワールドの座標
		void draw(const Vec3& pos) const;

		/// @brief 3D モデルを描画します。
		/// @param x ワールドの X 座標
		/// @param y ワールドの Y 座標
		/// @param z ワールドの Z 座標
		/// @param rotation 回転
		void draw(double x, double y, double z, const Quaternion& rotation) const;

		/// @brief 3D モデルを描画します。
		/// @param pos ワールドの座標
		/// @param rotation 回転
		void draw(const Vec3& pos, const Quaternion& rotation) const;

		/// @brief 3D モデルを描画します。
		/// @param mat 座標変換行列
		void draw(const Mat4x4& mat) const;

		/// @brief 別の 3D モデルと中身を交換します。
		/// @param other 別の 3D モデル
		void swap(Model& other) noexcept;

		/// @brief 3D モデルに含まれるテクスチャ情報をもとに、テクスチャアセットを登録します。
		/// @param model 3D モデル
		/// @param textureDesc テクスチャの設定
		/// @return テクスチャアセットの登録に成功した場合 true, それ以外の場合は false
		static bool RegisterDiffuseTextures(const Model& model, TextureDesc textureDesc = TextureDesc::MippedSRGB);
	};
}

template <>
inline void std::swap(s3d::Model& a, s3d::Model& b) noexcept;

# include "detail/Model.ipp"
