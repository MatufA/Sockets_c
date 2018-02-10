
#include <sys/types.h>
#include <unistd.h>    
#include <strings.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>    
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include "nslookup.h"
#define SIM_LENGTH 10 
//#define IP_ADDRESS "127.0.0.1" 
#define PORT 1337 

int main(int argc, char* argv[])
{ 
  int sock; 
  struct sockaddr_in cli_name; 
  int count;
  int value; 
  char* addrinfo;
  char *addr = argv[1];
  
 if (argc != 2) {
    perror("Usage: hostnamelookup <hostname>\n");
    exit(1);
  }
  
  printf("Client is alive and establishing socket connection.\n");
  
  
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
    { perror ("Error opening channel");
      close(sock);
      exit(1);
    }

  memset((char *)&cli_name,0, sizeof(cli_name)); 
  
  addrinfo = nslookup( addr);
  cli_name.sin_family = AF_INET; 
  cli_name.sin_addr.s_addr = inet_addr(addrinfo); 
  cli_name.sin_port = htons(PORT);


  if (connect(sock, (struct sockaddr *)&cli_name, sizeof(cli_name)) < 0)
    { perror ("Error establishing communications");
      close(sock);
      exit(1);
    }


  for (count = 1; count <= SIM_LENGTH; count++)
    { 
      read(sock, &value, 4);
      printf("Client has received %d from socket.\n", value);
    }

  printf("Exiting now.\n");

  close(sock); 
  exit(0); 

} 
