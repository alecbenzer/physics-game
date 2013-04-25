#include "level.h"
#include <iostream>
#include <string>

using std::string;
using std::cerr;
using std::endl;

Level::~Level() {
  for (int i = 0; i < objects_.size(); ++i) {
    delete objects_[i];
  }
}

void Level::Setup(World* world) {
  cerr << "loading " << filename_ << endl;

  L_ = lua_open();
  luaL_openlibs(L_);
  luaL_loadfile(L_, filename_);
  lua_pcall(L_, 0, 0, 0);

  lua_getglobal(L_, "ship");
  if (!lua_istable(L_, -1)) {
    cerr << "NOT A TABLE" << endl;
    return;
  }
  double x = 0, y = 0;
  GetDoubleField("x", &x);
  GetDoubleField("y", &y);

  ship_.set_initial_position(x, y);

  world->AddObject(&ship_);

  lua_getglobal(L_, "objs");
  int n = luaL_getn(L_, -1);
  for (int i = 1; i <= n; ++i) {
    lua_rawgeti(L_, -1, i);
    BasicObject* obj = new BasicObject;

    double x = 0.0, y = 0.0, w = 1.0, h = 1.0;
    string type = "dynamic";
    GetDoubleField("x", &x);
    GetDoubleField("y", &y);
    GetDoubleField("w", &w);
    GetDoubleField("h", &h);
    GetStringField("btype", &type);

    obj->set_initial_position(x, y);
    obj->set_box_shape(w, h);

    if (type == "dynamic") {
      obj->set_dyanmic();
    } else {
      obj->set_static();
    }

    lua_pop(L_, 1);

    objects_.push_back(obj);
    world->AddObject(obj);
  }

  lua_getglobal(L_, "message");
  if (lua_isstring(L_, -1)) {
    cerr << lua_tostring(L_, -1) << endl;
  }
}

void Level::Step(World* world) {
  if (ship_.health() < 0.0) {
    lost_ = true;
  }

  lua_getglobal(L_, "objs");
  for (int i = 0; i < objects_.size(); ++i) {
    lua_rawgeti(L_, -1, i + 1);

    BasicObject* obj = objects_[i];

    lua_pushliteral(L_, "x");
    lua_pushnumber(L_, obj->body()->GetPosition().x);
    lua_settable(L_, -3);

    lua_pushliteral(L_, "y");
    lua_pushnumber(L_, obj->body()->GetPosition().y);
    lua_settable(L_, -3);

    lua_pushliteral(L_, "speed");
    lua_pushnumber(L_, obj->body()->GetLinearVelocity().Length());
    lua_settable(L_, -3);

    lua_pushliteral(L_, "health");
    lua_pushnumber(L_, obj->health());
    lua_settable(L_, -3);

    lua_pop(L_, 1);
  }

  lua_getglobal(L_, "won");
  if (lua_pcall(L_, 0, 1, 0) != 0) {
    cerr << lua_tostring(L_, -1) << endl;
  }
  won_ = lua_toboolean(L_, -1);

  lua_getglobal(L_, "lost");
  if (lua_isfunction(L_, -1)) {
    if (lua_pcall(L_, 0, 1, 0) != 0) {
      cerr << lua_tostring(L_, -1) << endl;
    }
    lost_ = lua_toboolean(L_, -1);
  }

  ship_.ProcessInput(world);
}


double Level::GetDoubleField(const char* k, double* var) {
  lua_pushstring(L_, k);
  lua_gettable(L_, -2);
  if (lua_isnumber(L_, -1)) {
    *var = lua_tonumber(L_, -1);
  }
  lua_pop(L_, 1);

  return *var;
}

string Level::GetStringField(const char* k, string* var) {
  lua_pushstring(L_, k);
  lua_gettable(L_, -2);
  if (lua_isstring(L_, -1)) {
    *var = lua_tostring(L_, -1);
  }
  lua_pop(L_, 1);

  return *var;
}
