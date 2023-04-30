#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    // Встановлюємо PID процесу, пам'ять якого ми хочемо зчитати
    int pid = 8;

    // Відкриваємо файл /proc/[id]/mem
    stringstream mem_path;
    mem_path << "/proc/" << pid << "/mem";
    ifstream mem_file(mem_path.str().c_str(), ios::in | ios::binary);
    if (!mem_file) {
        cerr << "Can`t open file /proc/[id]/mem" << endl;
        return 1;
    }

    // Зчитуємо значення з пам'яті процесу
    unsigned char buffer[4];
    off_t offset = 0x12345678;  // Встановлюємо оффсет, з якого почнемо зчитування
    mem_file.seekg(offset, ios::beg);
    mem_file.read(reinterpret_cast<char *>(buffer), sizeof(buffer));
    if (mem_file.gcount() != sizeof(buffer)) {
        cerr << "Couldn`t read process` memory" << endl;
        return 1;
    }

    // Виводимо зчитане значення
    cout << "Value read from process` memory: ";
    for (size_t i = 0; i < sizeof(buffer); ++i) {
        cout << hex << static_cast<unsigned int>(buffer[i]);
    }
    cout << endl;

    // Закриваємо файл /proc/[id]/mem
    mem_file.close();

    return 0;
}
