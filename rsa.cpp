#include <iostream>
#include <vector>
#include <string>
using namespace std;

class RSA {
private:
    int p, q, n, phi, e, d;

    // Helper functions
    int gcd(int a, int b) {
        while (b != 0) {
            int t = b;
            b = a % b;
            a = t;
        }
        return a;
    }

    int modInverse(int e, int phi) {
        for (int i = 1; i < phi; ++i) {
            if ((e * i) % phi == 1)
                return i;
        }
        return -1;
    }

    long long modPow(long long base, long long exp, long long mod) {
        long long res = 1;
        base %= mod;
        while (exp > 0) {
            if (exp % 2 == 1)
                res = (res * base) % mod;
            base = (base * base) % mod;
            exp /= 2;
        }
        return res;
    }

    int findE(int phi) {
        for (int i = 3; i < phi; i += 2) {
            if (gcd(i, phi) == 1)
                return i;
        }
        return -1;
    }

    vector<long long> encrypt(const string &message) {
        vector<long long> encrypted;
        for (char ch : message) {
            long long m = static_cast<int>(ch);
            long long c = modPow(m, e, n);
            encrypted.push_back(c);
        }
        return encrypted;
    }

    string decrypt(const vector<long long> &ciphertext) {
        string message;
        for (long long c : ciphertext) {
            long long m = modPow(c, d, n);
            message += static_cast<char>(m);
        }
        return message;
    }

public:
    void genKey() {
    int p=11,q=13; 

        n = p * q;
        phi = (p - 1) * (q - 1);

        e = findE(phi);
        if (e == -1) {
            cout << "Failed to find suitable 'e'. Exiting.\n";
            return;
        }

        d = modInverse(e, phi);
        if (d == -1) {
            cout << "Failed to find modular inverse for 'e'. Exiting.\n";
            return;
        }

        cout << "Public Key: (" << e << ", " << n << ")\n";
        cout << "Private Key: (" << d << ", " << n << ")\n";

        string message;
        cout << "\nEnter message to encrypt: ";
        getline(cin, message);

        vector<long long> encrypted = encrypt(message);
        cout << "\nEncrypted message (numeric values):\n";
        for (auto val : encrypted) {
            cout << val << " ";
        }

        string decrypted = decrypt(encrypted);
        cout << "\n\nDecrypted message: " << decrypted << "\n";
    }
};

int main() {
    RSA rsa;
    rsa.genKey();
    return 0;
} 
