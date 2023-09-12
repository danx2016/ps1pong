#ifndef _SFX_H_
#define _SFX_H_

#include <stdint.h>

#define VAG_HEADER_SIZE 48
#define SPU_START_CHANNEL 12

#define SOUND_PADDLE_HIT  0
#define SOUND_PADDLE_WALL 1
#define SOUND_VERTICAL    2

// vag sounds data
extern const uint8_t _binary_sounds_sound0_vag_start[];
extern const uint8_t _binary_sounds_sound1_vag_start[];
extern const uint8_t _binary_sounds_sound2_vag_start[];

extern const uint32_t _binary_sounds_sound0_vag_size[];
extern const uint32_t _binary_sounds_sound1_vag_size[];
extern const uint32_t _binary_sounds_sound2_vag_size[];

extern void sfx_init();
extern void sfx_play(uint8_t sound_id);
extern void sfx_silence(uint8_t voice_channel);

#endif /* _SFX_H_ */