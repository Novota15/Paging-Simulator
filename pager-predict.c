#include <stdio.h> 
#include <stdlib.h>

#include "simulator.h"

void pager_predict(int*, int, int);
void set_to_one_A(int*, int*);
void set_to_one_B(int*, int*, int*);

void pager_predict(int* predict, int my_pg, int my_prog_var) {
    if(my_prog_var == 0) {
        if(my_pg == 2) {
            set_to_one_B(&predict[3], &predict[4], &predict[10]);
        }
        else if(my_pg == 3) {
            set_to_one_B(&predict[4], &predict[10], &predict[11]);
        }
        else if(my_pg == 10) {
            set_to_one_A(&predict[0], &predict[11]);
        }
        else if(my_pg == 11) {
            set_to_one_A(&predict[0], &predict[1]);
        }
        else {
            set_to_one_A(&predict[my_pg + 1], &predict[my_pg + 2]);
        }
    }
    else if(my_prog_var == 1) {
        if(my_pg == 7) {
            set_to_one_A(&predict[0], &predict[8]);
        }
        else if(my_pg == 8) {
            set_to_one_A(&predict[0], &predict[1]);
        }
        else {
            set_to_one_A(&predict[my_pg + 1], &predict[my_pg + 2]);
        }
    }
    else if(my_prog_var == 2) {
        if(my_pg == 12) {
            set_to_one_A(&predict[9], &predict[13]);
        }
        else if(my_pg == 13) {
            set_to_one_B(&predict[0], &predict[9], &predict[10]);
        }
        else {
            set_to_one_A(&predict[my_pg + 1], &predict[my_pg + 2]);
        }
    }
    else if(my_prog_var == 3) {
        if(my_pg == 13) {
            set_to_one_A(&predict[0], &predict[14]);
        }
        else if(my_pg == 14) {
            set_to_one_A(&predict[0], &predict[1]);
        }
        else {
            set_to_one_A(&predict[my_pg+1], &predict[my_pg+2]);
        }
    }
    else if(my_prog_var == 4) {
        if(my_pg == 2) {
            set_to_one_A(&predict[0], &predict[3]);
        }
        else if(my_pg == 3) {
            set_to_one_A(&predict[0], &predict[1]);
        }
        else {
            set_to_one_A(&predict[my_pg+1], &predict[my_pg+2]);
        }
    }
    else {
        // if none of the prog_vars -> id the page and run all 
        if(my_pg == 2) {
            set_to_one_B(&predict[3], &predict[4], &predict[10]);
        }
        else if(my_pg == 3) {
            set_to_one_A(&predict[4], &predict[10]);
        }
        else if(my_pg == 7) {
            set_to_one_B(&predict[0], &predict[8], &predict[9]);
        }
        else if(my_pg == 8) {
            set_to_one_B(&predict[0], &predict[9], &predict[10]);
        }
        else if(my_pg == 10) {
            set_to_one_B(&predict[0], &predict[11], &predict[12]);
        }
        else if(my_pg == 11) {
            set_to_one_B(&predict[0], &predict[12], &predict[13]);
        }
        else if(my_pg == 12) {
            set_to_one_A(&predict[0], &predict[9]);
            set_to_one_A(&predict[13], &predict[14]);
        }
        else if(my_pg == 13) {
            set_to_one_A(&predict[0], &predict[9]);
            set_to_one_A(&predict[10], &predict[14]);
        }
        else {
            set_to_one_A(&predict[my_pg+1], &predict[my_pg+2]);
        }
    }
}

void set_to_one_A(int* num_one, int* num_two) {
    *num_one = 1; // setting num_one to 1
    *num_two = 1; // setting num_two to 1
}

void set_to_one_B(int* num_one, int* num_two, int* num_three) {
    *num_one = 1; // setting num_one to 1
    *num_two = 1; // setting num_two to 1
    *num_three = 1; // setting num_three to 1
}

void pageit(Pentry q[MAXPROCESSES]) { 
    /* This file contains the stub for a predictive pager */

    /* Static vars */
    static int initialized = 0;
    static int tick = 1; // artificial time
    static int prev_pg[MAXPROCESSES];
    static int selection[MAXPROCESSES];

    /* Local vars */
    int proctmp;
    int p_counter;
    int my_pg;
    int proc_val;

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
            int pg_predict[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // max_pc only requires a pg num of 15
            p_counter = q[proc_val].pc;              
            my_pg = p_counter/PAGESIZE;         
            pg_predict[my_pg] = 1;

            // selecting prog based on the prev pg
            if(my_pg == 0 && prev_pg[proc_val] == 8) {
                selection[proc_val] = 1;
            }
            else if(my_pg == 0 && prev_pg[proc_val] == 3) { 
                selection[proc_val] = 4;  
            }
            else if(my_pg == 9 && prev_pg[proc_val] == 13) {
                selection[proc_val] = 2;  
            } 
            else if((prev_pg[proc_val] == 11 && my_pg == 0) || (prev_pg[proc_val] == 3 && my_pg == 10)) {
                selection[proc_val] = 0;
            }
            else if(my_pg == 14) {
                selection[proc_val] = 3;
            }

            pager_predict(pg_predict, my_pg, selection[proc_val]); // function that makes a prediction
            // 1911/128 < 15
            for(int i = 0; i < 15; i++) {
                if(pg_predict[i]) {
                    // swap the page if 'tis predicted
                    if(q[proc_val].pages[i]) {
                       continue;
                    }
                    else {
                        pagein(proc_val, i);
                    }
                    
                }
                else {
                    // doing a page out if the page is not predicted
                    if(q[proc_val].pages[i]) {
                        if(pageout(proc_val, i)) {
                            continue;
                        }
                        else {
                            printf("*** Error! ***\n");
                            exit(0);
                        }
                        
                    }
                }
            }
            // set the previous pg
            prev_pg[proc_val] = my_pg;
        }
    }

    /* advance time for next pageit iteration */
    tick++;
} 
