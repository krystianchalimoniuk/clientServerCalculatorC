/****************** SERVER CODE ****************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "mb.h"

int main(){
  int welcomeSocket, newSocket;
  char buffer[1024];
  char dzialanie[8];
  float parameters[3];
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;
  float wynik;
  float (*funkcja)(float a, float b);
  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
  
  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */
  serverAddr.sin_port = htons(7891);
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  /*---- Bind the address struct to the socket ----*/
  bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  /*---- Listen on the socket, with 5 max connection requests queued ----*/
  if(listen(welcomeSocket,5)==0)
    printf("Listening\n");
  else
    printf("Error\n");

  /*---- Accept call creates a new socket for the incoming connection ----*/
  addr_size = sizeof serverStorage;
  newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
// try to get data
 

 
  while(1){
  recv(newSocket,parameters,sizeof(parameters),0);

   if(parameters[2]==1.0){//dodawanie
			funkcja = suma;
                        strcpy(dzialanie,"suma");
			wynik=wskNaFunkcje(parameters[0],parameters[1],funkcja);

		}
		else if(parameters[2]==2.0){     //odejmowanie
			funkcja = roznica;
                        strcpy(dzialanie,"roznica");
			wynik=wskNaFunkcje(parameters[0],parameters[1],funkcja);
		}
		else if(parameters[2]==3.0){     //mnozenie
			funkcja = iloczyn;
                        strcpy(dzialanie,"iloczyn");
			wynik=wskNaFunkcje(parameters[0],parameters[1],funkcja);
		}
		else if(parameters[2]==4.0){     //dzielenie
			funkcja = iloraz;
                       strcpy(dzialanie,"iloraz");
			wynik=wskNaFunkcje(parameters[0],parameters[1],funkcja);
		}
		else{
			wynik = 0;
		}
  printf("Odebrane liczby: %.2f, %.2f \n",parameters[0],parameters[1]);
  printf("Wybrane działanie: %s \n",dzialanie);

 /*---- Send message to the socket of the incoming connection ----*/
  send(newSocket,&wynik,sizeof(wynik),0);
   break;
  }
  return 0;
}
