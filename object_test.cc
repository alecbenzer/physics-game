#include <gtest/gtest.h>
#include "object.h"

#include <Box2D/Box2D.h>

namespace {

class ObjectTest : public ::testing::Test {
 protected:
  ObjectTest() : world(b2Vec2(0, 0)) {
    obj = new Object(&world);
  }

  b2World world;
  Object* obj;
};

TEST_F(ObjectTest, DefaultBodyType) {
  EXPECT_EQ(b2_dynamicBody, obj->body_type());
}

TEST_F(ObjectTest, SetBodyType) {
  obj->set_static();

  EXPECT_EQ(b2_staticBody, obj->body_type());
}

}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
