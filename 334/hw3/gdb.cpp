#include <gdbm.h>
#include <stdio.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
//#include <fuse.h>
#include <libgen.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <iostream>
#include <ctime>
using namespace std;
typedef struct filecontent{
	char type;
	off_t size;
	uid_t user;
	gid_t group;
	mode_t permissions;
	time_t atime;
	time_t mtime;
	time_t ctime;
	char content[0];
}filecontent;

int main(){
	GDBM_FILE gdb;
	gdb=gdbm_open("gdbFile",0,GDBM_READER,0777,NULL);
	if(gdb){
		datum key={"/",2};
		datum value=gdbm_fetch(gdb,key);
		if(value.dsize>0){
			filecontent *fcon=new filecontent[value.dsize];
			memcpy(&fcon,value.dptr,value.dsize);
			//filecontent *fcon=(filecontent*)value.dptr;
			cout<< fcon->type<<endl;
		}
	}
	return 0;

}
