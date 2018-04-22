#include <stddef.h>	/* for size_t */
#include <stdlib.h>
#include <string.h>
#include <mint/osbind.h>
#include "lib.h"
#include "malloc_int.h"

/* CAUTION: use _mallocChunkSize() to tailor to your environment,
 *          do not make the default too large, as the compiler
 *          gets screwed on a 1M machine otherwise (stack/heap clash)
 */
/* minimum chunk to ask OS for */
static size_t MINHUNK =	8192L;	/* default */
static size_t MAXHUNK = 32 * 1024L; /* max. default */

/* tune chunk size */
void __mallocChunkSize(size_t siz) { MAXHUNK = MINHUNK = siz; }


void *malloc(size_t n)
{
	struct mem_chunk *p, *q;
	size_t sz;

	/* add a mem_chunk to required size and round up */
	n = (n + sizeof(struct mem_chunk) + (MALLOC_ALIGNMENT - 1)) & ~(MALLOC_ALIGNMENT - 1);

	/* look for first block big enough in free list */
	p = &_mchunk_free_list;
	q = _mchunk_free_list.next;
	while (q && (q->size < n || q->valid == VAL_BORDER))
	{
		p = q;
		q = q->next;
	}

	/* if not enough memory, get more from the system */
	if (q == NULL)
	{
		size_t const page_size = 8192;
		sz = n + BORDER_EXTRA;

		sz = (sz + page_size - 1) & -page_size;

		q = (struct mem_chunk * ) Malloc(sz);
		if (q == NULL) /* can't alloc any more? */
			return NULL;

		/* Note: q may be below the highest allocated chunk */
		p = &_mchunk_free_list;
		while (p->next && q > p->next)
			p = p->next;

		q->size = BORDER_EXTRA;
		sz -= BORDER_EXTRA;
		q->valid = VAL_BORDER;
		ALLOC_SIZE (q) = sz;
		q->next = (struct mem_chunk *) ((long) q + BORDER_EXTRA);
		q->next->next = p->next;
		p = p->next = q;
		q = q->next;

		q->size = sz;
		q->valid = VAL_FREE;
	}

	if (q->size > n + sizeof(struct mem_chunk))
	{
		/* split, leave part of free list */
		q->size -= n;
		q = (struct mem_chunk * )(((long) q) + q->size);
		q->size = n;
		q->valid = VAL_ALLOC;
	}
	else
	{
		/* just unlink it */
		p->next = q->next;
		q->valid = VAL_ALLOC;
	}

	q->next = NULL;
	q++; /* hand back ptr to after chunk desc */

	return (void *) q;
}

