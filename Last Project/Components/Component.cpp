#include "Component.h"

Component::Component(const GraphicsInfo &r_GfxInfo)
{
	m_GfxInfo = r_GfxInfo;	
	ID = ID_cnt;
	ID_cnt++;
	m_Label = "";
	sel_ect = false;
	cut = false;
}
GraphicsInfo Component::get_info()
{
	return m_GfxInfo;
}
void Component::setx(int l)
{
	saved_x = l;
}

int Component::getx()
{
	return saved_x;
}

void Component::sety(int l)
{
	saved_y = l;
}

int Component::gety()
{
	return saved_y;
}

void Component::Sel()
{
	sel_ect = !sel_ect;
}

Component::Component()
{
	ID = ID_cnt;
	ID_cnt++;
	m_Label = "";
	sel_ect = false;
	cut = false;
}
bool Component::IsSelected()
{
	return sel_ect;
}
void Component::set_ID(int a)
{
	ID = a;
}
void Component::set_IDCnt(int a)
{
	ID_cnt = a;
}
int Component::get_ID()
{
	return ID;
}

void Component::setcut(bool f)
{
	cut = f;
}

bool Component::getcut()
{
	return cut;
}

void Component::setlabel(string a)
{
	m_Label = a;
}
string Component::getlabel()
{
	return m_Label;
}
Component::~Component()
{
}

int Component::ID_cnt = 1;
