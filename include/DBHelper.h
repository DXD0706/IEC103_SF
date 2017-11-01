/* 
* Copyright (c) 2015��������һ
* All rights reserved. 
*  
* �ļ����ƣ�DBHelper.h
* �ļ���ʶ���ڴ����ݲ����ӿ�
*  
* ��ʷ�汾��1.0 
* ��    �ߣ��ߺ���
* ��ʼ��������ڣ�2015��5��18�� 
*/

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

#ifdef WIN32

	#ifdef IDBTPYE_EXPORTS
	#define IDBTPYE __declspec(dllexport)
	#else
	#define IDBTPYE __declspec(dllimport)
	#endif
#else
	#define IDBTPYE
#endif


using namespace std;
//���������Զ���
typedef std::vector<unsigned char> BYTES;
typedef std::string KEY;
typedef std::string STRING;
typedef std::vector<KEY> KEYS;
typedef std::vector<STRING> STRINGS;//��
typedef std::vector<std::pair<KEY, BYTES> > PAIRS;
typedef PAIRS::value_type PAIR;
typedef std::pair<int, BYTES> INT_VALUE;
//����Ϣ
enum DATATYPE{TYPE_STRING=1,TYPE_INT32,TYPE_FLOAT,TYPE_LONG,TYPE_BOOL,TYPE_DOUBLE,TYPE_UNKOWN};
//����ģʽ
#define SUB_TYPE 1  //���ݶ���ģʽ
#define PUB_TYPE 0  //���ݷ���ģʽ
#define DEFAULT_TAGNAME_LEN 64 
#define DEFAULT_DATA_LEN   128
#define DEFAULT_CHENEL_LEN  10
const std::string DEFAULT = "TESTNO";
#pragma pack(push,1)
struct Tag
{
	Tag(){
		dataType = TYPE_UNKOWN;
		memset(pName,0,sizeof(pName));
		memset(pdata,0,sizeof(pdata));
		m_dataSize = 0;//Ĭ�ϲ��÷����ڴ�
		pResizeData = NULL;
	}
	~Tag(){
		if (pResizeData)
		{
			delete []pResizeData;
			pResizeData = NULL;
		}
	}
public:
	char dataType;
	char pName[DEFAULT_TAGNAME_LEN];
	char pdata[DEFAULT_DATA_LEN];
	char *pResizeData;
	int m_dataSize;
public:
	Tag& operator = (Tag &m_right)
	{
		dataType = m_right.dataType;
		memcpy(pName,m_right.pName,sizeof(m_right.pName));
		memcpy(pdata,m_right.pdata,sizeof(m_right.pdata));
		return *this;
	}
	void ZeroTag()
	{
		dataType = TYPE_UNKOWN;
		memset(pName,0,sizeof(pName));
		memset(pdata,0,sizeof(pdata));
		if (pResizeData)
		{
			delete []pResizeData;
			pResizeData = NULL;
		}
	}
	void CopyStrData(const char * pSrcData,int len)
	{
		if (len<0)
		{
			return;
		}
		if ( len > 0 && len < DEFAULT_DATA_LEN )
		{
			memcpy(pdata,pSrcData,len);
		}
		else
		{
			
			if (pResizeData == NULL)
			{
				pResizeData = new char[len+1];
				memset(pResizeData,0,len+1);
				m_dataSize = len;
				memcpy(pResizeData,pSrcData,len);
			}
			else
			{
				delete []pResizeData;
				pResizeData = new char[len+1];
				memset(pResizeData,0,len+1);
				m_dataSize = len;
				memcpy(pResizeData,pSrcData,len);
			}
		}
		return;

	}
};
#pragma pack(pop)



//
//��д�ڴ����ݿ�����࣬��װ��ϸ�ڲ���
//��ʼ����2015-5-4
class  IDB_Type
{
public:
	IDB_Type(){
		
	}
	virtual~IDB_Type(){}
public:
	//***************************************************************************
	//���ܣ������ڴ����ݿ⺯�� OK
	//���룺������Ip ��host �������˿ڣ�port,ConnectTpye��������1:���ģ�0������
	//��������ӳɹ����
	//ʱ�䣺[2015/5/18]
	//���ߣ�GHQ
	//***************************************************************************
	virtual bool Connect(int ConnectTpye,const char* host,unsigned short u_port  ) = 0;
	
	//***************************************************************************
	//���ܣ�������ݿ��Ƿ��������� OK
	//���룺ConnectTpye���ͣ��Ƕ��Ļ��Ƿ���ģʽ
	//������ɹ����
	//ʱ�䣺[2015/5/18]
	//���ߣ�GHQ
	//***************************************************************************
	virtual bool check_connection(int ConnectTpye) = 0;


	//***************************************************************************
	//���ܣ��Ͽ��ڴ����ݿ����Ӽ��ͷ���Դ���� OK
	//���룺
	//������Ͽ��ɹ����
	//ʱ�䣺[2015/5/18]
	//���ߣ�GHQ
	//***************************************************************************
	virtual bool DisConnect() = 0;


	//***************************************************************************
	//���ܣ�д��������(key ,value)����������д�����Ļ�Ч�ʺܵ� OK
	//���룺m_key�����֣�value��ֵ
	//�����
	//ʱ�䣺[2015/5/18]
	//���ߣ�GHQ
	//***************************************************************************
	virtual bool WritePointValue(const char* m_key,const char* value) = 0;
	
	
	//***************************************************************************
	//���ܣ�д��������(key ,value)����������д�����Ļ�Ч�ʺܵ� OK
	//���룺m_key�����֣�value��ֵ
	//�����
	//ʱ�䣺[2015/5/18]
	//���ߣ�GHQ
	//***************************************************************************
	virtual bool WritePointValue(Tag *m_tag) = 0;


	//***************************************************************************
	//���ܣ�д�������(pTags)����д OK
	//���룺pTags��m_count����
	//������ɹ����
	//ʱ�䣺[2015/5/18]
	//���ߣ�GHQ
	//***************************************************************************
	virtual bool WritePointsValue(Tag * pTags,int m_count) = 0;


	//***************************************************************************
	//���ܣ�д�������(pTags)����д OK
	//���룺pTags��m_count����
	//������ɹ����
	//ʱ�䣺[2015/5/18]
	//���ߣ�GHQ
	//***************************************************************************
	virtual bool WritePointsValue(std::vector<Tag>& m_tag_ver) = 0;


	//***************************************************************************
	//���ܣ�����������(key ,value)����������д�����Ļ�Ч�ʺܵ�
	//���룺m_key�����֣�value��ֵ
	//������ɹ����
	//ʱ�䣺[2015/5/18]
	//���ߣ�GHQ
	//***************************************************************************
	virtual bool ReadPointValue(const char* m_key, char* value) = 0;
	


	//***************************************************************************
	//���ܣ�����������(tag)����������д�����Ļ�Ч�ʺܵ� 0K
	//���룺m_key�����֣�value��ֵ
	//�����
	//ʱ�䣺[2015/5/18]
	//���ߣ�GHQ
	//***************************************************************************
	virtual bool ReadPointValue(Tag *m_tag) = 0;

	//***************************************************************************
	//���ܣ�����������(tag) OK
	//���룺m_tag��㣬tagNum��Ҫ���ĵ���
	//�����m_count���صĵ���
	//ʱ�䣺[2015/5/18]
	//���ߣ�GHQ
	//***************************************************************************
	virtual bool ReadPointsValue(Tag *m_tag,int tagNum ) = 0;

	//***************************************************************************
	//���ܣ������Ƿ����� OK
	//���룺name ������
	//������ɹ����
	//ʱ�䣺[2015/5/18]
	//���ߣ�GHQ
	//***************************************************************************
	virtual bool ExistPoint(const char*  name) = 0;




	//***************************************************************************
	//���ܣ�ģ���ź�֪ͨ����,�ͻ���д���ݺ���ã�ʵʱ��Ӧ���ݸ��� OK
	//���룺��Ҫ֪ͨ��ͨ��������֪ͨ���ͨ��pCh,m_ch_sizeͨ������
	//�����
	//ʱ�䣺[2015/5/18]
	//���ߣ�GHQ
	//***************************************************************************
	virtual void post( char *pCh,int m_ch_size) = 0;


	//***************************************************************************
	//���ܣ��ȴ�ͨ��֪ͨ OK
	//���룺
	//�����
	//ʱ�䣺[2015/5/18]
	//���ߣ�GHQ
	//***************************************************************************
	virtual bool wait(int timeout = 0) = 0;


	//***************************************************************************
	//���ܣ���������ͨ�������� OK
	//���룺pCh��Ҫ���ĵ�ͨ������
	//�����
	//ʱ�䣺[2015/5/18]
	//���ߣ�GHQ
	//***************************************************************************
	virtual void subscribe( char *pCh,int m_ch_size ) = 0;

	//***************************************************************************
	//���ܣ����û�����С
	//���룺m_sizeԤ���������������С
	//�����
	//ʱ�䣺[2015/5/18]
	//���ߣ�GHQ
	//***************************************************************************
	virtual void SetVecSize(int m_size) = 0;

	//***************************************************************************
	//���ܣ���ȡ���µ����ݵ�
	//���룺m_max_sizeȡ�����ֵ��m_tag��ʼ��������
	//�����
	//ʱ�䣺[2015/5/18]
	//���ߣ�GHQ
	//***************************************************************************
	virtual int GetUpdatePoints(Tag *m_tag,int m_max_size) = 0;

	//����ת����������
public:
virtual	void FloatToStr(float f_value,char* pData) = 0;
virtual void IntToStr(int f_value,char* pData) = 0;
virtual	void BoolToStr(bool b_value,char* pData) = 0;


public:
	std::string m_chenle;//ͨ��
	std::vector< Tag > m_tag_vec;
};










typedef IDB_Type* IDB_PtrT;