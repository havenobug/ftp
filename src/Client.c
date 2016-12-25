#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
pthread_mutex_t work_mutex=PTHREAD_MUTEX_INITIALIZER;
char path[1024];
char *filename;
char pwd[1024];
char temp[100];
char dir[100];
//Zhang
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
		if (remove(filename)==-1)
				{
				//printf("Removed %s\n",filename);
				}
				else{
				//perror("remove");
			}
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
	int cmd_ls(char *name)
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
	strcpy(name,temp);
	return 0;
}
	
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






	int cmd_help(char *path)
	{
	return 0;
	}
	

				
	int cmd_lcd(char *dir)
	{	//char str[50];
 	 	 chdir(dir);
 	 	//getcwd(str,sizeof(str));
 	 	//puts(str);
 	 
}
				
	int cmd_lmkdir(char *name)
{
	return mkdir(name,S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP);
	}

	void printdir(char *dir, int depath);
void printdir(char *dir, int depath){
	     
               DIR *dp;
               struct dirent *entry;
               struct stat statbuf;
               if ((dp = opendir(dir)) == NULL){
               	              //fprintf(stderr, "cannot open directory: %s\n",dir );
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

			
	static void get_full_path(char *path)
{	

	
}







//Yang
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

void recv_msg(int fd,struct FTP_MSG *msg)
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
}

void recv_msgQueue(int fd,struct FTP_MSG *msg)
{
	void* byte=(void*)msg;
	int length=sizeof(struct FTP_MSG);
	int tmp=0;
	while(length!=tmp)
	{
		tmp+=recv(fd,byte,length-tmp,0);
	}
	msg=(struct FTP_MSG*)byte;
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
int Connect(in_addr_t ConnectTo,in_port_t Cport)
{
	int ClientSocket;
	struct sockaddr_in ServerAddress;
	ClientSocket=socket(AF_INET,SOCK_STREAM,0);	
	if (ClientSocket==INVALID)
	{
		printf("cannot create\n");
		return INVALID;
	}
	ServerAddress.sin_addr.s_addr=ConnectTo;
	ServerAddress.sin_port=Cport;
	ServerAddress.sin_family=AF_INET;
	if (connect(ClientSocket,(struct sockaddr*)&ServerAddress,sizeof(struct sockaddr_in))==INVALID)
	{
		printf("failed\n");
		return INVALID;
	}
	printf("connected to %s:%d\n",inet_ntoa(*(struct in_addr*)&ConnectTo),(int)ntohs(Cport) );
	return ClientSocket;
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

void* thread_message(void *fd)
{
	printf("Message thread created\n");
	int sockfd=*(int*)fd;
	struct FTP_MSG QuitRecive;
	char recvmsg;
	while(1)
	{
		recv_msg(sockfd,&QuitRecive);    
		if(!strncmp(QuitRecive.head.command,"kill",4))
		{
			printf("you've been kicked from server\n");
			close(sockfd);
			break;
		}
		else if(!strncmp(QuitRecive.head.command,"quit",4))
		{
			printf("Server is down\n");
			close(sockfd);
			break;
		}
		else if(!strncmp(QuitRecive.head.command,"download",8))
		{
			
				
				strcat(path,"/");
				strcat(path,filename);
				FILE *file=NULL;
				file=fopen(path,"wt+");
				if(file==NULL)
				{
					printf("not find FIle");
				}
				chmod(path,S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP);
				Download(sockfd,file);
				pthread_mutex_lock(&work_mutex);
				pthread_mutex_unlock(&work_mutex);
				fclose(file);
				file=NULL;
				strcpy(path,"");
		}
		else if(!strncmp(QuitRecive.head.command,"cd",2))
		{
			//if(!strncmp(QuitRecive.data,"suc",3))
			//{
			printf("cd success\n");
			strcpy(pwd,QuitRecive.data);
			//}
			//else
			//{
			//printf("cd failed\n");
			//}
		}
	else if(!strncmp(QuitRecive.head.command,"ls",2))
		{
			if(!strncmp(QuitRecive.data,"88 		zy		server		Server		Server.c		Servermanage		Servermanage.c",3))
			{
			printf("server\n");
			}
			else
			{
			printf("%s\n",QuitRecive.data);
			}
			
		}
		else if(!strncmp(QuitRecive.head.command,"pwd",3))
		{			
			printf("%s\n",QuitRecive.data);
		}
		else if(!strncmp(QuitRecive.head.command,"mkdir",5))
		{
			if(!strncmp(QuitRecive.data,"suc",3))
			{
			printf("mkdir success\n");
			}
			else
			{
			printf("mkdir failed\n");
			}
		}
		else if(!strncmp(QuitRecive.head.command,"rmdir",5))
		{
			if(!strncmp(QuitRecive.data,"suc",3))
			{
			printf("rmdir success\n");
			}
			else
			{
			printf("rmdir failed\n");
			}
		}
	}
	exit(0);
	pthread_exit(NULL);	
	return NULL;		
}


void VS_StrRTrim(char *pStr)  
{  
    char *pTmp = pStr+strlen(pStr)-1;  
      
    while (*pTmp == ' ')   
    {  
        *pTmp='\0';  
        pTmp--;  
    }  
}

  
int main (char argc,char *argv[])//argv[1]:IP argv[2]:name argv[3]:password
{	
	char name[20];
	char dir[1024];
	char password[20];
	int sockfd;
	char cmd[1024];
	char buf[1024];
	struct FTP_MSG send;
	struct FTP_MSG recive;
	struct in_addr ip;
	struct in_addr addrtmp;	
	pthread_t messageThread;
	if(argv[1]==NULL||argv[2]==NULL||argv[3]==NULL)
	{
		printf("plz enter right argv");
		exit(0);
	}
	inet_aton(argv[1],&addrtmp);
	sockfd=Connect(addrtmp.s_addr,htons((unsigned short)9734));
	int* messageThreadfd=&sockfd;
	pthread_create(&messageThread,NULL,thread_message,(void*)messageThreadfd);
	//printf("PLZ ENTER YOUR ACCOUNT:");
	//scanf("%s",name);
	strcpy(send.data,argv[2]);
	send_msg(sockfd,&send);
	//printf("PLZ ENTER YOUR PASSWORD:");
	//scanf("%s",password);
	strcpy(send.data,argv[3]);
	send_msg(sockfd,&send);
	recv_msg(sockfd,&recive);
	if(!strcmp(recive.data,"success"))
	{
		printf("verify success\n");
		strcpy(send.data,GetIP());
		send_msg(sockfd,&send);
		recv_msg(sockfd,&recive);
		strcpy(pwd,recive.data);
		while(strncmp(cmd,"bye",3))
		{
			printf("myftp<");
			fgets(cmd,sizeof(cmd),stdin);
			getcwd(path,1024);
			if(!strcmp(cmd,""))
			{
			
			}
			else if(!strncmp(cmd,"put",3))
			{	int filenameSize;
				char *space=" ";
				filenameSize=strlen(cmd)-4;
				//filename=strchr(cmd,space);
				filename=strtok(cmd," ");
				filename=strtok(NULL,"\n");
				//VS_StrRTrim(filename);
				//memcpy(filename,cmd+4,filenameSize-1);
				strcat(path,"/");
				strcat(path,filename);
				printf("%s",path);
				printf("%s",filename);	
				strcpy(send.data,filename);
				strcpy(send.head.command,"put");
				send_msg(sockfd,&send);			
				FILE *file=NULL;
				file=fopen(path,"rt");
				if(file==NULL)
				{
	/* ERROR*/			printf("cant find the file\n");
				}
				Upload(sockfd,file);
				fclose(file);
				file=NULL;
				strcpy(path,"");
				strcpy(filename,"");
			}
			else if(!strncmp(cmd,"get",3))
			{
				int filenameSize;
				
				strcpy(send.head.command,"get");
				filenameSize=strlen(cmd)-4;
				//memcpy(filename,cmd+4,filenameSize-1);
				filename=strtok(cmd," ");
				filename=strtok(NULL,"\n");	
				strcpy(send.data,filename);
				send_msg  (sockfd,&send);				
				/*File Control*/
	
			}
	
			else if(!strncmp(cmd,"cd",2))
			{
				char dir[32];
				//printf("the dir is\n");
				//fgets(dir,sizeof(dir),stdin);
				while(1){
	if(cmd[strlen(cmd)-1] ==  ' ')
	cmd[strlen(cmd)-1]='\0';
	else 
	break;
	}
	while(1){
	if(cmd[strlen(cmd)-1]=='\n')
	cmd[strlen(cmd)-1]='\0';
	else 
	break;
	}
	char *p=cmd;
	p=p+3;
	strcpy(dir,p);
	cmd_lcd(dir);
				strcpy(send.head.command,"cd");
				strcpy(send.data,dir);
				strcpy(send.pwd,pwd);
				send_msg(sockfd,&send);
			}
			else if(!strncmp(cmd,"pwd",3))
			{
				//strcpy(send.head.command,"pwd");
				//send_msg(sockfd,&send);
				printf("%s\n",pwd);				
			}
			else if(!strncmp(cmd,"mkdir",5))
			{
				char dir[32];
				//printf("the name of the new dir:\n");
				//fgets(dir,sizeof(dir),stdin);
			while(1){
	if(cmd[strlen(cmd)-1] ==  ' ')
	cmd[strlen(cmd)-1]='\0';
	else 
	break;
	}
	while(1){
	if(cmd[strlen(cmd)-1]=='\n')
	cmd[strlen(cmd)-1]='\0';
	else 
	break;
	}
	//dir[strlen(dir)-1]='\0';
	
	char  *p=cmd;
	p=p+6;
	strcpy(dir,p);
	cmd_lmkdir(dir);
				//cmd_lmkdir(dir);
				strcpy(send.head.command,"mkdir");
				strcpy(send.data,dir);
				send_msg(sockfd,&send);
			}
			else if(!strncmp(cmd,"rmdir",5))
			{
			char  filename[80];
				/*char filename[80];
				
				//printf("THe file to delete:");
				//fgets(filename,sizeof(filename),stdin);
				int i = 6;
				int j= 0;
				while(cmd[i]!='\0')
				{
				filename[j]=cmd[i];
				i++;
				j++;
				}
				cmd_lrmdir(filename);*/
				while(1){
	if(cmd[strlen(cmd)-1] ==  ' ')
	cmd[strlen(cmd)-1]='\0';
	else 
	break;
	}
	while(1){
	if(cmd[strlen(cmd)-1]=='\n')
	cmd[strlen(cmd)-1]='\0';
	else 
	break;
	}
	//dir[strlen(dir)-1]='\0';
	
	char  *p=cmd;
	p=p+6;
	strcpy(filename,p);
	//cmd_lmkdir(dir);
	cmd_lrmdir(filename);
				strcpy(send.head.command,"rmdir");
				strcpy(send.data,filename);
				send_msg(sockfd,&send);
			}
			else if(!strncmp(cmd,"dir",3))
			{
				//printf("the name of the dir you want to list:\n");
				//fgets(path,sizeof(cmd),stdin);
			while(1){
	if(cmd[strlen(cmd)-1]=='\n')
	cmd[strlen(cmd)-1]='\0';
	else 
	break;
	}
			char *p=cmd;
			p=p+4;
			strcpy(dir,p);
			cmd_dir(dir);
			//printf("%s",dir);
				//cmd_dir(dir);
				//if(cmd_dir(path)==-1)
				//{
				//printf("error!");
				//}
			}
			else if(!strncmp(cmd,"lcd",3))
			{
				//printf("the dir is\n");
				//fgets(path,sizeof(path),stdin);
				while(1){
	if(cmd[strlen(cmd)-1] ==  ' ')
	cmd[strlen(cmd)-1]='\0';
	else 
	break;
	}
	while(1){
	if(cmd[strlen(cmd)-1]=='\n')
	cmd[strlen(cmd)-1]='\0';
	else 
	break;
	}
	char *p=cmd;
	p=p+4;
	strcpy(dir,p);
	cmd_lcd(dir);
			}
			else if (!strncmp(cmd,"ls",2))
			{
			//fgets(path,sizeof(cmd),stdin);
				//char *topdir=".";
				//printf("%s\n",topdir);
			//if(argc >=2)
			//topdir=argv[1];
			//printdir(topdir,0);
			//printf("done.\n");
		/*while(1){
	if(cmd[strlen(cmd)-1] ==  ' ')
	cmd[strlen(cmd)-1]='\0';
	else 
	break;
	}*/
	while(1){
	if(cmd[strlen(cmd)-1]=='\n')
	cmd[strlen(cmd)-1]='\0';
	else 
	break;
	}
	char *p=cmd;
	p=p+3;
	strcpy(dir,p);
	strcpy(send.head.command,"ls");
	strcpy(send.data,dir);
	send_msg(sockfd,&send);
			//recv_msg(sockfd,&recive);
			//printf("%s\n",recive.data);
			//cmd_ls(dir);
				
			}
			else if(!strncmp(cmd,"lpwd",4))
			{
				if(cmd_lpwd(path)==-1)
				{
					printf("error!\n");
				}
					else
				{
					printf("%s\n",path);
				}
			}
			else if(!strncmp(cmd,"lmkdir",6))
			{
				while(1){
	if(cmd[strlen(cmd)-1] ==  ' ')
	cmd[strlen(cmd)-1]='\0';
	else 
	break;
	}
	while(1){
	if(cmd[strlen(cmd)-1]=='\n')
	cmd[strlen(cmd)-1]='\0';
	else 
	break;
	}
	//dir[strlen(dir)-1]='\0';
	
	char  *p=cmd;
	p=p+7;
	strcpy(dir,p);
	cmd_lmkdir(dir);
			}
			else if(!strncmp(cmd,"lrmdir",6))
			{
				while(1){
	if(cmd[strlen(cmd)-1] ==  ' ')
	cmd[strlen(cmd)-1]='\0';
	else 
	break;
	}
	while(1){
	if(cmd[strlen(cmd)-1]=='\n')
	cmd[strlen(cmd)-1]='\0';
	else 
	break;
	}
	//dir[strlen(dir)-1]='\0';
	
	char  *p=cmd;
	p=p+7;
	strcpy(dir,p);
	//cmd_lmkdir(dir);
	cmd_lrmdir(dir);
				//printf("THe file to delete:");
				//fgets(filename,sizeof(cmd),stdin);
				/*if (remove(filename)==-1)
				{
				printf("Removed %s.\n",filename);
				}
				else{
				perror("remove");
			}*/
		}
			else if (!strncmp(cmd,"help",4)){
		printf("lpwd             显示当前目录\nlcd               切换目录\nlmkdir              创建一个文件夹\ndir              显示当前目录下文件\nlrmdir               删除一个文件夹\nls           显示当前目录下文件\npwd          显示服务器当前目录\nmkdir            在服务器创建目录\nrmdir            在服务器删除目录\ncd          切换服务器目录\n");
		fgets(path,sizeof(cmd),stdin);
	}
						
		}
		strcpy(send.head.command,"bye");
		send_msg(sockfd,&send);
		printf("goodbye");
		pthread_join(messageThread,NULL);
	}
	else
	{
		printf("verify failed\n");
	}
	
}
