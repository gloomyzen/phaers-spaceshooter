#include <gtest/gtest.h>
#include "../src/Core/Nodes/NodeManager.h"

using namespace TGEngine::core;

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

//using namespace TGEngine::test;

class NodeTest : public testing::Test
{
public:
  Node *node;
  NodeTest() { node = new Node("testNode"); }
  void constructor(std::string id) {
    delete node;
    node = nullptr;
    node = new Node(id);
  }
  ~NodeTest() { delete node; }
};


TEST_F(NodeTest, VectorConstructorTest)
{
  constructor("test");
  EXPECT_EQ(node->getId(), "test");

  auto testNode = new Node("testNode");
  node->addChild(testNode);
  EXPECT_EQ(node->getChilds().size(), 1);

  auto findTest = node->findNode("testNode");
  EXPECT_EQ(findTest, testNode);
  //links check
  findTest->setId("newId");
  EXPECT_EQ("newId", testNode->getId());

  //nullptr test
  auto nullptrTest = node->findNode("testNullptr");
  EXPECT_EQ(nullptrTest, nullptr);

}

