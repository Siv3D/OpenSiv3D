//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
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
		private:

			static constexpr double corner = 0.045;

			Card m_card;

			Font m_font;

			Font m_fontLarge;

			Vec2 m_cardSize;

			ColorF m_backSideColor;

			double m_frameThickness;

			struct DrawInfo
			{
				bool flip;

				Vec2 offset;
			};

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
			CardInfo(const Card& card, const Font& font, const Font& fontLarge, const Vec2& size, double frameThickness, const ColorF& backSideColor)
				: m_card{ card }
				, m_font{ font }
				, m_fontLarge{ fontLarge }
				, m_cardSize{ size }
				, m_backSideColor{ backSideColor }
				, m_frameThickness{ frameThickness }
			{
				assert(card.isValid());
			}

			/// @brief カードの裏面を描画します。
			/// @param pos カードの左上の座標
			void drawBack(const Vec2& pos) const
			{
				RoundRect{ pos, m_cardSize, (m_cardSize.x * corner) }
					.draw()
					.drawFrame(0.0, m_frameThickness, Palette::Black)
					.rect.stretched(m_cardSize.x * -0.1).draw(m_backSideColor);
			}

			void drawBack(double x, double y) const
			{
				drawBack(Vec2{ x, y });
			}

			/// @brief カードの裏面を描画します。
			/// @param pos カードの左上の座標
			/// @param angle カードの時計回りの回転
			void drawBack(const Vec2& pos, double angle) const
			{
				const Transformer2D transformer{ Mat3x2::Rotate(angle, (pos + m_cardSize / 2)) };

				drawBack(pos);
			}

			void drawBack(double x, double y, double angle) const
			{
				drawBack(Vec2{ x, y }, angle);
			}

			/// @brief 中心座標を指定してカードの裏面を描画します。
			/// @param center カードの中心の座標
			void drawBackAt(const Vec2& center) const
			{
				drawBack(center - m_cardSize * 0.5);
			}

			void drawBackAt(double x, double y) const
			{
				drawBackAt(Vec2{ x, y });
			}

			/// @brief 中心座標を指定してカードの裏面を描画します。
			/// @param center カードの中心の座標
			/// @param angle カードの時計回りの回転
			void drawBackAt(const Vec2& center, double angle) const
			{
				const Transformer2D transformer{ Mat3x2::Rotate(angle, center) };

				drawBackAt(center);
			}

			void drawBackAt(double x, double y, double angle) const
			{
				drawBackAt(Vec2{ x, y }, angle);
			}

			/// @brief カードを描画します。
			/// @param pos カードの左上の座標
			void draw(const Vec2& pos) const
			{
				if (not m_card.isFaceSide)
				{
					return drawBack(pos);
				}

				static const std::array<Array<DrawInfo>, 9> drawInfos =
				{ {
					{	// 2
						DrawInfo{ false, Vec2{ 0.0,-1.0 / 3.0 } },
						DrawInfo{ true, Vec2{ 0.0,1.0 / 3.0 } }
					},

					{	// 3
						DrawInfo{ false, Vec2{ 0.0,0.0 } },
						DrawInfo{ false, Vec2{ 0.0,-1.0 / 3.0 } },
						DrawInfo{ true, Vec2{ 0.0,1.0 / 3.0 } }
					},

					{	// 4
						DrawInfo{ false, Vec2{ 0.2,-1.0 / 3.0 } },
						DrawInfo{ true, Vec2{ -0.2,1.0 / 3.0 } },
						DrawInfo{ true, Vec2{ 0.2,1.0 / 3.0 } },
						DrawInfo{ false, Vec2{ -0.2,-1.0 / 3.0 } }
					},

					{	// 5
						DrawInfo{ false, Vec2{ 0.2,-1.0 / 3.0 } },
						DrawInfo{ true, Vec2{ -0.2,1.0 / 3.0 } },
						DrawInfo{ true, Vec2{ 0.2,1.0 / 3.0 } },
						DrawInfo{ false, Vec2{ -0.2,-1.0 / 3.0 } },
						DrawInfo{ false, Vec2{ 0.0,0.0 } }
					},

					{	// 5
						DrawInfo{ false, Vec2{ -0.2, -1.0 / 3.0 } },
						DrawInfo{ false, Vec2{ 0.2, -1.0 / 3.0 } },
						DrawInfo{ false, Vec2{ -0.2, 0.0 } },
						DrawInfo{ false, Vec2{ 0.2, 0.0 } },
						DrawInfo{ true, Vec2{ -0.2, 1.0 / 3.0 } },
						DrawInfo{ true, Vec2{ 0.2, 1.0 / 3.0 } },
					},

					{	// 6
						DrawInfo{ false, Vec2{ -0.2, -1.0 / 3.0 } },
						DrawInfo{ false, Vec2{ 0.2, -1.0 / 3.0 } },
						DrawInfo{ false, Vec2{ -0.2, 0.0 } },
						DrawInfo{ false, Vec2{ 0.2, 0.0 } },
						DrawInfo{ true, Vec2{ -0.2, 1.0 / 3.0 } },
						DrawInfo{ true, Vec2{ 0.2, 1.0 / 3.0 } },
						DrawInfo{ false, Vec2{ 0.0, -1.0 / 6.0 } },
					},

					{	// 7
						DrawInfo{ false, Vec2{ -0.2, -1.0 / 3.0 } },
						DrawInfo{ false, Vec2{ 0.2, -1.0 / 3.0 } },
						DrawInfo{ false, Vec2{ -0.2, 0.0 } },
						DrawInfo{ false, Vec2{ 0.2, 0.0 } },
						DrawInfo{ true, Vec2{ -0.2, 1.0 / 3.0 } },
						DrawInfo{ true, Vec2{ 0.2, 1.0 / 3.0 } },
						DrawInfo{ false, Vec2{ 0.0, -1.0 / 6.0 } },
						DrawInfo{ true, Vec2{ 0.0, 1.0 / 6.0 } },
					},

					{	// 8
						DrawInfo{ false, Vec2{ -0.2, -1.0 / 3.0 } },
						DrawInfo{ false, Vec2{ 0.2, -1.0 / 3.0 } },
						DrawInfo{ true, Vec2{ -0.2, 1.0 / 3.0 } },
						DrawInfo{ true, Vec2{ 0.2, 1.0 / 3.0 } },
						DrawInfo{ false, Vec2{ -0.2, -1.0 / 9.0 } },
						DrawInfo{ false, Vec2{ 0.2, -1.0 / 9.0 } },
						DrawInfo{ true, Vec2{ -0.2, 1.0 / 9.0 } },
						DrawInfo{ true, Vec2{ 0.2, 1.0 / 9.0 } },
						DrawInfo{ false, Vec2{ 0.0, 0.0 } },
					},

					{	// 9
						DrawInfo{ false, Vec2{ -0.2, -1.0 / 3.0 } },
						DrawInfo{ false, Vec2{ 0.2, -1.0 / 3.0 } },
						DrawInfo{ true, Vec2{ -0.2, 1.0 / 3.0 } },
						DrawInfo{ true, Vec2{ 0.2, 1.0 / 3.0 } },
						DrawInfo{ false, Vec2{ -0.2, -1.0 / 9.0 } },
						DrawInfo{ false, Vec2{ 0.2, -1.0 / 9.0 } },
						DrawInfo{ true, Vec2{ -0.2, 1.0 / 9.0 } },
						DrawInfo{ true, Vec2{ 0.2, 1.0 / 9.0 } },
						DrawInfo{ false, Vec2{ 0.0, -1.0 / 4.5 } },
						DrawInfo{ true, Vec2{ 0.0, 1.0 / 4.5 } }
					},
				} };

				const Vec2 center = (pos + m_cardSize * 0.5);
				const Vec2 centering = (m_cardSize * 0.1);
				const double drawSize = (0.34 / 0.467);
				const ColorF color = (m_card.isRed() ? Palette::Red : Palette::Black);

				RoundRect{ pos, m_cardSize, (m_cardSize.x * corner) }
					.draw()
					.drawFrame(0, m_frameThickness, Palette::Black);

				if (m_card.isJoker())
				{
					/*
					const Array<Glyph> glyphs = m_font.getGlyphs(U"JOKER");
					const double height = glyphs[0].texture.size.y * drawSize * 1.08;
					const Vec2 drawpos(centering / 10 + Vec2(glyphs[0].texture.resized(Vec2(glyphs[0].texture.size) * drawSize).size.x, height * 0.5));

					for (const auto a : step(glyphs.size()))
					{
						const TextureRegion t = glyphs[a].texture.resized(Vec2(glyphs[0].texture.size) * drawSize);
						t.drawAt(pos + drawpos + Vec2(0, a * height * 1.2), color);
						t.flipped().mirrored().drawAt(pos - drawpos - Vec2(0, a * height * 1.2) + m_cardSize, color);
					}

					m_fontLarge.getGlyph(U'♋').texture.scaled(0.9).drawAt(center, color);
					*/
					return;
				}

				/*
				const Glyph suitGlyph = m_font.getGlyph(Card::GetSuit(m_card.suit));
				const Glyph rankGlyph = m_font.getGlyph(Card::GetRank(m_card.rank)[0]);
				const Vec2 suitpos(0.0, m_cardSize.y * 0.13888);

				suitGlyph.texture.scaled(drawSize).drawAt(pos.movedBy(centering + suitpos), color);
				suitGlyph.texture.scaled(drawSize).flipped().mirrored().drawAt(pos + m_cardSize - centering - suitpos, color);

				if (m_card.rank == 10)
				{
					const auto zerotexture = m_font.getGlyph(U'0');
					const Vec2 rankSize = Vec2(rankGlyph.texture.size.x * 2.2 / 3.0, rankGlyph.texture.size.y) * drawSize;

					rankGlyph.texture.resized(rankSize)
						.drawAt(pos + centering - Vec2(rankSize.x * 1.1, 0), color);
					rankGlyph.texture.resized(rankSize)
						.flipped().mirrored()
						.drawAt(pos + m_cardSize - centering + Vec2(rankSize.x * 1.1, 0), color);

					zerotexture.texture.scaled(drawSize * 0.8, drawSize)
						.drawAt(pos + centering + Vec2(rankGlyph.texture.size.x * drawSize - rankSize.x / 1.55, 0), color);
					zerotexture.texture.scaled(drawSize * 0.8, drawSize)
						.flipped().mirrored()
						.drawAt(pos - centering + Vec2(-rankGlyph.texture.size.x * drawSize + rankSize.x / 1.55, 0) + m_cardSize, color);
				}
				else
				{
					rankGlyph.texture.scaled(drawSize).drawAt(pos + centering, color);
					rankGlyph.texture.scaled(drawSize).flipped().mirrored().drawAt(pos + m_cardSize - centering, color);
				}

				if (InRange(m_card.rank, 2, 10))
				{
					for (const auto a : drawInfos[m_card.rank - 2])
					{
						suitGlyph.texture.flipped(a.flip).drawAt(center.movedBy(m_cardSize.x * a.offset.x, m_cardSize.y * a.offset.y), color);
					}
				}
				else
				{
					const char32 c[4] = { static_cast<char32>(Card::GetSuit(m_card.suit)), U'\x1f482', U'\x1f478', U'\x1f474' };

					m_fontLarge.getGlyph(c[(m_card.rank - 1) % 9 % 4]).texture.drawAt(center.movedBy(m_card.rank == 13 ? Vec2(0, m_cardSize.y / 12 - m_cardSize.y / 21) : Vec2::Zero()), color);

					if (m_card.isKing())
					{
						m_fontLarge.getGlyph(U'\x1f451').texture.scaled(0.6).drawAt(center.movedBy(0, -m_cardSize.y / 7 - m_cardSize.y / 21), color);
					}
				}
				*/
			}

			void draw(double x, double y) const
			{
				draw(Vec2{ x, y });
			}

			/// @brief カードを描画します。
			/// @param pos カードの左上の座標
			/// @param angle カードの時計回りの回転
			void draw(const Vec2& pos, double angle) const
			{
				const Transformer2D transformer{ Mat3x2::Rotate(angle, pos + m_cardSize / 2) };

				draw(pos);
			}

			void draw(double x, double y, double angle) const
			{
				draw(Vec2{ x, y }, angle);
			}

			/// @brief 中心座標を指定してカードを描画します。
			/// @param center カードの中心の座標
			void drawAt(const Vec2& center) const
			{
				draw(center - m_cardSize * 0.5);
			}

			void drawAt(double x, double y) const
			{
				drawAt(Vec2{ x, y });
			}

			/// @brief 中心座標を指定してカードを描画します。
			/// @param center カードの中心の座標
			/// @param angle カードの時計回りの回転
			void drawAt(const Vec2& center, double angle) const
			{
				const Transformer2D transformer{ Mat3x2::Rotate(angle, center) };

				draw(center - m_cardSize * 0.5);
			}

			void drawAt(double x, double y, double angle) const
			{
				drawAt(Vec2{ x, y }, angle);
			}

			/// @brief シンプルなデザインの描画を行います。
			/// @param pos カードの左上の座標
			void drawSimple(const Vec2& pos) const
			{
				if (m_card.isFaceSide)
				{
					const RectF rect{ pos, m_cardSize };
					RoundRect{ rect, rect.w * corner }
						.draw()
						.drawFrame(m_frameThickness, Palette::Black);

					if (not m_card.isJoker())
					{
						const ColorF color = (m_card.isRed() ? Palette::Red : Palette::Black);
						const char32 suit = Card::GetSuit(m_card.suit);
						const StringView rank = Card::GetRank(m_card.rank);

						m_fontLarge(suit).drawAt(pos.movedBy(m_cardSize.x * 0.5, m_cardSize.y * 0.3), color);
						m_fontLarge(rank).drawAt(pos.movedBy(m_cardSize.x * 0.5, m_cardSize.y * 0.67), color);
					}
					else
					{
						//m_fontLarge.getGlyph(U'♋').texture.scaled(0.9).drawAt(rect.center(), Palette::Black);
					}
				}
				else
				{
					drawBack(pos);
				}
			}

			void drawSimple(double x, double y) const
			{
				drawSimple(Vec2{ x, y });
			}

			/// @brief シンプルなデザインの描画を行います。
			/// @param pos カードの左上の座標
			/// @param angle カードの時計回りの回転
			void drawSimple(const Vec2& pos, double angle) const
			{
				const Transformer2D transformer{ Mat3x2::Rotate(angle, pos + m_cardSize / 2) };

				drawSimple(pos);
			}

			void drawSimple(double x, double y, double angle) const
			{
				drawSimple(Vec2{ x, y }, angle);
			}

			/// @brief 中心座標を指定してシンプルなデザインの描画を行います。
			/// @param center カードの中心の座標
			void drawSimpleAt(const Vec2& center) const
			{
				drawSimple(center - m_cardSize * 0.5);
			}

			void drawSimpleAt(double x, double y) const
			{
				drawSimpleAt(Vec2{ x, y });
			}

			/// @brief 中心座標を指定してシンプルなデザインの描画を行います。
			/// @param center カードの中心の座標
			/// @param angle カードの時計回りの回転
			void drawSimpleAt(const Vec2& center, double angle) const
			{
				const Transformer2D transformer{ Mat3x2::Rotate(angle, center) };

				drawSimple(center - m_cardSize * 0.5);
			}

			void drawSimpleAt(double x, double y, double angle) const
			{
				drawSimpleAt(Vec2{ x, y }, angle);
			}
		};

		/// @brief カードに用いるフォントの大きさを計算します。
		/// @param cardWidth カードの幅（ピクセル）
		/// @return カードに用いるフォントの大きさ
		[[nodiscard]]
		constexpr inline int32 CalculateFontSize(double cardWidth) noexcept
		{
			return Max(static_cast<int32>(cardWidth * (2.0 / 3.0)), 1);
		}

		/// @brief カードを作成するクラス
		class Pack
		{
		private:

			Font m_font;

			Font m_fontLarge;

			Vec2 m_cardSize = { 0, 0 };

			ColorF m_backSideColor = Palette::Blue;

			double m_framethickness = 0.0;

		public:

			/// @brief デフォルトコンストラクタ
			Pack() = default;

			/// @brief カードを扱うための構造体を作成します。
			/// @param font 小さいフォント
			/// @param fontLarge 大きいフォント
			/// @param cardWidth カードの幅（ピクセル）
			/// @param backSideColor カード背面の色
			/// @param frameThickness カードの枠の太さ
			/// @remark フォントの大きさは `PlayingCard::CalculateFontSize()` を使って計算します。
			explicit Pack(const Font& font, const Font& fontLarge, double cardWidth = 50, const ColorF& backSideColor = Palette::Blue, double frameThickness = 1.0)
				: m_font{ font }
				, m_fontLarge{ fontLarge }
				, m_cardSize{ cardWidth, cardWidth * Math::Phi }
				, m_backSideColor{ backSideColor }
				, m_framethickness{ frameThickness } {}

			/// @brief カードを扱うための構造体を作成します。
			/// @param cardWidth カードの幅（ピクセル）
			/// @param backSideColor カード背面の色
			/// @param frameThickness カードの枠の太さ
			explicit Pack(double cardWidth, const ColorF& backSideColor = Palette::Blue, double frameThickness = 1.0)
				: m_font{ CalculateFontSize(cardWidth * 0.475) }
				, m_fontLarge{ CalculateFontSize(cardWidth) }
				, m_cardSize{ cardWidth, cardWidth * Math::Phi }
				, m_backSideColor{ backSideColor }
				, m_framethickness{ frameThickness } {}

			/// @brief カードの描画用の情報を作成します。
			/// @param suit カードのスート
			/// @param rank カードの数字
			/// @param isFaceSide カードが表面かどうか
			/// @return カードの描画用の情報
			[[nodiscard]]
			CardInfo operator ()(Suit suit, int32 rank = 1, bool isFaceSide = Card::Front) const
			{
				return operator()(Card{ suit, rank, isFaceSide });
			}

			/// @brief カードの描画用の情報を作成します。
			/// @param card カード
			/// @return カードの描画用の情報
			[[nodiscard]]
			CardInfo operator ()(const Card& card) const
			{
				return CardInfo{ card, m_font, m_fontLarge, m_cardSize, m_framethickness, m_backSideColor };
			}

			/// @brief カードの大きさ（ピクセル）を返します。
			/// @return カードの大きさ（ピクセル）
			[[nodiscard]]
			Vec2 size() const noexcept
			{
				return m_cardSize;
			}

			/// @brief カードの幅（ピクセル）を返します。
			/// @return カードの幅（ピクセル）
			[[nodiscard]]
			double width() const noexcept
			{
				return m_cardSize.x;
			}

			/// @brief カードの高さ（ピクセル）を返します。
			/// @return カードの高さ（ピクセル）
			[[nodiscard]]
			double height() const noexcept
			{
				return m_cardSize.y;
			}

			/// @brief カードの領域を返します。
			/// @param pos カードの左上の座標
			/// @return カードの領域
			[[nodiscard]]
			RectF region(const Vec2& pos) const
			{
				return{ pos, m_cardSize };
			}

			/// @brief カードの領域を返します。
			/// @param pos カードの左上の座標
			/// @param angle カードの時計回りの回転
			/// @return カードの領域
			[[nodiscard]]
			Quad region(const Vec2& pos, double angle) const
			{
				return RectF{ pos, m_cardSize }.rotated(angle);
			}

			/// @brief カードの領域を返します。
			/// @param center カードの中心の座標
			/// @return カードの領域
			[[nodiscard]]
			RectF regionAt(const Vec2& center) const
			{
				return{ Arg::center = center, m_cardSize };
			}

			/// @brief カードの領域を返します。
			/// @param center カードの中心の座標
			/// @param angle カードの時計回りの回転
			/// @return カードの領域
			[[nodiscard]]
			Quad regionAt(const Vec2& center, double angle) const
			{
				return RectF{ Arg::center = center, m_cardSize }.rotated(angle);
			}
		};

		/// @brief カードの山札を作ります。
		/// @param num_jokers ジョーカーの枚数
		/// @param isFaceSide 各カードの裏表の初期状態
		/// @remark ジョーカーは配列の最後に加えられます。
		/// @remark シャッフルしたい場合は、取得後に shuffle() します。
		/// @return カードの山札		
		[[nodiscard]]
		inline Array<Card> CreateDeck(size_t num_jokers = 0, bool isFaceSide = Card::Front)
		{
			Array<Card> cards(Arg::reserve = (13 * 4 + num_jokers));
			{
				for (uint16 suit = 0; suit < 4; ++suit)
				{
					for (int32 i = 1; i <= 13; ++i)
					{
						cards.emplace_back(static_cast<Suit>(suit), i, isFaceSide);
					}
				}

				cards.insert(cards.end(), num_jokers, Card{ Suit::Joker, 0, isFaceSide });
			}

			return cards;
		}
	}
}

# include "detail/PlayingCard.ipp"

/*

// example



*/
