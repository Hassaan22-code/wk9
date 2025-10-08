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

    // Read with per-exception message, always close, then rethrow
    void read(Records &records) {
        _file.open(_filename, ios::in);
        if (!_file.is_open()) {
            throw runtime_error("could not open file");
        }

        try {
            string line;
            while (getline(_file, line)) {
                int value = stoi(line);          // may throw
                records.push_back(value);
            }
            _file.close();                        // normal path
        }
        catch (const invalid_argument&) {
            cout << "invalid_argument error" << endl;
            if (_file.is_open()) _file.close();
            throw;                                // propagate to main()
        }
        catch (const out_of_range&) {
            cout << "out_of_range error" << endl;
            if (_file.is_open()) _file.close();
            throw;
        }
        catch (...) {                             // anything unexpected
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
        // After read() prints the specific tag, report the exception to the user
        cerr << e.what() << endl;
        return 1;
    }

    long long sum = 0;
    for (size_t i = 0; i < myRecords.size(); ++i) sum += myRecords[i];
    cout << sum << endl;
    return 0;
}
