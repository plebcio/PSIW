#include "common.h"


// TICKS update only when new book comes out

// returns enter tick - inclusive
int enter_lib(process_info proc_state){

    proc_state.library_state[number_of_readers]++;
    

    printf("\t\tn of free spots = %d\n", proc_state.library_state[number_of_free_spots]);
    printf("\t\twriters waiting read list len = %d\n", proc_state.library_state[len_queued_writer_reading_list]);

    
    return proc_state.library_state[lib_tick];
}


// returns exit tick - inclusive
int exit_lib(process_info* proc_state_ptr, int entry_tick){

    proc_state_ptr->library_state[number_of_readers]--;
    int exit_tick = proc_state_ptr->library_state[lib_tick];
    
    // and new tick - writer could have published during these ticks
    for (int tick = entry_tick+1; tick <= exit_tick; tick++){
        //printf("ticked in lib %d\n", tick); fflush(stdout);
        // add new ticks to list
        proc_state_ptr->library_ticks = append_node_unique(proc_state_ptr->library_ticks, tick);
    }

    printf("\t\tn of free spots = %d\n", proc_state_ptr->library_state[number_of_free_spots]);
    printf("\t\twriters waiting read list len = %d\n", proc_state_ptr->library_state[len_queued_writer_reading_list]);

    return exit_tick;
}

