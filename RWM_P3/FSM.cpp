#include "FSM.h"

FSM::FSM(void)
{
}


FSM::~FSM(void)
{
}

void FSM::PushFSMelement(std::string state1,
						std::string evnt,
						std::string action,
						std::string state2)
{
	FSMelement l_el = FSMelement();
	l_el.m_state1 = state1;
	l_el.m_event = evnt;
	l_el.m_action = action;
	l_el.m_state2 = state2;

	m_fsm.push_back(l_el);
}

std::string FSM::Update(std::string &state, 
						std::string evnt)
{
	for (int i = 0; i < m_fsm.size(); i++)
	{
		if (m_fsm.at(i).m_state1 == state  && 
			m_fsm.at(i).m_event == evnt)
		{
			state = m_fsm.at(i).m_state2;
			return m_fsm.at(i).m_action;
		}
	}

	return "No Action";
}


