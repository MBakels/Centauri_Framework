#ifndef SINGLETON_H
#define SINGLETON_H

template<class T>
class Singleton {
public:
	static T* instance();
	static void destroy();

private:
	Singleton() {
		Singleton::_instance = static_cast<T*>(this);
	}
	
	~Singleton() {
		Singleton::destroy();
	}

	/// @brief overloaded copy constructor (no implementation)
	//Singleton(Singleton const&);
	/// @brief overloaded operator= (no implementation)
	//Singleton& operator=(Singleton const&);

	static T* _instance; // The instance itself
};

// ========================== implementation ==========================
template<class T>
T* Singleton<T>::instance() {
	if (Singleton::_instance == 0) {
		Singleton::_instance = new T();
		std::atexit(Singleton::destroy);
	}
	return Singleton::_instance;
}

template<class T>
void Singleton<T>::destroy() {
	if (Singleton::_instance != 0) {
		delete Singleton::_instance;
		Singleton::_instance = 0;
	}
}

template<class T>
T* Singleton<T>::_instance = 0;

#endif