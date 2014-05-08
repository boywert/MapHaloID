/*
 * pagehdr.h
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


#ifndef PAGEHDR_H_
#define PAGEHDR_H_

#include "basehdr.h"

struct page_base_hdr
{
private:
	FILEOFF_T eof;
	FILEOFF_T pagelsn;
	FILEOFF_T rofftORdirsz;
	SHORT_T pgtpORgd;
	SHORT_T empty1;
	int empty2;
public:
	page_base_hdr() {}

	page_base_hdr(FILEOFF_T _eof, FILEOFF_T _pglsn, FILEOFF_T _rofftORdirsz, SHORT_T _pgtpORgd)
	{
		eof = (_eof);
		pagelsn = (_pglsn);
		rofftORdirsz = (_rofftORdirsz);
		pgtpORgd = (_pgtpORgd);
		empty1 = 0;
		empty2 = 0;
	}

	void init_base_hdr(FILEOFF_T _eof, FILEOFF_T _pglsn, FILEOFF_T _rofftORdirsz, SHORT_T _pgtpORgd)
	{
		eof = (_eof);
		pagelsn = (_pglsn);
		rofftORdirsz = (_rofftORdirsz);
		pgtpORgd = (_pgtpORgd);
		empty1 = 0;
		empty2 = 0;
	}

	void reset()
	{
		eof = (-1);
		pagelsn = (-1);
		rofftORdirsz = (-1);
		pgtpORgd = (-1);
		empty1 = 0;
		empty2 = 0;
	}

	//getters and setters
	void seteof(FILEOFF_T _eof) { eof = (_eof); }
	FILEOFF_T geteof() { return (eof); }

	void setpagelsn(FILEOFF_T _pglsn) { pagelsn = (_pglsn); }
	FILEOFF_T getpagelsn() { return (pagelsn); }

	void setrofftORdirsz(FILEOFF_T _rofftORdirsz) { rofftORdirsz = (_rofftORdirsz); }
	FILEOFF_T getrofftORdirsz() { return (rofftORdirsz); }

	void setpagetypeORgd(SHORT_T _pgtp) { pgtpORgd = (_pgtp); }
	SHORT_T getpagetypeORgd() { return (pgtpORgd); }
};

const int PAGE_BASE_HDR_SZ = sizeof(page_base_hdr);

#define DATHDR_SZ 				PAGE_BASE_HDR_SZ

struct dir_idx_record
{
private:
	FILEOFF_T idxofft;
public:
	dir_idx_record() {}
	dir_idx_record(FILEOFF_T _idxofft) { idxofft = (_idxofft); }
	void setidxofft(FILEOFF_T _idxofft) { idxofft = (_idxofft); }
	FILEOFF_T getidxofft() { return (idxofft); }
};

struct btree_hdr
{
private:
	SHORT_T pgtype;
	SHORT_T m;
	int empty;
	FILEOFF_T lowkeyptr;
	FILEOFF_T nextpage;
	FILEOFF_T pagelsn;

public:
	btree_hdr() {}

	btree_hdr(SHORT_T _pgtype, SHORT_T _m, FILEOFF_T _lowkeyptr, FILEOFF_T _nextpage, FILEOFF_T _pagelsn);

	void inithdr(SHORT_T _pgtype, SHORT_T _m, FILEOFF_T _lowkeyptr, FILEOFF_T _nextpage, FILEOFF_T _pagelsn);

	void reset();

	//getters and setters
	void setpgtype(SHORT_T _pgtype) { pgtype = (_pgtype); }
	SHORT_T getpgtype() { return (pgtype); }

	void setm(SHORT_T _m) { m = (_m); }
	SHORT_T getm() { return (m); }

	void setlowkeyptr(FILEOFF_T _lowkeyptr) { lowkeyptr = (_lowkeyptr); }
	FILEOFF_T getlowkeyptr() { return (lowkeyptr); }

	void setnextpage(FILEOFF_T _nextpage) { nextpage = (_nextpage); }
	FILEOFF_T getnextpage() { return (nextpage); }

	void setpagelsn(FILEOFF_T _pagelsn) { pagelsn = (_pagelsn); }
	FILEOFF_T getpagelsn() { return (pagelsn); }
};

struct ehash_hdr
{
private:
	FILEOFF_T nextpage;
	FILEOFF_T pagelsn;
	SHORT_T ld;
	SHORT_T m;

	SHORT_T M;
	SHORT_T idxsize;
	int pagesize;
	int empty;

public:
	ehash_hdr() {}

	ehash_hdr(FILEOFF_T _nextpage, FILEOFF_T _pagelsn, SHORT_T _ld, SHORT_T _m, SHORT_T _M, SHORT_T idx_sz);

	void inithdr(FILEOFF_T _nextpage, FILEOFF_T _pagelsn, SHORT_T _ld, SHORT_T _m, SHORT_T _M, SHORT_T idx_sz);

	void reset();

	void setnextpage(FILEOFF_T _nextpage) { nextpage = (_nextpage); }
	FILEOFF_T getnextpage() { return (nextpage); }

	void setpagelsn(FILEOFF_T _pagelsn) { pagelsn = (_pagelsn); }
	FILEOFF_T getpagelsn() { return (pagelsn); }

	void setld(SHORT_T _ld) { ld = (_ld); }
	SHORT_T getld() { return (ld); }

	void setm(SHORT_T _m) { m = (_m); }
	SHORT_T getm() { return (m); }

	void setM(SHORT_T _M) { M = (_M); }
	SHORT_T getM() { return (M); }
};

const int BTREE_HDR_SZ = sizeof(btree_hdr);
const int EHASH_HDR_SZ = sizeof(ehash_hdr);

const int PAG_HDR = (BTREE_HDR_SZ >= EHASH_HDR_SZ)?BTREE_HDR_SZ:EHASH_HDR_SZ;

struct idxrecinfo
{
private:
	int keylen;
	int datlen;
	FILEOFF_T datoff;
public:
	idxrecinfo() {}
	idxrecinfo(int _keylen, int _datlen, FILEOFF_T _datoff)
	{
		keylen = (_keylen);
		datlen = (_datlen);
		datoff = (_datoff);
	}
	void init(int _keylen, int _datlen, FILEOFF_T _datoff)
	{
		keylen = (_keylen);
		datlen = (_datlen);
		datoff = (_datoff);
	}
	void setkeylen(int _keylen) { keylen = (_keylen); }
	int getkeylen() { return (keylen); }

	void setdatlen(int _datlen) { datlen = (_datlen); }
	int getdatlen() { return (datlen); }

	void setdatoff(FILEOFF_T _datoff) { datoff = (_datoff); }
	FILEOFF_T getdatoff() { return (datoff); }
};

const int idxrecinfolen = sizeof(idxrecinfo);

struct dptxrec
{
	char* bufrec;
	dptxrec* nextaddr;
	dptxrec* prevaddr;
	pthread_mutex_t hdrlock;
	void initlock()
	{
		Pthread_mutex_init_private(&hdrlock);
	}
	void lock() { Pthread_mutex_lock(&hdrlock); }
	void unlock() { Pthread_mutex_unlock(&hdrlock); }
};

const int DPTXRECHDR	=	sizeof(dptxrec);

#endif /* PAGEHDR_H_ */
