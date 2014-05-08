/*
 * connection.h
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

#ifndef CONNECTION_H_
#define CONNECTION_H_

#include "iqindex.h"
#include "iqbpool.h"
#include "iqlog.h"
#include "transaction_manager.h"
#include "hash_tbl.h"

class transaction_manager;
class connection;
class table_impl;

struct connection_item
{
	connection *conn;
	connection_item()
	{
		conn = NULL;
	}
	connection_item(connection *_conn)
	{
		conn = _conn;
	}
};

struct table_item
{
	table_impl *tbl;
	SHORT_T fid;
	table_item()
	{
		tbl = NULL;
		fid = 0;
	}
	table_item(table_impl *_tbl, SHORT_T _fid)
	{
		tbl = _tbl;
		fid = _fid;
	}
};

class connection
{
public:

	connection(char *idxname, INT_T _connid, hash_tbl<connection_item> *_tblconn, int indexfd, int datafd, int dirctfd, iqbpool *bptr, iqlog *flg, transaction_manager *tmgr, SHORT_T openflg, table_env *tenv, SHORT_T _fid);

	int init(bool isfirst);

	char* get(char *key, void *txn_handle);

	FILEOFF_T put(char *key, char *val, insert_options flag, void *txn_handle);

	FILEOFF_T del(char *key, void *txn_handle);

	resultset* scan(char *skey, char *ekey, void *txn_handle, scan_filter *sf = NULL);

	FDT* get(FDT *key, void *txn_handle);

	FILEOFF_T put(FDT *key, FDT *val, insert_options flag, void *txn_handle);

	FILEOFF_T del(FDT *key, void *txn_handle);

	resultset* scan(FDT *skey, FDT *ekey, void *txn_handle, scan_filter *sf = NULL);

	char* get(char *key);

	FILEOFF_T put(char *key, char *val, insert_options flag);

	FILEOFF_T del(char *key);

	resultset* scan(char *skey, char *ekey, scan_filter *sf = NULL);

	FILEOFF_T count(char *skey, char *key, scan_filter *sf = NULL);

	FDT* get(FDT *key);

	FILEOFF_T put(FDT *key, FDT *val, insert_options flag);

	FILEOFF_T del(FDT *key);

	resultset* scan(FDT *skey, FDT *ekey, scan_filter *sf = NULL);

	FILEOFF_T count(FDT *skey, FDT *key, scan_filter *sf = NULL);

	FILEOFF_T count();

	void set_autocommit(bool flag);

	SHORT_T getdbtype();

	SHORT_T getidxtype();

	SHORT_T getidxsize();

	iqindex* getidx();

	ULONG_T get_table_hash_id();

	INT_T getconnid();

	int closeconnection();

	virtual ~connection();

private:

	char* _get(char *key);

	FILEOFF_T _put(char *key, char *val, insert_options flag);

	FILEOFF_T _del(char *key);

	resultset* _scan(char *skey, char *ekey, scan_filter *sf);

	FDT* _get(FDT *key);

	FILEOFF_T _put(FDT *key, FDT *val, insert_options flag);

	FILEOFF_T _del(FDT *key);

	resultset* _scan(FDT *skey, FDT *ekey, scan_filter *sf);

	bool _check_for_nullable(void *txn_handle);

	bool _check_for_nullable(char *kv);

	bool _check_for_nullable(FDT* kv);

	bool _check_for_nullable(char *k, char *v);

	bool _check_for_nullable(FDT *k, FDT *v);

	void _verify_scan_filter(scan_filter *sf);

	SHORT_T openflag;

	SHORT_T idxsz;

	SHORT_T fid;

	bool auto_commit;

	int idxfd;

	int datfd;

	int dirfd;

	UINT_T table_hash_id;

	INT_T connid;

	hash_tbl<connection_item> *tblconn;

	char *indexname;

	iqindex *idx;

	iqbpool *bp;

	iqlog *fg;

	transaction_manager *tm;

	table_env *tbl_env;

	pthread_mutex_t connlock;
};

#endif /* CONNECTION_H_ */
