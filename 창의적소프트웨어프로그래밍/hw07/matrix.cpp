#include "matrix.h"

using namespace std;

Matrix::Matrix() {
    /* Implement Here */
}

Matrix::Matrix(int rows, int cols) {
    /* Implement Here */
    rows_ = rows;
    cols_ = cols;
}

void Matrix::Print(void) {
    /* Implement Here */
    cout << rows_ << " " << cols_ << endl;
}

int Matrix::Getter(int id) const{
    vector<int>::const_iterator it;
    it = values_.begin() + id;
    return *it;
}

ostream& operator<<(ostream& os, const Matrix& m) {
    int cnt = 0;
    vector<int>::iterator it;
    for(int i=0 ; i < m.rows() * m.cols() ; i++) {
        cnt++;
        os << m.Getter(i);
        if(cnt % m.cols() == 0) {
            os << endl;
        } else {
            os << " ";
        }
    }
    return os;
}
void Matrix::Add(int v) {
    values_.push_back(v);
}

Matrix operator+(const Matrix& lm, const Matrix& rm) {
    /* Implement Here */
    Matrix m = Matrix(lm.rows(), lm.cols());
    for(int i=0 ; i < lm.rows() * lm.cols() ; i++) {
        m.Add(lm.Getter(i) + rm.Getter(i));
    }
    return m;
}

Matrix operator-(const Matrix& lm, const Matrix& rm) {
    /* Implement Here */
    Matrix m = Matrix(lm.rows(), lm.cols());
    for(int i=0 ; i < lm.rows() * lm.cols() ; i++) {
        m.Add(lm.Getter(i) - rm.Getter(i));
    }
    return m;
}

Matrix operator*(const Matrix& lm, const Matrix& rm) {
    /* Implement Here */
    
    Matrix m = Matrix(lm.rows(), rm.cols());
    int **arr = new int*[lm.rows()];
    for(int i = 0; i < lm.rows(); ++i) {
        arr[i] = new int[lm.cols()];
        memset(arr[i], 0, sizeof(int)*lm.cols());   // 메모리 공간을 0으로 초기화
    }
    int **arr2 = new int*[rm.rows()];
    for(int i = 0; i < rm.rows(); ++i) {
        arr2[i] = new int[rm.cols()];
        memset(arr2[i], 0, sizeof(int)*rm.cols());   // 메모리 공간을 0으로 초기화
    }
    int **arr3 = new int*[lm.rows()];
    for(int i = 0; i < lm.rows(); ++i) {
        arr3[i] = new int[lm.cols()];
        memset(arr3[i], 0, sizeof(int)*lm.cols());   // 메모리 공간을 0으로 초기화
    }

    int cnt=0;
    for(int i=0 ; i < lm.rows() ; i++) {
        for(int j=0 ; j < lm.cols() ; j ++ ) {
            arr[i][j] = lm.Getter(cnt);
            cnt ++;
        }
    }
    
    
    cnt=0;
    for(int i=0 ; i < rm.rows() ; i++) {
        for(int j=0 ; j < rm.cols() ; j ++ ) {
            arr2[i][j] = rm.Getter(cnt);
            cnt ++;
        }
    }
    
    
    for(int i=0 ; i < lm.rows() ; i++) {
        for(int j=0 ; j < rm.cols() ; j ++ ) {
            for(int k=0 ; k< lm.cols() ; k++) {
                arr3[i][j] += arr[i][k] * arr2[k][j];
            }
        }
    }
    

    /* 메모리 해제 */
    /*
    for(int i = 0; i < lm.rows(); ++i) {
        delete [] arr[i];
    }
    delete [] arr;
     */
    
    for(int i=0 ; i < lm.rows() ; i++) {
        for(int j=0; j< rm.cols() ; j++) {
            m.Add(arr[i][j]);
            cout << arr[i][j] << " ";
        }
    }
    return m;
}

Matrix operator+(const int& a, const Matrix& rm) {
    /* Implement Here */
}

Matrix operator-(const int& a, const Matrix& rm){
    /* Implement Here */
}	

Matrix operator*(const int& a, const Matrix& rm) {
    /* Implement Here */
}

Matrix operator+(const Matrix& lm, const int& a) {
    /* Implement Here */
}

Matrix operator-(const Matrix& lm, const int& a) {
    /* Implement Here */
}	

Matrix operator*(const Matrix& lm, const int& a) {
    /* Implement Here */
}
