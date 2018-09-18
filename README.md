## About Centauri framework

Centauri framework is a basic 2D framework that is used for making games. It is still a work in progress.

## Compiling

You can use CMake to create the project files.
You can download it here https://cmake.org/
Under windows run this in the PowerShell to generate the project files, the project files will be placed in a folder called `build`.

```
  mkdir build
  cd build
  cmake -Wno-dev ..
```

The framework is tested in windows 10 using visual studio 2017. If you are using something else i can't guarantee it will work.

## Libraries

- glad: <http://glew.sourceforge.net/>
- glfw: <http://www.glfw.org/>
- glm: <http://glm.g-truc.net/index.html>
- freetype2: <https://www.freetype.org/>

## License & copyright

@ Marco Bakels

Licensed under the [MIT License](LICENSE).
