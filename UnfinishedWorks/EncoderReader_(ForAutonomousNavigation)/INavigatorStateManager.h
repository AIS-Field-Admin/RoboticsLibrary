#pragma once
#ifndef INAVIGATORSTATEMANAGER_H
#define INAVIGATORSTATEMANAGER_H


class INavigatorStateManager
{
	public:
		virtual void UpdateStates(const char* data) = 0;

};

#endif // INAVIGATORSTATEMANAGER_H