#include <iostream>
#include <string>
#include <vector>
#include "draw_shape.h"


using namespace std;

Canvas::Canvas(size_t row, size_t col)
{
	/*Implement here*/
	int i;
	int count;
	width_ = row;
	height_ = col;
	
	char arr[200];
	for (i = 0; i < width_; ++i) {
		arr[i] = '.';
		count = i;
	}
	arr[count + 1] = '\0';
	string str(arr);
	for (i = 0; i < height_; ++i) {
		canvas_.push_back(str);
	}

}

Canvas::~Canvas()
{
}

void Canvas::AddShape(const Shape &s)
{
		/*Implement here*/
	shapes_.push_back(s);

}

void Canvas::DeleteShape(int index)
{
	/*Implement here*/
    if(index < shapes_.size()){
        its = shapes_.begin() + index;
        shapes_.erase(its);
    }

}

void Canvas::Draw(ostream& os)
{
	/*Implement here*/
	int i;
    char arr[200];
    int count =0;

    canvas_.clear();
    for(i = 0; i< width_; ++i){
        arr[i] = '.';
        count = i;
    }
    arr[count + 1] = '\0';
    string strs(arr);
    for(i =0 ; i < height_; ++i){
        canvas_.push_back(strs);
    }
    
    for(int k=0; k<shapes_.size();++k){
       if (shapes_[k].type == "rect") {
          for (it = canvas_.begin() + shapes_[k].y - shapes_[k].height / 2; it < canvas_.begin() + shapes_[k].y + shapes_[k].height / 2 + 1; it++) {
             string str = *it;
             for (int i = shapes_[k].x - shapes_[k].width/2; i <shapes_[k].x + shapes_[k].width/2 + 1; i++) {
                str[i] = shapes_[k].brush;   
             }
             canvas_.erase(it);
                canvas_.insert(it,str);
         
          }
       }
    
        if(shapes_[k].type == "tri_up"){
            int i = 0;
                  
                for(it = canvas_.begin() + shapes_[k].y; it < canvas_.begin() + shapes_[k].y + shapes_[k].height; it++){
                    string str = *it; 
                    for(int j = shapes_[k].x - i; j<= shapes_[k].x+i; j++){
                        str[j] = shapes_[k].brush;
                    }

                    canvas_.erase(it);
                    canvas_.insert(it,str);
                    i++;
                }
            
            }
    
    
        if(shapes_[k].type == "tri_down"){
            int i =0;
            
                for(it = canvas_.begin() + shapes_[k].y;it > canvas_.begin() + shapes_[k].y - shapes_[k].height; it--){

                    string str = *it;
                    for(int j = shapes_[k].x - i; j <= shapes_[k].x + i; j++){
                        str[j] = shapes_[k].brush;
                    }

                    canvas_.erase(it);
                    canvas_.insert(it,str);
                    i++;
                }
      
        

        }
    }

	cout << " ";
	for (i = 0; i < width_; ++i) {
		cout << i;
	}
	cout << endl;
	for (i = 0; i < canvas_.size(); ++i) {
		cout << i << canvas_[i] << endl;
	}
	

}

void Canvas::Dump(ostream& os)
{
	/*Implement here*/
    int i; 
    for(i=0;i< shapes_.size();i++){
        cout << i << " " << shapes_[i].type<<" "<<shapes_[i].x<< " " <<shapes_[i].y<<" ";
        if(shapes_[i].type == "rect"){
            cout << shapes_[i].width <<" " << shapes_[i].height <<" " <<shapes_[i].brush << endl;
        }
        else{
            cout << shapes_[i].height <<" " <<shapes_[i].brush << endl;
        }
        
    }

}
