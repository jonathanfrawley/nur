#ifndef  EVT_HPP
#define  EVT_HPP

typedef enum EvtType
{
	ET_Thrust
} EvtType;

class Evt
{
	public:
		Evt(EvtType type)
			:
				m_Type(type)
		{
		}
		virtual ~Evt()
		{
		}

		EvtType getType() { return m_Type; }

	protected:
		EvtType m_Type;
};


#endif   // EVT_HPP
