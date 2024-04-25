#pragma once

#ifndef IORDERSTORAGE_H
#define IORDERSTORAGE_H

#include <iostream>
#include <queue>
#include <mutex>

class IOrderStorage
{
	public:
		virtual ~IOrderStorage() = default;

		virtual void AddOrder(const std::string order) = 0;

		virtual std::queue<std::string> GetOrders() = 0;

		virtual void CleanOrders() = 0;

		virtual std::string GetStorageName() = 0;

};

#endif IORDERSTORAGE_H

