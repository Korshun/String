#ifndef STRINGCLASS_H
#define STRINGCLASS_H



#include <cassert>
#include <string>

typedef int StringSize;

class String;
class StringRef;
class StringRefZ;

class String
{
private:
    char *mStr;
    StringSize mSize;

    String() {}
    void assign(const char *data, StringSize size);

public:
    String(StringRefZ str);
    String(StringRef str);
    String(const char *str);
    String(const char *data, StringSize size);
    String(std::string str);
    static String takeOwnership(char *data, StringSize size);

    ~String();
    String(const String &other);
    String(String &&other);

    const char* data()  const { return mStr; }
    StringSize  size()  const { return mSize; }
    const char* c_str() const { return mStr; }

    char operator[](StringSize index) const
    {
        assert(index >= 0);
        assert(index < mSize);
        return mStr[index];
    }
};


class StringRefZ
{
private:
    const char *mStr;
    StringSize mSize;

public:
    StringRefZ(String str);
    StringRefZ(const char *str);
    StringRefZ(const char *data, StringSize size);
    StringRefZ(std::string str);

    const char* data()  const { return mStr; }
    StringSize  size()  const { return mSize; }
    const char* c_str() const { return mStr; }

    char operator[](StringSize index) const
    {
        assert(index >= 0);
        assert(index < mSize);
        return mStr[index];
    }
};


class StringRef
{
private:
    const char *mStr;
    StringSize mSize;

public:
    StringRef(String str);
    StringRef(StringRefZ str);
    StringRef(const char *str);
    StringRef(const char *data, StringSize size);
    StringRef(std::string str);

    const char* data() const { return mStr; }
    StringSize  size() const { return mSize; }

    char operator[](StringSize index) const
    {
        assert(index >= 0);
        assert(index < mSize);
        return mStr[index];
    }
};


String operator+(StringRef a, StringRef b);
bool operator<=(StringRef a, StringRef b);
bool operator==(StringRef a, StringRef b);


// String operations.
namespace StringOps
{
    String add(StringRef a, StringRef b);
    String insert(StringRef str, StringSize index, StringRef what);
    String remove(StringRef str, StringRef what);
    String removeFirst(StringRef str, StringRef what);
    String removeLast(StringRef str, StringRef what);
    String replace(StringRef str, StringRef what, StringRef with);
    String reverse(StringRef str);
    String simplify(StringRef str);
    String times(StringRef str, StringSize count);

    String uppercase (StringRef str);
    String lowercase (StringRef str);
    String capitalize(StringRef str);
    String swapcase  (StringRef str);

    StringRefZ lstrip(StringRefZ str);
    StringRefZ right (StringRefZ what, StringSize size);

    StringRef strip  (StringRef str);
    StringRef lstrip (StringRef str);
    StringRef rstrip (StringRef str);
    StringRef slice  (StringRef what, StringSize start, StringSize end);
    StringRef left   (StringRef what, StringSize size);
    StringRef right  (StringRef what, StringSize size);
    StringRef middle (StringRef what, StringSize start, StringSize size);
    StringRef rmiddle(StringRef what, StringSize end, StringSize size);

    bool isAscii   (StringRef str);
    bool startsWith(StringRef str, StringRef what);
    bool endsWith  (StringRef str, StringRef what);
    bool contains  (StringRef str, StringRef what);

    StringSize compare(StringRef a, StringRef b);
    StringSize count  (StringRef str, StringRef what);
    StringSize find   (StringRef str, StringRef what);
    StringSize rfind  (StringRef str, StringRef what);
}



#endif // STRINGCLASS_H
