#ifndef VEHICLE_H_
#define VEHICLE_H_

// abstract class vehicle
class Vehicle
{
  public:
    Vehicle(float u, float u_max);
    ~Vehicle();
    void ForwardLeft(float dt);
    void ForwardRight(float dt);
    void TurnDown(float radius, float dt);
    void TurnUp(float radius, float dt);
    bool Moving();
    void SpeedUp(float a);
    void SpeedDown(float a);
    virtual bool ReachedPosition(float x, float y1, float y2) = 0;

  protected:
    float xBeforeTurn_;
    float zBeforeTurn_;
    float x_;
    float z_;
    float u_;
    float u_max_;
    float theta_;
    bool turning_;
    short int direction_;
};

#endif