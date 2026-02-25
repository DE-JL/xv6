#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "stat.h"
#include "spinlock.h"
#include "proc.h"
#include "fs.h"
#include "sleeplock.h"
#include "file.h"
#include "fcntl.h"

static struct spinlock readcount_lock;
static uint64 readcount;

void readcount_init(void)
{
    initlock(&readcount_lock, "readcount");
    readcount = 0;
}

void readcount_inc(void)
{
    acquire(&readcount_lock);
    ++readcount;
    release(&readcount_lock);
}

uint64 readcount_get(void)
{
    acquire(&readcount_lock);
    uint64 count = readcount;
    release(&readcount_lock);
    return count;
}
