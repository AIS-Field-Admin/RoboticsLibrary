#pragma once
#ifndef ORDERHANDLERCOMMAND_H
#define ORDERHANDLERCOMMAND_H

#include<iostream>

#include "..\OrderStore\OrderStorage.h"
#include "..\OrderStore\OrderWrapper.h"
#include "..\OrderStore\Order.h"

class OrderHandlerCommand
{
	public:

		OrderHandlerCommand(std::shared_ptr<IOrderStorage> orderStorage);

		virtual void Execute() = 0;

		bool PostOrder(const Order& order);
	

	protected:

		std::shared_ptr<IOrderStorage> _orderStorage;

};

#endif // ORDERHANDLERCOMMAND_H