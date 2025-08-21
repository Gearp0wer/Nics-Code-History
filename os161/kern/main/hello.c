/*
 * Funny haha assignment 0
 */




#include <types.h>
#include <kern/errno.h>
#include <kern/unistd.h>
#include <kern/limits.h>
#include <lib.h>
#include <clock.h>
#include <thread.h>
#include <syscall.h>
#include <uio.h>
#include <vfs.h>
#include <sfs.h>
#include <test.h>

#define _PATH_SHELL "/bin/sh"

void hello(void){
  kprintf("Hello World!\n");
}

