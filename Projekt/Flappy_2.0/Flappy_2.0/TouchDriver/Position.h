/*
 * Position.h
 *
 * Created: 19-03-2020 11:15:42
 *  Author: math0
 */ 


#ifndef POSITION_H_
#define POSITION_H_

class Position
{
public:
	Position()
	{
		
	}
	Position(int x, int y)
	{
		setX(x);
		setY(y);
	}

	void setX(int x)
	{
		if (x < 0)
			x = 0;
		x_value=x;
	}
	void setY(int y)
	{
		if(y < 0)
			y = 0;
		y_value = y;
	}
	int getX()
	{
		return x_value;
	}
	int getY()
	{
		return y_value;
	}
protected:
private:
	int x_value;
	int y_value;
};


#endif /* POSITION_H_ */