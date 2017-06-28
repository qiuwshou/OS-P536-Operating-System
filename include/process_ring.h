/* process_ring.h */

extern int32 NUM_PROCESS;
extern int32 NUM_ROUND;
void work(int32 e, int32 r, int32 value[], sid32 mutex );
void hang(int32 e, int32 r, int32 value[], sid32 mutex );
void loop(int32 e, int32 r, int32 value[], sid32 mutex );
void chaos(int32 e, int32 r, int32 value[], sid32 mutex );
