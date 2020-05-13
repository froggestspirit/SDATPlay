
bool running;
void readTemp(int bytes);
void readTempKey(int bytes);
bool NDS_begin(int songID, int sRate);
bool NDS_loadSong(int id);
unsigned char NDS_Cnv_Attack(unsigned char attk);//table generated from Fincs FSS
int NDS_Calc_Attack(unsigned char i, unsigned char frame);
unsigned short NDS_Cnv_Fall(unsigned char fall);//table generated from Fincs FSS
int NDS_Cnv_Sust(unsigned char sust);//table generated from Fincs FSS
int NDS_Cnv_dB(unsigned char vol);//table generated from Fincs FSS
unsigned short NDS_Cnv_Vol(int db);
unsigned long NDS_getSampleAddress(unsigned char bank,unsigned short inst);
unsigned long NDS_getAddress(unsigned long addr);
bool NDS_decInst(int index);
int NDS_decSample(int ID, int freeSpace, unsigned long address);
float * NDS_loop();
bool NDS_stop();
bool NDS_isRunning(){ return running;}
void buttonLoop();
void buttonPause();
void buttonNext();
void buttonShuffle();
float sampleRate;

bool delayHit;
bool seqFrame;
int maxLoops;//number of times to loop the song before fading out
unsigned char timesLooped[16];
signed short fadeVol;
unsigned char loopi;
bool infLoop=false;
bool paused=false;

unsigned char temp[4];
unsigned char tempKey[8];
unsigned long temp32;
unsigned char varLength;
unsigned short headerSize;
unsigned long infoBlock;
unsigned long fatArray;
unsigned long sseqArray;
unsigned long sbnkArray;
unsigned long swarArray;
unsigned short sseqID;
unsigned short sbnkID;
unsigned short swarID[4];

int sseqIndex;
unsigned long sseqPointer;
unsigned long sbnkPointer;
unsigned long swarPointer[4];
unsigned long sseqSize;
unsigned long dataOffset;
unsigned long chPointer[16];
unsigned short usedTracks;
unsigned short sseqTempo;
unsigned short tempoFill;
unsigned char sseqVol;

unsigned char slotChannel[16];//sample playing in this slot belongs to what channel
unsigned char slotFree[16];//is this slot free?
unsigned char curSlot;
unsigned long slotMidiFreq[16];
unsigned char slotNote[16];
signed short slotNoteVel[16];
unsigned long slotNoteLen[16];
unsigned long chDelay[16];
unsigned char chInstrument[16];
unsigned char chPan[16];
signed short chPanL[16];
signed short chPanR[16];
signed short chVol[16];
unsigned char chTranspose[16];
int chPitchBendCur[16];
unsigned char chPitchBend[16];
unsigned char chPitchBendRange[16];
unsigned short chSweepPitch[16];
unsigned char chPriority[16];
unsigned char chPolyMono[16];
unsigned char chTie[16];
unsigned char chPort[16];
unsigned char chPortOn[16];
unsigned char chPortTime[16];
unsigned short chModDelay[16];
unsigned char chModDepth[16];
unsigned char chModSpeed[16];
unsigned char chModType[16];
unsigned char chModRange[16];
unsigned char chAttack[16];
unsigned char chDecay[16];
unsigned char chSustain[16];
unsigned char chRelease[16];
unsigned char chLoopTimes[16];//times left to loop
unsigned long chLoopOffset[16];//offset to return to from loop end marker
unsigned long chReturnOffset[16];//offset to return to from the call
bool chInCall[16];//track hit a call command and did not hit return yet
bool validInst[128];

float slotAttack[16];
float slotDecay[16];
float slotSustain[16];
float slotRelease[16];
unsigned char slotPan[16];
signed short slotPanL[16];
signed short slotPanR[16];
signed long slotADSRVol[16];
unsigned char slotADSRState[16];

unsigned long instAddress[128];//address of the instrument definition for instruments 0-127
unsigned char instType[128];

float volModL[16];
float volModR[16];
float mixer[2];//pre mixer
float soundOut[2];//final output
bool chActive[16];//is the channel on
float slotPitch[16];
float slotPitchFill[16];
unsigned short slotSampleID[16];//(channel instrument<<7)+note
float samplePitchFill[16];
float samplePos[16];//current position in the sample

float samplePitch[0x80*0x80];
unsigned long sampleOffset[0x80*0x80];//offset of the current sample
float sampleEnd[0x80*0x80];//the end of the sample
float sampleLoop[0x80*0x80];//loop point
float sampleLoopLength[0x80*0x80];//length of loop point to end
unsigned char sampleFormat[0x80*0x80];//format of the sample
bool sampleLoops[0x80*0x80];//does the sample loop

bool sampleDone[16];//did the non-looping sample finish
bool sampleNibbleLow;
unsigned char tempNibble;
signed char sampleStepIndex;
signed short sampleDiff;
signed short samplePredictor;
signed short sampleStep;
float sampleOutput[16];
unsigned long keyRoot[0x80*0x80];//root key for each key (freq)
char keyRootVal[0x80*0x80];//root key for each key
float curKeyRoot[16];
unsigned char keyBank[0x80*0x80];//for split key instruments
unsigned short keySample[0x80*0x80];//for split key instruments
unsigned short keySWAV[0x80*0x80];//for split key instruments
unsigned char keyAttack[0x80*0x80];
unsigned char keyDecay[0x80*0x80];
unsigned char keySustain[0x80*0x80];
unsigned char keyRelease[0x80*0x80];
unsigned char keyPan[0x80*0x80];

float lastSample[2];

unsigned short soundChannel4Bit;
int decSWAVFree;//position for free space
unsigned long decSWAVPointer[0x80*0x80];
float decSWAVBuffer[0x2000000];

#include "AudioGeneratorNDS.cpp"
