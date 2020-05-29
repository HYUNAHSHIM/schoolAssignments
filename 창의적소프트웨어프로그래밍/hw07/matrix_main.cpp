#include <map>
#include <string>
#include "matrix.h"
#include <iostream>

using namespace std;

int main() {
    map<string, Matrix> matrices;
    string cmd;
    while (cmd != "quit") {
        cin >> cmd;
        if (cmd == "matrix") {
            /* Implement Here */
            string name;
            int row, col;
            cin >> name >> row >> col;
            Matrix m = Matrix(row,col);
            for(int i=0 ; i < row * col ; i++) {
                int val;
                cin >> val;
                m.Add(val);
            }
            matrices.insert(make_pair(name, m));
            cout << name << ":" << endl;
            
            cout << m;
            
        } else if (cmd == "list") {
            /* Implement Here */
            map<string, Matrix>::iterator it;
            for(it = matrices.begin() ; it != matrices.end() ; it++) {
                cout << it->first << " ";
                it->second.Print();
            }
            
        } else if (cmd == "eval") {
            /* Implement Here */
            string st1, st2, op;
            cin >> st1 >> op >> st2;
            
            if(matrices.find(st1) == matrices.end() || matrices.find(st2) == matrices.end() ) {
                if(op == "+") {
                    cout << stoi(st1) + stoi(st2) << endl;
                } else if(op == "-") {
                    cout << stoi(st1) - stoi(st2) << endl;
                } else if(op == "*") {
                    cout << stoi(st1) * stoi(st2) << endl;
                }
                
            } else if(matrices.find(st1) != matrices.end() && matrices.find(st2) != matrices.end() ) {
                if(op == "+") {
                    if( matrices.at(st1).rows() == matrices.at(st2).rows() && matrices.at(st1).cols() == matrices.at(st2).cols()) {
                        Matrix res = matrices.at(st1) + matrices.at(st2);
                        cout << res;
                    } else {
                        cout << "Invalid operation" << endl;
                    }
                    
                } else if(op == "-") {
                    if( matrices.at(st1).rows() == matrices.at(st2).rows() && matrices.at(st1).cols() == matrices.at(st2).cols()) {
                        Matrix res = matrices.at(st1) - matrices.at(st2);
                        cout << res;
                    } else {
                        cout << "Invalid operation" << endl;
                    }
                    
                } else if(op == "*") {
                    if( matrices.at(st1).cols() == matrices.at(st2).rows() ) {
                        Matrix res = matrices.at(st1) * matrices.at(st2);
                        cout << res;
                    } else {
                        cout << "Invalid operation" << endl;
                    }
                }
            }
            
        }
    }
    return 0;
}
