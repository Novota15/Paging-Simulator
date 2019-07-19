#include <stdio.h> 
#include <stdlib.h>

#include "simulator.h"

void pageit(Pentry q[MAXPROCESSES]) { 
    /* This file contains the stub for an LRU pager */

    /* Static vars */
    static int initialized = 0;
    static int tick = 1; // artificial time
    static int timestamps[MAXPROCESSES][MAXPROCPAGES];

    /* Local vars */
    int proctmp;
    int pagetmp;
    int p_counter;
    int my_pg;
    int proc_val;
    

    /* initialize static vars on first run */
    if(!initialized){
	for(proctmp=0; proctmp < MAXPROCESSES; proctmp++){
	    for(pagetmp=0; pagetmp < MAXPROCPAGES; pagetmp++){
		timestamps[proctmp][pagetmp] = 0; 
	    }
	}
	initialized = 1;
    }
    // LRU paging implementation

    for(proc_val = 0; proc_val < MAXPROCESSES; proc_val++) { 
        if(!q[proc_val].active) {
            continue;
        }
        else {
            p_counter = q[proc_val].pc;         
            my_pg = p_counter/PAGESIZE;
            timestamps[proc_val][my_pg] = tick;
            if(!q[proc_val].pages[my_pg]) {
                // check to see if swap is possible and use LRU
                if(!pagein(proc_val, my_pg)) {
                    min_val = tick;
                    for(new_pg = 0; new_pg < MAXPROCPAGES; new_pg++) {
                        if(!q[proc_val].pages[new_pg]) {
                            continue;
                        }
                        else {
                            if(timestamps[proc_val][new_pg] < min_val) {
                                // setting lowest timestamp
                                min_val = timestamps[proc_val][new_pg];
                                min_pg = new_pg; // setting lowest page
                            }
                        }
                    }
                    // if pageout returns failure then exit
                    if(!pageout(proc_val, min_pg)) {
                        printf("*** Error! ***\n");
                    }
                        
                }
            }
        }
    }    

    /* advance time for next pageit iteration */
    tick++;
} 
