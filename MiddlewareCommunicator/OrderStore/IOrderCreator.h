#pragma once

#ifndef IORDERCREATOR_H
#define IORDERCREATOR_H

#include <iostream>
#include <map>
#include "OrderWrapper.h"

class IOrderCreator
{
	public:

		virtual bool ConstructOrderCreator(std::string recipientName, std::string senderName) = 0;
		virtual std::string CreateOrder(std::string orderType, const std::map<std::string, std::string>& parameters) = 0;

};

#endif // !IORDERCREATOR_H