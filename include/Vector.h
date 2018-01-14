#ifndef _VECTOR_H_
#define _VECTOR_H_


template <typename T>
class Vector2{
	T x;
	T y;
public:
	Vector2(T,T);
	~Vector2();
	T Get_x();
	T Get_y();
};

template <typename T>
class Vector3: public Vector2<T>{
	T z;
public:
	Vector3(T,T,T);
	~Vector3();
	T Get_z();
};

#endif