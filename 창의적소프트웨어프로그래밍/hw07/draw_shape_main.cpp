#include <iostream>
#include <string>
#include "draw_shape.h"


using namespace std;

int main()
{
	int row, col;

	cin>>row>>col;

	Canvas canvas(row, col);

	canvas.Draw(cout);

	while(true)
	{
		string word;

		cin>>word;

		if(word=="add")
		{
			cin>>word;

			if(word=="rect")
			{
					/*Implement here*/
				Shape rect;
				rect.type = "rect";
				cin >> rect.x >> rect.y >> rect.width >> rect.height >> rect.brush;
			    if((rect.x + rect.width/2 < row)&&(rect.x - rect.width/2 >=0)&&(rect.y + rect.height/2<col)&&(rect.y - rect.height/2>=0)&&(rect.width%2!=0)&&(rect.height%2!=0)){
              	canvas.AddShape(rect);
                }
                else if(rect.width % 2 == 0 || rect.height % 2 == 0){
                    cout << "error invalid input" << endl;               
                }
                else{
                    cout << "error out of canvas" << endl;
                }

				
			}

			else if(word=="tri_up")
			{
					/*Implement here*/
				Shape tri_up;
				tri_up.type = "tri_up";
				cin >> tri_up.x >> tri_up.y >> tri_up.height >> tri_up.brush;
			
                if((tri_up.x + tri_up.height - 1 < row)&&(tri_up.x - (tri_up.height - 1)>=0) && (tri_up.y >=0)&&(tri_up.y + tri_up.height-1 < col)){
              	canvas.AddShape(tri_up);
                }
                
                else{
                    cout << "error out of canvas" << endl;
                }

			}

			else if(word=="tri_down")
			{
			       /*Implement here*/
				Shape tri_down;
				tri_down.type = "tri_down";
				cin >> tri_down.x >> tri_down.y >> tri_down.height >> tri_down.brush;
               
                if((tri_down.x + tri_down.height - 1 < row)&&(tri_down.x - (tri_down.height - 1)>=0)&&(tri_down.y<col)&&(tri_down.y -(tri_down.height - 1)>=0)){
				canvas.AddShape(tri_down);
                }

              
                else{
                    cout << "error out of canvas" << endl;
                }
			}

			else
				break;
		}

		else if(word=="delete")
		{
			/*Implement here*/
            int number;
            cin >> number;
            canvas.DeleteShape(number);			
		}

		else if(word=="draw")
	    {
			/*Implement here*/
			canvas.Draw(cout);
		}
		else if(word=="dump")
		{
			/*Implement here*/
            canvas.Dump(cout);
		}

		else
			break;
	}
}
