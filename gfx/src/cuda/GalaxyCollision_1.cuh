#ifndef _SHORTEST_CUDA_H_
#define _SHORTEST_CUDA_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#define MAX_GRID_DIM_SIZE 65535

#define MAX_BLOCK_THREAD_COUNT 512

#define MAX_BLOCK_DIM_SIZE 32

#define C_ERR(err) (printf("%s in %s at line %d\n", cudaGetErrorString(err), __FILE__, __LINE__),\
                    exit(EXIT_FAILURE))

__device__
float3 bodiesInteraction(double4 body1, double4 body2, double3 acceleration);

__device__
float3 tileAcceleration(double3 currPosition, double3 acceleration);

__global__
void calculateForcesKernel(double4* bodyDescription, double3* acceleration, int n);

__host__
void galaxyCollisionLogic(double4* d_bodyDescription, double3* d_acceleration, int n);

__host__
void galaxyCollisionInit(double4* bodyDescription, double3* acceleration, int count);

#endif
