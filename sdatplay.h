#ifdef __cplusplus
extern "C"{
#endif 

void sdatplay_init(int sRate);
bool sdatplay_close();
void sdat_load_song(const char *filename, int songID);
void load_sseq(const char *filename);
void song_seek(int pos);
void set_swav(int index, int key, const char *swav);
void set_swav_range(int index, int keyFrom, int keyTo, const char *swav);
void set_inst(int index, int key, const char *swav, int note, int attack, int decay, int sustain, int release, int pan);
void set_inst_range(int index, int keyFrom, int keyTo, const char *swav, int note, int attack, int decay, int sustain, int release, int pan);
void set_inst_type(int index, int type);
//void sdatSongNumStart(uint16_t n);
float *RunMixerFrame();

#ifdef __cplusplus
}
#endif
