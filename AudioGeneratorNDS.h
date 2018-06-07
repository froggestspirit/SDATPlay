
bool running;
void readTemp(int bytes);
void readTempKey(int bytes);
bool NDS_begin(int songID, int sRate);
void NDS_decodeADPCMSample(int i,unsigned char nibble);
bool NDS_loadSong(int id);
unsigned char NDS_Cnv_Attack(unsigned char attk);//table generated from Fincs FSS
int NDS_Calc_Attack(unsigned char i, unsigned char frame);
unsigned short NDS_Cnv_Fall(unsigned char fall);//table generated from Fincs FSS
int NDS_Cnv_Sust(unsigned char sust);//table generated from Fincs FSS
int NDS_Cnv_dB(unsigned char vol);//table generated from Fincs FSS
unsigned short NDS_Cnv_Vol(int db);
unsigned long NDS_getSampleAddress(unsigned char bank,unsigned short inst);
unsigned long NDS_getAddress(unsigned long addr);
bool NDS_setInst(int i, unsigned char index);
bool NDS_setSample(int i, unsigned long address);
char * NDS_loop();
bool NDS_stop();
bool NDS_isRunning(){ return running;}
void buttonLoop();
void buttonPause();
void buttonNext();
void buttonShuffle();
int sampleRate;

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
bool validInst[16];
bool validSample[16];

unsigned char slotAttack[16];
unsigned short slotDecay[16];
signed long slotSustain[16];
unsigned short slotRelease[16];
unsigned char slotPan[16];
signed short slotPanL[16];
signed short slotPanR[16];
signed long slotADSRVol[16];
unsigned char slotADSRState[16];

unsigned long instAddress[128];//address of the instrument definition for instruments 0-127
unsigned char instType[128];

signed short volModL[16];
signed short volModR[16];
int mixer[2];//pre mixer
char soundOut[6];//final output
bool chActive[16];//is the channel on
unsigned long slotPitch[16];
unsigned long slotPitchFill[16];
unsigned long samplePitch[16];
unsigned long samplePitchFill[16];
unsigned long sampleOffset[16];//offset of the current sample
unsigned long samplePos[16];//current position in the sample
unsigned long sampleEnd[16];//the end of the sample
unsigned long sampleLoop[16];//loop point
unsigned long sampleLoopLength[16];//length of loop point to end
unsigned char sampleFormat[16];//format of the sample
bool sampleLoops[16];//does the sample loop
bool sampleDone[16];//did the non-looping sample finish

bool sampleNibbleLow[16];
unsigned char tempNibble[16];
signed char sampleStepIndex[16];
signed short sampleDiff;
signed short samplePredictor[16];
signed short sampleOutput[16];
signed short sampleStep[16];
signed char sampleStepIndexLoop[16];
signed short samplePredictorLoop[16];
signed short sampleStepLoop[16];
signed char sampleStepIndexStart[16];
signed short samplePredictorStart[16];
signed short sampleStepStart[16];
unsigned long keyRoot[16*0x80];//root key for each key (freq)
char keyRootVal[16*0x80];//root key for each key
unsigned long curKeyRoot[16];
unsigned char keyBank[16*0x80];//for split key instruments
unsigned short keySample[16*0x80];//for split key instruments
unsigned char keyAttack[16*0x80];
unsigned char keyDecay[16*0x80];
unsigned char keySustain[16*0x80];
unsigned char keyRelease[16*0x80];
unsigned char keyPan[16*0x80];

signed short lastSample[2];

#include "AudioGeneratorNDS.cpp"
