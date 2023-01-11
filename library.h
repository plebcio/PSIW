#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include "common.h"

// returns enter tick - inclusive
int enter_lib(process_info proc_state);
// returns exit tick - inclusive
int exit_lib(process_info* proc_state_ptr, int entry_tick);


#endif