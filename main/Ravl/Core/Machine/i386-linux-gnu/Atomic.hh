// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_ATOMIC_I386_HEADER
#define RAVL_ATOMIC_I386_HEADER 1
//! file="Ravl/Core/Machine/i386-linux-gnu/Atomic.hh"
//! userlevel=Default
//! author="Charles Galambos"
//! date="25/02/1999"
//! rcsid="$Id$"
//! docentry="Ravl.Core.Misc"
//! lib=RavlCore

#ifdef __cplusplus
extern "C" {
#endif

#define __ravl_atomic_fool_gcc(x) (*(volatile struct { int a[50]; } *)x)

typedef struct { volatile int counter; } ravl_atomic_t;

#define RAVL_ATOMIC_INIT(i)	{ (i) }

#define ravl_atomic_read(v)		((v)->counter)
#define ravl_atomic_set(v,i)		(((v)->counter) = (i))

static __inline__ void ravl_atomic_inc(volatile ravl_atomic_t *v) {
	__asm__ __volatile__(
		"lock ; incl %0"
		:"=m" (__ravl_atomic_fool_gcc(v))
		:"m" (__ravl_atomic_fool_gcc(v)));
}

static __inline__ void ravl_atomic_dec(volatile ravl_atomic_t *v) {
	__asm__ __volatile__(
	        "lock ; decl %0"
		:"=m" (__ravl_atomic_fool_gcc(v))
		:"m" (__ravl_atomic_fool_gcc(v)));
}

static __inline__ int ravl_atomic_dec_and_test(volatile ravl_atomic_t *v) {
	unsigned char c;

	__asm__ __volatile__(
		"lock ; decl %0; sete %1"
		:"=m" (__ravl_atomic_fool_gcc(v)), "=qm" (c)
		:"m" (__ravl_atomic_fool_gcc(v)));
	return c != 0;
}

#undef LOCK

#ifdef __cplusplus
};
#endif

#endif
