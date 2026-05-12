#include <iostream>
#include <cstring>

using namespace std;

class Stack
{
private:
    typedef struct stack1
    {
        char data;
        struct stack1* next;
    } node;

    node* top;

public:
    Stack();
    ~Stack();

    void push(char, node**);
    char pop(node**);
    int stackempty(node*);
    void postfix();
};

int main()
{
    int ch;
    Stack st;

    do
    {
        cout << "\n1. Infix to Postfix";
        cout << "\n2. Exit";
        cout << "\nEnter your choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            st.postfix();
            break;

        case 2:
            break;

        default:
            cout << "\nInvalid choice";
        }

    } while (ch != 2);

    return 0;
}

Stack::Stack()
{
    top = NULL;
}

Stack::~Stack()
{
    node* temp;

    while (top != NULL)
    {
        temp = top;
        top = top->next;
        delete temp;
    }
}

void Stack::push(char x, node** top)
{
    node* newnode = new node;

    newnode->data = x;
    newnode->next = *top;
    *top = newnode;
}

char Stack::pop(node** top)
{
    if (*top == NULL)
        return '\0';

    char x = (*top)->data;

    node* temp = *top;
    *top = (*top)->next;

    delete temp;

    return x;
}

int Stack::stackempty(node* temp)
{
    if (temp == NULL)
        return 1;
    else
        return 0;
}

void Stack::postfix()
{
    char exp[40];
    char post[40];
    char ch;

    int length, j = 0;

    cout << "\nEnter expression: ";
    cin >> exp;

    length = strlen(exp);

    cout << "\nThe postfix is: ";

    for (int i = 0; i < length; i++)
    {
        ch = exp[i];

        if (ch == '(' || ch == '+' ||
            ch == '-' || ch == '*' ||
            ch == '/')
        {
            push(ch, &top);
        }
        else if (ch != ')')
        {
            post[j] = ch;
            j++;

            cout << ch;
        }
        else
        {
            do
            {
                ch = pop(&top);

                if (ch != '(')
                {
                    post[j] = ch;
                    j++;

                    cout << ch;
                }

            } while (ch != '(');
        }
    }

    post[j] = '\0';
}
