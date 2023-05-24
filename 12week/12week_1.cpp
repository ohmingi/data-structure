#include <iostream>
#include <string>

#define NOITEM 0
#define ISITEM 1
#define AVAILAVLE 2

using namespace std;

class entry {
public:
    int key;
    string value;
    int valid;

    entry() {
        key = 0;
        value = "";
        valid = NOITEM;
    }

    entry(int key, string value) {
        this->key = key;
        this->value = value;
        valid = ISITEM;
    }

    void erase() {   //��Ʈ���� ���� AVAILABLE�� �ٲ�
        valid = AVAILAVLE;
    }

};
class hashTable {
private:
    entry* table;   //�ؽ����̺� �����ϴ� ����
    int capacity;   //�ؽ����̺� �뷮 ����
    int hashFunc(int key) {
        return key % capacity;
    }
public:
    hashTable(int N) {
        capacity = N;
        table = new entry[capacity];
    }

    void put(int key, string value) {
        int index = hashFunc(key);  //ù��° Ž�� ��ġ�� �ؽ��Լ��� �����
        int probe = 1;  //Ž��Ƚ��
        while (table[index].valid == ISITEM && probe <= capacity) {
            index = hashFunc(index + 1);
            probe++;
        }

        cout << probe +index << endl;
        if (probe > capacity) { return; }
        table[index] = entry(key, value);
    }
    void erase(int key) {
        find(key);
        int index = hashFunc(key);
        int probe = 1;
        while (table[index].valid != NOITEM && probe <= capacity) {
            if (table[index].valid == ISITEM && table[index].key == key) {
                table[index].erase();
                return;

            }
            index = hashFunc(index + 1);
            probe++;
        }
        return;
    }
    void find(int key) {
        int index = hashFunc(key);
        int probe = 1;
        bool empty = true;
        while (table[index].valid != NOITEM && probe <= capacity) {
            if (table[index].valid == ISITEM && table[index].key == key) {
                cout << table[index].value << endl;
                empty = false;
            }
            index = hashFunc(index + 1);
            probe++;
        }
        if (empty)
            cout << "None" << endl;
    }
    void vacant() {
        int index = 0;
        int count = 0;
        while (index < capacity) {
            if (table[index].valid != ISITEM) {
                count++;
            }
            index++;
        }
        cout << count << endl;
    }
};

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int t, n;
    cin >> t >> n;

    hashTable* ht = new hashTable(n);

    while (t--) {
        string cmd;
        cin >> cmd;

        if (cmd == "put") {
            int key;
            string value;
            cin >> key >> value;

            ht->put(key, value);
        }
        else if (cmd == "erase") {
            int key;
            cin >> key;

            ht->erase(key);
        }
        else if (cmd == "find") {
            int key;
            cin >> key;

            ht->find(key);
        }
        else if (cmd == "vacant") {
            ht->vacant();
        }
    }

    return 0;
};
