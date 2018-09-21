#ifndef CONFIG_H
#define CONFIG_H

// screenwidth, screenheight
#define SWIDTH 1200 // The screen width
#define SHEIGHT 800 // The screen height

#define FULLSCREEN 0 // Fullscreen or not(0=not, 1=fullscreen, 2=windowed fullscreen)

#define RESIZABLE 1 // Resizable or not

#define WINDOWNAME "Centauri Framework" // The window name

#define VSYNC 1 // VSYNC on (1) or off (0)

#define MSAA 4 // MSAA (Anti Aliasing) (0=off or use 4 or 8 for Anti Aliasing, higher is possible but it costs more performance)

// defaultshader for Renderer as fallback if Sprite has no shader defined
#define DEFAULTVERTEXSHADER "shaders/default_vert_shader.vert" // vertexshader (path to the file)
#define DEFAULTFRAGMENTSHADER "shaders/default_frag_shader.frag" // fragmentshader (path to the file)
#define DEFAULTGRAYSCALEFRAGMENTSHADER "shaders/default_frag_shader_grayscale.frag" // grayscale fragmentshader (path to the file)
#define DEFAULTFRAGMENTSHADERBASICSHAPES "shaders/default_frag_shader_basicshapes.frag" // BasicShapes fragmentshader (path to the file)

#define DEFAULTFILTER 3 // texture filter (0=No filtering, 1=Bilinear, 2=Bilinear mipmap, 3=Trilinear)
#define DEFAULTWRAP 1 // texture clamping (0=repeat, 1=mirror, 2=clamp)

#endif
