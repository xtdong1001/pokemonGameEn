#pragma once
#pragma warning (disable : 4996)
#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<windows.h>  
#include<winsock.h>
#include<winbase.h>
#include"ORMLite.h"
#include"sqlite3.h"
#pragma comment (lib,"ws2_32.lib")

const int BUF_SIZE = 64;  
const int maxLength = 14;
const int msgLength = 63; 

const int online = 1; 
const int offline = 0; 

const int SIGNUP_NAME = 1;       
const int SIGNUP_PASSWORD = 2;   
const int LOGIN_NAME = 3;        
const int LOGIN_PASSWORD = 4;    
const int LOGOUT_REQ = 5;        
const int SEARCHUSER_REQ = 6;   
const int SEARCHPOKEMON_REQ = 7; 
const int UPDATE_REQ = 8;        
const int SYNCHRONIZATION = 9;  
const int WINRATE_REQ = 10;      
const int SYNCHROWINRATE = 11;   

const int SUCCESS = 1;       
const int FAILURE = 0;       
const int PASSWORDERROR = 0; 
const int ALREADYONLINE = 1; 
const int INEXISTENCE = 2;  
const int REQUEST = 1;      
const int OFFLINE = 1;       


struct user
{
    std::string userName;
    std::string passWord;
    int state;			 
    int winNum;         
    int sumNum;			 
    ORMAP("user", userName, passWord, state, winNum, sumNum);
    
};

struct elf
{
    int primaryKey;
    std::string userName;
    int elfKind;  
    int level;     
    int exp;	  
    ORMAP("elf", primaryKey, userName, elfKind, level, exp);
};


int server(LPVOID);			
void toString(char*, elf);  				
void winRateStr(char*, int, int, int);  
void readInfo(char*, int&, int&, int&); 
void toChar(int, char*, int&);			
