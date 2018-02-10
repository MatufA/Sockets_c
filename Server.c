#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void printsin(struct sockaddr_in *sin, char *pname, char* msg);

void printsin(struct sockaddr_in *sin, char *pname, char* msg){
	  printf("%s\n%s ip = %s , port = %d\n", pname, msg, inet_ntoa(sin->sin_addr) , sin->sin_port);
}

int main(int argc, char *argv[])
{
  int socket_fd, cc, fsize;
  struct sockaddr_in  s_in, from;
  struct { char head; unsigned long  body; char tail;} msg;
  unsigned char buffer[256];

  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);        /*Open socket*/
  memset((char *) &s_in,0, sizeof(s_in));             /* Initial dest pointer to zero*/

  s_in.sin_family = (short)AF_INET;                   /*IPV4*/
  s_in.sin_addr.s_addr = htonl(INADDR_ANY);           /* IP Adress */
  s_in.sin_port = htons((unsigned short)0x3332);      /*Port*/

  printsin( &s_in, "UDP-SERVER:", "Local socket is:"); /*Print IP and port*/
  fflush(stdout);

  bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in));    /*Pass the IP and socket to client*/

  while(true) {
    fsize = sizeof(from);
    cc = recvfrom(socket_fd,&buffer,sizeof(buffer),0,(struct sockaddr *)&from,&fsize);
    printf("Got data ::%s\n",buffer); 
	  printsin((struct sockaddr_in*)&from, "UDP-SERVER: ", "Packet from:");

    fflush(stdout);
  }
  
  return 0;
}

