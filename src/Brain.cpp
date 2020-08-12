#include "Brain.h"

Brain *Brain::breed(Brain *mother, Brain *father)
{
  return NULL; // TODO
}


// everything below this line is ugly, but it was the only way

// add an include for every derived class of Brain...
#include "SMP.h"
#include "SP.h"

#define _BRAIN_DYNAMIC_LOAD(c, s, e) \
if(e == c::getExtension()) \
{ \
  Brain *b = new c; \
  if(b->load(s)) \
    return b; \
  else \
    delete b; \
}

Brain *_brain_dynamic_load(string file)
{
  string ext = file.substr(file.find_last_of('.'));
  _BRAIN_DYNAMIC_LOAD(SMP, file, ext) // ...add one of these macros for every derived class of Brain...
  _BRAIN_DYNAMIC_LOAD(SP, file, ext)
  return NULL;
}

Brain *_brain_random(int inputSize)
{
  static const int NUM_DERIVED = 2; // ...increment this...

  srand(time(0));
  switch(rand() % NUM_DERIVED) // ...and add a new case
  {
  case 0:
    return new SMP(inputSize);
  case 1:
    return new SP(inputSize);
  default:
    return NULL;
  }
}
