#ifndef POINT_H
#define POINT_H

#include <iostream>

template <class T>
class Point_t {
public:
	T x;
	T y;
	T z;

	// Constructors
	Point_t<T>();
	Point_t<T>(T xx, T yy);
	Point_t<T>(T xx, T yy, T zz);

	virtual ~Point_t<T>(); // Deconstructor

	// Operator overloaders for another Point
	Point_t<T>& operator+=(const Point_t<T>& rhs);
	Point_t<T> operator+(const Point_t<T>& rhs) const;
	Point_t<T>& operator-=(const Point_t<T>& rhs);
	Point_t<T> operator-(const Point_t<T>& rhs) const;
	Point_t<T>& operator*=(const Point_t<T>& rhs);
	Point_t<T> operator*(const Point_t<T>& rhs) const;
	Point_t<T>& operator/=(const Point_t<T>& rhs);
	Point_t<T> operator/(const Point_t<T>& rhs) const;
	Point_t<T>& operator+=(const T rhs);
	Point_t<T> operator+(const T rhs) const;
	Point_t<T>& operator-=(const T rhs);
	Point_t<T> operator-(const T rhs) const;
	Point_t<T>& operator*=(const T rhs);
	Point_t<T> operator*(const T rhs) const;
	Point_t<T>& operator/=(const T rhs);
	Point_t<T> operator/(const T rhs) const;
	bool operator==(const Point_t<T>& other) const;
	bool operator!=(const Point_t<T>& other) const;
};

// Point typedefs
typedef Point_t<int> Pointi;
typedef Point_t<float> Pointf;
typedef Point_t<double> Pointd;
typedef Pointf Point;
typedef Point_t<int> Point2i;
typedef Point_t<float> Point2f;
typedef Point_t<double> Point2d;
typedef Point2f Point2;
typedef Point_t<int> Point3i;
typedef Point_t<float> Point3f;
typedef Point_t<double> Point3d;
typedef Point3f Point3;

// Implementation of Point_t<T>

// constructors and destructor
template <class T>
Point_t<T>::Point_t() {
	x = 0;
	y = 0;
	z = 0;
}

template <class T>
Point_t<T>::Point_t(T xx, T yy) {
	x = xx;
	y = yy;
	z = 0;
}

template <class T>
Point_t<T>::Point_t(T xx, T yy, T zz) {
	x = xx;
	y = yy;
	z = zz;
}

template <class T>
Point_t<T>::~Point_t() {

}

// Add another Point (and assign)
template <class T>
Point_t<T>& Point_t<T>::operator+=(const Point_t<T>& rhs) {
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

template <class T>
Point_t<T> Point_t<T>::operator+(const Point_t<T>& rhs) const {
	return Point_t<T>(x + rhs.x, y + rhs.y, z + rhs.z);
}

// Subtract another Point (and assign)
template <class T>
Point_t<T>& Point_t<T>::operator-=(const Point_t<T>& rhs) {
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

template <class T>
Point_t<T> Point_t<T>::operator-(const Point_t<T>& rhs) const {
	return Point_t<T>(x + -rhs.x, y - rhs.y, z - rhs.z);
}

// Multiply with another Point (and assign)
template <class T>
Point_t<T>& Point_t<T>::operator*=(const Point_t<T>& rhs) {
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	return *this;
}

template <class T>
Point_t<T> Point_t<T>::operator*(const Point_t<T>& rhs) const {
	return Point_t<T>(x*rhs.x, y*rhs.y, z*rhs.z);
}

// Divide by another Point (and assign)
template <class T>
Point_t<T>& Point_t<T>::operator/=(const Point_t<T>& rhs) {
	// TODO: check for division by 0?
	x /= rhs.x;
	y /= rhs.y;
	z /= rhs.z;
	return *this;
}

template <class T>
Point_t<T> Point_t<T>::operator/(const Point_t<T>& rhs) const {
	// TODO: check for division by 0?
	return Point_t<T>(x / rhs.x, y / rhs.y, z / rhs.z);
}

// Add any Number (and assign)
template <class T>
Point_t<T>& Point_t<T>::operator+=(const T rhs) {
	x += rhs;
	y += rhs;
	z += rhs;
	return *this;
}

template <class T>
Point_t<T> Point_t<T>::operator+(const T rhs) const {
	return Point_t<T>(x + rhs, y + rhs, z + rhs);
}

// Subtract any Number (and assign)
template <class T>
Point_t<T>& Point_t<T>::operator-=(const T rhs) {
	x -= rhs;
	y -= rhs;
	z -= rhs;
	return *this;
}

template <class T>
Point_t<T> Point_t<T>::operator-(const T rhs) const {
	return Point_t<T>(x - rhs, y - rhs, z - rhs);
}

// Multiply with any Number (and assign)
template <class T>
Point_t<T>& Point_t<T>::operator*=(const T rhs) {
	x *= rhs;
	y *= rhs;
	z *= rhs;
	return *this;
}

template <class T>
Point_t<T> Point_t<T>::operator*(const T rhs) const {
	return Point_t<T>(x*rhs, y*rhs, z*rhs);
}

// Divide by any Number (and assign)
template <class T>
Point_t<T>& Point_t<T>::operator/=(const T rhs) {
	// TODO: check for division by 0?
	x /= rhs;
	y /= rhs;
	z /= rhs;
	return *this;
}

template <class T>
Point_t<T> Point_t<T>::operator/(const T rhs) const {
	// TODO: check for division by 0?
	return Point_t<T>(x / rhs, y / rhs, z / rhs);
}

// operator == and != overloader
template <class T>
bool Point_t<T>::operator==(const Point_t<T>& other) const {
	return (x == other.x && y == other.y && z == other.z);
}

template <class T>
bool Point_t<T>::operator!=(const Point_t<T>& other) const {
	return !(*this == other);
}

// iostream << and >> overloader
/**
* @param stream
* @param ob
*/
template <class T>
std::ostream& operator<<(std::ostream& stream, Point_t<T> ob) {
	stream << "(" << ob.x << ", " << ob.y << ", " << ob.z << ")";

	return stream;
}

/**
* @param stream
* @param ob
*/
template <class T>
std::istream& operator>>(std::istream& stream, Point_t<T>& ob) {
	stream >> ob.x >> ob.y >> ob.z;

	return stream;
}

#endif
