#ifndef _SCORE_H_
#define _SCORE_H_


class Score{
	int home_score;
	int away_score;
public:
	Score();
	~Score();
	void Render(float);
	void home();
	void away();
	void Reset();
  int GetHome();
  int GetAway();
  int SetHome(int home);
  int SetAway(int away);
};

#endif