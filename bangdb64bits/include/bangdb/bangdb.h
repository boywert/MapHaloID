/*
 * bangdb.h
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


#ifndef BANGDB_H_
#define BANGDB_H_

#include "bheader.h"
#include "pagehdr.h"
#include "logheader.h"
#include "tableenv.h"

#define MINLINE					128
#define SHORTLINE 				512
#define MAXLINE 				4096
#define	BUFFSIZE 				8192
#define MAXN 					16384
#define MAXTRY					20
#define BANGDB_DIV_FORMAT_KB 	1024

#define SEP 					':'
#define SLASH 					'/'
#define SPACE 					0
#define BLANK 					' '
#define PTR_SZ 					12
#define INT_SZ 					4
#define FREE_OFF 				0
#define DIRREC_SZ 				8
#define BTREE_PAGE 				1
#define EHASH_PAGE 				0
#define NULL_PAGE 				-9
#define INFINITY_KEY 			"$#&*!%^@"

#define GDLEN_SZ 				2
#define DIRLEN_SZ 				PTR_SZ
#define IDXLEN_SZ 				INT_SZ
#define GD_OFF 					PTR_SZ
#define ROOT_OFF 				(INT_SZ+INT_SZ+PTR_SZ)

#define DBSTATUSLEN				 1
#define LSNLEN					14
#define TXNIDLEN				13
#define PAGEIDLEN				 9
#define LOGRECLEN				 9
#define FIDLEN					 3

#define LOGMAXFULL				80
#define OFFSETLEN				PTR_SZ
#define DATSZLEN				 9
#define LOGXTNSZ				 8

#define MIN_CHKPT_TXN			500

#define DPRECSZ					(1+FIDLEN+PAGEIDLEN+LSNLEN+5)

#define TXRECSZ					(TXNIDLEN+LSNLEN+1+4)
#define DPTXRECSZ				DPRECSZ
#define DPTXKEYLEN				(1+FIDLEN+PAGEIDLEN)
#define RECHDRSZ				(LSNLEN+LOGRECLEN+LSNLEN+TXNIDLEN+1+1+FIDLEN+PAGEIDLEN)
#define INRPRTSZ				(DATSZLEN+OFFSETLEN+DATSZLEN)
#define LOGFXDSZ				(RECHDRSZ+INRPRTSZ)

#define MAX_KEYCMP_FUNC 2

const int NDPRECSZ = DPRECSZ;
const int NTXRECSZ = TXRECSZ;
const int NDPTXRECSZ = DPTXRECSZ;
const int NDPTXKEYLEN = DPTXKEYLEN;
const int NRECHDRSZ = RECHDRSZ;
const int NINRPRTSZ = INRPRTSZ;
const int NLOGFXDSZ = LOGFXDSZ;

//types of db
enum bangdb_persist_type
{
	INMEM_ONLY,			//only RAM based, cache enabled (no overflow to disk, ideally overflow to other RAM)
	INMEM_PERSIST,		//disked backed, cache enabled (over flow to disk)
	PERSIST_ONLY,		//cache disabled, direct file IO
};

//types of index
enum bangdb_index_type
{
	HASH,
	EXTHASH,
	BTREE,
	HEAP
};

//log type
enum bangdb_log_type
{
	SHARED_LOG,
	PRIVATE_LOG,
};

//how should we access db, various ways
enum bangdb_open_type
{
	OPENCREATE,
	TRUNCOPEN,
	JUSTOPEN
};

//the various state of the db
enum bangdb_state
{
	DBCLOSE,
	DBOPEN
};

//how should db be closed
enum bangdb_close_type
{
	DEFAULT,
	CONSERVATIVE,
	OPTIMISTIC,
	CLEANCLOSE,
	SIMPLECLOSE,
};

//the insert options
enum insert_options
{
	INSERT_UNIQUE,		//if non-existing then insert else return
	UPDATE_EXISTING,	//if existing then update else return
	INSERT_UPDATE,		//insert if non-existing else update
	DELETE_EXISTING,	//delete if existing
};

enum db_transaction_type
{
	DB_TRANSACTION_NONE,
	DB_OPTIMISTIC_TRANSACTION,
	DB_PESSIMISTIC_TRANSACTION,
};

enum db_transaction_phase
{
	TRAN_READ_PHASE,
	TRAN_VALIDATE_PHASE,
	TRAN_COMMIT_PHASE,
	TRAN_ABORT_PHASE,
};

enum table_size_hint
{
	TINY_TABLE_SIZE,
	SMALL_TABLE_SIZE,
	NORMAL_TABLE_SIZE,
	BIG_TABLE_SIZE,
};

enum scan_limit_by
{
	LIMIT_RESULT_SIZE,
	LIMIT_RESULT_ROW,
};

enum scan_operator
{
	GT,
	GTE,
	LT,
	LTE,
};

struct db_meta
{
	char db_name[MINLINE];
	ULONG_T db_pwd;
	SHORT_T keycmpid;
	SHORT_T ntableid;	//ever increasing number, MAX TABLE = 64K, starts from 1
	int page_size;
};

struct table_meta
{
	char tbl_name[MINLINE];
	SHORT_T log_st;
	SHORT_T log_sz;	//in MB
	SHORT_T log_tp;
	SHORT_T idx_tp;
	SHORT_T key_sz;
	SHORT_T db_tp;
	SHORT_T db_close;
	SHORT_T fid;
	int nusers;
};

struct master_log_info
{
	FILEOFF_T nextlsn;
	FILEOFF_T nexttxn;
	FILEOFF_T logflushedlsn;
	FILEOFF_T bufflushedlsn;
};

const int MASTER_LOG_INFO_SZ = sizeof(master_log_info);

#define METAEXTN				".met"
#define IDXEXTN					".idx"
#define DATEXTN					".dat"
#define DIREXTN					".dir"
#define LOGXTN					".log"

#define BANGDB_CONFIG			"bangdb.config"

#ifdef BPOOL_DEBUG_MODE
#undef BPOOL_DEBUG_MODE
#endif

#define TINY_STACK_SIZE 32

template <class T>
class Stack {
public:
   Stack();
   void push(T i);
   T pop();
private:
   int top;
   T st[TINY_STACK_SIZE];
};

//very simple stack, not considering overflow etc... mainly because it's not required, also needed the fastest one with out any extra features etc...
template <class T>
Stack<T>::Stack()
{
	top = -1;
}

template <class T>
void Stack<T>::push(T i)
{
	if(top == (TINY_STACK_SIZE-1))
		return;
	st[++top] = i;
}

template <class T>
T Stack<T>::pop()
{
	if(top < 0)
		return -1;
	return st[top--];
}

namespace USERCONFIG
{
	extern char SERVER_DIR[SHORTLINE];

	extern char BANGDB_DATABASE_NAME[MINLINE];

	extern char BANGDB_TABLE_NAME[MINLINE];

	extern int BANGDB_PERSIST_TYPE;

	extern int BANGDB_INDEX_TYPE;

	extern int BANGDB_LOG;

	extern int BANGDB_AUTOCOMMIT;

	extern int BANGDB_TRANSACTION_CACHE_SIZE;

	extern int PAGE_SIZE;

	extern int DAT_SIZE;

	extern int KEY_SIZE;

	extern int MAX_RESULTSET_SIZE;

	extern char BANGDB_GROUP[64];

	extern int MAXTABLE;

	extern int MAXCONN;

	extern int LISTENQ;

	extern int MAX_THREADS;

	extern int MAX_CLIENT_EVENTS;

	extern int SERVER_TYPE;

	extern int ENABLE_REPLICATION;

	extern char SERVER_ID[128];

	extern int SERV_PORT;

	extern char MASTER_SERVER_ID[128];

	extern int MASTER_SERV_PORT;

	extern int MAX_SLAVES;

	extern int PING_FREQ;

	extern int PING_THRESHOLD;

	extern int CLIENT_TIME_OUT;

	extern int SERVER_STAGE_OPTION;

	extern int SERVER_OPS_WORKERS;

	extern FILEOFF_T BUFF_POOL_SIZE_HINT;

	extern FILEOFF_T LOG_BUF_SIZE;

	extern int MASTER_LOG_BUF_SIZE;

	extern FILEOFF_T OPS_REC_BUF_SIZE;

	extern int BANGDB_SYNC;

	extern int LOG_FLUSH_FREQ;

	extern int CHKPNT_ENABLED;

	extern int CHKPNT_FREQ;

	extern int LOG_SPLIT_CHECK_FREQ;

	extern int BUF_FLUSH_RECLAIM_FREQ;

	extern FILEOFF_T GROW_BUFF_SIZE;

	extern int SCATTER_GATHER_MAX;

	extern int MIN_DIRTY_SCAN;

	extern int MIN_UPDATED_SCAN;

	extern int IDX_FLUSH_CONSTRAINT;

	extern int DAT_FLUSH_CONSTRAINT;

	extern int IDX_RECLAIM_CONSTRAINT;

	extern int DAT_RECLAIM_CONSTRAINT;

	extern int PAGE_WRITE_FACTOR;

	extern int IDX_DAT_NORMALIZE;

	extern int PREFETCH_BUF_SIZE;

	extern int PREFETCH_SCAN_WINDOW_NUM;

	extern int PREFETCH_EXTENT_NUM;

	extern int KEY_COMP_FUNCTION_ID;

	extern char SERV_PORT_STR[8];

	extern char MASTER_SERV_PORT_STR[8];

	extern int BANGDB_GROUP_ID;

	extern int HASH_TABLE_SIZE_IDX;

	extern int HASH_TABLE_SIZE_DAT;

	extern int HASH_TABLE_SIZE_DIR;

	extern int NLOOPFOR;

	extern int DIR_OFF;

	extern int NUMLOGREC;

	extern int NUMCONTHREAD;

	extern int DAT_BUF;

	extern FILEOFF_T MASTERLOGSHMSZ;

	extern FILEOFF_T RECORDSHMEM;

	extern FILEOFF_T RECORDSZ;

	extern int (*keycmp)(char*, DATLEN_T, char*, DATLEN_T);
}
using namespace USERCONFIG;

table_env *readuserconfig(char* path);
table_env *set_db_vars();
void set_table_buf_sizes(FILEOFF_T *buff_pool_size_hint, int *hash_table_size_dir, int *hash_table_size_idx, int *hash_table_size_dat);
FILEOFF_T _compute_buf_hash_table_size(int bufsize);
FILEOFF_T _compute_buf_size_from_table(int tbsz);
int keycmp_lexGraph(char *key, DATLEN_T klen, char *cmpto, DATLEN_T cmptolen);
int keycmp_quasiLexGraph(char *key, DATLEN_T klen, char *cmpto, DATLEN_T cmptolen);
void init_keycmp();

#endif /* BANGDB_H_ */
