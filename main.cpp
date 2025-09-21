#include <bits/stdc++.h>
using namespace std;
string cleanInput(const string &raw) {
    string out;
    out.reserve(raw.size());
    for (char c : raw) {
        if (c == ' ' || c == '-') continue;
        if (!isdigit(static_cast<unsigned char>(c))) return "";
        out.push_back(c);
    }
    return out;
}

string detectIssuer(const string &digits) {
    if (digits.empty()) return "Unknown";

    if (digits[0] == '4') return "Visa";

    if (digits.size() >= 2) {
        int p2 = stoi(digits.substr(0, 2));
        if (p2 >= 51 && p2 <= 55) return "MasterCard";
    }

    if (digits.size() >= 4) {
        int p4 = stoi(digits.substr(0, 4));
        if (p4 >= 2221 && p4 <= 2720) return "MasterCard";
    }

    return "Unknown";
}

bool lengthValidForIssuer(const string &digits, const string &issuer) {
    int len = static_cast<int>(digits.size());
    if (issuer == "Visa") {
        return (len == 13 || len == 16 || len == 19);
    } else if (issuer == "MasterCard") {
        return (len == 16);
    }
    return false;
}

bool luhnCheck(const string &digits) {
    int n = static_cast<int>(digits.size());
    int sum = 0;
    bool doubleDigit = false;

    for (int i = n - 1; i >= 0; --i) {
        int d = digits[i] - '0';
        if (doubleDigit) {
            d *= 2;
            if (d > 9) d -= 9;
        }
        sum += d;
        doubleDigit = !doubleDigit;
    }
    return (sum % 10) == 0;
}

string maskNumber(const string &digits) {
    int n = static_cast<int>(digits.size());
    if (n <= 4) return digits;
    string masked;
    masked.append(max(0, n - 4), '*');
    masked += digits.substr(n - 4);
    return masked;
}

int main() {
    cout << "\033[31mThis is red text\033[0m\n";

    cout << "Enter a credit card number (spaces/dashes allowed):\n";
    string raw;
    if (!getline(cin, raw)) return 0;

    string digits = cleanInput(raw);
    if (digits.empty()) {
        cout << "Input error: contains invalid characters. Use digits, spaces, or dashes only.\n";
        return 0;
    }

    string issuer = detectIssuer(digits);
    if (issuer == "Unknown") {
        cout << "Issuer: Unknown (only Visa and MasterCard are supported by this validator)\n";
        cout << "Result: INVALID\n";
        return 0;
    }

    if (!lengthValidForIssuer(digits, issuer)) {
        cout << "Issuer: " << issuer << "\n";
        cout << "Length check: FAILED for " << issuer << " (found " << digits.size() << " digits)\n";
        cout << "Result: INVALID\n";
        return 0;
    }

    bool ok = luhnCheck(digits);
    if (!ok) {
        cout << "Issuer: " << issuer << "\n";
        cout << "Luhn checksum: FAILED\n";
        cout << "Result: INVALID\n";
        return 0;
    }

    cout << "Issuer: " << issuer << "\n";
    cout << "Card:   " << maskNumber(digits) << "\n";
    cout << "Result: VALID\n";

    return 0;
}
