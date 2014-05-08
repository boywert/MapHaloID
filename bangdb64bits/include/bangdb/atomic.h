/*
 * atomic.h
 *
 *  Author: Sachin Sinha
 *  Libbangdb library
 *
 *  Copyright (C) 2014 IQLECT All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *
 *      * Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *      * Redistributions in binary form must reproduce the above
 *  copyright notice, this list of conditions and the following disclaimer
 *  in the documentation and/or other materials provided with the
 *  distribution.
 *
 *      * The names of its contributors may not be used to endorse or
 *  promote products derived from this software without specific prior
 *  written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ATOMIC_H_
#define ATOMIC_H_

typedef struct {

    volatile int counter;

} atomic_t;


#define ATOMIC_INIT(i)  { (i) }

#define atomic_read(v) ((v)->counter)

#define atomic_set(v,i) (((v)->counter) = (i))

static inline void atomic_add( int i, atomic_t *v )
{
         (void)__sync_add_and_fetch(&v->counter, i);
}

static inline void atomic_sub( int i, atomic_t *v )
{
        (void)__sync_sub_and_fetch(&v->counter, i);
}

static inline int atomic_sub_and_test( int i, atomic_t *v )
{
        return !(__sync_sub_and_fetch(&v->counter, i));
}

static inline void atomic_inc( atomic_t *v )
{
       (void)__sync_fetch_and_add(&v->counter, 1);
}

static inline int atomic_get_inc(atomic_t *v)
{
	return __sync_fetch_and_add(&v->counter, 1);
}

static inline int atomic_inc_get(atomic_t *v)
{
	return __sync_add_and_fetch(&v->counter, 1);
}

static inline void atomic_dec( atomic_t *v )
{
       (void)__sync_fetch_and_sub(&v->counter, 1);
}

static inline int atomic_get_dec( atomic_t *v )
{
      return __sync_fetch_and_sub(&v->counter, 1);
}

static inline int atomic_dec_get( atomic_t *v )
{
      return __sync_sub_and_fetch(&v->counter, 1);
}

static inline int atomic_dec_and_test( atomic_t *v )
{

       return !(__sync_sub_and_fetch(&v->counter, 1));
}

static inline int atomic_inc_and_test( atomic_t *v )
{
      return !(__sync_add_and_fetch(&v->counter, 1));
}

static inline int atomic_add_negative( int i, atomic_t *v )
{
       return (__sync_add_and_fetch(&v->counter, i) < 0);
}

typedef struct {

    volatile off_t counter;

} atomic_FILEOFF_T;

#define ATOMIC_FILEOFF_T_INIT(i)  { (i) }

#define atomic_FILEOFF_T_read(v) ((v)->counter)

#define atomic_FILEOFF_T_set(v,i) (((v)->counter) = (i))

static inline void atomic_FILEOFF_T_add( off_t i, atomic_FILEOFF_T *v )
{
         (void)__sync_add_and_fetch(&v->counter, i);
}

static inline void atomic_FILEOFF_T_sub( off_t i, atomic_FILEOFF_T *v )
{
        (void)__sync_sub_and_fetch(&v->counter, i);
}

static inline off_t atomic_FILEOFF_T_sub_and_test( off_t i, atomic_FILEOFF_T *v )
{
        return !(__sync_sub_and_fetch(&v->counter, i));
}

static inline void atomic_FILEOFF_T_inc( atomic_FILEOFF_T *v )
{
       (void)__sync_fetch_and_add(&v->counter, 1);
}

static inline off_t atomic_FILEOFF_T_get_inc(atomic_FILEOFF_T *v)
{
	return __sync_fetch_and_add(&v->counter, 1);
}

static inline off_t atomic_FILEOFF_T_inc_get(atomic_FILEOFF_T *v)
{
	return __sync_add_and_fetch(&v->counter, 1);
}

static inline off_t atomic_FILEOFF_T_get_add(atomic_FILEOFF_T *v, int x)
{
	return __sync_fetch_and_add(&v->counter, x);
}

static inline off_t atomic_FILEOFF_T_add_get(atomic_FILEOFF_T *v, int x)
{
	return __sync_add_and_fetch(&v->counter, x);
}

static inline void atomic_FILEOFF_T_dec( atomic_FILEOFF_T *v )
{
       (void)__sync_fetch_and_sub(&v->counter, 1);
}

static inline off_t atomic_FILEOFF_T_dec_and_test( atomic_FILEOFF_T *v )
{
       return !(__sync_sub_and_fetch(&v->counter, 1));
}

static inline off_t atomic_FILEOFF_T_inc_and_test( atomic_FILEOFF_T *v )
{
      return !(__sync_add_and_fetch(&v->counter, 1));
}

static inline off_t atomic_FILEOFF_T_add_negative( int i, atomic_t *v )
{

       return (__sync_add_and_fetch(&v->counter, i) < 0);

}

typedef struct {

    volatile long long counter;

} atomic64_t;

#define ATOMIC64_INIT(i)  { (i) }

#define atomic64_read(v) ((v)->counter)

#define atomic64_set(v,i) (((v)->counter) = (i))

static inline void atomic64_add( int i, atomic64_t *v )
{
         (void)__sync_add_and_fetch(&v->counter, i);
}

static inline void atomic64_sub( int i, atomic64_t *v )
{
        (void)__sync_sub_and_fetch(&v->counter, i);
}

static inline int atomic64_sub_and_test( int i, atomic64_t *v )
{
        return !(__sync_sub_and_fetch(&v->counter, i));
}

static inline void atomic64_inc( atomic64_t *v )
{
       (void)__sync_fetch_and_add(&v->counter, 1);
}

static inline long long atomic64_get_inc(atomic64_t *v)
{
	return __sync_fetch_and_add(&v->counter, 1);
}

static inline long long atomic64_inc_get(atomic64_t *v)
{
	return __sync_add_and_fetch(&v->counter, 1);
}

static inline void atomic64_dec( atomic64_t *v )
{
       (void)__sync_fetch_and_sub(&v->counter, 1);
}

static inline int atomic64_dec_and_test( atomic64_t *v )
{
       return !(__sync_sub_and_fetch(&v->counter, 1));
}

static inline int atomic64_inc_and_test( atomic64_t *v )
{
      return !(__sync_add_and_fetch(&v->counter, 1));
}

static inline int atomic64_add_negative( int64_t i, atomic64_t *v )
{
       return (__sync_add_and_fetch(&v->counter, i) < 0);
}

#endif /* ATOMIC_H_ */
