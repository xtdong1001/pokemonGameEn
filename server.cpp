#include"server.h"
using namespace BOT_ORM;
using namespace BOT_ORM::Expression;

int server(LPVOID  lparam)
{
    SOCKET sClient = (SOCKET)(LPVOID)lparam; 
    int    retVal;  

    user   userT; 
    elf    elfT;  
    auto   field = FieldExtractor{ userT, elfT };
    ORMapper mapper("user.db");

    try
    {
        mapper.CreateTbl(user{});
        mapper.CreateTbl(elf{});
    }
    catch (...)
    {
    }

    char recvBuf[BUF_SIZE] = { '\0' };  
    char sendBuf[BUF_SIZE] = { '\0' }; 
    std::string stName = "";			
    std::string updateName = "";	
    std::string sychroName = "";		
    int totalSendTimes = 0;				
    int sendTimes = 0;				

    while (true)
    {
        retVal = recv(sClient, recvBuf, BUF_SIZE, 0);

        if (SOCKET_ERROR == retVal)
        {
            std::cout << "recv failed!\n";
            return -1;
        }

        char passwordBuf[maxLength] = { '\0' };
        char userNameBuf[maxLength] = { '\0' };

        if (SIGNUP_NAME == recvBuf[0])
        {
            strncpy_s(userNameBuf, recvBuf + 1, maxLength);

            std::string stNameBuf(&userNameBuf[0], &userNameBuf[strlen(userNameBuf)]);

            stName = stNameBuf;

            std::cout << "sign up name: " << stName << "\n";

            auto result = mapper.Query(user{})
                .Where(field(userT.userName) == stNameBuf)//string
                .ToVector();

            if (0 == result.size())//length
            {
                sendBuf[0] = SUCCESS;
            }
            else
            {
                sendBuf[0] = FAILURE;

                stName = "";
            }
        }

        else if (SIGNUP_PASSWORD == recvBuf[0])
        {
            strncpy_s(passwordBuf, recvBuf + 1, maxLength);

            std::string stPasswordBuf(&passwordBuf[0], &passwordBuf[strlen(passwordBuf)]);
            std::cout << "sign up password: " << stPasswordBuf << "\n";


            mapper.Insert(user{ stName, stPasswordBuf, online, 0, 0 });

            sendBuf[0] = SUCCESS;

            srand((int)time(NULL));

            for (int i = 0; i < 3; i++)
            {
                int p = rand() % 8 + 1;
                sendBuf[i + 1] = p;

                mapper.Insert(elf{ 0, stName, p, 1, 0 }, false);
            }

            stName = "";
        }

        else if (LOGIN_NAME == recvBuf[0])
        {
            strncpy_s(userNameBuf, recvBuf + 1, maxLength);

            std::string stNameBuf(&userNameBuf[0], &userNameBuf[strlen(userNameBuf)]);

            stName = stNameBuf;
            std::cout << "log in name: " << stName << "\n";

            sendBuf[0] = SUCCESS;
        }

        else if (LOGIN_PASSWORD == recvBuf[0])
        {
            strncpy_s(passwordBuf, recvBuf + 1, maxLength);

            std::string stPasswordBuf(&passwordBuf[0], &passwordBuf[strlen(passwordBuf)]);
            std::cout << "log in password: " << stPasswordBuf << "\n";

            auto result = mapper.Query(user{})
                .Where(field(userT.userName) == stName)
                .ToVector();

            if (0 == result.size())
            {
                sendBuf[0] = FAILURE;
                sendBuf[1] = INEXISTENCE;
            }
            else if (result[0].passWord == stPasswordBuf)//length
            {
                if (result[0].state == offline)
                {
                    mapper.Update(user{},
                        (field(userT.state) = online),
                        field(userT.userName) == stName);
                    sendBuf[0] = SUCCESS;
                    updateName = stName;
                }
                else
                {
                    sendBuf[0] = FAILURE;
                    sendBuf[1] = ALREADYONLINE;
                }
            }
            else
            {
                sendBuf[0] = FAILURE;
                sendBuf[1] = PASSWORDERROR;//ÃÜÂë´íÎó
            }
            stName = "";
        }

        else if (LOGOUT_REQ == recvBuf[0])
        {
            strncpy_s(userNameBuf, recvBuf + 1, maxLength);

            std::string stNameBuf(&userNameBuf[0], &userNameBuf[strlen(userNameBuf)]);
            std::cout << "log out name: " << stNameBuf << "\n";


            auto result = mapper.Query(user{})
                .Where(field(userT.userName) == stNameBuf)//string
                .ToVector();

            if (0 == result.size())//length
            {
                sendBuf[0] = FAILURE;
                sendBuf[1] = FAILURE;  
            }

            else if (result[0].state == online)
            {
                mapper.Update(user{},
                    (field(userT.state) = offline),
                    field(userT.userName) == stNameBuf);
                sendBuf[0] = SUCCESS;

                sychroName = stNameBuf;

                mapper.Delete(elf{}, field(elfT.userName) == sychroName);
            }
            else
            {
                sendBuf[0] = FAILURE;
                sendBuf[1] = OFFLINE;
            }
        }

        else if (SEARCHUSER_REQ == recvBuf[0])
        {
            auto result = mapper.Query(user{})
                .Where(field(userT.state) == online)//string
                .ToVector();

            if (0 == result.size())
            {
                sendBuf[0] = FAILURE;
            }

            else if (REQUEST == recvBuf[1])
            {
                totalSendTimes = int(result.size());

                strncpy(sendBuf + 1, result[sendTimes].userName.c_str(),
                    result[sendTimes].userName.length());

                sendTimes++;
                sendBuf[0] = SUCCESS;
            }

            else
            {
                if (sendTimes == totalSendTimes)
                {
                    sendBuf[0] = 0;
                    sendTimes = 0;
                    totalSendTimes = 0;
                }
                else
                {
                    sendBuf[0] = SUCCESS;
                    strncpy(sendBuf + 1, result[sendTimes].userName.c_str(),
                        result[sendTimes].userName.length());
                    sendTimes++;
                }
            }
        }//SEARCH ONLINE USER

        else if (SEARCHPOKEMON_REQ == recvBuf[0])
        {
            strncpy_s(userNameBuf, recvBuf + 1, maxLength);

            std::string stNameBuf(&userNameBuf[0], &userNameBuf[strlen(userNameBuf)]);
            std::cout << "query pokemon of a user: " << stNameBuf << "\n";

            auto result = mapper.Query(elf{})
                .Where(field(elfT.userName) == stNameBuf)//string
                .ToVector();

            if (0 == result.size())//length
            {
                sendBuf[0] = FAILURE;
            }
            else
            {
                sendBuf[0] = SUCCESS;
                for (int i = 0; i < (int)result.size(); i++)
                {
                    sendBuf[i + 1] = result[i].elfKind;
                }
            }
        }//SEARCH POKEMON

        else if (UPDATE_REQ == recvBuf[0])
        {
            auto result = mapper.Query(elf{})
                .Where(field(elfT.userName) == updateName)//string
                .ToVector();

            if (REQUEST == recvBuf[1])
            {
                totalSendTimes = int(result.size());

                char toStr[msgLength] = { '\0' };

                toString(toStr, result[sendTimes]);
                strncpy(sendBuf + 1, toStr, strlen(toStr));

                sendTimes++;
                sendBuf[0] = SUCCESS;
            }
            else
            {
                if (sendTimes == totalSendTimes)
                {
                    sendBuf[0] = FAILURE;
                    sendTimes = 0;
                    totalSendTimes = 0;
                }
                else
                {
                    sendBuf[0] = SUCCESS;

                    char toStr[msgLength] = { '\0' };

                    toString(toStr, result[sendTimes]);
                    strncpy(sendBuf + 1, toStr, strlen(toStr));
                    sendTimes++;
                }
            }
        }//UPDATE_REQ

        else if (SYNCHRONIZATION == recvBuf[0])
        {
            char elfInfo[msgLength] = { '\0' };
            int kind, level, exp;

            strncpy(elfInfo, recvBuf + 1, BUF_SIZE - 1);
            readInfo(elfInfo, kind, level, exp);

            mapper.Insert(elf{ 0, sychroName, kind, level, exp }, false);
        }//SYNCHRONIZATION

        else if (WINRATE_REQ == recvBuf[0])
        {
            strncpy_s(userNameBuf, recvBuf + 1, maxLength);

            std::string stNameBuf(&userNameBuf[0], &userNameBuf[strlen(userNameBuf)]);

            std::cout << "search for win rate: " << stNameBuf << "\n";

            auto result = mapper.Query(user{})
                .Where(field(userT.userName) == stNameBuf)//string
                .ToVector();

            if (0 == result.size())//length
            {
                sendBuf[0] = FAILURE;
            }
            else
            {
                sendBuf[0] = SUCCESS;

                char toStr[msgLength] = { '\0' };

                winRateStr(toStr, result[0].winNum, result[0].sumNum, 0);
                strncpy(sendBuf + 1, toStr, strlen(toStr));
            }
        }//WINRATE_REQ

        else if (SYNCHROWINRATE == recvBuf[0])
        {
            char winRate[msgLength] = { '\0' };
            int winN, sumN, useless;

            strncpy(winRate, recvBuf + 1, BUF_SIZE - 1);
            readInfo(winRate, winN, sumN, useless);

            mapper.Update(user{},
                (field(userT.winNum) = winN) && (field(userT.sumNum) = sumN),
                field(userT.userName) == sychroName);
        }//SYNCHROWINRATE

        else if (0 == recvBuf[0])
        {
            std::cout << "disconnected\n";
        }

        send(sClient, sendBuf, BUF_SIZE, 0);

        for (int i = 0; i < BUF_SIZE; i++)
        {
            sendBuf[i] = '\0';
            recvBuf[i] = '\0';
        }
    }//while(true)    
}
