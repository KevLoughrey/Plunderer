// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : PLUNDERER
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : Used to simply the addition of information to a packet
#include <string>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#pragma once
using namespace std;
class PacketStream {
public:       
		PacketStream(void);
		~PacketStream(void) {}
        void writeFloat(float f);
        void writeInt(int i);
        void writeBool(bool b);
        void writeString(string s);
        float readFloat(string f);
        int readInt(string i);
        bool readBool(string b);
        string readString(string s);
        char* toCharArray();
        string toPacketStream(char* cArray);
		void clearString();
		string m_string;
		void setMessage(string messageReceived);
private:
       
        
        
};