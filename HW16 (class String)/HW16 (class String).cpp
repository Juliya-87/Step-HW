#include <iostream>

using namespace std;

class MyString
{
private:
    static constexpr int DEFAULT_SIZE = 81;
    static int sCount;

    char* mChars;
    int mSize;

public:
    MyString() : MyString(DEFAULT_SIZE)
    {
    }

    MyString(int size)
    {
        mSize = size;
    	mChars = new char[mSize];
        *mChars = '\0';
        sCount++;
    }

    MyString(const char* str)
    {
        mSize = static_cast<int>(strlen(str)) + 1;
        mChars = new char[mSize];
        strcpy_s(mChars, mSize, str);
        sCount++;
    }

    MyString(const MyString &obj)
    {
        mSize = obj.mSize;
        mChars = new char[mSize];
        strcpy_s(mChars, mSize, obj.mChars);
        sCount++;
    }

    void enter_string()
    {
        cout << "Enter string with max " << mSize << " characters: " << '\n';
        cin.getline(mChars, mSize);
    }

    void print_line()
    {
        cout << mChars << '\n';
    }

    static int get_count()
    {
        return sCount;
    }


    ~MyString()
    {
        delete[] mChars;
    }
};

int MyString::sCount = 0;

int main()
{
    MyString s;
    s.enter_string();
    s.print_line();

    MyString s2(s);
    s2.print_line();

    cout << "Number of created objects: " << MyString::get_count();
    
}
