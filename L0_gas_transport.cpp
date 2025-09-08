#include <iostream>
using namespace std;

class Pipe {
    public:
        string km_mark;
        float lenght; // km
        float diameter; // mm
        bool is_in_repair;
};

class CompressorStation {
    public:
        string name;
        int workshop_count;
        int current_working_workshop_count; 
        float station_cls; // я так и не понял какой нужен тип
};

int main()
{
    int user_input;
    while (true) {
        cin >> user_input;
        switch (user_input){
        case 1: // add pipe
        case 2: // add CS
        case 3: // see all objects
        case 4: // change pipe
        case 5: // change CS
        case 6: // save
        case 7: // load
        case 0: // exit
        default: cout << "Input is incorrect\n try digits in range 0-7";
        }
    }
}

