#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

typedef vector<int> Records;

class RecordsManager {
private:
    fstream _file;
    string _filename;
public:
    RecordsManager(string filename) : _filename(filename) {}

    void read(Records &records) {
        _file.open(_filename, ios::in);
        if (!_file.is_open()) {
            throw runtime_error("could not open file");
        }

        try {
            string line;
            while (getline(_file, line)) {
                int value = stoi(line);
                records.push_back(value);
            }
            _file.close();
        }
        catch (const invalid_argument&) {
            cout << "invalid_argument error" << endl;
            if (_file.is_open()) _file.close();
            throw;
        }
        catch (const out_of_range&) {
            cout << "out_of_range error" << endl;
            if (_file.is_open()) _file.close();
            throw;
        }
        catch (...) {
            if (_file.is_open()) _file.close();
            throw;
        }
    }
};

int main(int argc, char* argv[]) {
    Records myRecords;
    string filename = "records.txt";
    if (argc > 1) filename = argv[1];
    RecordsManager recordM(filename);

    try {
        recordM.read(myRecords);
    } catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }

    long long sum = 0;
    for (size_t i = 0; i < myRecords.size(); ++i)
        sum += myRecords[i];

    cout << sum << endl;
    return 0;
}
