#ifndef  EVTMAN_HPP
#define  EVTMAN_HPP

#include <assert.h>

const int MAX_HANDLERS=255;
const int MAX_EVENTS=255;

class EvtMan
{
	public:
		virtual ~EvtMan()
		{
		}

		static EvtMan& get()
        {
            static EvtMan m_Instance; 
            return m_Instance;
        }

		void pushHnd(sptr<EvtHnd> hnd)
		{
			assert(MAX_HANDLERS > m_NEvtHnds);
			m_EvtHnds[m_NEvtHnds++] = hnd;
		}

		void push(sptr<Evt> ev)
		{
			assert(MAX_EVENTS > m_NEvts);
			m_Evts[m_NEvts++] = ev;
		}

		void handle()
		{
			for(int i=0;i<m_NEvts;i++)
			{
				for(int j=0;j<m_NEvtHnds;j++)
				{
					m_EvtHnds[j]->handle(m_Evts[i]);
				}
			}
			m_NEvts=0;
		}

	protected:
		EvtMan()
			: m_NEvtHnds(0),m_NEvts(0)
		{
		}

		sptr<EvtHnd> m_EvtHnds[MAX_HANDLERS];
		int m_NEvtHnds;
		sptr<Evt> m_Evts[MAX_EVENTS];
		int m_NEvts;
};

#endif   // EVTMAN_HPP
