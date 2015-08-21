#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>



struct pack{
    float time;
    int seq_nr;
    int ack_nr;
    int size;
};

struct SEQ{
    float time;
    int seq_nr;
    int size;
};


using namespace std;
int main(){
    vector<struct pack> packets;
    struct pack tmp_packet;

    string line;
    char filename[40];
    cin.getline(filename, 40);

    ifstream the_file;
    the_file.open(filename);
    string word;
    stringstream ss;
    int tmp_int;
    float tmp_float;
    ss.clear();
getline(the_file, line);

    //parse file, each packet in vector<struct pack>
    while(the_file){
        getline(the_file, line);
//cout << line << endl << endl;
        ss << line;
        for(int i = 0; i<9; ++i){
            ss >> word;
           cout << '(' << i << ')' + word << endl;

            switch (i){
                case 1:
                    tmp_float = atof(word.c_str());
                    //cout << tmp_packet.time << endl;
                    tmp_packet.time=tmp_float;
                    break;
                case  5:
                    tmp_int = atoi(word.c_str());
                    tmp_packet.size = tmp_int;
                    break;
                case  6:
                    tmp_int = atoi(word.c_str());
                    tmp_packet.seq_nr = tmp_int;
                    break;
                case  7:
                    tmp_int = atoi(word.c_str());
                    tmp_packet.ack_nr = tmp_int;
                    break;
            }
            
        }
        ss.str("");
//        ss.clear();
        packets.push_back(tmp_packet);
    }
    the_file.close();
    /*
       tmp_packet.seq_nr = -1;
       packets.push_back(tmp_packet);
       */

    int tot_size = 0;
    for(std::vector<struct pack>::iterator it = packets.begin(); it != packets.end(); ++it){
    //    cout << it->size << endl;
      //cout << it->time << endl;
        tot_size += it->size;
    cout << tot_size << endl;
    }
    cout << tot_size << endl;


    /*
       char teest[100];
       ack_file >> teest;

       while(ack_file.good()){
       std::cout << teest << " ";
       ack_file >> teest;
       }
       std::map<int, float> Ack_map;
       Ack_map[233] = 2.55;
       std::cout << Ack_map[233] << std::endl;
       */
    return 0;
}
