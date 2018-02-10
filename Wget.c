
#include <sys/types.h>
#include <unistd.h>    
#include <strings.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <signal.h>    
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include "nslookup.h"

int main(int argc, char* argv[])
{ 
  int sock; 
  struct sockaddr_in cli_name; 
  char hostname[100], path[100]  , buf[1024], request[100];
  int port=80, r;
  char* url=argv[1];
  
  printf("Client is alive and establishing socket connection.\n");
  
   if (argc != 2) {
       perror("Usage: hostnamelookup <hostname>\n");
       exit(1);
     }  
   
  if(sscanf(url, "http://%99[^:]:%i%199[^\n]", hostname, &port, path)==3);
  else if(sscanf(url, "http://%99[^/]%199[^\n]", hostname, path)==2);
  else if(sscanf(url, "http://%99[^/]%199[^\n]", hostname, path)==1){
    path[0] = '/';
  }else{
    perror ("Error readind URL!");
    close(sock);
     exit(1);
  } 
  
  printf("hostname = \"%s\"\n", hostname);
  printf("port = \"%d\"\n", port);
  printf("path = \"%s\"\n", path);
  
  sock = socket(AF_INET, SOCK_STREAM, 0);
  
  if (sock < 0)
    { 
      perror ("Error opening channel");
      close(sock);
      exit(1);
    }

  memset((char *)&cli_name,0, sizeof(cli_name)); 
  
  cli_name.sin_family = AF_INET; 
  cli_name.sin_addr.s_addr = inet_addr(nslookup(hostname)); 
  cli_name.sin_port = htons(port);

  if (connect(sock, (struct sockaddr *)&cli_name, sizeof(cli_name)) < 0)
    { perror ("Error establishing communications");
      close(sock);
      exit(1);
    }
  
  bzero(request, sizeof(request));
  strcpy(request, "GET ") ;
  strcat(request , path);
  strcat(request, " HTTP/1.0\nHOST: ");
  strcat(request, hostname);
  strcat(request, "\n\n");
  puts(request);
   
  write(sock, request, strlen(request));

  memset(buf,0, sizeof(buf));
  r=read(sock, buf, sizeof(buf));
  
    while(r>0)  
    { 
    write(1,buf,r);
    r=read(sock,buf,sizeof(buf));
    }
  write(1," \0\n",2);
  printf("\nExiting now.\n");

  close(sock); 
  exit(0); 
  return 0;
} 

