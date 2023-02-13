//202014048
#include<bits/stdc++.h>
#include "fstream"
using namespace std;
const int TABLE_SIZE = 10;
class symbolInfo
{
public:

    string  key;
    string value;

    symbolInfo* next;

    symbolInfo(string key, string value)
    {
        this->key = key;
        this->value = value;
        this->next = NULL;
    }
};

class SymbolTable
{
private:
    symbolInfo** hashT;

public:

    SymbolTable()
    {
        int i;
        hashT = new symbolInfo*[TABLE_SIZE];
        for (i = 0; i < TABLE_SIZE; i++)
        {
            hashT[i] = NULL;
        }

    }



    int HashFunction(string key)//hash technique
    {
        int current =0 ;
        int sum=0 ;

        while(key[current]!='\0')
        {
            for(int i=0;i<=current;i+=2){
                sum+= (key[current]-'0'<<8);//ID:202014048
                current++;
            }

        }
        return sum % TABLE_SIZE;
    }


    void Insert(string key, string value)
    {
        int hashValue = HashFunction(key);
        symbolInfo* prev = NULL;
        symbolInfo* entry = hashT[hashValue];

        while (entry != NULL)
        {
            prev = entry;
            entry = entry->next;
        }

        if (entry == NULL)
        {
            entry = new symbolInfo(key, value);
            if (prev == NULL)
            {
                hashT[hashValue] = entry;
            }
            else
            {
                prev->next = entry;
            }
        }

    }


    void Delete(string key)
    {
        int hashValue = HashFunction(key);
        symbolInfo* entry = hashT[hashValue];
        symbolInfo* prev = NULL;
        if (entry == NULL )
        {
            return;
        }
        while (entry != NULL)
        {
            if(entry->key == key)
            {
                break;
            }
            prev = entry;
            entry = entry->next;
        }

        if(prev != NULL)
        {
            prev->next = entry->next;
            cout << "Deleted" << endl;
            delete entry;
            delete prev;
            return;
        }
        else
        {
            hashT[hashValue] = entry->next;
            cout << "Deleted" << endl;
            delete entry;
            delete prev;
            return;
        }

        delete entry;
        delete prev;

        cout << "Element could not be deleted" << endl;
        return;
    }

    bool LookUp(string key)
    {
        bool flag = false;
        int hashValue = HashFunction(key);
        symbolInfo* entry = hashT[hashValue];

        while (entry != NULL)
        {
            if (entry->key == key)
            {
                cout<<entry->value<<" ";
                flag = true;
            }
            entry = entry->next;

        }
        return flag;
    }

    void Print()
    {
        for(int i=0; i < TABLE_SIZE ; i++)
        {
            symbolInfo* current_node = hashT[i];
            if(current_node == NULL)
            {
                continue;
            }

            else
            {
                cout << i << " --> " ;

                while(current_node != NULL)
                {
                    cout << "<" <<  current_node->key << "," << current_node->value << ">" << "  " ;
                    current_node = current_node->next;
                }
                cout << endl;
            }
        }
    }
};


void getKeyword(char str[10]){
    if(strcmp("if",str)==0||strcmp("else",str)==0||strcmp("for",str)==0||strcmp("while",str)==0||strcmp("break",str)==0||strcmp("int",str)==0||strcmp("char",str)==0||strcmp("float",str)==0||strcmp("double",str)==0||strcmp("return",str)==0||strcmp("include",str)==0) printf("\n%s is a keyword");
    else printf("\n%s is an identifier");
}
vector<pair<string,int>>vkey,vfun,vop,vid;
int main() {
    string inputs[10000];
    string s;
    char ch;
    char operators[] = "+-\*%=";
    int tmp = 0;
    SymbolTable sb;
    //cin>>str;

    ofstream file_1("output_function.txt");
    ofstream file_2("output_identifier.txt");
    ofstream file_3("output_keyword.txt");
    ofstream file_4("output_operator.txt");

    ifstream file("sample_input.txt");

    int ln = 1;
    while (getline(file, s)) {
        for (int i = 0; i < s.size(); i++) {
            if ((s[i] >= 'a' and s[i] <= 'z') or (s[i] >= 'A' and s[i] <= 'Z') or (s[i] >= '0' and s[i] <= '9')) {
                tmp += s[i];
            } else if (s[i] == '(') {
//                dbg1(tmp);
                if (getKeyword(tmp)) {
                    cout << "pushed into keyword-->" << tmp << " ln-->" << ln << endl;
                    sb.Insert(tmp, "KEYWORD", "string");
                    sb.print();
                    vkey.push_back({tmp, ln});
                } else {
                    if (tmp.size() > 0) {
                        cout << "pushed into function-->" << tmp << " ln-->" << ln << endl;
                        sb.Insert(tmp, "FUNCTION", "string");
                        sb.print();
                        vfun.push_back({tmp, ln});
                    }
                }
                tmp = "";
            } else if ((s[i] == '&' and s[i + 1] == '&') or (s[i] == '|' and s[i + 1] == '|') or
                       (s[i] == '=' and s[i + 1] == '=') or (s[i] == '!' and s[i + 1] == '=') or
                       (s[i] == '+' and s[i + 1] == '=') or (s[i] == '-' and s[i + 1] == '=') or
                       (s[i] == '*' and s[i + 1] == '=') or (s[i] == '/' and s[i + 1] == '=') or
                       (s[i] == '%' and s[i + 1] == '=')) {
                string str = "";
                str += s[i];
                str += s[i + 1];
                i++;
                cout << "pushed into operator-->" << str << " ln-->" << ln << endl;
                sb.Insert(str, "OPERATOR", "string");
                sb.Print();
                vop.push_back({str, ln});
            } else if (s[i] == '+' or s[i] == '-' or s[i] == '*' or s[i] == '/' or
                       (s[i] == '%' and s[i + 1] != 'd' and s[i + 1] != 's' and s[i + 1] != 'f' and s[i + 1] != 'c') or
                       s[i] == '!' or s[i] == '=') {
                cout << "pushed into operator-->" << s[i] << " ln-->" << ln << endl;
                string str = "";
                str += s[i];
                sb.Insert(str, "OPERATOR", "string");
                sb.print();
                vop.push_back({str, ln});

            } else getKeyword(tmp);
            if (tmp.size() > 1) getKeyword(tmp);

            ln++;
            for (auto it: vkey) {
                file_3 << it.first << " " << it.second << endl;
            }
            for (auto it: vfun) {
                file_1 << it.first << " " << it.second << endl;
            }
            for (auto it: vid) {
                file_2 << it.first << " " << it.second << endl;
            }
            for (auto it: vop) {
                file_4 << it.first << " " << it.second << endl;
            }

            file.close();

        }

        return 0;
    }
}