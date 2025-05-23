#include "movies.h"
#include <string>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

movieList::movie::movie(string n, double r){
    name = n;
    rate = r;
}
string movieList::movie::getname() const{
    return name;
}
double movieList::movie::getrate() const{
    return rate;
}
bool movieList::movie::operator<(const movie& other) const {
    return name < other.name;
}

void movieList::movie::printout() const{
    cout << name << ", " << rate << endl;
}

bool movieList::movie::contain(string pre) const{
    if (name.substr(0,pre.size()) == pre) return true;
    return false;
}

void movieList::sort() {
    std::sort(movielist.begin(), movielist.end(), [](const movie& a, const movie& b) {
        return a.getname() < b.getname();
    });
}
void movieList::addMovie(movie newone){
    movielist.push_back(newone);
}

void movieList::printmovie() const {
    for (const movie& x : movielist){
        x.printout();
    }
}

const vector<movieList ::movie>& movieList::getlist() const{
    return movielist;
}

searchList::movieRes::movieRes(string n, double r){
    name = n;
    rate = r;
}

bool searchList::movieRes::operator<(const movieRes &other) const{
    if (other.rate == rate){
        return name < other.name;
    }
    return rate > other.rate;
}

searchList::searchList(string prefix){
    pre = prefix;
}

void searchList::addlist(movieRes newone)
{
    serach_list.insert(newone);
}

void searchList::printlist() const{
    if(serach_list.empty()) return;
    for (const movieRes& x : serach_list){
        x.printlistout();
    }
    cout << "\n";
}

const set<searchList::movieRes> &searchList::getsearchlist() const{
    return serach_list;
}

const searchList::movieRes &searchList::gettop() const{
    return *serach_list.begin();
}

const string &searchList::getprefix() const{
    return pre;
}

void searchList::movieRes::printlistout() const{
    cout << name << ", " << rate << endl;
}
const string &searchList::movieRes::get_name() const{
    return name;
}

const double &searchList::movieRes::get_rate() const{
    return rate;
}
