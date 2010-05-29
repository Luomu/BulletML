#pragma once

class BulletPtr;
class BulletPtrList;
class ActionPtr;
class SubAction;

struct BulletDirection
{
	int type; //aim, absolute, relative, sequence
	float angle;
};

struct FireSpeed
{
	int type; //absolute, relative, sequence
	float speed;
};

namespace SpeedType
{
	enum SpeedTypes { absolute, relative, sequence };
};

/*
Fires a bullet to <direction> degrees at <speed>.
The labeled fire element is referred by fireRef elements. 
*/
class FireDef : public SubAction;
{
public:
	FireDef(const std::string& label, const BulletDirection& dir, const FireSpeed& speed);
	void call(BulletPtr owner, ActionPtr action,
			  float params, float rank, BulletPtrList created);
private:
	std::string label_;
	BulletDirection direction_;
	FireSpeed speed_;
	//bullet or bulletref
};

/*
Refers to the labeled fire action.
This element is handled as the fire action element
that has the same label.

Variables in the referred element are replaced
with parameters in <param>. 
*/
class FireRef : public SubAction
{
private:
	//label
	//param(s)
};