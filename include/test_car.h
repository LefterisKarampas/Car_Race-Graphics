#ifndef TEST_CAR_
#define TEST_CAR_

#include "vehicle.h"

class TestCar : public Vehicle
{
  public:
    TestCar(float u, float u_max, float hRatio, 
              float lRatio, float dRatio);
    ~TestCar();
    void Render(float startX, float startY, double R, double D, double L);
    bool ReachedPosition(float x, float y1, float y2);
    void ResetDirection();

  private:
    void drawBall();
    float startX_;
    // ratios
    float hR_;
    float lR_;
    float dR_;
    float noseX_;
    float noseY_;

};

#endif