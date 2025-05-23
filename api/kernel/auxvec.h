#ifndef KERNEL_AUXVEC_H
#define KERNEL_AUXVEC_H

// From: https://github.com/torvalds/linux/blob/v3.19/include/uapi/linux/auxvec.h

/* Symbolic values for the entries in the auxiliary table
   put on the initial stack */
#define AT_NULL   0 /* end of vector */
#define AT_IGNORE 1 /* entry should be ignored */
#define AT_EXECFD 2 /* file descriptor of program */
#define AT_PHDR   3 /* program headers for program */
#define AT_PHENT  4 /* size of program header entry */
#define AT_PHNUM  5 /* number of program headers */
#define AT_PAGESZ 6 /* system page size */
#define AT_BASE   7 /* base address of interpreter */
#define AT_FLAGS  8 /* flags */
#define AT_ENTRY  9 /* entry point of program */
#define AT_NOTELF 10  /* program is not ELF */
#define AT_UID    11  /* real uid */
#define AT_EUID   12  /* effective uid */
#define AT_GID    13  /* real gid */
#define AT_EGID   14  /* effective gid */
#define AT_PLATFORM 15  /* string identifying CPU for optimizations */
#define AT_HWCAP  16    /* arch dependent hints at CPU capabilities */
#define AT_CLKTCK 17  /* frequency at which times() increments */
/* AT_* values 18 through 22 are reserved */
#define AT_SECURE 23   /* secure mode boolean */
#define AT_BASE_PLATFORM 24 /* string identifying real platform, may
         * differ from AT_PLATFORM. */
#define AT_RANDOM 25  /* address of 16 random bytes */
#define AT_HWCAP2 26  /* extension of AT_HWCAP */

#define AT_EXECFN  31 /* filename of program */

typedef struct auxv
{
  long int a_type;              /* Entry type */
  union
    {
      long int a_val;           /* Integer value */
      const void *a_ptr;        /* Pointer value */
      void (*a_fcn) (void);     /* Function pointer value */
    } a_un;

  void set_long(long t, long v) {
    a_type = t;
    a_un.a_val = v;
  }
  void set_ptr(long t, const void* ptr) {
    a_type = t;
    a_un.a_ptr = ptr;
  }
  void set_func(long t, void (*fn)()) {
    a_type = t;
    a_un.a_fcn = fn;
  }
} auxv_t;

#endif /* KERNEL_AUXVEC_H */
