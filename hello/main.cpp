#include "config.h"
/*
 author: JoyChenCN
 github: https://github.com/JoyChen1998
 */
#define stringlen(x) sizeof(x)/sizeof(x[0])
#define for0(x, n) for(int x = 0 ; x < n ; x++)
#define for1(x, n) for(int x = 1 ; x < n ; x++)
#define for_str0(x, n) for(string::size_type x = 0; x < n ; x++)
#define for_str1(x, n) for(string::size_type x = 1; x < n ; x++)
#define for_uns0(x, n) for(unsigned int x = 0; x < n; x++)
#define PAUSE cout<<"\t\tPress Enter key to continue..."; fgetc(stdin);
#define setCurtTime  time_t curtime; time(&curtime);
#define TAB "\t\t"
using namespace std;

user user[10];
int user_cnt = 0;
int dirLevel = 0;
bool init_finish = false;
bool is_root = false;
node *head = nullptr;
node *dirGo = nullptr;
node *saveHead = head;
string curnt_user;
string curnt_auth;
string curnt_path[10];
node* pwdlsit[10];
int listcnt = 2;

string getCurrentTimeStr() {
    time_t t = time(nullptr);
    char ch[64] = {0};
    strftime(ch, sizeof(ch) - 1, "%m-%d %Y", localtime(&t));
    return ch;
}

void user::CreateUsr(const string usrnm, const string pswd, const string auth) {
    this->setUsrname(usrnm);
    this->setPasswd(pswd);
    this->setAuthority(auth);
    setCurtTime;
    cout << TAB << "  Create " << usrnm << " Successfully on " << ctime(&curtime) << endl;
}

void user::setUsrname(const string username) {
    this->username = username;
}

void user::setPasswd(const string paswd) {
    this->password = paswd;
}

void user::setAuthority(const string auth) {
    this->authority = auth;
}

string user::getUsrname() {
    return this->username;
}

string user::getUsrPswd() {
    return this->password;
}

string user::getUsrAuth() {
    return this->authority;
}

void user::changePasswd() {
    string passwrd;
    while (true) {
        char pswd[20];
        char passwd[20];
        cout << TAB;
        gets(pswd);
        cout << TAB << "Second Input" << endl;
        cout << TAB;
        gets(passwd);
        if (strcmp(pswd, "") != 0 && strcmp(pswd, passwd) == 0) {
            passwrd = passwd;
            break;
        }
        cout << TAB << "Error: The code you enter twice must be the same and not be null. Try Again!" << endl;
    }
    this->password = passwrd;
    cout << TAB << TAB << "*Change Password Successfully!*" << endl;
    cout << endl;
}

void user::deleteUsr(string del) {
    for_str1(i,stringlen(userSet)){
        if(userSet[i] == del){
            userSet[i] = "";
        }
    }
}

void createUser(int w) {
    string usrname;
    char passwd[20];
    string passwrd;
    string auth = "755";
    if (w == 0) {
        usrname = "root";
        auth = "777";
        is_root = true;
        curnt_user = usrname;
        curnt_auth = auth;
    } else {
        cout << TAB << "Please Input Your Username" << endl;
        while (true) {
            int i = 0;
            cout << TAB;
            cin >> usrname;
            getchar();
            for (i = 0; i < stringlen(userSet); i++) {
                if (userSet[i] == usrname) {
                    cout << "This Account Has Already Existed! Please Try Another" << endl;
                    return;
                }
            }
            if (i == stringlen(userSet)) {
                break;
            }
        }
    }
    cout << endl;
    cout << TAB << "Please Input Your Password Twice" << endl;
    //    getchar();
    while (true) {
        char pswd[20];
        cout << TAB;
        gets(pswd);
        cout << TAB << "Second Input" << endl;
        cout << TAB;
        gets(passwd);
        if (strcmp(pswd, "") != 0 && strcmp(pswd, passwd) == 0) {
            passwrd = passwd;
            break;
        }
        cout << TAB << "Error: The code you enter twice must be the same and not be null. Try Again!" << endl;
    }
    user[w].CreateUsr(usrname, passwrd, auth);
    for(int i = 0 ; i < 10; i++){
        if(userSet[i] == ""){
            userSet[i] = user[w].getUsrname();
            break;
        }
    }
    if(w == 0){
        for (int i = 3; i > 0; i--) {
            cout << TAB << TAB << "After " << i << " Seconds To Enter The System" << endl;
            sleep(1);
        }
    }
}

void menu() {
    system("clear");
    for_str0(i, stringlen(menu_msg)) {
        cout << menu_msg[i] << endl;
    }
    cout << TAB << input_msg << endl;
}

void split(const string &src, const string &separator, vector<string> &dest) {
    const string &str = src;
    string substring;
    string::size_type start = 0, index;
    dest.clear();
    index = str.find_first_of(separator, start);
    do {
        if (index != string::npos) {
            substring = str.substr(start, index - start);
            dest.push_back(substring);
            start = index + separator.size();
            index = str.find(separator, start);
            if (start == string::npos)
                break;
        }
    } while (index != string::npos);
    substring = str.substr(start);
    dest.push_back(substring);
}


node *createNode(node *head, string x, int istc) {
    node *p1, *p2;
    p1 = new node();
    p2 = new node();
    p1->name = x;
    p1->owner = curnt_user;
    if (!istc) {
        cout << TAB << "Please input content" << endl;
        cout << TAB;
        cin >> p1->content;
    }
    if (is_root)
        p1->auth = "f755";
    else
        p1->auth = "f644";
    p1->lastOpTime = getCurrentTimeStr();
    p1->next = nullptr;
    p1->pre = head;
    if (head == nullptr)
        head = p1;
    else
        p2->next = p1;
    p2 = p1;
    getchar();
    return head;
}

node *createNode_dir(node *head, string x) {
    node *p1, *p2;
    node *in = new node();
    p1 = new node();
    p2 = new node();
    in = nullptr;
    p1->name = x;
    p1->pre = nullptr;
    p1->owner = curnt_user;
    p1->innerp = in;
    p1->fsize = 4096;
    if (is_root)
        p1->auth = "d755";
    else
        p1->auth = "d644";
    p1->lastOpTime = getCurrentTimeStr();
    p1->next = nullptr;
    if (head == nullptr)
        head = p1;
    else
        p2->next = p1;
    p2 = p1;
    return head;
}


node *insertNode(node *head, string x, int istc) {              // istc = 1 => touch |  istc = 0 => vim
    if (ModifyFile(head, x)) {
        return head;
    }
    node *newnode = new node();
    newnode->next = nullptr;
    newnode->name = x;
    newnode->owner = curnt_user;
    newnode->upper = head;
    if (is_root)
        newnode->auth = "f755";
    else
        newnode->auth = "f644";
    newnode->lastOpTime = getCurrentTimeStr();
    if (!istc) {
        cout << "Please input content" << endl;
        cout << TAB;
        cin >> newnode->content;
    }
    node *p = new node();
    p = head;
    if (head == nullptr) {
        head = newnode;
    } else {
        while (p->next != nullptr)
            p = p->next;
        newnode->pre = p;
        p->next = newnode;
    }
    getchar();
    return head;
}


node *insertNode_dir(node *head, string x) {
    node *newnode = new node();
    node *in = new node();
    in = nullptr;
    newnode->next = nullptr;
    newnode->name = x;
    newnode->innerp = in;
    newnode->owner = curnt_user;
    newnode->fsize = 4096;
    newnode->upper = head;
    if (is_root)
        newnode->auth = "d755";
    else
        newnode->auth = "d644";
    newnode->lastOpTime = getCurrentTimeStr();
    node *p = new node();
    p = head;
    if (head == nullptr) {
        head = newnode;
    } else {
        while (p->next != nullptr)
            p = p->next;
        newnode->pre = p;
        p->next = newnode;
    }
    return head;
}

node *removeNode(node *head, string x) {
    node *pNode = head;
    node *deleteNode = nullptr;
    if (head == nullptr) {
        cout << "Error: Empty" << endl;
        return nullptr;
    } else if (head->content == x) {
        deleteNode = head;
        head = head->next;
    } else {
        while (pNode->next != nullptr && pNode->next->name != x)
            pNode = pNode->next;
        if (pNode->next != nullptr && pNode->next->name == x) {
            deleteNode = pNode->next;
            pNode->next = pNode->next->next;
            //            pNode->next->pre = pNode;
        }
    }
    if (deleteNode != nullptr) {
        delete deleteNode;
        deleteNode = nullptr;
    }
    return head;
}

void catNode(node *head, string x) {
    node *pNode = head;
    if (pNode == nullptr)
        return;
    
    else {
        cout << TAB;
        while (pNode->next != nullptr) {
            if (pNode->name == x) {
                if (!ckAuth(head, x, 1)) {
                    cout << TAB << "READ Permission Denied!" << endl;
                    getchar();
                    return;
                }
                cout << TAB << pNode->content << endl;
                return;
            }
            pNode = pNode->next;
        }
        if (pNode->name == x) {
            cout << TAB << pNode->content << endl;
            return;
        }
        if (pNode->name != x) {
            cout << "Error : Can't find it " << endl;
        }
    }
}

void changeAuth(node *head, string x, string flag) {
    node *pNode = head;
    const char *p = flag.data();
    for_uns0(i, strlen(p)) {
        if (p[i] < '0' || p[i] > '7') {
            cout << TAB << "The auth that you input does not correct!" << endl;
            getchar();
            return;
        }
    }
    if (pNode == nullptr)
        return;
    else {
        while (pNode->next != nullptr) {
            if (pNode->name == x) {
                pNode->auth.replace(1, 3, flag);
                cout << "Change Successfully" << endl;
                getchar();
                return;
            }
        }
        if (pNode->name == x) {
            pNode->auth.replace(1, 3, flag);
            cout << "Change Successfully" << endl;
            getchar();
            return;
        }
        cout << "Can't Find the File" << endl;
        getchar();
    }
}

string auth_digit_to_alpha(string x) {
    const char *p = x.data();
    string s;
    for_uns0(i, strlen(p)) {
        if (p[i] == '1')
            s.append("--x");
        else if (p[i] == '2')
            s.append("-w-");
        else if (p[i] == '3')
            s.append("-wx");
        else if (p[i] == '4')
            s.append("r--");
        else if (p[i] == '5')
            s.append("r-x");
        else if (p[i] == '6')
            s.append("rw-");
        else if (p[i] == '7')
            s.append("rwx");
        else if (p[i] == '0')
            s.append("---");
        else if (p[i] == 'f')
            s.append("-");
        else if (p[i] == 'd')
            s.append("d");
    }
    return s;
}

void showNodeList(node *head, int flag) {
    node *pNode = head;
    if (pNode == nullptr) {
        cout <<TAB<< "Don't exist any files" << endl;
        return;
    } else {
        if (flag) {
            while (pNode->next != nullptr) {
                
                int maxSize = (int) pNode->content.size() > pNode->fsize ? (int) pNode->content.size() : pNode->fsize;
                printf("\t\t%5s %5s %6dB %12s %7s\n", auth_digit_to_alpha(pNode->auth).data(), pNode->owner.data(),
                       maxSize, pNode->lastOpTime.data(), pNode->name.data());
                pNode = pNode->next;
            }
            int maxSize = (int) pNode->content.size() > pNode->fsize ? (int) pNode->content.size() : pNode->fsize;
            printf("\t\t%5s %5s %6dB %12s %7s\n", auth_digit_to_alpha(pNode->auth).data(), pNode->owner.data(),
                   maxSize, pNode->lastOpTime.data(), pNode->name.data());
        } else {
            while (pNode->next != nullptr) {
                printf("\t\t%s ", pNode->name.data());
                pNode = pNode->next;
            }
            printf("\t\t%s\n", pNode->name.data());
        }
    }
    //    getchar();
}

string getCurnt_Auth() {
    string tmp_auth;
    for_str0(i, stringlen(user)) {
        if (user[i].getUsrname() == curnt_user) {
            tmp_auth = user[i].getUsrAuth();
        }
    }
    return tmp_auth;
}

bool ckAuth(node *head, const string &x, int flag) {
    node *pNode = head;
    string auth = getCurnt_Auth();
    if (pNode == nullptr) {
        cout << "Don't exist any files" << endl;
        return false;
    } else {
        if (curnt_user == "root")
            return true;
        while (pNode->next != nullptr) {
            if (pNode->name == x) {
                const char authority_x = curnt_auth.data()[1];
                const char authority_pNode = pNode->auth.data()[2];
                if (authority_pNode == authority_x)
                    return true;
                if ((authority_x >= '4' || authority_pNode >= '4') && flag == 1)   // flag = 1   read
                    return true;
                if ((authority_x >= '6' || authority_pNode >= '6') && flag == 0)   // flag = 0   write
                    return true;
                
            }
            pNode = pNode->next;
        }
        if (pNode->name == x) {
            const char authority_x = curnt_auth.data()[1];
            const char authority_pNode = pNode->auth.data()[2];
            if (authority_pNode == authority_x)
                return true;
            if ((authority_x >= '4' || authority_pNode >= '4') && flag == 1)   // flag = 1   read
                return true;
            if ((authority_x >= '6' || authority_pNode >= '6') && flag == 0)   // flag = 0   write
                return true;
        }
    }
    return false;
}

bool ModifyFile(node *head, const string &x) {
    node *pNode = head;
    if (pNode == nullptr)
        return false;
    else {
        cout << TAB;
        while (pNode->next != nullptr) {
            if (pNode->name == x) {
                if (!ckAuth(head, x, 1)) {
                    cout << TAB << "READ Permission Denied!" << endl;
                    getchar();
                    return true;
                }
                cout << "origin file content:";
                cout << pNode->content << endl;
                cout << TAB << "Please input the new content" << endl;
                cout << TAB;
                string content;
                cin >> content;
                if (!ckAuth(head, x, 0)) {
                    cout << TAB << "WRITE Permission Denied!" << endl;
                    getchar();
                    return true;
                }
                pNode->content = content;
                pNode->lastOpTime = getCurrentTimeStr();
                getchar();
                return true;
            }
            pNode = pNode->next;
        }
        if (pNode->name == x) {
            if (!ckAuth(head, x, 1)) {
                cout << TAB << "READ Permission Denied!" << endl;
                getchar();
                return true;
            }
            cout << "origin file content:"<< TAB;
            cout << pNode->content << endl;
            cout << TAB << "Please input the new content" << endl;
            cout << TAB;
            string content;
            cin >> content;
            if (!ckAuth(head, x, 0)) {
                cout << TAB << "WRITE Permission Denied!" << endl;
                getchar();
                return true;
            }
            pNode->content = content;
            pNode->lastOpTime = getCurrentTimeStr();
            getchar();
            return true;
        }
        
    }
    return false;
}

void run() {
    string x;
    while (true) {
        if (is_root)
            cout << TAB <<curnt_user<<"#";
        else
            cout << TAB <<curnt_user<<"$";
        string choice;
        choice = "";
        getline(cin, choice);
        vector<string> text;
        if (choice.find(' ') != string::npos) {
            split(choice, " ", text);
            x = text[1];
        }
        if (choice.find("ll") != string::npos && choice.size() == 2) {
            ll();
        } else if (choice.find("ls") != string::npos && choice.size() == 2) {
            ls();
        } else if (choice.find("cd") != string::npos) {
            cd(x);
        } else if (choice.find("chmod") != string::npos) {
            chmod(x);
        } else if (choice.find("pwd") != string::npos && choice.size() == 3) {
            pwd();
        } else if (choice.find("useradd") != string::npos && choice.size() == 7) {
            useradd();
        } else if (choice.find("cat") != string::npos) {
            cat(x);
        } else if (choice.find("vim") != string::npos) {
            vim(x);
        } else if (choice.find("touch") != string::npos) {
            touch(x);
        } else if (choice.find("rmuser") != string::npos && choice.size() == 6) {
            rmuser();
        } else if (choice.find("su") != string::npos) {
            su(x);
        } else if (choice.find("exit") != string::npos && choice.size() == 4) {
            if (!is_root) {
                logout();
                break;
            }
            exit();
        } else if (choice.find("passwd") != string::npos && choice.size() == 6) {
            passwd();
        } else if (choice.find("clear") != string::npos && choice.size() == 5) {
            system("clear");
        } else if (choice.find("logout") != string::npos) {
            logout();
            break;
        } else if (choice.find("rm") != string::npos) {
            rm(x);
        } else if (choice.find("mkdir") != string::npos) {
            mkdir(x);
        } else {
            if (!choice.empty())
                cout << TAB << cmd_err << choice << endl;
        }
        x = "";
    }
}

void greet_msg() {
    cout << "\t\t***********************************************************************************" << endl;
    cout << "\t\t  Hi Guys ! This Is A Light-weight File System That Models Linux Made By JoyChan!" << endl;
    cout << "\t\t***********************************************************************************" << endl;
    cout << endl;
    cout << TAB<<"@Github: https://github.com/JoyChen1998" <<endl;
}

void createRootDir() {
    head = createNode_dir(head,"");
    head->innerp = insertNode_dir(head->innerp, "home");
    head->innerp->innerp = insertNode_dir(head->innerp->innerp, "root");
    head->innerp = insertNode_dir(head->innerp, "data");
    head->innerp = insertNode_dir(head->innerp, "lib");
    head->innerp = insertNode_dir(head->innerp, "sys");
    head->innerp = insertNode_dir(head->innerp, "proc");
    head->innerp = insertNode_dir(head->innerp, "run");
    head->innerp = insertNode_dir(head->innerp, "dev");
    head->innerp = insertNode_dir(head->innerp, "etc");
    head->innerp = insertNode_dir(head->innerp, "mnt");
    head->innerp = insertNode_dir(head->innerp, "var");
    head->innerp = insertNode_dir(head->innerp, "usr");
    head->innerp->innerp->upper = head->innerp;
    dirGo = head->innerp->innerp->innerp;
    saveHead = head->innerp->innerp;
    pwdlsit[0] = head->innerp;
    pwdlsit[1] = head->innerp->innerp;
    pwdlsit[2] = head->innerp->innerp->innerp;
    curnt_path[0] = head->name;
    curnt_path[1] = head->innerp->name;
    curnt_path[2] = head->innerp->innerp->name;
    
}

void init() {
    greet_msg();
    PAUSE;
    cout << TAB << "First,let's set a root account to login the system!" << endl;
    createUser(0);
    createRootDir();
    init_finish = true;
}

void vim(string filename) {
    if (filename.empty()) {
        cout << TAB << "No File Operate" << endl;
        return;
    } else {
        if (!haveFile) {
            dirGo = createNode(dirGo, filename, 0);
            haveFile = true;
        } else {
            dirGo = insertNode(dirGo, filename, 0);
        }
        //        showNodeList(head, 1);
    }
}

void touch(string filename) {
    if (filename.empty()) {
        cout << TAB << "No File Operate" << endl;
        return;
    } else {
        if (!haveFile) {
            dirGo = createNode(dirGo, filename, 1);
            haveFile = true;
        } else {
            dirGo = insertNode(dirGo, filename, 1);
        }
        //        showNodeList(head, 0);
    }
}

void su(string x) {
    if (x.empty()) {
        if (is_root) {
            cout << TAB << "You're already the root user" << endl;
        } else {
            cout << TAB << "Password:";
            string pswd;
            int cnt = 3;
            while (cnt--) {
                cin >> pswd;
                if (pswd == user[0].getUsrPswd()) {
                    is_root = true;
                    break;
                }
            }
            if (cnt == -1) {
                cout << "Error: Password Wrong." << endl;
                getchar();
                return;
            }
            getchar();
            curnt_user = userSet[0];
        }
    } else {
        int i = 0;
        for (i = 0; i < stringlen(userSet); i++) {
            if (userSet[i] == x) {
                curnt_user = x;
                curnt_auth = getCurnt_Auth();
                if (i != 0)
                    is_root = false;
                return;
            }
        }
        if (i == stringlen(userSet)) {
            cout <<TAB << "this user does not exist" << endl;
            return;
        }
        
    }
}

void logout() {
    cout << ending << endl;
}

void rm(string filename) {
    if (filename.empty()) {
        cout << rm_err << endl;
        return;
    }
    dirGo = removeNode(dirGo, filename);
}

void passwd() {
    for_str0(i, stringlen(user)) {
        if (user[i].getUsrname() == curnt_user) {
            cout << "Changing password for user " << curnt_user << "." << endl;
            user[i].changePasswd();
        }
    }
}

void rmuser(){
    if(curnt_user != "root"){
        cout<<"Permission denied!"<<endl;
        return;
    }
    user_cnt--;
    cout<<TAB<<"Please input the username TO DELETE"<<endl;
    string userdel;
    cout<<TAB;
    cin>>userdel;
    
    for0(i, stringlen(userSet)){
        if(userSet[i] == userdel){
            user[0].deleteUsr(userdel);
        }
    }
    getchar();
}

void mkdir(string dirname) {
    if (dirname.empty()) {
        cout << "No DirName" << endl;
        getchar();
        return;
    }
    
    if (!haveFile || !init_finish) {
        createNode_dir(dirGo, dirname);
    } else {
        insertNode_dir(dirGo, dirname);
    }
    //    showNodeList(head, 0);
}

void exit() {
    if (is_root) {
        is_root = false;
        cout << TAB << "*exit root mode*" << endl;
        return;
    } else {
        logout();
    }
}


void pwd() {
    cout<<TAB;
    for_str0(i,listcnt+1){
        cout<<curnt_path[i]<<"/";
    }
    cout<<endl;
}

void useradd() {
    user_cnt++;
    if(user_cnt < 10)
        createUser(user_cnt);
    else
        cout<<TAB <<" Error: user_list is full!"<<endl;
}

void cat(string fileName) {
    catNode(dirGo, std::move(fileName));
    
}

void chmod(string filename) {
    if(curnt_user != "root"){
        cout<<"Permission denied!"<<endl;
        return;
    }
    cout << TAB << "Please Input The change of auth To the file" << endl;
    cout << TAB;
    string flag;
    cin >> flag;
    while (flag.length() != 3) {
        cout << "Illegal Input , Please Input Again!" << endl;
        cin >> flag;
    }
    changeAuth(dirGo, std::move(filename), flag);
}

void cd(string path) {
    node *tmp = dirGo;
    if (path.empty())
        return;
    vector<string> path_chips;
    split(path, "/", path_chips);
    for0(i,path_chips.size()){
        if(path_chips[i] == ".")
            continue;
        else if (path_chips[i] == ".."){
            if(listcnt == 0) {
                cout << TAB << "This is the bottom directory!" << endl;
                return;
            }
            dirGo = pwdlsit[--listcnt];
            while(dirGo->pre!= nullptr)
                dirGo = dirGo->pre;
        }else{
            tmp = dirGo;
            while(tmp->next != nullptr){
                if(tmp->name == path_chips[i]){
                    pwdlsit[listcnt++] = dirGo;
                    curnt_path[listcnt] = path_chips[i];
                    dirGo = tmp->innerp;
                }
                tmp = tmp->next;
            }
            if(tmp->name == path_chips[i]){
                pwdlsit[listcnt++] = tmp;
                curnt_path[listcnt] = path_chips[i];
                dirGo = tmp->innerp;
                continue;
            }
            break;
        }
    }
}

void ls() {
    showNodeList(dirGo, 0);
}

void ll() {
    showNodeList(dirGo, 1);
}

int main() {
    init();
    menu();
    run();
    return 0;
}

