/**
 * This header should be included as first in every other header
 * */

#ifndef _STDIFX_MACROS_H_
#define _STDIFX_MACROS_H_

//#define _GNU_SOURCE
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#define ERR(source) (fprintf(stderr,"%s:%d\n",__FILE__,__LINE__),\
                        perror(source),kill(0,SIGKILL),\
                        exit(EXIT_FAILURE))

#define HERR(source) (fprintf(stderr,"%s(%d) at %s:%d\n",\
                        source,h_errno,__FILE__,__LINE__),\
                        perror(source),kill(0,SIGKILL),\
                        exit(EXIT_FAILURE))
	     
#endif
