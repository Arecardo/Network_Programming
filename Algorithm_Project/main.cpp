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

generate_demo(vector<int> &temp_test_v, vector<int> &temp_test_w){
  // use array to store data
  int a = [3, 4, 15, 4, 21, 6, 8, 9, 1, 12];
  int b = [2, 3, 7, 3, 15, 4, 5, 3, 1, 6];

  //assign data to the vectors
  for(int i=0; i<10; i++)
  {
    temp_test_v.push_back(a[i]);
    temp_test_w.push_back(b[i]);
  }

}

void get_total_value(int v, int w){

}

int main(){
  // generate data for demo case
  vector<int> temp_test_v;
  vector<int> temp_test_w;
  generate_demo(temp_test_v, temp_test_w);

  return 0;
}
