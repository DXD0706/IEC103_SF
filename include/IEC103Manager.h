/*
 * IEC103Manager.h
 *
 *  Created on: Jun 19, 2015
 *      Author: root
 */

#ifndef IEC103MANAGER_H_
#define IEC103MANAGER_H_

#include <string.h>
#include <iostream>
#include <signal.h>
#include "Logger.h"
#include "Config.h"
#include "SerialService.h"
#include "TcpService.h"
#include "Serial485ClientService.h"
#include "EncapMysql.h"
#include "MemCache.h"
#include "WarningLib.h"
#include "WgjXml.h"

using namespace std;

#define LOGPATH "./Log/"

class IEC103Manager {
public:
	IEC103Manager();
	virtual ~IEC103Manager();
	bool Init();
	void Start();
	void Stop();
	static void SignalHandle(int sigNo);
private:
	Service * m_service;
};

#endif /* IEC103MANAGER_H_ */
