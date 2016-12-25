#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/stat.h>
#include<pthread.h>
#include<arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include<sys/types.h>
#include<dirent.h>

#define INVALID -1
pthread_mutex_t server_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t client_mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t work_mutex=PTHREAD_MUTEX_INITIALIZER;
int servercounter=0;
int clientcounter=0;
	char temp[80];
pthread_t ServermanageThread;
pthread_t ClientThread;
pthread_t ServerThread;
//Waiting for adding Mutex Control

struct FTP_HEAD
{
	char command[32];           
	int len;
};
struct FTP_MSG
{
	struct FTP_HEAD head;       
	char data[1024];
	char pwd[512];
};
struct user
{
	in_addr_t ip;
	int sockfd;
	int flag;
	unsigned long int tid;
};
struct FTP_MSG Send;
struct FTP_MSG Recv;
struct FTP_MSG ManageSend;
struct FTP_MSG ManageRecv;
struct user Userlist[10];
//Zhang's part
int cmd_lpwd(char *path)
{
{
	if(getcwd(path,1024)!=NULL)
{
	return 0;
}
	else
{
	return -1;
}


}
}
int cmd_lrmdir(char *filename){
	return 0;
}
int cmd_ls(char *name)
{
	char temp[1024]="\0";
	DIR *dir=opendir(name);

	if(dir==NULL)
	{
	//char dir [128];
	//getcwd(dir,1024);
	//printf("%s\n",dir);
	//printf("Do not find this directory!\n");
	strcpy(Send.data,"88 		zy		server		Server		Server.c		Servermanage		Servermanage.c");
	return -1;
	}
	
	//printf("successfully find the directory!\n");
	chdir(name);
	struct dirent* item=NULL;
	//item=readdir(dir);
	int count=0;
	while(item = readdir(dir))
{	if(count==5)
	{
	strcat(temp,"\n");
	count=0;
	}
	if(strcmp(".",item->d_name)==0||strcmp("..",item->d_name)==0)
	{
	//item=readdir(dir);
	continue;
	}
	strcat(temp,item->d_name);
	strcat(temp,"    ");
	count++;
	//item=readdir(dir);
}
	strcat(temp,"\n");
	chdir("..");
	closedir(dir);
	//printf("%s",temp);
	//strcpy(Send.data,temp);
	strcpy(Send.data,temp);
	//send_msg(sockfd,&Send);
	//strcpy(name,temp);
	return 0;
}
/*int cmd_lls()
{
	cahr dir[100];
	getcwd(dir,sizeof(dir));
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	if((dp=opendir(dir))==NULL){
	fprintf(stderr,"%s\n",dir);
	return 0;	}
	chdir(dir);
	char ch[500]="";
	while((entry=readdir(dp))!=NULL）{
	lstat(entry->d_name,&statbuf);
	if(S_ISDIR(statbufar,st_mode)){
		if(strcmp(".",entry->d_name)==0||strcmp("..",entry->d_name)==0){
		continue;
		}
		strcat(strcat(ch," "0),entry->d_name);
		strcat(c,"/");
		}
		else{
		strcat(strcat(ch," "),entry->d_name);
		}
		}
		}*/
		/*int cmd_ls()
		{
	
		int i =0;
		DIR *dir;
		struct dirent *ptr;
		char buffer[80];
		dir = opendir(getcwd(buffer,sizeof(buffer)));
		while((ptr=readdir(dir))!=NULL){
		if(strcmp(".",ptr->d_name)==0||strcmp("..",ptr->d_name)==0)
		continue;
		printf("%s\n",ptr->d_name);
		strcat(temp,ptr->d_name);
		strcat(temp,"\n");
		i++;
		}
		
		}*/
		
int cmd_dir(char *name)
{
	char temp[1024]="\0";
	DIR *dir=opendir(name);

	if(dir==NULL)
	{
	printf("Do not find this directory!\n");
	return -1;
	}
	
	printf("successfully find the directory!\n");
	chdir(name);
	struct dirent* item=NULL;
	//item=readdir(dir);
	int count=0;
	while(item = readdir(dir))
{	if(count==5)
	{
	strcat(temp,"\n");
	count=0;
	}
	if(strcmp(".",item->d_name)==0||strcmp("..",item->d_name)==0)
	{
	//item=readdir(dir);
	continue;
	}
	strcat(temp,item->d_name);
	strcat(temp,"    ");
	count++;
	//item=readdir(dir);
}
	strcat(temp,"\n");
	chdir("..");
	closedir(dir);
	printf("%s",temp);
	//strcpy(name,temp);
	return 0;
}


void printdir(char *dir, int depath);
void printdir(char *dir, int depath){
	     
               DIR *dp;
               struct dirent *entry;
               struct stat statbuf;
               if ((dp = opendir(dir)) == NULL){
               	              fprintf(stderr, "cannot open directory: %s\n",dir );
               	              return ;
               }
               chdir(dir);
               while((entry = readdir(dp)) != NULL){
                              lstat(entry->d_name,&statbuf);
                              if(S_ISDIR(statbuf.st_mode)){
                              	if (strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0 )
                              		continue;
                              	printf("%*s%s/\n", depath,"",entry->d_name);
                              	printdir(entry->d_name,depath+4);
                              }
                              else printf("%*s%s\n",depath,"",entry->d_name );
               }
               chdir("..");
               closedir(dp);
}

	int cmd_help(char *path)
	{
	return 0;
	}
	

				
	int cmd_lcd(char *dir)
	{
 		return chdir(dir);
}
				
	int cmd_lmkdir(char *name)
{
	return mkdir(name,S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP);
	}

				

			
	static void get_full_path(char *path)
{	

	
}
//Zhang's part
void send_head(int fd,struct FTP_HEAD *head)
{
	void* byte=(void*)head;
	int length=sizeof(struct FTP_HEAD);
	int tmp=0;
	while(length!=tmp)
	{
		tmp+=send(fd,byte,length-tmp,0);
	}
	printf("send head success\n");
}

void send_msg(int fd,struct FTP_MSG *msg)
{
	void* byte=(void*)msg;
	int length=sizeof(struct FTP_MSG);
	int tmp=0;
	while(length!=tmp)
	{
		tmp+=send(fd,byte,length-tmp,0);
	}
	printf("send msg success\n");
}

void recv_head(int fd,struct FTP_HEAD *head)
{
	printf("Waiting recv\n");
	void* byte=(void*)head;
	int length=sizeof(struct FTP_HEAD);
	int tmp=0;
	while(length!=tmp)
	{
		tmp+=recv(fd,byte,length-tmp,0);
	}
	head=(struct FTP_HEAD*)byte;
	printf("recv head success\n");
}

struct FTP_MSG* recv_msg(int fd,struct FTP_MSG *msg)
{
	printf("Waiting recv\n");
	void* byte=(void*)msg;
	int length=sizeof(struct FTP_MSG);
	int tmp=0;
	while(length!=tmp)
	{
		tmp+=recv(fd,byte,length-tmp,0);
	}
	msg=(struct FTP_MSG*)byte;
	printf("recv msg success\n");
	return msg;
}

void Upload(int fd,FILE *fp)
{
	struct FTP_MSG msg;
	int sendlen;
	char byte[1024];
	while((sendlen=fread(byte,sizeof(char),512,fp))!=0)
	{
	printf("%d",sendlen);
	strcpy(msg.data,byte);
	msg.head.len=sendlen;
	send_msg(fd,&msg);
	}
	//eof
	msg.head.len=-1;
	send_msg(fd,&msg);
}

void Download(int fd,FILE *fp)
{
	struct FTP_MSG msg;
	int recv=0;
	while(1)
	{
		recv_msg(fd,&msg);
		if(msg.head.len!=-1)
		{
			recv=fwrite(msg.data,sizeof(char),msg.head.len,fp);
		}
		else
		{
			break;
		}		
	}
}

int Start(int nPort)
{
	int nServerSocket=INVALID;
	struct sockaddr_in tAddress;
	nServerSocket=socket(AF_INET,SOCK_STREAM,0);
	if(nServerSocket==INVALID)
	{
		return INVALID;
	}
	tAddress.sin_port=htons((unsigned short)nPort);
	tAddress.sin_family=AF_INET;
	tAddress.sin_addr.s_addr=htonl(INADDR_ANY);
	if(bind(nServerSocket,(const struct sockaddr*)&tAddress
		,sizeof(struct sockaddr_in))==INVALID)
	{
		return -1;
	}
	if (listen(nServerSocket,5)==INVALID)
	{
		return INVALID;
		exit(1);
	}
	printf("Server Created\n");	
	return nServerSocket;
}
int Accept(int nSocket){
	struct sockaddr_in tAddr_in;
	socklen_t nLength=sizeof(struct sockaddr_in);
	int nAccSocket=accept(nSocket,(struct sockaddr*)&tAddr_in,&nLength);
	if(nAccSocket<0)
{
	return -1;
	exit(0);
}
	return nAccSocket;
}

/*void* thread_try(void *fd)
{	pthread_mutex_lock(&mutex);
	printf("id:%u\n",(unsigned int)pthread_self());	
	tmp++;
	printf("%d\n",tmp);
	pthread_mutex_unlock(&mutex);
	return NULL;
				
}*/
void* thread_ServerManage(void *fd)
{	char cmd[1024];
	int sockfd;
	sockfd=*(int*)fd;
	char ipadd[1024];
	char tmp[1024];
	char strsave[20];
	while(1)
	{
		recv_msg(sockfd,&ManageRecv);
		strcpy(ManageSend.data,"");
		if(!strncmp(ManageRecv.head.command,"list",4))
		{
			int i;
			for(i=0;i<10;i++)
			{
				if(Userlist[i].flag==1)
				{
					strcpy(ipadd,inet_ntoa((*(struct in_addr*)&Userlist[i].ip)));
					strcpy(tmp,"ip:");
					strcat(tmp,ipadd);
					strcat(tmp," ");
					strcat(tmp,"tid:");
					sprintf(strsave,"%lu ",Userlist[i].tid);
					strcat(tmp,strsave);
					strcat(tmp,"sockfd:");
					sprintf(strsave,"%d ",Userlist[i].sockfd);
					strcat(tmp,strsave);
					strcat(tmp,"\n");
					strcat(ManageSend.data,tmp);
					//printf("tid:%d sockfd:%d\n",Userlist[i].tid,Userlist[i].sockfd);
					
				}
			}
			strcpy(tmp,"");
			send_msg(sockfd,&ManageSend);
		}
		else if(!strncmp(ManageRecv.head.command,"kill",4))
		{
			for(int i=0;i<10;i++)
			{
				if(Userlist[i].sockfd==atoi(ManageRecv.data))
				{
					//strcpy(ManageSend.data,"killed");
					//send_msg(Userlist[i].sockfd,ManageSend);
					strcpy(Send.head.command,"kill");
					send_msg(Userlist[i].sockfd,&Send);     
					close(Userlist[i].sockfd); 
					Userlist[i].flag=0;
					break;
				}
			}
			printf("Kill complete\n");
		}
		else if(!strncmp(ManageRecv.head.command,"quit",4))
		{
			for(int i=0;i<10;i++)
			{
				if(!Userlist[i].flag==0)
				{
					strcpy(Send.head.command,"quit");
					send_msg(Userlist[i].sockfd,&Send);
					close(Userlist[i].sockfd);
				}
			}
			break;
		}
	}
	printf("quiting\n");
	exit(0);
	pthread_exit(NULL);
	//Waiting for edit
	/*struct user User[1024];
	User=(struct user)fd;*/
	//system("gnome-terminal -e ./Servermanage");
	return NULL;
				
}	





void* thread_ClientCreate(void* userinf)
{
	int i;
	int sockfd;
	char path[1024];
	char dir[1024]="/home/sabbah/Folder";
	struct user *User=(struct user*)userinf;
	printf("Child Thread Create\n");
	pthread_mutex_lock(&client_mutex);
	clientcounter++;
	pthread_mutex_unlock(&client_mutex);
	pthread_detach(pthread_self());
	for(i=0;i<10;i++)
	{
		if(Userlist[i].flag==0)
		{
			Userlist[i].ip=User->ip;
			Userlist[i].sockfd=User->sockfd;
			Userlist[i].tid=pthread_self();
			Userlist[i].flag=1;
			sockfd=Userlist[i].sockfd;
			break;
		}
	}
	while(1)
	{	
		recv_msg(sockfd,&Recv);
		strcpy(Send.data,"");
		getcwd(path,1024);
		if(!strncmp(Recv.head.command,"put",3))
		{
			FILE *fp;
			char tmp[1024];
			strcpy(tmp,path);
			strcat(tmp,"/");
			strcat(tmp,Recv.data);
			printf("%s",path);
			fp=fopen(tmp,"wt+");
			if(fp==NULL)
			{
				printf("not find File");
			}
			chmod(path,S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP);
			Download(sockfd,fp);
			fclose(fp);
			fp=NULL;
			strcpy(tmp,"");
		}
		else if(!strncmp(Recv.head.command,"get",3))
		{
			FILE *fp;
			char tmp[1024];
			strcpy(tmp,path);
			strcat(tmp,"/");
			strcat(tmp,Recv.data);
			fp=fopen(tmp,"rt");
			if(fp==NULL)
			{
				printf("not find FIle");
			}
			strcpy(Send.head.command,"download");
			send_msg(sockfd,&Send);
			Upload(sockfd,fp);
			fclose(fp);
			fp=NULL;
			strcpy(tmp,"");
		}
		else if(!strncmp(Recv.head.command,"ls",2))
			{
				strcpy(Send.head.command,"ls");		
			char dir[128];
			strcpy(dir,Recv.data);
			//printf("%s\n",dir);
			if(dir == NULL){
			getcwd(dir,128);
			//strcpy(dir,Recv.data);
			cmd_ls(dir);
			printf("%s\n",dir);
			}
			else {			
			strcpy(dir,Recv.data);
			cmd_ls(Recv.data);
			}
			send_msg(sockfd,&Send);
			//printf("%s\n",Recv.data);
			//printf("%s\n",dir);
			//char *topdir=".";
			//if(argc>=2)
			//topdir=argv[1];
			//printf("scan of %s\n",Recv.data);
			//printdir(topdir,0);
			//printf("done.\n");
			//send_msg(sockfd,&send);
			
			}
			else if(!strncmp(Recv.head.command,"rmdir",5))
			{
				strcpy(Send.head.command,"rmdir");
				if (remove(Recv.data)==-1)
				{
				printf("Removed %s.\n",Recv.data);
				strcpy(Send.data,"suc");
				}
				else{
				perror("remove");
				strcpy(Send.data,"fal");
					}
				send_msg(sockfd,&Send);
			}
			else if(!strncmp(Recv.head.command,"cd",2))
			{
				chdir(Recv.pwd);
				strcpy(Send.head.command,"cd");
				if(cmd_lcd(Recv.data)==-1)
				{
					strcpy(Send.data,"fal");
					printf("Do not find this directory!\n");
				}
				else
				{
				char tmppwd[1024];
				getcwd(tmppwd,1024);
				strcpy(Send.data,tmppwd);
				send_msg(sockfd,&Send);
				}
			}
			else if(!strncmp(Recv.head.command,"pwd",3))
			{
				strcpy(Send.head.command,"pwd");
				if(cmd_lpwd(path)==-1)
				{
					printf("error!\n");
					strcpy(Send.data,"failed");
					send_msg(sockfd,&Send);
				}
					else
				{					
					strcpy(Send.data,path);
					send_msg(sockfd,&Send);
				}
			}
			else if(!strncmp(Recv.head.command,"mkdir",5))
			{
				strcpy(Send.head.command,"mkdir");
				if(cmd_lmkdir(Recv.data)==-1)
				{
					printf("error!\n");
					strcpy(Send.data,"fal");
				}
				else
				{
				strcpy(Send.data,"suc");			
				}
				send_msg(sockfd,&Send);
			}
			
/*			else if(!strncmp(Recv.head.command,"dir",3))
			{
			}
			else if(!strncmp(Recv.head.command,"lcd",3))
			{
			}
			else if(!strncmp(Recv.head.command,"lpwd",4))
			{
			}
			else if(!strncmp(Recv.head.command,"lmkdir",6))
			{
			}
			else if(!strncmp(Recv.head.command,"lrmdir",6))
			{
			}*/	
		if(!strncmp(Recv.head.command,"bye",3))
		{
			Userlist[i].flag=0;
			close(Userlist[i].sockfd);
		}
		
	}					
}

int FTP_CreateNewClient(int nSocket,in_addr_t ipaddress)
{
	struct user *User=NULL;
	User=(struct user*)malloc(sizeof(struct user));
	if(!User)
	{
		printf("failed to create user malloc\n");
	}
	User->sockfd=nSocket;
	User->ip=ipaddress;
	pthread_create(&ClientThread,NULL,thread_ClientCreate,(void*)User);
	return 0;
}

void* thread_ServerCreate(void* fd)
{
	char recvname[20];
	char recvpass[20];
	char name[20]="admin";
	char password[20]="admin";
	char specname[20]="root";
	char specpass[20]="root";
	char clientip[1024];
	char pwd[1024];
	struct in_addr ip;
	getcwd(pwd,1024);
	int sockfd=Start(9734);
	for(int i=0;i<10;i++)
	{
		Userlist[i].sockfd=-1;
		Userlist[i].flag=0;
	}
	system("gnome-terminal -e ./Servermanage");
	while(1)
	{
		int client_sockfd=Accept(sockfd);
		if(client_sockfd==-1)
		{
			printf("Connection failed");
			break;
		}
		recv_msg(client_sockfd,&Recv);
		strcpy(recvname,Recv.data);
		recv_msg(client_sockfd,&Recv);
		strcpy(recvpass,Recv.data);
		if(!strcmp(recvname,name)&&!strcmp(recvpass,password))
		{
			pthread_mutex_lock(&server_mutex);
			servercounter++;
			pthread_mutex_unlock(&server_mutex);
			strcpy(Send.data,"success");
			send_msg(client_sockfd,&Send);
			recv_msg(client_sockfd,&Recv);
			printf("get ip address%s\n",Recv.data);
			strcpy(clientip,Recv.data);
			printf("%d",inet_aton(clientip,&ip));
			strcpy(Send.data,pwd);
			send_msg(client_sockfd,&Send);
			FTP_CreateNewClient(client_sockfd,ip.s_addr);
		}
		else if(!strcmp(recvname,specname)&&!strcmp(recvpass,specpass))
		{
			printf("Server manage online");
			pthread_create(&ServermanageThread,NULL,thread_ServerManage,(void*)&client_sockfd);
		}
		else
		{
			printf("verify failed\n");
		}
	}
pthread_join(ServermanageThread,NULL);
}
char *GetIP()
{
	char name[128];
	struct hostent *hent;
int i;
	gethostname(name,sizeof(name));
	hent=gethostbyname(name);
	return inet_ntoa(*(struct in_addr*)(hent->h_addr_list[i]));
}
	
int main()
{	

	char cmd[20];
	int sockfd=0;
	int ret=0;
	ret=pthread_create(&ServerThread,NULL,thread_ServerCreate,NULL);	
	ret=pthread_join(ServerThread,NULL);
	return 0;
}
