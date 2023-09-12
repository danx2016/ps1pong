#ifndef _MUSIC_PLAYER_H_
#define _MUSIC_PLAYER_H_

extern void music_play_init();

// call this every vsync
extern void music_play_next_sample();

extern void music_play_pause();
extern void music_play_resume();

#endif /* _MUSIC_PLAYER_H_ */