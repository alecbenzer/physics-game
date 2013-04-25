#include "world.h"

#include <cstdio>
#include <GL/gl.h>
#include <SDL/SDL_opengl.h>

float RayCastCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point,
                                     const b2Vec2& normal, float fraction) {
    if (fixture->GetBody()->GetType() == b2_dynamicBody) {
      body_ = fixture->GetBody();
      point_ = point;
      normal_ = normal;
      return 0;
    } else {
     body_ = NULL;
     return -1;
    }
}

void ContactListener::PostSolve(b2Contact* contact,
                                const b2ContactImpulse* impulse) {
  Object* objA =
    static_cast<Object*>(contact->GetFixtureA()->GetBody()->GetUserData());
  Object* objB =
    static_cast<Object*>(contact->GetFixtureB()->GetBody()->GetUserData());

  if (objA == objB && objA != NULL) {
    objA->HandleContact(contact, impulse);
  } else {
    if (objA != NULL) {
     objA->HandleContact(contact, impulse);
    }
    if (objB != NULL) {
      objB ->HandleContact(contact, impulse);
    }
  }
}

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

  world_.SetContactListener(&contact_listener_);
}

void World::AddObject(Object* obj) {
  obj->Init(&world_);
  objects_.push_back(obj);
}

void World::ClearObjects() {
  objects_.clear();
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
    } else if (event.type == SDL_KEYDOWN) {
      key_down_.insert(event.key.keysym.sym);
    } else if (event.type == SDL_KEYUP) {
      key_down_.erase(event.key.keysym.sym);
    } else if (event.type == SDL_MOUSEMOTION) {
      double a = (1.0 * event.motion.x / window_width_ - 0.5) * 2.0;
      double b = (1.0 * event.motion.y / window_height_ - 0.5) * 2.0;
      mouse_x_ = view_x_ + a * (view_width_ / 2.0);
      mouse_y_ = view_y_ + b * (view_height_ / 2.0);
    } else if (event.type == SDL_MOUSEBUTTONDOWN) {
      button_down_.insert(event.button.button);
    } else if (event.type == SDL_MOUSEBUTTONUP) {
      button_down_.erase(event.button.button);
    }
  }
  

  world_.Step(time_step_, velocity_iters_, position_iters_);

  for (int i = 0; i < objects_.size(); ++i) {
    objects_[i]->Step(&world_);
  }
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

void World::PerformRaycast(const b2Vec2& a, const b2Vec2& b) {
  raycast_callback_.reset();

  b2Vec2 direction = (1/((b - a).Length())) * (b - a);
  world_.RayCast(&raycast_callback_, a, a + 8 * direction);
}

void World::Message(std::string msg) {
  printf("%s\n", msg.c_str());
}
