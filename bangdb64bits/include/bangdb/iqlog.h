/*
 * iqlog.h
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


#ifndef IQLOG_H_
#define IQLOG_H_

#include "logrecord.h"
#include "iqindex.h"
#include "iqbpool.h"
class iqbpool;

class iqlog {
public:

	virtual void set_table_params(SHORT_T fid, iqbpool *_bp, table_env *_tenv) = 0;

	virtual void setidx(iqindex *_idx, SHORT_T fid = 0) = 0;

	virtual void unset_table_params(SHORT_T fid) = 0;

	virtual int initflog() = 0;

	virtual FILEOFF_T gettxnid() = 0;

	virtual logrecord* getlogrec(SHORT_T logtype, FILEOFF_T pLSN, FILEOFF_T tid, SHORT_T optype, SHORT_T filetype, SHORT_T fid) = 0;

	virtual FILEOFF_T writelogrec(logrecord *logrec) = 0;

	virtual FILEOFF_T writelogrec2(logrecord *logrec) = 0;

	virtual logrecord* readlogrec(FILEOFF_T LSN) = 0;

	virtual void freelogrec(logrecord *logrec) = 0;

	virtual FILEOFF_T flush(FILEOFF_T uptoLSN = 0) = 0;

	virtual int flush_master() = 0;

	virtual void *getmasterlog() = 0;

	virtual int updatedbfile(bool shouldanalyze) = 0;

	virtual void setbufflushedlsn(FILEOFF_T bflsn) = 0;

	virtual void removefromdbtbl(SHORT_T ftype, SHORT_T fid, BLOCKNUM_T pageid) = 0;

	virtual void removefromdbtbl(SHORT_T ftype, SHORT_T fid, BLOCKNUM_T frompageid, BLOCKNUM_T endpageid) = 0;

	virtual int undo(FILEOFF_T txnid = -1) = 0;

	virtual int closeflog() = 0;

	virtual void kill_log_workers() = 0;

	virtual void master_sanity() = 0;

	virtual void lockmaster() = 0;

	virtual void releasemaster() = 0;

	virtual int undotran(FILEOFF_T txnid) = 0;

	virtual int inithousekeep() = 0;

	virtual void setundo(bool _undoflag) = 0;

	virtual FILEOFF_T getnextlsn() = 0;

	virtual ~iqlog() {}
};
#endif /* IQLOG_H_ */
