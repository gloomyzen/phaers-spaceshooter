#include "../src/Core/DataTypes/Vector2D.h"
#include <gtest/gtest.h>

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

namespace TGEngine::test {

    using namespace TGEngine::core;

    class Vector2DTest : public testing::Test {
    public:
        Vector2D *vector;

        Vector2DTest() { vector = new Vector2D; }

        void constructor(float _x, float _y) {
            delete vector;
            vector = nullptr;
            vector = new Vector2D(_x, _y);
        }

        ~Vector2DTest() { delete vector; }
    };

}// namespace TGEngine::test

using namespace TGEngine::core;
using namespace TGEngine::test;

TEST_F(Vector2DTest, VectorConstructorTest) {
    float one = 0.0f;
    float two = 1.5f;
    constructor(one, one);
    EXPECT_EQ(one, vector->getX());
    EXPECT_EQ(one, vector->getY());
    vector->setX(two);
    vector->setY(two);
    EXPECT_EQ(two, vector->getX());
    EXPECT_EQ(two, vector->getY());
}

TEST_F(Vector2DTest, VectorZeroTest) {
    float zero = 0.0f;
    vector->Zero();
    EXPECT_EQ(zero, vector->getX());
    EXPECT_EQ(zero, vector->getY());
}

TEST_F(Vector2DTest, VectorAddTest) {
    Vector2D vector1(0, 0);
    Vector2D vectorExpect = vector1;
    Vector2D vector2(264, 255);
    vector1.Add(vector2);
    EXPECT_EQ(vector1.getX(), vectorExpect.getX() + vector2.getX());
    EXPECT_EQ(vector1.getY(), vectorExpect.getY() + vector2.getY());
}
