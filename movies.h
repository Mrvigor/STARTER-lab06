#include <string>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

class movieList {
    public:
    movieList() {};
    
    struct movie {
        movie(string n = "", double r = 0);
        string getname() const;
        double getrate() const;
        bool operator <(const movie& other) const;
        void printout() const;
        bool contain(string pre) const;
    private:
        string name;
        double rate;
    };

    void addMovie(movie newone);
    void printmovie() const;
    const vector<movie>& getlist() const;  
    void sort();                           

private:
    vector<movie> movielist;  
};
class searchList{
    public:
    struct movieRes{
        public:
        movieRes(string n = "", double r = 0);
        bool operator <(const movieRes & other) const;
        void printlistout() const;
        const string& get_name() const;
        const double& get_rate() const;
        private: 
        string name;
        double rate;
    };
    searchList(string prefix);
    void addlist(movieRes newone);
    void printlist() const;
    const set<movieRes> & getsearchlist() const;
    const movieRes& gettop() const;
    const string & getprefix() const;
    private:
    set <movieRes> serach_list;
    string pre;
};