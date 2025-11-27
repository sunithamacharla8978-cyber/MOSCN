#include <iostream>
#include <string>
using namespace std;

// XOR operation between two binary strings
string findXor(string a, string b) {
    string result = "";
    for (int i = 1; i < b.length(); i++) {
        result += (a[i] == b[i]) ? '0' : '1';
    }
    return result;
}

// Modulo-2 Division
string mod2div(string dividend, string divisor) {
    int pick = divisor.length();
    string temp = dividend.substr(0, pick);

    while (pick < dividend.length()) {
        if (temp[0] == '1')
            temp = findXor(divisor, temp) + dividend[pick];
        else
            temp = findXor(string(pick, '0'), temp) + dividend[pick];
        pick++;
    }

    // Last step after loop
    if (temp[0] == '1')
        temp = findXor(divisor, temp);
    else
        temp = findXor(string(pick, '0'), temp);

    return temp;
}

// Encode the data using CRC
string encodeData(string data, string key) {
    int keyLen = key.length();
    string appendedData = data + string(keyLen - 1, '0');
    string remainder = mod2div(appendedData, key);

    cout << "\nRemainder: " << remainder << endl;
    return data + remainder;
}

// Receiver check for error detection
bool receiverCheck(string codeword, string key) {
    string remainder = mod2div(codeword, key);
    return (remainder.find('1') == string::npos);
}

int main() {
    string data = "10011101";
    string key = "1001"; // Polynomial: x^3 + 1

    cout << "=== CRC ENCODING PROCESS ===" << endl;
    cout << "Data: " << data << endl;
    cout << "Key: " << key << endl;

    string codeword = encodeData(data, key);
    cout << "Encoded (Transmitted) Codeword: " << codeword << endl;

    // Introduce an error in bit position 3
    string received = codeword;
    received[2] = (received[2] == '0') ? '1' : '0';
    cout << "Received Codeword (error at bit 3): " << received << endl;

    if (receiverCheck(received, key))
        cout << "Receiver Output: No Error Detected ?" << endl;
    else
        cout << "Receiver Output: Error Detected ?" << endl;

    return 0;
}
