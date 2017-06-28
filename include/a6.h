#ifndef UTILSH
#define UTILSH




struct mutex_t{
  int32 count;
};

struct cond_t{
  int32 cond; //1 for need to fill, 0 for ready to eat
  struct mutex_t mx;
};

#endif
