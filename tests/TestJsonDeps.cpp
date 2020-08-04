#include <gtest/gtest.h>
#include <fstream>
#include "rapidjson/document.h"
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/ostreamwrapper.h>
#include "../src/Core/Loaders/JsonLoader.h"

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(TestJsonDeps, IncludeJsonTest) {
    const char json[] = " { \"test\" : \"row\", \"t\" : true , \"f\" : false } ";
    rapidjson::Document document;
    document.Parse(json);

    ASSERT_TRUE(document.IsObject());
    ASSERT_FALSE(document.HasMember("false"));
    ASSERT_TRUE(document.HasMember("test"));
    ASSERT_TRUE(document.HasMember("t"));
    ASSERT_TRUE(document.HasMember("f"));
    ASSERT_TRUE(document["test"].IsString());
    EXPECT_EQ(document["test"], "row");
}

TEST(TestJsonFileRead, IncludeJsonTest) {
  /*** Note: need use ../ because all tests located in test folder */
  //usefull links: https://rapidjson.org/md_doc_stream.html#FileReadStream
  //usefull links: https://stackoverflow.com/questions/45248182/how-to-read-json-file-using-rapidjson-and-output-to-stdstring
  std::ifstream ifs ("../resources/data/nodes/mainMenu.json", std::ifstream::in);
  EXPECT_TRUE(ifs.is_open());

  //read
  rapidjson::IStreamWrapper isw { ifs };

  rapidjson::Document document {};
  document.ParseStream( isw );
  ASSERT_TRUE(document.IsObject());
  ASSERT_TRUE(document.HasMember("type"));
  ASSERT_TRUE(document["type"].IsString());
  EXPECT_EQ(document["type"], "node");

  //write
//  rapidjson::StringBuffer buffer {};
//  rapidjson::Writer<rapidjson::StringBuffer> writer { buffer };
//  document.Accept( writer );
//  EXPECT_FALSE(document.HasParseError());
}

TEST(TestCorJsonLoader, IncludeJsonTest) {
  using namespace TGEngine::core;
  ASSERT_TRUE(true);
  auto json = JsonLoader::loadJson("resources/data/nodes/defaultScene.json", "../");
  ASSERT_TRUE(json.IsObject());
  auto notValidJson = JsonLoader::loadJson("resources/data/nodes/defaultSceneNotValid.json", "../");
  EXPECT_EQ(notValidJson.IsObject(), false);
}