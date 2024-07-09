#include "treap.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <string>
#include <algorithm>
#include <cstring>
#include <utility>
#include <dirent.h>
#include <chrono>
#include <tuple>

using namespace std;
using namespace std::chrono;

void test_insert()
{

}

vector<vector<pair<int,int>>> load_tests_from_directory(const string& directory)
{
    vector<vector<pair<int,int>>> all_tests;
    DIR* dir;
    struct dirent* entry;

    if((dir=opendir(directory.c_str())) != nullptr)
    {
        while((entry=readdir(dir)) != nullptr)
        {
            string filename = entry->d_name;
            if(filename != "." && filename != "..")
            {
                string filepath = directory + "/" + filename;
                ifstream infile(filepath);
                if(infile)
                {   
                    vector<pair<int,int>> test;
                    int key, priority;
                    while(infile >> key >> priority)
                    {
                        test.push_back(make_pair(key,priority));
                    }
                    all_tests.push_back(test);
                    infile.close();
                }
                else
                {
                    cerr<<"Error while opening file: " << filepath << endl;
                }
            }
        }
        closedir(dir);
    }
    else
    {
        cerr << "Error while opening directory: " << directory << endl;
    }
    return all_tests;
}
TreapNode* buildTree(vector<pair<int,int>> test)
{
    TreapNode* treap = nullptr;
    for(const auto& t : test)
    {
        treap = insert(treap,t.first,t.second);
    }
    return treap;
}
vector<TreapNode*> upload_treaps(string& filename)
{
    vector<vector<pair<int,int>>> tests = load_tests_from_directory(filename);
    vector<TreapNode*> treaps;

    for(const auto& test : tests)
    {
        TreapNode* t = nullptr;
        for(const auto& p : test)
        {
            t = insert(t, p.first, p.second);
        }
        treaps.push_back(t);
    }

    return treaps;
}
double insert_test(vector<TreapNode*> treaps)
{
    double total_duration = 0.0;

    for(auto& t : treaps)
    {
        auto start = high_resolution_clock::now();
        t = insert(t, 3, 500000);
        auto end = high_resolution_clock::now();
        duration<double> diff = end - start;
        total_duration += diff.count();
    }
    return total_duration / treaps.size();
}
double remove_test(vector<TreapNode*> treaps)
{
    double total_duration = 0.0;
    for(auto& t : treaps)
    {
        auto start = high_resolution_clock::now();
        t = remove(t,0);
        auto end = high_resolution_clock::now();
        duration<double> diff = end - start;
        total_duration += diff.count();
    }
    return total_duration / treaps.size();
}
double search_test(vector<TreapNode*> treaps)
{
    double total_duration = 0.0;

    for(auto& t : treaps)
    {
        auto start = high_resolution_clock::now();
        t = search(t, 0); 
        auto end = high_resolution_clock::now();
        duration<double> diff = end - start;
        total_duration += diff.count();
    }
    return total_duration / treaps.size();
}
tuple<double,int,int> depth_test(vector<TreapNode*> treaps)
{   
    int total= 0;
    int min = INT_MAX;
    int max = INT_MIN;

    tuple<double,int,int> result;

    for(auto& t : treaps)
    {
        int d = depth(t);
        total += d;
        if(d < min)
        {
            min = d;
        }
        if(d > max)
        {
            max = d;
        }
    }
    double mean = total*1.0 / treaps.size();
    return {mean,min,max};
}
int main(int argc, char**argv)
{
    vector<string> directories = {"tests/test_10","tests/test_100","tests/test_1000","tests/test_10000","tests/test_100000"};
    //vector<string> directories = {"tests/test_1000000"};
    vector<double> insert_results;
    vector<double> remove_results;
    vector<double> search_results;
    vector<tuple<double,int,int>> depth_results; //mean,min,max depth
    
    // TreapNode* t = upload_treaps(directories[0])[0];
    // printTreap(t);
    // cout<<"-------------\n";
    //t = remove(t,-11);
    //printTreap(t);

    // auto [left,right] = split(t, 0);
    // printTreap(left);
    // cout <<"---------\n";
    // printTreap(right);
    // cout <<"---------\n";
    // TreapNode* m = merge(left,right);
    // printTreap(m);
    // freeTreap(t);

    for(auto &d : directories)
    {
        vector<TreapNode*> treaps = upload_treaps(d);
        insert_results.push_back(insert_test(treaps));
        remove_results.push_back(remove_test(treaps));
        search_results.push_back(search_test(treaps));
        depth_results.push_back(depth_test(treaps));
    }
    for(auto& i: insert_results)
    {
        cout<<i <<" ";
    }
    cout<<"\n";
    for(auto &r : remove_results)
    {
        cout<< r <<" ";
    }
    cout<<"\n";
    for(auto &s : search_results)
    {
        cout<< s <<" ";
    }
    cout<<"\n";
    for(auto &d : depth_results)
    {
        cout<< "(" <<get<0>(d)<<","<<get<1>(d)<<","<<get<2>(d)<<")"<<" ";
    }
    cout<<"\n";

    
    

    return 0;
}