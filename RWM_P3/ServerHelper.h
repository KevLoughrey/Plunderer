// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : PLUNDERER
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : Used to communicate with the server hosted on windows azure. Posts and gets high scores
#pragma once
#include <string>
#include <fstream>
#include <curl\curl.h>
#include <iostream>
#include <sstream>
class ServerHelper
{
protected:
        CURL* curl; //our curl object  
public:
        static std::string dataStore;
		///Empty constructor
        ServerHelper(void);
        ~ServerHelper(void);
		///Send highscore to azure server
		/// \param[score] the score to post to the server
		/// \param[name] the name associated with score
        void PostHighScore(int score, std::string name);
		///Send coop highscore to azure server
		/// \param[score] the score to post to the server
		/// \param[name1] the name associated with score
		/// \param[name2] the second name associated with score
        void PostCoopHighScore(int score, std::string name1, std::string name2);
		///Get string containing coop high scores
		/// \return string containing scores
        std::string GetCoopHighScores();
		///Get string containing our ip
		/// \return string containing our ip
        std::string GetIPAddress();
		///Get string containing high scores
		/// \return string containing scores
        std::string GetHighScores();
		///Post our name ip port and friends name to server for matchmaking
		/// \param[ip] our ip
		/// \params[port] our port
		/// \params[name] our name
		/// \params[friendName] our friends name
		/// \return string containing seed stored on server
        std::string PostNameToServer(std::string ip, int PORT, std::string name, std::string friendName);
		///Get names from server that match names
		/// \param[name] our name
		/// \params[friendName] our friends name
		/// \return ip and port of our friend
        std::string GetNamesFromServer(std::string name, std::string friendName);      
};