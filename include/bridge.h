#ifndef BRIDGE_H
#define BRIDGE_H

#include <time.h>

class Bridge {
  public:
    Bridge(float u, float tEid);
    ~Bridge();
    void Render(double R, double D, double L);
    void Move(float dt);
    void Reset();
    bool Moving();
    bool Closing();
    char Get_Color();
    void SetTEid(float);
  private:
    float angle_;
    bool moving_;
    bool full_;
    float u_;
    int t_;
    time_t nextWarningTime_;
    time_t nextMoveTime_;
    char color;
    float warning_time;
};
#endif