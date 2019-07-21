#include <stdio.h> 
#include <stdlib.h>

#include "simulator.h"

int selector(int, int);
void pager_predict(int*, int, int);
void set_to_one_2(int*, int*);
void set_to_one_3(int*, int*, int*);

// process selector
int selector(int curr_pg, int prev) {
    if(curr_pg == 0 && prev == 8) {
        return 1;
    }
    else if(curr_pg == 0 && prev == 3) { 
        return 4;  
    }
    else if(curr_pg == 9 && prev == 13) {
        return 2;  
    } 
    else if((prev == 11 && curr_pg == 0) || (prev == 3 && curr_pg == 10)) {
        return 0;
    }
    else if(curr_pg == 14) {
        return 3;
    }
    return -1;
}
// functions that set value to one
void set_to_one_2(int* a, int* b) {
    *a = 1; // setting a to 1
    *b = 1; // setting b to 1
}
// has one more input than A
void set_to_one_3(int* a, int* b, int* c) {
    *a = 1; // setting a to 1
    *b = 1; // setting b to 1
    *c = 1; // setting c to 1
}
// my predictions
void pager_predict(int* predict, int curr_pg, int curr_prog_var) {
    if(curr_prog_var == 0) {
        if(curr_pg == 2) {
            set_to_one_3(&predict[3], &predict[4], &predict[9]);
        }
        else if(curr_pg == 3) {
            set_to_one_3(&predict[4], &predict[10], &predict[11]);
        }
        else if(curr_pg == 10) {
            set_to_one_2(&predict[0], &predict[11]);
        }
        else if(curr_pg == 11) {
            set_to_one_2(&predict[0], &predict[1]);
        }
        else {
            set_to_one_2(&predict[curr_pg + 1], &predict[curr_pg + 2]);
        }
    }
    else if(curr_prog_var == 1) {
        if(curr_pg == 7) {
            set_to_one_2(&predict[0], &predict[8]);
        }
        else if(curr_pg == 8) {
            set_to_one_2(&predict[0], &predict[1]);
        }
        else {
            set_to_one_2(&predict[curr_pg + 1], &predict[curr_pg + 2]);
        }
    }
    else if(curr_prog_var == 2) {
        if(curr_pg == 12) {
            set_to_one_2(&predict[9], &predict[13]);
        }
        else if(curr_pg == 13) {
            set_to_one_3(&predict[0], &predict[9], &predict[10]);
        }
        else {
            set_to_one_2(&predict[curr_pg + 1], &predict[curr_pg + 2]);
        }
    }
    else if(curr_prog_var == 3) {
        if(curr_pg == 13) {
            set_to_one_2(&predict[0], &predict[14]);
        }
        else if(curr_pg == 14) {
            set_to_one_2(&predict[0], &predict[1]);
        }
        else {
            set_to_one_2(&predict[curr_pg+1], &predict[curr_pg+2]);
        }
    }
    else if(curr_prog_var == 4) {
        if(curr_pg == 2) {
            set_to_one_2(&predict[0], &predict[3]);
        }
        else if(curr_pg == 3) {
            set_to_one_2(&predict[0], &predict[1]);
        }
        else {
            set_to_one_2(&predict[curr_pg+1], &predict[curr_pg+2]);
        }
    }
    else {
        // if none of the prog_vars -> check the page and run all 
        // if (curr_pg == 1) {
        //     set_to_one_2(&predict[curr_pg+1], &predict[curr_pg+2]);
        // }
        if(curr_pg == 2) {
            set_to_one_3(&predict[3], &predict[4], &predict[10]);
        }
        else if(curr_pg == 3) {
            set_to_one_2(&predict[4], &predict[10]);
        }
        // else if(curr_pg == 4) {
        //     set_to_one_2(&predict[curr_pg+1], &predict[curr_pg+2]);
        // }
        // else if(curr_pg == 5) {
        //     set_to_one_2(&predict[curr_pg+1], &predict[curr_pg+2]);
        // }
        // else if(curr_pg == 6) {
        //     set_to_one_2(&predict[curr_pg+1], &predict[curr_pg+2]);
        // }
        else if(curr_pg == 7) {
            set_to_one_3(&predict[0], &predict[8], &predict[9]);
        }
        else if(curr_pg == 8) {
            set_to_one_3(&predict[0], &predict[9], &predict[10]);
        }
        // else if(curr_pg == 9) {
        //     set_to_one_2(&predict[curr_pg+1], &predict[curr_pg+2]);
        // }
        else if(curr_pg == 10) {
            set_to_one_3(&predict[0], &predict[10], &predict[12]);
        }
        else if(curr_pg == 11) {
            set_to_one_3(&predict[0], &predict[12], &predict[13]);
        }
        else if(curr_pg == 12) {
            set_to_one_2(&predict[0], &predict[9]);
            set_to_one_2(&predict[13], &predict[14]);
        }
        else if(curr_pg == 13) {
            set_to_one_2(&predict[0], &predict[9]);
            set_to_one_2(&predict[10], &predict[14]);
        }
        else {
            set_to_one_2(&predict[curr_pg+1], &predict[curr_pg+2]);
        }
    }
}

void pageit(Pentry q[MAXPROCESSES]) { 
    /* This file contains the stub for a predictive pager */

    /* Static vars */
    static int initialized = 0;
    static int tick = 1; // artificial time
    static int prev_pg[MAXPROCESSES];
    static int selection[MAXPROCESSES];

    /* Local vars */
    // int proctmp;
    int p_counter;
    int curr_pg;
    int proc_val;
    int selected = 0;

    /* initialize static vars on first run */
    if(!initialized){
	/* Init complex static vars here */
	
	initialized = 1;
    }
    
    /* TODO: Implement Predictive Paging */
    // fprintf(stderr, "pager-predict not yet implemented. Exiting...\n");
    // exit(EXIT_FAILURE);

    for(proc_val = 0; proc_val < MAXPROCESSES; proc_val++) {
        // if the proocess isn't active
        if(!q[proc_val].active) {
            continue; // do nothing
        }
        else { // if the process is active
            int page_predict[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // max_pc only needs a page number of 15
            p_counter = q[proc_val].pc;              
            curr_pg = p_counter/PAGESIZE;         
            page_predict[curr_pg] = 1;
            
            // selecting program based on the previous page
            selected = selector(curr_pg, prev_pg[proc_val]);
            if (selected != -1) {
                selection[proc_val] = selected;
            }

            pager_predict(page_predict, curr_pg, selection[proc_val]); // my prediction function
            for(int i = 0; i < 15; i++) { // 1911/128 < 15
                if(page_predict[i]) {
                    // swap the page if predicted
                    if(q[proc_val].pages[i]) {
                       continue;
                    }
                    else {
                        pagein(proc_val, i);
                    }    
                }
                else {
                    // page out if page not predicted
                    if(q[proc_val].pages[i]) {
                        if(pageout(proc_val, i)) {
                            continue;
                        }
                        else {
                            printf("Error\n");
                            exit(0);
                        }
                        
                    }
                }
            }
            // set the previous page from the current that was used
            prev_pg[proc_val] = curr_pg;
        }
    }

    /* advance time for next pageit iteration */
    tick++;
} 
