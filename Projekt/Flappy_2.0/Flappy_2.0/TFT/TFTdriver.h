/************************************************************
  File name: "TFTdriver.c"

  Driver for "ITDB02 320 x 240 TFT display module, Version 2"
  mounted at "ITDB02 Arduino Mega2560 Shield".
  Display controller = ILI 9341.
  
  Max. uC clock frequency = 16 MHz (Tclk = 62,5 ns)

  Connections:
  DB15-DB8:   PORT A
  DB7-DB0:    PORT C

  RESETx:     PORT G, bit 0
  CSx:        PORT G, bit 1
  WRx:        PORT G, bit 2
  RS (=D/Cx): PORT D, bit 7

  Henning Hargaard, February 15, 2018
************************************************************/  
class TFTDriver
{
//Variables
private:
	int _height;
	int _width;

public: 
	TFTDriver(int height, int width);
	TFTDriver();
	~TFTDriver();
	void DisplayInit();
	void Reset();
	void DisplayOff();
	void DisplayOn();
	void FillRectangle(unsigned int StartX, unsigned int StartY, unsigned int Width,
	unsigned int Height, unsigned char Red, unsigned char Green, unsigned char Blue);
	void DrawFrame(int *data);
	void DisplayInversionOn();
	void DisplayInversionOff();
private:
	void SleepOut();
	void MemoryAccessControl(unsigned char parameter);
	void InterfacePixelFormat(unsigned char parameter);
	void WritePixel(int encodedColor);
	void SetColumnAddress(unsigned int Start, unsigned int End);
	void SetPageAddress(unsigned int Start, unsigned int End);
	void MemoryWrite();
	void WriteCommand(unsigned int command);
	void WriteData(unsigned int data);
};



