/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"

class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

TEST(PiezasTest, boundries)
{
  Piezas game;
  game.reset();
  ASSERT_TRUE(game.dropPiece(5) == Invalid);
}

TEST(PiezasTest, full_col)
{
  Piezas game;
  game.reset();
  game.dropPiece(0);
  game.dropPiece(0);
  game.dropPiece(0);
  ASSERT_TRUE((game.dropPiece(0) == Blank));
}

  TEST(PiezasTest, place_one)
  {
    Piezas game;
    game.reset();
    ASSERT_TRUE(game.dropPiece(0) == X);
}

TEST(PiezasTest, piece_boundry)
{
  Piezas game;
  ASSERT_TRUE(game.pieceAt(18, 24) == Invalid);
}

TEST(PiezasTest, piece_same)
{
  Piezas game;
  game.reset();
  ASSERT_TRUE(game.pieceAt(0, 0) == Blank);
}

TEST(PiezasTest, piece_get_false)
{
  Piezas game;
  game.reset();
  game.dropPiece(0);
  ASSERT_FALSE(game.pieceAt(0, 0) == Blank);
}

TEST(PiezasTest, piece_get)
{
  Piezas game;
  game.reset();
  game.dropPiece(0);
  ASSERT_TRUE(game.pieceAt(0, 0) == X);
}

TEST(PiezasTest, gamestate_invalid)
{
  Piezas game;
  game.reset();
  ASSERT_TRUE(game.gameState() == Invalid);
}

TEST(PiezasTest, gamestate_tie)
{
  Piezas game;
  game.reset();
  game.dropPiece(0);
  game.dropPiece(1);
  game.dropPiece(2);
  game.dropPiece(3);

  game.dropPiece(0);
  game.dropPiece(1);
  game.dropPiece(2);
  game.dropPiece(3);

  game.dropPiece(0);
  game.dropPiece(1);
  game.dropPiece(2);
  game.dropPiece(3);

  ASSERT_TRUE(game.gameState() == Blank);
}

TEST(PiezasTest, gamestate_win)
{
  Piezas game;
  game.reset();
  game.dropPiece(0);
  game.dropPiece(0);
  game.dropPiece(1);
  game.dropPiece(3);

  game.dropPiece(2);
  game.dropPiece(3);
  game.dropPiece(1);
  game.dropPiece(2);

  game.dropPiece(1);
  game.dropPiece(0);
  game.dropPiece(3);
  game.dropPiece(2);

  ASSERT_TRUE(game.gameState() == X);
}
