#ifndef _WORLD_H
#define _WORLD_H

#include <vector>
#include "object.h"
#include "help.h"

class World {
  public:
    World();
    ~World();

    void SetScreenSize(int w, int h) {
      window_width_ = w;
      window_height_ = h;
    }

    void SetViewHeight(int view_height) {
      view_height_ = view_height;
    }

    void SetViewCenter(double x, double y) {
      view_x_ = x;
      view_y_ = y;
    }

    void SetStepParams(double time_step, double velocity_iters, double position_iters) {
      time_step_ = time_step;
      velocity_iters_ = velocity_iters;
      position_iters_ = position_iters;
    }

    void Init();

    Object* NewObject();

    void Step();
    void Render();

    bool done() { return done_; }

  protected:
    b2World world_;

    // parameters for world simulation
    double time_step_;
    double velocity_iters_;
    double position_iters_;

  private:
    DISALLOW_COPY_AND_ASSIGN(World);

    void UpdateViewport();

    // pixel dimmensions of the window we're displaying
    int window_width_;
    int window_height_;

    // the height (in Box2D units) that the window's height should represent
    double view_height_;

    // The width (in Box2D units) that the window's width represents. It's
    // calculated based on view_height_.
    double view_width_;

    // center (in Box2D coordinates) of the rendering view
    double view_x_;
    double view_y_;

    bool done_;

    std::vector<Object*> objects_;
};

#endif  // _WORLD_H
