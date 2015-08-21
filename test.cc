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
    int port;
};

struct SEQ{
    float time;
    int seq_nr;
    int size;
};

using namespace std;

void parse_input(vector<struct pack> *packets, char* filename)
{
    ifstream the_file;
    the_file.open(filename);
    int tmp_int;
    struct pack tmp_packet;
    float tmp_float;
    string word;
    string line;
    stringstream ss;

    getline(the_file, line);
    while(the_file){
        getline(the_file, line);
        ss << line;
        for(int i = 0; i<9; ++i){
            ss >> word;
            //cout << '(' << i << ')' + word << endl;

            switch (i){
                case 1:
                    tmp_packet.time = atof(word.c_str());
                    break;
                case  5:
                    tmp_packet.port = atoi(word.c_str());
                    break;
                case  6:
                    tmp_packet.seq_nr = atoi(word.c_str());
                    break;
                case  7:
                    tmp_packet.ack_nr = atoi(word.c_str());
                    break;
            }

        }
        ss.str("");
        packets->push_back(tmp_packet);
    }
    the_file.close();
}


int main(){
    vector<struct pack> sent_packets;
    vector<struct pack> acked_packets;

    string source_port;
    char filename1[40];
    char filename2[40];

    cout << "in-file (sent): ";
    cin.getline(filename1, 40);

    cout << "in-file (ack): ";
    cin.getline(filename2, 40);

    parse_input(&sent_packets, filename1);
    parse_input(&acked_packets, filename2);

    //parse file, each packet in vector<struct pack>
    int tot_size = 0;

    //<time, unacked bytes>
    map<float, int> unack_map;

    for(std::vector<struct pack>::iterator it = sent_packets.begin(); it != sent_packets.end(); ++it){
        
    /*
    unack_map[1.04] = 8;
    unack_map[2.04] = 7;
    unack_map[1.05] = 6;
    unack_map[1.03] = 10;
*/
    for(std::map<float, int>::iterator it = unack_map.begin(); it != unack_map.end(); ++it){
        cout << it->second << endl;
    }
    bool base_found = false;

    int seq_nr;

    int big_sent = 0;
    int big_acked = 0;
/*
    //itterate through vector
    std::vector<struct pack>::iterator it2;
    for(std::vector<struct pack>::iterator it = packets.begin(); it != packets.end(); ++it){
        //find base seq
        if(!base_found && it->port == source_port)
            base_seq = it->seq_nr;

        if(it->port == source_port){
            if(big_sent < it->seq_nr)
                big_sent = it->seq_nr; 

        }else{
            if(big_acked < it->ack_nr)
                big_acked = it->ack_nr;
        }




        //    cout << it->size << endl;
        //cout << it->time << endl;
        current = it-seq_nr;
        size
            tot_size += it->size;
        cout << tot_size << endl;
    }
    cout << tot_size << endl;

*/
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

