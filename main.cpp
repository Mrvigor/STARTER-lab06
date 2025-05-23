// Winter'24
// Instructor: Diba Mirza
// Student name:  Shunzhi Luo
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <sstream>
#include <chrono>
using namespace std;

#include "utilities.h"
#include "movies.h"

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    // auto start = chrono::high_resolution_clock::now();
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
  
    // Create an object of a STL data-structure to store all the movies
    movieList listA;
    string line, movieName;
    double movieRating;
    // Read each file and store the name and rating
    while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
            movieList::movie input = movieList::movie(movieName, movieRating);
            listA.addMovie(input);
            // Use std::string movieName and double movieRating
            // to construct your Movie objects
            // cout << movieName << " has rating " << movieRating << endl;
            // insert elements into your data structure
    }

    movieFile.close();
    listA.sort();
    if (argc == 2){
        listA.printmovie();
        return 0;
    }

    ifstream prefixFile (argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    while (getline (prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }

    vector<searchList> listB;
   const std::vector<movieList::movie>& allMovies = listA.getlist();

    for (const std::string& prefix : prefixes) {
        searchList B(prefix);
        auto it = std::lower_bound(allMovies.begin(), allMovies.end(), prefix,
            [](const movieList::movie& m, const std::string& p) {
            return m.getname() < p;
            });
        while (it != allMovies.end() && it->getname().substr(0, prefix.size()) == prefix) {
            B.addlist(searchList::movieRes(it->getname(), it->getrate()));
            ++it;
        }
        listB.push_back(B);
    }

    for (searchList listwithpre : listB){
       if(listwithpre.getsearchlist().empty()){
            cout << "No movies found with prefix "<< listwithpre.getprefix() << endl;
        }
         listwithpre.printlist();
    }
   
    for(searchList listwithpre : listB){
        if(!listwithpre.getsearchlist().empty()){
            searchList:: movieRes best = listwithpre.gettop();
            cout << "Best movie with prefix " << listwithpre.getprefix() << " is: " << best.get_name() << " with rating " << std::fixed << std::setprecision(1) << best.get_rate() << endl;
        }
    }
    //  For each prefix,
    //  Find all movies that have that prefix and store them in an appropriate data structure
    //  If no movie with that prefix exists print the following message
    
    //  For each prefix,
    //  Print the highest rated movie with that prefix if it exists.

    /* auto end = chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "running time: " << elapsed_ms.count() << " ms\n";
    return 0; */


}


/* Add your run time analysis for part 3 of the assignment here as commented block
===============
TIME COMPLEXITY
===============

 1. find the prefix matched time = O(log n)

 2. scan until the prefix is not matched O(l) per comparison and worst-case with k matched
 time for 2 is O(k * l)

 total per prefix = O(log n + k * l )
 with m prefix
 total time = O(m * (log n + k * l)

=============
RUNTIME COUNT
=============

 input_20_random: 47ms
 input_100_random: 39ms
 input_1000_random: 46ms
 input_76920_random: 239ms

================
SPACE COMPLEXITY
================

 For n movies = O(n * l)
 For m prefix = O(m * l)
 For each searchList = O(k * l) total searchList = O(m * k * l)
 Total = O( (n * l) + (m * l) + (m * k * l)) = O(nl + mkl)

================
EXPLORE TRADEOFF
================

 For part 2 of the assignment, I designed my algorithm with the goal of achieving low time complexity,
 especially because the task involves searching for movie name prefixes across a large dataset of movies.
 I used a sorted vector of movies and applied binary search (std::lower_bound) to quickly locate where matching movie names might begin. 
 This was much faster than scanning the entire list of movies for each prefix.
 I was unable to keep the space complexity relatively low, since if i want to increase the search speed I may use hashmap, which require more space.
 Low time complexity was harder to achieve than low space complexity.
 This is because naive approaches are simple but slow, and optimizing for speed required sorting, binary search, and careful prefix matching.
 Once time was optimized, the space cost remained manageable.
*/

bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}