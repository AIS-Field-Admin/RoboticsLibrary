#pragma once

#ifndef IINTERNALORDERSCOURIER_H
#define IINTERNALORDERSCOURIER_H

#include "..\OrderHandler\OrderHandler.h"
#include "..\OrderStore\Order.h"

class IInternalOrdersCourier
{
	public:

		virtual bool RegisterOrderHandler(std::shared_ptr<OrderHandler> orderHandler) = 0;

		virtual bool PostOrder(const Order& order) = 0;

};

#endif // IINTERNALORDERSCOURIER_H
