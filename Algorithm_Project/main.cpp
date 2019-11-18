/*
  Author: Xinrun Zhang
  Title: main file for Algorithm Project
  Date: 11/13/2019
*/

#include<iostream>
#include<vector>
using namespace std;

class solution{
public:
  /*
  main solution class
  */
  void get_solution(int val[], int wt[], int capacity_limit, int len_val){
    // initial the solution table,
    // the size of table is (len_val)*(capacity+1)
    int solution_table[len_val+1][capacity_limit+1];

    // assign 0 to the first row and the first column of the table
    for(int i = 0; i < len_val+1; i++){
      solution_table[i][0] = 0;
    }

    for(int i = 0; i < capacity_limit+1; i++){
      solution_table[0][i] = 0;
    }

    // iteratively generate the value of each cell
    for(int item = 1; item < len_val+1; item++){
      for(int curr_cap = 1; curr_cap < capacity_limit+1; curr_cap++){
        int max_val_without_curr = solution_table[item - 1][curr_cap]; // this is always exist
        int max_val_with_curr = 0; // initial the value to 0

        int curr_wt = wt[item-1]; // get the current item's weight

        if(curr_cap >= curr_wt){ // check if the knapsack can include the current item
          max_val_with_curr = val[item - 1]; // if it is, get the current value of the item

          // get the remaining capacity if we include the current item in the knapsack
          int remain_cap = curr_cap - curr_wt;

          // the maximum value with current item is:
          // value of current item + maximum value obtainble with the remaining capacity
          max_val_with_curr = max_val_with_curr + solution_table[item - 1][remain_cap];
        }

        // compare the max_val_with_curr with max_val_without_curr
        // assign the cell with the bigger one
        if(max_val_without_curr > max_val_with_curr){
          solution_table[item][curr_cap] = max_val_without_curr;
        }
        else{
          solution_table[item][curr_cap] = max_val_with_curr;
        }
      }
    }

    // print out the result
    cout << "The maximum value you can carry is: ";
    cout << solution_table[len_val][capacity_limit] << endl;
    cout << endl;
  }
};

void demo(){
  // print out information
  cout << "----------------------------------------------------" << endl;
  cout << "Welcome to the demo mode!" << endl;
  cout << "Initializing..." << endl;

  // generate data for demo case
  int temp_test_val[10] = {3, 4, 15, 4, 21, 6, 8, 9, 1, 12};
  int temp_test_wt[10] = {2, 1, 7, 3, 15, 4, 5, 3, 1, 6};
  int capacity_limit = 20;
  int len_val = sizeof(temp_test_val)/sizeof(temp_test_val[0]);

  // print out information
  cout << "In this demo, there are 10 available items." << endl;
  cout << "weight for each item: ";
  for(int i=0; i<10; i++){
    cout << temp_test_wt[i] << " ";
  }
  cout << endl;
  cout << "value for each item: ";
  for(int i=0; i<10; i++){
    cout << temp_test_val[i] << " ";
  }
  cout << endl;
  cout << "The capacity of the bag is: " << capacity_limit << endl;

  // create solution object
  // get solution_table
  cout << endl << "Calculating..." << endl;
  int demo_solution_table[11][11];
  solution demo_solution;
  demo_solution.get_solution(temp_test_val, temp_test_wt, capacity_limit, len_val);
  cout << "The domo is done! Thank you! " << endl;
  cout << "----------------------------------------------------" << endl;
}

void user_manual_test(){
  
}

int main(){
  cout << "****************************************************" << endl;
  cout << "*           Welcome to the knapsack program        *" << endl;
  cout << "*                Author: Xinrun Zhang              *" << endl;
  cout << "****************************************************" << endl;
  while(true){
    cout << "Please select a mode to demonstrate a demo or input your own data: " << endl;
    cout << "1. demo" << endl;
    cout << "2. self-defined 0-1 knapsack problem" << endl;
    cout << "3. quit" << endl;
    cout << "Your choice: ";

    int user_choice;
    cin >> user_choice;
    if(user_choice == 1){
      demo();
    }
    else if(user_choice == 2) {
      cout << "Sorry, I'm still working on this part!" << endl;
    }
    else if(user_choice == 3){
      break;
    }
    else{
      cout << "Incorrect Input! Please choose the mode! " << endl;
    }
  }
  return 0;
}
