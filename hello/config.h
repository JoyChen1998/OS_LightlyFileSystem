#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <vector>
#include <stack>
using namespace std;

const long int fileMaxSize = 0x3f3f3f;

const string ending = "Bye Bye";
const string cmd_err = "Command Not Found:";
const string input_msg = "Please Input A Command";
const string rm_err = "rm: cannot remove it : No such file or directory";

bool haveFile = false;
string choice;
string userSet[11];


class user{
private:
    string username;
    string password;
    string authority;
    bool canMoAu;
public:
    void CreateUsr(string usrnm,string pswd,string auth);
    void deleteUsr(string del);
    void setPasswd(string pswd);
    void setUsrname(string usrnm);
    void setAuthority(string auth);
    void changePasswd();
    string getUsrPswd();
    string getUsrname();
    string getUsrAuth();
    
};


struct node{
    int fsize;
    string name;
    string content;
    string lastOpTime;
    string auth;
    string owner;
    char filter[5];
    struct node *pre;
    struct node *next;
    struct node *innerp;
    struct node *upper;
};


const string commands[] = {
    "ls","cd","ll","clear","chmod","pwd",
    "useradd","cat","vim","touch",
    "su","exit","rm","mkdir","rmuser"
};

void passwd();
void ll();
void ls();
void pwd();
void exit();
void useradd();
void logout();
void cd(string path);
void chmod(string attribute);
void cat(string filename);
void vim(string filename);
void su(string x);
void touch(string filename);
void rm(string filename);
void mkdir(string dirname);
void init();
void greet_msg();
string auth_digit_to_alpha(string x);
void createUser(int w);
void menu();
void split(const string& src, const string& separator, vector<string>& dest);
node *createNode(node *head,string x,int istc);
node *createNode_dir(node *head,string x);
node *insertNode(node *head,string x,int istc);
node *insertNode_dir(node *head,string x);
node *removeNode(node *head, string x);
void catNode(node *head, string x);
void showNodeList(node *head, int flag);
bool ModifyFile(node *head, const string &x);
void run();
void changeAuth(node *head, string x, string flag);
bool ckAuth(node *head, const string &x, int flag);
string getCurnt_Auth();
void createRootDir();
string getCurrentTimeStr();
void rmuser();

const string menu_msg[] ={
    " \t\t*****************************************************************************\n"
    " \t\t*                           Commands Are Here                               *\n"
    " \t\t*****************************************************************************\n"
    " \t\t*                                ls                                         *\n"
    " \t\t*                                ll                                         *\n"
    " \t\t*                                cd                                         *\n"
    " \t\t*                                chmod                                      *\n"
    " \t\t*                                pwd                                        *\n"
    " \t\t*                                useradd                                    *\n"
    " \t\t*                                passwd                                     *\n"
    " \t\t*                                cat                                        *\n"
    " \t\t*                                vim                                        *\n"
    " \t\t*                                touch                                      *\n"
    " \t\t*                                su                                         *\n"
    " \t\t*                                exit                                       *\n"
    " \t\t*                                rm                                         *\n"
    " \t\t*                                rmuser                                     *\n"
    " \t\t*                                mkdir                                      *\n"
    " \t\t*****************************************************************************\n"
};


#endif // CONFIG_H_INCLUDED
