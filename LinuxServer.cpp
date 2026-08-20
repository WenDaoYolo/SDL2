#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/epoll.h>
#include<unistd.h>
#include<iostream>
#include<stdlib.h>
#include<signal.h>
#include<cstring>
#include<fcntl.h>
#include<vector>
using namespace std;

bool EXIT;
vector<int> client_fds;
sockaddr_in my_sa;
char* recv_position;
char sendbuffer[64],recvbuffer[64];
int listen_fd,recv_epolls;
epoll_event listen_event,recv_events[64];

char system_msg_join[]="加入了房间";
char system_msg_leave[]="离开了房间";

void RemoveSocket(int target)
{
    for(int i=0;i<client_fds.size();i++)
    {
        if(client_fds[i]==target)
        {
            client_fds.pop_back();
            return;
        }
    }
}

void GetNotifyMessage(char* mainstr,int fd,const char* str2,const char* str3)
{
    char id[12];
    sprintf(id,"%d",fd);
    strcat(mainstr,id);
    strcat(mainstr,str2);
    strcat(mainstr,str3);
}

int setnonblocking(int fd)
{   
    int flags;
    if((flags=fcntl(fd,F_GETFL))==-1)
        flags=0;
    return fcntl(fd,F_SETFL,flags|O_NONBLOCK);
}

void broadcast(int source,const char* msg,int msg_len)
{
    for(int i=0;i<client_fds.size();i++)
    {
        if(client_fds[i]==source)
            continue;
        send(client_fds[i],msg,msg_len,MSG_DONTWAIT);
    }
}

void Init()
{
    listen_fd=socket(AF_INET,SOCK_STREAM,0);
    if(listen_fd==-1)
    {
        EXIT=true;
        return;
    }

    EXIT=false;
    recv_position=NULL;
    signal(SIGPIPE,SIG_IGN);
    setnonblocking(listen_fd);
    listen_event.data.fd=listen_fd;
    listen_event.events=EPOLLIN|EPOLLET;
    recv_epolls=epoll_create(1);
    epoll_ctl(recv_epolls,EPOLL_CTL_ADD,listen_fd,&listen_event);

    my_sa.sin_family=PF_INET;
    my_sa.sin_addr.s_addr=htonl(INADDR_ANY);
    my_sa.sin_port=htons(4399);

    bind(listen_fd,(sockaddr*)&my_sa,sizeof(my_sa));
    listen(listen_fd,10);
}

void loop()
{
    while(!EXIT)
    {
        int adjust=epoll_wait(recv_epolls,recv_events,64,1000);
        if(adjust<0){perror("epoll_wait");return;}
        if(adjust==0){continue;}
    
        for(int i=0;i<adjust;i++)
        {
            if(recv_events[i].data.fd==listen_fd)
            {
                int new_fd=accept(listen_fd,NULL,NULL);
                if(new_fd==-1&&errno!=EAGAIN)
                {
                    perror("accept");
                    return;
                }
                else
                {
                    epoll_event new_event;
                    new_event.data.fd=new_fd;

                    new_event.events=EPOLLIN|EPOLLET;
                    epoll_ctl(recv_epolls,EPOLL_CTL_ADD,new_fd,&new_event);
                    client_fds.push_back(new_fd);
                    cout<<"client "<<new_fd<<" is join"<<endl;

                    char tmp[64]="客户机";
                    GetNotifyMessage(tmp,new_fd,"",system_msg_join);
                    broadcast(new_fd,tmp,strlen(tmp));
                }
                continue;
            }

            if((recv_events[i].events&EPOLLIN)==1)
            {
                int recv_once;
                recv_position=recvbuffer;
                memset(recvbuffer,0,64);
                while(true)
                {
                    recv_once=recv(recv_events[i].data.fd,recvbuffer,64,MSG_DONTWAIT);
                    if(recv_once<=0)
                    {
                        if((errno==EAGAIN)&&(strcmp(recvbuffer,"exit")))
                        {
                            char tmp[64]="客户机";
                            GetNotifyMessage(tmp,recv_events[i].data.fd,":",recvbuffer);
                            broadcast(recv_events[i].data.fd,tmp,strlen(tmp));
                        }
                        else
                        {
                            char tmp[64]="客户机";
                            GetNotifyMessage(tmp,recv_events[i].data.fd,"",system_msg_leave);
                            broadcast(recv_events[i].data.fd,tmp,strlen(tmp));

                            cout<<"client "<<recv_events[i].data.fd<<" disconnect"<<endl;
                            epoll_ctl(recv_epolls,EPOLL_CTL_DEL,recv_events[i].data.fd,NULL);
                            RemoveSocket(recv_events[i].data.fd);
                            close(recv_events[i].data.fd);
                        }
                        break;
                    }
                    recv_position+=recv_once;
                }
                continue;
            }
        }
    }
}

void Destory()
{
    close(listen_fd);
    cout<<"program exit!"<<endl;
}

int main()
{
    Init();
    loop();
    Destory();

    return 0;
}