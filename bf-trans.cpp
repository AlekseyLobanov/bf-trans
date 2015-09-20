#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <cstdint>

using namespace std;

void proc(istream& is){
    set< char > COMMANDS = { '<', '>', '+', '-', '.', ',', '[', ']' };
    const size_t CELL_NUM = 30000;
    vector< uint8_t > cells(CELL_NUM, 0);
    ssize_t cur_cell = 0;
    ssize_t rec_level = 0;
    vector< char > script;
    while ( is.good() ){
        char cur_ch;
        is >> cur_ch;
        if ( COMMANDS.find(cur_ch) == COMMANDS.end() )
            continue;
        script.push_back(cur_ch);
    }
    for (size_t cur_ch_ind = 0; cur_ch_ind < script.size(); ++cur_ch_ind) {
        char cur_ch = script.at(cur_ch_ind);
        switch ( cur_ch ) {
            case '>': {
                ++cur_cell;
                break;
            }
            case '<': {
                --cur_cell;
                break;
            }
            case '+': {
                ++cells.at(cur_cell);
                break;
            }
            case '-': {
                --cells.at(cur_cell);
                break;
            }
            case '.': {
                cout << cells.at(cur_cell);
                break;
            }
            case ',': {
                char t;
                cin >> t;
                cells.at(cur_cell) = t;
                break;
            }
            case '[': {
                if( !cells[cur_cell] ) {
                    ++rec_level;
                    while( rec_level ) {
                        ++cur_ch_ind;
                        if ( '[' == script[cur_ch_ind]  )
                            ++rec_level;
                        if ( ']' == script[cur_ch_ind] )
                            --rec_level;
                    }
                }else
                    continue;
                break;
            }
            case ']': {
                if( !cells[cur_cell] ) {
                    continue;
                }
                else {
                    if( ']' == script[cur_ch_ind] )
                        rec_level++;
                    while( rec_level ) {
                        --cur_ch_ind;
                        if( '[' == script[cur_ch_ind] )
                            rec_level--;
                        if( ']' == script[cur_ch_ind] )
                            rec_level++;
                    }
                    --cur_ch_ind;
                }
                break;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if ( 1 == argc )
        proc(cin);
    else {
        ifstream fin(argv[1]);
        proc(fin);
    }
    return 0;
}
