#ifndef ___CLASS_GYROSTOPP
#define ___CLASS_GYROSTOPP

class GyroStopP {
public:
    GyroStopP();
    int getTurn(int ang);
    void calcTurn();
    void calcP();

private:
    static float pgain;
    static int threathold;

	int angle;
	int turn;
	int diff;
	int Pvalue;
};

#endif // ___CLASS_GYROSTOPP
