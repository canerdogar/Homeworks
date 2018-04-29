#include <stdio.h>
#include <unistd.h>
//#include <wait.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

struct command{
    string cname;
    vector<string> cargs;
    vector<int> ins;//birden fazla olabiliyo repeaterla hallet
    vector<int> outs;//bundan sadece bi tane oluyo//commandin stdin ine bağlayacağın pipe
    bool created;
};
struct pipe{
    int pipeid;
    int fds[2];
    int inouts[2];
    bool created;
    bool parentClosed;
    bool repeaterClosed;
};

/*bool commandinpipeıvarmı(struct command &command1,vector<struct pipe>&pipes){
    for(int i=0;i<command1.ins.size();i++){
        for(int j=0;j<pipes.size();j++){
            if(pipes[j].pipeid==command1.ins[i] && !pipes[j].created){
                return true;
            }
        }
    }
    for(int i=0;i<command1.outs.size();i++){
        for(int j=0;j<pipes.size();j++){
            if(pipes[j].pipeid==command1.outs[i] && !pipes[j].created){
                return true;
            }
        }
    }
    return false;
}*/

/*void execute(vector<struct pipe>&pipes,vector<struct command>&commands,struct command &command1){
    if (fork()==0) {
        command1.created=true;
        if (commandinpipeıvarmı(command1,pipes)) {
            int fd[2];
            for(int i=0;i<command1.ins.size();i++){
                for(int j=0;j<pipes.size();j++){
                    if(pipes[j].pipeid==command1.ins[i] && !pipes[j].created){
                        pipe(fd);
                        pipes[j].created=true;
                        for (int k=0; k<2; k++)
                            pipes[j].fds[k]=fd[k];
                        for (int k=0; k<commands.size(); k++) {
                            int flag=0;
                            for (int l=0; l<commands[k].ins.size(); l++) {
                                if (commands[k].ins[l]==pipes[j].pipeid) {
                                    flag=1;
                                }
                            }
                            for (int l=0; l<commands[k].outs.size(); l++) {
                                if (commands[k].outs[l]==pipes[j].pipeid) {
                                    flag=1;
                                }
                            }
                            if (flag==1) {
                                execute(pipes,commands,commands[k]);
                            }
                        }
                    }
                }
            }
        }
        
    }
}*/

void my_fork(vector<struct pipe> pipes,struct command command1){
    if(fork()==0){
        //cout<<command1.cname<<" i forkladım"<<endl;
        if(command1.outs.size()!=0){

            for(int i=0;i<pipes.size();i++){
                if(pipes[i].pipeid==command1.outs[0]){
                    //cout<<command1.cname<<" in stdin e "<<pipes[i].fds[0]<<endl;
                    
                    //tr out
                    close(pipes[i].fds[1]);
                    dup2(pipes[i].fds[0],0);
                    close(pipes[i].fds[0]);
                    pipes[i].parentClosed=true;
                }
            }
        }
        //cout<<command1.cname<<" 6"<<endl;
        if(command1.ins.size()==1){
            for(int i=0;i<pipes.size();i++){
                if(pipes[i].pipeid==command1.ins[0]){
                    //cout<<command1.cname<<" in stdout una "<<pipes[i].fds[1]<<endl;
                    dup2(pipes[i].fds[1],1);
                    //close(pipes[i].fds[1]);
                    //close(pipes[i].fds[0]);
                }
            }
        }
        else if(command1.ins.size()>1){
            int fd3[2];
            pipe(fd3);
            
            
            //repeaterın readleri
            for (int i=0; i<pipes.size(); i++) {
                for (int j=0; j<command1.ins.size(); j++) {
                    if (command1.ins[j]==pipes[i].pipeid) {
                        close(pipes[i].fds[0]);
                        pipes[i].repeaterClosed=true;
                    }
                }
            }
            
            //gereksizleri kapa
            for (int i=0; i<pipes.size(); i++) {
                if (!pipes[i].parentClosed && !pipes[i].repeaterClosed && pipes[i].created) {
                    close(pipes[i].fds[0]);
                    close(pipes[i].fds[1]);
                    pipes[i].parentClosed=true;
                }
            }
            
            if (fork()==0) {
                
                if(command1.outs.size()==1){
                    close(0);
                }
                
                char temp;
                close(fd3[1]);
                while (read(fd3[0],&temp,1)>0) {
                    //bağlı olduğu tüm pipelara write et;
                    for (int i=0; i<command1.ins.size(); i++) {
                        for(int j=0;j<pipes.size();j++){
                            if (command1.ins[i]==pipes[j].pipeid) {
                                write(pipes[j].fds[1],&temp,1);
                            }
                        }
                    }
                }
                close(fd3[0]);
               
               //repeaterın yazmaları
                for (int i=0; i<command1.ins.size(); i++) {
                    for(int j=0;j<pipes.size();j++){
                        if (command1.ins[i]==pipes[j].pipeid) {
                            close(pipes[j].fds[1]);
                        }
                    }
                }
                
                exit(0);
            }
            
            //commandi repeater a bağla
            close(fd3[0]);
            dup2(fd3[1],1);
            close(fd3[1]);
            
            //repeaterın yazmaları
            for (int i=0; i<command1.ins.size(); i++) {
                for(int j=0;j<pipes.size();j++){
                    if (command1.ins[i]==pipes[j].pipeid) {
                        close(pipes[j].fds[1]);
                    }
                }
            }
            
            goto atla;
            
    
        }
        
        //yukardaki fd kapamayı siktir et sen gerekli gereksiz bi kapa
        //cout<<"8"<<endl;
        for (int i=0; i<pipes.size(); i++) {
            if (!pipes[i].parentClosed && pipes[i].created) {
                //cout<<command1.cname<<" "<<pipes[i].fds[0]<<" ve "<<pipes[i].fds[1]<<" i kapadı"<<endl;
                close(pipes[i].fds[0]);
                close(pipes[i].fds[1]);
            }
        }
        
        //cout<<command1.cname<<" 7"<<endl;
    atla:char **execom=new char*[command1.cargs.size()+2];
        execom[0]=(char*)command1.cname.c_str();
        //cout<<"segment"<<endl;
        for(int i=0;i<command1.cargs.size();i++){
            execom[i+1]=(char*)command1.cargs[i].c_str();
        }
        execom[command1.cargs.size()+1]=NULL;
        //cout<<"baban"<<endl;
        if(execvp((const char*)execom[0],(char* const*)execom))
            cout<<"error aldın"<<endl;
        //cout<<"çalışmıyo"<<endl;
    }
}

int main(){
    vector<struct command>commands;
    vector<struct pipe>pipes;
    string line;
    getline(cin,line);
    while (line!="quit") {
        char * writable = new char[line.size() + 1];
        copy(line.begin(),line.end(),writable);
        writable[line.size()] = '\0';
        char * pch;
        pch=strtok(writable," ");
        int flag1=0,flag2=1,flag3=1,flag4=1;
        while ((pch)!= NULL)
        {
            if (!flag1) {
                struct command command1;
                command1.cname=pch;
                command1.created=false;
                commands.push_back(command1);
                flag1=1;
                flag4=0;
                goto c;
            }
            else if(string(pch)==">|"){
                flag2=0;
                flag3=1;
                flag4=1;
                goto c;
            }
            else if(string(pch)=="<|"){
                flag3=0;
                flag2=1;
                flag4=1;
                goto c;
            }
            else if(!flag4){
                commands[commands.size()-1].cargs.push_back(string(pch));
                goto c;
            }
            else if(!flag2){
                int flag5=0;
                for (int i=0;i<pipes.size();i++) {
                    if(pipes[i].pipeid==atoi((const char*)pch)){
                        flag5=1;
                        if (pipes[i].inouts[0]==0) {
                            pipes[i].inouts[0]=1;
                        }
                    }
                }
                if (flag5==0) {
                    struct pipe pipe1;
                    pipe1.pipeid=atoi((const char*)pch);
                    pipe1.inouts[0]=1;
                    pipe1.created=false;
                    pipe1.parentClosed=false;
                    pipe1.repeaterClosed=false;
                    pipes.push_back(pipe1);
                }
                commands[commands.size()-1].ins.push_back(atoi((const char*)pch));
                goto c;
            }
            else if(!flag3){
                int flag6=0;
                for (int i=0;i<pipes.size();i++) {
                    if(pipes[i].pipeid==atoi((const char*)pch)){
                        flag6=1;
                        if (pipes[i].inouts[1]==0) {
                            pipes[i].inouts[1]=1;
                        }
                    }
                }
                if (flag6==0) {
                    struct pipe pipe1;
                    pipe1.pipeid=atoi((const char*)pch);
                    pipe1.inouts[1]=1;
                    pipe1.created=false;
                    pipe1.parentClosed=false;
                    pipe1.repeaterClosed=false;
                    pipes.push_back(pipe1);
                }
                commands[commands.size()-1].outs.push_back(atoi((const char*)pch));
            }
            c:pch=strtok(NULL," ");
        }
        //graph connected mi bak
        bool connected=true;
        for (int i=0; i<pipes.size(); i++) {
            if (pipes[i].inouts[0]==0 || pipes[i].inouts[1]==0) {
                connected=false;
            }
        }
        //işlemini yap
        if (connected) {
            //cout<<"connected"<<endl;
            int status;
            for(int i=0;i<commands.size();i++){
                //pipe ı var mı bak
                int fd[2];
                for(int j=0;j<pipes.size();j++){
                    for(int k=0;k<commands[i].ins.size();k++){
                        if(pipes[j].pipeid==commands[i].ins[k] && !pipes[j].created){
                            pipe(fd);
                            pipes[j].created=true;
                            //cout<<commands[i].cname<<" için"<<fd[0]<<" ve "<<fd[1]<<" yaratıldı"<<endl;
                            for(int l=0;l<2;l++){
                                pipes[j].fds[l]=fd[l];
                            }
                        }
                    }
                    for(int k=0;k<commands[i].outs.size();k++){
                        if(pipes[j].pipeid==commands[i].outs[k] && !pipes[j].created){
                            pipe(fd);
                            pipes[j].created=true;
                            //cout<<commands[i].cname<<" için"<<fd[0]<<" ve "<<fd[1]<<" yaratıldı"<<endl;
                            for(int l=0;l<2;l++){
                                pipes[j].fds[l]=fd[l];
                            }
                        }
                    }

                }

                //forkla
                //cout<<"geldim "<<commands[i].cname<<endl;
                //cout<<pipes[0].fds[0]<<pipes[0].fds[1]<<endl;
                my_fork(pipes,commands[i]);
                commands[i].created=true;
                //cout<<"segment2"<<endl;
                //gereksiz connection kapa
                for (int j=0; j<pipes.size(); j++) {
                    //cout<<"segment3 "<<pipes.size()<<endl;
                    int flagp=0;
                    for (int k=0; k<commands.size(); k++) {
                        //cout<<"segment5 "<<commands.size()<<" cname"<<commands[k].cname<<" "<<commands[k].outs.size()<<endl;
                        //cout<<"commandin outu: "<<commands[k].outs[0]<<" pipeın idsi"<<pipes[j].pipeid<<endl;
                        
                        if (commands[k].outs.size()!=0 && commands[k].outs[0]==pipes[j].pipeid && !commands[k].created && pipes[j].created && !pipes[j].parentClosed) {
                            flagp=1;
                        }
                        //cout<<"segment6"<<endl;
                        for (int l=0; l<commands[k].ins.size(); l++) {
                            if (commands[k].ins[l]==pipes[j].pipeid && !commands[k].created && pipes[j].created && !pipes[j].parentClosed) {
                                flagp=1;
                                break;
                            }
                        }
                        
                        /*if (commands[k].outs[0]==pipes[j].pipeid && commands[k].created && pipes[j].created && !pipes[j].parentClosed) {
                            pipes[j].parentShouldClosed=true;
                        }else if(commands[k].outs[0]==pipes[j].pipeid && !commands[k].created && pipes[j].created && !pipes[j].parentClosed) {
                            pipes[j].parentShouldClosed=false;
                        }
                        for (int l=0; l<commands[k].ins.size(); l++) {
                            if (commands[k].ins[l]==pipes[j].pipeid && commands[k].created && pipes[j].created && !pipes[j].parentClosed) {
                                pipes[j].parentShouldClosed=true;
                            }
                            else if (commands[k].ins[l]==pipes[j].pipeid && !commands[k].created && pipes[j].created && !pipes[j].parentClosed) {
                                pipes[j].parentShouldClosed=false;
                            }
                        }*/
                    }
                    //cout<<"segment4"<<endl;
                    if (!flagp && pipes[j].created && !pipes[j].parentClosed) {
                        //cout<<"parent "<<commands[i].cname<<" i forkladıktan sonra "<<pipes[j].fds[0]<<" ve "<<pipes[j].fds[1]<<" i kapadı"<<endl;
                        close(pipes[j].fds[0]);
                        close(pipes[j].fds[1]);
                        pipes[j].parentClosed=true;
                    }
                }
                /*for (int j=0; j<pipes.size(); j++) {
                    if (!pipes[j].parentClosed && pipes[j].parentShouldClosed) {
                        close(pipes[j].fds[0]);
                        close(pipes[j].fds[1]);
                    }
                }*/
                
                
            }

            //parent connection kapa//tekrar yaz
            for(int i=0;i<pipes.size();i++){
                if (!pipes[i].parentClosed && pipes[i].created) {
                    //cout<<"hersey bittikten sonra "<<pipes[i].fds[0]<<" ve "<<pipes[i].fds[1]<<" i kapadı"<<endl;
                    close(pipes[i].fds[0]);
                    close(pipes[i].fds[1]);
                    pipes[i].parentClosed=true;
                }
            }

            for(int i=0;i<commands.size();i++){

                wait(&status);
            }

            commands.clear();
            pipes.clear();


        }
        
        delete[] writable;
        getline(cin,line);
    }
}