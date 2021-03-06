/*Takes two files with tcp-data and creates file
 * with time and unacknowledged bytes sent which can
 * later be plotted.
 */




#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <cstring>


struct pack{
    float time;
    int seq_nr;
    int ack_nr;
};

struct in_air{
    int seq;
    int ack;
};

using namespace std;

void parse_input(vector<struct pack> *packets, char* filename)
{
    ifstream the_file;
    the_file.open(filename);

    struct pack tmp_packet;
    string word;
    string line;
    stringstream ss;
    int handshaker = 0;

    getline(the_file, line);
    while(the_file){
        ss << line;
        for(int i = 0; i<10; ++i){
            ss >> word;
            switch (i){
                case 1:
                    tmp_packet.time = atof(word.c_str());
                    break;
                case  7:
                    tmp_packet.seq_nr = atoi(word.c_str());
                    break;
                case  8:
                    tmp_packet.ack_nr = atoi(word.c_str());
                    break;
                case 9:
                    handshaker = word.compare("Not");
                    break;
            }
        }
        ss.str("");

        if(handshaker == 0)
            packets->push_back(tmp_packet);

        getline(the_file, line);
    }
    the_file.close();
}


int main(){
    vector<struct pack> sent_packets;
    vector<struct pack> acked_packets;

    int z=1; // set to 0 to make fast run but strict file names
    char filename1[40];
    char filename2[40];
    if(z){
        cout << "in-file (sent): ";
        cin.getline(filename1, 40);

        cout << "in-file (ack): ";
        cin.getline(filename2, 40);
    }else{
        strcpy(filename1, "seq.txt");
        strcpy(filename2, "ack.txt");
    }

    parse_input(&sent_packets, filename1);
    parse_input(&acked_packets, filename2);

    //<time, {seq, ack}>
    map<float, struct in_air> unack_map;
    struct pack next_sent;

    //add seq to map
    for(std::vector<struct pack>::iterator it1 = sent_packets.begin(); it1 != sent_packets.end(); ++it1){
        for(std::vector<struct pack>::iterator it3 = it1; it3 != sent_packets.end(); ++it3){
            if(it1->seq_nr < it3->seq_nr){
                next_sent = *it3;
                break;
            }
        }
        unack_map[it1->time].seq = next_sent.seq_nr;  
        unack_map[it1->time].ack = 0;  
    }

    //add ack to map
    for(std::vector<struct pack>::iterator it1 = acked_packets.begin(); it1 != acked_packets.end(); ++it1){
        unack_map[it1->time].ack = it1->ack_nr;  
        unack_map[it1->time].seq = 0;  
    } 

    //itterate through map and adjust it (replace 0's)
    int latest_seq = 0;
    int latest_ack = sent_packets.at(0).seq_nr;
    for(map<float, struct in_air>::iterator it1 = unack_map.begin(); it1 != unack_map.end(); ++it1){
        if(it1->second.seq != latest_seq && it1->second.seq != 0)
            latest_seq = it1->second.seq;

        if(it1->second.ack != latest_ack && it1->second.ack != 0)
            latest_ack = it1->second.ack;

        it1->second.seq = latest_seq;
        it1->second.ack = latest_ack;
    }

    cout << "printing to file..." << endl;
    ofstream outfile;
    outfile.open("t_vs_cwnd.txt");
    int points = 0;

    for(std::map<float, struct in_air>::iterator it = unack_map.begin(); it != unack_map.end(); ++it){
        outfile << it->first << " " << it->second.seq << " " << it->second.ack << " " << it->second.seq - it->second.ack << endl;
        ++points;
    }

    cout << points << " data-points printed..." << endl;
    cout << "Done!" << endl;

    return 0;
}
