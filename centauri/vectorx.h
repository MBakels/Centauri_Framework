#ifndef VECTORX_H
#define VECTORX_H

#include <cmath>
#include "pointx.h"

#define PI			3.1415926535897932384626433832795 // PI (180 deg)
#define HALF_PI		1.5707963267948966192313216916398 // PI/2 (90 deg)
#define TWO_PI		6.283185307179586476925286766559 // PI*2 (360 deg)
#define DEG_TO_RAD	0.017453292519943295769236907684886 // Convert degrees to radians
#define RAD_TO_DEG	57.295779513082320876798154814105 // Convert radians to degrees

// Class definition of VectorX_t<T>
template <class T>
class VectorX_t : public Point_t<T> {
public:
	// Constructors
	VectorX_t<T>();
	VectorX_t<T>(T xx, T yy);
	VectorX_t<T>(T xx, T yy, T zz);
	VectorX_t<T>(Point_t<T> p);
	VectorX_t<T>(Point_t<T> begin, Point_t<T> end);

	virtual ~VectorX_t(); // Deconstructor

	// length, angle, normalize, dot
	const T getLength() const;
	const T getLengthSquared() const;
	const T getAngle() const;
	const T getAngleDeg() const;
	const T getAngle(const VectorX_t<T>& other) const;
	const T getAngleDeg(const VectorX_t<T>& other) const;
	const VectorX_t<T> getNormalized() const;
	void normalize();
	void lerp(T frac);
	const VectorX_t<T> getLerped(T frac) const;
	const T dot(const VectorX_t<T>& other) const;
	const VectorX_t<T> cross(const VectorX_t<T>& other) const;
	void rotate(T angle);
	void rotation(T angle);
	void rotateDeg(T angle);
	void rotationDeg(T angle);
	const VectorX_t<T> getRotated(T angle) const;
	const VectorX_t<T> getRotatedDeg(T angle) const;
	void limit(T amount);

	// operator overloaders
	bool operator<(VectorX_t<T> other);
	bool operator>(VectorX_t<T> other);
	bool operator<=(VectorX_t<T> other);
	bool operator>=(VectorX_t<T> other);
};

// Vector typedefs
typedef VectorX_t<int> Vector2i;
typedef VectorX_t<float> Vector2f;
typedef VectorX_t<double> Vector2d;
typedef Vector2f Vector2;
typedef VectorX_t<int> Vector3i;
typedef VectorX_t<float> Vector3f;
typedef VectorX_t<double> Vector3d;
typedef Vector3f Vector3;

// Implementation of VectorX_t<T>

// Constructors and destructor
template <class T>
VectorX_t<T>::VectorX_t() {

}

template <class T>
VectorX_t<T>::VectorX_t(T xx, T yy) {
	this->x = xx;
	this->y = yy;
	this->z = 0;
}

template <class T>
VectorX_t<T>::VectorX_t(T xx, T yy, T zz) {
	this->x = xx;
	this->y = yy;
	this->z = zz;
}

template <class T>
VectorX_t<T>::VectorX_t(Point_t<T> begin, Point_t<T> end) {
	this->x = (end.x - begin.x);
	this->y = (end.y - begin.y);
	this->z = (end.z - begin.z);
}

template <class T>
VectorX_t<T>::VectorX_t(Point_t<T> p) {
	this->x = p.x;
	this->y = p.y;
	this->z = p.z;
}

template <class T>
VectorX_t<T>::~VectorX_t() {

}

// getLength()
template <class T>
const T VectorX_t<T>::getLength() const {
	return sqrtf(getLengthSquared());
}

template <class T>
const T VectorX_t<T>::getLengthSquared() const {
	T xx = this->x;
	T yy = this->y;
	T zz = this->z;

	return (xx*xx) + (yy*yy) + (zz*zz);
}

// getAngle()
template <class T>
const T VectorX_t<T>::getAngle() const {
	// this only works on a 2D Vector, so we use atan2()
	// because we want to know to which quadrant the Vector2 is pointing.
	// returns the angle relative to the X-axis.
	// range: -179.99 to +180
	return atan2(this->y, this->x);

	// You'd expect the following to work, but it doesn't, because the
	// angle between 2 Vectors is always between 0 and 180 degrees (pi radians)
	//return getAngle(VectorX_t<T>(1,0,0));
}

template <class T>
const T VectorX_t<T>::getAngleDeg() const {
	return (getAngle() * RAD_TO_DEG);
}

// getAngle(VectorX_t<T>& other)
template <class T>
const T VectorX_t<T>::getAngle(const VectorX_t<T>& other) const {
	VectorX_t<T> copy = *this;
	T dot = copy.dot(other);
	T l1 = copy.getLength();
	T l2 = other.getLength();

	return acos(dot / (l1*l2)); // law of cosines
}

template <class T>
const T VectorX_t<T>::getAngleDeg(const VectorX_t<T>& other) const {
	return (getAngle(other) * RAD_TO_DEG);
}

// getNormalized() & normalize()
template <class T>
const VectorX_t<T> VectorX_t<T>::getNormalized() const {
	VectorX_t<T> copy = *this;
	copy.normalize();

	return copy;
}

template <class T>
void VectorX_t<T>::normalize() {
	T l = this->getLength();
	if (l != 0) {
		*this /= l;
	}
}

template <class T>
void VectorX_t<T>::lerp(T frac) {
	*this *= frac;
}

template <class T>
const VectorX_t<T> VectorX_t<T>::getLerped(T frac) const {
	VectorX_t<T> copy = *this;
	copy.lerp(frac);

	return copy;
}

// dot and cross products
template <class T>
const T VectorX_t<T>::dot(const VectorX_t<T>& other) const {
	T x = this->x * other.x;
	T y = this->y * other.y;
	T z = this->z * other.z;

	return (x + y + z);
}

template <class T>
const VectorX_t<T> VectorX_t<T>::cross(const VectorX_t<T>& other) const {
	T x = (this->y * other.z) - (this->z * other.y);
	T y = (this->z * other.x) - (this->x * other.z);
	T z = (this->x * other.y) - (this->y * other.x);

	return VectorX_t<T>(x, y, z);
}

// rotation
template <class T>
void VectorX_t<T>::rotate(T angle) {
	T aa = this->getAngle() + angle;
	this->rotation(aa);
}

template <class T>
void VectorX_t<T>::rotation(T angle) {
	T l = this->getLength();
	this->x = cos(angle) * l;
	this->y = sin(angle) * l;
}

template <class T>
void VectorX_t<T>::rotateDeg(T angle) {
	this->rotate(angle * DEG_TO_RAD);
}

template <class T>
void VectorX_t<T>::rotationDeg(T angle) {
	this->rotation(angle * DEG_TO_RAD);
}

template <class T>
const VectorX_t<T> VectorX_t<T>::getRotated(T angle) const {
	VectorX_t<T> copy = *this;
	copy.rotate(angle);

	return copy;
}

template <class T>
const VectorX_t<T> VectorX_t<T>::getRotatedDeg(T angle) const {
	return this->getRotated(angle * DEG_TO_RAD);
}

template <class T>
void VectorX_t<T>::limit(T amount) {
	if (this->getLengthSquared() > amount*amount) {
		this->normalize();
		*this *= amount;
	}
}

// operator <, >, <=, >= overloader
template <class T>
bool VectorX_t<T>::operator<(VectorX_t<T> other) {
	return (this->getLengthSquared() < other.getLengthSquared());
}

template <class T>
bool VectorX_t<T>::operator>(VectorX_t<T> other) {
	return (this->getLengthSquared() > other.getLengthSquared());
}

template <class T>
bool VectorX_t<T>::operator<=(VectorX_t<T> other) {
	return (this->getLengthSquared() <= other.getLengthSquared());
}

template <class T>
bool VectorX_t<T>::operator>=(VectorX_t<T> other) {
	return (this->getLengthSquared() >= other.getLengthSquared());
}



// Class definition of Polar_t<T>
template <class T>
class Polar_t {
public:
	T angle; // angle of Polar_t
	T radius; // radius of Polar_t

	Polar_t<T>(); // Default constructor.
	Polar_t<T>(T a, T r); // Overloaded constructor

	const VectorX_t<T> cartesian() const;
	Polar_t<T> fromCartesian(const VectorX_t<T>& vec);
	Polar_t<T> fromCartesian(T x, T y);
};

// Class implementation of Polar_t<T>
template <class T>
Polar_t<T>::Polar_t() {
	this->angle = 0;
	this->radius = 1;
}

template <class T>
Polar_t<T>::Polar_t(T a, T r) {
	this->angle = a;
	this->radius = r;
}

template <class T>
const VectorX_t<T> Polar_t<T>::cartesian() const {
	VectorX_t<T> cartesian = VectorX_t<T>();

	cartesian.x = cos(this->angle) * this->radius;
	cartesian.y = sin(this->angle) * this->radius;
	cartesian.z = 0;

	return cartesian;
}

template <class T>
Polar_t<T> Polar_t<T>::fromCartesian(const VectorX_t<T>& vec) {
	this->angle = vec.getAngle();
	this->radius = vec.getLength();

	return *this;
}

template <class T>
Polar_t<T> Polar_t<T>::fromCartesian(T x, T y) {
	const VectorX_t<T> vec = VectorX_t<T>(x, y);

	return this->fromCartesian(vec);
}

/// @brief A typedef for creating a Polar of ints
typedef Polar_t<int> Polari;
/// @brief A typedef for creating a Polar of floats
typedef Polar_t<float> Polarf;
/// @brief A typedef for creating a Polar of doubles
typedef Polar_t<double> Polard;
/// @brief A typedef for creating a default Polar
typedef Polarf Polar;



#endif