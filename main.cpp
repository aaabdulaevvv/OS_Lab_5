#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    // ������������ PID �������, ���'��� ����� �� ������ �������
    int pid = 8;

    // ³�������� ���� /proc/[id]/mem
    stringstream mem_path;
    mem_path << "/proc/" << pid << "/mem";
    ifstream mem_file(mem_path.str().c_str(), ios::in | ios::binary);
    if (!mem_file) {
        cerr << "Can`t open file /proc/[id]/mem" << endl;
        return 1;
    }

    // ������� �������� � ���'�� �������
    unsigned char buffer[4];
    off_t offset = 0x12345678;  // ������������ ������, � ����� ������� ����������
    mem_file.seekg(offset, ios::beg);
    mem_file.read(reinterpret_cast<char *>(buffer), sizeof(buffer));
    if (mem_file.gcount() != sizeof(buffer)) {
        cerr << "Couldn`t read process` memory" << endl;
        return 1;
    }

    // �������� ������� ��������
    cout << "Value read from process` memory: ";
    for (size_t i = 0; i < sizeof(buffer); ++i) {
        cout << hex << static_cast<unsigned int>(buffer[i]);
    }
    cout << endl;

    // ��������� ���� /proc/[id]/mem
    mem_file.close();

    return 0;
}
