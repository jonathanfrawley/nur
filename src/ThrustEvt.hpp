#ifndef  THRUSTEVT_HPP
#define  THRUSTEVT_HPP

#include "Evt.hpp"

class ThrustEvt : public Evt
{
	public:
		ThrustEvt(float x,float y)
			: Evt(ET_Thrust), m_X(x), m_Y(y)
		{
		}

		virtual ~ThrustEvt()
		{
		}

	protected:
		float m_X;
		float m_Y;
	private:
};

#endif   // THRUSTEVT_HPP
