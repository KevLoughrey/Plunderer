// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : PLUNDERER
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : HANDLES AI LOGIC FOR MUMMY AND SNAKE.  STRING DRIVEN.  

#pragma once
#include <string>
#include <vector>
#include <functional>
#include <map>


/// String based Finite State Machine.
class FSM
{

private: 
	/// Struct which stores:
	/// -# Current State
	/// -# Event
	/// -# Action
	/// -# New State
	struct FSMelement
	{
		std::string m_state1;
		std::string m_event;
		std::string m_action;
		std::string m_state2;
	};

	/// Stores FSM elements.
	std::vector<FSMelement> m_fsm;

public:
	FSM(void);
	~FSM(void);

	void PushFSMelement(std::string state1,
						std::string evnt,
						std::string action,
						std::string state2);

	/// Updates FSM
	/// \param[in] a reference of a current state.
	/// \param[in] event.
	/// \return string with an action to do.
	std::string Update(	std::string &state, 
						std::string evnt);
};

