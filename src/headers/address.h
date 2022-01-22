#ifndef ADDRESS_H
#define ADDRESS_H

class Address
{
public:
    Address();
    Address(Address &); // copy constructor
    Address(char addr[]);
    Address(char addr[], unsigned short port);
    Address(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port);
    Address(unsigned int address, unsigned short port);

    // NOTE(Noah): the const in the function decl makes it a compiler error for this func to change member
    // variables of this class.
    unsigned int getAddress() const;
    unsigned short getPort() const;

    void setAddresss(unsigned int);
    void setPort(unsigned short);
    
    char* toString() const;
    unsigned char getA() const;
    unsigned char getB() const;
    unsigned char getC() const;
    unsigned char getD() const;

private:
    unsigned int address;
    unsigned short port;

    void init(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port);
};

#endif