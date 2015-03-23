#include "PacketStream.h"
 
 

PacketStream::PacketStream() {
	m_string = "";
}
 

void PacketStream::writeInt(int i) {
	m_string.append(std::to_string(i) + " ");
}
 
void PacketStream::writeFloat(float f) {		
	m_string.append(std::to_string(f) + " ");
}
 
void PacketStream::writeBool(bool b) {
	m_string.append(((b==true) ? "true" : "false"));
	m_string.append(" ");
}
 
void PacketStream::writeString(string s) {
	m_string.append(s + " ");
}
 
int PacketStream::readInt(string i) {
	return stoi(i);
}
 
float PacketStream::readFloat(string f) {
	return stof(f);
}
 
bool PacketStream::readBool(string b) {
	b.erase(b.end()-1);
	return (b == "true") ? true : false;
}
 
string PacketStream::readString(string s) {
	s.erase(s.end());
	return s;
}

char* PacketStream::toCharArray() {
	char* cstr = new char[m_string.length() + 1];
	strcpy(cstr, m_string.c_str());
		
	return cstr;
}
void PacketStream::clearString(){
	m_string = "";
}
 
string PacketStream::toPacketStream(char* cArray) {
	string str(cArray);
	return str;
}
void PacketStream::setMessage(string receivedMessage){
	m_string = receivedMessage;
}