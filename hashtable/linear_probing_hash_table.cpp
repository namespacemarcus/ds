#include <iostream>
using namespace std;

enum State {
    STATE_UNUSE,
    STATE_USING,
    STATE_DEL,
};

struct Bucket {
    Bucket(int key = 0, State state = STATE_UNUSE) : key_(key), state_(state) {}

    int key_;
    State state_;
};

class HashTable {
public:
    HashTable(int size = primes_[0], double loadFactor = 0.75)
        : useBucketNum_(0),
          loadFactor_(loadFactor),
          primeIdx_(0) {
        if (size != primes_[0]) {
            for (; primeIdx_ < PRIME_SIZE; primeIdx_++) {
                if (primes_[primeIdx_] >= size) {
                    break;
                }
            }
            if (primeIdx_ == PRIME_SIZE) {
                primeIdx_--;
            }
        }
        tableSize_ = primes_[primeIdx_];
        table_ = new Bucket[tableSize_];
    }

    ~HashTable() {
        delete[] table_;
        table_ = nullptr;
    }

public:
    bool insert(int key) {
        double factor = useBucketNum_ * 1.0 / tableSize_;
        cout << "factor:" << factor << endl;
        if (factor > loadFactor_) {
            expand();
        }

        int idx = key % tableSize_;
        if (table_[idx].state_ != STATE_USING) {
            table_[idx].state_ = STATE_USING;
            table_[idx].key_ = key;
            useBucketNum_++;
            return true;
        }
        for (int i = (idx + 1) % tableSize_; i != idx;
             i = (i + 1) % tableSize_) {
            if (table_[i].state_ != STATE_USING) {
                table_[i].state_ = STATE_USING;
                table_[i].key_ = key;
                useBucketNum_++;
                return true;
            }
        }
        return false;
    }

    bool erase(int key) {
        int idx = key % tableSize_;
        if (table_[idx].state_ == STATE_USING && table_[idx].key_ == key) {
            table_[idx].state_ = STATE_DEL;
            useBucketNum_--;
        }
        for (int i = (idx + 1) % tableSize_;
             i != idx && table_[i].state_ != STATE_UNUSE;
             i = (i + 1) % tableSize_) {
            if (table_[i].state_ == STATE_USING && table_[i].key_ == key) {
                table_[i].state_ = STATE_DEL;
                useBucketNum_--;
            }
        }
        return true;
    }

    bool find(int key) {
        int idx = key % tableSize_;
        if (table_[idx].state_ == STATE_USING && table_[idx].key_ == key) {
            return true;
        }
        for (int i = (idx + 1) % tableSize_;
             i != idx && table_[i].state_ != STATE_UNUSE;
             i = (i + 1) % tableSize_) {
            if (table_[i].state_ == STATE_USING && table_[i].key_ == key) {
                return true;
            }
        }
        return false;
    }

private:
    void expand() {
        primeIdx_++;
        if (primeIdx_ == PRIME_SIZE) {
            throw "HashTable is too large! can not expand anymore!";
        }

        Bucket *newTable = new Bucket[primes_[primeIdx_]];
        for (int i = 0; i < tableSize_; i++) {
            if (table_[i].state_ == STATE_USING) {
                int idx = table_[i].key_ % primes_[primeIdx_];
                if (newTable[idx].state_ != STATE_USING) {
                    newTable[idx].state_ = STATE_USING;
                    newTable[idx].key_ = table_[i].key_;
                    continue;
                }
                for (int k = (idx + 1) % primes_[primeIdx_]; k != idx;
                     k = (k + 1) % primes_[primeIdx_]) {
                    if (newTable[k].state_ != STATE_USING) {
                        newTable[k].state_ = STATE_USING;
                        newTable[k].key_ = table_[i].key_;
                        break;
                    }
                }
            }
        }
        delete[] table_;
        table_ = newTable;
        tableSize_ = primes_[primeIdx_];
    }

private:
    Bucket *table_;
    int tableSize_;
    int useBucketNum_;
    double loadFactor_;

    static const int PRIME_SIZE = 10;
    static int primes_[PRIME_SIZE];
    int primeIdx_;
};

int HashTable::primes_[PRIME_SIZE] = {3,   7,   23,  47,   97,
                                      251, 443, 911, 1471, 42773};

int main() {
    HashTable htable;
    htable.insert(21);
    htable.insert(32);
    htable.insert(14);
    htable.insert(15);
    htable.insert(22);
    cout << htable.find(22) << endl;
    htable.erase(22);
    cout << htable.find(22) << endl;
}
