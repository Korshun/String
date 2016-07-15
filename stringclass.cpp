#include "stringclass.h"

#include <cstring>


// StringRef constructors
StringRef::StringRef(String str):
    mStr(str.data()),
    mSize(str.size())
{

}

StringRef::StringRef(StringRefZ str):
    mStr(str.data()),
    mSize(str.size())
{

}

StringRef::StringRef(const char *str):
    mStr(str),
    mSize(strlen(str))
{

}

StringRef::StringRef(const char *data, StringSize size):
    mStr(data),
    mSize(size)
{

}

StringRef::StringRef(std::string str):
    mStr(str.c_str()),
    mSize(str.size())
{

}


// StringRefZ constructors
StringRefZ::StringRefZ(String str):
    mStr(str.data()),
    mSize(str.size())
{

}

StringRefZ::StringRefZ(const char *str):
    mStr(str),
    mSize(strlen(str))
{

}

StringRefZ::StringRefZ(const char *data, StringSize size):
    mStr(data),
    mSize(size)
{
    assert(data[size] == '\0');
}

StringRefZ::StringRefZ(std::string str):
    mStr(str.c_str()),
    mSize(str.size())
{

}


// String constructors
void String::assign(const char *data, StringSize size)
{
    mSize = size;
    mStr = new char[mSize + 1];
    memcpy(mStr, data, mSize);
    mStr[mSize] = '\0';
}

String::String(StringRef str)
{
    assign(str.data(), str.size());
}

String::String(StringRefZ str)
{
    assign(str.data(), str.size());
}

String::String(const char *str)
{
    assign(str, strlen(str));
}

String::String(const char *data, StringSize size)
{
    assign(data, size);
}

String::String(std::string str)
{
    assign(str.c_str(), str.size());
}

String String::takeOwnership(char *data, StringSize size)
{
    String str;
    str.mStr = data;
    str.mSize = size;
    assert(data[size] == '\0');
    return str;
}


// String memory management
String::~String()
{
    delete mStr;
}

String::String(const String &other)
{
    mSize = other.mSize;
    mStr = new char[mSize];
    memcpy(mStr, other.mStr, mSize);
}

String::String(String &&other)
{
    mSize = other.mSize;
    mStr = other.mStr;
    other.mStr = NULL;
}

String operator+(StringRef a, StringRef b)
{
    return StringOps::add(a, b);
}

bool operator==(StringRef a, StringRef b)
{
    return a.size() == b.size() && !memcmp(a.data(), b.data(), a.size());
}

namespace StringOps
{

static char* allocString(StringSize size)
{
    return new char[size + 1];
}

String add(StringRef a, StringRef b)
{
    char *data = allocString(a.size() + b.size());
    memcpy(data,            a.data(), a.size());
    memcpy(data + a.size(), b.data(), b.size());
    data[a.size() + b.size()] = '\0';
    return String::takeOwnership(data, a.size() + b.size());
}

}

#if 0
// Convenience methods.
String insert     (StringSize index, StringRef what) const;
String remove     (StringRef what) const;
String removeFirst(StringRef what) const;
String removeLast (StringRef what) const;
String replace    (StringRef what, StringRef with) const;
String reverse    (StringRef str) const;
String simplify   (StringRef str) const;
String times      (StringSize count) const;

String uppercase () const;
String lowercase () const;
String capitalize() const;
String swapcase  () const;

StringRefZ lstrip() const;
StringRefZ right  (StringSize size) const;

StringRef strip  () const;
StringRef rstrip () const;
StringRef slice  (StringSize start, StringSize end) const;
StringRef left   (StringSize size) const;
StringRef middle (StringSize start, StringSize size) const;
StringRef rmiddle(StringSize end, StringSize size) const;

bool isAscii   () const;
bool startsWith(StringRef what) const;
bool endsWith  (StringRef what) const;
bool contains  (StringRef what) const;

StringSize compare(StringRef rhs) const;
StringSize count  (StringRef what) const;
StringSize find   (StringRef what) const;
StringSize rfind  (StringRef what) const;

String String::insert(StringSize index, StringRef what) const { return StringOps::insert(*this, index, what); }
String String::remove(StringRef what) const { return StringOps::remove(*this, what); }
String String::removeFirst(StringRef what) const { return StringOps::removeFirst(*this, what); }
String String::removeLast(StringRef what) const { return StringOps::removeLast(*this, what); }
String String::replace(StringRef what, StringRef with) const { return StringOps::replace(*this, what, with); }
String String::reverse(StringRef str) const { return StringOps::reverse(*this); }
String String::simplify(StringRef str) const { return StringOps::simplify(*this); }
String String::times(StringSize count) const { return StringOps::times(*this, count); }

String String::uppercase () const { return StringOps::uppercase(*this); }
String String::lowercase () const { return StringOps::lowercase(*this); }
String String::capitalize() const { return StringOps::capitalize(*this); }
String String::swapcase  () const { return StringOps::swapcase(*this); }

StringRef String::strip () const { return StringOps::strip(*this); }
StringRef String::lstrip() const { return StringOps::lstrip(*this); }
StringRef String::rstrip() const { return StringOps::rstrip(*this); }
StringRef String::slice  (StringSize start, StringSize end) const { return StringOps::slice(*this, start, end); }
StringRef String::left   (StringSize size) const { return StringOps::left(*this, size); }
StringRef String::right  (StringSize size) const { return StringOps::right(*this, size); }
StringRef String::middle (StringSize start, StringSize size) const { return StringOps::middle(*this, start, size); }
StringRef String::rmiddle(StringSize end, StringSize size) const { return StringOps::rmiddle(*this, end, size); }

bool String::isAscii   () const { return StringOps::isAscii(*this); }
bool String::startsWith(StringRef what) const { return StringOps::startsWith(*this, what); }
bool String::endsWith  (StringRef what) const { return StringOps::endsWith(*this, what); }
bool String::contains  (StringRef what) const { return StringOps::contains(*this, what); }

StringSize String::compare(StringRef rhs) const { return StringOps::compare(*this, rhs); }
StringSize String::count  (StringRef what) const { return StringOps::count(*this, what); }
StringSize String::find   (StringRef what) const { return StringOps::find(*this, what); }
StringSize String::rfind  (StringRef what) const { return StringOps::rfind(*this, what); }


String StringRef::insert(StringSize index, StringRef what) const { return StringOps::insert(*this, index, what); }
String StringRef::remove(StringRef what) const { return StringOps::remove(*this, what); }
String StringRef::removeFirst(StringRef what) const { return StringOps::removeFirst(*this, what); }
String StringRef::removeLast(StringRef what) const { return StringOps::removeLast(*this, what); }
String StringRef::replace(StringRef what, StringRef with) const { return StringOps::replace(*this, what, with); }
String StringRef::reverse(StringRef str) const { return StringOps::reverse(*this); }
String StringRef::simplify(StringRef str) const { return StringOps::simplify(*this); }
String StringRef::times(StringSize count) const { return StringOps::times(*this, count); }

String StringRef::uppercase () const { return StringOps::uppercase(*this); }
String StringRef::lowercase () const { return StringOps::lowercase(*this); }
String StringRef::capitalize() const { return StringOps::capitalize(*this); }
String StringRef::swapcase  () const { return StringOps::swapcase(*this); }

StringRef StringRef::strip () const { return StringOps::strip(*this); }
StringRef StringRef::lstrip() const { return StringOps::lstrip(*this); }
StringRef StringRef::rstrip() const { return StringOps::rstrip(*this); }
StringRef StringRef::slice  (StringSize start, StringSize end) const { return StringOps::slice(*this, start, end); }
StringRef StringRef::left   (StringSize size) const { return StringOps::left(*this, size); }
StringRef StringRef::right  (StringSize size) const { return StringOps::right(*this, size); }
StringRef StringRef::middle (StringSize start, StringSize size) const { return StringOps::middle(*this, start, size); }
StringRef StringRef::rmiddle(StringSize end, StringSize size) const { return StringOps::rmiddle(*this, end, size); }

bool StringRef::isAscii   () const { return StringOps::isAscii(*this); }
bool StringRef::startsWith(StringRef what) const { return StringOps::startsWith(*this, what); }
bool StringRef::endsWith  (StringRef what) const { return StringOps::endsWith(*this, what); }
bool StringRef::contains  (StringRef what) const { return StringOps::contains(*this, what); }

StringSize StringRef::compare(StringRef rhs) const { return StringOps::compare(*this, rhs); }
StringSize StringRef::count  (StringRef what) const { return StringOps::count(*this, what); }
StringSize StringRef::find   (StringRef what) const { return StringOps::find(*this, what); }
StringSize StringRef::rfind  (StringRef what) const { return StringOps::rfind(*this, what); }
#endif
