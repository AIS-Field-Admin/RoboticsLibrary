#pragma once
#ifndef ICONNECTIONMANAGER_H
#define ICONNECTIONMANAGER_H

class IConnectionManager
{
	public:
		~IConnectionManager() = default;

		virtual bool Connect() = 0;

		virtual bool Disconnect() = 0;

		virtual bool IsConnected() = 0;

	protected:

		bool _isConnected;
};


#endif // !ICONNECTIONMANAGER_H