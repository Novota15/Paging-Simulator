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
    int pg_counter;
    int curr_pg;
    int proc_val;
    int new_pg;
    int min_val;
    int min_pg;


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
        // keep looping if process is not active
        if(!q[proc_val].active) {
            continue;
        }
        else {
            pg_counter = q[proc_val].pc;         
            curr_pg = pg_counter/PAGESIZE;
            timestamps[proc_val][curr_pg] = tick;
            if(!q[proc_val].pages[curr_pg]) {
                // check to see if swap is possible and use LRU
                if(!pagein(proc_val, curr_pg)) {
                    min_val = tick;
                    for(new_pg = 0; new_pg < MAXPROCPAGES; new_pg++) {
                        // keep looping if new page not in pages
                        if(!q[proc_val].pages[new_pg]) {
                            continue;
                        }
                        else {
                            if(timestamps[proc_val][new_pg] < min_val) {
                                min_val = timestamps[proc_val][new_pg]; // set lowest timestamp
                                min_pg = new_pg; // set lowest page
                            }
                        }
                    }
                    // if pageout returns failure, exit
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
