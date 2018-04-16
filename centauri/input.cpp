#include "input.h"

Input::Input() {
	_window = NULL;

	for (unsigned int i = 0; i<GLFW_KEY_LAST; i++) {
		_keys[i] = false;
		_keysUp[i] = false;
		_keysDown[i] = false;
	}
	for (unsigned int i = 0; i<GLFW_MOUSE_BUTTON_LAST; i++) {
		_mouse[i] = false;
		_mouseUp[i] = false;
		_mouseDown[i] = false;
	}
}

Input::~Input() {
	std::cout << "Input destructor" << std::endl;
}

void Input::updateInput(GLFWwindow* w) {
	_window = w;

	glfwPollEvents();

	// 32-97 = ' ' to '`'
	for (unsigned int i = 32; i<97; i++) {
		handleKey(i);
	}
	// Func + arrows + esc, etc
	for (unsigned int i = 255; i<GLFW_KEY_LAST; i++) {
		handleKey(i);
	}
	//  window size
	glfwGetWindowSize(_window, &_windowWidth, &_windowHeight);

	glfwGetCursorPos(_window, &_mouseX, &_mouseY);

	// Fix cursor position if window size is different from the set resolution
	_mouseX = ((float)SWIDTH / _windowWidth) * _mouseX;
	_mouseY = ((float)SHEIGHT / _windowHeight) * _mouseY;

	// mouse buttons
	for (unsigned int i = 0; i<GLFW_MOUSE_BUTTON_LAST; i++) {
		handleMouse(i);
	}
}

void Input::handleMouse(unsigned int button) {
	if (glfwGetMouseButton(_window, button) == GLFW_PRESS) {
		if (_mouse[button] == false) { // if first time pressed down
			_mouse[button] = true;
			_mouseDown[button] = true;
			//std::cout << "DOWN: " << button << std::endl;
		} else {
			// not the first time this is pressed
			// keys[button] is still true;
			_mouseDown[button] = false;
		}
	}
	if (glfwGetMouseButton(_window, button) == GLFW_RELEASE) {
		if (_mouse[button] == true) { // still pressed
			_mouse[button] = false;
			_mouseUp[button] = true;
			//std::cout << "UP: " << button << std::endl;
		} else {
			_mouseUp[button] = false;
		}
	}
}

void Input::handleKey(unsigned int key) {
	if (glfwGetKey(_window, key) == GLFW_PRESS) {
		if (_keys[key] == false) { // if first time pressed down
			_keys[key] = true;
			_keysDown[key] = true;
			//std::cout << "DOWN: " << key << std::endl;
		} else {
			// not the first time this is pressed
			// keys[key] is still true;
			_keysDown[key] = false;
		}
	}
	if (glfwGetKey(_window, key) == GLFW_RELEASE) {
		if (_keys[key] == true) { // still pressed
			_keys[key] = false;
			_keysUp[key] = true;
			//std::cout << "UP: " << key << std::endl;
		} else {
			_keysUp[key] = false;
		}
	}
}