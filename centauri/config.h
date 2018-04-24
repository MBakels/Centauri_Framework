#ifndef CONFIG_H
#define CONFIG_H

// screenwidth, screenheight
#define SWIDTH 1200 // The screen width
#define SHEIGHT 800 // The screen height

#define FULLSCREEN 0 // Fullscreen or not(0=not, 1=fullscreen, 2=windowed fullscreen)

#define RESIZABLE 1 // Resizable or not

#define WINDOWNAME "Centauri Framework" // The window name

// defaultshader for Renderer as fallback if Sprite has no shader defined
#define DEFAULTVERTEXSHADER "shaders/default_vert_shader.vert" // vertexshader (path to the file)
#define DEFAULTFRAGMENTSHADER "shaders/default_frag_shader.frag" // fragmentshader (path to the file)
#define DEFAULTGRAYSCALEFRAGMENTSHADER "shaders/default_frag_shader_grayscale.frag" // grayscale fragmentshader (path to the file)

#define DEFAULTFILTER 1 // texture filter
#define DEFAULTWRAP 1 // texture clamping (0=repeat, 1=mirror, 2=clamp)

#endif
