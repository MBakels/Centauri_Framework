#ifndef COLOR_H_
#define COLOR_H_

#include <algorithm>
#include <cmath>

#define BLACK   RGBAColor(0,   0,   0,   255)
#define GRAY    RGBAColor(127, 127, 127, 255)
#define RED     RGBAColor(255, 0,   0,   255)
#define ORANGE  RGBAColor(255, 127, 0,   255)
#define YELLOW  RGBAColor(255, 255, 0,   255)
#define GREEN   RGBAColor(0,   255, 0,   255)
#define CYAN    RGBAColor(0,   255, 255, 255)
#define BLUE    RGBAColor(0,   0,   255, 255)
#define MAGENTA RGBAColor(255, 0,   255, 255)
#define PINK    RGBAColor(255, 127, 255, 255)
#define WHITE   RGBAColor(255, 255, 255, 255)

// A struct that defines an HSV Color (Hue, Saturation, Brightness). Each value is a float between 0.0f and 1.0f.
struct HSVColor {
	float h = 0.0f;
	float s = 0.0f;
	float v = 1.0f;

	HSVColor() {
		h = 0.0f;
		s = 0.0f;
		v = 1.0f;
	}

	HSVColor(float hue, float sat, float val) {
		h = hue;
		s = sat;
		v = val;
	}
};



// A struct that defines an RGBA Color. Each value is an uint8_t (0-255).
struct RGBAColor {
	uint8_t r = 255;
	uint8_t g = 255;
	uint8_t b = 255;
	uint8_t a = 255;

	RGBAColor() {
		r = 255;
		g = 255;
		b = 255;
		a = 255;
	}

	RGBAColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}

	RGBAColor(uint8_t red, uint8_t green, uint8_t blue) {
		r = red;
		g = green;
		b = blue;
		a = 255;
	}

	RGBAColor(uint32_t color) {
		r = color >> 24 & 0xFF;
		g = color >> 16 & 0xFF;
		b = color >> 8 & 0xFF;
		a = color & 0xFF;
	}

	uint32_t asInt() {
		uint32_t color = (r << 24) + (g << 16) + (b << 8) + (a);
		return color;
	}

	inline bool operator==(const RGBAColor& rhs) {
		return ( r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a );
	}

	inline bool operator!=(const RGBAColor& rhs) {
		return !(*this == rhs);
	}
};


// HSV <-> RGBA conversion
struct Color
{
	// http://www.easyrgb.com/index.php?X=MATH&H=20#text20
	// RGBA to HSV conversion
	static HSVColor RGBA2HSV(RGBAColor rgba) {
		float var_R = (float) rgba.r / 255;
		float var_G = (float) rgba.g / 255;
		float var_B = (float) rgba.b / 255;

		float var_Min = std::min( std::min( var_R, var_G), var_B );
		float var_Max = std::max( std::max( var_R, var_G), var_B );
		float del_Max = var_Max - var_Min;

		float H = 0.0f;
		float S = 0.0f;
		float V = var_Max;

		if ( del_Max == 0 ) {
			H = 0;
			S = 0;
		} else {
			S = del_Max / var_Max;

			float del_R = ( ( ( var_Max - var_R ) / 6.0f ) + ( del_Max / 2.0f ) ) / del_Max;
			float del_G = ( ( ( var_Max - var_G ) / 6.0f ) + ( del_Max / 2.0f ) ) / del_Max;
			float del_B = ( ( ( var_Max - var_B ) / 6.0f ) + ( del_Max / 2.0f ) ) / del_Max;

			if      ( var_R == var_Max ) H = del_B - del_G;
			else if ( var_G == var_Max ) H = ( 1.0f / 3.0f ) + del_R - del_B;
			else if ( var_B == var_Max ) H = ( 2.0f / 3.0f ) + del_G - del_R;

			if ( H < 0.0f ) H += 1.0f;
			if ( H > 1.0f ) H -= 1.0f;
		}
		return HSVColor(H, S, V);
	}

	// http://www.easyrgb.com/index.php?X=MATH&H=21#text21
	// HSV to RGBA conversion
	static RGBAColor HSV2RGBA(HSVColor hsv) {
		uint8_t R = 0;
		uint8_t G = 0;
		uint8_t B = 0;
		if ( hsv.s == 0 ) {
			R = hsv.v * 255;
			G = hsv.v * 255;
			B = hsv.v * 255;
		} else {
			float var_h = hsv.h * 6;
			if ( var_h >= 6.0f ) { var_h = 0; }
			int var_i = int( var_h );
			float var_1 = hsv.v * ( 1.0f - hsv.s );
			float var_2 = hsv.v * ( 1.0f - hsv.s * ( var_h - var_i ) );
			float var_3 = hsv.v * ( 1.0f - hsv.s * ( 1.0f - ( var_h - var_i ) ) );
			float var_r;
			float var_g;
			float var_b;
			if      ( var_i == 0 ) { var_r = hsv.v ; var_g = var_3 ; var_b = var_1 ; }
			else if ( var_i == 1 ) { var_r = var_2 ; var_g = hsv.v ; var_b = var_1 ; }
			else if ( var_i == 2 ) { var_r = var_1 ; var_g = hsv.v ; var_b = var_3 ; }
			else if ( var_i == 3 ) { var_r = var_1 ; var_g = var_2 ; var_b = hsv.v ; }
			else if ( var_i == 4 ) { var_r = var_3 ; var_g = var_1 ; var_b = hsv.v ; }
			else                   { var_r = hsv.v ; var_g = var_1 ; var_b = var_2 ; }

			R = var_r * 255;
			G = var_g * 255;
			B = var_b * 255;
		}
		return RGBAColor(R, G, B, 255);
	}

	// Rotate RGBA color (use HSV)
	static RGBAColor rotate(RGBAColor rgba, float step) {
		HSVColor hsv = RGBA2HSV(rgba);
		hsv.h += step;
		if (hsv.h > 1.0f) { hsv.h -= 1.0f; }
		if (hsv.h < 0.0f) { hsv.h += 1.0f; }
		return HSV2RGBA(hsv);
	}

	static RGBAColor lerpColor(RGBAColor c1, RGBAColor c2, float amount) {
		if (amount < 0) { amount = 0; }
		if (amount > 1) { amount = 1; }

		uint8_t r = floor(c1.r + (c2.r-c1.r)*amount);
		uint8_t g = floor(c1.g + (c2.g-c1.g)*amount);
		uint8_t b = floor(c1.b + (c2.b-c1.b)*amount);
		uint8_t a = floor(c1.a + (c2.a-c1.a)*amount);

		return RGBAColor(r, g, b, a);
	}
};

#endif
