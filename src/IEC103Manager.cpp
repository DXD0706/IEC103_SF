/*
 * IEC103Manager.cpp
 *
 *  Created on: Jun 19, 2015
 *      Author: root
 */

#include "IEC103Manager.h"


IEC103Manager::IEC103Manager():m_service(NULL)
{

}

IEC103Manager::~IEC103Manager()
{
	delete m_service;
}

bool IEC103Manager::Init()
{
	//初始化日志文件
	//InitLogging("",(LogLevel)Config::GetInstance()->GetLogLv(),string(LOGPATH + Config::GetInstance()->GetChannelName() + "/").c_str());
	LOG_INITPATH(LOGPATH + Config::GetInstance()->GetChannelName() + "/");
	WgjXml wgjXMl;
	if(!wgjXMl.LoadXml("Configuration.xml"))
	{
		LOG_ERROR("Configuration read error");
		return false;
	}

	string redis_ip;
	int redis_port;
	wgjXMl.GetRedisConnectionConfig(redis_ip,redis_port);
	WgjFunctionEx::GetInstance()->InitParam(Config::GetInstance()->GetChannelName(), redis_ip,redis_port);
	vector<string> vecChannel = wgjXMl.GetTransmitChannel();

	wgjXMl.InitIEC103Xml(Config::GetInstance()->GetChannelName());
	IEC103::Map_IEC103Config mapConfig = wgjXMl.GetIEC103Param();
	if(mapConfig.size() == 0)
	{
		LOG_ERROR("1 NULL read channel data error");
	}
	else
	{
		IEC103::Map_IEC103Config::iterator it = mapConfig.begin();

		Config::GetInstance()->SetIp(it->second.ip_A);
		Config::GetInstance()->SetUdpPort(it->second.A_Port);
	}


	IEC103::Map_IEC103Point mapIEDPoint = wgjXMl.GetIEC103Point();
	IEC103::Map_IEC103Point::iterator it1 = mapIEDPoint.begin();

	map<string, string> mapPoint = it1->second;


	signal(SIGTERM, SignalHandle);

	//初始化服务
	uint16_t netType = Config::GetInstance()->GetNetType();

	std::string strNetType("");
	if(1 == netType)
	{
		if(Config::RS485_CLIENT_RUN == Config::GetInstance()->GetIec103RunType())
		{
			m_service = new Serial485ClientService();
		}
		else
		{
			m_service = new SerialService();
		}
		strNetType = "serial";
	}
	else if(2 == netType)
	{
		//网络通信
		strNetType = "Internet";
		m_service = new Service();
		m_service->setChannel(vecChannel);
		m_service->setChannel("config");
		m_service->setPointAddrMap(mapPoint);
		if(m_service->connectRedis(redis_ip,redis_port))
		{
			WgjFunctionEx::GetInstance()->LogSend(LOGINFO::INFO,LOGINFO::NORMAL,"start parse");
		}
	}
	else
	{
		LOG_ERROR("invalid netType \n");
		return false;
	}


	return true;
}

void IEC103Manager::Start()
{
	m_service->Start();  //启动服务
}

void IEC103Manager::Stop()
{
	WarningLib::GetInstance()->Stop();
}

void IEC103Manager::SignalHandle(int sigNo)
{
	INFO("received SIGTERM IEC103 pid[%d] exit\n", getpid() );
	WarningLib::GetInstance()->Stop();
	exit(0);
}
