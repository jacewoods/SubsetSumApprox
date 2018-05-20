#include <iostream>
#include <list>

using namespace std;

int target = 308; //Declare here in order to use remove_if with bool function below

//This function is used to remove all elements "n" from  list L[i] that are larger than the target number above
bool ifGreater (int n)
{
    return (n > target); //if n > target, element n is removed. if n <= target, does nothing
}

list<int> Trim (list<int> L, double trimParam)
{
    int m = L.size(); //Set m to size of L
    list<int> Li; //Make a new list to later return
    Li.push_back(*L.begin()); //Begin list Li with the first value being the first value in list L
    int last = *L.begin(); //Set the last number added to the first number in Li
    list<int>::iterator yi = ++L.begin(); //set iterator yi to the second value in list L

    //Loops from i = 2 to m
    for(int i = 2; i <= m; i++)
    {
        //If the value in L[yi] is > the last value seen * (1 + parameter set for Trim), enter if-statement
        /* This evaluation utilizes the Approximation scheme of the algorithm, it evaluates as true if we
         * haven't seen a number that is relatively close to the value of *yi in list L yet */
        if(*yi > (last * (1 + trimParam)))
        {
            Li.push_back(*yi); //Adds value to Li
            last = *yi; //Sets "last" to the most recent value added to list Li
        }
        yi++; //Increments yi, which then looks at the next value in list L
    }

    return Li; //Return Li to be the new list L after it completes a trim of list L
}

int main()
{
    //Create list S and initialize its elements
    list<int> S;
    S.push_back(104);
    S.push_back(102);
    S.push_back(201);
    S.push_back(101);

    int n = S.size(); //n is equal to cardinality of S
    list<int> L[5]; //Set to S.size + 1

    L[0].push_back(0); //The first list L is set to have only one element: 0

    //This is the percentage of accuracy you want from the approximation list, must be a number between 0 and 1
    double approxParam = 0.4; //0.4, for example, should return an answer within 40% of the optimal  answer

    list<int>::iterator it = S.begin(); //Iterator to get each element in S during the loop
    for(int i = 1; i <= n; i++)
    {
        //Start of "merge" process

        list<int> temp; //List to combine L[i - 1] with

        //Go through all elements of L[i - 1] (denoted *j) and add the current element S[it] to it (denoted *it)
        for(list<int>::iterator j = L[i - 1].begin(); j != L[i - 1].end(); j++)
            temp.push_back(*it + *j);

        L[i - 1].merge(temp); //Merge the temp list with L[i - 1]
        L[i].merge(L[i - 1]); //Merge L[i - 1] with L[i]
        it++; //Increment the value we look at in list S

        //End of "merge" process

        //Perform TRIM function, pass in L[i] and the preselected approximate paramater / (2 * the size of S)
        L[i] = Trim(L[i], approxParam / (2*n));

        L[i].remove_if(ifGreater); //Removes elements from list L[i] that are greater than the target number
    }

    //Print out the final list L[n], probably should comment this out if list L[n] is large
    cout << "The list of elements found in L[n] are:" << endl;
    for(list<int>::iterator i = L[n].begin(); i != L[n].end(); i++)
    {
        cout << *i << endl;
    }
    cout << endl;

    //Get the largest element of the list by retrieving the final element in L[n], which is already sorted to have the last element
    int z = *(--L[n].end()); //L[n].end is actually one address ahead of final element so we have to decrement it before passing element to "z"
    cout << "The element found in the Approximation list that is approximated to be closest to the target value is: " << z << endl;

    return 0;
}
