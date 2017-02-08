/******************************************************************************/
#ifdef JEMALLOC_H_TYPES

typedef struct spin_s spin_t;

#endif /* JEMALLOC_H_TYPES */
/******************************************************************************/
#ifdef JEMALLOC_H_STRUCTS

struct spin_s {
	unsigned iteration;
};

#endif /* JEMALLOC_H_STRUCTS */
/******************************************************************************/
#ifdef JEMALLOC_H_EXTERNS

#endif /* JEMALLOC_H_EXTERNS */
/******************************************************************************/
#ifdef JEMALLOC_H_INLINES

#ifndef JEMALLOC_ENABLE_INLINE
void	spin_init(spin_t *spin);
void	spin_adaptive(spin_t *spin);
#endif

#if (defined(JEMALLOC_ENABLE_INLINE) || defined(JEMALLOC_SPIN_C_))
JEMALLOC_INLINE void
spin_init(spin_t *spin)
{

	spin->iteration = 0;
}

JEMALLOC_INLINE void
spin_adaptive(spin_t *spin)
{
	volatile uint32_t i;

	if (spin->iteration < 5) {
		for (i = 0; i < (1U << spin->iteration); i++) {
			CPU_SPINWAIT;
		}
		spin->iteration++;
	} else {
#ifdef _WIN32
		SwitchToThread();
#else
		sched_yield();
#endif
	}
}

#endif

#endif /* JEMALLOC_H_INLINES */
/******************************************************************************/

