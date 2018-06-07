//SDAT Player 1.0 FroggestSpirit


void readTemp(int bytes){
	for(int ini=0; ini<bytes; ini++){
		temp[ini]=sdat[filePos++];
	}
}

void readTempKey(int bytes){
	for(int ini=0; ini<bytes; ini++){
		tempKey[ini]=sdat[filePos++];
	}
}

#include "lookuptables.h"

void NDSbuttonloop(){
	infLoop^=1;
}
void NDSbuttonPause(){
	paused^=1;
	seqFrame=true;
}
void NDSbuttonNext(){
	running = false;
}
void NDSbuttonShuffle(){
	running = false;
}

bool NDS_loadSong(int id){//loads a song
    int idi=id;
	temp32=NDS_getAddress(sseqArray+(idi*4))+infoBlock;
	while(temp32==infoBlock){
		idi++;
		song++;
        if(idi>=totalSongs){
		idi=0;
		song=0;
	}
		temp32=NDS_getAddress(sseqArray+(idi*4))+infoBlock;
	}
	filePos=temp32;
	readTemp(4);
	sseqID=(temp[1]<<8);
	sseqID=(sseqID+temp[0]);
    printf("sseqID:%X\n",sseqID);
	readTemp(4);
	sbnkID=(temp[1]<<8);
	sbnkID=(sbnkID+temp[0]);
	temp32=NDS_getAddress(sbnkArray+(sbnkID*4))+infoBlock;
	filePos=temp32;
	readTemp(4);
	sbnkID=(temp[1]<<8);
	sbnkID=(sbnkID+temp[0]);
    printf("sbnkID:%X\n",sbnkID);
	readTemp(4);
	swarID[0]=(temp[1]<<8);
	swarID[0]=(swarID[0]+temp[0]);
	swarID[1]=(temp[3]<<8);
	swarID[1]=(swarID[1]+temp[2]);
	readTemp(4);
	swarID[2]=(temp[1]<<8);
	swarID[2]=(swarID[2]+temp[0]);
	swarID[3]=(temp[3]<<8);
	swarID[3]=(swarID[3]+temp[2]);
	for(int i=0; i<4; i++){
		if(swarID[i]!=0xFFFF){
			temp32=NDS_getAddress(swarArray+(swarID[i]*4))+infoBlock;
			filePos=temp32;
			readTemp(2);
			swarID[i]=(temp[1]<<8);
			swarID[i]=(swarID[i]+temp[0]);
		}
	}
    printf("swarID 1:%X\n",swarID[0]);
    printf("swarID 2:%X\n",swarID[1]);
    printf("swarID 3:%X\n",swarID[2]);
    printf("swarID 4:%X\n",swarID[3]);
	sseqPointer=NDS_getAddress(fatArray+(sseqID*0x10));
	dataOffset=sseqPointer+0x1C;
	sbnkPointer=NDS_getAddress(fatArray+(sbnkID*0x10));
	if(swarID[0]!=0xFFFF) swarPointer[0]=NDS_getAddress(fatArray+(swarID[0]*0x10));
	if(swarID[1]!=0xFFFF) swarPointer[1]=NDS_getAddress(fatArray+(swarID[1]*0x10));
	if(swarID[2]!=0xFFFF) swarPointer[2]=NDS_getAddress(fatArray+(swarID[2]*0x10));
	if(swarID[3]!=0xFFFF) swarPointer[3]=NDS_getAddress(fatArray+(swarID[3]*0x10));
    printf("sseqPointer:%X\n",sseqPointer);
    printf("sbnkPointer:%X\n",sbnkPointer);
    printf("swarPointer 1:%X\n",swarPointer[0]);
    printf("swarPointer 2:%X\n",swarPointer[1]);
    printf("swarPointer 3:%X\n",swarPointer[2]);
    printf("swarPointer 4:%X\n",swarPointer[3]);
	return true;
}

unsigned long NDS_getSampleAddress(unsigned char bank,unsigned short inst){//returns the absolute address of the SWAV header
	filePos=swarPointer[bank]+(inst*4)+0x3C;
	readTemp(4);
	temp32=(temp[3]<<8);
	temp32=((temp32+temp[2])<<8);
	temp32=((temp32+temp[1])<<8);
	temp32=(temp32+temp[0]);
	return temp32+swarPointer[bank];
}

unsigned long NDS_getAddress(unsigned long addr){//returns the 4-byte address at addr
	filePos=addr;
	readTemp(4);
	temp32=(temp[3]<<8);
	temp32=((temp32+temp[2])<<8);
	temp32=((temp32+temp[1])<<8);
	temp32=(temp32+temp[0]);
	return temp32;
}

bool NDS_setInst(int i, unsigned char index){
	if(instType[index]==0){//blank
		printf("ERROR:0 NDS_setInst(%X, %X)\n",i,index);
		return false;
	}else if(instType[index]<16){//single inst
		filePos=instAddress[index];
		readTemp(4);
		tempKey[0]=sdat[filePos++];
		keyBank[(i<<7)]=temp[2];
		keySample[(i<<7)]=temp[0]+(temp[1]<<8);
		keyRoot[(i<<7)]=MIDI_FREQ[tempKey[0]];
        keyRootVal[(i<<7)]=tempKey[0];
		readTemp(4);
		keyAttack[(i<<7)]=temp[0];
		keyDecay[(i<<7)]=temp[1];
		keySustain[(i<<7)]=temp[2];
		keyRelease[(i<<7)]=temp[3];
		temp[0]=sdat[filePos++];
		keyPan[(i<<7)]=temp[0];
	}else if(instType[index]==16){//range inst (like drumset)
		filePos=instAddress[index];
		readTempKey(2);
		int keyiPointer=(i<<7);
		for(int keyi=tempKey[0]; keyi<=tempKey[1]; keyi++){
			filePos=instAddress[index]+4+((keyi-tempKey[0])*12);
			readTemp(4);
			keyBank[keyiPointer+keyi]=temp[2];
			keySample[keyiPointer+keyi]=temp[0]+(temp[1]<<8);
			temp[0]=sdat[filePos++];
			keyRoot[keyiPointer+keyi]=MIDI_FREQ[temp[0]];
            keyRootVal[keyiPointer+keyi]=temp[0];
			readTemp(4);
			keyAttack[keyiPointer+keyi]=temp[0];
			keyDecay[keyiPointer+keyi]=temp[1];
			keySustain[keyiPointer+keyi]=temp[2];
			keyRelease[keyiPointer+keyi]=temp[3];
			temp[0]=sdat[filePos++];
			keyPan[keyiPointer+keyi]=temp[0];
		}
	}else if(instType[index]==17){//regional inst
		filePos=instAddress[index];
		readTempKey(8);
		int key=0;
		int keyiPointer=(i<<7);
		for(int keyi=0; keyi<8; keyi++){
			if(key<=tempKey[keyi]){
				filePos=instAddress[index]+10+(keyi*12);
				readTemp(4);
				keyBank[keyiPointer+key]=temp[2];
				keySample[keyiPointer+key]=temp[0]+(temp[1]<<8);
				temp[0]=sdat[filePos++];
				keyRoot[keyiPointer+key]=MIDI_FREQ[temp[0]];
                keyRootVal[keyiPointer+key]=temp[0];
				readTemp(4);
				keyAttack[keyiPointer+key]=temp[0];
				keyDecay[keyiPointer+key]=temp[1];
				keySustain[keyiPointer+key]=temp[2];
				keyRelease[keyiPointer+key]=temp[3];
				temp[0]=sdat[filePos++];
				keyPan[keyiPointer+key]=temp[0];
				key++;
			}
			while(key<=tempKey[keyi]){
				keyBank[keyiPointer+key]=keyBank[keyiPointer+(key-1)];
				keySample[keyiPointer+key]=keySample[keyiPointer+(key-1)];
				keyRoot[keyiPointer+key]=keyRoot[keyiPointer+(key-1)];
                keyRootVal[keyiPointer+key]=keyRootVal[keyiPointer+(key-1)];
				keyAttack[keyiPointer+key]=keyAttack[keyiPointer+(key-1)];
				keyDecay[keyiPointer+key]=keyDecay[keyiPointer+(key-1)];
				keySustain[keyiPointer+key]=keySustain[keyiPointer+(key-1)];
				keyRelease[keyiPointer+key]=keyRelease[keyiPointer+(key-1)];
				keyPan[keyiPointer+key]=keyPan[keyiPointer+(key-1)];
				key++;
			}
		}
	}else{
		printf("ERROR:%X NDS_setInst(%X, %X)\n",instType[index],i,index);
		return false;
	}
	return true;
}
bool NDS_setSample(int i, unsigned long address){
	if(address==0) return false;
	filePos=address;
	readTemp(4);
	sampleFormat[i]=temp[0];
	sampleLoops[i]=(temp[1]==1);
	samplePitch[i]=temp[2]+(temp[3]<<8);
	readTemp(4);
	sampleLoop[i]=((temp[2]+(temp[3]<<8))<<2);
	readTemp(4);
	sampleLoopLength[i]=(temp[3]<<8);
	sampleLoopLength[i]=((sampleLoopLength[i]+temp[2])<<8);
	sampleLoopLength[i]=((sampleLoopLength[i]+temp[1])<<8);
	sampleLoopLength[i]=((sampleLoopLength[i]+temp[0])<<2);
	sampleEnd[i]=sampleLoop[i]+sampleLoopLength[i];
	samplePos[i]=0;
	sampleDone[i]=true;
	sampleNibbleLow[i]=true;
	sampleOutput[i]=0;
	sampleOffset[i]=address+12;//skip the header
	if(sampleFormat[i]==2){
		readTemp(4);
		sampleStepIndexStart[i]=(temp[2]&0x7F);
		samplePredictorStart[i]=(temp[0]+(temp[1]<<8));
		sampleStepStart[i]=0;
		sampleStepIndex[i]=sampleStepIndexStart[i];
		samplePredictor[i]=samplePredictorStart[i];
		sampleOutput[i]=samplePredictor[i];
		sampleStep[i]=sampleStepStart[i];
		sampleStepIndexLoop[i]=sampleStepIndex[i];
		samplePredictorLoop[i]=samplePredictor[i];
		sampleStepLoop[i]=sampleStep[i];
		sampleOffset[i]+=4;//skip the ima-adpcm header
	}else if(sampleFormat[i]>2){
		printf("%X Sample format %X\n",i,sampleFormat[i]);
		return false;
	}
	return true;
}

bool NDS_begin(int songID, int sRate)
{
    running=false;
	sampleRate=sRate;
    filePos=0;
	// Set the output values properly
	delayHit=false;
	tempoFill=0;
	usedTracks=0xFFFF;
	sseqTempo=120;
	sseqVol=0x7F;
	fadeVol=0;
	maxLoops=2;
	mixer[0]=0;
	mixer[1]=0;
	soundOut[0]=0;
	soundOut[1]=0;
	
	//Read SDAT header
    filePos=0x0E;
	readTemp(2);
    printf("numBlocks:%X\n",temp[0]);
    headerSize=0x38;
	if (temp[0]==4){//has a SYMB block
		readTemp(4);//skip 8 bytes
		readTemp(4);
        headerSize=0x40;
	}
	readTemp(4);
	infoBlock=(temp[3]<<8);
	infoBlock=((infoBlock+temp[2])<<8);
	infoBlock=((infoBlock+temp[1])<<8);
	infoBlock=(infoBlock+temp[0]);
    printf("infoBlock:%X\n",infoBlock);
	readTemp(4);//skip 4 bytes

	readTemp(4);
	fatArray=(temp[3]<<8);
	fatArray=((fatArray+temp[2])<<8);
	fatArray=((fatArray+temp[1])<<8);
	fatArray=(fatArray+temp[0]);
	fatArray+=12;
    printf("fatArray:%X\n",fatArray);
	
	filePos=infoBlock+8;
	readTemp(4);
	sseqArray=(temp[3]<<8);
	sseqArray=((sseqArray+temp[2])<<8);
	sseqArray=((sseqArray+temp[1])<<8);
	sseqArray=(sseqArray+temp[0]);
	sseqArray+=infoBlock+4;
    totalSongs=NDS_getAddress(sseqArray-4);
    printf("sseqArray:%X\n",sseqArray);
	
    filePos=infoBlock+0x10;
	readTemp(4);
	sbnkArray=(temp[3]<<8);
	sbnkArray=((sbnkArray+temp[2])<<8);
	sbnkArray=((sbnkArray+temp[1])<<8);
	sbnkArray=(sbnkArray+temp[0]);
	sbnkArray+=infoBlock+4;
    printf("sbnkArray:%X\n",sbnkArray);
	readTemp(4);
	swarArray=(temp[3]<<8);
	swarArray=((swarArray+temp[2])<<8);
	swarArray=((swarArray+temp[1])<<8);
	swarArray=(swarArray+temp[0]);
	swarArray+=infoBlock+4;
    printf("swarArray:%X\n",swarArray);
	
	for (int i=0; i<16; i++) {
		timesLooped[i]=maxLoops;
		chPointer[i]=0;
		slotChannel[i]=0;
		slotFree[i]=0;
		slotNote[i]=0;
		slotNoteVel[i]=0;
		slotNoteLen[i]=0;
		chDelay[i]=0;
		chInstrument[i]=0;
		chPan[i]=0x40;
		chPanL[i]=0;
		chPanR[i]=0;
		chVol[i]=0x7F;
		chTranspose[i]=0;
		chPitchBendCur[i]=0;
		chPitchBend[i]=0;
		chPitchBendRange[i]=2;
		chSweepPitch[i]=0;
		chPriority[i]=0;
		chPolyMono[i]=0;
		chTie[i]=0;
		chPort[i]=0;
		chPortOn[i]=0;
		chPortTime[i]=0;
		chModDelay[i]=0;
		chModDepth[i]=0;
		chModSpeed[i]=0;
		chModType[i]=0;
		chModRange[i]=0;
		chAttack[i]=0;
		chDecay[i]=0;
		chSustain[i]=0;
		chRelease[i]=0;
		chLoopTimes[i]=0;
		chLoopOffset[i]=0;
		chReturnOffset[i]=0;
		chInCall[i]=false;
	
		chActive[i]=false;
		sampleOffset[i]=0;
		tempNibble[i]=0;
		slotMidiFreq[i]=0;
		slotPitch[i]=0;
		slotPitchFill[i]=0;
		samplePitch[i]=0;
		samplePitchFill[i]=0;
		//NDS_setSample(i,sampleOffset[i]);
		chInstrument[i]=0;
		validSample[i]=false;
        validInst[i]=NDS_setInst(i,chInstrument[i]);
	}

	sseqIndex=songID;
	NDS_loadSong(sseqIndex);
	//read sseq header
	filePos=dataOffset;
	readTemp(3);
	usedTracks=(temp[2]<<8)+temp[1];
	chPointer[0]=dataOffset+3;
	for(int i=1; i<16; i++){
		if((usedTracks&(1<<i))!=0){
			temp[0]=sdat[filePos++];//read 0x93 channel pointer command 
			readTemp(4);//read channel number and pointer
			chPointer[temp[0]]=(temp[3]<<16)+(temp[2]<<8)+temp[1]+dataOffset;
			chPointer[0]+=5;
			chActive[temp[0]]=true;
			timesLooped[temp[0]]=0;
		}
	}
    //read sbnk header
	filePos=sbnkPointer+0x38;
	readTemp(4);
	temp32=(temp[3]<<8);
	temp32=((temp32+temp[2])<<8);
	temp32=((temp32+temp[1])<<8);
	temp32=(temp32+temp[0]);
	if(temp32>128){//bounds check
		temp32=128;
	}
	for(int i=0; i<temp32; i++){
		readTemp(4);
		instAddress[i]=(temp[3]<<8);
		instAddress[i]=((instAddress[i]+temp[2])<<8);
		instAddress[i]=(instAddress[i]+temp[1]);
		instAddress[i]+=sbnkPointer;
		instType[i]=temp[0];
	}
	
	//read swar header
	
	chActive[0]=true;
    
    printf("%X chPointer 0:%X\n",chActive[0],chPointer[0]);
    printf("%X chPointer 1:%X\n",chActive[1],chPointer[1]);
    printf("%X chPointer 2:%X\n",chActive[2],chPointer[2]);
    printf("%X chPointer 3:%X\n",chActive[3],chPointer[3]);
    printf("%X chPointer 4:%X\n",chActive[4],chPointer[4]);
    printf("%X chPointer 5:%X\n",chActive[5],chPointer[5]);
    printf("%X chPointer 6:%X\n",chActive[6],chPointer[6]);
    printf("%X chPointer 7:%X\n",chActive[7],chPointer[7]);
    printf("%X chPointer 8:%X\n",chActive[8],chPointer[8]);
    printf("%X chPointer 9:%X\n",chActive[9],chPointer[9]);
    printf("%X chPointer A:%X\n",chActive[10],chPointer[10]);
    printf("%X chPointer B:%X\n",chActive[11],chPointer[11]);
    printf("%X chPointer C:%X\n",chActive[12],chPointer[12]);
    printf("%X chPointer D:%X\n",chActive[13],chPointer[13]);
    printf("%X chPointer E:%X\n",chActive[14],chPointer[14]);
    printf("%X chPointer F:%X\n",chActive[15],chPointer[15]);
    
	running = true;
	return true;
}

bool NDS_stop()
{
	running = false;
	return true;
}

void NDS_decodeADPCMSample(int i,unsigned char nibble){
	temp[0] = (nibble >> 3);//sign
	temp[1] = nibble & 7;//delta
	/*sampleStep[i]=ADPCM_TABLE[sampleStepIndex[i]];
	sampleDiff = sampleStep[i] >> 3;
	if (temp[1] & 4) sampleDiff += sampleStep[i];
	if (temp[1] & 2) sampleDiff += (sampleStep[i] >> 1);
	if (temp[1] & 1) sampleDiff += (sampleStep[i] >> 2);*/
	sampleDiff = ADPCM_TABLE[sampleStepIndex[i]+(temp[1]<<7)];
	if (temp[0]){samplePredictor[i]=max(samplePredictor[i]-sampleDiff,-0x7FFF);}
	else{samplePredictor[i]=min(samplePredictor[i]+sampleDiff,0x7FFF);}
	sampleStepIndex[i]=max(min(sampleStepIndex[i]+INDEX_TABLE[temp[1]],88),0);
	if(sampleNibbleLow[i]){
		sampleNibbleLow[i]=false;
	}else{
		sampleNibbleLow[i]=true;
		samplePos[i]++;
		if(samplePos[i]==sampleLoop[i]){
			sampleStepIndexLoop[i]=sampleStepIndex[i];
			samplePredictorLoop[i]=samplePredictor[i];
		}
	}
}

char * NDS_loop(){
	seqFrame=false;
	static int c = 0;
//sample processing
	if (!running) return 0; // Nothing to do here!
    if(paused) return 0;
    c+=192;
    if(c>=sampleRate){//player update
        c-=sampleRate;
        seqFrame=true;
        if(fadeVol<0){
            fadeVol--;
            if(fadeVol<=-723) running = false;
            if (!running) return 0;
        }
        tempoFill+=sseqTempo;
        if(tempoFill>=240){
            tempoFill-=240;
            for(int i=0; i<16; i++){
                if(chActive[i]){
                    if(chDelay[i]==0){
                        delayHit=false;
                        while(!delayHit){
                            filePos=chPointer[i];
                            temp[0]=sdat[filePos++];
                            switch(temp[0]){
                                case 0xFE: //Multitrack
                                    readTemp(2);
                                    usedTracks=(temp[1]<<8)+temp[0];
                                    chPointer[i]+=3;
                                break;
                                case 0x93: //Track Start
                                    printf("%X Undefined Instruction 0x93 at: %X\n",i,filePos-1);
                                    readTemp(4);
                                    
                                    chPointer[i]+=5;
                                break;
                                case 0x80: //Rest
                                    delayHit=true;
                                    readTemp(4);
                                    chDelay[i]=(temp[0]&0x7F);
                                    varLength=2;
                                    for(int j=0; j<3; j++){
                                        if(temp[j]>0x7F){
                                            chDelay[i]=(chDelay[i]<<7);
                                            chDelay[i]+=(temp[j+1]&0x7F);
                                            varLength++;
                                        }else{
                                            j=3;
                                        }
                                    }
                                    chPointer[i]+=varLength;
                                break;
                                case 0x81: //Instrument Change
                                    readTemp(4);
                                    if(chInstrument[i]!=(temp[0]&0x7F)){
                                        chInstrument[i]=temp[0]&0x7F;
                                        validInst[i]=NDS_setInst(i,chInstrument[i]);
                                        //if(validInst[i]) printf("%X Instrument: %X Set %X\n",i,chInstrument[i],filePos-4);
                                        if(!validInst[i]) printf("%X Invalid Instrument: %X? %X\n",i,chInstrument[i],filePos-4);
                                    }
                                    varLength=2;
                                    for(int j=0; j<3; j++){
                                        if(temp[j]>0x7F){
                                            varLength++;
                                        }else{
                                            j=3;
                                        }
                                    }
                                    chPointer[i]+=varLength;
                                break;
                                case 0x94: //Jump
                                    readTemp(3);
                                    chPointer[i]=(temp[2]<<16)+(temp[1]<<8)+temp[0]+dataOffset;
                                    if(timesLooped[i]<maxLoops)timesLooped[i]++;
                                    loopi=0;
                                    while(timesLooped[loopi]>=maxLoops && loopi<16) loopi++;
                                    if(loopi==16 && fadeVol==0 && !infLoop) fadeVol--;
                                break;
                                case 0x95: //Call
                                    readTemp(3);
                                    chReturnOffset[i]=chPointer[i]+4;
                                    chInCall[i]=true;
                                    chPointer[i]=(temp[2]<<16)+(temp[1]<<8)+temp[0]+dataOffset;
                                break;
                                case 0xFD: //Return
                                    if(chInCall[i]){
                                        chPointer[i]=chReturnOffset[i];
                                        chInCall[i]=false;
                                    }else{
                                        chPointer[i]++;
                                    }
                                break;
                                case 0xC0: //Pan
                                    temp[0]=sdat[filePos++];
                                    chPan[i]=temp[0];
                                    chPanL[i]=PAN_TABLE[temp[0]];
                                    chPanR[i]=PAN_TABLE[127-temp[0]];
                                    chPointer[i]+=2;
                                break;
                                case 0xC1: //Volume
                                    temp[0]=sdat[filePos++];
                                    chVol[i]=NDS_Cnv_dB(temp[0]);
                                    chPointer[i]+=2;
                                break;
                                case 0xC2: //Master Volume
                                    printf("%X Undefined Instruction 0xC2 at: %X\n",i,filePos-1);
                                    temp[0]=sdat[filePos++];
                                    sseqVol=temp[0];
                                    chPointer[i]+=2;
                                break;
                                case 0xC3: //Transpose
                                    printf("%X Undefined Instruction 0xC3 at: %X\n",i,filePos-1);
                                    temp[0]=sdat[filePos++];
                                    chTranspose[i]=temp[0];
                                    chPointer[i]+=2;
                                break;
                                case 0xC4: //Pitch Bend
                                    temp[0]=sdat[filePos++];
                                    chPitchBend[i]=(temp[0]);
                                    chPointer[i]+=2;
                                    if(chPitchBend[i]>128) chPitchBendCur[i]=((chPitchBend[i]-256)*chPitchBendRange[i]);
                                    if(chPitchBend[i]<=128) chPitchBendCur[i]=(chPitchBend[i]*chPitchBendRange[i]);
                                break;
                                case 0xC5: //Pitch Bend Range
                                    temp[0]=sdat[filePos++];
                                    chPitchBendRange[i]=temp[0];
                                    chPointer[i]+=2;
                                    if(chPitchBend[i]>128) chPitchBendCur[i]=((chPitchBend[i]-256)*chPitchBendRange[i]);
                                    if(chPitchBend[i]<=128) chPitchBendCur[i]=(chPitchBend[i]*chPitchBendRange[i]);
                                break;
                                case 0xC6: //Track Priority
                                    printf("%X Undefined Instruction 0xC6 at: %X\n",i,filePos-1);
                                    temp[0]=sdat[filePos++];
                                    chPriority[i]=temp[0];
                                    chPointer[i]+=2;
                                break;
                                case 0xC7: //Poly/Mono
                                    printf("%X Undefined Instruction 0xC7 at: %X\n",i,filePos-1);
                                    temp[0]=sdat[filePos++];
                                    chPolyMono[i]=temp[0];
                                    chPointer[i]+=2;
                                break;
                                case 0xC8: //Tie (?)
                                    printf("%X Undefined Instruction 0xC8 at: %X\n",i,filePos-1);
                                    temp[0]=sdat[filePos++];
                                    chTie[i]=temp[0];
                                    chPointer[i]+=2;
                                break;
                                case 0xC9: //Port Control
                                    printf("%X Undefined Instruction 0xC9 at: %X\n",i,filePos-1);
                                    temp[0]=sdat[filePos++];
                                    chPort[i]=temp[0];
                                    chPointer[i]+=2;
                                break;
                                case 0xCA: //Mod Depth
                                    printf("%X Undefined Instruction 0xCA at: %X\n",i,filePos-1);
                                    temp[0]=sdat[filePos++];
                                    chModDepth[i]=temp[0];
                                    chPointer[i]+=2;
                                break;
                                case 0xCB: //Mod Speed
                                    printf("%X Undefined Instruction 0xCB at: %X\n",i,filePos-1);
                                    temp[0]=sdat[filePos++];
                                    chModSpeed[i]=temp[0];
                                    chPointer[i]+=2;
                                break;
                                case 0xCC: //Mod Type
                                    printf("%X Undefined Instruction 0xCC at: %X\n",i,filePos-1);
                                    temp[0]=sdat[filePos++];
                                    chModType[i]=temp[0];
                                    chPointer[i]+=2;
                                break;
                                case 0xCD: //Mod Range
                                    printf("%X Undefined Instruction 0xCD at: %X\n",i,filePos-1);
                                    temp[0]=sdat[filePos++];
                                    chModRange[i]=temp[0];
                                    chPointer[i]+=2;
                                break;
                                case 0xCE: //Port On/Off
                                    printf("%X Undefined Instruction 0xCE at: %X\n",i,filePos-1);
                                    temp[0]=sdat[filePos++];
                                    chPortOn[i]=temp[0];
                                    chPointer[i]+=2;
                                break;
                                case 0xCF: //Port Time
                                    printf("%X Undefined Instruction 0xCF at: %X\n",i,filePos-1);
                                    temp[0]=sdat[filePos++];
                                    chPortTime[i]=temp[0];
                                    chPointer[i]+=2;
                                break;
                                case 0xD0: //Attack Rate
                                    printf("%X Undefined Instruction 0xD0 at: %X\n",i,filePos-1);
                                    temp[0]=sdat[filePos++];
                                    chAttack[i]=temp[0];
                                    chPointer[i]+=2;
                                break;
                                case 0xD1: //Decay Rate
                                    printf("%X Undefined Instruction 0xD1 at: %X\n",i,filePos-1);
                                    temp[0]=sdat[filePos++];
                                    chDecay[i]=temp[0];
                                    chPointer[i]+=2;
                                break;
                                case 0xD2: //Sustain Rate
                                    printf("%X Undefined Instruction 0xD2 at: %X\n",i,filePos-1);
                                    temp[0]=sdat[filePos++];
                                    chSustain[i]=temp[0];
                                    chPointer[i]+=2;
                                break;
                                case 0xD3: //Release Rate
                                    printf("%X Undefined Instruction 0xD3 at: %X\n",i,filePos-1);
                                    temp[0]=sdat[filePos++];
                                    chRelease[i]=temp[0];
                                    chPointer[i]+=2;
                                break;
                                case 0xD4: //Loop Start Marker
                                    temp[0]=sdat[filePos++];
                                    chLoopTimes[i]=temp[0];
                                    chPointer[i]+=2;
                                    chLoopOffset[i]=chPointer[i];
                                break;
                                case 0xFC: //Loop End Marker
                                    if(chLoopTimes[i]>0){
                                        chLoopTimes[i]--;
                                        chPointer[i]=chLoopOffset[i];
                                    }else{
                                        chPointer[i]++;
                                    }
                                break;
                                case 0xD5: //Expression
                                    printf("%X Undefined Instruction 0xD5 at: %X\n",i,filePos-1);
                                    temp[0]=sdat[filePos++];
                                    
                                    chPointer[i]+=2;
                                break;
                                case 0xD6: //Print Variable
                                    printf("%X Undefined Instruction 0xD6 at: %X\n",i,filePos-1);
                                    temp[0]=sdat[filePos++];
                                    
                                    chPointer[i]+=2;
                                break;
                                case 0xE0: //Mod Delay
                                    printf("%X Undefined Instruction 0xE0 at: %X\n",i,filePos-1);
                                    readTemp(2);
                                    chModDelay[i]=(temp[1]<<8)+temp[0];
                                    chPointer[i]+=3;
                                break;
                                case 0xE1: //Tempo
                                    readTemp(2);
                                    sseqTempo=(temp[1]<<8)+temp[0];
                                    chPointer[i]+=3;
                                break;
                                case 0xE3: //Sweep Pitch
                                    printf("%X Undefined Instruction 0xE3 at: %X\n",i,filePos-1);
                                    readTemp(2);
                                    
                                    chPointer[i]+=3;
                                break;
                                case 0xFF: //End of Track
                                    chActive[i]=false;
                                    delayHit=true;
                                    timesLooped[i]=maxLoops;
                                    loopi=0;
                                    while(timesLooped[loopi]>=maxLoops && loopi<16) loopi++;
                                    if(loopi==16) fadeVol=-722;
                                break;
                                default: //
                                    if(temp[0]<0x80){//Note on
                                        curSlot=0xFF;
                                        for(int slot=0; slot<16; slot++){
                                            if(slotFree[slot]==0){//check for free slots
                                                curSlot=slot;
                                                slot=16;
                                            }
                                        }
                                        if(curSlot==0xFF){
                                            for(int slot=0; slot<16; slot++){
                                                if(slotFree[slot]==1){//if free slots are unavailable, check for slot in release state
                                                    curSlot=slot;
                                                    slot=16;
                                                }
                                            }
                                        }
                                        if(curSlot<0xFF){
                                            slotChannel[curSlot]=i;
                                            slotFree[curSlot]=2;
                                            slotNote[curSlot]=temp[0];
                                            slotMidiFreq[curSlot]=(slotNote[curSlot]*128);
                                            temp[0]=sdat[filePos++];
                                            slotNoteVel[curSlot]=NDS_Cnv_dB(temp[0]);
                                            varLength=3;
                                            readTemp(4);
                                            slotNoteLen[curSlot]=(temp[0]&0x7F);
                                            samplePos[curSlot]=0;
                                            sampleNibbleLow[curSlot]=true;
                                            for(int j=0; j<3; j++){
                                                if(temp[j]>0x7F){
                                                    slotNoteLen[curSlot]=(slotNoteLen[curSlot]<<7);
                                                    slotNoteLen[curSlot]+=(temp[j+1]&0x7F);
                                                    varLength++;
                                                }else{
                                                    j=3;
                                                }
                                            }
                                            if(instType[chInstrument[i]]>=16){
                                                if(validInst[i]) validSample[curSlot]=NDS_setSample(curSlot,NDS_getSampleAddress(keyBank[(i<<7)+slotNote[curSlot]],keySample[(i<<7)+slotNote[curSlot]]));
                                                if(!validInst[i]) printf("%X Invalid Instrument? %X\n",i,filePos-4);
                                                if(!validSample[curSlot]) printf("%X Invalid Sample? %X\n",i,filePos-4);
                                                slotPitch[curSlot]=keyRoot[(i<<7)+slotNote[curSlot]];
                                                curKeyRoot[curSlot]=FREQ_TABLE[(keyRootVal[(i<<7)+slotNote[curSlot]]<<7)];
                                                slotAttack[curSlot]=NDS_Cnv_Attack(keyAttack[(i<<7)+slotNote[curSlot]]);
                                                slotDecay[curSlot]=NDS_Cnv_Fall(keyDecay[(i<<7)+slotNote[curSlot]]);
                                                slotSustain[curSlot]=NDS_Cnv_Sust(keySustain[(i<<7)+slotNote[curSlot]]);
                                                slotRelease[curSlot]=NDS_Cnv_Fall(keyRelease[(i<<7)+slotNote[curSlot]]);
                                                slotPan[curSlot]=keyPan[(i<<7)+slotNote[curSlot]];
                                            }else{
                                                if(validInst[i]) validSample[curSlot]=NDS_setSample(curSlot,NDS_getSampleAddress(keyBank[(i<<7)],keySample[(i<<7)]));
                                                slotPitch[curSlot]=keyRoot[(i<<7)];
                                                curKeyRoot[curSlot]=FREQ_TABLE[(keyRootVal[(i<<7)]<<7)];
                                                if(!validInst[i]) printf("%X Invalid Instrument? %X\n",i,filePos-4);
                                                if(!validSample[curSlot]) printf("%X Invalid Sample? %X\n",i,filePos-4);
                                                slotAttack[curSlot]=NDS_Cnv_Attack(keyAttack[(i<<7)]);
                                                slotDecay[curSlot]=NDS_Cnv_Fall(keyDecay[(i<<7)]);
                                                slotSustain[curSlot]=NDS_Cnv_Sust(keySustain[(i<<7)]);
                                                slotRelease[curSlot]=NDS_Cnv_Fall(keyRelease[(i<<7)]);
                                                slotPan[curSlot]=keyPan[(i<<7)];
                                            }
                                            slotADSRState[curSlot]=0;
                                            slotADSRVol[curSlot]=-92544;
                                            max(slotPanL[curSlot]=chPanL[i]+PAN_TABLE[slotPan[curSlot]],-723);
                                            max(slotPanR[curSlot]=chPanR[i]+PAN_TABLE[127-slotPan[curSlot]],-723);
                                            if(validInst[i] && validSample[curSlot]) sampleDone[curSlot]=false;
                                        }else{
                                            temp[0]=sdat[filePos++];
                                            varLength=3;
                                            readTemp(4);
                                            for(int j=0; j<3; j++){
                                                if(temp[j]>0x7F){
                                                    varLength++;
                                                }else{
                                                    j=3;
                                                }
                                            }
                                        }
                                        chPointer[i]+=varLength;
                                        //if(i==0) printf("Note:%X Length:%X\n",slotNote[curSlot],slotNoteLen[curSlot]);
                                    }else if(temp[0]>=0xA0 && temp[0]<0xC0){//Arithmetic operations
                                        printf("%X Undefined Instruction 0x%X at: %X\n",temp[0],filePos-1);
                                    	running=false;
					delayHit=true;
                                    }else{
                                        printf("Illegal Instruction 0x%X at: %X\n",temp[0],filePos-1);
					running=false;
					delayHit=true;
                                    }
                                break;
                            }
                        }
                    }
                    if(chDelay[i]>0) chDelay[i]-=1;//change this
                }
            }
            for(int i=0; i<16; i++){                
                if(slotNoteLen[i]>0){
                    slotNoteLen[i]-=1;//change this
                }else if(slotADSRState[i]<3){
                    slotFree[i]=1;
                    slotADSRState[i]=3;
                    slotADSRVol[i]=slotSustain[i];
                }
            }
        }
        for(int i=0; i<16; i++){
            
            switch(slotADSRState[i]){
                case 0:
                    slotADSRVol[i]=((slotADSRVol[i]*slotAttack[i])/255);
                    if(slotADSRVol[i]<0) break; 
                    slotADSRState[i]++;
                break;
                case 1:
                    slotADSRVol[i]-=slotDecay[i];
                    if(slotADSRVol[i]>slotSustain[i]) break;
                    slotADSRState[i]++;
                case 2:
                    slotADSRVol[i]=slotSustain[i];
                break;
                case 3:
                    slotADSRVol[i]-=slotRelease[i];
                    if(slotADSRVol[i]>-92544) break;
                    slotADSRVol[i]=-92544;
                    slotADSRState[i]++;
                    sampleDone[i]=true;
                    slotFree[i]=0;
                break;					
            }
            volModL[i]=NDS_Cnv_Vol(fadeVol+slotNoteVel[i]+(slotADSRVol[i]>>7)+chVol[slotChannel[i]]+slotPanL[i]);
            volModR[i]=NDS_Cnv_Vol(fadeVol+slotNoteVel[i]+(slotADSRVol[i]>>7)+chVol[slotChannel[i]]+slotPanR[i]);
        }
    }
    mixer[0]=0;
    mixer[1]=0;
    for(int i=0; i<16; i++){//process each slot
        if(slotFree[i]!=0 && !sampleDone[i]){
            signed long tune=slotMidiFreq[i]+chPitchBendCur[slotChannel[i]];//(((float)chPitchBend[slotChannel[i]] * (float)chPitchBendRange[slotChannel[i]]) / 2.0);
            if(tune<0) tune=0;
            if(tune>=(128*128)){
             printf("Freq to high:%X\n",tune);
             tune=(128*128)-1;
            }
            tune=FREQ_TABLE[tune];
            //finalTune=(int)pow(tune,18);
            slotPitchFill[i]+=tune;//slotMidiFreq[i];//+(chPitchBend[slotChannel[i]]*chPitchBendRange[slotChannel[i]]);
            while(slotPitchFill[i]>=curKeyRoot[i] && curKeyRoot[i]>0){
                slotPitchFill[i]-=curKeyRoot[i];
                samplePitchFill[i]+=samplePitch[i];
                while(samplePitchFill[i]>=sampleRate){
                    samplePitchFill[i]-=sampleRate;
                    if(sampleFormat[i]==2){///IMA-ADPCM
                        if(sampleNibbleLow[i]){
                            filePos=sampleOffset[i] + samplePos[i];
                            temp[0]=sdat[filePos++];
                            tempNibble[i]=temp[0];
                            //NDS_decodeADPCMSample(i,(temp[0]&0x0F));
                            temp[1] = temp[0] & 7;//delta
                            /*sampleStep[i]=ADPCM_TABLE[sampleStepIndex[i]];
                            sampleDiff = sampleStep[i] >> 3;
                            if (temp[1] & 4) sampleDiff += sampleStep[i];
                            if (temp[1] & 2) sampleDiff += (sampleStep[i] >> 1);
                            if (temp[1] & 1) sampleDiff += (sampleStep[i] >> 2);*/
                            sampleDiff = ADPCM_TABLE[sampleStepIndex[i]+(temp[1]<<7)];
                            if (temp[0]&8){samplePredictor[i]=max(samplePredictor[i]-sampleDiff,-0x7FFF);}
                            else{samplePredictor[i]=min(samplePredictor[i]+sampleDiff,0x7FFF);}
                            sampleStepIndex[i]=max(min(sampleStepIndex[i]+INDEX_TABLE[temp[1]],88),0);
                            sampleNibbleLow[i]=false;
                        }else{
                            //NDS_decodeADPCMSample(i,tempNibble[i]);
                            temp[1] = tempNibble[i] & 0x70;//delta
                            /*sampleStep[i]=ADPCM_TABLE[sampleStepIndex[i]];
                            sampleDiff = sampleStep[i] >> 3;
                            if (temp[1] & 4) sampleDiff += sampleStep[i];
                            if (temp[1] & 2) sampleDiff += (sampleStep[i] >> 1);
                            if (temp[1] & 1) sampleDiff += (sampleStep[i] >> 2);*/
                            sampleDiff = ADPCM_TABLE[sampleStepIndex[i]+(temp[1]<<3)];
                            if (tempNibble[i]&0x80){samplePredictor[i]=max(samplePredictor[i]-sampleDiff,-0x7FFF);}
                            else{samplePredictor[i]=min(samplePredictor[i]+sampleDiff,0x7FFF);}
                            sampleStepIndex[i]=max(min(sampleStepIndex[i]+INDEX_TABLE[temp[1]>>4],88),0);
                            sampleNibbleLow[i]=true;
                            samplePos[i]++;
                            if(samplePos[i]==sampleLoop[i]){
                                sampleStepIndexLoop[i]=sampleStepIndex[i];
                                samplePredictorLoop[i]=samplePredictor[i];
                            }
                        }
                        sampleOutput[i]=samplePredictor[i];
                    }else if(sampleFormat[i]==1){//16-bit PCM
                        filePos=sampleOffset[i] + samplePos[i];
                        readTemp(2);
                        samplePos[i]+=2;
                        sampleOutput[i]=temp[0]+(temp[1]<<8);
                    }else{//8-bit PCM
                        filePos=sampleOffset[i] + samplePos[i];
                        temp[0]=sdat[filePos++];
                        samplePos[i]++;
                        sampleOutput[i]=(temp[0]<<8);
                    }
                    
                    if(samplePos[i]>=sampleEnd[i]){
                        if(sampleLoops[i]){
                            samplePos[i]=sampleLoop[i];
                            sampleStepIndex[i]=sampleStepIndexLoop[i];
                            samplePredictor[i]=samplePredictorLoop[i];
                        }else{
                            sampleDone[i]=true;
                            slotFree[i]=0;
                        }
                    }

                }
            }			
            mixer[0]+=(sampleOutput[i]*volModL[i]);//left
            mixer[1]+=(sampleOutput[i]*volModR[i]);//left
        }
    }
    soundOut[0]=((mixer[0]>>3) & 0xFF);
    soundOut[1]=((mixer[0]>>11) & 0xFF);
    soundOut[2]=((mixer[0]>>19) & 0xFF);
    soundOut[3]=((mixer[1]>>3) & 0xFF);
    soundOut[4]=((mixer[1]>>11) & 0xFF);
    soundOut[5]=((mixer[1]>>19) & 0xFF);
	return soundOut;
}
