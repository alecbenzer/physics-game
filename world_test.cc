#include <gtest/gtest.h>
#include "world.h"
#include "object.h"

#include <Box2D/Box2D.h>

namespace {

class WorldStub : public World {
 public:
  void Step() {
    world_.Step(time_step_, velocity_iters_, position_iters_);
  }
};

class WorldTest : public ::testing::Test {
 protected:
  Object* TestObject() {
    Object* obj = world.NewObject();
    obj->set_initial_position(0, 0);
    obj->set_box_shape(1, 1);
    return obj;
  }

  void StepALot() {
    for(int i = 0; i < 100; ++i) world.Step();
  }

  WorldStub world;
};

TEST_F(WorldTest, ObjectMoves) {
  Object* obj = TestObject();
  obj->set_dynamic();
  obj->Init();

  b2Vec2 old_position = obj->position();
  StepALot();

  // operator != undefined for b2Vec2
  EXPECT_FALSE(old_position == obj->position());
}

TEST_F(WorldTest, StaticObjectDoesntMove) {
  Object* obj = TestObject();
  obj->set_static();
  obj->Init();

  b2Vec2 old_position = obj->position();
  StepALot();

  EXPECT_EQ(old_position, obj->position());
}

TEST_F(WorldTest, DisableGravity) {
  Object* obj = TestObject();
  obj->set_dynamic();
  obj->Init();

  world.set_gravity(0.0);  // disable gravity
  b2Vec2 old_position = obj->position();
  StepALot();

  EXPECT_EQ(old_position, obj->position());
}

}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
