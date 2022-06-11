#include <string>
#include <fstream>

using namespace std;

void Binary_Output(string file_name, string binary_text) {
    ofstream oF(file_name, ios_base::binary);
    int bad_count = 8 - binary_text.size() % 8;
    string bad_code = "";
    while (--bad_count)
        bad_code += '0';
    bad_code += '1';
    binary_text = bad_code + binary_text;
    uint8_t single[8];
    unsigned int n = 1;
    for (auto it = binary_text.begin(); it != binary_text.end(); it++, n++) {
        single[n - 1] = (uint8_t)(*it - '0' == 1);
        if (n == 8) {
            uint8_t temp = 0x00;
            for (int i = 0; i < 8; i++)
                temp |= single[i] << (7 - i);
            oF.write((char*)&temp, sizeof(uint8_t));
            n = 0;
        }
    }
    oF.close();
    return;
}

string Binary_Input(string file_name) {
    ifstream iF(file_name);
    iF.seekg(0, ios::end);
    size_t length = iF.tellg();
    iF.seekg(0, ios::beg);
    uint8_t* data = new uint8_t[length];
    iF.read((char*)data, length * sizeof(uint8_t));
    iF.close();
    string binary_text = "";
    for (int i = 0; i < length; i++)
        for (int j = 7; j >= 0; j--)
            binary_text += ('0' + ((data[i] >> j) % 2));
    for (int i = 0; i < 8; i++)
        if (binary_text[i] == '1')
            return binary_text.substr(++i, string::npos);
    return binary_text;
}