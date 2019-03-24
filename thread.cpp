#include"server.h"

int main()
{
    WSADATA         wsd;             
    SOCKET          sServer;        
    SOCKET          sClient;        
    SOCKADDR_IN     addrServ;;     
    int             retVal;       

    if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
    {
        std::cout << "WSAStartup failed!\n";
        return 1;
    }

    sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (INVALID_SOCKET == sServer)
    {
        std::cout << "socket failed!\n";
        WSACleanup();
        return  -1;
    }

    addrServ.sin_family = AF_INET;
    addrServ.sin_port = htons(4999);
    addrServ.sin_addr.s_addr = INADDR_ANY;

    retVal = bind(sServer, (LPSOCKADDR)&addrServ, sizeof(SOCKADDR_IN));
    if (SOCKET_ERROR == retVal)
    {
        std::cout << "bind failed!\n";
        closesocket(sServer);  
        WSACleanup();          
        return -1;
    }

    retVal = listen(sServer, 1);
    if (SOCKET_ERROR == retVal)
    {
        std::cout << "listen failed!\n";
        closesocket(sServer);   
        WSACleanup();          
        return -1;
    }

    sockaddr_in addrClient;
    int addrClientlen = sizeof(addrClient);

    while (1)
    {
        sClient = SOCKET_ERROR;
        while (SOCKET_ERROR == sClient)
        {
            sClient = accept(sServer, (sockaddr FAR*)&addrClient, &addrClientlen);
        }

        DWORD  dwThreadId;
        HANDLE  hThread;

        hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)server,
            (LPVOID)sClient, 0, &dwThreadId);
        if (hThread == NULL)
        {
            printf("CreatThread failed.\n");
        }
        else
        {
            printf("CreateThread  OK.\n");
        }
    }

    closesocket(sServer);    
    WSACleanup();           
    return 0;
}