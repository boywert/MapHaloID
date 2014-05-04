/*
 * database.h
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


#ifndef DATABASE_H_
#define DATABASE_H_

#include "table.h"
class table;

class database
{
public:
	database(char *databasename, char *configpath = NULL, db_transaction_type transaction_type = DB_TRANSACTION_NONE, char *dbpath = NULL);

	table* gettable(char *name, bangdb_open_type openflag = OPENCREATE, table_env *tenv=NULL);

	void* begin_transaction();

	FILEOFF_T commit_transaction(void **txn_handle);

	void abort_transaction(void **txn_handle);

	void free_transaction(void *txn);

	int get_num_tables();

	int dumpdata();

	int closetable(char *rname, bangdb_close_type tblclose = DEFAULT);

	int closetable(table *tbl, bangdb_close_type tblclose = DEFAULT);

	void closedatabase(bangdb_close_type dbclose = DEFAULT);

	void cleanup();

	char *getdbdir();

	int get_table_name_list(char ***list);

	void free_table_name_list(char **list, int nt);

	int get_tran_type();

	char *get_dbmetadata(int *fd);

	table_env *get_table_meta(char *tablename);

	char* getdbname() { return dbname; }

private:

	void _initdb();

	int _createdbmeta();

	int _verifymeta(int fd);

	int _writemeta(int fd);

	void _cleanup_table(char *tblname);

	table_impl* _tableexists(char *tbl);

	int _create_buffreelist();

	bool _check_for_nullable(void *txn_handle);

	bool _is_enough_mem(table_env *tenv, bool isfirst);

	table_impl *_get_table_impl (UINT_T table_id);

	int _open_shared_log_tables();

	SHORT_T _increase_tbl_id();

	int _close_log();

	int dbmetafd;

	int dbsockfd;

	bool isNETWORK_INMEM_PERSIST;

	SHORT_T db_tran_type;

	char *dbname;

	char *username;

	char *dbdir;

	char *dbmetafile;

	table_env *gtable_env;

	hash_tbl<table_item> *dbtbls;

	iqfreelist *free_list;

	iqlog *log;

	transaction_manager *tm;

	pthread_mutex_t dbmutex;

	friend class table_impl;
};

#endif /* DATABASE_H_ */
