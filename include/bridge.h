#ifndef BRIDGE_H
#define BRIDGE_H

#include <time.h>

class Bridge {
  public:
    Bridge(float u);
    ~Bridge();
    void Render(double R, double D, double L);
    void Move(float dt);
    bool Moving();
    char Get_Color();
  private:
    float angle_;
    bool moving_;
    bool full_;
    float u_;
    time_t nextWarningTime_;
    time_t nextMoveTime_;
    char color;
};
#endif