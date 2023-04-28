#include <iostream>
#include <fstream>
#include "md5.hpp"

using std::cout; using std::endl;


//Функция для хэширования исходного файла
//file_name - имя файла
std::string hashing_files_md5(const std::string& file_name) {
    std::ifstream file(file_name, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file: " << file_name << '\n';
        return "error";
    }

    file.seekg(0, std::ios::end);
    long Length = file.tellg();
    file.seekg(0, std::ios::beg);

    char* data = new char[Length];
    file.read(data, Length);

    std::string hash = md5(data);
    //cout << hash << endl;

    delete[] data;

    return hash;
}

//Функция для проверки целостности файла
//file_name - имя файла
//hash_name - имя файла с хэшем
bool check_file_integrity(const std::string& file_name, const std::string& hash_file) {
    std::ifstream file(file_name, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file: " << file_name << '\n';
        return false;
    }

    std::ifstream hash(hash_file, std::ios::binary);
    if (!hash) {
        std::cerr << "Failed to open file: " << hash_file << '\n';
        return false;
    }

    file.seekg(0, std::ios::end);
    long Length = file.tellg();
    file.seekg(0, std::ios::beg);

    char* data = new char[Length];
    file.read(data, Length);

    std::string old_hash;
    hash >> old_hash;

    std::string new_hash = md5(data);

    delete[] data;

    return old_hash==new_hash;
}


//Пример использования
int main(int argc, char* argv[])
{

    std::string st = hashing_files_md5("data.txt");
    std::ofstream hash("data.hash");
    hash << st;
    hash.close(); //создаем хэш исходного файла

    bool f = check_file_integrity("data.txt", "data.hash");
    cout << (f ? "ok" : "file has been changed")<<endl; //проверяем на оригинальном файле


    f = check_file_integrity("data2.txt", "data.hash");
    cout << (f ? "ok" : "file has been changed"); //проверяем на копии файла файла


    return 0;
}
