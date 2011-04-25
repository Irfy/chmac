/*
	Copyright(C) Nishant Sivakumar, 2005. All rights reserved.
	http://blog.voidnish.com
*/

#pragma once

#include <windows.h>
#include <string>
#include <tchar.h>

#pragma comment(lib,"Iphlpapi.lib")
#include <Iphlpapi.h>

#pragma comment(lib,"Rpcrt4.lib")

#include <netcon.h>

namespace CodeProjectUtils
{
	struct ADAPTERINFO
	{
		ADAPTERINFO()
		{
			InstanceId = Description = MAC = _T("");
		}
		std::wstring InstanceId;
		std::wstring Description;
		std::wstring MAC;
	};

	class CNetworkAdapterList
	{
	public:
		CNetworkAdapterList(void);
		~CNetworkAdapterList(void);
	private:
		PIP_ADAPTER_INFO pAdapterInfo;
		int m_count;
	public:
		bool IsValid(void);
		int GetCount(void);
		int GetAdapters(ADAPTERINFO* pADAPTERINFO);
	};

	bool EnableConnection(GUID guidId, bool bEnable);
	bool UpdateRegistry(std::wstring strNetCfgInstanceId, LPCTSTR lpszMacID = NULL);
	bool Reset(ADAPTERINFO* pAdInfo);
	DWORD ErrorCOMToWin32(HRESULT hr);
}