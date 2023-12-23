#include <iostream>
using std::cout;
using std::endl;
#include <algorithm>
#include <vector>
#include <thread>
#include <chrono>
using std::thread;
#include "Boid.h"

int main()
{
    std::vector<std::thread> boidThreads;
	for(int i = 0; i < 10; i++)	{
		boidThreads.push_back( std::thread{Boid{}} );
	}
    // Now wait for all the worker thread to finish i.e.
    // Call join() function on each of the std::thread object
	std::cout<<"wait for all the worker thread to finish"<<std::endl;
	std::vector<std::thread>::iterator myBoid;
	for (myBoid=boidThreads.begin(); myBoid != boidThreads.end(); ++myBoid)
		myBoid->join();
	std::cout<<"Exiting from Main Thread"<<std::endl;

    /*
    Boid myBoid;

    for (int t = 0; t < 50; ++t){

        cout << myBoid << endl;

        myBoid.pos_update();

        std::this_thread::sleep_for(std::chrono::seconds{1});

    }
    */
    return 0;
}