// chmac.cpp : Defines the entry point for the console application.
//

#include <tchar.h>
#include "NetworkAdapter.h"
#include <iostream>

using namespace CodeProjectUtils;

ADAPTERINFO* adapters = NULL;
CNetworkAdapterList nal;

int reset(_TCHAR* str) {
	int count = nal.GetCount();
	for(int i = 0; i < count; i++) {
		if(adapters[i].Description.find(str) == std::wstring::npos)
			continue;
		std::wcout << L"Resetting " << adapters[i].Description << ": " << adapters[i].MAC << L" -> ";
		wchar_t &last = adapters[i].MAC.at(11);
		++last;
		if(last > L'F')
			last = L'0';
		std::wcout << adapters[i].MAC << std::endl;

		if(!UpdateRegistry(adapters[i].InstanceId, adapters[i].MAC.c_str())) {
			std::cout << "UpdateRegistry failed.\n";
			return -3;
		}

		if(!Reset(&adapters[i])) {
			std::cout << "Reset failed." << std::endl;
			return -4;
		}

		std::cout << "Reset succeeded." << std::endl;
		return 0;
	}
	return -5;
}

int _tmain(int argc, _TCHAR* argv[])
{
	bool do_reset = false;
	if(argc > 1)
		do_reset = true;

	int retval = 0;
	if(!nal.IsValid()) {
		retval = -1;
		goto cleanup;
	}

	int count = nal.GetCount();
	if(count <= 0) {
		retval = -2;
		goto cleanup;
	}
	adapters = new ADAPTERINFO[count];
	nal.GetAdapters(adapters);

	if(do_reset)
		retval = reset(argv[1]);
	else
		for(int i=0; i<count; i++) {
			std::wcout << adapters[i].Description << std::endl;
			std::wcout << adapters[i].InstanceId << std::endl;
			std::wcout << adapters[i].MAC << std::endl;
		}

cleanup:
	delete[]adapters;
	return retval;
}

