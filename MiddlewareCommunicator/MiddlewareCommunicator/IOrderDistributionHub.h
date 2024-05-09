#pragma once

#ifndef IORDERDISTRIBUTIONHUB_H
#define IORDERDISTRIBUTIONHUB_H

#include "..\OrderHandler\OrderHandler.h"
#include "..\OrderStore\Order.h"

class IOrderDistributionHub
{
	public:

		virtual bool Run() = 0;

		virtual bool Stop() = 0;

};

#endif IORDERDISTRIBUTIONHUB_H