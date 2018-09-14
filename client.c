/****************** CLIENT CODE ****************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>

  char dod[]="suma";
  char mno[]="iloczyn";
  char odej[]="roznica";
  char dzie[]="iloraz";
  char znak[1];
  float dzialanie;

int main(int argc, char *argv[]){
  int clientSocket;
  float wynik;
  float parameters[3];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;


  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  
  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */
  serverAddr.sin_port = htons(7891);
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  /*---- Connect the socket to the server using the address struct ----*/
  addr_size = sizeof serverAddr;
  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);


  

if(strcmp(dod,argv[4])==0){
	dzialanie=1.0;
        strcpy(znak,"+");
  }
  else if(strcmp(odej,argv[4])==0){
	dzialanie=2.0;
        strcpy(znak,"-");
  }
  else if(strcmp(mno,argv[4])==0){
	dzialanie=3.0;
        strcpy(znak,"*");
  }
  else if(strcmp(dzie,argv[4])==0){
	dzialanie=4.0;
        strcpy(znak,"/");
  }	
   
while(1){ 
  /*---- Sending parameters to server ----*/
  parameters[0]=atof(argv[2]);
  parameters[1]=atof(argv[3]);
  parameters[2]=dzialanie;


 
  send(clientSocket,parameters,sizeof(parameters),0); 
   
 /*---- Read the message from the server into the buffer ----*/
  recv(clientSocket,&wynik, sizeof(wynik), 0);

  /*---- Print the received message ----*/
   printf("%.2f %s %.2f = %.2f \n",parameters[0],znak,parameters[1],wynik);
 break;
}


  return 0;
}
