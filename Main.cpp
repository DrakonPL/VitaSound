#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <time.h>

//psp2
#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/touch.h>
#include <vita2d.h>

//audio
extern "C"
{
	#include "Audio.h"
}

AudioHandler _audio;


extern unsigned int basicfont_size;
extern unsigned char basicfont[];

SceCtrlData     pad;
SceTouchData    touch;

int fxTouch;
int fyTouch;

#define lerp(value, from_max, to_max) ((((value*10) * (to_max*10))/(from_max*10))/10)
#define EXIT_COMBO (SCE_CTRL_START | SCE_CTRL_SELECT)
#define BLACK   RGBA8(  0,   0,   0, 255)
#define WHITE   RGBA8(255, 255, 255, 255)

bool pressed = true;

//for fps
int fps;
long curTime = 0, lateTime = 0, count = 0, totalFrames = 0, beginTime = 0;
float msec = 0.0f, average = 0.0f;

void CalcFPS()
{
	count++;
	time_t seconds;
	time( &seconds );
	curTime = (long)seconds;
	if ( lateTime != curTime )
	{
		lateTime = curTime;
		msec = (1.0f / (float)count);
		totalFrames += count;
		average = (float)totalFrames / (float)(curTime - beginTime);
		fps = (int)count;
		count = 0;
	}
}

void init_stuff()
{
    //init time counter
	time_t begin;
	time( &begin );
	beginTime = (long)begin;

	//init sound
	InitializeAudio(&_audio);
	
	//load sound
	//stream ogg from file as background soud - only 1 background sound possible
	//LoadOgg(&_audio, "cache0:/VitaDefilerClient/Documents/music.ogg", AUDIO_OUT_BGM,0);
	
	//stream wav from file as main sound - 8 sounds possible
	//LoadWav(&_audio, "cache0:/VitaDefilerClient/Documents/music.wav", AUDIO_OUT_MAIN,0);
	
	//load wav from to memory and play as main sound - 8 sounds possible
	LoadWav(&_audio, "cache0:/VitaDefilerClient/Documents/organ.wav", AUDIO_OUT_MAIN,1);
	
	//play sound
	PlayAudio(&_audio);
}

int main()
{
    vita2d_init();
    vita2d_set_clear_color(BLACK);
	
	init_stuff();

    sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG_WIDE);

    vita2d_font *font = vita2d_load_font_mem(basicfont, basicfont_size);

    while (1) 
	{
		sceKernelPowerTick(SCE_KERNEL_POWER_TICK_DISABLE_AUTO_SUSPEND);
		sceKernelPowerTick(SCE_KERNEL_POWER_TICK_DISABLE_OLED_OFF);

        sceCtrlPeekBufferPositive(0, &pad, 1);

        if (pad.buttons == EXIT_COMBO)
		{
            break;
        }
		
		//start drawing
        vita2d_start_drawing();
        vita2d_clear_screen();

		vita2d_font_draw_textf(font, 10, 10, WHITE, 25,"FPS: %4d  AVG: %3.1f  MS: %3f\n", fps, average, msec);	
        vita2d_font_draw_text(font, 650, 10, WHITE, 25, "Press Start + Select to exit");

		if (pad.buttons & SCE_CTRL_SQUARE)
		{
			if(pressed)
			{
				
				pressed = false;				
			}
        }
		else
		{
			pressed = true;
		}

        vita2d_end_drawing();
        vita2d_swap_buffers();
		
		CalcFPS();
    }
	
	StopAudio(&_audio);
	TerminateAudio(&_audio);

    vita2d_fini();
    vita2d_free_font(font);
	
	sceKernelExitProcess(0);

    return 0;
}
