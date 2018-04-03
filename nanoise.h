/* get value V, that is something between min and max,
   and scale it to something between a and b */
#define scale(v,min,max,a,b) ( (v-min)*(b-a)/(max-min)+a )

/* Cubic Sigmoid easing function, where 0.0 < N < 1.0 */
#define  S(N) (N*N*((N-1.0)*-2.0+1.0))

#ifndef NOISE_1D
  /* returns a value between 0 and RAND_MAX */
  #define NOISE_1D(V) (  \
    srandom((int)V),      \
    ( (random())/2 *       \
      S( (V-(int)V) )       \
    ) +                      \
    ( srandom((int)V-1),      \
      (random()/2) *           \
      S( (1-(V-(int)V)))        \
    )                            \
  )
#endif

#define FRACT(F) ( (F) - ((int)(F)) )

#define FLOOR(F) ((int)(F))

#define SMOOTH_SAW(F) ( S( FRACT(F) ) )

#define STEP_RANDOM_2D(x,y)\
  (srandom((FLOOR(x+2))*(FLOOR(y+2))), (float)(random()))

#define HORIZONTAL(x,y)                         \
  (                                              \
    ( SMOOTH_SAW(x) * STEP_RANDOM_2D(x,y)) +      \
    ( (1-SMOOTH_SAW(x)) * STEP_RANDOM_2D(x-1,y))   \
  )

#define NOISE_2D(x,y)(                          \
  (1-SMOOTH_SAW((y))) * HORIZONTAL((x),(y  )) +  \
  (  SMOOTH_SAW((y))  * HORIZONTAL((x),(y+1)) ))
