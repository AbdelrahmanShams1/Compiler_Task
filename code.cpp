//------------------------------------------tiny parser---------------------------------------
#include <bits/stdc++.h>
using namespace std;
#define all(v) v.begin(), v.end()
#define Unique(v) sort(all(v)), v.resize(unique(all(v)) - v.begin())
set<string> keywords = {"int", "float", "if", "else", "while", "return", "for", "printf", "double", "char", "bool", "break", "continue", "byte", "switch", "define", "include", "main", "const"};
set<string> operators = {
    "+",
    "-",
    "*",
    "/",
    "=",
    ";",
    "(",
    ")",
    "{",
    "}",
    "&&",
    "||",
    "!",
    "<<",
    ">>",
    "%",
    "&",
    "|",
    "^",
    "~",
    "!",
    "==",
    "!=",
    "<",
    ">",
    "<=",
    ">=",
    "++",
    "--",
    "<<",
    ">>",
};
vector<string> kw_vec;
vector<string> id_vec;
vector<string> num_vec;
vector<string> op_vec;
string last; // op , id , key , num
int is_key(string &w)
{
    return keywords.find(w) != keywords.end(); // if iterator is equal end , it is not in vector
}
int is_op(string &op)
{
    return operators.find(op) != operators.end();
}
void let_analyze()
{
    string token;
    char c;
    while (cin.get(c))
    {
        if (c == '/' && cin.peek() == '/')
        {
            cout << "this is comment : /";
            while (cin.get(c) && c != '\n')
            {
                cout << c;
            }
            cout << '\n';
            continue;
        }

        if (c == '/' && cin.peek() == '*')
        {
            cout << "this is comment : /*";
            
            cin.get(c); 
            while (cin.get(c))
            {
                cout << c;
                if (c == '*' && cin.peek() == '/')
                {
                    cin.get(c); 
                    cout << c << '\n';
                    break;
                }
            }
            continue;
        }

        if (isspace(c))
            continue;

        if (isalpha(c))
        {
            token = c;
            while (cin.get(c) && (isalnum(c) || c == '_'))
            {
                token += c;
            }
            cin.putback(c);
            if (is_key(token))
            {
                kw_vec.push_back(token);
                last = "key";
            }
            else
            {
                if (last == "key")
                {
                    id_vec.push_back(token);
                    last = "id";
                }
            }
        }

        else if (isdigit(c))
        {
            token = c;
            while (cin.get(c) && (isdigit(c) || c == '.'))
            {
                token += c;
            }
            if (c == 'e' && isdigit(cin.peek()))
            {
                token += c;
                while (cin.get(c) && isdigit(c))
                {
                    token += c;
                }
            }
            else if (c == 'e' && (cin.peek() == '-' || cin.peek() == '+'))
            {
                token += c;
                cin.get(c);
                token += c;
                while (cin.get(c) && isdigit(c))
                {
                    token += c;
                }
            }
            cin.putback(c); // the last char that break the while , add it to input to check in next loop
            num_vec.push_back(token);
            last = "num";
        }
        else
        {
            token = c;
            // cin.peek()  for second char from input because i can't access the second char
            if (cin.peek() == '&' || cin.peek() == '|' || cin.peek() == '<' || cin.peek() == '>' || cin.peek() == '+' || cin.peek() == '-' || (token == "=" && cin.peek() == '='))
            {
                cin.get(c);
                token += c;
            }
            if (is_op(token))
            {
                op_vec.push_back(token);
                last = "op";
            }
        }
    }
}

int main()
{
    // to open input/output within a txt files
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    let_analyze();
    Unique(kw_vec); // to unique each element in vector
    Unique(id_vec);
    Unique(num_vec);
    Unique(op_vec);

    cout << "Keywords : ";
    for (string kw : kw_vec)
    {
        cout << kw << " ";
        if (kw_vec.back() == kw)
        {
            cout << '\n';
        }
    }

    cout << "\nIdentifiers : ";
    for (string id : id_vec)
    {
        cout << id << " ";
        if (id_vec.back() == id)
        {
            cout << '\n';
        }
    }

    cout << "\nNumeric Constants : ";
    for (string num : num_vec)
    {
        cout << num << " ";
        if (num_vec.back() == num)
        {
            cout << '\n';
        }
    }

    cout << "\nOperators : ";
    for (string op : op_vec)
    {
        cout << op << " ";
        if (op_vec.back() == op)
        {
            cout << '\n';
        }
    }

    return 0;
}
