#pragma once
class Menu
{
public:
	Menu();
	void main();
	void about();

	bool getReadyStatus() { return isPlayGame_; };

private:
	bool isPlayGame_;
};

