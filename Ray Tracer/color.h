#ifndef COLOR_H
#define COLOR_H

struct Color{
	float r;
	float g;
	float b;

	Color();
	Color(float rgb);
	Color(float r, float g, float b);

	virtual ~Color();

	void clamp();
	float getBrightness();

	Color& operator =(const Color& c);
	Color& operator +=(const Color& c);
	Color& operator *=(const Color& c);
	Color& operator *=(float f);
};

inline Color operator +(const Color& c1, const Color& c2){
	return Color(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
}

inline Color operator *(const Color& c1, const Color& c2){
	return Color(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b);
}

inline Color operator *(const Color& c, float f){
	return Color(c.r * f, c.g * f, c.b * f);
}

inline Color operator *(float f, const Color& c){
	return Color(f * c.r, f * c.g, f * c.b);
}

#endif // COLOR_H
