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

unsigned char NDS_Cnv_Attack(unsigned char attk){//table generated from Fincs FSS
	static const char lut[] =
	{
		255,254,253,252,
		251,250,249,248,247,246,245,244,243,242,
		241,240,239,238,237,236,235,234,233,232,
		231,230,229,228,227,226,225,224,223,222,
		221,220,219,218,217,216,215,214,213,212,
		211,210,209,208,207,206,205,204,203,202,
		201,200,199,198,197,196,195,194,193,192,
		191,190,189,188,187,186,185,184,183,182,
		181,180,179,178,177,176,175,174,173,172,
		171,170,169,168,167,166,165,164,163,162,
		161,160,159,158,157,156,155,154,153,152,
		151,150,149,148,147,143,137,132,127,123,
		116,109,100,92,84,73,63,51,38,26,14,5,1,0
	};
	return lut[attk];
}

int NDS_Calc_Attack(unsigned char i, unsigned char frame){
	static const char lut[] =
	{
		255,254,253,252,
		251,250,249,248,247,246,245,244,243,242,
		241,240,239,238,237,236,235,234,233,232,
		231,230,229,228,227,226,225,224,223,222,
		221,220,219,218,217,216,215,214,213,212,
		211,210,209,208,207,206,205,204,203,202,
		201,200,199,198,197,196,195,194,193,192,
		191,190,189,188,187,186,185,184,183,182,
		181,180,179,178,177,176,175,174,173,172,
		171,170,169,168,167,166,165,164,163,162,
		161,160,159,158,157,156,155,154,153,152,
		151,150,149,148,147,143,137,132,127,123,
		116,109,100,92,84,73,63,51,38,26,14,5,1,0
	};
	return lut[0x7F];
}

unsigned short NDS_Cnv_Fall(unsigned char fall){//table generated from Fincs FSS
	const unsigned short lut[] = {
		1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,
		39,41,43,45,47,49,51,53,55,57,59,61,63,65,67,69,71,73,75,77,
		79,81,83,85,87,89,91,93,95,97,99,101,102,103,105,106,108,109,
		111,112,114,116,118,120,121,123,125,128,130,132,134,137,139,
		142,144,147,150,153,156,160,163,166,170,174,178,182,187,192,
		196,202,207,213,219,225,232,240,247,256,264,274,284,295,307,
		320,333,349,365,384,404,426,451,480,512,548,590,640,698,768,
		853,960,1097,1280,1536,1920,2560,3840,7680,15360,65535
	};
	return lut[fall];	
}

int NDS_Cnv_Sust(unsigned char sust){//table generated from Fincs FSS
	const long lut[] = {
		-4194304,-92416,-92288,-83328,-76928,
		-71936,-67840,-64384,-61440,-58880,-56576,-54400,-52480,-50688,
		-49024,-47488,-46080,-44672,-43392,-42240,-41088,-40064,-39040,
		-38016,-36992,-36096,-35328,-34432,-33664,-32896,-32128,-31360,
		-30592,-29952,-29312,-28672,-28032,-27392,-26880,-26240,-25728,
		-25088,-24576,-24064,-23552,-23040,-22528,-22144,-21632,-21120,
		-20736,-20224,-19840,-19456,-19072,-18560,-18176,-17792,-17408,
		-17024,-16640,-16256,-16000,-15616,-15232,-14848,-14592,-14208,
		-13952,-13568,-13184,-12928,-12672,-12288,-12032,-11648,-11392,
		-11136,-10880,-10496,-10240,-9984,-9728,-9472,-9216,-8960,
		-8704,-8448,-8192,-7936,-7680,-7424,-7168,-6912,-6656,-6400,
		-6272,-6016,-5760,-5504,-5376,-5120,-4864,-4608,-4480,-4224,
		-3968,-3840,-3584,-3456,-3200,-2944,-2816,-2560,-2432,-2176,
		-2048,-1792,-1664,-1408,-1280,-1024,-896,-768,-512,-384,-128,0
	};
	return lut[sust];
}

unsigned short NDS_Cnv_Vol(int db){
	const unsigned char lut[] = {
		0,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,
		3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
		3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,5,
		5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
		6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,8,8,8,
		8,8,8,8,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
		11,11,11,11,11,11,11,11,11,11,11,11,12,12,12,12,12,12,12,12,12,12,12,12,13,13,13,
		13,13,13,13,13,13,13,13,14,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,
		16,16,16,16,16,16,16,16,17,17,17,17,17,17,17,17,17,18,18,18,18,18,18,18,19,19,19,
		19,19,19,19,19,20,20,20,20,20,20,20,21,21,21,21,21,21,22,22,22,22,22,22,22,23,23,
		23,23,23,23,24,24,24,24,24,25,25,25,25,25,25,26,26,26,26,26,27,27,27,27,27,28,28,
		28,28,28,29,29,29,29,29,30,30,30,30,30,31,31,31,31,32,32,32,32,32,33,33,33,33,34,
		34,34,34,35,35,35,35,36,36,36,36,37,37,37,37,38,38,38,39,39,39,39,40,40,40,41,41,
		41,41,42,42,42,43,43,43,44,44,44,45,45,45,46,46,46,47,47,47,48,48,48,49,49,49,50,
		50,50,51,51,51,52,52,53,53,53,54,54,54,55,55,56,56,56,57,57,58,58,59,59,59,60,60,
		61,61,62,62,62,63,63,64,64,65,65,66,66,67,67,68,68,69,69,70,70,71,71,72,72,73,73,
		74,74,75,75,76,76,77,78,78,79,79,80,80,81,82,82,83,83,84,85,85,86,86,87,88,88,89,
		90,90,91,91,92,93,93,94,95,96,96,97,98,98,99,100,100,101,102,103,103,104,105,106,
		106,107,108,109,110,110,111,112,113,114,114,115,116,117,118,119,119,120,121,122,123,
		124,125,126,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,
		144,145,146,147,148,149,150,151,152,154,155,156,157,158,159,160,162,163,164,165,166,
		167,169,170,171,172,174,175,176,177,179,180,181,183,184,185,187,188,189,191,192,193,
		195,196,198,199,200,202,203,205,206,208,209,211,212,214,215,217,219,220,222,223,225,
		227,228,230,231,233,235,237,238,240,242,243,245,247,249,251,252,254,255
	};
	if(db<=-723) return 0;
	if(db>=0) return 256;
	return lut[db+723];
}

int NDS_Cnv_dB(unsigned char vol){//table generated from Fincs FSS
	const short lut[] = {
		-32768, -722, -721, -651, -601, -562, -530, -503,
		-480, -460, -442, -425, -410, -396, -383, -371,
		-360, -349, -339, -330, -321, -313, -305, -297,
		-289, -282, -276, -269, -263, -257, -251, -245,
		-239, -234, -229, -224, -219, -214, -210, -205,
		-201, -196, -192, -188, -184, -180, -176, -173,
		-169, -165, -162, -158, -155, -152, -149, -145,
		-142, -139, -136, -133, -130, -127, -125, -122,
		-119, -116, -114, -111, -109, -106, -103, -101,
		-99, -96, -94, -91, -89, -87, -85, -82,
		-80, -78, -76, -74, -72, -70, -68, -66,
		-64, -62, -60, -58, -56, -54, -52, -50,
		-49, -47, -45, -43, -42, -40, -38, -36,
		-35, -33, -31, -30, -28, -27, -25, -23,
		-22, -20, -19, -17, -16, -14, -13, -11,
		-10, -8, -7, -6, -4, -3, -1, 0
	};
	return lut[vol];
}

const unsigned long MIDI_FREQ[] = {//midi frequency for notes, bit shifted << 18 then rounded
	0x0020B405,0x0022A5D8,0x0024B546,0x0026E410,0x00293415,0x002BA74E,0x002E3FD2,0x0030FFDB,0x0033E9C0,0x00370000,0x003A453E,0x003DBC44,
	0x00416809,0x00454BB0,0x00496A8C,0x004DC821,0x0052682A,0x00574E9B,0x005C7FA5,0x0061FFB5,0x0067D380,0x006E0000,0x00748A7B,0x007B7888,
	0x0082D013,0x008A9760,0x0092D517,0x009B9041,0x00A4D054,0x00AE9D37,0x00B8FF49,0x00C3FF6A,0x00CFA700,0x00DC0000,0x00E914F6,0x00F6F110,
	0x0105A025,0x01152EC1,0x0125AA2E,0x01372082,0x0149A0A8,0x015D3A6D,0x0171FE92,0x0187FED5,0x019F4E01,0x01B80000,0x01D229EC,0x01EDE220,
	0x020B404A,0x022A5D82,0x024B545C,0x026E4104,0x0293414F,0x02BA74DB,0x02E3FD25,0x030FFDAA,0x033E9C01,0x03700000,0x03A453D9,0x03DBC440,
	0x04168094,0x0454BB04,0x0496A8B9,0x04DC8208,0x0526829E,0x0574E9B6,0x05C7FA4A,0x061FFB54,0x067D3803,0x06E00000,0x0748A7B1,0x07B78880,
	0x082D0128,0x08A97607,0x092D5172,0x09B90410,0x0A4D053D,0x0AE9D36B,0x0B8FF494,0x0C3FF6A7,0x0CFA7005,0x0DC00000,0x0E914F62,0x0F6F1100,
	0x105A0251,0x1152EC0E,0x125AA2E4,0x13720820,0x149A0A79,0x15D3A6D6,0x171FE928,0x187FED4E,0x19F4E00B,0x1B800000,0x1D229EC4,0x1EDE2200,
	0x20B404A2,0x22A5D81D,0x24B545C7,0x26E41040,0x293414F2,0x2BA74DAC,0x2E3FD250,0x30FFDA9D,0x33E9C015,0x37000000,0x3A453D89,0x3DBC4401,
	0x41680943,0x454BB03A,0x496A8B8F,0x4DC82080,0x526829E4,0x574E9B58,0x5C7FA49F,0x61FFB539,0x67D3802A,0x6E000000,0x748A7B12,0x7B788802,
	0x82D01286,0x8A976074,0x92D5171D,0x9B904101,0xA4D053C9,0xAE9D36B0,0xB8FF493E,0xC3FF6A72
};

const unsigned short ADPCM_TABLE[] = {
	0,1,1,1,1,1,1,1,2,2,2,2,2,3,3,3,4,4,5,5,6,6,7,8,9,10,11,12,13,14,16,17,19,21,23,26,28,31,34,38,42,46,51,56,61,68,74,82,90,99,109,120,132,145,160,176,194,213,234,258,284,312,343,378,415,457,503,553,608,669,736,810,891,980,1078,1186,1305,1435,1579,1737,1911,2102,2312,2543,2798,3077,3385,3724,4095,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,3,3,3,3,4,4,4,6,6,6,7,7,9,10,10,12,13,15,16,18,19,22,24,27,30,33,36,39,43,48,52,58,64,70,78,85,94,103,114,126,138,153,168,184,204,223,246,271,298,328,360,397,436,480,528,582,639,703,774,852,936,1030,1134,1246,1372,1509,1660,1825,2008,2209,2431,2674,2941,3235,3559,3915,4306,4737,5211,5733,6306,6937,7630,8394,9232,10156,11172,12286,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	3,5,5,6,6,7,7,8,10,10,11,12,13,15,17,18,21,22,25,27,31,33,37,41,45,50,55,60,66,73,81,88,97,107,118,130,143,157,173,191,210,231,255,280,308,340,373,411,452,497,547,601,662,728,801,881,970,1066,1173,1291,1420,1561,1717,1890,2078,2287,2516,2767,3043,3348,3683,4052,4457,4902,5393,5932,6526,7178,7896,8686,9555,10511,11562,12718,13990,15388,16928,18621,20478,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	4,7,7,8,8,10,10,11,14,14,15,17,18,21,24,25,29,31,35,38,43,46,52,57,63,70,77,84,92,102,113,123,136,150,165,182,200,220,242,267,294,323,357,392,431,476,522,575,633,696,766,841,927,1019,1121,1233,1358,1492,1642,1807,1988,2185,2404,2646,2909,3202,3522,3874,4260,4687,5156,5673,6240,6863,7550,8305,9136,10049,11054,12160,13377,14715,16187,17805,19586,21543,23699,26069,28669,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	7,9,10,11,12,13,14,15,18,19,21,23,25,28,31,34,38,41,46,50,56,61,67,74,82,90,99,109,120,132,146,160,176,194,213,235,258,284,313,345,379,417,459,505,555,612,672,740,814,895,985,1083,1192,1311,1442,1587,1746,1920,2112,2324,2556,2811,3092,3402,3742,4117,4529,4981,5479,6027,6630,7294,8023,8825,9708,10679,11747,12922,14214,15636,17200,18920,20812,22893,25183,27700,30471,33518,36862,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	8,11,12,13,14,16,17,18,22,23,25,28,30,34,38,41,46,50,56,61,68,74,82,90,100,110,121,133,146,161,178,195,215,237,260,287,315,347,382,421,463,509,561,617,678,748,821,904,995,1094,1204,1323,1457,1602,1762,1939,2134,2346,2581,2840,3124,3435,3779,4158,4573,5032,5535,6088,6696,7366,8103,8915,9806,10786,11865,13052,14357,15793,17372,19110,21022,23124,25437,27980,30779,33855,37242,40966,45053,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	10,13,14,16,17,19,20,22,26,27,30,33,36,40,45,49,55,59,66,72,81,88,97,107,118,130,143,157,173,191,211,231,254,280,308,339,373,410,452,498,547,602,663,729,802,884,971,1069,1176,1293,1423,1564,1722,1894,2083,2292,2522,2773,3051,3357,3692,4060,4466,4914,5405,5947,6542,7195,7914,8706,9577,10536,11589,12747,14023,15425,16968,18665,20531,22585,24844,27329,30062,33068,36375,40011,44014,48415,53245,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	11,15,16,18,19,22,23,25,30,31,34,38,41,46,52,56,63,68,76,83,93,101,112,123,136,150,165,181,199,220,243,266,293,323,355,391,430,473,521,574,631,694,765,841,925,1020,1120,1233,1357,1492,1642,1804,1987,2185,2403,2644,2910,3199,3520,3873,4260,4684,5153,5670,6236,6862,7548,8302,9131,10045,11050,12157,13372,14708,16180,17798,19578,21536,23689,26059,28666,31533,34687,38155,41971,46166,50785,55863,61436,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

const unsigned short ADPCM_TABLE_O[] = {
	0x0007,0x0008,0x0009,0x000A,0x000B,0x000C,0x000D,0x000E,0x0010,0x0011,0x0013,0x0015,
	0x0017,0x0019,0x001C,0x001F,0x0022,0x0025,0x0029,0x002D,0x0032,0x0037,0x003C,0x0042,
	0x0049,0x0050,0x0058,0x0061,0x006B,0x0076,0x0082,0x008F,0x009D,0x00AD,0x00BE,0x00D1,
	0x00E6,0x00FD,0x0117,0x0133,0x0151,0x0173,0x0198,0x01C1,0x01EE,0x0220,0x0256,0x0292,
	0x02D4,0x031C,0x036C,0x03C3,0x0424,0x048E,0x0502,0x0583,0x0610,0x06AB,0x0756,0x0812,
	0x08E0,0x09C3,0x0ABD,0x0BD0,0x0CFF,0x0E4C,0x0FBA,0x114C,0x1307,0x14EE,0x1706,0x1954,
	0x1BDC,0x1EA5,0x21B6,0x2515,0x28CA,0x2CDF,0x315B,0x364B,0x3BB9,0x41B2,0x4844,0x4F7E,
	0x5771,0x602F,0x69CE,0x7462,0x7FFF
};


const signed char INDEX_TABLE[] = {
	-1,-1,-1,-1,2,4,6,8,-1,-1,-1,-1,2,4,6,8
};

const signed short PAN_TABLE[] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,-2,-3,
	-5,-8,-11,-14,-18,-22,-26,-31,-36,-42,-48,-55,-62,-69,-77,-85,-94,-103,
	-112,-122,-132,-142,-153,-164,-176,-187,-199,-212,-224,-237,-251,-264,
	-278,-292,-307,-321,-336,-351,-367,-382,-398,-414,-430,-446,-463,-479,
	-496,-513,-530,-547,-565,-582,-599,-617,-634,-652,-670,-688,-705,-723
};

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
	temp32=NDS_getAddress(sseqArray+(id*4))+infoBlock;
	while(temp32==0){
		id++;
		temp32=NDS_getAddress(sseqArray+(id*4))+infoBlock;
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
		
	}else if(instType[index]<16){//single inst
		filePos=instAddress[index];
		readTemp(4);
		tempKey[0]=sdat[filePos++];
		keyBank[(i<<7)]=temp[2];
		keySample[(i<<7)]=temp[0]+(temp[1]<<8);
		keyRoot[(i<<7)]=MIDI_FREQ[tempKey[0]];
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
				keyAttack[keyiPointer+key]=keyAttack[keyiPointer+(key-1)];
				keyDecay[keyiPointer+key]=keyDecay[keyiPointer+(key-1)];
				keySustain[keyiPointer+key]=keySustain[keyiPointer+(key-1)];
				keyRelease[keyiPointer+key]=keyRelease[keyiPointer+(key-1)];
				keyPan[keyiPointer+key]=keyPan[keyiPointer+(key-1)];
				key++;
			}
		}
	}
	return true;
}
bool NDS_setSample(int i, unsigned long address){
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
	}
	return true;
}

bool NDS_begin(int songID, int sRate)
{
	sampleRate=sRate;
	// Set the output values properly
	/*if (!output->SetRate(sampleRate)) return false;
	if (!output->SetBitsPerSample(16)) return false;
	if (!output->SetChannels(2)) return false;
	if (!output->begin()) return false;*/
	delayHit=false;
	tempoFill=0;
	usedTracks=0xFFFF;
	sseqTempo=120;
	sseqVol=0x7F;
	fadeVol=0;
	maxLoops=2;
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
		chPitchBend[i]=0;
		chPitchBendRange[i]=0;
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
		sampleOffset[i]=NDS_getSampleAddress(0,33);
		tempNibble[i]=0;
		slotMidiFreq[i]=0;
		slotPitch[i]=0;
		slotPitchFill[i]=0;
		samplePitchFill[i]=0;
		NDS_setSample(i,sampleOffset[i]);
	}
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
	running = true;
    
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

short * NDS_loop(){
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
                                        NDS_setInst(i,chInstrument[i]);
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
                                    temp[0]=sdat[filePos++];
                                    sseqVol=temp[0];
                                    chPointer[i]+=2;
                                break;
                                case 0xC3: //Transpose
                                    temp[0]=sdat[filePos++];
                                    chTranspose[i]=temp[0];
                                    chPointer[i]+=2;
                                break;
                                case 0xC4: //Pitch Bend
                                    temp[0]=sdat[filePos++];
                                    chPitchBend[i]=temp[0];
                                    chPointer[i]+=2;
                                break;
                                case 0xC5: //Pitch Bend Range
                                    temp[0]=sdat[filePos++];
                                    chPitchBendRange[i]=temp[0];
                                    chPointer[i]+=2;
                                break;
                                case 0xC6: //Track Priority
                                    temp[0]=sdat[filePos++];
                                    chPriority[i]=temp[0];
                                    chPointer[i]+=2;
                                break;
                                case 0xC7: //Poly/Mono
                                    temp[0]=sdat[filePos++];
                                    chPolyMono[i]=temp[0];
                                    chPointer[i]+=2;
                                break;
                                case 0xC8: //Tie (?)
                                    temp[0]=sdat[filePos++];
                                    chTie[i]=temp[0];
                                    chPointer[i]+=2;
                                break;
                                case 0xC9: //Port Control
                                    temp[0]=sdat[filePos++];
                                    chPort[i]=temp[0];
                                    chPointer[i]+=2;
                                break;
                                case 0xCA: //Mod Depth
                                    temp[0]=sdat[filePos++];
                                    chModDepth[i]=temp[0];
                                    chPointer[i]+=2;
                                break;
                                case 0xCB: //Mod Speed
                                    temp[0]=sdat[filePos++];
                                    chModSpeed[i]=temp[0];
                                    chPointer[i]+=2;
                                break;
                                case 0xCC: //Mod Type
                                    temp[0]=sdat[filePos++];
                                    chModType[i]=temp[0];
                                    chPointer[i]+=2;
                                break;
                                case 0xCD: //Mod Range
                                    temp[0]=sdat[filePos++];
                                    chModRange[i]=temp[0];
                                    chPointer[i]+=2;
                                break;
                                case 0xCE: //Port On/Off
                                    temp[0]=sdat[filePos++];
                                    chPortOn[i]=temp[0];
                                    chPointer[i]+=2;
                                break;
                                case 0xCF: //Port Time
                                    temp[0]=sdat[filePos++];
                                    chPortTime[i]=temp[0];
                                    chPointer[i]+=2;
                                break;
                                case 0xD0: //Attack Rate
                                    temp[0]=sdat[filePos++];
                                    chAttack[i]=temp[0];
                                    chPointer[i]+=2;
                                break;
                                case 0xD1: //Decay Rate
                                    temp[0]=sdat[filePos++];
                                    chDecay[i]=temp[0];
                                    chPointer[i]+=2;
                                break;
                                case 0xD2: //Sustain Rate
                                    temp[0]=sdat[filePos++];
                                    chSustain[i]=temp[0];
                                    chPointer[i]+=2;
                                break;
                                case 0xD3: //Release Rate
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
                                    temp[0]=sdat[filePos++];
                                    
                                    chPointer[i]+=2;
                                break;
                                case 0xD6: //Print Variable
                                    temp[0]=sdat[filePos++];
                                    
                                    chPointer[i]+=2;
                                break;
                                case 0xE0: //Mod Delay
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
                                            slotMidiFreq[curSlot]=MIDI_FREQ[slotNote[curSlot]];
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
                                                NDS_setSample(curSlot,NDS_getSampleAddress(keyBank[(i<<7)+slotNote[curSlot]],keySample[(i<<7)+slotNote[curSlot]]));
                                                slotPitch[curSlot]=keyRoot[(i<<7)+slotNote[curSlot]];
                                                slotAttack[curSlot]=NDS_Cnv_Attack(keyAttack[(i<<7)+slotNote[curSlot]]);
                                                slotDecay[curSlot]=NDS_Cnv_Fall(keyDecay[(i<<7)+slotNote[curSlot]]);
                                                slotSustain[curSlot]=NDS_Cnv_Sust(keySustain[(i<<7)+slotNote[curSlot]]);
                                                slotRelease[curSlot]=NDS_Cnv_Fall(keyRelease[(i<<7)+slotNote[curSlot]]);
                                                slotPan[curSlot]=keyPan[(i<<7)+slotNote[curSlot]];
                                            }else{
                                                NDS_setSample(curSlot,NDS_getSampleAddress(keyBank[(i<<7)],keySample[(i<<7)]));
                                                slotPitch[curSlot]=keyRoot[(i<<7)];
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
                                            sampleDone[curSlot]=false;
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
                    slotADSRVol[i]=((slotADSRVol[i]*slotAttack[i])>>8);
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
            slotPitchFill[i]+=slotMidiFreq[i];
            while(slotPitchFill[i]>=slotPitch[i]){
                slotPitchFill[i]-=slotPitch[i];
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
            mixer[0]+=((sampleOutput[i]*volModL[i])>>8);//left
            mixer[1]+=((sampleOutput[i]*volModR[i])>>8);//left
        }
    }
    soundOut[0]=((mixer[0]>>4) & 0xFFFF);
    soundOut[1]=((mixer[1]>>4) & 0xFFFF);
	return soundOut;
}
