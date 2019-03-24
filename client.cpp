#include"pokemon.h"
using namespace std;

int client()
{
    WSADATA wsd;  
    SOCKET sHost; 
    SOCKADDR_IN servAddr;
    int retVal; 

    if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0) 
    {
        cout << "WSAStartup failed!" << endl;
        return -1;
    }
    sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (INVALID_SOCKET == sHost)
    {
        cout << "socket failed!" << endl;
        WSACleanup();
        return  -1;
    }

    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servAddr.sin_port = htons((short)4999);
    int nServAddlen = sizeof(servAddr);

    retVal = connect(sHost, (LPSOCKADDR)&servAddr, sizeof(servAddr));
    if (SOCKET_ERROR == retVal)
    {
        cout << "connect failed!" << endl;
        closesocket(sHost);
        WSACleanup(); //release 
        return -1;
    }
    cout << "connect!\n";

    while (stop == 0)
    {
        if (sendRequest == SEND)
        {
            // send info
            retVal = send(sHost, sendBuf, strlen(sendBuf), 0);
            if (SOCKET_ERROR == retVal)
            {
                cout << "send failed!" << endl;
                closesocket(sHost);  
                WSACleanup(); //release   
                return -1;
            }

            recv(sHost, recvBuf, BUF_SIZE, 0);

            //sending lock
            sendRequest = WAIT;
            //receiving lock
            receiveInfo = RECV;
        }
    }//stop==0  

     //exit  
    closesocket(sHost); //close socket  
    WSACleanup();       //clean up 

    //release threads
    return 0;
}