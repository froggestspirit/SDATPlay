/*
 * $Id$
 *
 * This program uses the PortAudio Portable Audio Library.
 * For more information see: http://www.portaudio.com
 * Copyright (c) 1999-2000 Ross Bencina and Phil Burk
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * The text above constitutes the entire PortAudio license; however, 
 * the PortAudio community also makes the following non-binding requests:
 *
 * Any person wishing to distribute modifications to the Software is
 * requested to send the modifications to the original developer so that
 * they can be incorporated into the canonical version. It is also 
 * requested that these non-binding requests be included along with the 
 * license above.
 */

#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <math.h>
#define min(a,b) fmin(a,b)
#define max(a,b) fmax(a,b)
#include <portaudio.h>
#define NUM_SECONDS   (40)
#define SAMPLE_RATE   (96000)
unsigned char sdat[0x8000000];
int filePos;
int song;
int totalSongs;

short *DSAudio;
short *lastDSAudio;
char *filename;
FILE* sdatf = NULL;
#include "AudioGeneratorNDS.h"
#include <ncurses.h>

typedef struct
{
    float left_phase;
    float right_phase;
}
paTestData;

struct termios saved_attributes;

void
reset_input_mode (void)
{
  tcsetattr (STDIN_FILENO, TCSANOW, &saved_attributes);
}

void
set_input_mode (void)
{
  struct termios tattr;
  char *name;

  /* Make sure stdin is a terminal. */
  if (!isatty (STDIN_FILENO))
    {
      fprintf (stderr, "Not a terminal.\n");
      exit (EXIT_FAILURE);
    }

  /* Save the terminal attributes so we can restore them later. */
  tcgetattr (STDIN_FILENO, &saved_attributes);
  atexit (reset_input_mode);

  /* Set the funny terminal modes. */
  tcgetattr (STDIN_FILENO, &tattr);
  tattr.c_lflag &= ~(ICANON|ECHO); /* Clear ICANON and ECHO. */
  tattr.c_cc[VMIN] = 1;
  tattr.c_cc[VTIME] = 0;
  tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);
}

/* This routine will be called by the PortAudio engine when audio is needed.
** It may called at interrupt level on some machines so don't do anything
** that could mess up the system like calling malloc() or free().
*/
static int patestCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData )
{
    /* Cast data passed through stream to our structure. */
    paTestData *data = (paTestData*)userData;
    short *out = (short*)outputBuffer;
    unsigned int i;
    (void) inputBuffer; /* Prevent unused variable warning. */

    for( i=0; i<framesPerBuffer; i++ )
    {
        DSAudio=NDS_loop();
        if(running){
            lastDSAudio=DSAudio;
        }else{
            DSAudio=lastDSAudio;
            if(song>=(totalSongs-1)) song=-1;
            NDS_begin(++song,SAMPLE_RATE);
        }
        *out++ = (short)*(DSAudio);
        *out++ = (short)*(DSAudio+1);
        //*out++ = data->left_phase;  /* left */
        //*out++ = data->right_phase;  /* right */
        /* Generate simple sawtooth phaser that ranges between -1.0 and 1.0. */
        data->left_phase += 0.01f;
        /* When signal reaches top, drop back down. */
        if( data->left_phase >= 1.0f ) data->left_phase -= 2.0f;
        /* higher pitch so we can distinguish left and right. */
        data->right_phase += 0.03f;
        if( data->right_phase >= 1.0f ) data->right_phase -= 2.0f;
    }
    return 0;
}

/*******************************************************************/
static paTestData data;
int main(int argc, char *argv[])
{
    song=0;
    if(argc>1){
        filename=argv[1];
    }else{
        filename="platinum.sdat";
    }
    set_input_mode ();
    
    PaStream *stream;
    PaError err;
    sdatf = fopen(filename, "rb");
	if (0!=fseek(sdatf, 0, SEEK_END)) return false;
	int sizef=ftell(sdatf);
	if (0!=fseek(sdatf, 0, SEEK_SET)) return false;
	if (sizef!=fread(sdat, 1, sizef, sdatf)) return false;
	printf("SDAT Size: %X\n",sizef);
	fclose(sdatf);
    NDS_begin(song,SAMPLE_RATE);//SDAT Song Number, Frequency
    printf("PortAudio Test: output sawtooth wave.\n");
    /* Initialize our data for use by callback. */
    data.left_phase = data.right_phase = 0.0;
    /* Initialize library before making any other calls. */
    err = Pa_Initialize();
    if( err != paNoError ) goto error;
    
    /* Open an audio I/O stream. */
    err = Pa_OpenDefaultStream( &stream,
                                0,          /* no input channels */
                                2,          /* stereo output */
                                paInt16,  /* 32 bit floating point output */
                                SAMPLE_RATE,
                                256,        /* frames per buffer */
                                patestCallback,
                                &data );
    if( err != paNoError ) goto error;

    err = Pa_StartStream( stream );
    if( err != paNoError ) goto error;

    /* Sleep for several seconds. */
    //Pa_Sleep(NUM_SECONDS*1000);
    keypad(stdscr, TRUE);
    while(1){
        static int ch;
        //while ((ch = getchar()) != ERR) {
        ch = getchar();
        if      (ch=='a'){
            err = Pa_StopStream( stream );
            if(song<=0) song=totalSongs;
            NDS_begin(--song,SAMPLE_RATE);
            err = Pa_StartStream( stream );
        }else if (ch=='s'){
            err = Pa_StopStream( stream );
            if(song>=(totalSongs-1)) song=-1;
            NDS_begin(++song,SAMPLE_RATE);
            err = Pa_StartStream( stream );
        }else if (ch=='x'){
            err = Pa_StopStream( stream );
            NDS_stop();
            return 0;
        }
    }
    err = Pa_StopStream( stream );
    if( err != paNoError ) goto error;
    err = Pa_CloseStream( stream );
    if( err != paNoError ) goto error;
    Pa_Terminate();
    printf("Test finished.\n");
    return err;
error:
    Pa_Terminate();
    fprintf( stderr, "An error occured while using the portaudio stream\n" );
    fprintf( stderr, "Error number: %d\n", err );
    fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
    return err;
}
