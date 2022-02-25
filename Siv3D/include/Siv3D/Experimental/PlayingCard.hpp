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
// s3d::PlayingCard is originally created by Yuta Ishii (OpenSiv3D Project)
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/Transformer2D.hpp>

namespace s3d
{
	/// @brief トランプカードの描画
	namespace PlayingCard
	{
		/// @brief カードのスート（絵柄のマーク）
		enum Suit : uint16
		{
			/// @brief ♠ スペード
			Spade,

			/// @brief ♥ ハート
			Heart,

			/// @brief ♣ クラブ
			Club,

			/// @brief ♦ ダイヤ
			Diamond,

			/// @brief ジョーカー
			Joker,
		};

		/// @brief カードの番号、スート、裏表などのデータ
		struct Card
		{
			/// @brief 番号
			int32 rank;

			/// @brief スート
			Suit suit;

			/// @brief 表向きであるか
			bool isFaceSide;

			/// @brief 表向き
			static constexpr bool Front = true;

			/// @brief 裏向き
			static constexpr bool Back = false;

			/// @brief デフォルトコンストラクタ
			Card() = default;

			/// @brief カードを作成します。
			/// @param _suit スート
			/// @param _rank 番号
			/// @param _isFaceSide 表向きであるか
			constexpr Card(Suit _suit, int32 _rank, bool _isFaceSide = Card::Front) noexcept;

			/// @brief カードの裏表を反転します。
			/// @return *this
			constexpr Card& flip() noexcept;

			/// @brief カードが赤色のスート（ハートまたはダイヤ）かどうかを返します。
			/// @return カードが赤色のスートの場合 true, それ以外の場合は false	
			[[nodiscard]]
			constexpr bool isRed() const noexcept;

			/// @brief カードが黒色のスート（スペードまたはクラブ）かどうかを返します。
			/// @return カードが黒色のスートの場合 true, それ以外の場合は false	
			[[nodiscard]]
			constexpr bool isBlack() const noexcept;

			/// @brief カードのスートがスペードかどうかを返します。
			/// @return カードのスートがスペードの場合 true, それ以外の場合は false
			[[nodiscard]]
			constexpr bool isSpade() const noexcept;

			/// @brief カードのスートがハートかどうかを返します。
			/// @return カードのスートがハートの場合 true, それ以外の場合は false
			[[nodiscard]]
			constexpr bool isHeart() const noexcept;

			/// @brief カードのスートがクラブかどうかを返します。
			/// @return カードのスートがクラブの場合 true, それ以外の場合は false
			[[nodiscard]]
			constexpr bool isClub() const noexcept;

			/// @brief カードのスートがダイヤかどうかを返します。
			/// @return カードのスートがダイヤの場合 true, それ以外の場合は false
			[[nodiscard]]
			constexpr bool isDiamond() const noexcept;

			/// @brief カードがジョーカーかどうかを返します。
			/// @return カードがジョーカーの場合 true, それ以外の場合は false
			[[nodiscard]]
			constexpr bool isJoker() const noexcept;

			/// @brief カードがエース (A) かどうかを返します。
			/// @return カードがエース (A) の場合 true, それ以外の場合は false
			[[nodiscard]]
			constexpr bool isAce() const noexcept;

			/// @brief カードがジャック (J) かどうかを返します。
			/// @return カードがジャック (J) の場合 true, それ以外の場合は false
			[[nodiscard]]
			constexpr bool isJack() const noexcept;

			/// @brief カードがクイーン (Q) かどうかを返します。
			/// @return カードがクイーン (Q) の場合 true, それ以外の場合は false
			[[nodiscard]]
			constexpr bool isQueen() const noexcept;

			/// @brief カードがキング (K) かどうかを返します。
			/// @return カードがキング (K) の場合 true, それ以外の場合は false
			[[nodiscard]]
			constexpr bool isKing() const noexcept;

			/// @brief カードの数字が有効な範囲 (1-13) かどうかを返します。
			/// @return カードの数字が有効な範囲の場合 true, それ以外の場合は false
			[[nodiscard]]
			constexpr bool isValid() const noexcept;

			[[nodiscard]]
			friend constexpr bool operator ==(const Card& lhs, const Card& rhs) noexcept
			{
				return ((lhs.rank == rhs.rank)
					&& (lhs.suit == rhs.suit));
			}

			[[nodiscard]]
			friend constexpr bool operator !=(const Card& lhs, const Card& rhs) noexcept
			{
				return ((lhs.rank != rhs.rank)
					|| (lhs.suit != rhs.suit));
			}

			/// @brief スートの文字を返します。
			/// @param suit スート
			/// @return スートの文字
			[[nodiscard]]
			static constexpr char32 GetSuit(const Suit suit) noexcept;

			/// @brief 番号の文字列表現を返します。
			/// @param rank 番号
			/// @return 番号の文字列表現
			[[nodiscard]]
			static constexpr StringView GetRank(const int32 rank) noexcept;
		};

		/// @brief カードの描画用の情報
		struct CardInfo
		{
		public:

			/// @brief デフォルトコンストラクタ
			CardInfo() = default;

			/// @brief カードの情報を作成します。
			/// @param card カード
			/// @param font 描画に使用するフォント
			/// @param fontLarge 描画に使用するフォント
			/// @param size カードの大きさ
			/// @param frameThickness 枠の太さ
			/// @param backSideColor 裏面の色
			CardInfo(const Card& card, const Font& font, const Font& fontLarge, const Font& fontEmoji, const Vec2& size, double frameThickness, const ColorF& backSideColor);

			/// @brief カードの裏面を描画します。
			/// @param pos カードの左上の座標
			void drawBack(const Vec2& pos) const;

			/// @brief カードの裏面を描画します。
			/// @param x カードの左上の X 座標
			/// @param y カードの左上の Y 座標
			void drawBack(double x, double y) const;

			/// @brief カードの裏面を描画します。
			/// @param pos カードの左上の座標
			/// @param angle カードの時計回りの回転
			void drawBack(const Vec2& pos, double angle) const;

			/// @brief カードの裏面を描画します。
			/// @param x カードの左上の X 座標
			/// @param y カードの左上の Y 座標
			/// @param angle カードの時計回りの回転
			void drawBack(double x, double y, double angle) const;

			/// @brief 中心座標を指定してカードの裏面を描画します。
			/// @param center カードの中心の座標
			void drawBackAt(const Vec2& center) const;

			/// @brief 中心座標を指定してカードの裏面を描画します。
			/// @param x カードの左上の X 座標
			/// @param y カードの左上の Y 座標
			void drawBackAt(double x, double y) const;

			/// @brief 中心座標を指定してカードの裏面を描画します。
			/// @param center カードの中心の座標
			/// @param angle カードの時計回りの回転
			void drawBackAt(const Vec2& center, double angle) const;

			/// @brief 中心座標を指定してカードの裏面を描画します。
			/// @param x カードの中心の X 座標
			/// @param y カードの中心の Y 座標
			/// @param angle カードの時計回りの回転
			void drawBackAt(double x, double y, double angle) const;

			/// @brief カードを描画します。
			/// @param pos カードの左上の座標
			void draw(const Vec2& pos) const;

			/// @brief カードを描画します。
			/// @param x カードの左上の X 座標
			/// @param y カードの左上の Y 座標
			void draw(double x, double y) const;

			/// @brief カードを描画します。
			/// @param pos カードの左上の座標
			/// @param angle カードの時計回りの回転
			void draw(const Vec2& pos, double angle) const;

			/// @brief カードを描画します。
			/// @param x カードの左上の X 座標
			/// @param y カードの左上の Y 座標
			/// @param angle カードの時計回りの回転
			void draw(double x, double y, double angle) const;

			/// @brief 中心座標を指定してカードを描画します。
			/// @param center カードの中心の座標
			void drawAt(const Vec2& center) const;

			/// @brief 中心座標を指定してカードを描画します。
			/// @param x カードの中心の X 座標
			/// @param y カードの中心の Y 座標
			void drawAt(double x, double y) const;

			/// @brief 中心座標を指定してカードを描画します。
			/// @param center カードの中心の座標
			/// @param angle カードの時計回りの回転
			void drawAt(const Vec2& center, double angle) const;

			/// @brief 中心座標を指定してカードを描画します。
			/// @param x カードの中心の X 座標
			/// @param y カードの中心の Y 座標
			/// @param angle カードの時計回りの回転
			void drawAt(double x, double y, double angle) const;

			/// @brief シンプルなデザインでカードを描画します。
			/// @param pos カードの左上の座標
			void drawSimple(const Vec2& pos) const;

			/// @brief シンプルなデザインでカードを描画します。
			/// @param x カードの左上の X 座標
			/// @param y カードの左上の Y 座標
			void drawSimple(double x, double y) const;

			/// @brief シンプルなデザインでカードを描画します。
			/// @param pos カードの左上の座標
			/// @param angle カードの時計回りの回転
			void drawSimple(const Vec2& pos, double angle) const;

			/// @brief シンプルなデザインでカードを描画します。
			/// @param x カードの左上の X 座標
			/// @param y カードの左上の Y 座標
			/// @param angle カードの時計回りの回転
			void drawSimple(double x, double y, double angle) const;

			/// @brief 中心座標を指定してシンプルなデザインでカードを描画します。
			/// @param center カードの中心の座標
			void drawSimpleAt(const Vec2& center) const;

			/// @brief 中心座標を指定してシンプルなデザインでカードを描画します。
			/// @param x カードの中心の X 座標
			/// @param y カードの中心の Y 座標
			void drawSimpleAt(double x, double y) const;

			/// @brief 中心座標を指定してシンプルなデザインでカードを描画します。
			/// @param center カードの中心の座標
			/// @param angle カードの時計回りの回転
			void drawSimpleAt(const Vec2& center, double angle) const;

			/// @brief 中心座標を指定してシンプルなデザインでカードを描画します。
			/// @param x カードの中心の X 座標
			/// @param y カードの中心の Y 座標
			/// @param angle カードの時計回りの回転
			void drawSimpleAt(double x, double y, double angle) const;

		private:

			static constexpr double corner = 0.045;

			Card m_card;

			Font m_font;

			Font m_fontLarge;

			Font m_fontEmoji;

			Vec2 m_cardSize;

			ColorF m_backSideColor;

			double m_frameThickness;

			struct DrawInfo
			{
				bool flip;

				Vec2 offset;
			};
		};

		/// @brief カードに用いるフォントの大きさを計算します。
		/// @param cardWidth カードの幅（ピクセル）
		/// @return カードに用いるフォントの大きさ
		[[nodiscard]]
		inline constexpr int32 CalculateFontSize(double cardWidth) noexcept;

		/// @brief カードを作成するクラス
		class Pack
		{
		public:

			/// @brief デフォルトコンストラクタ
			Pack() = default;

			/// @brief カードを扱うための構造体を作成します。
			/// @param font 小さいフォント
			/// @param fontLarge 大きいフォント
			/// @param fontEmoji 絵文字フォント
			/// @param cardWidth カードの幅（ピクセル）
			/// @param backSideColor カード背面の色
			/// @param frameThickness カードの枠の太さ
			/// @remark フォントの大きさは `PlayingCard::CalculateFontSize()` を使って計算します。
			explicit Pack(const Font& font, const Font& fontLarge, const Font& fontEmoji, double cardWidth = 50, const ColorF& backSideColor = Palette::Blue, double frameThickness = 1.0);

			/// @brief カードを扱うための構造体を作成します。
			/// @param cardWidth カードの幅（ピクセル）
			/// @param backSideColor カード背面の色
			/// @param frameThickness カードの枠の太さ
			explicit Pack(double cardWidth, const ColorF& backSideColor = Palette::Blue, double frameThickness = 1.0);

			/// @brief カードの描画用の情報を作成します。
			/// @param suit カードのスート
			/// @param rank カードの数字
			/// @param isFaceSide カードが表面かどうか
			/// @return カードの描画用の情報
			[[nodiscard]]
			CardInfo operator ()(Suit suit, int32 rank = 1, bool isFaceSide = Card::Front) const;

			/// @brief カードの描画用の情報を作成します。
			/// @param card カード
			/// @return カードの描画用の情報
			[[nodiscard]]
			CardInfo operator ()(const Card& card) const;

			/// @brief カードの大きさ（ピクセル）を返します。
			/// @return カードの大きさ（ピクセル）
			[[nodiscard]]
			Vec2 size() const noexcept;

			/// @brief カードの幅（ピクセル）を返します。
			/// @return カードの幅（ピクセル）
			[[nodiscard]]
			double width() const noexcept;

			/// @brief カードの高さ（ピクセル）を返します。
			/// @return カードの高さ（ピクセル）
			[[nodiscard]]
			double height() const noexcept;

			/// @brief カードの領域を返します。
			/// @param pos カードの左上の座標
			/// @return カードの領域
			[[nodiscard]]
			RectF region(const Vec2& pos) const;

			/// @brief カードの領域を返します。
			/// @param pos カードの左上の座標
			/// @param angle カードの時計回りの回転
			/// @return カードの領域
			[[nodiscard]]
			Quad region(const Vec2& pos, double angle) const;

			/// @brief カードの領域を返します。
			/// @param center カードの中心の座標
			/// @return カードの領域
			[[nodiscard]]
			RectF regionAt(const Vec2& center) const;

			/// @brief カードの領域を返します。
			/// @param center カードの中心の座標
			/// @param angle カードの時計回りの回転
			/// @return カードの領域
			[[nodiscard]]
			Quad regionAt(const Vec2& center, double angle) const;

		private:

			Font m_font;

			Font m_fontLarge;

			Font m_fontEmoji;

			Vec2 m_cardSize = { 0, 0 };

			ColorF m_backSideColor = Palette::Blue;

			double m_framethickness = 0.0;
		};

		/// @brief カードの山札を作ります。
		/// @param num_jokers ジョーカーの枚数
		/// @param isFaceSide 各カードの裏表の初期状態
		/// @remark ジョーカーは配列の最後に加えられます。
		/// @remark シャッフルしたい場合は、取得後に shuffle() します。
		/// @return カードの山札		
		[[nodiscard]]
		inline Array<Card> CreateDeck(size_t num_jokers = 0, bool isFaceSide = Card::Front);
	}
}

# include "detail/PlayingCard.ipp"

/*

// example

# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);
	Scene::SetBackground(Palette::Darkgreen);

	const PlayingCard::Pack pack{ 75, Palette::Red };
	Array<PlayingCard::Card> cards = PlayingCard::CreateDeck(2);

	while (System::Update())
	{
		for (auto i : step(13 * 4 + 2))
		{
			const Vec2 center{ 100 + i % 13 * 90, 100 + (i / 13) * 130 };

			if (pack.regionAt(center).mouseOver())
			{
				Cursor::RequestStyle(CursorStyle::Hand);

				if (MouseL.down())
				{
					cards[i].flip();
				}
			}

			pack(cards[i]).drawAt(center);
		}
	}
}

*/
