#ifndef _LEVEL_H
#define _LEVEL_H

#include <vector>
#include <string>
#include <lua5.1/lua.hpp>
#include "help.h"
#include "world.h"
#include "ship.h"
#include "basic_object.h"

using std::string;

class Level {
 public:
  Level(const char* filename)
    : filename_(filename),
      won_(false),
      lost_(false) {
  }
  virtual ~Level();

  virtual void Setup(World* world);
  virtual void Step(World* world);

  virtual bool won() { return won_; }
  virtual bool lost() { return lost_; }

 private:
  DISALLOW_COPY_AND_ASSIGN(Level);

  double GetDoubleField(const char* k, double* var);
  string GetStringField(const char* k, string* var);

  bool won_;
  bool lost_;

  Ship ship_;

  std::vector<BasicObject*> objects_;

  const char* filename_;
  lua_State* L_;

};

#endif  // _LEVEL_H
