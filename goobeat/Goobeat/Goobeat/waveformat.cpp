#include "waveformat.h"

using namespace std;


void print_wave_info(WAVE *wave)
{
    if(wave->riff) {
        printf("   RIFF chunk : %.4s\n",&wave->riff->ID   );
        printf("         Size : %d\n",wave->riff->Size    );
        printf("       Format : %.4s\n",&wave->riff->Format    );
        printf("\n");
    }
    if(wave->format) {
        printf(" Format chunk : %.4s\n",&wave->format->ID);
        printf("         Size : %d\n",wave->format->Size);
        printf("  AudioFormat : %d\n",wave->format->AudioFormat  );
        printf("  NumChannels : %d\n",wave->format->NumChannels  );
        printf("SamplesPerSec : %d\n",wave->format->SamplesPerSec);
        printf("  BytesPerSec : %d\n",wave->format->BytesPerSec  );
        printf("   BlockAlign : %d\n",wave->format->BlockAlign   );
        printf("BitsPerSample : %d\n",wave->format->BitsPerSample);
        printf("\n");
    }
    if(wave->fact) {
        printf("   Fact Chunk : %.4s\n",&wave->fact->ID);
        printf("         Size : %d\n",wave->fact->Size);
        printf("Sample Length : %d\n",wave->fact->dwSampleLength);
        printf("\n");
    }
    if(wave->data) {
        printf("   Data Chunk : %.4s\n",&wave->data->ID);
        printf("         Size : %d\n",wave->data->Size);
        printf("\n");
        {
            int i;
            for(i=0; i < wave->data->Size; i++) 
            {
                printf("%d\n",wave->data->Data[i]);
                /*if(i%16 == 15) putchar('\n');
                else {
                    putchar(' ');
                    if(i%8 == 7) putchar(' ');
                }*/
            }
        }
    }
}

CHUNK *read_chunk(FILE *fptr)
{
    CHUNK *chunk;
    DWORD id;
    DWORD size;

    if( 1 != fread(&id,sizeof(id),1,fptr) ) return 0;
    if( 1 != fread(&size,sizeof(size),1,fptr) ) return 0;
	if(id==0x61746164){
		chunk=(CHUNK*)malloc(sizeof(id)+sizeof(size));
		chunk->id=id;
		chunk->size=size;
		return chunk;
	}
    chunk = (CHUNK *)malloc(sizeof(id)+sizeof(size)+size);
    chunk->id   = id;
    chunk->size = size;
    if( size != fread(chunk->buff,1,size,fptr) ) return 0;

    return chunk;
}

WAVE *read_wave(const char *fname)
{
    FILE *fptr;
    WAVE  *wave;
    CHUNK *chunk;


	fptr = fopen(fname,"rb");
    assert(fptr);
    wave = (WAVE *)malloc(sizeof(WAVE));
    wave->riff = (RIFF *)malloc(sizeof(RIFF));
    wave->format = 0;
    wave->fact = 0;
    wave->data = 0;

    if( 1 == fread(wave->riff,sizeof(RIFF),1,fptr) ) {
        while( (chunk = read_chunk(fptr)) != 0)
        {
            switch(chunk->id)
            {
            case 0x20746D66: // fmt 
                wave->format = (FORMAT *)chunk;
                break;
            case 0x74636166: // fact 
                wave->fact   = (FACT   *)chunk;
                break;
            case 0x61746164: // data 
                wave->data   = (DATA   *)chunk;
                break;
            }
        }
    }
    fclose(fptr);

    return wave;
}

void free_wave(WAVE *wave)
{
    if(wave) {
        if(wave->riff)   free(wave->riff);
        if(wave->format) free(wave->format);
        if(wave->fact)   free(wave->fact);
        if(wave->data)   free(wave->data);
        free(wave);
    }
}
/*
int main()
{
    WAVE *wave;

    wave = read_wave("01_PUYO2_MLK5.wav");
	
    print_wave_info(wave);

    free_wave(wave);
}*/