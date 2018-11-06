#pragma once

//Only for simple types like int and float
template <class T>
struct VarU
{
    VarU(T copy) { value = copy; }
    VarU(unsigned char* array)
        { for (int i = 0; i < sizeof(T); i++) bytes[i] = array[i]; }

    unsigned int size() const { return sizeof(T); }

    unsigned char& operator[](int i) { return bytes[i]; }
    T& operator()() { return value; };

    private:
        union
        {
            T value;
            unsigned char bytes[sizeof(T)];
        };
};
