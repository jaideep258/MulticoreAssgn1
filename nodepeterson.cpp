#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <atomic>
#include <thread>
#include <math.h>
#include "boost/date_time/posix_time/posix_time.hpp"
#include <random>
#include <fstream>

using namespace std;

class peterson
{

private:

int no_of_threads;
int iterate;
int arr[100]={0}; // for tree
volatile int victim[100];
volatile  bool interested[100];
int arrsize=0;
int shared=0;
int countparent=0;
std::thread mythreads[50];
int iterations=0;
int mean=1;

public:

peterson(int a, int b, int c)
{
no_of_threads=a;
iterations=b;
mean =c;
}

void tournament_unlock(int me)
{
    int i;
    for(i=0;i<arrsize;i++)
        {
           if (arr[i] == me)
               interested[i] = false;
	}
}

void tournament_lock(int me) 
{

    int i,index=0;
    
    //get self index
    for (i=countparent;i<arrsize;i++)
    {
       if(arr[i]==me)
       {
          index=i;
          break;
       }
    }
   
    while(index>0)
    {
        
	interested[index] = true;
	if(index%2)
        {
             victim[index+1]=me;
	     while(interested[index+1] && victim[index+1]==me);
             index=(index-1)/2;       
        }
        else
        {
             victim[index]=me;
	     while(interested[index-1] && victim[index]==me); 
             index=(index-2)/2;
        }
	arr[index]=me;  // me thread moving up
    }

}


void enterCS(int thread_num)
{
    float x;
    double const exp_dist_mean   = mean;
    double const exp_dist_lambda = 1 / exp_dist_mean;
    std::random_device rd;
    std::exponential_distribution<> rng (exp_dist_lambda);
    std::mt19937 rnd_gen (rd ());
       
    for(int i=0;i<iterations;i++)
    {
        tournament_lock(thread_num);
	cout<<"Entering CS for"<< thread_num <<endl;
        x= rng(rnd_gen);
        if (x<1)
        x=x*100;
        else
        x=x*10;
	usleep(x);
	shared++;
	tournament_unlock(thread_num);
    }
   
}


void petersontree()
{

    int nodes=no_of_threads;
    int level=0,i,j=1;
           
    for(i=0;i<100;i++)
    interested[i]=false;

    for(i=0;i<100;i++)
    victim[i]=0;

    while(nodes>0)
    {
        nodes=nodes/2;
        level++;
    }

    countparent=pow(2,level)-1;

    arrsize=countparent+no_of_threads;

    // copy node number from level to arrsize-1
    for(i=countparent;i<arrsize;i++)
        arr[i]=j++;
       
    // create no_of_nodes threads
    //each thread will call enterCS function
    
    for(i=0;i<no_of_threads;i++)
       mythreads[i] = std::thread(&peterson::enterCS,this, i+1);

    for(i=0;i<no_of_threads;i++)
        mythreads[i].join();

     cout<<"After number of threads "<<no_of_threads<<"* iterations "<<iterations<<"the value is: "<<shared<<endl;

}

};


int main ( int argc, char *argv[] )
{  
    if ( argc != 4 ) // argc should be 2 for correct execution
        {
	cout<<"usage: "<< argv[0] <<" number_of_threads iterations mean\n";
	exit(1);
	}
    
    peterson p(atoi(argv[1]),atoi(argv[2]),atoi(argv[3]));
    boost::posix_time::ptime start_time = boost::posix_time::microsec_clock::local_time();
    p.petersontree();
    boost::posix_time::time_duration total = boost::posix_time::microsec_clock::local_time() - start_time; 		  
    cout <<"Total Time taken"<< total.total_milliseconds()<<endl;
    ofstream file;
    file.open("results");
    file<<total.total_milliseconds()<<endl;
    file.close();

    return 0;

}
