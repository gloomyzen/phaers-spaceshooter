#include <gtest/gtest.h>
#include "../src/Core/Nodes/Node.h"
#include "../src/Core/Nodes/NodeManager.h"
#include "../src/Core/Components/TransformComponent.h"

using namespace TGEngine::core;

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

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


TEST_F(NodeTest, NodeConstructorTest)
{
  constructor("test");
  EXPECT_EQ(node->getId(), "test");

  auto testNode = new Node("testNode2");
  node->addChild(testNode);
  EXPECT_EQ(node->getChilds().size(), 1);

  auto findTest = node->findNode("testNode2");
  EXPECT_EQ(findTest, testNode);
  //links check
  findTest->setId("newId");
  EXPECT_EQ("newId", testNode->getId());

  //nullptr test
  auto nullptrTest = node->findNode("testNullptr");
  EXPECT_EQ(nullptrTest, nullptr);

}

TEST(NodeManager, NodeManagerTest) {
  std::vector<std::string> layers = {
    "Ground", "Units", "UI"
  };
  //Для тесткейса создаем 3 дефольтные ноды в менеджере
  for (auto layer : layers) {
    GET_NODE_MANAGER().addChild(new Node(layer));
  }

  //берем ноду Ground
  auto ground = GET_NODE_MANAGER().findNode("Ground");
  EXPECT_EQ(ground->getId(), "Ground");

  //Создаем ноду с крепостью
  auto fortress = new Node("fortress");
  ground->addChild(fortress);
  //Сверяем имя ноды Units
  EXPECT_EQ(fortress->getId(), "fortress");

  //Ищем ноду крепости в ноде Ground
  EXPECT_EQ(ground->findNode("fortress"), fortress);
  //Ищем ноду крепости глобально чеез менеджер
  EXPECT_EQ(GET_NODE_MANAGER().findNode("fortress"), fortress);

  //Находим ноду Units
  auto units = GET_NODE_MANAGER().findNode("Units");
  //Сверяем имя ноды Units
  EXPECT_EQ(units->getId(), "Units");

  //Создаем ноду героя
  auto hero = new Node("hero");
  //Добавляем ноду героя к ноде Units
  units->addChild(hero);
  //Сверяем имя ноды
  EXPECT_EQ(hero->getId(), "hero");

  //Ищем ноду героя в ноде Units
  EXPECT_EQ(units->findNode("hero"), hero);
  //Ищем ноду героя глбально через менеджер
  EXPECT_EQ(GET_NODE_MANAGER().findNode("hero"), hero);
}

TEST(NodeTransform, NodeManagerTest) {
  auto node = new Node("test1");
  node->addComponent<TransformComponent>();
  auto transform = node->getComponent<TransformComponent>();
  transform.setPosition(5.f, 5.f);
  EXPECT_EQ(transform.getPosition().getY(), Vector2D(5.f, 5.f).getY());
  EXPECT_EQ(transform.getPosition().getX(), Vector2D(5.f, 5.f).getX());
}

