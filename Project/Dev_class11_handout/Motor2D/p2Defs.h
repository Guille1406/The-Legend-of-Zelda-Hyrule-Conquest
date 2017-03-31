#ifndef __P2DEFS_H__
#define __P2DEFS_H__

#include <stdio.h>
#include <list>
#include "SDL\include\SDL.h"
//  NULL just in case ----------------------

#ifdef NULL
#undef NULL
#endif
#define NULL  0

// Deletes a buffer
#define RELEASE( x ) \
    {                        \
    if( x != NULL )        \
	    {                      \
      delete x;            \
	  x = NULL;              \
	    }                      \
    }

// Deletes an array of buffers
#define RELEASE_ARRAY( x ) \
    {                              \
    if( x != NULL )              \
	    {                            \
      delete[] x;                \
	  x = NULL;                    \
	    }                            \
                              \
    }

#define IN_RANGE( value, min, max ) ( ((value) >= (min) && (value) <= (max)) ? 1 : 0 )
#define MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )
#define MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )
#define TO_BOOL( a )  ( (a != 0) ? true : false )

typedef unsigned int uint;
typedef unsigned __int32 uint32;
typedef unsigned __int64 uint64;
typedef unsigned char uchar;

template <class VALUE_TYPE> void SWAP(VALUE_TYPE& a, VALUE_TYPE& b)
{
	VALUE_TYPE tmp = a;
	a = b;
	b = tmp;
}

// Standard string size
#define SHORT_STR	32
#define MID_STR		255
#define HUGE_STR	8192

// Joins a path and file
inline const char* const PATH(const char* folder, const char* file)
{
	static char path[MID_STR];
	sprintf_s(path, MID_STR, "%s/%s", folder, file);
	return path;
}

// Performance macros
#define PERF_START(timer) timer.Start()
#define PERF_PEEK(timer) LOG("%s took %f ms", __FUNCTION__, timer.ReadMs())

//some usefull str
//doing that, they are created only one time
const static std::string empty_char = "";
const static std::string password_char = "*";
const static std::string true_str = "true";
const static std::string false_str = "false";


static const SDL_Rect rect_button = { 0,0,32,32 };
static const SDL_Rect rect_pressed_button = { 192,64,32,32 };
static const SDL_Rect rect_movable_block = { 96,0,32,32 };
static const SDL_Rect rect_Heart = { 128,0,32,32 };
static const SDL_Rect rect_jar = { 160,0,32,32 };
static const SDL_Rect rect_key = { 192,0,16,32 };
static const SDL_Rect rect_boss_key = { 208,0,32,32 };
static const SDL_Rect rect_sign = { 144,32,32,32 };
static const SDL_Rect rect_lever_blue = { 176,32,32,32 };
static const SDL_Rect rect_lever_red = { 208,32,32,32 };
static const SDL_Rect rect_lever_block_blue_off = { 0,64,32,32 };
static const SDL_Rect rect_lever_block_blue_on = { 32,64,32,32 };
static const SDL_Rect rect_lever_block_red_off = { 64,64,32,32 };
static const SDL_Rect rect_lever_block_red_on = { 96,64,32,32 };
static const SDL_Rect rect_chest_close = { 128,64,32,32 };
static const SDL_Rect rect_chest_open = { 160,64,32,32 };
static const SDL_Rect rect_Giant_chest_close = { 0,96,64,48 };
static const SDL_Rect rect_Giant_chest_open = { 64,96,64,48 };
static const SDL_Rect rect_door_down = { 240,-1,64,64 };
#endif