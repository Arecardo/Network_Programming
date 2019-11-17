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
  vector<vector<int>> get_solution(vector<int> &val, vector<int> &wt, int capacity_limit){
    // get the size of val and wt
    len_val = val.size();
    len_wt = wt.size();

    // initial the solution table,
    // the size of table is (len_val)*(capacity+1)
    vector<vector<int>> solution_table(len_val+1, vector<int>(capacity_limit+1));

    // assign 0 to the first row and the first column of the table
    for(int i = 0; i < len_val+1; i++){
      solution_table[i][0] = 0;
    }

    for(int i = 0; i < capacity+1; i++){
      solution_table[0][i] = 0;
    }

    // iteratively generate the value of each cell
    for(int item = 1; item < len_val+1; i++){
      for(int curr_cap = 1; curr_cap < capacity+1; j++){
        int max_val_without_curr = solution_table[item - 1][curr_cap]; // this is always exist
        int max_with_curr = 0; // initial the value to 0

        int curr_wt = wt[item-1]; // get the current item's weight
        if(curr_cap >= curr_wt){ // check if the knapsack can include the current item
          max_val_with_curr = val[item - 1]; // if it is, get the current value of the item

          // get the remaining capacity if we include the current item in the knapsack
          int remain_cap = curr_cap - curr_wt;

          // the maximum value with current item is:
          // value of current item + maximum value obtainble with the remaining capacity
          max_val_with_curr += solution_table[item - 1][remain_cap];
        }
        if (max_val_without_curr > max_val_with_curr){
          solution_table[item][curr_cap] = max_val_without_curr;
        }
        else{
          solution_table[item][curr_cap] = max_val_with_curr;
        }
      }
    }

    // return the result
    return solution_table;
  }
};

int main(){
  // generate data for demo case
  vector<int> temp_test_val;
  vector<int> temp_test_wt;
  generate_demo(temp_test_val, temp_test_wt);
  int capacity_limit = 20;

  // create solution object
  // get solution_table
  vector<vector<int>> demo_solution_table;
  solution demo_solution;
  demo_solution_table = demo_solution.get_solution(temp_test_val, temp_test_wt, capacity_limit);
  return 0;
}
