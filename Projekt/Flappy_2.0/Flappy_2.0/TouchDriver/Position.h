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
	void Position(int x, int y)
	{
		setX(x);
		setY(y);
	}

	void setX(int x)
	{
		x_value=x;
	}
	void setY(int y)
	{
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