#include <iostream>
#include <list>
#include <string>
#include <unordered_set>
#include <cstdlib>

using namespace std;

template <typename K, typename V>
class HashTable {
private:
    struct entry {
        K key;
        V value;
        entry(const K &key, const V &value) : key(std::move(key)), value(std::move(value)) {};
    };

    list<entry> *table;
    int num_elements, table_size;
    double factor;

    int hash(const K &key) {
        return std::hash<K>{}(key) % table_size;
    }

    void rehash() {
        int new_size = table_size * 2;
        auto *new_table = new list<entry>[new_size];

        for(int i = 0; i < table_size; i++){
            for(const entry& n : table[i]) {
                int new_index = std::hash<K>{}(n.key);
                new_table[new_index].push_back(n);
            }
        }

        delete[] table;
        table = new_table;
        table_size = new_size;
    }

public:
    explicit HashTable(int init_size, double load_factor = 0.75)
        : num_elements(0), table_size(init_size), factor(load_factor) {
        table = new list<entry>[init_size];
    }

    void Insert(const K &key,const V &value) {
        int index = hash(key);
        for(auto &n : table[index]) {
            if(n.key == key) {
                n.value = value;
                return;
            }
        }
        table[index].push_back(entry(key, value));
        num_elements++;

        if(static_cast<double>(num_elements) / table_size > factor)
            rehash();
    }

    void Remove(K &key) {
        int index = hash(key);
        auto &bucket = table[index];
        for(auto i = bucket.begin(); i != bucket.end(); i++){
            if(i->key == key) {
                bucket.erase(i);
                num_elements--;
                return;
            }
        }
    }

    V Find(K &key) {
        int index = hash(key);
        for(entry n : table[index])
            if (n.key == key)
                return n.value;
        throw 3;
    }

    int Size() {
        return num_elements;
    }

    int CountUniqueValues() {
        std::unordered_set<V> unique_values;
        for (int i = 0; i < table_size; ++i)
            for (const auto& entry : table[i])
                unique_values.insert(entry.value);
        return unique_values.size();
    };

    void ShowTable() {
        int k =0;
        for(int i = 0; i < table_size; i++) {
            std::cout << "table[" << i << "] ";

            for (auto n : table[i]) {
                std::cout << "" << k << " ";
                k++;
            }
            std::cout << "\n";
        }
    }

    ~HashTable() {
        delete[] table;
    }
};
//----------------------------------------------------------------------------------------------------------------------

#define switchSecondOper(TypeKey, TypeValue)  \
    switch (TypeValue) {                \
        case 'I': {                     \
            Oper(TypeKey, int)          \
            break;                      \
        }                               \
        case 'D':{                      \
            Oper(TypeKey, double )      \
            break;                      \
        }                               \
        case 'S':{                      \
            Oper(TypeKey, string)       \
            break;                      \
        }                               \
        default: exit(1);               \
            break;                      \
    }

#define switchFirstOper(TypeKey, TypeValue) \
switch (TypeKey) {                          \
    case 'I': {                             \
        switchSecondOper(int, typeValue)    \
        break;                              \
    }                                       \
    case 'D':{                              \
        switchSecondOper(double, typeValue) \
        break;                              \
    }                                       \
    case 'S':{                              \
        switchSecondOper(string, typeValue) \
        break;                              \
    }                                       \
    default: exit(1);                       \
}

void* convertToType(char type, string &str) {
    void* answer;
    switch (type) {
        case 'I': {
            answer = new int (stoi(str));
            break;
        }
        case 'D': {
            answer = new double(stod(str));
            break;
        }
        case 'S': {
            answer = new string(str);
            break;
        }
        default:
            exit(1);
    }
    return answer;
}
void* getHashTable(char typeKey, char typeValue){
    #define Oper(TypeKey, TypeValue) answer = new  HashTable<TypeKey,TypeValue>(20);

    void* answer = nullptr;
    switchFirstOper(typeKey, typeValue)
    return answer;
    #undef Oper
}
void AddInTable(void* hashTable, char typeKey, char typeValue, string &key, string &value) {
#define Oper(TypeKey, TypeValue)                                                         \
    TypeKey * ptrKey = static_cast<TypeKey *>(convertToType(typeKey, key));                 \
    TypeValue * ptrValue = static_cast<TypeValue *>(convertToType(typeValue, value));       \
    static_cast<HashTable<TypeKey,TypeValue>*>(hashTable)->Insert(*ptrKey, *ptrValue);      \
    delete ptrKey;                                                                          \
    delete ptrValue;

    switchFirstOper(typeKey, typeValue)
#undef Oper
}
void remFromTable(void* hashTable, char typeKey, char typeValue, string &key) {

#define Oper(TypeKey, TypeValue)                                                            \
    TypeKey * ptrKey = static_cast<TypeKey *>(convertToType(typeKey, key));                 \
    static_cast<HashTable<TypeKey,TypeValue>*>(hashTable)->Remove(*ptrKey);                 \
    delete ptrKey;                                                                          \

    switchFirstOper(typeKey, typeValue)
#undef Oper
}
int getSize(void* hashTable, char typeKey, char typeValue){
#define Oper(TypeKey, TypeValue) return static_cast<HashTable<TypeKey, TypeValue>*>(hashTable)->Size();

    switchFirstOper(typeKey, typeValue)
#undef Oper
}
int getCountUniqueValues(void* hashTable, char typeKey, char typeValue){
#define Oper(TypeKey, TypeValue) return static_cast<HashTable<TypeKey, TypeValue>*>(hashTable)->CountUniqueValues();

    switchFirstOper(typeKey, typeValue)
#undef Oper
}
void freeHash(void* hashTable, char typeKey, char typeValue){
#define Oper(TypeKey, TypeValue) delete static_cast<HashTable<TypeKey, TypeValue>*>(hashTable);

    switchFirstOper(typeKey, typeValue)
#undef Oper
}
#undef switchFirstOper
#undef switchSecondOper

int main() {
    char type1_char, type2_char;
    int n;
    cin >> type1_char >> type2_char >> n;
    void *hashTable = getHashTable(type1_char, type2_char);
    for (int i = 0; i < n; i++) {
        char chose;
        cin >> chose;
        string str1, str2;
        if (chose == 'A') {
            cin >> str1 >> str2;
            AddInTable(hashTable, type1_char, type2_char, str1, str2);
        } else {
            cin >> str1;
            remFromTable(hashTable, type1_char, type2_char, str1);
        }
    }
    cout << getSize(hashTable, type1_char, type2_char) << " "
         << getCountUniqueValues(hashTable, type1_char, type2_char);
    freeHash(hashTable, type1_char, type2_char);

}
