// Online C++ compiler to run C++ program online
#include <iostream>
#include <algorithm>
#include <fstream>
#include <unordered_set>
#include <stdexcept>
#include <unordered_map>

using std::cout;            using std::endl;
using std::cerr;            using std::string;
using std::unordered_map;   using std::unordered_set;

bool valid_wikilink(const string& link) {
    auto valid = std::all_of(link.begin(), link.end(), [](char c){return c != '#' && c != ':'; });
    return valid;    
}
// END STUDENT CODE HERE
///////////////////////////////////////////////////////////////////////////////////////////////////

std::pair<unordered_set<string>, int> findWikiLinks(const string& inp) {
    /* Delimiter for start of a link  */
    static const string delim = "href=\"/wiki/";

    unordered_set<string> ret;

    auto url_start = inp.begin();
    auto end = inp.end();

    int invalid_cnt = 0;
    auto cnt = 0;

    while(true) {

        // TODO: ASSIGNMENT 2 TASK 1:
        // Set url_start to the next location of "delim" (starting your search at url_start), using std::search.
        // After doing so, break out of the while loop if there are no occurrences of delim left
        // (use your work from the line above).
        // Estimated length: 2-3 lines

        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // BEGIN STUDENT CODE HERE
        // Please delete this line when you start working!
        auto next_delim = std::search(url_start, end, delim.begin(), delim.end());
        if (next_delim == end) {
            break;
        } 
        url_start = next_delim + delim.size();

        // END STUDENT CODE HERE
        ///////////////////////////////////////////////////////////////////////////////////////////////////

        // TODO: ASSIGNMENT 2 TASK 2:
        // Set url_end to the end of the wikilink. Start searching after the delimeter you found above.
        // Make sure to use std::find! (std::find looks for a single element in a container, e.g. character in 
        // a string—std::search looks for a series of elements in a container, like a substring in a string. 
        // remember that a string is represented as an array of characters, and is also a container!)
        // Estimated length: 1 lines

        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // BEGIN STUDENT CODE HERE (delete/edit this line)
        auto url_end = std::find(url_start, end, '"');
        // END STUDENT CODE HERE
        ///////////////////////////////////////////////////////////////////////////////////////////////////

        // TODO: ASSIGNMENT 2 TASK 3:
        // Last exercise of this function! Create a string from the two iterators (url_start and url_end) above
        // using a string constructor. Make sure you start the string AFTER the delimiter you found in task 5!
        // Estimated length: 1 lines
        
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // BEGIN STUDENT CODE HERE (delete/edit this line)
        string link = string(url_start, url_end);
        if (cnt < 20) {
            cnt += 1;
        }
        // END STUDENT CODE HERE
        ///////////////////////////////////////////////////////////////////////////////////////////////////

        /*
         * Only add link to the set if it is valid i.e. doesn't
         * contain a ':' or a '#'.
         */
        if(valid_wikilink(link)){
            auto [trash, inserted] = ret.insert(link);
            if (!inserted) {
                invalid_cnt += 1;
            } else {
                cout << link << endl;
            }
        } else {
            invalid_cnt += 1;
        }

        url_start = url_end + 1;

    }
    return std::make_pair(ret, invalid_cnt);
}


// run below to print out all valid page names:
// g++ -std=c++17 wikiscraper2.cpp -o scrapper
// ./scrapper 
int main() {
    printf("In Main!\n");
    std::string content;
    std::ifstream file("test-resources/Germany.html");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            content += line + "\n";  // Append each line to the content string
        }
    }
    file.close();
    auto temp = findWikiLinks(content);
    cout << temp.first.size() << endl;
    cout << temp.second << endl; // invalid cnt includes strings with : or # and duplicates. 
}

