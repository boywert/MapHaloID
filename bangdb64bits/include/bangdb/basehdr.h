/*
 * 	basehdr.h
 *
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
 *
 */
#ifndef BASEHDR_H_
#define BASEHDR_H_
//#define _MAC_OS_COMPILE_

#ifndef _PLATFORM_BIT_64_
#define _PLATFORM_BIT_64_
#endif

#ifndef _BANGDB_SERVER_HDR_
//#define _BANGDB_SERVER_HDR_
#endif


#ifndef _BANGDB_ALL_TEST_SERVER_
//#define _BANGDB_ALL_TEST_SERVER_
#endif

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/termios.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/mman.h>
#ifndef TIOCGWINSZ
#include <sys/ioctl.h>
#endif
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>
#include <signal.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <syslog.h>
#include <stdarg.h>
#include <pthread.h>
#include <poll.h>
#include <sys/poll.h>
#include <grp.h>
#include "atomic.h"

#ifndef _MAC_OS_COMPILE_
#include <sys/sendfile.h>
#include <stropts.h>
#include <sys/epoll.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <libkern/OSAtomic.h>
typedef long int loff_t;
#define MAP_ANONYMOUS MAP_ANON
typedef OSSpinLock pthread_spinlock_t;
#endif

#if defined(_WIN32)
#include <windows.h>
#include <psapi.h>

#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
#include <sys/resource.h>

#if defined(__APPLE__) && defined(__MACH__)
#include <mach/mach.h>

#elif (defined(_AIX) || defined(__TOS__AIX__)) || (defined(__sun__) || defined(__sun) || defined(sun) && (defined(__SVR4) || defined(__svr4__)))
#include <fcntl.h>
#include <procfs.h>

#elif defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
#include <sys/sysinfo.h>
#endif

#else
#error "Cannot define getPeakRSS( ) or getCurrentRSS( ) for an unknown OS."
#endif

#ifdef _PLATFORM_BIT_64_
typedef u_int64_t 	ULONG_T;
typedef int64_t		LONG_T;
#else
typedef unsigned long long ULONG_T;
typedef long long LONG_T;
#endif

typedef u_int32_t	UINT_T;
typedef int32_t		INT_T;
typedef int16_t		SHORT_T;

typedef off_t		FILEOFF_T;
typedef ULONG_T		LCOUNT_T;
typedef ULONG_T		BUFFER_T;
typedef UINT_T		DATLEN_T;
typedef INT_T		BLOCKNUM_T;
typedef	UINT_T		COUNT_T;

#define FILE_MODE   		(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

#define DIR_MODE    		(FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)

#define RWRWRW 				(S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)
#define LOCKMODE 			(S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP)

#define min(a,b)     		((a) < (b) ? (a) : (b))
#define max(a,b)     		((a) > (b) ? (a) : (b))

typedef void   Sigfunc(int);

#if defined(SIG_IGN) && !defined(SIG_ERR)
#define SIG_ERR ((Sigfunc *)-1)
#endif

void setnonblocking(int fd);

void setblocking(int fd);

void     clr_fl(int fd, int flags);

void     set_fl(int fd, int flags);

void     pr_exit(int status);

void     pr_mask(const char *str);

Sigfunc *signal_intr(int signo, Sigfunc *func);

void     sleep_us(unsigned int);

ssize_t  readn(int, void *, size_t);

ssize_t readn_timeout(int fd, void *vptr, size_t n, int to_sec);

ssize_t  writen(int, const void *, size_t);

ssize_t writevn(int fd, struct iovec *iov, int iovcnt, int towrite);

ssize_t readmessage(int fd, char *buf, size_t minbyte, size_t maxbyte);

u_int64_t htonll(u_int64_t v);

u_int64_t ntohll(u_int64_t v);

void 	 pr_cpu_time(void);

int Epoll_ctl(int _epfd, int _op, int _fd, int _edit_type);

int     lock_reg(int fd, int cmd, int type, off_t, int, off_t);

#define read_lock(fd, offset, whence, len) \
            lock_reg((fd), F_SETLK, F_RDLCK, (offset), (whence), (len))
#define readw_lock(fd, offset, whence, len) \
            lock_reg((fd), F_SETLKW, F_RDLCK, (offset), (whence), (len))
#define write_lock(fd, offset, whence, len) \
            lock_reg((fd), F_SETLK, F_WRLCK, (offset), (whence), (len))
#define writew_lock(fd, offset, whence, len) \
            lock_reg((fd), F_SETLKW, F_WRLCK, (offset), (whence), (len))
#define un_lock(fd, offset, whence, len) \
            lock_reg((fd), F_SETLK, F_UNLCK, (offset), (whence), (len))

pid_t   lock_test(int, int, off_t, int, off_t);

#define is_read_lockable(fd, offset, whence, len) \
            (lock_test((fd), F_RDLCK, (offset), (whence), (len)) == 0)
#define is_write_lockable(fd, offset, whence, len) \
            (lock_test((fd), F_WRLCK, (offset), (whence), (len)) == 0)

void    err_dump(const char *, ...);

void    err_ret(const char *, ...);

void    err_sys(const char *, ...);

void    err_msg(const char *, ...);

void    err_quit(const char *, ...);

void    err_exit(int, const char *, ...);

void    log_open(const char *, int, int);

void    log_ret(const char *, ...);

void    log_sys(const char *, ...);

void    log_msg(const char *, ...);

void    log_quit(const char *, ...);

void    TELL_WAIT(void);
void    TELL_PARENT(pid_t);
void    TELL_CHILD(pid_t);
void    WAIT_PARENT(void);
void    WAIT_CHILD(void);

extern int log_to_stderr;

char* strappend(char *str1, char *str2);

void printflstfg(int filedes);

void pr_times(clock_t real, struct tms *tmsstart, struct tms *tmsend);

void print_local_time();

LONG_T get_current_time_us();

LONG_T get_timestamp();

int isastream(int fd);

Sigfunc *signal(int signo, Sigfunc *func);

int	 daemon_init(const char *pname, int facility);

void daemon_inetd(const char *, int);

struct addrinfo *host_serv(const char *, const char *, int, int);

int tcp_connect(const char *host, const char *serv);

int tcp_connect_timeout(const char *host, const char *serv, int to_sec);

int set_socket_r_timeo(int sockfd, int to_sec);

int set_socket_w_timeo(int sockfd, int to_sec);

int tcp_listen(const char *host, const char *serv, socklen_t *addrlenp);

int Setsockoptabort(int sockfd);

int isdrunning(const char *filepath);

int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);

char * Sock_ntop_host(const struct sockaddr *sa, socklen_t salen, char **portnum);

char * Sock_ntop_host(const struct sockaddr *sa, socklen_t salen, int *portnum);

int Sock_ntop_host(const struct sockaddr *sa, socklen_t salen, char *ip, int iplen, char *portnum, int portlen);

int Sock_ntop_host(const struct sockaddr *sa, socklen_t salen, char *ip, int iplen, int *portnum);

int get_sockaddr(int family, char *ip, char *port, sockaddr_in *sa);

int get_sockaddr(int family, char *ip, int port, sockaddr_in *sa);

int Setsockopt(int fd, int level, int optname, const void *optval, socklen_t optlen);

int creatw(const char *pathname, mode_t mode);

int creatrw(const char *pathname, mode_t mode);

off_t lseek_cur(int fd);

void Pthread_mutex_init(pthread_mutex_t *mptr, const pthread_mutexattr_t *attr);

void Pthread_mutex_init_shared(pthread_mutex_t *mptr);

void Pthread_mutex_init_private(pthread_mutex_t *mptr);

void Pthread_cond_init_shared(pthread_cond_t *cond);

void Pthread_cond_init_private(pthread_cond_t *cond);

void Pthread_attr_init(pthread_attr_t *attr);

void Pthread_attr_destroy(pthread_attr_t *attr);

void Pthread_detach (pthread_t th);

void Pthread_cancel(pthread_t th);

void Pthread_attr_setdetachstate (pthread_attr_t *attr, int detachstate);

void Pthread_cond_init(pthread_cond_t *cptr, pthread_condattr_t *attr);

void Pthread_mutex_destroy(pthread_mutex_t *mptr);

void Pthread_cond_destroy(pthread_cond_t *cptr);

void Pthread_mutex_lock(pthread_mutex_t *mptr);

int Pthread_mutex_trylock(pthread_mutex_t *mptr);

void Pthread_mutex_unlock(pthread_mutex_t *mptr);

void Pthread_cond_wait(pthread_cond_t *cptr, pthread_mutex_t *mptr);

void Pthread_cond_signal(pthread_cond_t *cptr);

void Pthread_cond_broadcast(pthread_cond_t *cptr);

void Pthread_mutexattr_init(pthread_mutexattr_t *mattr);

void Pthread_condattr_init(pthread_condattr_t *cattr);

void Pthread_mutexattr_destroy(pthread_mutexattr_t *mattr);

void Pthread_condattr_destroy(pthread_condattr_t *cattr);

void Pthread_mutexattr_setpshared(pthread_mutexattr_t *mattr, int value);

void Pthread_condattr_setpshared(pthread_condattr_t *cattr, int value);

void Pthread_create(pthread_t *tid, const pthread_attr_t *attr, void *(*func)(void*), void *arg);

void Pthread_join(pthread_t tid, void **status);

void Pthread_once(pthread_once_t *onceptr, void (*init)(void));

void Pthread_key_create(pthread_key_t *keyptr, void (*destructor)(void *value));

void Pthread_setspecific(pthread_key_t key, const void *value);

void Pthread_rwlock_init(pthread_rwlock_t *rwptr, const pthread_rwlockattr_t *rwattr);

void Pthread_rwlock_init_shared(pthread_rwlock_t *rwptr);

void Pthread_rwlock_init_private(pthread_rwlock_t *rwptr);

void Pthread_rwlockattr_setpshared(pthread_rwlockattr_t *mattr, int value);

void Pthread_rwlockattr_init(pthread_rwlockattr_t *rwattr);

void Pthread_rwlock_destroy(pthread_rwlock_t *rwptr);

void Pthread_rwlockattr_destroy(pthread_rwlockattr_t *rwattr);

void Pthread_rwlock_rdlock(pthread_rwlock_t *rwptr);

void Pthread_rwlock_wrlock(pthread_rwlock_t *rwptr);

int Pthread_rwlock_tryrdlock(pthread_rwlock_t *rwptr);

int Pthread_rwlock_trywrlock(pthread_rwlock_t *rwptr);

void Pthread_rwlock_unlock(pthread_rwlock_t *rwptr);

void Pthread_spin_init(pthread_spinlock_t *lock, int pshared);

void Pthread_spin_destroy(pthread_spinlock_t *lock);

void Pthread_spin_lock(pthread_spinlock_t *lock);

void Pthread_spin_unlock(pthread_spinlock_t *lock);

void Fclose(FILE *fp);

FILE *Fdopen(int fd, const char *type);

char * Fgets(char *ptr, int n, FILE *stream);

FILE * Fopen(const char *filename, const char *mode);

void Fputs(const char *ptr, FILE *stream);

ssize_t Sendfile(int out_fd, int in_fd, off_t offset, size_t count);

size_t Splice(int fdin, loff_t offtin, int fdout, loff_t offtout, size_t len);

char* Strncpy(char *dest, char *src);

char* Strncpy(char *dest, char *src, int srclen);

char* Strncpy(char* src);

char* Strncpy(char* src, int srclen);

int Strncpy(char* dest, int destlen, char* src);

char* Strncat(char *dest, char *src);

char *get_full_path(char *base, char *name, bool filedir);

char** get_index_file_names(char *tabledir, char *tablename);

char* Reverse(char s[], int n);

char* Itoa(int i);

int Itoa(int i, char *str, int len);

char* Ltoa(LONG_T i);

int isnumeric (const char * s);

char* Strchr(char* str, char c, size_t len);

void listdir(char *dname);

int num_dirs(const char* path);

int num_list_dirs(const char* path, char **list, int n);

bool direxists(char *path);

FILEOFF_T size_of_file(int fd, char *fname);

int num_files_dir(char *dbname, char *extname);

void recurlistdir(char *dname);

void removefile(char *parent, DIR *dp);

void rrmdir(char *dname);

int readlinesfromfile(int fd, char *buf[], int bufdim);

int fileexists(char *fname);

int _copy_tofile(char *filename, char *buf, off_t offset, int len);

int Mkdir(const char *path, mode_t mode);

int Chown(const char *path, uid_t owner, gid_t group);

int Chmod(const char *path, mode_t mode);

int Chdir(const char *path);

int Fstat(int fd, struct stat *buf);

int Fchown(int fd, uid_t owner, gid_t group);

int Rename(const char *oldpath, const char *newpath);

int modulo(int a, int b, int c);

LONG_T mulmod(LONG_T a, LONG_T b, LONG_T c);

bool Miller(LONG_T p, int iteration);

int mmap_private(FILEOFF_T bufsize, char **bufptr);

UINT_T hash_string_32(char* str, int len);

ULONG_T hash_string_64(char* str, int len);

ULONG_T hash_long(ULONG_T key);

UINT_T hash_int(UINT_T blocknum);

size_t getPeakRSS();

void getRamStat(unsigned long *totalRam, unsigned long *freeRam);

size_t getCurrentRSS();

void getTotalSystemMemory(unsigned long *totalmem, unsigned long *freemem, unsigned long *freevirtmem);

#endif /* BASEHDR_H_ */
