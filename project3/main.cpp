#include<iostream>
#include<string>
using namespace std;

// DEFINE YOUR TEST
#define TEST4

#ifdef TEST1
//        What single specific paricular uno ein one-thing is being tested?:
//        What is expected?:
//        What happens?:
#include"list.h"
int main() {
    
    
    List<int> l;
    
    l.addToRear(3);
    l.addToFront(-1);
    l.addToFront(9000);
    //l.addToFront(2);
    //l.addItem(-9, 0);
    l.printItems();
    //cout<<l.getSize()<<endl;
    l.deleteItem(1);
    l.printItems();
    //l.deleteRear();
    l.deleteFront();
    l.deleteFront();
    if(l.isEmpty()){cout<<"empty"<<endl;}
    else cout<<"not empty"<<endl;
    
    return 0;
}

#elif defined(TEST2)
//        What single specific paricular uno ein one-thing is being tested?:
//        What is expected?:
//        What happens?:
#include"stack.h"
int main() {
    
    Stack<std::string> s;
    
    if(s.isEmpty()) s.push("Soo");
    s.push("Harry");
    s.push("Ron");
    s.push("Hermione");
    if(s.isEmpty()) s.push("Soo");
//    cout << s.peek() << endl;
    s.pop();
//    cout << s.peek() << endl;
//    s.pop();
//    cout << s.peek() << endl;
//    s.pop();
//    cout << s.peek() << endl;
    s.printStack();
    return 0;
}

#elif defined(TEST3) //Test the maze in lecture slides
//        What single specific paricular uno ein one-thing is being tested?:
//        What is expected?:
//        What happens?:
#include"game.h"
int main() {
    Game g("maze_lecture.txt", 3);
    g.play();
    return 0;
}
#elif defined(TEST4) //Test a custom maze.
//        What single specific paricular uno ein one-thing is being tested?:
//        What is expected?:
//        What happens?:
#include"game.h"
int main() {
    Game g("maze.txt", 6);
    g.play();
    return 0;
}
#elif defined(TEST5) //Test too many sharks
//        What single specific paricular uno ein one-thing is being tested?:
//        What is expected?:
//        What happens?:
#include"game.h"
int main() {
    Game g("maze.txt", 800);
    g.play();
    return 0;
}
#else
int main() {
    cout << "Hello World!" << endl;
    return 0;
}
#endif
