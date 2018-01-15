#ifndef CAR_MODEL_H_
#define CAR_MODEL_H_

#include "vehicle.h"
#include "Model.h"

class CarModel : public Vehicle
{
  public:
    CarModel(float u, float u_max, Model* model,
      float startX, float startY, float startZ);
    ~CarModel();
    void Render(double R, double D, double L);
    bool ReachedPosition(float x, float y1, float y2);

  private:
    Model* model_;
    float startX_;
    float startY_;
    float startZ_;
};

#endif // CAR_MODEL_H_