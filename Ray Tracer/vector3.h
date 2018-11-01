#ifndef VEC3_H
#define VEC3_H

#ifndef PI
#define PI 3.1415926f
#endif

struct Vector3{
	float x;
	float y;
	float z;

	Vector3();
	Vector3(const Vector3& v);
	Vector3(float x, float y, float z);
	Vector3(float f);

	virtual ~Vector3();

	inline float lengthSquared();
	inline float length();

	Vector3 normalized();
	Vector3 getReflection(const Vector3& normal);
	Vector3 getRefraction(const Vector3& normal, float snellK);

	Vector3& operator =(const Vector3& v);
	Vector3& operator +=(const Vector3& v);
	Vector3& operator -=(const Vector3& v);
	Vector3& operator *=(float f);
	Vector3& operator /=(float f);
	Vector3 operator -() const;
};

typedef Vector3 Point;

float dot(Vector3 v1, Vector3 v2);
Vector3 cross(Vector3 v1, Vector3 v2);

inline Vector3 operator +(const Vector3& v1, const Vector3& v2){
	return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

inline Vector3 operator -(const Vector3& v1, const Vector3& v2){
	return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline Vector3 operator *(const Vector3& v, float f){
	return Vector3(v.x * f, v.y * f, v.z * f);
}

inline Vector3 operator *(float f, const Vector3& v){
	return Vector3(v.x * f, v.y * f, v.z * f);
}

inline Vector3 operator /(const Vector3& v, float f){
	return Vector3(v.x / f, v.y / f, v.z / f);
}

inline Vector3 operator /(float f, const Vector3& v){
	return Vector3(f / v.x, f / v.y, f / v.z);
}

#endif // VEC3_H
