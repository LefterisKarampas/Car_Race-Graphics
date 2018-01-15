#ifndef VEHICLE_H_
#define VEHICLE_H_

// abstract class vehicle
class Vehicle
{
  public:
    Vehicle(float u, float u_max, float uOp);
    ~Vehicle();
    void Reset(float u);
    void ForwardLeft(float dt);
    void ForwardRight(float dt);
    void TurnDown(float radius, float dt);
    void TurnUp(float radius, float dt);
    bool Moving();
    void SpeedUp(float a);
    void SpeedDown(float a);
    void SetSpeed(float u);
    float GetSpeed();
    void Stop();
    virtual bool ReachedPosition(float x) = 0;

  protected:
    float xBeforeTurn_;
    float zBeforeTurn_;
    float x_;
    float z_;
    float u_;
    float u_max_;
    float uOp_;
    float theta_;
    bool turning_;
    bool up_;
    bool down_;
    short int direction_;
    bool crash_;
};

#endif