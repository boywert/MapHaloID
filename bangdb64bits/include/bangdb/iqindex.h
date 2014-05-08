/*
 * iqindex.h
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


#ifndef IQINDEX_H_
#define IQINDEX_H_


#define CONCURRENT_OPS

#include "resultset.h"
#include "FDT.h"

struct scan_filter
{
	scan_operator skey_op;	//default GTE
	scan_operator ekey_op;	//default LTE
	scan_limit_by limitby;	//default LIMIT_RESULT_SIZE
	int limit;				//default 2MB (MAX_RESULTSET_SIZE) for LIMIT_RESULT_SETSIZE
	scan_filter()
	{
		skey_op = GTE;
		ekey_op = LTE;
		limitby = LIMIT_RESULT_SIZE;
		limit = MAX_RESULTSET_SIZE;
	}
};

class iqindex
{
public:

	virtual FILEOFF_T initidx(SHORT_T flag) = 0;

	virtual char* fetch(char *key) = 0;

	virtual FILEOFF_T putdata(char *key, char *value, SHORT_T flag) = 0;//flag = 0 for INSERT and 1 for UPDATE

	virtual FILEOFF_T deletedata(char *key) = 0;

	virtual resultset* scan(char *skey, char *ekey, scan_filter *sf = NULL) = 0;

	virtual FILEOFF_T count(char *skey, char *eky, scan_filter *sf = NULL) = 0;

	virtual FDT* fetch(FDT *key) = 0;

	virtual FILEOFF_T putdata(FDT *key, FDT *value, SHORT_T flag) = 0;//flag = 0 for INSERT and 1 for UPDATE

	virtual FILEOFF_T deletedata(FDT *key) = 0;

	virtual resultset* scan(FDT *skey, FDT *ekey, scan_filter *sf = NULL) = 0;

	virtual FILEOFF_T count(FDT *skey, FDT *ekey, scan_filter *sf = NULL) = 0;

	virtual void rewind() = 0;

	virtual void printstats() = 0;

	virtual void clean() = 0;

	virtual FILEOFF_T uninsert(char *key, DATLEN_T keylen) = 0;

	virtual FILEOFF_T unupdate(char *key, DATLEN_T keylen, FILEOFF_T offt, DATLEN_T datlen) = 0;

	virtual FILEOFF_T undelete(char *key, DATLEN_T keylen, FILEOFF_T datofft, DATLEN_T datlen) = 0;

	virtual ~iqindex() { }
};

#endif /* IQINDEX_H_ */
