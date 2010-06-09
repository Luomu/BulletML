// Include StdAfx
#include "StdAfx.h"

//////////////////////////////////////////////////////////////////////////////////
// Conditions
//////////////////////////////////////////////////////////////////////////////////
long ExtObject::cFinished(LPVAL params)
{
	if(unreportedFinish == true && manager.finished())
	{
		unreportedFinish = false;
		return 1;
	}
	return 0;
}

long ExtObject::cIsRunning(LPVAL params)
{
	if(manager.finished())
		return false;
	return true;
}

long ExtObject::cErrorOccurred(LPVAL params)
{
	if(unreportedError)
	{
		unreportedError = false;
		return 1;
	}
	return 0;
}

// This is taken almost 1:1 from Sprite
long ExtObject::cOnCollision(LPVAL params)
{
	CRunObjType* pOtherType = params[0].GetObjectParam(pRuntime);

	if (pOtherType == NULL)
		return FALSE;

	void* pCurrentCnd = pRuntime->GetCurrentConditionPtr();

	// No collision record for this condition yet: create one
	if (collisionMemory.find(pCurrentCnd) == collisionMemory.end())
		collisionMemory[pCurrentCnd] = set<CRunObject*>();

	map<void*, set<CRunObject*> >::iterator c = collisionMemory.find(pCurrentCnd);
	set<CRunObject*>& cur_set = c->second;

	// Iterate all object instances and check if a first instance of collision has happened
	CRunObject** objects;
	int count;
	pRuntime->GetTypeSelectedInstances(pOtherType, objects, count);

	if (count == 0 || objects == NULL)
		return FALSE;

	// For each othertype object
	CRunObject** end = objects + count;
	CRunObject** i = objects;

	// Take local copy since SOL modified
	vector<CRunObject*> vec;
	vec.reserve(count);

	for ( ; i != end; ++i)
		vec.push_back(*i);

	bool any_collisions_happened = false;

	vector<CRunObject*>::iterator v = vec.begin();
	vector<CRunObject*>::iterator v_end = vec.end();

	for ( ; v != v_end; ++v) {
		bool isOverlapping = manager.queryCollision((*v)->info.box);

		// Is overlapping
		if (isOverlapping) {

			// See if this object is in the set yet
			set<CRunObject*>::iterator f = cur_set.find(*v);

			// If not, add it and fire condition
			if (f == cur_set.end()) {
				cur_set.insert(*v);

				if (!pRuntime->IsSelectedF(*v, pOtherType))
					pRuntime->SelectF(*v, pOtherType);

				any_collisions_happened = true;
			}
		}
		// Is not overlapping: remove any record if there is one of this object
		else {
			if (!cur_set.empty()) {
				set<CRunObject*>::iterator f = cur_set.find(*v);

				if (f != cur_set.end())
					cur_set.erase(f);
			}
		}
	}

	if (any_collisions_happened)
		return true;
	else
		return pRuntime->SelectRegisteredCollisions(this, pOtherType);
}