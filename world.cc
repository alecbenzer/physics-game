#include "world.h"

#include <cstdio>
#include <GL/gl.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

World::World()
    : window_width_(640),
      window_height_(480),
      view_height_(10),
      view_width_(640.0 / 480.0 * 10.0),
      view_x_(0),
      view_y_(0),
      world_(b2Vec2(0.0, 9.8)),
      time_step_(1.0 / 60.0),
      velocity_iters_(6),
      position_iters_(2),
      done_(false) {
}

World::~World() {
  for (int i = 0; i < objects_.size(); ++i) {
    delete objects_[i];
  }
}

void World::Init() {
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_SetVideoMode(window_width_, window_height_, 32,
                   SDL_OPENGL | SDL_GL_DOUBLEBUFFER);

  glClearColor(0, 0, 0, 0);
  glClearDepth(1.0f);

  glViewport(0, 0, window_width_, window_height_);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  UpdateViewport();

  glMatrixMode(GL_MODELVIEW);

  glEnable(GL_TEXTURE_2D);

  glLoadIdentity();
}

Object* World::NewObject() {
  Object* obj = new Object(&world_);
  objects_.push_back(obj);
  return obj;
}

void World::Render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for (int i = 0; i < objects_.size(); ++i) {
    objects_[i]->Render();
  }

  SDL_GL_SwapBuffers();
}

void World::Step() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      done_ = true;
    } else if (event.type == SDL_VIDEORESIZE) {
      window_width_ = event.resize.w;
      window_height_ = event.resize.h;

      SDL_SetVideoMode(window_width_, window_height_, 32,
                       SDL_OPENGL | SDL_GL_DOUBLEBUFFER);
      glViewport(0, 0, window_width_, window_height_);
      UpdateViewport();
    }
  }

  world_.Step(time_step_, velocity_iters_, position_iters_);
}

void World::UpdateViewport() {
  // compute view_width_ based on current values for window_width_,
  // window_height_, and view_height_
  double window_ratio = 1.0 * window_width_ / window_height_;
  view_width_ = window_ratio * view_height_;

  double left = view_x_ - view_width_ / 2.0;
  double right = view_x_ + view_width_ / 2.0;
  double top = view_y_ - view_height_ / 2.0;
  double bottom = view_y_ + view_height_ / 2.0;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(left, right, bottom, top);
  glMatrixMode(GL_MODELVIEW);
}
