/*
 * free.c
 *
 *  Created on: 29.05.2013
 *      Author: mfro
 */

#include <stdlib.h>
#include <mint/osbind.h>
#include "lib.h"
#include "malloc_int.h"

/* linked list of free blocks struct defined in lib.h */
struct mem_chunk _mchunk_free_list = { VAL_FREE, NULL, 0L };


void free(void *param)
{
	struct mem_chunk *o, *p, *q, *s;
	struct mem_chunk *r = (struct mem_chunk *) param;

	/* free(NULL) should do nothing */
	if (r == NULL)
		return;

	/* move back to uncover the mem_chunk */
	r--; /* there it is! */

	if (r->valid != VAL_ALLOC)
		return;

	r->valid = VAL_FREE;

	/* stick it into free list, preserving ascending address order */
	o = NULL;
	p = &_mchunk_free_list;
	q = _mchunk_free_list.next;
	while (q && q < r)
	{
		o = p;
		p = q;
		q = q->next;
	}

	/* merge after if possible */
	s = (struct mem_chunk *)(((long) r) + r->size);
	if (q && s >= q && q->valid != VAL_BORDER)
	{
		r->size += q->size;
		q = q->next;
		s->size = 0;
		s->next = NULL;
	}
	r->next = q;

	/* merge before if possible, otherwise link it in */
	s = (struct mem_chunk * )(((long) p) + p->size);
	if (q && s >= r && p != &_mchunk_free_list)
	{
		/* remember: r may be below &_mchunk_free_list in memory */
		if (p->valid == VAL_BORDER)
		{
			if (ALLOC_SIZE(p) == r->size)
			{
				o->next = r->next;
				Mfree (p);
			}
			else
				p->next = r;

			return;
		}

		p->size += r->size;
		p->next = r->next;
		r->size = 0;
		r->next = NULL;

		s = (struct mem_chunk *)(((long) p) + p->size);

		if (o->valid == VAL_BORDER && ALLOC_SIZE(o) == p->size)
		{
			q = &_mchunk_free_list;
			s = q->next;
			while (s && s < o)
			{
				q = s;
				s = q->next;
			}
			if (s)
			{
				q->next = p->next;
				Mfree (o);
			}
		}
	}
	else
    {
		s = (struct mem_chunk * )(((long) r) + r->size);
		p->next = r;
	}
}
