#include "ServerHelper.h"
 
std::string ServerHelper::dataStore;
 
size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up)
{ //callback must have this declaration
        //buf is a pointer to the data that curl has for us
        //size*nmemb is the size of the buffer
 
        for (int c = 0; c<size*nmemb-1; c++)
        {
                ServerHelper::dataStore.push_back(buf[c]);
        }
        return size*nmemb; //tell curl how many bytes we handled
}
ServerHelper::ServerHelper(void)
{
        curl_global_init(CURL_GLOBAL_ALL);
        curl = curl_easy_init();
}
 
 
ServerHelper::~ServerHelper(void)
{
}
std::string ServerHelper::PostNameToServer(std::string ip, int PORT, std::string name, std::string friendName)
{
        dataStore = "";
 
        curl = curl_easy_init();
       
        std::string params = "ip=' " + ip + "'&port='" + std::to_string(PORT) + "'&name='" + name + "'&friend='"+friendName+"'";
       
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
       
        curl_easy_setopt(curl, CURLOPT_URL, "http://23.97.140.62:8000/PostName");
 
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);       
 
        return dataStore;
}
std::string ServerHelper::GetNamesFromServer(std::string name, std::string friendName)
{
        dataStore = "";
        curl = curl_easy_init();
       
        std::string params = "name='" + name + "'&friend='" + friendName + "'";
 
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
        curl_easy_setopt(curl, CURLOPT_URL, "http://23.97.140.62:8000/GetNames");
       
 
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);       
 
        return dataStore;
}
void ServerHelper::PostHighScore(int score, std::string name)
{
        dataStore = "";
        curl = curl_easy_init();
		std::string s = std::to_string(score);

		std::string params = "name=' " + name + "'&score='" + s + "'";

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params.c_str());
        curl_easy_setopt(curl, CURLOPT_URL, "http://23.97.140.62:8000/PostScore");
 
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
 
}
 
 
std::string ServerHelper::GetHighScores()
{
        dataStore = "";
        curl = curl_easy_init();
 
        curl_easy_setopt(curl, CURLOPT_URL, "http://23.97.140.62:8000/GetScore");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
       
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
 
        return dataStore;      
}
 
std::string ServerHelper::GetIPAddress()
{
        dataStore = "";
       
        curl_easy_setopt(curl, CURLOPT_URL, "http://www.icanhazip.com");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
       
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
 
       
        return dataStore;
}
 
void ServerHelper::PostCoopHighScore(int score, std::string name1, std::string name2)
{
        dataStore = "";
        curl = curl_easy_init();

		std::string s = std::to_string(score);

		std::string params = "name=' " + name1 + "'&friend='" + name2  + "'&score='" + s + "'";

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params.c_str());
        curl_easy_setopt(curl, CURLOPT_URL, "http://23.97.140.62:8000/PostCoopScore");
 
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
}
std::string ServerHelper::GetCoopHighScores()
{
        dataStore = "";
        curl = curl_easy_init();
 
        curl_easy_setopt(curl, CURLOPT_URL, "http://23.97.140.62:8000/GetCoopScore");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
       
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
 
        return dataStore;      
}