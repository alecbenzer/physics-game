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
  WorldStub world;
};

TEST_F(WorldTest, ObjectDoesntMove) {
  Object* obj = world.NewObject();
  world.Step();
}

}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
