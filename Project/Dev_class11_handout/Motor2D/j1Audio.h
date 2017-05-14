#ifndef __j1AUDIO_H__
#define __j1AUDIO_H__

#include "j1Module.h"
#include <list>
#define DEFAULT_MUSIC_FADE_TIME 2.0f

struct _Mix_Music;
struct Mix_Chunk;

class j1Audio : public j1Module
{
public:

	j1Audio();

	// Destructor
	virtual ~j1Audio();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	bool Start();

	// Called before quitting
	bool CleanUp();

	// Play a music file
	bool PlayMusic(const char* path, float fade_time = DEFAULT_MUSIC_FADE_TIME);

	// Load a WAV in memory
	unsigned int LoadFx(const char* path);

	// Play a previously loaded WAV
	bool PlayFx(unsigned int fx, int repeat = 0);
	uint button_sound = 0;
	uint secret_sound = 0;

	bool StopMusic(float fade_time);
	bool ResumeMusic();
	void VolumeMusic(int volume);
	
private:

	_Mix_Music*			music = nullptr;
	std::list<Mix_Chunk*> fx;
	/*boss_defeated_sound = App->audio->LoadFx("audio/fx/boss defeated");
	boss_hit_sound = App->audio->LoadFx("audio/fx/boss-hit");
	boss_invencible_sound = App->audio->LoadFx("audio/fx/boss-invencible");
	boss_laser_sound = App->audio->LoadFx("audio/fx/boss_laser_countdown");
	boss_dies_sound = App->audio->LoadFx("audio/fx/boss_dies");*/
};

#endif // __j1AUDIO_H__