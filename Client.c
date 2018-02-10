#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>

#include <arpa/inet.h>
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
  int socket_fd , cc=-1, dsize;
  struct sockaddr_in  dest;
  struct hostent *hostptr;
  unsigned char buffer[256];
  char *data = argv[2];
  
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);
  memset((char *) &dest,0, sizeof(dest));       /* Initial dest pointer to zero*/
  hostptr = gethostbyname(argv[1]);             /*Get des IP*/
  dest.sin_family = (short) AF_INET;            /*IPV4*/
  memcpy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length); 
  dest.sin_port = htons((unsigned short)0x3333);
 
  /*Send the message through socket*/
  sendto(socket_fd,data,sizeof(data),0,(struct sockaddr *)&dest,sizeof(dest));
  printf("Client sent: %s\n", data);
  
  return 0;
}
