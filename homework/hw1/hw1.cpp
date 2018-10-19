#include <iostream>
#include <vector>
#include <ctime>
using namespace std;



/*
 Programmer: Corey Carrington
 NetID:cac844
 */


class timer {//clocks the time an alogorithm takes
public:
    timer() : start(clock()) {}
    double elapsed() { return ( clock() - start ) / CLOCKS_PER_SEC; }
    void reset() { start = clock(); }
private:
    double start;
};

/**
 * Cubic maximum contiguous subsequence sum algorithm.
 */
int maxSubSum1( const vector<int> & a )
{
    int maxSum = 0;

    for( int i = 0; i < a.size( ); ++i )
        for( int j = i; j < a.size( ); ++j )
        {
            int thisSum = 0;

            for( int k = i; k <= j; ++k )
                thisSum += a[ k ];

            if( thisSum > maxSum )
                maxSum   = thisSum;
        }

    return maxSum;
}


/**
 * Quadratic maximum contiguous subsequence sum algorithm.
 */
int maxSubSum2( const vector<int> & a )
{
    int maxSum = 0;

    for( int i = 0; i < a.size( ); ++i )
    {
        int thisSum = 0;
        for( int j = i; j < a.size( ); ++j )
        {
            thisSum += a[ j ];

            if( thisSum > maxSum )
                maxSum = thisSum;
        }
    }

    return maxSum;
}


/**
 * Linear-time maximum contiguous subsequence sum algorithm.
 */
int maxSubSum4( const vector<int> & a )
{
    int maxSum = 0, thisSum = 0;

    for( int j = 0; j < a.size( ); ++j )
    {
        thisSum += a[ j ];

        if( thisSum > maxSum )
            maxSum = thisSum;
        else if( thisSum < 0 )
            thisSum = 0;
    }

    return maxSum;
}

//Question 1 use MaxSubSeq functions to determine time of algorithm
void programmingProblem1(){
	cout << "Big-oh \t Cubic  \t Quadratic \t Linear-time \n";
	for(int i = 128; i < 4097; i*=2){//loop allow for the 

		
			timer t;
			double nuClicks;
			vector<int> items;
			for(int j=0; j < i; ++j){
				int x = (rand()% 2001)-1000;
				items.push_back(x);
			}
			cout << i << "\t ";
			t.reset();
			maxSubSum1(items);
			nuClicks = t.elapsed();
			
			cout << nuClicks << "\t\t";

			t.reset();
			maxSubSum2(items);
			nuClicks = t.elapsed();
			cout << nuClicks << "\t\t";

			t.reset();
			maxSubSum4(items);
			nuClicks = t.elapsed();
			cout << nuClicks  << endl;

			//can't get the numbers to allign properly
	}

}//end of function
void sampleA(int n){
	int sum=0;
	for (int i = 0; i < n; i++)
		++sum;
}
void sampleB(int n){
	int sum=0;
	for(int i = 0; i < n; i++)
        for(int j = 0; j < n; ++j)
            ++sum;

}
void sampleC(int n){
	int sum =0;
	for(int i = 0; i < n; i++)
    	for(int j = 0; j < i; ++j)
        	++sum;
}
void sampleD(int n){
	int sum=0;
	for(int i = 0; i < n; i++)
        for(int j = 0; j < n; ++j)
        	for(int k = 0; k < n; ++k)
				++sum;
}

void programmingProblem2(){
	//run loops on written question2 and get time.
	cout << "n  |\t   a|\t      b|\t   		c|\t   d|" << endl;
	for(int i = 256; i <= 4096; i *= 2 ){
		timer t;
		double nuClicks;
		//cout << "\t";
		t.reset();
		sampleA(i);
		nuClicks = t.elapsed();
		cout << i << "|\t"; 
		cout << nuClicks << "\t";

		t.reset();
		sampleB(i);
		nuClicks = t.elapsed(); 
		cout << nuClicks << "|\t";


		t.reset();
		sampleC(i);
		nuClicks = t.elapsed(); 
		cout << nuClicks << "|\t";


		t.reset();
		sampleD(i);
		nuClicks = t.elapsed(); 
		cout << nuClicks << "|\n";

	}





}//end of function 

int main(){
	programmingProblem1();
	programmingProblem2();

	return 0;
}



























































