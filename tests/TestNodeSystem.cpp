#include <gtest/gtest.h>
#include "../src/Core/Nodes/Node.h"
#include "../src/Core/Nodes/NodeManager.h"
#include "../src/Core/Components/TransformComponent.h"
#include "../src/Core/Components/SpriteComponent.h"

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
  EXPECT_EQ(fortress->getModule(), "");
  fortress->setModule("window");
  EXPECT_EQ(fortress->getModule(), "window");

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

TEST(NodeTransformComponent, NodeManagerTest) {
  float five = 5.f;
  float zero = 0.f;
  auto node = new Node("test1");
  node->addComponent<TransformComponent>();
  EXPECT_EQ(node->getComponent<TransformComponent>().getPosition().getX(), zero);
  EXPECT_EQ(node->getComponent<TransformComponent>().getPosition().getY(), zero);
  auto transform = node->getComponent<TransformComponent>();
  transform.setPosition(five, five);
  EXPECT_EQ(transform.getPosition().getY(), Vector2D(five, five).getY());
  EXPECT_EQ(transform.getPosition().getX(), Vector2D(five, five).getX());
  //test width height and scale
  EXPECT_EQ(transform.getWidth(), 0);
  EXPECT_EQ(transform.getHeight(), 0);
  EXPECT_EQ(transform.getScale(), 1.f);
  int testWidth = 32;
  int testHeight = 110;
  float testScale = 3.f;
  transform.setWidth(testWidth);
  transform.setHeight(testHeight);
  transform.setScale(testScale);
  EXPECT_EQ(transform.getWidth(), testWidth);
  EXPECT_EQ(transform.getHeight(), testHeight);
  EXPECT_EQ(transform.getScale(), testScale);
  //test wrong values
  transform.setWidth(-15);
  transform.setHeight(-25);
  transform.setScale(-1);
  EXPECT_EQ(transform.getWidth(), testWidth);
  EXPECT_EQ(transform.getHeight(), testHeight);
  EXPECT_EQ(transform.getScale(), testScale);
  //test node access from component
  EXPECT_EQ(transform.getNode().getId(), "test1");
}

TEST(NodeSpriteComponen, NodeManagerTest)
{
  auto node = new Node("test1");
  node->addComponent<SpriteComponent>();
  auto spriteNode = node->getComponent<SpriteComponent>();
  //test node access from component
  EXPECT_EQ(spriteNode.getNode().getId(), "test1");
  EXPECT_FALSE(spriteNode.isAnimated());
  //TODO try get animation
  EXPECT_EQ(spriteNode.getAnimation("testAnim"), nullptr);
  EXPECT_EQ(spriteNode.getAnimations().size(), 0);
  //set animation
  auto animStructRun = new sAnimation();
  animStructRun->index = 0;
  animStructRun->frames = 8;
  animStructRun->speed = 150;
  spriteNode.addAnimation("idle", 0, 8, 150);
  EXPECT_TRUE(spriteNode.hasAnimation("idle"));
  EXPECT_EQ(spriteNode.getAnimations().size(), 1);
  EXPECT_EQ(animStructRun->index, 0);
  EXPECT_EQ(animStructRun->frames, 8);
  EXPECT_EQ(animStructRun->speed, 150);
  spriteNode.addAnimation("run", animStructRun);
  EXPECT_TRUE(spriteNode.hasAnimation("run"));
  EXPECT_EQ(spriteNode.getAnimations().size(), 2);
}

