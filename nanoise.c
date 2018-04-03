#include <stdio.h>     /* printf                            */
#include <stdlib.h>    /* atof, atoi, srandom, random, puts */
#include <time.h>      /* time, to seed random              */
#include <inttypes.h>  /* uint_8, uint_16 */
#include "nanoise.h"

#ifdef SKIP
  : ${D=_2D}
  tcc -D$D nanoise.c                       \
    && echo 'running a.out'                \
    && a.out 8 0.01 > nanoise$D.pgm        \
    && echo 'converting to png'            \
    && convert nanoise$D.pgm nanoise$D.png \
    && rm nanoise$D.pgm
  exit 0
#endif

/* nanoise - Nano Noise */

int main(int argc, char ** argv){

  #ifdef _1D

    if(argc!=4) return 1;
  
    float i, x, l;
    x = (float) atof(argv[1]);   /* initial value */
    l = (float) atof(argv[2])+x; /* upper limit   */
    i = (float) atof(argv[3]);   /* increment     */
  
    while(x<l)
      printf("%f %f\n", x,
        (noise1d(x))+(noise1d((x/0.01))*0.01)),
      x += i;

  /* 1D Noise, refactoring...
    uint_16 * array = malloc(sizeof(short)*0xff);
    NANOISE_1D(array, 0x00, 0xff, 0x0f, 0x02);
    uint_8 i = 0;
    do{ printf("%u %u ", i, array[i]); i++;}while(i);
  */
  #endif

  #ifdef _2D
    if(argc!=3) return 1;

    uint32_t s, S;
    float y, x, i;
    s =          atoi(argv[1]);
    i = (float)  atof(argv[2]);
    S = (uint32_t) ((float)s)/i;
    srandom(time(0x00));
  
    puts("P2");
    printf("%d %d 255\n", S, S);

    /* refactoring...
    uint8_t * canvas = malloc(0xff * 0xff);
    NANOISE_2D(canvas, 0x00, 0xff, 0x0f);
    x=y=0;
    while((int)y<)
    */

    x=y=0;
    while((int)y<s){
      x=0;
      while((int)x<s){
        printf(
          "%u ",
          (unsigned int)
          scale( (float)(
            (NOISE_2D(x,y          )*0.5f  ) +
            (NOISE_2D(x/0.5f,y/0.5f)*0.25f ) +
            (NOISE_2D(x/0.2f,y/0.2f)*0.125f) +
            (NOISE_2D(x/0.1f,y/0.1f)*0.125f) ),
            (float) 0,
            (float) RAND_MAX,
            (float) 0, 
            (float) 256
          )
        );
        x+=i;
      };
      puts("");
      y+=i;    
    };
  #endif

  return 0;
}
