/*
 * fmap.h
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


#ifndef FMAP_H_
#define FMAP_H_

#include "FDT.h"

struct FDTnode
{
	FDT *key;
	FDT *value;
	FDTnode *next;
	FDTnode *prev;
	FDTnode(FDT *k, FDT *v);
	FDTnode();

	void clear();
};

class fmap
{
public:
	fmap(bool flag);

	void begin();

	bool isempty();

	bool hasnext();

	bool more_data_to_come();

	void set_more_data_to_come(bool flag);

	FDT *last_evaluated_key();

	FDT* getkey();

	FDT* getval();

	FDT* getval(FDT *key);

	FDTnode *getvalnode(FDT *key);

	void movenext();

	void put(FDT *key, FDT *val);

	void put(char *key, char *val);

	void put(void *key, int klen, void *val, int vlen);

	void insert(FDT *key, FDT *val);

	void remove(FDTnode *fnode);

	void remove(FDT *k);

	int size();

	void updateVal(FDTnode* fn, FDT *v);

	int dataSize();

	void clear();

private:

	FDT *_copy_data(void *k, int len, bool copyflag);
	FDTnode *_get_node(FDTnode *head, int idx);
	FDTnode *_mid_node(FDTnode *p1, int low, int high, int *mid);
	FDTnode *_binSearch(FDTnode *first, int ncount, FDT *k, int match, int *exactmatch = NULL);
	void _makeNodeList(FDTnode *head, FDT *k, FDT *v);

	bool sortflag;
	bool _more_data_to_come;
	int numelems;
	int data_size;
	FDTnode *fdthead;
	FDTnode *hold_fdthead;
};

#endif /* FMAP_H_ */
