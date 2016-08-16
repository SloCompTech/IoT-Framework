// ---------------- Usage example -------------------- //
#include <string>
using std::string;
using std::getline;
using std::cout;
using std::endl;

int main() {
    const char* const argv[] = {"/bin/cat", (const char*)0};
    spawn cat(argv);
    cat.stdin << "Hello" << std::endl;
    string s;
    getline(cat.stdout, s);
    cout << "Read from program: '" << s << "'" << endl;
    cat.send_eof();
    cout << "Waiting to terminate..." << endl;
    cout << "Status: " << cat.wait() << endl;
    return 0;
}
