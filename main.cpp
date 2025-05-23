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
using namespace std;

#include "utilities.h"
#include "movies.h"

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
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
    for(string x: prefixes){
        searchList B = searchList(x);
        for(const movieList::movie& n: listA.getlist()){
            if(n.contain(x)){
                searchList::movieRes input(n.getname(), n.getrate());
                B.addlist(input);
            }  
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

    return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/

bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}