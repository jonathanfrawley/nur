#ifndef  POINT2_HPP
#define  POINT2_HPP

class Point2
{
	public:
		Point2()
			: m_X(0),m_Y(0)
		{
		}
		virtual ~Point2()
		{
		}
		float getX()const{return m_X;}
		float getY()const{return m_Y;}
		void setX(float x){m_X=x;}
		void setY(float y){m_Y=y;}
	protected:
		float m_X;
		float m_Y;
	private:
};


#endif   // POINT2_HPP
