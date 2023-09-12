#include <stdbool.h>
#include <libetc.h>

#include "sfx.h"
#include "music_player.h"
#include "third_party/nugget/modplayer/modplayer.h"

// mod music data
extern const uint8_t _binary_music_hit_start[];
extern const uint8_t _binary_music_hit_end[];
extern const uint8_t _binary_music_hit_size[];

static bool music_play_paused = false;

void music_play_init()
{
    MOD_Load((struct MODFileFormat*) _binary_music_hit_start);
    MOD_SetMusicVolume(8000);
}

void music_play_next_sample()
{
    if (!music_play_paused)
    {
        MOD_Poll();
    }
}

void music_play_pause()
{
    music_play_paused = true;
    VSync(0);
    sfx_silence(0);
    sfx_silence(1);
    sfx_silence(2);
    sfx_silence(3);
}

void music_play_resume()
{
    music_play_paused = false;
}
