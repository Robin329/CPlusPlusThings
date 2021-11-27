//
// Created by renbin jiang on 2021/4/25.
//
#include <iomanip>
#include <iostream> // align
using namespace std;

struct inflatable {
    char name[20];
    float volume;
    double price;
};

struct torgle_reg {
    unsigned int sn : 4;
    unsigned int : 4;
    bool goodIn : 1;
    bool goodTorgle : 1;
};

struct widget {
    char *brand;
    int type;
    union id {
        long id_num;
        char id_char[20];
    } id_val;
};
int main(int argc, char **argv) {
    inflatable duck{"robin", 0.12, 9.98};
    inflatable choice;
    choice = duck;

    cout << "choice.name: " << setw(8) << choice.name << "\nchoice.volume:" << setw(8) << choice.volume
         << "\nchoice.price:" << setw(8) << choice.price << endl;

    cout << "1.-------------------" << endl;
    cout << "Right align:\n";
    cout.fill('0');
    cout << "choice.name:" << choice.name << "\nchoice.volume:" << setw(8) << choice.volume
         << "\nchoice.price:" << setw(8) << choice.price << endl;
    cout << "2.-------------------" << endl;
    torgle_reg tr = {14, true, false};
    if (tr.goodIn) {
        cout << "tr.goodTorgle is true" << endl;
    }
    cout << "3.-------------------" << endl;
    widget prize;
    //  prize.type = 1;
    if (prize.type == 1) {
        cin >> prize.id_val.id_num;
    } else {
        //    cin >> prize.brand;
        //    cin >> prize.id_val.id_char;
    }
    cout << "prize.brand:" << prize.brand << endl;
    cout << "prize.id_val.id is:" << prize.id_val.id_char << endl;
    cout << "prize.id_val.id is:" << prize.id_val.id_num << endl;
    cout << "4.-------------------" << endl;
    char msg1[] = "robin";
    char *msg2 = "robin";
    cout << sizeof(msg1) << endl;
    for (int i = 0; i < sizeof(msg1); i++) {
        cout << "msg1 + i:" << msg1 + i << endl;
        cout << "i:" << msg1[i] << endl;
    }
    for (int i = 0; i < sizeof(msg2); i++) {
        cout << "msg2:" << msg2++ << endl;
    }

    return 0;
}