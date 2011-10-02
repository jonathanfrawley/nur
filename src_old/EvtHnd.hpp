#ifndef  EVTHND_HPP
#define  EVTHND_HPP

#include "Evt.hpp"

class EvtHnd
{
	public:
		EvtHnd()
		{
		}
		virtual ~EvtHnd()
		{
		}

		virtual void handle(sptr<Evt> ev) = 0;

	protected:
};

#endif   // EVTHND_HPP
