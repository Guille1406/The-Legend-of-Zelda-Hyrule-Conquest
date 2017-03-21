#ifndef __COLOR_H__
#define __COLOR_H__

#include "p2Defs.h"

struct Color
{
	//This struct is for RGB colors from 255 to 0, not from 1.0 to 0.0

	uint r, g, b, a = 0;

	Color() : r(0), g(0), b(0), a(100)
	{}

	Color(int r, int g, int b, int a = 100) : r(r), g(g), b(b), a(a)
	{}

	void Set(int r, int g, int b, int a = 100)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	int operator () (int i)
	{
		int ret = 0;

		if ((i >= 0) && (i < 3))
		{
			switch (i) {
			case 0:
				ret = r;
				break;
			case 1:
				ret = g;
				break;
			case 2:
				ret = b;
				break;
			}
		}
		
		return ret;
	}
};

//Reds
extern Color IndianRed;
extern Color LightCoral;
extern Color Salmon;
extern Color DarkSalmon;
extern Color LightSalmon;
extern Color Crimson;
extern Color Red;
extern Color FireBrick;
extern Color DarkRed;
//Pinks
extern Color Pink;
extern Color LightPink;
extern Color HotPink;
extern Color DeepPink;
extern Color MediumVioletRed;
extern Color PaleVioletRed;
//Oranges
extern Color Coral;
extern Color Tomato;
extern Color OrangeRed;
extern Color DarkOrange;
extern Color Orange;
//Yellows
extern Color Gold;
extern Color Yellow;
extern Color LightYellow;
extern Color LemonChion;
extern Color LightGoldenrodYellow;
extern Color PapayaWhip;
extern Color Moccasin;
extern Color PeachPu;
extern Color PaleGoldenrod;
extern Color Khaki;
extern Color DarkKhaki;
//Pinks
extern Color Lavender;
extern Color Thistle;
extern Color Plum;
extern Color Violet;
extern Color Orchid;
extern Color Fuchsia;
extern Color Magenta;
extern Color MediumOrchid;
//Violets
extern Color MediumPurple;
extern Color BlueViolet;
extern Color DarkViolet;
extern Color DarkOrchid;
extern Color DarkMagenta;
extern Color Purple;
//Violet-Blues
extern Color Indigo;
extern Color SlateBlue;
extern Color DarkSlateBlue;
//Greens
extern Color GreenYellow;
extern Color Chartreuse;
extern Color LawnGreen;
extern Color Lime;
extern Color LimeGreen;
extern Color PaleGreen;
extern Color LightGreen;
extern Color MediumSpringGreen;
extern Color SpringGreen;
extern Color MediumSeaGreen;
extern Color SeaGreen;
extern Color ForestGreen;
extern Color Green;
extern Color DarkGreen;
extern Color YellowGreen;
extern Color OliveDrab;
extern Color Olive;
extern Color DarkOliveGreen;
//Green-Blues
extern Color MediumAquamarine;
extern Color DarkSeaGreen;
extern Color LightSeaGreen;
extern Color DarkCyan;
extern Color Teal;
//Blues
extern Color Aqua;
extern Color Cyan;
extern Color LightCyan;
extern Color PaleTurquoise;
extern Color Aquamarine;
extern Color Turquoise;
extern Color MediumTurquoise;
extern Color DarkTurquoise;
extern Color CadetBlue;
extern Color SteelBlue;
extern Color LightSteelBlue;
extern Color PowderBlue;
extern Color LightBlue;
extern Color SkyBlue;
extern Color LightSkyBlue;
extern Color DeepSkyBlue;
extern Color DodgerBlue;
extern Color CornlowerBlue;
extern Color MediumSlateBlue;
extern Color RoyalBlue;
extern Color Blue;
extern Color MediumBlue;
extern Color DarkBlue;
extern Color Navy;
extern Color MidnightBlue;
//Browns
extern Color Cornsilk;
extern Color BlanchedAlmond;
extern Color Bisque;
extern Color NavajoWhite;
extern Color Wheat;
extern Color BurlyWood;
extern Color Tan;
extern Color RosyBrown;
extern Color SandyBrown;
extern Color Goldenrod;
extern Color DarkGoldenrod;
extern Color Peru;
extern Color Chocolate;
extern Color SaddleBrown;
extern Color Sienna;
extern Color Brown;
extern Color Maroon;
//Whites
extern Color White;
extern Color Snow;
extern Color Honeydew;
extern Color MintCream;
extern Color Azure;
extern Color AliceBlue;
extern Color GhostWhite;
extern Color WhiteSmoke;
extern Color Seashell;
extern Color Beige;
extern Color OldLace;
extern Color FloralWhite;
extern Color Ivory;
extern Color AntiqueWhite;
extern Color Linen;
extern Color LavenderBlush;
extern Color MistyRose;
//Greys
extern Color Gainsboro;
extern Color LightGrey;
extern Color Silver;
extern Color DarkGray;
extern Color Gray;
extern Color DimGray;
extern Color LightSlateGray;
extern Color SlateGray;
extern Color DarkSlateGray;
//Black
extern Color Black;

#endif // __COLOR_H__