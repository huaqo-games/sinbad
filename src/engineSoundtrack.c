#include "engine.h"

Soundtrack LoadSoundtrack(const char* musicPath){
    Soundtrack soundtrack = {
        .music = LoadMusicStream(musicPath),
        .playing = false,
		    .paused = false
    };
    return soundtrack; 
}

void UpdateSoundtrack(Soundtrack *soundtrack, bool shouldPlay){

	if (shouldPlay && !soundtrack->playing){
		PlayMusicStream(soundtrack->music);
    soundtrack->playing = true;
		soundtrack->paused = false;
	} else if (!shouldPlay && soundtrack->playing){
		PauseMusicStream(soundtrack->music);
    soundtrack->playing = false;
		soundtrack->paused = true;
	} else if (shouldPlay && soundtrack->playing) {
		UpdateMusicStream(soundtrack->music);
	}

}

