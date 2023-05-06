#include <sys/types.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <string>

using namespace std;

int main() {

    pid_t pid;
    cout << "Enter process ID: ";
    cin >> pid;

    string mem_path = "/proc/" + to_string(pid) + "/mem";

    int fd = open(mem_path.c_str(), O_RDONLY);

    if (fd < 0) {
        cerr << "Failed to open process with pid = " << pid << endl;
        return 1;
    }

    long addr;
    cout << "Enter the address to read (in hexadecimal): ";
    cin >> hex >> addr;

    int data = 0;
    if (pread(fd, &data, sizeof(data), addr) == -1) {
        cerr << "Failed to read process memory" << endl;
        close(fd);
        return 1;
    }

    cout << "Value at address " << hex << addr << ": " << dec << data << endl;

    for (int i=0; i<10; i++)
    {
        sleep(5);
        int newdata = 0;
        if (pread(fd, &newdata, sizeof(newdata), addr) == -1)
        {
            cerr << "Failed to read process memory, maybe it is not active anymore" << endl;
            close(fd);
            return 1;
        }
        if (newdata!=data)
        {
            data = newdata;
            cout << "New value: " << newdata << endl;
        }
        else
            cout << "No change" << endl;
    }

    close(fd);
    return 0;
}
