#pragma once

#ifndef IEXTERNALMODULEBOUNDARY_H
#define IEXTERNALMODULEBOUNDARY_H

#include <iostream>
#include <queue>

class IExternalModuleBoundary
{
	public:

		virtual ~IExternalModuleBoundary() = default;

		virtual bool SetOrder(const std::string& order) = 0;

		virtual std::queue<std::string> GetOrders() = 0;

		virtual bool Start() = 0;
};

#endif // IEXTERNALMODULEBOUNDARY_H
