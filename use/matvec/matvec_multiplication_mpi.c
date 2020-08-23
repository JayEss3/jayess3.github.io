#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define RUNTIME 1000

int main(int argc, char *argv[]){
	/*
		Initialize MPI library and get number of processes and current rank.
	*/
	int numprocs, myid;
	double startTime, endTime;
	MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	
	if(myid==0){
       startTime=MPI_Wtime();
    }
	
	int numPg = 1600;
	int num_of_sections = numPg/numprocs;
	int offset = myid*(num_of_sections);
	
	double pageRank = 1.0/numPg;
	double damp = 0.15;
	
	double max = 0.0;
	double min = 1.0;
	double total = 0.0;
	
	/*
		Initialize global vector to have equal probabilities of starting point.
		Initialize local x and y vectors to store values that are
		brought together in the end.
	*/
	double global_x[numPg];
	for(int i=0; i<numPg; i++){
		global_x[i] = pageRank;
	}
	double local_x[num_of_sections];
	for(int i=0; i<numPg; i++){
		local_x[i] = pageRank;
	}
	double local_y[num_of_sections];
	/*
		Dynamically allocate size of matrix, taken from slides.
		Create pieces of matrix for each process.
		Give values of 0.5 and apply damping simultaneously.
	*/
	double **Gmatrix;
	Gmatrix = (double**) malloc(num_of_sections*sizeof(double*));
	for(int i=0; i<num_of_sections; i++){
		Gmatrix[i] = (double*) malloc(numPg*sizeof(double));
	}
	for(int r=0; r<num_of_sections; r++){
		for(int c=0; c<numPg; c++){
			Gmatrix[r][c]= (damp/numPg);
			if(((offset-c)==1 || (offset-c)==-1) && (c!=0 && c!=numPg-1)){
				Gmatrix[r][c] = (1-damp)*.5 + (damp/numPg);
			}
		}
		offset++;
	}
	
	/*
		Give values for special edge cases.
	*/
	if(myid==0){
		Gmatrix[1][0] = (1-damp)*1 + (damp/numPg);
		Gmatrix[0][numPg-1] = (1-damp)*.5 + (damp/numPg);
	}
	if(myid==(numprocs-1)){
		Gmatrix[num_of_sections-2][numPg-1] = (1-damp)*.5 + (damp/numPg);
	}

	/*
		Loop through MatVec mulitplication k times.
		Call Allgather after each run through to update global_x.
	*/
	for(int k=0; k<RUNTIME; k++){
		for(int r=0; r<num_of_sections; r++){
			local_y[r] = 0.0;
			for(int c=0; c<numPg; c++){
				local_y[r] += Gmatrix[r][c] * global_x[c];
			}
		}
		for(int i=0; i<numPg; i++){
			local_x[i] = local_y[i];
		}
		MPI_Allgather(local_x, num_of_sections, MPI_DOUBLE,
					  global_x, num_of_sections, MPI_DOUBLE,
					  MPI_COMM_WORLD);
	}
	
	/*
		Go to any single process and find the min, max, and total
		values for the finalized vector.
	*/
	if(myid==0){
		for(int c=0; c<numPg; c++){
			if(global_x[c] > max){max = global_x[c];}
			if(global_x[c] < min){min = global_x[c];}
			total += global_x[c];
		}
	}
	/*
		Output Min, max, total, and final runtime.
	*/
	if(myid==0){
		printf("Max: %lf\n", max);
		printf("Min: %lf\n", min);
		printf("Total: %lf\n", total);
		endTime=MPI_Wtime();
        printf("Runtime: %.16f",endTime-startTime);
	}
	
	/*
		Free all of the memory previously allocated.
	*/
	for(int i=0; i<num_of_sections; i++){
		free(Gmatrix[i]);
	}
	free(Gmatrix);
	
	MPI_Finalize();
	return 0;
}