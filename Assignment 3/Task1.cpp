#include <iostream>
#include <string>
using namespace std;

// XOR operation between two binary strings
string findXor(const string &a, const string &b) {
    string result = "";
    for (int i = 1; i < b.length(); i++)
        result += (a[i] == b[i]) ? '0' : '1';
    return result;
}

// Performs Modulo-2 division
string mod2div(string dividend, const string &divisor) {
    int pick = divisor.length();
    string tmp = dividend.substr(0, pick);

    while (pick < dividend.length()) {
        if (tmp[0] == '1')
            tmp = findXor(divisor, tmp) + dividend[pick];
        else
            tmp = findXor(string(pick, '0'), tmp) + dividend[pick];
        pick++;
    }

    // Final step after loop
    if (tmp[0] == '1')
        tmp = findXor(divisor, tmp);
    else
        tmp = findXor(string(pick, '0'), tmp);

    return tmp;
}

// Encode data using CRC
string encodeData(const string &data, const string &key) {
    int keyLen = key.length();
    string appendedData = data + string(keyLen - 1, '0');
    
    cout << "\nAppended Data (with zeros): " << appendedData << endl;

    string remainder = mod2div(appendedData, key);
    cout << "Remainder (CRC bits): " << remainder << endl;

    return data + remainder;
}

int main() {
    string data = "1101011011";
    string key  = "10011"; // Generator polynomial (x^4 + x + 1)

    cout << "=== CRC ENCODING PROGRAM ===" << endl;
    cout << "Input Data: " << data << endl;
    cout << "Generator Key: " << key << endl;

    string codeword = encodeData(data, key);

    cout << "\nTransmitted Codeword: " << codeword << endl;
    cout << "==============================" << endl;

    return 0;
}
