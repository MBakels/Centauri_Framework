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

The framework is tested in windows 10 using visual studio 2017. If you are using something else I can't guarantee it will work.

## Libraries

- glad: <http://glew.sourceforge.net/>
- glfw: <http://www.glfw.org/>
- glm: <http://glm.g-truc.net/index.html>
- freetype2: <https://www.freetype.org/>
- stb_image: <https://github.com/nothings/stb/>

## Other files

- acari-sans font [License](centauri/fonts/acari-sans/OFL.TXT)

## Sources

Most of what I learnt I learnt on [learnopengl.com](https://learnopengl.com/).
I also used my teachers framework as reference while developing mine, you can find his here <https://github.com/rktrlng/rt2d>.

## License & copyright

@ Marco Bakels

Licensed under the [MIT License](LICENSE).
