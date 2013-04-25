#include <gtest/gtest.h>
#include "world.h"
#include "basic_object.h"

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
  BasicObject* TestObject() {
    BasicObject* obj = new BasicObject();
    obj->set_initial_position(0.0, 0.0);
    obj->set_box_shape(1, 1);

    return obj;
  }

  void StepALot() {
    for (int i = 0; i < 100; ++i) world.Step();
  }

  WorldStub world;
  b2BodyDef bodyDef;
};

TEST_F(WorldTest, ObjectMoves) {
  BasicObject* obj = TestObject();
  obj->set_dyanmic();
  world.AddObject(obj);

  b2Vec2 old_position = obj->body()->GetPosition();
  StepALot();

  // operator != undefined for b2Vec2
  EXPECT_FALSE(old_position == obj->body()->GetPosition());
}

TEST_F(WorldTest, StaticObjectDoesntMove) {
  BasicObject* obj = TestObject();
  obj->set_static();
  world.AddObject(obj);

  b2Vec2 old_position = obj->body()->GetPosition();
  StepALot();

  EXPECT_EQ(old_position, obj->body()->GetPosition());
}

TEST_F(WorldTest, DisableGravity) {
  BasicObject* obj = TestObject();
  obj->set_dyanmic();
  world.AddObject(obj);

  world.set_gravity(0.0);  // disable gravity
  b2Vec2 old_position = obj->body()->GetPosition();
  StepALot();

  EXPECT_EQ(old_position, obj->body()->GetPosition());
}

}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
