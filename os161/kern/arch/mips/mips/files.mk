SRCS-y += cache_mips1.S exception.S start.S switch.S threadstart.S tlb_mips1.S

SRCS-y += interrupt.c lamebus_mips.c pcb.c ram.c spl.c syscall.c trap.c

SRCS-$(OPT_DUMBVM) += dumbvm.c

# Include copyinout.c here, as it's implementation relies on certain machine-dependent
# assumptions.
SRCS-y += ../../../lib/copyinout.c