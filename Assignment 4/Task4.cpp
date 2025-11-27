#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Hamming {
public:
    string data;
    int m, r = 0; 
    char* msg;

    Hamming(string data) {
        this->data = data;

        reverse(data.begin(), data.end());
        m = data.size();

        int power = 1;

        // find redundant bits
        while (power < (m + r + 1)) {
            r++;
            power *= 2;
        }

        msg = new char[m + r + 1];

        int idx = 0;

        // fill msg with data bits and placeholders for redundant bits
        for (int i = 1; i <= m + r; i++) {
            if (i & (i - 1)) {
                msg[i] = data[idx++];
            } else {
                msg[i] = 'n';
            }
        }

        setRedundantBits();
    }

    ~Hamming() {
        delete[] msg;
    }

    void showMsg() {
        cout << "Data packet to be sent: ";
        for (int i = m + r; i >= 1; i--) {
            cout << msg[i] << " ";
        }
        cout << endl;
    }

    void setRedundantBits() {
        int bitPos = 0;

        for (int i = 1; i <= m + r; i *= 2) {
            int count = 0;

            for (int j = i + 1; j <= m + r; j++) {
                if (j & (1 << bitPos)) {
                    if (msg[j] == '1') count++;
                }
            }

            msg[i] = (count & 1) ? '1' : '0';
            bitPos++;
        }

        showMsg();
    }

    void receiver() {
        string ans = "";
        int bitPos = 0;

        for (int i = 1; i <= m + r; i *= 2) {
            int count = 0;

            for (int j = i + 1; j <= m + r; j++) {
                if (j & (1 << bitPos)) {
                    if (msg[j] == '1') count++;
                }
            }

            // compare parity
            if (count & 1) {
                ans.push_back(msg[i] == '1' ? '0' : '1');
            } else {
                ans.push_back(msg[i] == '0' ? '0' : '1');
            }

            bitPos++;
        }

        // check for wrong bit
        if (ans.find('1') != string::npos) {
            int wrongBit = 0, power = 1;

            for (int i = 0; i < ans.size(); i++) {
                if (ans[i] == '1') wrongBit += power;
                power *= 2;
            }

            cout << "Error found at bit position: " << wrongBit << endl;
        } else {
            cout << "Correct data packet received." << endl;
        }
    }
};

int main() {
    string data = "1011001";
    Hamming h(data);

    // Introduce error (optional)
    // int pos = 3;
    // h.msg[pos] = (h.msg[pos] == '0' ? '1' : '0');

    h.receiver();
    return 0;
}