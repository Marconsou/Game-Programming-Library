#include "CardStats.h"

using namespace std;
using namespace TT;

CardStats::CardStats(const CardID id,const string& name,const int level,const int left,const int top,const int right,const int bottom,const Elemental elemental) :
id(id),
name(name),
level(level),
left(left),
top(top),
right(right),
bottom(bottom),
elemental(elemental)
{

}

CardID CardStats::GetID() const
{
	return this->id;
}

const string& CardStats::GetName() const
{
	return this->name;
}

int CardStats::GetLevel() const
{
	return this->level;
}

int CardStats::GetLeft() const
{
	return this->left;
}

int CardStats::GetTop() const
{
	return this->top;
}

int CardStats::GetRight() const
{
	return this->right;
}

int CardStats::GetBottom() const
{
	return this->bottom;
}

Elemental CardStats::GetElemental() const
{
	return this->elemental;
}