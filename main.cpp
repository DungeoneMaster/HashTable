#include <iostream>
#include <list>
#include <string>
#include <unordered_set>
#include <variant>
#include <cstdlib>

using std::list, std::string;

//struct Type {
//    char type;
//    union {
//        int intValue{};
//        double doubleValue;
//        //string stringValue;
//    };
//    explicit Type(char t) : type(t) {};
//    //explicit Value(double v) : type(ValueType::D) { doubleValue = v; }
//    //explicit Value(string v) : type(ValueType::S) { stringValue = std::move(v); }
//
////    ~Type() {
////        if (type == ValueType::S)
////            stringValue.~string();
////    }
//};



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

std::variant<int, double, string> DefineType(char type) {
    switch (type) {
        case 'I': return 1;
        case 'D': return .1;
        default: return "";
    }
}
std::variant<int, double, string> ToType(string &str, char type) {
    switch (type) {
        case 'I': return atoi(str.c_str());
        case 'D': return atof(str.c_str());
        default: return str;
    }
}


enum class Type {I = 'I',D = 'D',S = 'S'};
template<Type a>
struct M{

};


int GetVal(M<Type::I> &p) {
    return 1;
}
//template<char tmp>
//int GetVal(M<Type(tmp)> p) {
//    return 1;
//}
//template<typename T>
//int GetVal(M<Type::T> p) {
//
//}

const Type vvvv() {
    return Type::I;
}
template <typename T>
auto getTypeName(const T& value) {
    return typeid();
}


int main(){

    char type1_char, type2_char;
    int n;

//    Type a = ;



    std::cin >> type1_char >> type2_char >> n;

    HashTable<getTypeName(type1_char),type2> hash_table{n*10};
//    M<(Type)> b;
//    auto s = GetVal();
//    Type type1(type1_char), type2(type2_char);
//    HashTable<type1,type2> hash_table{n*10};

//    for(int i = 0; i < n; i++) {
//        char chose;
//        string str1, str2;
//        std::cin >> chose >> str1;
//        decltype(DefineType(type1)) value1 = ToType(str1,type1);
//
//        if(chose == 'A') {
//            std::cin >> str2;
//            decltype(DefineType(type2)) value2 = ToType(str2,type2);
//            hash_table.Insert(value1, value2);
//        }
//        else
//            hash_table.Remove(value1);
//        //
//    }
//
//    std::cout << hash_table.Size() << " " << hash_table.CountUniqueValues();
//    //hash_table.ShowTable();
//    return 0;
}





//
//
//
//
//Value getValue(char choice) {
//    switch (choice) {
//        case 'I': return Value(1);
//        case 'D': return Value(0.1);
//        default: return Value("");
//    }
////}
//
//////concept Numeric = std::integral<T> || std::floating_point<T>;






//for (int i = 0; i < size; ++i) {
//    bool isUnique = true;
//
//    for (int j = 0; j < i; ++j) {
//        if (arr[i] == arr[j]) {
//            isUnique = false;
//            break;
//        }
//    }
//
//
//    if (isUnique)
//        uniqueCount++;
//
//}