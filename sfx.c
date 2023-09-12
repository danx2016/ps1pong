#include <libspu.h>

#include "sfx.h"

static uint32_t sound0_spu_addr;
static uint32_t sound1_spu_addr;
static uint32_t sound2_spu_addr;

static uint32_t sound0_size;
static uint32_t sound1_size;
static uint32_t sound2_size;

#define SPU_RAM_START 0x1010

static void sfx_init_voices()
{
	SpuVoiceAttr voice_attr;
	voice_attr.mask = (
		SPU_VOICE_VOLL |
		SPU_VOICE_VOLR |
		SPU_VOICE_PITCH |
		SPU_VOICE_WDSA |
		SPU_VOICE_ADSR_AMODE |
		SPU_VOICE_ADSR_SMODE |
		SPU_VOICE_ADSR_RMODE |
		SPU_VOICE_ADSR_AR |
		SPU_VOICE_ADSR_DR |
		SPU_VOICE_ADSR_SR |
		SPU_VOICE_ADSR_RR |
		SPU_VOICE_ADSR_SL
	);

	voice_attr.volume.left = 0x3fff;
	voice_attr.volume.right = 0x3fff;
	voice_attr.pitch = 4096;
	voice_attr.a_mode = SPU_VOICE_LINEARIncN;
	voice_attr.s_mode = SPU_VOICE_LINEARIncN;
	voice_attr.r_mode = SPU_VOICE_LINEARDecN;
	voice_attr.ar = 0x0;
	voice_attr.dr = 0x0;
	voice_attr.sr = 0x0;
	voice_attr.rr = 0x0;
	voice_attr.sl = 0xf;

	voice_attr.voice = 1 << (SPU_START_CHANNEL + 0);
	voice_attr.addr = sound0_spu_addr;
	SpuSetVoiceAttr (&voice_attr);

	voice_attr.voice = 1 << (SPU_START_CHANNEL + 1);
	voice_attr.addr = sound1_spu_addr;
	SpuSetVoiceAttr (&voice_attr);

	voice_attr.voice = 1 << (SPU_START_CHANNEL + 2);
	voice_attr.addr = sound2_spu_addr;
	SpuSetVoiceAttr (&voice_attr);

	SpuSetKey(SpuOff, 1 << (SPU_START_CHANNEL + 0));
	SpuSetKey(SpuOff, 1 << (SPU_START_CHANNEL + 1));
	SpuSetKey(SpuOff, 1 << (SPU_START_CHANNEL + 2));
}

static void sfx_transfer_vag_to_spu(uint32_t spu_addr, uint8_t* vag_start, uint32_t vag_size)
{
    uint32_t l_top = SpuSetTransferStartAddr(spu_addr);
	uint32_t l_size = SpuWrite(vag_start + VAG_HEADER_SIZE, vag_size);
	SpuIsTransferCompleted (SPU_TRANSFER_WAIT);
}

void sfx_init()
{
    sound0_size = (uint32_t) _binary_sounds_sound0_vag_size;
    sound1_size = (uint32_t) _binary_sounds_sound1_vag_size;
    sound2_size = (uint32_t) _binary_sounds_sound2_vag_size;

    SpuInit();
    SpuSetCommonMasterVolume(0x3fff, 0x3fff);

    SpuSetTransferMode(SpuTransByDMA);
	sound0_spu_addr = SPU_RAM_START;
	sound1_spu_addr = sound0_spu_addr + sound0_size;
	sound2_spu_addr = sound1_spu_addr + sound1_size;
	sfx_transfer_vag_to_spu(sound0_spu_addr, (uint8_t*) _binary_sounds_sound0_vag_start, sound0_size);
	sfx_transfer_vag_to_spu(sound1_spu_addr, (uint8_t*) _binary_sounds_sound1_vag_start, sound1_size);
	sfx_transfer_vag_to_spu(sound2_spu_addr, (uint8_t*) _binary_sounds_sound2_vag_start, sound2_size);

	sfx_init_voices();
}

void sfx_play(uint8_t sound_id)
{
	SpuSetKey(SpuOn, 1 << (SPU_START_CHANNEL + sound_id));
}

void sfx_silence(uint8_t voice_channel)
{
	SpuSetKey(SpuOff, 1 << voice_channel);
}