#ifndef CONFIG_H
#define CONFIG_H

#define SWIDTH 1200 // The screen width
#define SHEIGHT 800 // The screen height

#define FULLSCREEN 0 // Fullscreen or not(0=not, 1=fullscreen, 2=windowed fullscreen)

#define RESIZABLE 0 // Resizable or not

#define WINDOWNAME "Centauri framework" // The window name

#define VSYNC 0 // VSYNC on (1) or off (0)

#define MSAA 4 // MSAA (Anti Aliasing) (0=off or use 4 or 8 for Anti Aliasing, higher is possible but it costs more performance)

// Default shaders for Renderering
#define DEFAULTFRAMEBUFFERVERTEXSHADER "shaders/framebuffer/default_framebuffer_shader.vert" // FrameBuffer vertexshader (path to the file)
#define DEFAULTFRAMEBUFFERFRAGMENTSHADER "shaders/framebuffer/default_framebuffer_shader.frag" // FrameBuffer fragmentshader (path to the file)
#define DEFAULTVERTEXSHADER "shaders/sprite/default_vert_shader.vert" // Sprite vertexshader (path to the file)
#define DEFAULTFRAGMENTSHADER "shaders/sprite/default_frag_shader.frag" // Sprite fragmentshader (path to the file)
#define DEFAULTGRAYSCALEFRAGMENTSHADER "shaders/sprite/default_frag_shader_grayscale.frag" // Sprite grayscale fragmentshader (path to the file)
#define DEFAULTTEXTVERTEXSHADER "shaders/text/default_text_shader.vert" // Text vertexshader (path to the file)
#define DEFAULTTEXTFRAGMENTSHADER "shaders/text/default_text_shader.frag" // Text fragmentshader (path to the file)
#define DEFAULTFRAGMENTSHADERBASICSHAPES "shaders/sprite/default_frag_shader_basicshapes.frag" // BasicShapes fragmentshader (path to the file)

#define DEFAULTFILTER 3 // Texture filter (0=No filtering, 1=Bilinear, 2=Bilinear mipmap, 3=Trilinear)
#define DEFAULTWRAP 1 // Texture clamping (0=repeat, 1=mirror, 2=clamp)

#endif
