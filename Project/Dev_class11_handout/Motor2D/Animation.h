#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SDL/include/SDL_rect.h"
#define MAX_FRAMES 25

struct Frame {
	SDL_Rect rect = { 0,0,0,0 };
	iPoint pivot = { 0,0 };
};


class Animation
{
public:
	bool loop = true;
	float speed = 1.0f;
	iPoint pivot = {0,0};
	//std::vector<SDL_Rect> frames;
	Frame frames[MAX_FRAMES];
	int last_frame = 0;
private:
	float current_frame = 0.0f;

	int loops = 0;

public:

	Animation()
	{}

	Animation(const Animation& anim) : loop(anim.loop), speed(anim.speed), last_frame(anim.last_frame)
	{
		this->pivot = anim.pivot;
		SDL_memcpy(&frames, anim.frames, sizeof(frames));
	}

	void PushBack(const Frame& rect)
	{
		frames[last_frame++] = rect;
	}

	Frame& GetCurrentFrame()
	{
		current_frame += speed;
		if(current_frame >= last_frame)
		{
			current_frame = (loop) ? 0.0f : last_frame - 1;
			loops++;
		}

		return frames[(int)current_frame];
	}

	bool Finished() const
	{
		return loops > 0;
	}

	void Reset()
	{
		current_frame = 0.0f;
		loops = 0;
	}
};

#endif