#include "../include/Vector.h"

/* -----------------Vector2--------------------*/

template <typename T>
Vector2<T>::Vector2(T x,T y){
	this->x = x;
	this->y = y;
}


template <typename T>
Vector2<T>::~Vector2(){};


template <typename T>
T Vector2<T>::Get_x(){
	return this->x;
}


template <typename T>
T Vector2<T>::Get_y(){
	return this->y;
}

/* -----------------Vector3--------------------*/

template <typename T>
Vector3<T>::Vector3(T x,T y,T z):Vector2<T>(x,y){
	this->z = z;
}

template <typename T>
Vector3<T>::~Vector3(){};

template <typename T>
T Vector3<T>::Get_z(){
	return this->z;
}

void TemporaryFunction ()
{
   Vector3<int> p(1,2,3);
   Vector3<double> q(0.0,0.0,0.0);
   Vector2<int> l(1,2);
   Vector2<int> m(0.0,0.0);
}
