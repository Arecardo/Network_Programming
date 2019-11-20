/*
  Author: Xinrun Zhang
  Title: main file for Algorithm Project
  Date: 11/13/2019
*/

#include<iostream>
#include<vector>
#include<string>
#include<sstream>
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
  // call the get_solution function
  // the function will print out the final result
  cout << endl << "Calculating..." << endl;
  solution demo_solution;
  demo_solution.get_solution(temp_test_val, temp_test_wt, capacity_limit, len_val);
  cout << "The domo is done! Thank you! " << endl;
  cout << "----------------------------------------------------" << endl;
}

void user_manual_test(){
  // print out message
  cout << "----------------------------------------------------" << endl;
  cout << "Welcome to the mode 2! " << endl;
  cout << "In this mode, you have to input some information about the problem manually! " << endl;

  // initial vecoters to store the user input val and wt
  // initial int to store the user input capacity
  vector<int> user_input_val;
  vector<int> user_input_wt;
  int user_input_cap_limit;
  int temp = 0;

  // user input
  cout << "Please input the value of the items with space, like 'xx xx xx xx', put enter as end: " << endl;
  while(cin >> temp){
    user_input_val.push_back(temp);
    if(cin.get() == '\n') break;
  }
  cin.clear();

  cout << "Please input the weight of the items with space, like 'xx xx xx xx', put enter as end: " << endl;
  while(cin >> temp){
    user_input_wt.push_back(temp);
    if(cin.get() == '\n') break;
  }
  cin.clear();

  cout << "Please input the limited capacity, it should be an integer: " << endl;
  cin >> user_input_cap_limit;

  // check if the input is valid
  int len_val = user_input_val.size();
  int len_wt = user_input_wt.size();
  if(len_val != len_wt){
    cout << "Sorry, the numbers of elements in the input array are not equal! Please try again! " << endl;
    cout << "----------------------------------------------------" << endl;
  }
  else if(user_input_val.empty() || user_input_wt.empty()){
    cout << "Sorry, one of the arrays is empty or both arrays are empty! Please try again! " << endl;
    cout << "----------------------------------------------------" << endl;
  }
  else{
    // turn the vectors into arrays
    int *new_val = new int[user_input_val.size()];
    int *new_wt = new int[user_input_wt.size()];
    if (!user_input_val.empty() && !user_input_wt.empty())
    {
        memcpy(new_val, &user_input_val[0], user_input_val.size()*sizeof(int));
        memcpy(new_wt, &user_input_wt[0], user_input_wt.size()*sizeof(int));
    }

    // create solution object
    // call the get_solution function
    // the function will print out the final result
    cout << endl << "Calculating..." << endl;
    solution user_solution;
    user_solution.get_solution(new_val, new_wt, user_input_cap_limit, len_val);
    cout << "The calculation is done! Thank you! " << endl;
    cout << "----------------------------------------------------" << endl;
  }

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
      user_manual_test();
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
