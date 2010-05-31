#pragma once
class Action;
class Bullet;
typedef boost::shared_ptr<Bullet> BulletPtr;
typedef std::list<BulletPtr> BulletList;

//Abstract subaction (fire, changedir etc) base class
class SubAction
{
public:
	SubAction() :
	  finished_(false)
	{}
	~SubAction(void) {}
	virtual void call(BulletPtr owner, Action& action,
					  float params, float rank, BulletList* created) = 0;
	bool finished() const { return finished_; }
	void setFinished(bool newf) { finished_ = newf; }
protected:
	bool finished_;
};

typedef std::list<SubAction*> SubActionList;

struct BulletDirection
{
	BulletDirection(int newtype, float newangle) :
		type(newtype),
		angle(newangle)
	{}
	int type; //aim, absolute, relative, sequence
	float angle;
};

namespace DirectionType
{
	enum DirectionTypes { aim, absolute, relative, sequence };
};
