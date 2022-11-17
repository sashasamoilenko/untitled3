#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

class Multer {
public:
    virtual void multiply() = 0;
};

class Lint {
private:
    vector<int> digits;
    static Multer *multer;

public:
    Lint() {
    }

    Lint (string digits_str) {
        for(int i = digits_str.size()-1; i >= 0 ; --i){
            digits.push_back(digits_str[i] - '0');
        }
    }

    Lint operator*(Lint other) {
        Lint res, res1;
        int carry, d, counter = 0;

        int max_len = digits.size() > other.digits.size() ? digits.size() : other.digits.size();
        vector<int> inter(2 * max_len);

        for (int i = 0; i < 2 * max_len; ++i) {
            inter[i] = 0;
        }

        for (int i = 0; i < digits.size(); ++i) {
            carry = 0;
            for (int j = 0; j < other.digits.size(); ++j) {
                d = inter[i + j] + digits[i] * other.digits[j] + carry;
                inter[i + j] = d % 10;
                carry = d / 10;
            }
            inter[i + other.digits.size()] += carry;
        }

        for (int i = 0; i < 2 * max_len; ++i) {
            res.digits.push_back(inter[i]);
        }

        return cut_null(res);

    }

    Lint operator-(Lint other) {
        Lint res, res1;
        int d = 0;
        int m = 0, counter = 0;

        int max_len = digits.size() > other.digits.size() ? digits.size() : other.digits.size();
        try {
            if (digits.size() < other.digits.size())
                throw "You subtracted from the larger number the smaller one";
            for (int i = 0; i < max_len; ++i) {

                if (i < digits.size()) {
                    d = digits[i] - m;
                    m = 0;
                }

                if (i < other.digits.size()) {
                    d -= other.digits[i];
                }

                if (d < 0) {
                    d += 10;
                    m = 1;
                }
                res.digits.push_back(d);
            }

            return cut_null(res);
        }
        catch (const char *exception) {
            std::cerr << "Error: " << exception << '\n';
        }
        return Lint();
    }

    Lint operator+(Lint other) {
        Lint res;
        int d = 0;

        int max_len = digits.size() > other.digits.size() ? digits.size() : other.digits.size();

        for (int i = 0; i < max_len; ++i) {

            if (i < digits.size()) {
                d += digits[i];
            }

            if (i < other.digits.size()) {
                d += other.digits[i];
            }

            res.digits.push_back(d % 10);
            d = d / 10;
        }

        if (d > 0){
            res.digits.push_back(d);
        }
        return res;
    }

    bool operator>(Lint other) {
        int counter;

        if (digits.size() < other.digits.size()){
            int i = other.digits.size() - 1;
            while (other.digits[i] == 0) {
                counter += 1;
                i -= 1;
            }
            if (digits.size() < other.digits.size() - counter){
                return false;
            }
        }
        else if (digits.size() == other.digits.size()){
            for (int i = digits.size() - 1; i >= 0; --i){
                if (digits[i] > other.digits[i]) {
                    break;
                }
                else if (digits[i] < other.digits[i]){
                    return false;
                }
            }
        }

        if (digits.size() > other.digits.size()) {
            int i = digits.size() - 1;
            while (digits[i] == 0) {
                counter += 1;
                i -= 1;
            }
            if (digits.size() - counter < other.digits.size()){
                return false;
            }
        }

        return true;
    }

    bool operator==(Lint other) {
        bool res = true;

        if (digits.size() < other.digits.size() || digits.size() > other.digits.size()){
            res = false;
        }
        else if (digits.size() == other.digits.size()){
            for (int i = digits.size() - 1; i >= 0; --i){
                if (digits[i] > other.digits[i]) {
                    res = false;
                }
                else if (digits[i] < other.digits[i]){
                    res = false;
                }
            }
        }
        return res;
    }

    Lint operator/(int a) {
        Lint res;
        vector<int> mid (digits.size());

        for (int i = digits.size() - 1; i > 0; --i){
            mid[i] = digits[i] / a;
            digits[i-1] = digits[i-1] + (digits[i] % a)*10;
        }
        mid[0] = digits[0] / a;

        for (int i = 0; i < mid.size() ; ++i) {
            res.digits.push_back(mid[i]);
        }

        return res;
    }

    void print() {
        for (int i = digits.size()-1; i >= 0 ; --i) {
            cout << digits[i];
        }
        cout << endl;
    }

    friend ostream& operator<<(ostream &stream, Lint x);
    friend Lint Karat_mult (Lint a, Lint b);
    friend Lint S_S (Lint a, Lint b);
    friend Lint div_rest (Lint a, Lint b);
    friend bool Ferma (Lint p);
    friend Lint cut_null(Lint a);
};

Lint cut_null(Lint a) {
    int counter = 0;
    Lint res;

    if (a.digits.size() == 1) {
        return a;
    }
    else {
        int i = a.digits.size() - 1;
        while (a.digits[i] == 0) {
            counter += 1;
            i -= 1;
        }
    }

    for (int i = 0; i < a.digits.size() - counter; ++i) {
        res.digits.push_back(a.digits[i]);
    }

    return res;
}
