#include "../src/Core/DataTypes/Vector2D.h"
#include <gtest/gtest.h>

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

namespace TGEngine::test {
  class Vector2DTest : public Vector2D {
  public:
    float x, y;
  };
}

using namespace TGEngine::test;

TEST(Vector2D, VectorConstructorTest) {
    Vector2DTest vector1;
    vector1.setX(0.5f);
    vector1.setY(0.5f);
    Vector2D vector2(0.5f, 0.5f);
    EXPECT_EQ(vector1.x, vector2.getX());
    EXPECT_EQ(vector1.y, vector2.getY());
}

TEST(Vector2D, VectorZeroTest) {
    Vector2D vector1(0, 0);
    Vector2D vector2;
    vector2.Zero();
    EXPECT_EQ(vector1.x ,vector2.x);
    EXPECT_EQ(vector1.y ,vector2.y);
}

TEST(Vector2D, VectorAddTest) {
    Vector2D vector1(0, 0);
    Vector2D vectorExpect = vector1;
    Vector2D vector2(264, 255);
    vector1.Add(vector2);
    EXPECT_EQ(vector1.x ,vectorExpect.x + vector2.x);
    EXPECT_EQ(vector1.y ,vectorExpect.y + vector2.y);
}

TEST(Vector2D, VectorMultiplyTest) {
    Vector2D vector1(1, 1);
    vector1 = vector1 * 5;
    EXPECT_EQ(vector1.x, 5);
    EXPECT_EQ(vector1.y, 5);
}