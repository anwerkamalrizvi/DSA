#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>


using namespace std;

class Transaction {
public:
  int id;
  double amt;
  string desc;
  int flag;

  Transaction(double a, string d) {
    amt = a;
    desc = d;
    id = 0;
    flag = 0;
  }

  Transaction() {
    id = 0;
    amt = 0;
    desc = "";
    flag = 0;
  }
};

class Node {
public:
  Transaction data;
  Node *next;

  Node(Transaction t) {
    data = t;
    next = NULL;
  }
};

class TransactionStack {
private:
  Node *top;
  int idCounter;

public:
  TransactionStack() {
    top = NULL;
    idCounter = 1;
  }

  void push(Transaction t) {
    if (t.desc.length() > 20) {
      t.desc = t.desc.substr(0, 17) + "...";
    }

    if (t.amt >= 0) {
      t.flag = 1;
      if (t.amt >= 1500) {
        t.amt = t.amt * 0.7;
      } else if (t.amt >= 1000) {
        t.amt = t.amt * 0.85;
      } else if (t.amt >= 500) {
        t.amt = t.amt * 0.95;
      }
    } else {
      t.flag = 0;
    }

    t.id = idCounter++;
    Node *newNode = new Node(t);
    newNode->next = top;
    top = newNode;
  }

  Transaction pop() {
    if (top == NULL) {
      Transaction empty;
      return empty;
    }

    Node *temp = top;
    Transaction t = temp->data;
    top = top->next;
    delete temp;

    t.amt = t.amt * -1;
    t.desc = t.desc + " [REVERSED]";
    t.flag = 2;

    return t;
  }

  void display() {
    Node *curr = top;
    while (curr != NULL) {
      cout << "[id=" << curr->data.id << ", amt=" << fixed << setprecision(2)
           << curr->data.amt << ", desc=\"" << curr->data.desc
           << "\", flag=" << curr->data.flag << "]" << endl;
      curr = curr->next;
    }
  }
};

class StackChar {
private:
  char arr[100];
  int topIndex;

public:
  StackChar() { topIndex = -1; }

  void push(char c) { arr[++topIndex] = c; }

  char pop() { return arr[topIndex--]; }

  char top() { return arr[topIndex]; }

  bool isEmpty() { return topIndex == -1; }
};

class StackDouble {
private:
  double arr[100];
  int topIndex;

public:
  StackDouble() { topIndex = -1; }

  void push(double v) { arr[++topIndex] = v; }

  double pop() { return arr[topIndex--]; }

  double top() { return arr[topIndex]; }
};

int getPrecedence(char op) {
  if (op == '+' || op == '-')
    return 1;
  if (op == '*' || op == '/')
    return 2;
  return 0;
}

bool isOperator(char c) { return c == '+' || c == '-' || c == '*' || c == '/'; }

string infixToPostfix(string infix) {
  StackChar stk;
  string postfix = "";

  for (int i = 0; i < infix.length(); i++) {
    char ch = infix[i];

    if (ch == ' ')
      continue;

    if ((ch >= '0' && ch <= '9') || ch == '.') {
      postfix += ch;
    } else if (ch == '(') {
      if (postfix.length() > 0 && postfix[postfix.length() - 1] != ' ')
        postfix += ' ';
      stk.push(ch);
    } else if (ch == ')') {
      if (postfix.length() > 0 && postfix[postfix.length() - 1] != ' ')
        postfix += ' ';
      while (!stk.isEmpty() && stk.top() != '(') {
        postfix += stk.top();
        postfix += ' ';
        stk.pop();
      }
      if (!stk.isEmpty())
        stk.pop();
    } else if (isOperator(ch)) {
      if (postfix.length() > 0 && postfix[postfix.length() - 1] != ' ')
        postfix += ' ';
      while (!stk.isEmpty() && stk.top() != '(' &&
             getPrecedence(stk.top()) >= getPrecedence(ch)) {
        postfix += stk.top();
        postfix += ' ';
        stk.pop();
      }
      stk.push(ch);
    }
  }

  if (postfix.length() > 0 && postfix[postfix.length() - 1] != ' ')
    postfix += ' ';

  while (!stk.isEmpty()) {
    postfix += stk.top();
    postfix += ' ';
    stk.pop();
  }

  while (postfix.length() > 0 && postfix[postfix.length() - 1] == ' ') {
    postfix = postfix.substr(0, postfix.length() - 1);
  }

  return postfix;
}

double evaluatePostfix(string postfix) {
  StackDouble stk;
  string num = "";

  for (int i = 0; i <= postfix.length(); i++) {
    char ch = (i < postfix.length()) ? postfix[i] : ' ';

    if (ch == ' ') {
      if (num != "") {
        double value = 0;
        int decimalPos = -1;

        for (int j = 0; j < num.length(); j++) {
          if (num[j] == '.') {
            decimalPos = j;
            break;
          }
        }

        if (decimalPos == -1) {
          for (int j = 0; j < num.length(); j++) {
            value = value * 10 + (num[j] - '0');
          }
        } else {
          for (int j = 0; j < decimalPos; j++) {
            value = value * 10 + (num[j] - '0');
          }
          double decimal = 0;
          double multiplier = 0.1;
          for (int j = decimalPos + 1; j < num.length(); j++) {
            decimal += (num[j] - '0') * multiplier;
            multiplier *= 0.1;
          }
          value += decimal;
        }
        stk.push(value);
        num = "";
      }
    } else if ((ch >= '0' && ch <= '9') || ch == '.') {
      num += ch;
    } else if (isOperator(ch)) {
      double b = stk.pop();
      double a = stk.pop();
      double result = 0;

      if (ch == '+')
        result = a + b;
      else if (ch == '-')
        result = a - b;
      else if (ch == '*')
        result = a * b;
      else if (ch == '/')
        result = a / b;

      stk.push(result);
    }
  }

  return stk.top();
}

int main() {
  srand(time(0));

  Transaction transactionList[7] = {
      Transaction(1200, "Sale: Blue Jacket"),
      Transaction(450, "Sale: Cotton Socks"),
      Transaction(-300, "Refund: Defective Shirt"),
      Transaction(1700, "Sale: Leather Jacket"),
      Transaction(800, "Sale: Running Shoes"),
      Transaction(-150, "Refund: Wrong Size Pants"),
      Transaction(2000, "Sale: Winter Coat Premium Quality")};

  TransactionStack stack;

  cout << "Pushed Transactions:" << endl;

  int indices[4];
  indices[0] = 0;
  indices[1] = 1;
  indices[2] = 3;
  indices[3] = 2;

  for (int i = 0; i < 4; i++) {
    Transaction trans = transactionList[indices[i]];
    double originalAmt = trans.amt;
    string originalDesc = trans.desc;

    stack.push(trans);

    cout << (i + 1) << ". " << originalDesc << " (" << originalAmt << ")";

    if (originalAmt >= 0) {
      if (originalAmt >= 1500) {
        cout << " → Discount 30% → Final: " << fixed << setprecision(2)
             << (originalAmt * 0.7) << endl;
      } else if (originalAmt >= 1000) {
        cout << " → Discount 15% → Final: " << fixed << setprecision(2)
             << (originalAmt * 0.85) << endl;
      } else if (originalAmt >= 500) {
        cout << " → Discount 5% → Final: " << fixed << setprecision(2)
             << (originalAmt * 0.95) << endl;
      } else {
        cout << " → No discount" << endl;
      }
    } else {
      cout << endl;
    }
  }

  cout << endl << "Intermediate Expression Calculation:" << endl;
  string infixExpr = "(100 + 20) * 0.9 - 5";
  cout << "Infix: " << infixExpr << endl;

  string postfixExpr = infixToPostfix(infixExpr);
  cout << "Postfix: " << postfixExpr << endl;

  double result = evaluatePostfix(postfixExpr);
  cout << "Evaluated Result: " << fixed << setprecision(2) << result << endl;

  cout << endl << "Pop (remove) one transaction:" << endl;
  Transaction poppedTrans = stack.pop();
  cout << "Popped Transaction: " << poppedTrans.desc << endl;
  cout << "Amount changed from " << (poppedTrans.amt * -1) << " to +"
       << poppedTrans.amt << endl;
  cout << "Flag updated to " << poppedTrans.flag << endl;

  cout << endl << "Final Stack Output:" << endl;
  cout << "Top → ";
  stack.display();
  cout << "Bottom →" << endl;

  return 0;
}