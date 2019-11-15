/*
  Author: Xinrun Zhang
  Title: main file for Algorithm Project
  Date: 11/13/2019
*/

#include<iostream>
#include<vector>
using namespace std;

void load_data(){

}

void generate_demo(vector<int> &temp_test_val, vector<int> &temp_test_wt){
  // use array to store data
  int a = [3, 4, 15, 4, 21, 6, 8, 9, 1, 12];
  int b = [2, 3, 7, 3, 15, 4, 5, 3, 1, 6];

  //assign data to the vectors
  for(int i=0; i<10; i++)
  {
    temp_test_val.push_back(a[i]);
    temp_test_wt.push_back(b[i]);
  }
}

class solution{
public:
  /*
  v: the length of the vector v
  w: the length of the vector w
  return: solution_table - a 2-d vector object
  */
  vector<vector<int>> get_solution(vector<int> &val, vector<int> &wt){
    //initial  solution_table
    vector<vector<int>> solution_table;
    len_val = val.size();
    len_wt = wt.size();

    // return the result
    return solution_table;
  }
}

int main(){
  // generate data for demo case
  vector<int> temp_test_val;
  vector<int> temp_test_wt;
  generate_demo(temp_test_val, temp_test_wt);

  // create solution object
  // get solution_table
  vector<vector<int>> demo_solution_table;
  solution demo_solution;
  demo_solution_table = demo_solution.get_solution(temp_test_val, temp_test_wt);
  return 0;
}
